#include<SFML/Graphics.hpp>
#include<sstream>
#include <SFML/Audio.hpp>
#include<iostream>
#include<fstream>
#include<Windows.h>
#include<thread>



using namespace sf;
using namespace std;
//void level2(int);
void mainGame();
void scor();
int settings();
void death(int);
bool checkbrightness;
int main()
{
	int pressCounter = 0;

	RenderWindow window(VideoMode(2100, 1280), "winter is here", Style::Fullscreen);
	Font fo;
	Texture background;
	background.loadFromFile("graphics/score.jpg");
	fo.loadFromFile("font/font.ttf");
	Sprite backg(background);

	Text play, setting, score, checkedplay, checkedsettings, checkedscore, exit, checkedexit;


	play.setFont(fo);
	play.setString("play");
	play.setCharacterSize(120);
	play.setFillColor(Color::Black);
	play.setPosition(370, 250);

	checkedplay.setFont(fo);
	checkedplay.setString("play");
	checkedplay.setCharacterSize(120);
	checkedplay.setFillColor(Color::Red);
	checkedplay.setPosition(370, 250);

	setting.setFont(fo);
	setting.setString("setings");
	setting.setCharacterSize(120);
	setting.setFillColor(Color::Black);
	setting.setPosition(370, 450);

	checkedsettings.setFont(fo);
	checkedsettings.setString("setings");
	checkedsettings.setCharacterSize(120);
	checkedsettings.setFillColor(Color::Red);
	checkedsettings.setPosition(370, 450);

	score.setFont(fo);
	score.setString("score board");
	score.setCharacterSize(120);
	score.setFillColor(Color::Black);
	score.setPosition(370, 650);

	checkedscore.setFont(fo);
	checkedscore.setString("score board");
	checkedscore.setCharacterSize(120);
	checkedscore.setFillColor(Color::Red);
	checkedscore.setPosition(370, 650);

	exit.setFont(fo);
	exit.setString("exit");
	exit.setCharacterSize(120);
	exit.setFillColor(Color::Black);
	exit.setPosition(370, 850);

	checkedexit.setFont(fo);
	checkedexit.setString("exit");
	checkedexit.setCharacterSize(120);
	checkedexit.setFillColor(Color::Red);
	checkedexit.setPosition(370, 850);
	//prepare the sound
	SoundBuffer chopBuffer;
	chopBuffer.loadFromFile("sound/4.wav");
	Sound chop;
	chop.setBuffer(chopBuffer);

	SoundBuffer  ootBuffer;
	ootBuffer.loadFromFile("sound/5.wav");
	Sound oot;
	oot.setBuffer(ootBuffer);


	while (window.isOpen())
	{


		if (pressCounter > 3 || pressCounter < 0)
			pressCounter = 0;


		Event chose;
		while (window.pollEvent(chose))
		{

			switch (chose.type) {
			case Event::KeyPressed:
				switch (chose.key.code)
				{
				case Keyboard::Down:
					pressCounter++; break;
				case Keyboard::Up:
					pressCounter--; break;


				default:
					break;
				}
			}
		}
		window.clear();

		switch (pressCounter)
		{
		case 0:
			window.draw(backg);
			window.draw(checkedplay);
			window.draw(setting);
			window.draw(score);
			window.draw(exit);
			break;
		case 1:
			window.draw(backg);
			window.draw(play);
			window.draw(checkedsettings);
			window.draw(score);
			window.draw(exit);
			break;
		case 2:
			window.draw(backg);
			window.draw(play);
			window.draw(setting);
			window.draw(checkedscore);
			window.draw(exit);
			break;
		case 3:
			window.draw(backg);
			window.draw(play);
			window.draw(setting);
			window.draw(score);
			window.draw(checkedexit);
			break;
		}
		if (Keyboard::isKeyPressed(Keyboard::Space))
		{
			switch (pressCounter)
			{
			case 0:
				window.close();
				mainGame();
				break;
			case 1:   window.close();
				settings(); break;
			case 2:
				window.close();
				scor();
				break;
			case 3:
				window.close();
			}
		}
		chop.play();


		window.display();



	}


}




