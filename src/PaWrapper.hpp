/*
** EPITECH PROJECT, 2021
** babel
** File description:
** Created by seb,
*/

#pragma once

#include "includes/portaudio.h"

#define SAMPLE_RATE (44100)
#define FRAMES_PER_BUFFER (1024)

struct PaBuffer {
	float buffers[2][FRAMES_PER_BUFFER];
};

class PaWrapper {
public:
	PaWrapper();

	void startRecord();
	void record();
	void stopRecord();
	void startPlay();
	void play(PaBuffer const&);
	void stopPlay();

	PaBuffer &getBuffer();

private:

	PaBuffer		_buff;
	PaStreamParameters	_in;
	PaStreamParameters	_out;
	//OpusEncoder		*_encoder;
	//OpusDecoder		*_decoder;
	PaStream 		*_streamIn;
	PaStream 		*_streamOut;
};
