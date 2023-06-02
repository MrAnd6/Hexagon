
#include "Saver.h"

///Private functions

void Saver::initVariables() {
    this->mouseHeld = false;
}

void Saver::initGUI() {
    bg.setSize({400,300});
    bg.setFillColor(sf::Color(147,9,220, 200));
    if(!this->font.loadFromFile("CALIST.TTF"))
        std::cout << " ERROR::HEXAGON::FONT::COULD NOT LOAD FONT FROM FILE" << "\n";
    texts.push_back(sf::Text(font, "Quit", 30));
    texts.push_back(sf::Text(font, "Please enter a\n    file path\nto the console", 40));
    for (sf::Text & text : texts)
        text.setFillColor(sf::Color::Black);
}

void Saver::setPos() {
    this->bg.setPosition({400, 250});
    this->texts.at(0).setPosition({560, 450});
    this->texts.at(1).setPosition({480, 280});
}

void Saver::eventListener() {
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        if (!mouseHeld) {
            mouseHeld = true;
            if(texts.at(0).getGlobalBounds().contains(mousePos))
                this->state = 0;
        } else mouseHeld = false;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)){
        if(this->state == 2)
            this->state = 1;
        if(this->state == 5)
            saveGame();
    }
}

///Constructor and Destructor
Saver::Saver() {
    this->initVariables();
    this->initGUI();
    this->setPos();
}

Saver::~Saver() {
}

///Public functions
void Saver::update(sf::Vector2f pos, int & state) {
    this->mousePos = pos;
    this->eventListener();
    state = this->state;
}

void Saver::render(sf::RenderTarget &target) {
    target.draw(this->bg);
    for(sf::Text & text : texts)
        target.draw(text);
}

void Saver::saveGame() {
    std::fstream file;
    std::string path;
    std::cin >> path;
    file.open(path, std::ios_base::out);
    if (file.is_open()) {
        std::vector<int> vec = Hexagon::getField();
        for (int i : vec)
            file << i << " ";
        this->state = 0;
    }
    else
        std::cout<<"ERROR::SAVER::CANNOT OPEN THE FILE"<<'\n';
}

void Saver::changeState(int state) {
    this->state = state;
}

void Saver::loadGame() {
    std::fstream file;
    std::string path;
    std::cin >> path;
    file.open(path, std::ios_base::in);
    std::vector<int> vec;
    int var;
    while(file >> var){
        vec.push_back(var);
    }
    Hexagon::loadGame(vec);
}