void scor()
{

	RenderWindow window(VideoMode(1920, 1080), "winter is here", Style::Fullscreen);
	Font fo;
	Texture background;
	background.loadFromFile("graphics/wall.jpg");
	Sprite sbackground;
	sbackground.setTexture(background);
	fo.loadFromFile("font/font.ttf");
	Text score, player, high;
	int cameray = 0, y = 15;
	View view(FloatRect(0, 0, 1920, 1080));



	int i, max = 0;
	string numscore, maxscore;
	string content;
	ifstream scoregame("numberscore.txt");

	while (getline(scoregame, numscore))
	{

		content += numscore + "\n";

	}

	scoregame.close();
	istringstream ssi(content);
	while (ssi >> i) {
		if (i >= max)
			max = i;
		ifstream highscore("name score.txt");
		highscore >> maxscore;
		highscore.close();
	}
	high.setFont(fo);
	//high.setString(max);
	high.setCharacterSize(100);
	high.setFillColor(Color::White);
	high.setPosition(1000, 120);
	stringstream d;
	d << "high score : " << max << endl << "name : " << maxscore;
	high.setString(d.str());


	score.setFont(fo);
	//score.setString(content);
	score.setCharacterSize(30);
	score.setFillColor(Color::White);
	score.setPosition(630, 120);
	stringstream s;
	s << "score : " << endl << content;
	score.setString(s.str());



	string namescore;

	string content2;
	ifstream scoreplayer("nameplayer.txt");

	while (getline(scoreplayer, namescore))
	{
		content2 += namescore + "\n";
	}
	scoreplayer.close();


	player.setFont(fo);
	//player.setString(content2);
	player.setCharacterSize(30);
	player.setFillColor(Color::White);
	player.setPosition(230, 120);
	stringstream p;
	p << "name : " << endl << content2;
	player.setString(p.str());



	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{

			if (event.type == Event::Closed)
				window.close();



			if (event.type == Event::KeyPressed) {

				if (Keyboard::isKeyPressed(Keyboard::Key::Up))
				{
					if (cameray > 0) {
						view.move(Vector2f(0, -y));
						cameray -= y;
					}

				}
				if (Keyboard::isKeyPressed(Keyboard::Key::Down))
				{
					if (cameray <= 1300) {
						view.move(Vector2f(0, +y));
						cameray += y;
					}

				}
			}
		}

		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
			main();
		}


		window.setView(view);

		window.clear();
		window.draw(sbackground);
		window.draw(score);
		window.draw(player);
		window.draw(high);

		window.display();

	}
}



