#include<SFML/Graphics.hpp>

using namespace sf;

struct Player {
	RectangleShape sprite;
	int fps;                 // Frames per sec
	int idx;                // 애니메이션 index
};

int main()
{
	RenderWindow window(VideoMode(1200, 800), "Card Game!");
	window.setFramerateLimit(60);

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
	player.sprite.setTexture(&run[0]);
	player.sprite.setSize(Vector2f(90, 120));
	player.sprite.setPosition(200, 600);

	while (window.isOpen())
	{
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

		window.clear(Color::Magenta);

		window.draw(player.sprite);

		window.display();
	}

	return 0;
}
