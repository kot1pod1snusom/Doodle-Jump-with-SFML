

#include "HelpClasses.h" 
Player player;
Dodle doodle;
Settings settings;


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
	sf::RenderWindow window(sf::VideoMode(1000, 1080), "Doodle jump");
	
	sf::Font font;
	font.loadFromFile("arial.ttf");


	sf::Text score;
	score.setCharacterSize(24);
	score.setFont(font);
	score.setStyle(sf::Text::Bold);
	score.setFillColor(sf::Color::Red);
	string text = "Your score - ";
	string str = to_string(doodle.Score);
	text.append(str);
	score.setString(text);
	score.setPosition(300, 400);

	Buttion restart(300, 200, 150, 500);
	restart.setTexture("Pics\\game_over\\restart_b_t.png");

	Buttion fon(1000, 1080, 0, 0);
	fon.setTexture("Pics\\FON.jpg");

	Buttion xt(300, 200, 300, 750);
	xt.setTexture("Pics\\exit_b_t.png");

	Buttion tomenu(300, 200, 550, 500);
	tomenu.setTexture("Pics\\game_over\\tomenu_b_t.png");

	Buttion pomer(500, 200, 200, 100);
	pomer.setTexture("Pics\\game_over\\pomer.png");

	while (window.isOpen())
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			sf::Vector2i mousecoord = sf::Mouse::getPosition(window);
			if (restart.TapCheck(mousecoord) == true)
			{
				window.close();
				StartGame();
			}
			else if (xt.TapCheck(mousecoord) == true)
			{
				window.close();
				exit;
				abort;
				break;
			}
			else if (tomenu.TapCheck(mousecoord) == true)
			{
				window.close();
				menu();
			}
		}
		
		window.clear();
		fon.draw(&window);
		pomer.draw(&window);
		window.draw(score);
		tomenu.draw(&window);
		xt.draw(&window);
		restart.draw(&window);
		window.display();
	}
	exit;
}

void otladka(sf::RenderWindow* w, vector<Block> vec) {
	bool ShowDoodleCoord = false;
	bool ShowDistanseCount = false;
	bool ShowBlockCoord = false;

	while (w->isOpen())
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

		if (ShowDoodleCoord == true || ShowBlockCoord == true || ShowDistanseCount == true)
		{
			DataOut(vec, doodle, ShowDoodleCoord, ShowDistanseCount, ShowBlockCoord);
		}
	}
	system("cls");
	terminate;
	return void(0);
}


void game() {
	//Вектор блоков
	vector<Block> vec; 
	sf::RenderWindow window(sf::VideoMode(1000, 1080), "Doodle jump");
	sf::RectangleShape fon((sf::Vector2f(1000,1080)));

	Sound sound_jump;
	sound_jump.setSound("Sound\\jump.mp3");
	sound_jump.setVolume(settings.sound_volume);

	Music mc(true, settings.sound_volume);
	mc.setMusic("Sound\\play.mp3");
	mc.play(settings);

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
	

	thread th(otladka, &window,vec);
	th.detach();

	while (window.isOpen())
	{


		//Движение дудла игроков
		doodle.Player_Move();
		
		//Движение дудла вверх ввниз
		doodle.Auto_Move(vec);
		
		

		//Коллизия
		for (size_t i = 0; i < vec.size(); i++)
		{
			if (vec[i].Kollizon(doodle) == true)
			{
				
				doodle.move_up_down = true;
				

				sound_jump.play(settings);
			}
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



		//Проверка слил игрок или нет
		if (doodle.yend >= 1000)
		{
			window.close();
		}

		auto t = chrono::nanoseconds(800);
		std::this_thread::sleep_for(t);
	}
	TerminateThread(th.native_handle(), 0);
	GameOver();
	mc.stop();
}

void StartGame() {
	system("cls");
	doodle.NewGame();
	game();
}



void Statistic() {
	system("cls");
	cout << "Статистика:" << endl;
	cout << "Всего игр - " << player.TotalGames << endl;
	cout << "Среднее количество очков за игру - " << player.AverageScore << endl;
	cout << "Максимальное количество очков за игру - " << player.MaxScore << endl;
	cout << "Введите любое число чтобы вернуться в меню" << endl;
	char t;
	cin >> t;
	menu();
}


void Setting() {
	system("cls");
	cout << "Введите 1 чтобы поменять громкость звука" << endl;
	cout << "Введите 2 чтобы выключить или включить звук" << endl;
	cout << "Введите 3 чтобы вернуться в меню" << endl;
	settings.out();
	int t;
	cin >> t;
	switch (t)
	{
	case 1:
		settings.ChouseMusicVolum();
		Setting();
		break;
	case 2:
		settings.ChouseMusicOffOn();
		Setting();
		break;
	case 3:
		menu();
	default:
		Setting();
		break;
	}
}


void menu() {
	sf::RenderWindow window(sf::VideoMode(1000, 1080), "xuy");

	Buttion dj(880, 200, 80,100);
	dj.setTexture("Pics\\menu\\dj.png");

	Buttion fon(1000, 1080, 0,0);
	fon.setTexture("Pics\\FON.jpg");


	Buttion stat(300,200,550, 400);
	stat.setTexture("Pics\\menu\\statistic_b_t.png");

	Buttion start(300, 200, 100, 400);
	start.setTexture("Pics\\menu\\start_b_t.png");
	
	Buttion setting(300, 200, 100, 700);
	setting.setTexture("Pics\\menu\\settings_b_t.png");

	Buttion ext(300, 200, 550, 700);
	ext.setTexture("Pics\\exit_b_t.png");

	while (true)
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			sf::Vector2i mousecoord = sf::Mouse::getPosition(window);
			if (start.TapCheck(mousecoord) == true)
			{	
				window.close();
				StartGame();
			}
			else if (setting.TapCheck(mousecoord) == true)
			{
				window.close();
				/*cout << "Будет доступно в следующих версия" << endl;
				cout << "Введите любую строку, чтобы вернуться назад" << endl;
				string str;
				cin >> str;
				menu();*/
				Setting();
			}
			else if (stat.TapCheck(mousecoord) == true)
			{
				window.close();
				Statistic();
			}
			else if (ext.TapCheck(mousecoord) == true)
			{
				window.close();
				break;
			}
		}


		window.clear();
		fon.draw(&window);
		dj.draw(&window);
		ext.draw(&window);
		setting.draw(&window);
		start.draw(&window);
		stat.draw(&window);
		window.display();
	}

	exit;

}



int main() {
	setlocale(0, "RUSSIAN");
	srand(time(NULL));
	//menu();
	
	menu();
	cout << "Git test" << endl;

	return 0;
}