int settings() {
	RenderWindow win(VideoMode(500, 600), " ", Style::None);
	RectangleShape shape1(Vector2f(70, 20));
	RectangleShape turn(Vector2f(35, 25));
	turn.setFillColor(Color::Black);
	turn.setPosition(Vector2f(350, 220));
	shape1.setPosition(Vector2f(350, 222.5));

	double r = 100, g = 100, b = 100;
	Texture tex;
	tex.loadFromFile("graphics/score.jpg");
	Sprite background(tex);
	Font fo;
	fo.loadFromFile("font/font.ttf");

	Text option;
	Text sound;
	Text brightness;
	Text light;
	Text dark;
	brightness.setFont(fo);
	brightness.setFillColor(Color::Black);
	brightness.setString("brightness");
	brightness.setCharacterSize(40);
	brightness.setPosition(Vector2f(50, 300));
	sound.setFont(fo);
	sound.setString("sound");
	sound.setPosition(Vector2f(50, 200));
	sound.setCharacterSize(40);
	sound.setFillColor(Color::Black);
	option.setFont(fo);
	option.setString("option");
	option.setPosition(Vector2f(180, 50));
	option.setCharacterSize(50);
	option.setFillColor(Color::Black);
	light.setFont(fo);
	light.setString("light");
	light.setPosition(Vector2f(350, 300));
	light.setCharacterSize(25);
	light.setFillColor(Color::Black);
	dark.setFont(fo);
	dark.setString("Dark");
	dark.setPosition(Vector2f(350, 335));
	dark.setCharacterSize(25);
	dark.setFillColor(Color::Black);
	while (win.isOpen())
	{

		Event even;
		while (win.pollEvent(even)) {
			if (Keyboard::isKeyPressed(Keyboard::Right))
			{
				turn.setPosition(Vector2f(400, 220));
				turn.setFillColor(Color::Red);
			}
			if (Keyboard::isKeyPressed(Keyboard::Left))
			{
				turn.setPosition(Vector2f(350, 220));
				turn.setFillColor(Color::Green);

			}
		}
		background.setColor(Color(r, g, b));
		if (r<250 && g<250 && b<250)
		{
			if (Keyboard::isKeyPressed(Keyboard::Up))
			{
				checkbrightness = 1;
				r = 250;
				g = 250;
				b = 250;
				light.setFillColor(Color::Red);
				dark.setFillColor(Color::Black);
			}
		}
		if (r>0 && g>0 && b>0)
		{

			if (Keyboard::isKeyPressed(Keyboard::Down))
			{
				checkbrightness= false;
				r=100;
				g = 100;
				b =100;
				light.setFillColor(Color::Black);
				dark.setFillColor(Color::Red);
			}
		}
		if (Keyboard::isKeyPressed(Keyboard::Escape)) {
			return main();
		}
		win.clear();
		win.draw(background);
		win.draw(option);
		win.draw(sound);
		win.draw(brightness);
		win.draw(light);
		win.draw(dark);
		win.draw(shape1);
		win.draw(turn);
		//win.draw(road);
		win.display();
	}
}


