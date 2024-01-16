#pragma once
#include "Includes.h"


class Block;

class Dodle {
public:
	//���������� �������� ������ ����
	int x = 200;
	int y = 700;

	//���������� ������� ������� ����
	int xend = x + 100;
	int yend = y + 100;

	//����������, ������� ������ ���������� Doodle � x;
	int Distance = 350;
	int Distance_count = 0;

	int Score = 0;

	sf::Texture DoodleRightTexture;
	sf::Texture DoodleLeftTexture;
	//False - �������� ����, true - ��������� �����
	bool move_up_down = false;

	sf::RectangleShape Doodle;


	Dodle() {
		Doodle = sf::RectangleShape(sf::Vector2f(100, 100));
		//����� �����
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

	//�������� 
	void Player_Move() {
		if (sf::Keyboard::isKeyPressed(sf::	Keyboard::A))
		{
			x--;
			//������ ��������� ����� �� ������������� � ����� �������
			Doodle.setTexture(&DoodleLeftTexture);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			x++;
			
			//������ ��������� ����� �� ������������� � ������ �������
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
	//���������� �������� ������ ����
	int x;
	int y;
	
	//���������� ������� ������� ���� 
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

	//������� ��������� �����
	void Move_down() {
		y++;
		y_end++;
		Blok.setPosition(x, y);
	}

	//����� ���� ���� �� ����� ���������, ������� ��� ������ 
	void Brick_relocate() {
		if (y >= 1080) 
		{ 
			y = 0 - 10; // ������� ���, ����� ��������� �� ���������� �� ������
			x = (rand() % (1000 - 150)) + 1; //������ ����� - ���������� �������� ���� �� �, ������� xend, ����� ��������� �� �������� �� ���������
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
	//���������, ���� ������ ��������� ���� 
	if (move_up_down == false) //���� ������ ������ � ���, ������� ������ ������ ��� ���������� �� �����, ���� �� �� ��������� ��� �� �������� ���������
	{
		y++;
		yend++;
		Doodle.setPosition(x, y);
	}
	else if (move_up_down == true)
	{
		//����������, �������� �� ���� ������ ����� ���������
		if (Distance_count != Distance)
		{
			//��������� ��� ��������� ����, ���� �������� ��� �������� �����, ��� ���������
			if (y >= 500) //������� �����
			{
				y--;
				yend--;
				Doodle.setPosition(x, y);

				//��������� +! � ���������� ���������
				Distance_count++;
			}
			else //������� ���������
			{
				for (size_t i = 0; i < vec.size(); i++)
				{
					vec[i].Move_down();
				}

				//�������� +1 � ���������� ���������
				Distance_count++;

				//�.�. ��� ����� ������� � ����� �����, �� ��� ���� +����
				Score += 5;
			}
		}
		else //���� ������ ��� ���������
		{
			//������ ���� �������� �� �������� ����
			move_up_down = false;

			//�������� ������� ��������� ���������
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
		cout << "������� 1 ����� ��������� ����" << endl;
		cout << "������� 2 ����� �������� ����" << endl;
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