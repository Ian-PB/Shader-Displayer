
#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include "Globals.h"

class Game
{
public:
	Game();
	~Game();
	/// <summary>
	/// main method for game
	/// </summary>
	void run();

private:

	void processEvents();
	void processKeys(sf::Event t_event);
	void processMouseMove(sf::Event t_event);
	void processMouseDown(sf::Event t_event);

	void update(sf::Time t_deltaTime);
	void render();

	void setupFontAndText();
	void setupSprite();

	void updateShader();

	sf::RenderWindow m_window; // main SFML window
	sf::Vector2f mousePos;
	// Shaders
	sf::Shader shader;
	sf::Shader post;

	// Display info
	int size = SCREEN_SIZE / 2;
	float rotation = 0.0f;
	sf::Vector2f position = { SCREEN_SIZE / 2.0f, SCREEN_SIZE / 2.0f };

	// Uniforms
	sf::Clock shaderTime;

	bool m_exitGame; // control exiting game

	// Sprite
	sf::Texture texture;
	sf::Sprite sprite;
	sf::RectangleShape squareDisplay;
	sf::CircleShape circleDisplay;

	int displayType = 0;
};

#endif // !GAME_HPP