void mainGame()
{
	double r = 250, g = 250, b = 250;
	if (checkbrightness) {

	 double r = 250, g = 250, b = 250;

	}
	else
	{
		double r = 100, g = 100, b = 100;

	}

	int c = 1;
	bool deathflag = 0;
	//int final_y,final_y1, numberofstone;
	int gameMap[27][48];
	int a, s;
	//puting the background in the array
	for (int i = 0; i < 26; ++i) {
		for (int j = 0; j < 47; ++j)
		{
			gameMap[i][j] = 1;
		}
	}

	srand(time(0));

	for (int i = 0; i <= 7; i++) {

		for (int j = 0; j <= 7; j++) {

			int x = 4 + rand() % 24;
			int y = 4 + rand() % 44;
			gameMap[x][y] = 2;

		}
	}




	for (int i = 0; i <= 5; i++) {

		for (int j = 0; j <= 5; j++) {

			int x = 4 + rand() % 24;
			int y = 4 + rand() % 44;
			gameMap[x][y] = 3;

		}
	}
	for (int i = 0; i <= 26; i++)
	{
		gameMap[i][0] = 4;
		gameMap[i][47] = 4;
	}
	for (int i = 0; i <= 47; i++)
	{
		gameMap[0][i] = 4;
		gameMap[26][i] = 4;
	}
	for (int i = 1; i < 47; i++) {
		for (int j = 22; j <= 25; j++) {
			gameMap[j][i] = 0;
		}
	}
	
		for (int j = 1; j < 47; j++) {
			gameMap[22][j] = 7;
		}
		for (int j = 1; j < 47; j++) {
			gameMap[25][j] = 7;
	}
		gameMap[23][13] = 7;
		gameMap[24][14] = 7;
		gameMap[23][31] = 7;
		gameMap[24][32] = 7;
	int randx = 4 + rand() % 10;
	int randy = 4 + rand() % 10;
	gameMap[randy][randx] = 5;


	VideoMode vm(1920, 1080);

	RenderWindow Window(vm, "digjim", Style::Fullscreen);

	int score = 0;
	//scorebartext
	Text  Score, score2, timer;
	Font fo;
	fo.loadFromFile("font/font.ttf");
	Score.setFont(fo);
	Score.setString("Score :");
	Score.setCharacterSize(80);
	Score.setFillColor(Color::Red);
		timer.setFont(fo);
		timer.setString("Timer:");
	timer.setCharacterSize(80);
	timer.setFillColor(Color::Red);

	timer.setPosition(15 * 40, 22.75 * 40);
	Score.setPosition(1 * 40, 22.75 * 40);
	stringstream pi;
	pi << score;
	
	score2.setString(pi.str());
	score2.setPosition(6 * 40, 22.50 * 40);
	
	


	

	//background
	Texture textureBackground, textureiron, textureblock, texturediamond, texturescorebar;
	Sprite spritebackground, spriteiron, spriteblock, spritediamond, spritescorebar;
	//background
	textureBackground.loadFromFile("graphics/sand.jpg");
	spritebackground.setTexture(textureBackground);
 	spritebackground.setColor(Color(r, g, b));
	//frame
	textureiron.loadFromFile("graphics/iron.jpg");
	spriteiron.setTexture(textureiron);
	spriteiron.setColor(Color(r, g, b));
	//block
	textureblock.loadFromFile("graphics/rock.jpg");
	spriteblock.setTexture(textureblock);
	spriteblock.setColor(Color(r, g, b));
	//diamond
	texturediamond.loadFromFile("graphics/diamond.jpg");
	spritediamond.setTexture(texturediamond);
	spritediamond.setColor(Color(r, g, b));
	//scorebar
	texturescorebar.loadFromFile("graphics/scorebar.jpg");
	

	spritescorebar.setTexture(texturescorebar);
	
	

	Texture Tcharc;
	Tcharc.loadFromFile("graphics/charc.jpg");
	
	Sprite Scharc(Tcharc);
	Scharc.setColor(Color(r, g, b));

	Texture Tbomb;
	Tbomb.loadFromFile("graphics/smash.png");

	Sprite Sbomb(Tbomb);
	Sbomb.setColor(Color(r, g, b));

	while (Window.isOpen())
	{
		b = 2;
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{

			Window.close();
			main();
		}
		//clear everything
		Window.clear();


		for (int i = 0; i <= 26; ++i)
		{
			for (int j = 0; j <= 47; ++j)
			{
				switch (gameMap[i][j])
				{
				case 1:	spritebackground.setPosition(j * 40, i * 40);
					Window.draw(spritebackground);  break;
				case 2: spriteblock.setPosition(j * 40, i * 40);
					Window.draw(spriteblock);       break;
				case 3: spritediamond.setPosition(j * 40, i * 40);
					Window.draw(spritediamond);     break;
				case 4: spriteiron.setPosition(j * 40, i * 40);
					Window.draw(spriteiron); break;
				case 5:
					Scharc.setPosition(j * 40, i * 40);
				Window.draw(Scharc); break; 
				case 10:Sbomb.setPosition(j * 40, i * 40);
					Window.draw(Sbomb); break;
				case 7:
					spritescorebar.setPosition(j * 40, i * 40);
					Window.draw(spritescorebar); break;

				default:
					break;
				}
			}
		}


		if (deathflag == 0)
		{
			Event move;
			while (Window.pollEvent(move))
			{
				b = 2;
				int k, d;

				switch (move.type) {
				case Event::KeyPressed:
					switch (move.key.code)
					{
					case Keyboard::Right:
						if (gameMap[randy][randx + 1] == 2 || gameMap[randy][randx + 1] == 4)break;
						if (gameMap[randy][randx + 1] == 3) score++;
						gameMap[randy][randx] = 0;
						randx++; gameMap[randy][randx] = 5;

						k = randy - 1;
						while (k >= 0 && (gameMap[k][randx - 1] == 2 || gameMap[k][randx - 1] == 3))
						{
							d = k + 1;
							while (d < 26 && gameMap[d][randx - 1] == 0)
							{
								swap(gameMap[d - 1][randx - 1], gameMap[d][randx - 1]);
								d++;
							}

							k--;
						}


						break;

					case Keyboard::Left:
						if (gameMap[randy][randx - 1] == 2 || gameMap[randy][randx - 1] == 4)break;
						if (gameMap[randy][randx - 1] == 3) score++;
						gameMap[randy][randx] = 0;
						randx--; gameMap[randy][randx] = 5;


						k = randy - 1;
						while (k >= 0 && (gameMap[k][randx + 1] == 2 || gameMap[k][randx + 1] == 3))
						{
							d = k + 1;
							while (d < 26 && gameMap[d][randx + 1] == 0)
							{
								swap(gameMap[d - 1][randx + 1], gameMap[d][randx + 1]);
								d++;
							}

							k--;
						}


						break;
					case Keyboard::Up:
						if (gameMap[randy - 1][randx] == 2 || gameMap[randy - 1][randx] == 4)break;
						if (gameMap[randy - 1][randx] == 3) score++;
						gameMap[randy][randx] = 0;
						randy--; gameMap[randy][randx] = 5;
						break;
					case Keyboard::Down:
						if (gameMap[randy + 1][randx] == 2 || gameMap[randy + 1][randx] == 4)break;
						if (gameMap[randy + 1][randx] == 3) score++;
						gameMap[randy][randx] = 0;
						randy++; gameMap[randy][randx] = 5;

						k = randy - 2;
						while (k >= 0 && (gameMap[k][randx] == 2 || gameMap[k][randx] == 3))
						{
							d = k + 1;
							while (d < 26 && gameMap[d][randx] == 0)
							{
								swap(gameMap[d - 1][randx], gameMap[d][randx]);
								d++;
							}

							k--;
						}

						break;

					}
				case Event::KeyReleased:
					switch (move.key.code)
					{
					case Keyboard::Down:
						if (gameMap[randy][randx] == 5 && gameMap[randy - 1][randx] == 3 || gameMap[randy - 1][randx] == 2)
						{
							gameMap[randy][randx] = 10;
							gameMap[randy + 1][randx] = 10;
							gameMap[randy - 1][randx] = 10;
							gameMap[randy][randx + 1] = 10;
							gameMap[randy][randx - 1] = 10;
							gameMap[randy + 1][randx - 1] = 10;
							gameMap[randy - 1][randx + 1] = 10;
							gameMap[randy - 1][randx - 1] = 10;
							gameMap[randy + 1][randx + 1] = 10;
								death(score); deathflag = 1; 
							Window.close();
							
						}
					}

				}

			}
		}
		if (score == 25)gameMap[5][47] = 0;




		if (gameMap[5][47] == 5) {  Window.close(); }
		
	

	

		
		Window.draw(Score);
		Window.draw(score2);
		Window.draw(timer);

		Window.display();

		//	Sleep(100);

	}

}






