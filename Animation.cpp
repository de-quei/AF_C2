#include<SFML/Graphics.hpp>
#include<stdlib.h>
#include<time.h>

using namespace sf;

struct Player {
	RectangleShape sprite;
	int fps;                 // Frames per sec
	int idx;                 // 애니메이션 index
	int frame_num;           // 애니메이션 frame수
	long ani_time;           // 애니메이션이 바뀔 때의 시간

};

int main()
{
	RenderWindow window(VideoMode(1200, 800), "Animation");
	window.setFramerateLimit(60);

	long start_time;
	long spent_time;

	Texture run[10];
	run[0].loadFromFile("./resources/png/Run__000.png");
	run[1].loadFromFile("./resources/png/Run__001.png");
	run[2].loadFromFile("./resources/png/Run__002.png");
	run[3].loadFromFile("./resources/png/Run__003.png");
	run[4].loadFromFile("./resources/png/Run__004.png");
	run[5].loadFromFile("./resources/png/Run__005.png");
	run[6].loadFromFile("./resources/png/Run__006.png");
	run[7].loadFromFile("./resources/png/Run__007.png");
	run[8].loadFromFile("./resources/png/Run__008.png");
	run[9].loadFromFile("./resources/png/Run__009.png");

	struct Player player;
	player.fps = 10;
	player.frame_num = 10;
	player.idx = 0;
	player.sprite.setTexture(&run[0]);
	player.sprite.setSize(Vector2f(90, 120));
	player.sprite.setPosition(200, 600);

	start_time = clock();
	player.ani_time = start_time;

	while (window.isOpen())
	{
		spent_time = clock() - start_time;
		Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case Event::Closed:
				window.close();
				break;

			default:
				break;
			}
		}

		// 0.1초마다 애니메이션 그림이 바뀜
		while (spent_time - player.ani_time > 1000 / player.frame_num);
		{
			player.ani_time = spent_time;
			player.sprite.setTexture(&run[player.idx % player.frame_num]);
			player.idx++;
		}
		
		window.clear(Color::Magenta);

		window.draw(player.sprite);

		window.display();
	}

	return 0;
}
