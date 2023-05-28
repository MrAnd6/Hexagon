
#include "Menu.h"

//Private functions
void Menu::initTexts() {
    /**
        Initializing text elements
        - loads font
        - creates Texts
        - changes texts color
        - adds to vector of texts
     */
    if(!this->font.loadFromFile("CALIST.TTF"))
        std::cout << " ERROR::MENU::FONT::COULD NOT LOAD FONT FROM FILE" << "\n";
    this->menu = sf::Text(font, "Menu", 40);
    texts.push_back(sf::Text(font, "New Game", 25));
    texts.push_back(sf::Text(font, "Load Game", 25));
    texts.push_back(sf::Text(font, "Score Board", 25));
    texts.push_back(sf::Text(font, "Game Type", 25));
    for (sf::Text & text : texts){
        text.setFillColor(sf::Color::Black);
    }
}

void Menu::initMenu() {
    /**
        Intializing Menu background
        - creating rectangle that is menu background
        - changes menu color
     */
    this->mbg = sf::RectangleShape({800, 500});
    this->mbg.setFillColor(sf::Color(200, 0, 250, 120));
}

void Menu::setPos(sf::RenderTarget &target) {
    float x = target.getSize().x/2 - mbg.getSize().x / 2;
    float y = target.getSize().y/2 - mbg.getSize().y / 2;
    this->mbg.setPosition({x, y});
    this->menu.setPosition({x+50,y+40});
    for (sf::Text & text : texts){
        y += 50;
        text.setPosition({x+100 , y+70});
    }
}
int Menu::eventListener() {
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
        if(!mouseHeld){
            mouseHeld = true;
            if (this->texts.at(0).getGlobalBounds().contains((mousePos)))
                return 1;
            else if (this->texts.at(1).getGlobalBounds().contains((mousePos)))
                return 2;
            else if (this->texts.at(2).getGlobalBounds().contains((mousePos)))
                return 3;
            else if (this->texts.at(3).getGlobalBounds().contains((mousePos)))
                return 4;
            else return 0;
        }

    } else
        mouseHeld = false;
    return 0;
}

//Constructor and destructor
Menu::Menu() : menu(font){
    this->initTexts();
    this->initMenu();
}

Menu::~Menu() {
    delete this;
}

//Public functions
void Menu::update(sf::Vector2f pos, int & state) {
    this->mousePos = pos;
    state = this->eventListener();
}

void Menu::render(sf::RenderTarget & target) {
    /**
        Drawing menu elements
     */
    this->setPos(target);
    target.draw(mbg);
    target.draw(menu);
    for (sf::Text & text : texts){
        target.draw(text);
    }
}




