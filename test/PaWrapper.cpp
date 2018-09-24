/*
** EPITECH PROJECT, 2021
** babel
** File description:
** Created by seb,
*/
#include "PaWrapper.hpp"
#include <iostream>
#include <vector>

PaWrapper::PaWrapper() {

	/// Initialise microphone
	_in.device = Pa_GetDefaultInputDevice(); /* default input device */
	if (_in.device == paNoDevice) {
		std::cout << "Error: No default input device." << std::endl;
	}
	_in.channelCount = 2;                    /* stereo input */
	_in.sampleFormat = paFloat32;
	_in.suggestedLatency = Pa_GetDeviceInfo(_in.device)->defaultLowInputLatency;
	_in.hostApiSpecificStreamInfo = NULL;


	/// Initialise data
	int totalFrames, numSamples, numBytes;
	_data.maxFrameIndex = totalFrames = 60 * 44100;
	_data.frameIndex = 0;
	numSamples = totalFrames * 2;
	numBytes = numSamples * sizeof(float);
	_data.recordedSamples = (float *) malloc(numBytes);
	if (_data.recordedSamples == NULL) {
		printf("Could not allocate record array.\n");
	}
	for (long i = 0; i < numSamples; i++) _data.recordedSamples[i] = 0;


	/// Initialise the encoder
	int err;
	_encoder = opus_encoder_create(44100, 2, OPUS_APPLICATION_AUDIO, &err);
	if (err < 0) {
		std::cout << "ERROR: couldn't create encoder." << std::endl;
		exit(0);
	}
	opus_encoder_ctl(_encoder, OPUS_SET_BITRATE(64000));


	/// Initialise speakers
	_out.device = Pa_GetDefaultOutputDevice(); /* default output device */
	if (_out.device == paNoDevice) {
		std::cout << "Error: No default output device." << std::endl;
		exit(0);
	}
	_out.channelCount = 2;                     /* stereo output */
	_out.sampleFormat = paFloat32;
	_out.suggestedLatency = Pa_GetDeviceInfo(_out.device)->defaultLowOutputLatency;
	_out.hostApiSpecificStreamInfo = NULL;


	/// Initialise decoder
	_decoder = opus_decoder_create(44100, 2, &err);
	if (err<0)
	{
		std::cout << "Error: failed to create decoder" << std::endl;
		exit(0);
	}
}

void PaWrapper::startRecord() {
	std::vector<unsigned short> captured(512 * 2);

	if (Pa_OpenStream(
		&_stream, &_in, NULL, 44100, 512, paClipOff, recordCallback, &_data) != paNoError) {
		std::cout << "ERROR: can't open stream" << std::endl;
		return;
	}

	while (Pa_IsStreamActive(_stream) == 1) {
		//Pa_Sleep(1000);
		printf("index = %d\n", _data.frameIndex);
		fflush(stdout);
		opus_encode(_encoder, in, 512*2, cbits, 512*2);
	}
}

int PaWrapper::recordCallback( const void *inputBuffer, void *outputBuffer,
			   unsigned long framesPerBuffer,
			   const PaStreamCallbackTimeInfo* timeInfo,
			   PaStreamCallbackFlags statusFlags,
			   void *userData )
{
	auto data = static_cast<paTestData*>(userData);
	auto rptr = static_cast<const float*>(inputBuffer);
	float *wptr = &data->recordedSamples[data->frameIndex * 2];
	long framesToCalc;
	long i;
	int finished;
	auto framesLeft = static_cast<unsigned long>(data->maxFrameIndex - data->frameIndex);

	(void) outputBuffer; /* Prevent unused variable warnings. */
	(void) timeInfo;
	(void) statusFlags;
	(void) userData;

	if( framesLeft < framesPerBuffer )
	{
		framesToCalc = framesLeft;
		finished = paComplete;
	}
	else
	{
		framesToCalc = framesPerBuffer;
		finished = paContinue;
	}

	if( inputBuffer == NULL )
	{
		for( i=0; i<framesToCalc; i++ )
		{
			*wptr++ = 0.0f;  /* left */
			if( 2 == 2 ) *wptr++ = 0.0f;  /* right */
		}
	}
	else
	{
		for( i=0; i<framesToCalc; i++ )
		{
			*wptr++ = *rptr++;  /* left */
			if( 2 == 2 ) *wptr++ = *rptr++;  /* right */
		}
	}
	data->frameIndex += framesToCalc;
	return finished;
}