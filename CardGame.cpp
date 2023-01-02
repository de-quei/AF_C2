#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace sf;

const int arr_size = 4;
const int CARD_W = 200;
const int CARD_H = 200;

struct Card {
	RectangleShape sprite;
	int id_i;
	int id_j;
	int type;
	int is_clicked;		// 현재 뒤집혀진 카드인지
	int is_cleared;		// 정답을 맞춘 카드인지
};

void swap_card(struct Card* c1, struct Card* c2)
{
	struct Card temp = *c1;
	*c1 = *c2;
	*c2 = temp;
}

int main(void)
{
	RenderWindow window(VideoMode(1200, 800), "Match the OverWatch Healer Cards!");
	window.setFramerateLimit(60);

	Vector2i mouse_pos;
	int flipped_num = 0;		// 현재 뒤집혀진 카드의 갯수

	long start_time;
	long spent_time;
	long delay_time;			// 바로 다시 ?로 뒤집혀지지 않도록 딜레이를 줌

	srand(time(0));

	Texture texture[8 + 1];
	texture[0].loadFromFile("./resources/ch0.png");
	texture[1].loadFromFile("./resources/ch1.png");
	texture[2].loadFromFile("./resources/ch2.png");
	texture[3].loadFromFile("./resources/ch3.png");
	texture[4].loadFromFile("./resources/ch4.png");
	texture[5].loadFromFile("./resources/ch5.png");
	texture[6].loadFromFile("./resources/ch6.png");
	texture[7].loadFromFile("./resources/ch7.png");
	texture[8].loadFromFile("./resources/ch8.png");

	Font font;
	font.loadFromFile("c:/Windows/Fonts/arial.ttf");

	//텍스트
	Text text;
	text.setFont(font);
	text.setCharacterSize(30);
	text.setFillColor(Color::Red);
	text.setPosition(0, 0);
	char info[40];

	//사운드
	SoundBuffer C_buffer;
	C_buffer.loadFromFile("./resources/kill.wav");
	Sound C_sound;
	C_sound.setBuffer(C_buffer);

	struct Card compare_card;	// 첫 번째로 뒤집힌 카드
	struct Card cards[arr_size][arr_size];
	int n = 0;
	for (int i = 0; i < arr_size; i++)
	{
		for (int j = 0; j < arr_size; j++)
		{
			cards[i][j].sprite.setSize(Vector2f(CARD_W, CARD_H));
			cards[i][j].sprite.setTexture(&texture[0]);
			cards[i][j].type = 1 + n / 2;
			cards[i][j].is_clicked = 0;
			cards[i][j].is_cleared = 0;
			n++;
		}
	}

	// 카드 100번 섞기
	for (int i = 0; i < 100; i++)
	{
		swap_card(&(cards[rand() % arr_size][rand() % arr_size]), &(cards[rand() % arr_size][rand() % arr_size]));
	}

	// idx에 맞춰서 id값, 위치 조정
	for (int i = 0; i < arr_size; i++)
	{
		for (int j = 0; j < arr_size; j++)
		{
			cards[i][j].id_i = i;
			cards[i][j].id_j = j;
			cards[i][j].sprite.setPosition(j * CARD_W, i * CARD_H);
		}
	}


	start_time = clock();
	delay_time = start_time;

	while (window.isOpen())
	{
		mouse_pos = Mouse::getPosition(window);
		spent_time = clock() - start_time;

		Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case Event::Closed:
				window.close();
				break;
				// 한 번 누르면 한 번만 적용
				// TODO : 버튼 눌러도 적용 안되는 버그 해결하기
			case Event::MouseButtonPressed:
				if (event.mouseButton.button == Mouse::Left)
				{
					for (int i = 0; i < arr_size; i++)
					{
						for (int j = 0; j < arr_size; j++)
						{
							if (flipped_num < 2)
							{
								// 마우스 위치가 cards[i][j]의 위치에 해당한다면?
								if (cards[i][j].sprite.getGlobalBounds().contains(mouse_pos.x, mouse_pos.y))
								{
									// 뒤집혀지지 않은 카드만 뒤집겠다.
									if (cards[i][j].is_clicked == 0)
									{
										cards[i][j].is_clicked = 1;
										flipped_num++;

										// 뒤집혀진 카드가 한 개라면
										if (flipped_num == 1)
										{
											compare_card = cards[i][j];
										}
										// 두 개를 뒤집었다면
										else if (flipped_num == 2)
										{
											// 두 카드가 같은 종류면
											if (compare_card.type == cards[i][j].type)
											{
												C_sound.play();
												cards[i][j].is_cleared = 1;
												cards[compare_card.id_i][compare_card.id_j].is_cleared = 1;
											}
											// 두 카드가 다른 종류이면
											else
											{
												delay_time = spent_time;
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}

		for (int i = 0; i < arr_size; i++)
		{
			for (int j = 0; j < arr_size; j++)
			{
				// 클릭이 된 상태이거나, 정답을 맞춘 카드이면
				if (cards[i][j].is_clicked == 1 || cards[i][j].is_cleared == 1)
				{
					// 그림이 있는 스프라이트로 변경(카드를 뒤집겠다는 의미)
					cards[i][j].sprite.setTexture(&texture[cards[i][j].type]);
				}
				else
					// 카드는 ???상태
					cards[i][j].sprite.setTexture(&texture[0]);
			}
		}

		// 뒤집힌 카드가 2개라면
		if (flipped_num == 2)
		{
			// 두 카드가 뒤집힌지 1초 이내라면
			if (spent_time - delay_time <= 1000)
			{
			}
			else
			{	// 다 ?상태로 만들어 버리겠다
				for (int i = 0; i < arr_size; i++)
					for (int j = 0; j < arr_size; j++)
						cards[i][j].is_clicked = 0;
				flipped_num = 0;
			}
		}


		sprintf(info, "%d \n", spent_time / 1000);
		text.setString(info);


		window.clear(Color::Black);
		for (int i = 0; i < arr_size; i++)
		{
			for (int j = 0; j < arr_size; j++)
			{
				window.draw(cards[i][j].sprite);
			}
		}

		window.draw(text);

		window.display();
	}
	return 0;
}
