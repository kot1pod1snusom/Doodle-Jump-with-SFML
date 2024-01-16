#pragma once
#include "Includes.h"


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
		//Спавн Дудла
		Doodle.setPosition(x, y);

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

	void Auto_Move(vector<Block>& vec);
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
		Blok.setTexture(&t);
		

		Blok.setPosition(x, y);
	}


	bool Kollizon(Dodle& doodle) {

		bool kollizion_up_check = false;

		if (((doodle.x > x && doodle.x < x_end) || (doodle.xend > x && doodle.x < x_end)) && (doodle.yend == y) && kollizion_up == false)
		{
			return true;
			kollizion_up_check = false;
		}
		else if (((doodle.x > x && doodle.x < x_end) || (doodle.xend > x && doodle.x < x_end)) && (doodle.y <= y && doodle.yend >= y))
		{
			kollizion_up_check = true;
		}

		if (kollizion_up_check == true)
		{
			kollizion_up = true;
		}
		else
		{
			kollizion_up = false;
		}
		return false;
	}

	//Двигаем платформу вверх
	void Move_down() {
		y++;
		y_end++;
		Blok.setPosition(x, y);
	}

	//Когда блок ушел за грань видимости, спавним его вверху 
	void Brick_relocate() {
		if (y >= 1080) 
		{ 
			y = 0 - 10; // Спавним так, чтобы платформы не спавнились на глазах
			x = (rand() % (1000 - 150)) + 1; //Первое число - количество пикселей окна по х, вычитая xend, чтобы платформа не выходила за текстурки
			Blok.setPosition(x, y);

			x_end = x + 150;
			y_end = y + 10;
		}
		else
		{
			return;
		}
	}

};


void Dodle::Auto_Move(vector<Block>& vec) {
	//Проверяем, куда должен двигается дудл 
	if (move_up_down == false) //Дудл всегда падает с сам, поэтому просто меняет ему координаты до конца, пока он не проиграет или не коснется платформы
	{
		y++;
		yend++;
		Doodle.setPosition(x, y);
	}
	else if (move_up_down == true)
	{
		//Сравниваем, пролетел ли дудл нужную вверх дистанцуя
		if (Distance_count != Distance)
		{
			//Проверяем где находится дудл, чтоб двигаеть или самомого дудла, или платформы
			if (y >= 500) //Двигаем дудла
			{
				y--;
				yend--;
				Doodle.setPosition(x, y);

				//Добавляем +! в проеденную дистанцуя
				Distance_count++;
			}
			else //Двигаем платформы
			{
				for (size_t i = 0; i < vec.size(); i++)
				{
					vec[i].Move_down();
				}

				//Добвляем +1 в проеденную дистанцуя
				Distance_count++;

				//т.к. это самая высокая и новая точка, то тут даем +очки
				Score += 5;
			}
		}
		else //Дудл прошел всю дистанцию
		{
			//Меняем ключ движения на движение вниз
			move_up_down = false;

			//Обнуляем счетчик проёденной дистанции
			Distance_count = 0;
		}
	}
}

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
		sound_volume = (rand() % 100) + 1;
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