/*
** EPITECH PROJECT, 2021
** babel
** File description:
** Created by seb,
*/

#pragma once


#include <includes/portaudio.h>
#include <opus/opus.h>

#define NUM_SECONDS (10)
#define SAMPLE_RATE (44100)
#define FRAMES_PER_BUFFER (1024)

class PaWrapper {
public:
	PaWrapper();

	void startRecord();
	void listenRecord(void **buffer);

private:

	PaStreamParameters	_in;
	PaStreamParameters	_out;
	OpusEncoder		*_encoder;
	OpusDecoder		*_decoder;
	PaStream 		*_streamIn;
	PaStream 		*_streamOut;
};
