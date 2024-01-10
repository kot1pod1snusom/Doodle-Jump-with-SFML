

#include "Classes.h" 
Player player;
Dodle doodle;

void menu();
void StartGame();


void SetBlockStartPosition(vector<Block>& vec) {
		for (size_t i = 0; i < 10; i++)
		{
			if (i * 200 >= 1000)
			{
				vec.push_back(Block(i * 100, rand() & (i * 100)));
			}
			else
			{
				vec.push_back(Block(i * 100, i * 200));
			}
		}
		vec.push_back(Block(190, 900));
}

void DataOut(vector<Block> vec, Dodle dl, bool ShowDoodleCoord, bool ShowDistanseCount, bool ShowBlockCoord) {
	system("cls");
	if (ShowDoodleCoord == true)
	{
		cout << "Doodle coord: x - " << doodle.x << " y - " << doodle.y << endl;
		cout << "Doodle end coord: xend - " << doodle.xend << " yend - " << doodle.yend << endl;
	}

	if (ShowDistanseCount == true)
	{
		cout << "Now distanse - " << doodle.Distance_count << endl;
		cout << "Max distanse - " << doodle.Distance << endl;
	}

	if (ShowBlockCoord == true)
	{
		cout << "Block coord:" << endl;
		for (size_t i = 0; i < vec.size(); i++)
		{
			cout << "\t" << i << " x - " << vec[i].x << " y - " << vec[i].y << " xend - " << vec[i].x_end << " y_end - " << vec[i].y_end << endl;
		}
	}
}

void GameOver() {
	system("cls");
	cout << "   ████████      ██     ████     ████ ████████     ███████   ██      ██ ████████ ███████ " << endl;
	cout << "  ██░░░░░░██    ████   ░██░██   ██░██░██░░░░░     ██░░░░░██ ░██     ░██░██░░░░░ ░██░░░░██ " << endl;
	cout << " ██      ░░    ██░░██  ░██░░██ ██ ░██░██         ██     ░░██░██     ░██░██      ░██   ░██ " << endl;
	cout << "░██           ██  ░░██ ░██ ░░███  ░██░███████   ░██      ░██░░██    ██ ░███████ ░███████ " << endl;
	cout << "░██    █████ ██████████░██  ░░█   ░██░██░░░░    ░██      ░██ ░░██  ██  ░██░░░░  ░██░░░██ " << endl;
	cout << "░░██  ░░░░██░██░░░░░░██░██   ░    ░██░██        ░░██     ██   ░░████   ░██      ░██  ░░██ " << endl;
	cout << " ░░████████ ░██     ░██░██        ░██░████████   ░░███████     ░░██    ░████████░██   ░░██ " << endl;
	cout << "   ░░░░░░░░  ░░      ░░ ░░         ░░ ░░░░░░░░     ░░░░░░░       ░░     ░░░░░░░░ ░░     ░░ " << endl;
	cout << "Вы проиграли!" << endl;
	cout << "Вы набрали " << doodle.Score << endl;

	if (doodle.Score > player.MaxScore)
	{
		cout << "Поздравляем, это ноый рекорд. Вы обогнали ваш старый рекорд на " << doodle.Score - player.MaxScore << " очков" << endl;
		player.MaxScore = doodle.Score;
	}

	player.TotalGames++;
	player.AverageScore = player.ScoreSum / player.TotalGames;


	cout << "Нажмите 1 чтобы выйти в главное меню" << endl;
	cout << "Введите 2 чтобы сыграть ещё раз" << endl;
	cout << "Введите 3 чтобы выйти из игры" << endl;

	char pc;
	cin >> pc;
	switch (pc)
	{
	case '1':
		menu();
		break;
	case '2':
		StartGame();
		break;
	case '3':
		exit;
		break;
	default:
		ShellExecute(0, 0, L"https://www.youtube.com/watch?v=8ay_BkRuv-o&list=PL1VyMbVaxeI7cnGAD_Ci8zQn4-qqZQK4u&index=12", 0, 0, SW_SHOW);
		break;
	}

}

