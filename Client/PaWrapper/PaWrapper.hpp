/*
** EPITECH PROJECT, 2021
** babel
** File description:
** Created by seb,
*/

#pragma once

#include <portaudio.h>
#include <opus/opus.h>
#include <vector>

#define SAMPLE_RATE (48000)
#define FRAMES_PER_BUFFER (960)
#define MAX_PACKET (FRAMES_PER_BUFFER * 2 * 2)

struct CompData {
	std::vector<unsigned char>	data;
	int				length;
};

class PaWrapper {
public:
	PaWrapper();

	void startRecord();
	void record();
	void stopRecord();
	void startPlay();
	void play(CompData const&);
	void stopPlay();

	CompData &getData();


private:
	CompData		_comp;
	std::vector<float>	_buff;
	PaStreamParameters	_in;
	PaStreamParameters	_out;
	OpusEncoder		*_encoder;
	OpusDecoder		*_decoder;
	PaStream 		*_streamIn;
	PaStream 		*_streamOut;
};
