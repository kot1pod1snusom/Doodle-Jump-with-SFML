#pragma once

#include "HelpClasses.h"

class GameLogick {
public:
	void Doodle_Auto_Move(Dodle& doodle, vector<Block>& vec) {
		//���������, ���� ������ ��������� ���� 
		if (doodle.move_up_down == false) //���� ������ ������ � ���, ������� ������ ������ ��� ���������� �� �����, ���� �� �� ��������� ��� �� �������� ���������
		{
			doodle.y++;
			doodle.yend++;
		}
		else if (doodle.move_up_down == true)
		{
			//����������, �������� �� ���� ������ ����� ���������
			if (doodle.Distance_count != doodle.Distance)
			{
				//��������� ��� ��������� ����, ���� �������� ��� �������� �����, ��� ���������
				if (doodle.y >= 500) //������� �����
				{
					doodle.y--;
					doodle.yend--;
					//��������� +! � ���������� ���������
					doodle.Distance_count++;
				}
				else //������� ���������
				{
					for (size_t i = 0; i < vec.size(); i++)
					{
						vec[i].Move_down();
					}

					//�������� +1 � ���������� ���������
					doodle.Distance_count++;

					//�.�. ��� ����� ������� � ����� �����, �� ��� ���� +����
					doodle.Score += 2;
				}
			}
			else //���� ������ ��� ���������
			{
				//������ ���� �������� �� �������� ����
				doodle.move_up_down = false;

				//�������� ������� ��������� ���������
				doodle.Distance_count = 0;
			}
		}
	}

	bool kollizion(Block bl, Dodle doodle) {
		bool kollizion_up_check = false;
		if (((doodle.x > bl.x && doodle.x < bl.x_end) || (doodle.xend > bl.x && doodle.x < bl.x_end)) && (doodle.yend == bl.y) && bl.kollizion_up == false)
		{
			return true;
			kollizion_up_check = false;
		}
		else if (((doodle.x > bl.x && doodle.x < bl.x_end) || (doodle.xend > bl.x && doodle.x < bl.x_end)) && (doodle.y <= bl.y && doodle.yend >= bl.y))
		{
			kollizion_up_check = true;
		}

		if (kollizion_up_check == true)
		{
			bl.kollizion_up = true;
		}
		else
		{
			bl.kollizion_up = false;
		}
		return false;
	}






};