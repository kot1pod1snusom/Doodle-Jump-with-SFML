#pragma once
#include "HelpClasses.h"

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

		string left = "Pics\\game\\dudl_left.png";
		DoodleLeftTexture.loadFromFile(left);

		string right = "Pics\\game\\dudl_right.png";
		DoodleRightTexture.loadFromFile(right);
		Doodle.setTexture(&DoodleRightTexture);
	}
	
	void Move_down() {
		y++;
		yend++;
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

	void draw(sf::RenderWindow* w) {
		Doodle.setPosition(x, y);
		w->draw(Doodle);
	}

	void Move_up(vector<Block*>& vec);


	//�������� 
	void Player_Move() {
		if (sf::Keyboard::isKeyPressed(sf::	Keyboard::A))
		{
			x--;
			xend--;
			//������ ��������� ����� �� ������������� � ����� �������
			Doodle.setTexture(&DoodleLeftTexture);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			x++;
			xend++; 
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
	}
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


	Block(int x, int y, sf::Color color) : x(x), y(y), x_end(x + 100), y_end(y + 15) {
		Blok = sf::RectangleShape((sf::Vector2f(100.f, 15.f)));

		sf::Texture t;
		string str1 = (filesystem::current_path() / "Pics\\platform.png").string();
		string str = "Pics\\game\\platform.png";
		t.loadFromFile(str);
		Blok.setFillColor(color);
		Blok.setTexture(&t);

		Blok.setPosition(x, y);
	}


	virtual int kol_do(Dodle& dl) = 0;

	//������� ��������� �����
	virtual void Move_down() {
		this->y+=1;
		this->y_end+=1;
		Blok.setPosition(x, y);
	}

	//����� ���� ���� �� ����� ���������, ������� ��� ������ 
	virtual void Brick_relocate() {
		if (y >= 1080)
		{
			y = 0 - 10; // ������� ���, ����� ��������� �� ���������� �� ������
			x = (rand() % (1000 - 100)) + 1; //������ ����� - ���������� �������� ���� �� �, ������� xend, ����� ��������� �� �������� �� ���������

			x_end = x + 100;
			y_end = y + 15;

			Blok.setPosition(x, y);
		}
		else
		{
			return;
		}
	}
};

void Dodle::Move_up(vector<Block*>& vec) {
	//����������, �������� �� ���� ������ ����� ���������
	if (Distance_count != Distance)
	{
		//��������� ��� ��������� ����, ���� �������� ��� �������� �����, ��� ���������
		if (y >= 500) //������� �����
		{
			y--;
			yend--;
			Distance_count++;
		}
		else //������� ���������
		{
			for (size_t i = 0; i < vec.size(); i++)
			{
				vec[i]->Move_down();
			}

			//�������� +1 � ���������� ���������
			Distance_count++;

			//�.�. ��� ����� ������� � ����� �����, �� ��� ���� +����
			Score += 1;
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
			cout << "���� - �������" << endl;
		}
		else
		{
			cout << "���� - ��������" << endl;
		}
		cout << "��������� ����� " << sound_volume << endl;
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