void game() {
	//Вектор блоков
	vector<Block> vec; 
	sf::RenderWindow window(sf::VideoMode(1000, 1080), "Doodle jump");
	sf::RectangleShape fon((sf::Vector2f(1000,1080)));


	sf::Texture t;
	string s = "Pics\\FON.jpg";
	t.loadFromFile(s);
	fon.setTexture(&t);
	fon.setPosition(1, 1);

	SetBlockStartPosition(vec);

	sf::Font font;
	font.loadFromFile("arial.ttf");


	sf::Text score;
	score.setCharacterSize(24);
	score.setFont(font);
	score.setStyle(sf::Text::Bold);
	score.setFillColor(sf::Color::Red);

	
	bool ShowDoodleCoord = false;
	bool ShowDistanseCount = false;
	bool ShowBlockCoord = false;
		
	while (window.isOpen())
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
		{
			if (ShowDoodleCoord == false)
			{
				ShowDoodleCoord = true;
			}
			else if (ShowDoodleCoord == true)
			{
				ShowDoodleCoord = false;
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
		{
			if (ShowDistanseCount == false)
			{
				ShowDistanseCount = true;
			}
			else if (ShowDistanseCount == true)
			{
				ShowDistanseCount = false;
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
		{
			if (ShowBlockCoord == false)
			{
				ShowBlockCoord = true;
			}
			else if (ShowBlockCoord == true)
			{
				ShowBlockCoord = false;
			}
		}



		//Движение дудла игроков
		doodle.Player_Move();
		
		//Движение дудла вверх ввниз
		doodle.Auto_Move(vec);
		
		

		//Коллизия
		for (size_t i = 0; i < vec.size(); i++)
		{
			
			vec[i].Kollizon(doodle);
		}
		
		//Перемещение блоков если они ушли за границу обзора
		for (size_t i = 0; i < vec.size(); i++)
		{
			vec[i].Brick_relocate();
		}


		//Вывод
		window.clear();
		window.draw(fon);
		for (size_t i = 0; i < vec.size(); i++)
		{
			window.draw(vec[i].Blok);
		}
		
		doodle.Doodle.setPosition(doodle.x, doodle.y);
		window.draw(doodle.Doodle);

		score.setString(to_string(doodle.Score));
		window.draw(score);

		
		window.display();


		DataOut(vec, doodle, ShowDoodleCoord, ShowDistanseCount, ShowBlockCoord);

		//Проверка слил игрок или нет
		if (doodle.yend >= 1000)
		{
			window.close();
		}
	}

	GameOver();
}

void StartGame() {
	system("cls");
	for (int i = 5; i > 0; i--)
	{
		cout << "Приготовтесь! Начало игры через " << i << endl;
		std::this_thread::sleep_for(1s);
	}
	game();
}


void Statistic() {
	cout << "███████╗████████╗ █████╗ ████████╗██╗███████╗████████╗██╗ ██████╗" << endl;
	cout << "██╔════╝╚══██╔══╝██╔══██╗╚══██╔══╝██║██╔════╝╚══██╔══╝██║██╔════╝ " << endl;
	cout << "███████╗   ██║   ███████║   ██║   ██║███████╗   ██║   ██║██║	  " << endl;
	cout << "╚════██║   ██║   ██╔══██║   ██║   ██║╚════██║   ██║   ██║██║      " << endl;
	cout << "███████║   ██║   ██║  ██║   ██║   ██║███████║   ██║   ██║╚██████╗ " << endl;
	cout << "╚══════╝   ╚═╝   ╚═╝  ╚═╝   ╚═╝   ╚═╝╚══════╝   ╚═╝   ╚═╝ ╚═════╝ " << endl;

	cout << "Всего игр - " << player.TotalGames << endl;
	cout << "Среднее количество очков за игру - " << player.AverageScore << endl;
	cout << "Максимальное количество очков за игру - " << player.MaxScore << endl;

	cout << "Введите любое число чтобы вернуться в меню" << endl;
	char t;
	cin >> t;
	menu();

}


void menu() {

	system("cls");
	cout << "░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░" << endl;
	cout << "░      ░░░░░░░░░     ░░░░░░░░░░     ░░░░░░      ░░░░░   ░░░░░░░░         ░░░░░░░░░░░░   ░░   ░░░░░   ░   ░░░░░░░   ░        ░░ " << endl;
	cout << "▒   ▒▒▒   ▒▒▒▒   ▒▒▒▒   ▒▒▒▒▒   ▒▒▒▒   ▒▒▒   ▒▒▒   ▒▒   ▒▒▒▒▒▒▒▒   ▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒   ▒▒   ▒▒▒▒▒   ▒  ▒   ▒▒▒    ▒   ▒▒▒▒	   " << endl;
	cout << "▒   ▒▒▒▒   ▒   ▒▒▒▒▒▒▒▒   ▒   ▒▒▒▒▒▒▒▒   ▒   ▒▒▒▒   ▒   ▒▒▒▒▒▒▒▒   ▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒   ▒▒   ▒▒▒▒▒   ▒   ▒   ▒ ▒   ▒   ▒▒▒▒    " << endl;
	cout << "▓   ▓▓▓▓   ▓   ▓▓▓▓▓▓▓▓   ▓   ▓▓▓▓▓▓▓▓   ▓   ▓▓▓▓   ▓   ▓▓▓▓▓▓▓▓       ▓▓▓▓▓▓▓▓▓▓▓▓▓▓   ▓▓   ▓▓▓▓▓   ▓   ▓▓   ▓▓   ▓        ▓▓ " << endl;
	cout << "▓   ▓▓▓▓   ▓   ▓▓▓▓▓▓▓▓   ▓   ▓▓▓▓▓▓▓▓   ▓   ▓▓▓▓   ▓   ▓▓▓▓▓▓▓▓   ▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓   ▓▓   ▓▓▓▓▓   ▓   ▓▓▓  ▓▓   ▓   ▓▓▓▓▓▓▓ " << endl;
	cout << "▓   ▓▓▓   ▓▓▓▓   ▓▓▓▓▓   ▓▓▓▓   ▓▓▓▓▓   ▓▓   ▓▓▓   ▓▓   ▓▓▓▓▓▓▓▓   ▓▓▓▓▓▓▓▓▓▓▓▓▓  ▓▓▓   ▓▓   ▓▓▓▓▓   ▓   ▓▓▓▓▓▓▓   ▓   ▓▓▓▓▓▓▓ " << endl;
	cout << "█      █████████     ██████████     ██████      █████          █         ████████     ██████      ████   ███████   █   ███████ " << endl;
	cout << "██████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████ " << endl;
	cout << "Введите 1 чтобы начать игру" << endl;
	cout << "Введите 2 чтобы посмотреть вашу статистику " << endl;
	cout << "Введите 3 чтобы выйти из игры" << endl;
	char pc;
	cin >> pc;
	switch (pc)
	{
	case '1':
		StartGame();
		break;
	case '2':
		Statistic();
		break;
	case '3':
		exit;
		break;
	default:
		menu();
		break;
	}

}



void main() {
	setlocale(0, "RUSSIAN");
	srand(time(NULL));
	menu();
}