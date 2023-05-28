
#include "Menu.h"

///Private functions
void Menu::initTexts() {
    /**
     * \brief Initializes texts
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
     * \brief Initializes menu background
     */
    this->mbg = sf::RectangleShape({800, 500});
    this->mbg.setFillColor(sf::Color(147,9,220, 200));
}

void Menu::setPos(sf::RenderTarget &target) {
    /**
     * Sets positions of GUI components
     *
     * \param target Target where components are drawn
     */
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
    /**
     * \brief Listens for mouse event happened
     *
     * \return Value that changes state in Window class
     */
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

///Constructor and destructor
Menu::Menu() : menu(font){
    /**
     * \brief Default constructor
     *
     * Using other methods initializes and sets default values and positions
     */
    this->initTexts();
    this->initMenu();
}

Menu::~Menu() {
    /**
     * \brief Destructor
     */
    delete this;
}

///Public functions
void Menu::update(sf::Vector2f pos, int & state) {
    /**
     * \brief Updates mouse position and state
     *
     * \param pos Mouse position
     * \param state State from Window class
     */
    this->mousePos = pos;
    state = this->eventListener();
}

void Menu::render(sf::RenderTarget & target) {
    /**
     * \brief Draws menu components
     *
     * \param target Target where components are drawn
     */
    this->setPos(target);
    target.draw(mbg);
    target.draw(menu);
    for (sf::Text & text : texts){
        target.draw(text);
    }
}