void death(int score) {


	VideoMode vm(500, 400);
	RenderWindow window(vm, "digjim", Style::None);
	Texture background;
	background.loadFromFile("graphics/death.jpg");
	Sprite sbackground;
	sbackground.setTexture(background);
	Font fo;
	fo.loadFromFile("font/font.ttf");
	string display;

	Text text, text1, text2;
	text1.setFont(fo);
	text1.setCharacterSize(20);
	text1.setStyle(Text::Bold);
	text1.setFillColor(Color::White);
	text1.setPosition(40, 150);
	text1.setStyle(Text::Bold);
	text1.setString("ENTER YOUR NAME : ");

	text.setFont(fo);
	text.setCharacterSize(20);
	text.setFillColor(Color::Red);
	text.setPosition(280, 150);
	text.setStyle(Text::Underlined);


	text2.setFont(fo);
	text2.setCharacterSize(20);
	text2.setStyle(Text::Bold);
	text2.setFillColor(Color::White);
	text2.setPosition(40, 300);
	text2.setStyle(Text::Bold);
	stringstream p;
	p << "score : " << score;
	text2.setString(p.str());


	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::TextEntered)
			{

				if (Keyboard::isKeyPressed(Keyboard::Tab))
				{
					if (display.size()>0)
						window.close();
				}

				stringstream p;
				p << "score : " << score;
				text2.setString(p.str());

				if (event.text.unicode >= 32 && event.text.unicode <= 126)
					display += (char)event.text.unicode;

				else if (event.text.unicode == 8 && display.size()>0)
					display.erase(display.size() - 1);
				stringstream s;
				s << "ENTER YOUR NAME : ";
				text1.setString(s.str());
				text.setString(display);
			}
		}



		window.clear();
		window.draw(sbackground);
		window.draw(text2);
		window.draw(text);
		window.draw(text1);
		window.display();
	}

	ofstream name("nameplayer.txt", ios::app);
	name << display << endl;
	name.close();

	ofstream in("numberscore.txt", ios::app);
	in << score << endl;
	in.close();

	int i, max = 0;
	string numscore;
	string content;
	ifstream scoregame("numberscore.txt");

	while (getline(scoregame, numscore))
	{

		content += numscore + "\n";

	}

	scoregame.close();
	istringstream ssi(content);
	while (ssi >> i) {
		if (i >= max)
			max = i;

	}
	if (score >= max) {
		ofstream highscore("name score.txt");
		highscore << display;
		highscore.close();
	}
	main();





}

