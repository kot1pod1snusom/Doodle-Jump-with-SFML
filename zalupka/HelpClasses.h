#pragma once
#include "Classes.h"


class Buttion {
	int x;
	int y;

	int xend;
	int yend;
	sf::Texture t;
	sf::RectangleShape button;

public:

	Buttion(int x_raz, int y_raz, int x, int y) : x(x), y(y), xend(x + x_raz), yend(y + y_raz) {
		button = sf::RectangleShape((sf::Vector2f(x_raz, y_raz)));

		button.setPosition(x, y);
	}

	void setTexture(string file_name) {
		t.loadFromFile(file_name);

		button.setTexture(&t);
	}

	bool TapCheck(sf::Vector2i mousecoord) {
		if ((mousecoord.x >= x && mousecoord.x <= xend) && (mousecoord.y >= y && mousecoord.y <= yend))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	void draw(sf::RenderWindow* w) {
		w->draw(button);
	}
};

class Sound {

	sf::SoundBuffer buf;
	sf::Sound s;

public:

	void setSound(string str) {
		buf.loadFromFile(str);
	}

	void play(Settings set) {
		if (set.music_on_off == true)
		{
			s.setBuffer(buf);
			s.play();
		}
	}

	void setVolume(int volume) {
		s.setVolume(volume);
	}
};

class Music {

	sf::Music mc;

public:

	Music(bool LoopKey, int volume) {
		mc.setLoop(LoopKey);
		mc.setVolume(volume);
	}

	void setMusic(string str) {
		mc.openFromFile(str);
	}

	void play(Settings s) {
		if (s.music_on_off == true)
		{
			mc.play();
		}
	}

	void stop() {
		mc.stop();
	}

	void setVolume(int volume) {
		mc.setVolume(volume);
	}
};
