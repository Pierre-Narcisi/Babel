#include <iostream>
#include "src/PaWrapper.hpp"

/*
** EPITECH PROJECT, 2021
** babel
** File description:
** Created by seb,
*/

int main()
{
	PaWrapper oui;
	oui.startRecord();
	oui.startPlay();
	while (1) {
		oui.record();
		oui.play(oui.getData());
	}
	oui.stopRecord();
	oui.stopPlay();
}