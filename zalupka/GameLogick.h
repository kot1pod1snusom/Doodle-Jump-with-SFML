#pragma once

#include "HelpClasses.h"

class GameLogick {
public:
	void Doodle_Auto_Move(Dodle& doodle, vector<Block>& vec) {
		//Проверяем, куда должен двигается дудл 
		if (doodle.move_up_down == false) //Дудл всегда падает с сам, поэтому просто меняет ему координаты до конца, пока он не проиграет или не коснется платформы
		{
			doodle.y++;
			doodle.yend++;
		}
		else if (doodle.move_up_down == true)
		{
			//Сравниваем, пролетел ли дудл нужную вверх дистанцуя
			if (doodle.Distance_count != doodle.Distance)
			{
				//Проверяем где находится дудл, чтоб двигаеть или самомого дудла, или платформы
				if (doodle.y >= 500) //Двигаем дудла
				{
					doodle.y--;
					doodle.yend--;
					//Добавляем +! в проеденную дистанцуя
					doodle.Distance_count++;
				}
				else //Двигаем платформы
				{
					for (size_t i = 0; i < vec.size(); i++)
					{
						vec[i].Move_down();
					}

					//Добвляем +1 в проеденную дистанцуя
					doodle.Distance_count++;

					//т.к. это самая высокая и новая точка, то тут даем +очки
					doodle.Score += 2;
				}
			}
			else //Дудл прошел всю дистанцию
			{
				//Меняем ключ движения на движение вниз
				doodle.move_up_down = false;

				//Обнуляем счетчик проёденной дистанции
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