/*
** EPITECH PROJECT, 2021
** babel
** File description:
** Created by seb,
*/
#include "PaWrapper.hpp"
#include <iostream>
#include <vector>
#include <cstring>

PaWrapper::PaWrapper() {
	if (Pa_Initialize() != paNoError) {
		std::cout << "JE ME TIRE, lES RAGEUX SONT DANS LES RETROS" << std::endl;
		exit(0);
	}

	/// Initialise microphone
	_in.device = Pa_GetDefaultInputDevice(); /* default input device */
	if (_in.device == paNoDevice) {
		std::cout << "Error: No default input device." << std::endl;
	}
	_in.channelCount = 2;                    /* stereo input */
	_in.sampleFormat = paFloat32;
	_in.suggestedLatency = Pa_GetDeviceInfo(_in.device)->defaultLowInputLatency;
	_in.hostApiSpecificStreamInfo = NULL;


	/*/// Initialise the encoder
	int err;
	_encoder = opus_encoder_create(48000, 2, OPUS_APPLICATION_AUDIO, &err);
	if (err != OPUS_OK) {
		std::cout << "ERROR: couldn't create encoder. " << OPUS_OK << " " << err << std::endl;
		std::cout << opus_strerror(err) << std::endl;
		exit(0);
	}
	opus_encoder_ctl(_encoder, OPUS_SET_BITRATE(64000));*/


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


	/*/// Initialise decoder
	_decoder = opus_decoder_create(48000, 2, &err);
	if (err<0)
	{
		std::cout << "Error: failed to create decoder" << std::endl;
		exit(0);
	}
	opus_decoder_ctl(_decoder, OPUS_SET_BITRATE(64000));*/

	if (Pa_OpenStream(
		&_streamIn, &_in, NULL, SAMPLE_RATE, FRAMES_PER_BUFFER, paClipOff, NULL, NULL) != paNoError) {
		std::cout << "ERROR: can't open stream" << std::endl;
		return;
	}

	if (Pa_OpenStream(&_streamOut, NULL, &_out, SAMPLE_RATE, FRAMES_PER_BUFFER, paClipOff, NULL, NULL) != paNoError) {
		std::cout << "ERROR: can't open stream" << std::endl;
		return;
	}
}

void PaWrapper::startRecord() {
	if (Pa_IsStreamActive(_streamIn) != 1)
		Pa_StartStream(_streamIn);
}

void PaWrapper::record() {
	int err = 0;

	std::memset(_buff.buffers, 0, sizeof(_buff));

	if (Pa_IsStreamActive(_streamIn) == 1 && Pa_GetStreamReadAvailable( _streamIn ) >= FRAMES_PER_BUFFER) {
		if ((err = Pa_ReadStream(_streamIn, _buff.buffers, FRAMES_PER_BUFFER)) != paNoError) {
			std::cout << "Read " << Pa_GetErrorText(err) << std::endl;
		}
			/*if ((size = opus_encode_float(_encoder,
						      reinterpret_cast<float*>(buffers), FRAMES_PER_BUFFER, comp, FRAMES_PER_BUFFER * 2)) < 0) {
				std::cout << "Encode " << opus_strerror(size) << std::endl;
				exit(0);
			}

			for (int i = 0; i < FRAMES_PER_BUFFER; i++)
				leftBuffer[i] = 0.0f;
			for (int i = 0; i < FRAMES_PER_BUFFER; i++)
				rightBuffer[i] = 0.0f;

			if (size > 0 && (sizeout = opus_decode_float(_decoder, comp, size,
							       reinterpret_cast<float*>(buffers), FRAMES_PER_BUFFER, 0)) < 0) {
				std::cout << "Decode " << opus_strerror(sizeout) << std::endl;
				exit(0);
			}*/
		}
}

void PaWrapper::stopRecord() {
	if (Pa_IsStreamActive(_streamIn) == 1)
		Pa_StopStream(_streamIn);
}


void PaWrapper::startPlay() {
	if (Pa_IsStreamActive(_streamOut) != 1)
		Pa_StartStream(_streamOut);
}

void PaWrapper::play(PaBuffer const & buff) {
	int err;

	if (Pa_IsStreamActive(_streamOut) == 1) {
		err = Pa_WriteStream(_streamOut, buff.buffers,
				     FRAMES_PER_BUFFER);
		if (err != paNoError) {
			std::cout << "Write " << Pa_GetErrorText(err)
				  << std::endl;
			exit(0);
		}
	}
}

void PaWrapper::stopPlay() {
	if (Pa_IsStreamActive(_streamOut) == 1)
		Pa_StopStream(_streamOut);
}

PaBuffer& PaWrapper::getBuffer() {
	return _buff;
}