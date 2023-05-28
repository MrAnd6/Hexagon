
#include "GameType.h"
//Private functions

void GameType::initVariables() {
    this->mouseHeld = false;
}

void GameType::initGUI() {
    this->background = sf::RectangleShape({500,400});
    this->background.setFillColor(sf::Color(200, 0, 250, 120));
    if(!this->font.loadFromFile("CALIST.TTF"))
        std::cout << " ERROR::GAMETYPE::FONT::COULD NOT LOAD FONT FROM FILE" << "\n";
    this->texts.push_back(sf::Text(font, "Choose game type", 50));
    this->texts.push_back(sf::Text(font, "Player vs player", 35));
    this->texts.push_back(sf::Text(font, "Player vs computer", 35));
    for (sf::Text & text : texts)
        text.setFillColor(sf::Color::Black);
}

void GameType::setPos() {
    this->background.setPosition({350, 200});
    this->texts.at(0).setPosition({400,230});
    this->texts.at(1).setPosition({480, 340});
    this->texts.at(2).setPosition({460, 420});
}

int GameType::actionListener() {
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

//Constructor and destructor
GameType::GameType() {
    this->initVariables();
    this->initGUI();
    this->setPos();
}

GameType::~GameType() {
    delete this;
}

void GameType::update(sf::Vector2f pos, int & state, bool & player) {
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
    target.draw(background);
    for(sf::Text & text : texts)
        target.draw(text);
}
