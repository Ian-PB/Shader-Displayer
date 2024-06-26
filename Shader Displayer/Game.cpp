#include "Game.h"
#include <iostream>

Game::Game() :
    m_window{ sf::VideoMode{ SCREEN_SIZE, SCREEN_SIZE, 32U }, "SFML Game" },
    m_exitGame{ false } // when true game will exit
{
    setupFontAndText(); // load font 
    setupSprite(); // load texture
}

Game::~Game()
{
}

void Game::run()
{
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    const float fps{ 60.0f };
    sf::Time timePerFrame = sf::seconds(1.0f / fps); // 60 fps
    while (m_window.isOpen())
    {
        processEvents(); // as many as possible
        timeSinceLastUpdate += clock.restart();
        while (timeSinceLastUpdate > timePerFrame)
        {
            timeSinceLastUpdate -= timePerFrame;
            processEvents(); // at least 60 fps
            update(timePerFrame); // 60 fps
        }
        render(); // as many as possible
    }
}

void Game::processEvents()
{
    sf::Event newEvent;
    while (m_window.pollEvent(newEvent))
    {
        if (sf::Event::Closed == newEvent.type) // window message
        {
            m_exitGame = true;
        }
        if (sf::Event::KeyPressed == newEvent.type) // user pressed a key
        {
            processKeys(newEvent);
        }

        // Mouse
        if (sf::Event::MouseMoved == newEvent.type) // user pressed a key
        {
            processMouseMove(newEvent);
        }
        if (sf::Event::MouseButtonPressed == newEvent.type) // user pressed a key
        {
            processMouseDown(newEvent);
        }
    }
}

void Game::processMouseMove(sf::Event t_event)
{
    // Gets the position of the mouse
    mousePos.x = static_cast<float>(t_event.mouseMove.x);
    mousePos.y = static_cast<float>(t_event.mouseMove.y);
}

void Game::processMouseDown(sf::Event t_event)
{
    rotation++;
    if (rotation < 0)
    {
        rotation = 360;
    }
    else if (rotation > 360)
    {
        rotation = 0;
    }

    squareDisplay.setRotation(rotation);
    sprite.setRotation(rotation);
}

void Game::processKeys(sf::Event t_event)
{
    if (sf::Keyboard::Escape == t_event.key.code)
    {
        m_exitGame = true;
    }

    if (sf::Keyboard::F1 == t_event.key.code)
    {
        displayType++;
        if (displayType >= 4)
        {
            displayType = 0;
        }
    }
}

void Game::update(sf::Time t_deltaTime)
{
    if (m_exitGame)
    {
        m_window.close();
    }

    updateShader();
}

void Game::render()
{
    m_window.clear(sf::Color::White);

    switch (displayType)
    {
    default:
        break;

    case 0:
        m_window.draw(squareDisplay, &shader); // Shadow
        m_window.draw(squareDisplay);
        break;

    case 1:
        m_window.draw(circleDisplay, &shader); // Shadow
        m_window.draw(circleDisplay);
        break;

    case 2:
        m_window.draw(sprite, &shader); // Shadow
        m_window.draw(sprite);
        break;

    case 3:
        m_window.draw(sprite, &post); // Post Processing
        break;
    }


    m_window.display();
}

void Game::setupFontAndText()
{
    // Load and set up the font and text here
}

void Game::setupSprite()
{
    // Shader display
    squareDisplay.setFillColor(sf::Color::Blue);
    squareDisplay.setSize({ (float)size, (float)size });
    squareDisplay.setOrigin(size / 2.0, size / 2.0);
    squareDisplay.setPosition(position);

    circleDisplay.setPointCount(50);
    circleDisplay.setFillColor(sf::Color::Blue);
    circleDisplay.setRadius((float)size / 2);
    circleDisplay.setOrigin(size, size);
    circleDisplay.setPosition(position);

    // Shader
    if (!shader.loadFromFile("ASSETS\\SHADERS\\Shadow.vert", "ASSETS\\SHADERS\\Shadow.frag"))
    {
        std::cerr << "Error loading shaders" << std::endl;
    }

    // Sprite
    if (!texture.loadFromFile("ASSETS\\IMAGES\\ship.png"))
    {
        std::cerr << "Error loading texture" << std::endl;
    }
    // texture.setSmooth(true); // Optional: Makes the texture look smoother when scaled
    sprite.setTexture(texture);
    sprite.setOrigin(256, 256);
    sprite.setPosition(position);

   
    // Set texture uniform in shader
    shader.setUniform("u_texture", sf::Shader::CurrentTexture);


    // Post Processing Shader
    if (!post.loadFromFile("ASSETS\\SHADERS\\PostProcessing.frag", sf::Shader::Fragment))
    {
        std::cerr << "Error loading post processing shaders" << std::endl;
    }
    post.setUniform("u_texture", sf::Shader::CurrentTexture);
}

void Game::updateShader()
{
    // Update the time uniform each frame
    float gameTime = shaderTime.getElapsedTime().asSeconds();

    shader.setUniform("u_time", gameTime);
    shader.setUniform("u_mousePos", mousePos);

    post.setUniform("u_time", gameTime);
}
