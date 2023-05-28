
#include "GameType.h"

///Private functions
void GameType::initVariables() {
    /**
     * \brief Initializes default values of variables
     */
    this->mouseHeld = false;
}

void GameType::initGUI() {
    /**
     * \brief Initializes GUI components
     */
    this->background = sf::RectangleShape({500,400});
    this->background.setFillColor(sf::Color(147,9,220, 200));
    if(!this->font.loadFromFile("CALIST.TTF"))
        std::cout << " ERROR::GAMETYPE::FONT::COULD NOT LOAD FONT FROM FILE" << "\n";
    this->texts.push_back(sf::Text(font, "Choose game type", 50));
    this->texts.push_back(sf::Text(font, "Player vs player", 35));
    this->texts.push_back(sf::Text(font, "Player vs computer", 35));
    for (sf::Text & text : texts)
        text.setFillColor(sf::Color::Black);
}

void GameType::setPos() {
    /**
     * \brief Sets positions of GUI components
     */
    this->background.setPosition({350, 200});
    this->texts.at(0).setPosition({400,230});
    this->texts.at(1).setPosition({480, 340});
    this->texts.at(2).setPosition({460, 420});
}

int GameType::actionListener() {
    /**
     * \brief Listens for mouse event happened
     *
     * \return Value that sets game type
     */
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
        if (!mouseHeld){
            mouseHeld = true;
            if(texts.at(1).getGlobalBounds().contains(mousePos))
                return 1;
            else if(texts.at(2).getGlobalBounds().contains(mousePos)) {
                return 2;
            }
        }
    } else mouseHeld = false;
    return 0;
}

///Constructor and destructor
GameType::GameType() {
    /**
     * \brief Default constructor
     *
     * Using other methods initializes and sets default values and positions
     */
    this->initVariables();
    this->initGUI();
    this->setPos();
}

GameType::~GameType() {
    /**
     * \brief Destructor
     */
    delete this;
}

///Public functions
void GameType::update(sf::Vector2f pos, int & state, bool & player) {
    /**
     * \brief Updates state and which game type was chosen
     *
     * \param pos Mouse position
     * \param state State from the Window class
     * \param player Variable from Window class that is used to check who will play(player or computer)
     */
    this->mousePos = pos;
    int type = actionListener();
    if(type == 2){
        player = false;
        state = 0;
    } else if(type == 1){
        player = true;
        state = 0;
    }

}

void GameType::render(sf::RenderTarget & target) {
    /**
     * \brief Draws menu components
     *
     * \param target Target where components are drawn
     */
    target.draw(background);
    for(sf::Text & text : texts)
        target.draw(text);
}
