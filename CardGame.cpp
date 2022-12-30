#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace sf;

const int arr_cnt = 4;

struct Card{
	RectangleShape sprite;
	int id;
	int type;
	int is_clicked;
};

int main()
{
	int CARD_W = 200;
	int CARD_H = 200;

	RenderWindow window(VideoMode(1200, 800), "Card Game!");
	window.setFramerateLimit(60);

	Vector2i mouse_pos;
	int click_cnt = 0;     //마우스 누른 횟수

	Texture texture[8 + 1];
	texture[0].loadFromFile("./resources/ch0.png");    //뒤집기 전 Image
	texture[1].loadFromFile("./resources/ch1.png");    //바티스트
	texture[2].loadFromFile("./resources/ch2.png");    //브리기테
	texture[3].loadFromFile("./resources/ch3.png");    //키리코
	texture[4].loadFromFile("./resources/ch4.png");    //루시우
	texture[5].loadFromFile("./resources/ch5.png");    //메르시
	texture[6].loadFromFile("./resources/ch6.png");    //모이라
	texture[7].loadFromFile("./resources/ch7.png");    //젠야타
	texture[8].loadFromFile("./resources/ch8.png");    //아나

	//폰트
	Font font;
	font.loadFromFile("c:/Windows/Fonts/Arial.ttf");

	//텍스트
	Text text;
	text.setFont(font);
	text.setCharacterSize(30);
	text.setFillColor(Color::White);
	text.setPosition(0, 0);
	char info[40];

	struct Card cards[arr_cnt][arr_cnt];
	int n = 0;
	for (int i = 0; i < arr_cnt; i++) 
	{
		for (int j = 0; j < arr_cnt; j++)
		{
			cards[i][j].sprite.setSize(Vector2f(CARD_W, CARD_H));
			cards[i][j].sprite.setPosition(j * CARD_W, i * CARD_H);
			cards[i][j].sprite.setTexture(&texture[0]); // 뒤집기 전
			cards[i][j].type = 1 + n / 2;
			cards[i][j].id = n + 1;
			cards[i][j].is_clicked = 0;
			n++;
		}
	}

	while (window.isOpen())
	{
		mouse_pos = Mouse::getPosition(window);

		Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case Event::Closed :
				window.close();
				break;
			//한 번 누르면 한 번만 적용
			case Event::MouseButtonPressed:
				if (event.mouseButton.button == Mouse::Left)
				{
					click_cnt++;  // 필요없는 코드
					for (int i = 0; i < arr_cnt; i++)
					{
						for (int j = 0; j < arr_cnt; j++)
						{
							if (cards[i][j].sprite.getGlobalBounds().contains(mouse_pos.x, mouse_pos.y))
							{
								cards[i][j].is_clicked = 1;
							}
						}
					}
				}
			}
		}

		for (int i = 0; i < arr_cnt; i++)
		{
			for (int j = 0; j < arr_cnt; j++)
			{
				//클릭이 된 상태면
				if (cards[i][j].is_clicked)
				{
					// 그림이 있는 sprite로 변경
					cards[i][j].sprite.setTexture(&texture[cards[i][j].type]);
				}
			}
		}

		sprintf(info, "(%d, %d) / CLICKS : %d\n", mouse_pos.x, mouse_pos.y, click_cnt);
		text.setString(info);

		window.clear(Color::Black);
		for (int i = 0; i < arr_cnt; i++)
		{
			for (int j = 0; j < arr_cnt; j++)
			{
				window.draw(cards[i][j].sprite);
			}
		}

		window.draw(text);

		window.display();
	}

	return 0;
}
