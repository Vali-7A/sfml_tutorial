class Game {
       public:
	   						Game();
           void             run();
       private:
           void             processEvents();
           void             update(sf::Time);
           void             render();
           void             handlePlayerInput(sf::Keyboard::Key, bool);
       private:
           sf::RenderWindow mWindow;
           sf::Texture mTexture;
           sf::Sprite  mPlayer;
           bool mIsMovingUp = false;
           bool mIsMovingDown = false;
           bool mIsMovingLeft = false;
           bool mIsMovingRight = false;
           const float PlayerSpeed = 300.0f;
           const sf::Time TimePerFrame = sf::seconds(1.f / 60.f);
};

int main() {
	Game game;
	game.run();
}

Game::Game()
: mWindow(sf::VideoMode(640, 480), "SFML Application") , mPlayer()
{
    mWindow.setFramerateLimit(60);
    if (!mTexture.loadFromFile("src/Media/Textures/Eagle.png")) {
     // Handle loading error
   }
   mPlayer.setTexture(mTexture);
   mPlayer.setPosition(100.f, 100.f);
}
void Game::run()
{
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
	while (mWindow.isOpen()) {

        processEvents();
        timeSinceLastUpdate += clock.restart();
        while (timeSinceLastUpdate > TimePerFrame) {
            timeSinceLastUpdate -= TimePerFrame;
            processEvents();
            update(TimePerFrame);
        }
        render();
	}
}

void Game::processEvents()
{
	sf::Event event;
	while (mWindow.pollEvent(event)) {
		switch (event.type) {
            case sf::Event::KeyPressed:
                handlePlayerInput(event.key.code, true);
                break;
            case sf::Event::KeyReleased:
                handlePlayerInput(event.key.code, false);
                break;
            case sf::Event::Closed:
                mWindow.close();
                break;
            default:
                break;
        }
	}
}

void Game::update(sf::Time deltaTime)
{
    sf::Vector2f movement(0.f, 0.f);
    if (mIsMovingUp)
        movement.y -= PlayerSpeed;
    if (mIsMovingDown)
        movement.y += PlayerSpeed;
    if (mIsMovingLeft)
        movement.x -= PlayerSpeed;
    if (mIsMovingRight)
        movement.x += PlayerSpeed;

    mPlayer.move(movement*deltaTime.asSeconds());
}

 void Game::render()
{
	mWindow.clear();
    mWindow.draw(mPlayer);
    mWindow.display();
}

void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{
    if (key == sf::Keyboard::W)
        mIsMovingUp = isPressed;
    else if (key == sf::Keyboard::S)
        mIsMovingDown = isPressed;
    else if (key == sf::Keyboard::A)
        mIsMovingLeft = isPressed;
    else if (key == sf::Keyboard::D)
        mIsMovingRight = isPressed;
}
