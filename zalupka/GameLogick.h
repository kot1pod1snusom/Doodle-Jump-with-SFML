#pragma once

#include "Blocks.h"

class GameLogick {
public:
	void Doodle_Auto_Move(Dodle& doodle, vector<Block*>& vec) {
		//���������, ���� ������ ��������� ���� 
		if (doodle.move_up_down == false) //���� ������ ������ � ���, ������� ������ ������ ��� ���������� �� �����, ���� �� �� ��������� ��� �� �������� ���������
		{
			doodle.Move_down();
		}
		else if (doodle.move_up_down == true)
		{
			doodle.Move_up(vec);
		}
	}

	bool kollizion(Block* bl, Dodle doodle) {
		if (((doodle.x > bl->x && doodle.x < bl->x_end) || (doodle.xend > bl->x && doodle.x < bl->x_end)) && (doodle.yend == bl->y) && bl->kollizion_up == false)
		{
			bl->kollizion_up = true;
			return true;
		}
		else
		{
			bl->kollizion_up = false;
			return false;
		}

	}
};