/*
void level2(int score1) {
	int c = 1;
	int deathsteps = 10;
	bool deathflag = 0;
	//int final_y,final_y1, numberofstone;
	int gameMap[27][48];
	int a, b;
	//puting the background in the array
	for (int i = 0; i < 26; ++i) {
		for (int j = 0; j < 47; ++j)
		{
			gameMap[i][j] = 1;
		}
	}



	for (int i = 0; i <= 7; i++) {

		for (int j = 0; j <= 7; j++) {

			int x = 4 + rand() % 24;
			int y = 4 + rand() % 44;
			gameMap[x][y] = 2;

		}
	}




	for (int i = 0; i <= 5; i++) {

		for (int j = 0; j <= 5; j++) {

			int x = 4 + rand() % 24;
			int y = 4 + rand() % 44;
			gameMap[x][y] = 3;

		}
	}

	for (int i = 0; i <= 26; i++)
	{
		gameMap[i][0] = 4;
		gameMap[i][47] = 4;
	}
	for (int i = 0; i <= 47; i++)
	{
		gameMap[0][i] = 4;
		gameMap[26][i] = 4;
	}


	VideoMode vm(1920, 1080);
	RenderWindow Window(vm, "digjim", Style::Fullscreen);
	//background
	Texture textureBackground, textureiron, textureblock, texturediamond;
	Sprite spritebackground, spriteiron, spriteblock, spritediamond;
	//background
	textureBackground.loadFromFile("graphics/sand.jpg");
	spritebackground.setTexture(textureBackground);
	//frame
	textureiron.loadFromFile("graphics/iron.jpg");
	spriteiron.setTexture(textureiron);
	//block
	textureblock.loadFromFile("graphics/rock.jpg");
	spriteblock.setTexture(textureblock);
	//diamond
	texturediamond.loadFromFile("graphics/diamond.jpg");
	spritediamond.setTexture(texturediamond);

	Texture Tcharc;
	Tcharc.loadFromFile("graphics/char4.jpg");
	Sprite Scharc(Tcharc);
	int randx = 3, randy = 3;

	Texture Tbomb;
	Tbomb.loadFromFile("graphics/smash.jpg");
	Sprite Sbomb(Tbomb);

	int score = 0;
	while (Window.isOpen())
	{
		b = 2;
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{

			Window.close();
			main();
		}
		//clear everything
		Window.clear();


		for (int i = 0; i <= 26; ++i)
		{
			for (int j = 0; j <= 47; ++j)
			{
				switch (gameMap[i][j])
				{
				case 1:	spritebackground.setPosition(j * 40, i * 40);
					Window.draw(spritebackground);  break;
				case 2: spriteblock.setPosition(j * 40, i * 40);
					Window.draw(spriteblock);       break;
				case 3: spritediamond.setPosition(j * 40, i * 40);
					Window.draw(spritediamond);     break;
				case 4: spriteiron.setPosition(j * 40, i * 40);
					Window.draw(spriteiron); break;
				case 5:
					if (deathflag == 0)
					{
						Scharc.setPosition(j * 40, i * 40);
						Window.draw(Scharc); break;
					}
				case 10:Sbomb.setPosition(j * 40, i * 40);
					Window.draw(Sbomb); break;
				case 6:spriteblock.setPosition(j * 40, i * 40);
					Window.draw(spriteblock);
				default:
					break;
				}
			}
		}


		if (deathflag == 0)
		{
			Event move;
			while (Window.pollEvent(move))
			{
				b = 2;
				int k, d;

				switch (move.type) {
				case Event::KeyPressed:
					switch (move.key.code)
					{
					case Keyboard::Right:
						if (gameMap[randy][randx + 1] == 2 || gameMap[randy][randx + 1] == 4)break;
						if (gameMap[randy][randx + 1] == 3) score1++;
						if (gameMap[randy][randx + 1] == 6)deathsteps += 10;
						gameMap[randy][randx] = 0;
						randx++; gameMap[randy][randx] = 5;
						deathsteps--;
						k = randy - 1;
						while (k >= 0 && (gameMap[k][randx - 1] == 2 || gameMap[k][randx - 1] == 3))
						{
							d = k + 1;
							while (d < 26 && gameMap[d][randx - 1] == 0)
							{
								swap(gameMap[d - 1][randx - 1], gameMap[d][randx - 1]);
								d++;
							}

							k--;
						}
						
						break;

					case Keyboard::Left:
						if (gameMap[randy][randx - 1] == 2 || gameMap[randy][randx - 1] == 4)break;
						if (gameMap[randy][randx - 1] == 3) score1++;
						if (gameMap[randy][randx - 1] == 6)deathsteps += 10;
						gameMap[randy][randx] = 0;
						randx--; gameMap[randy][randx] = 5;
						deathsteps--;

						k = randy - 1;
						while (k >= 0 && (gameMap[k][randx + 1] == 2 || gameMap[k][randx + 1] == 3))
						{
							d = k + 1;
							while (d < 26 && gameMap[d][randx + 1] == 0)
							{
								swap(gameMap[d - 1][randx + 1], gameMap[d][randx + 1]);
								d++;
							}

							k--;
						}


						break;
					case Keyboard::Up:
						if (gameMap[randy - 1][randx] == 2 || gameMap[randy - 1][randx] == 4)break;
						if (gameMap[randy - 1][randx] == 3) score1++;
						if (gameMap[randy - 1][randx] == 6)deathsteps += 10;
						gameMap[randy][randx] = 0;
						randy--; gameMap[randy][randx] = 5;
						deathsteps--;
						break;
					case Keyboard::Down:
						if (gameMap[randy + 1][randx] == 2 || gameMap[randy + 1][randx] == 4)break;
						if (gameMap[randy + 1][randx] == 3) score1++;
						if (gameMap[randy + 1][randx] == 6)deathsteps += 10;
						gameMap[randy][randx] = 0;
						randy++; gameMap[randy][randx] = 5;
						deathsteps--;
						
						k = randy - 2;
						while (k >= 0 && (gameMap[k][randx] == 2 || gameMap[k][randx] == 3))
						{
							d = k + 1;
							while (d < 26 && gameMap[d][randx] == 0)
							{
								swap(gameMap[d - 1][randx], gameMap[d][randx]);
								d++;
							}

							k--;
						}

						if (gameMap[randy][randx] == 5 && gameMap[randy - 1][randx] == 3 || gameMap[randy - 1][randx] == 2) {
							gameMap[randy][randx] = 10;
							gameMap[randy + 1][randx] = 10;
							gameMap[randy - 1][randx] = 10;
							gameMap[randy][randx + 1] = 10;
							gameMap[randy][randx - 1] = 10;
							gameMap[randy + 1][randx - 1] = 10;
							gameMap[randy - 1][randx + 1] = 10;
							gameMap[randy - 1][randx - 1] = 10;
							gameMap[randy + 1][randx + 1] = 10;
							death(score); deathflag = 1; Window.close();
						}
						break;

					}

				}

			}
		}
		if (score1 == 50)gameMap[5][47] = 0;

		if (gameMap[5][47] == 5) { level2(score); Window.close(); }

		if (deathsteps == 0)
		{
			deathflag = 1;
			Window.close();
			death(score1);
		}

		gameMap[3][9] = 6;

		Window.display();

		//	Sleep(100);

	}
}*/
