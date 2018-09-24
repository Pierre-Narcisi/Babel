/*
** EPITECH PROJECT, 2021
** babel
** File description:
** Created by seb,
*/

#pragma once


#include <includes/portaudio.h>
#include <opus/opus.h>

class PaWrapper {
public:
	PaWrapper();

	void startRecord();
	static int recordCallback( const void *inputBuffer, void *outputBuffer,
				   unsigned long framesPerBuffer,
				   const PaStreamCallbackTimeInfo* timeInfo,
				   PaStreamCallbackFlags statusFlags,
				   void *userData );

private:
	typedef struct
	{
		int	frameIndex;
		int	maxFrameIndex;
		float	*recordedSamples;
	} paTestData;

	PaStreamParameters	_in;
	PaStreamParameters	_out;
	OpusEncoder		*_encoder;
	OpusDecoder		*_decoder;
	PaStream 		*_stream;
	paTestData		_data;
};
