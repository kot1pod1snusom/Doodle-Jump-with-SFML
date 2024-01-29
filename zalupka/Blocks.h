#pragma once
#include "Classes.h"

class Usual_Block : public Block {
public:
	
	Usual_Block(int x, int y) : Block(x , y, sf::Color::Green){
		
	}

	int kol_do(Dodle& dl) override {
		dl.move_up_down = true;
		return 0;
	}
};


class Break_Block : public Block {
	Sound sound_break;
public:
	

	Break_Block(int x, int y) : Block(x, y, sf::Color::Black) {
		sound_break.setSound();
	};


	int kol_do(Dodle& dl) override {
		


		return 0;
	}
};