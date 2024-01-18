#pragma once
#include "Blocks.h"


class Block;

class Dodle {
public:
	//Координаты верхнего левого угла
	int x = 200;
	int y = 700;

	//Координаты нижнего правого угла
	int xend = x + 100;
	int yend = y + 100;

	//Расстояние, которое должен преодолеть Doodle в x;
	int Distance = 350;
	int Distance_count = 0;

	int Score = 0;

	sf::Texture DoodleRightTexture;
	sf::Texture DoodleLeftTexture;
	//False - движение вниз, true - давижение вверх
	bool move_up_down = false;

	sf::RectangleShape Doodle;


	Dodle() {
		Doodle = sf::RectangleShape(sf::Vector2f(100, 100));

		string left = "Pics\\game\\dudl_left.png";
		DoodleLeftTexture.loadFromFile(left);

		string right = "Pics\\game\\dudl_right.png";
		DoodleRightTexture.loadFromFile(right);
		Doodle.setTexture(&DoodleRightTexture);


	}
	
	void NewGame() {
		x = 200;
		y = 700;
		xend = x + 100;
		yend = y + 100;
		move_up_down = false;
		Distance_count = 0;
		Score = 0;
	}

	//Движение 
	void Player_Move() {
		if (sf::Keyboard::isKeyPressed(sf::	Keyboard::A))
		{
			x--;
			//Меняем текстурку дудла на направленного в левую сторону
			Doodle.setTexture(&DoodleLeftTexture);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			x++;
			
			//Меняем текстурку дудла на направленного в правую сторону
			Doodle.setTexture(&DoodleRightTexture);
		}

		if (x >= 1000)
		{
			x = 0 - 20;
		}
		else if (x <= -21)
		{
			x = 1000;
		}

		yend = y + 100;
		xend = x + 100;
		
	}
};





class Block {
public:
	//Координаты верхнего левого угла
	int x;
	int y;

	//Координаты нижнего правого угла 
	int x_end;
	int y_end;


	bool kollizion_up = false;


	sf::RectangleShape Blok;


	Block(int x, int y) : x(x), y(y), x_end(x + 150), y_end(y + 10) {
		Blok = sf::RectangleShape((sf::Vector2f(100.f, 15.f)));

		sf::Texture t;
		string str1 = (filesystem::current_path() / "Pics\\platform.png").string();
		string str = "Pics\\game\\platform.png";
		t.loadFromFile(str);
		Blok.setFillColor(sf::Color::Green);
		Blok.setTexture(&t);

		Blok.setPosition(x, y);
	}

	//Двигаем платформу вверх
	void Move_down() {
		y++;
		y_end++;
		Blok.setPosition(x ,y );
	}

	//Когда блок ушел за грань видимости, спавним его вверху 
	void Brick_relocate() {
		if (y >= 1080)
		{
			y = 0 - 10; // Спавним так, чтобы платформы не спавнились на глазах
			x = (rand() % (1000 - 150)) + 1; //Первое число - количество пикселей окна по х, вычитая xend, чтобы платформа не выходила за текстурки

			x_end = x + 150;
			y_end = y + 10;

			Blok.setPosition(x, y);
		}
		else
		{
			return;
		}
	}

};


class Player {
public:
	int MaxScore = 0;
	int TotalGames = 0;
	int AverageScore = 0;
	int ScoreSum = 0;
};

class Settings {
public:
	float sound_volume = 0;

	//true - on, false - off
	bool music_on_off = true;

	void ChouseMusicVolum() {
		system("cls");
		sound_volume = (rand() % 100) + 1;
	}

	void out() {
		if (music_on_off == true)
		{
			cout << "Звук - включен" << endl;
		}
		else
		{
			cout << "Звук - выключен" << endl;
		}
		cout << "Громкость звука " << sound_volume << endl;
	}

	void ChouseMusicOffOn() {
		system("cls");
		cout << "Введите 1 чтобы выключить звук" << endl;
		cout << "Введите 2 чтобы включить звук" << endl;
		int t;
		cin >> t;
		switch (t)
		{
		case 1:
			music_on_off = false;
			break;
		case 2:
			music_on_off = true;
			break;
		default:
			ChouseMusicOffOn();
			break;
		}
	}
};