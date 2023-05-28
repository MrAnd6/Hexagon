
#include "Saver.h"

///Private functions

void Saver::initVariables() {
    /**
     * \brief Initializes default values of variables
     */
    this->mouseHeld = false;
}

void Saver::initGUI() {
    /**
     * \brief Initializes GUI elements of saver class
     */
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
    /**
     * \brief Sets positions of GUI elements
     */
    this->bg.setPosition({400, 250});
    this->texts.at(0).setPosition({560, 450});
    this->texts.at(1).setPosition({480, 280});
}

void Saver::eventListener() {
    /**
     * \brief Event listener for the event happened
     */
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
    /**
     * \brief Default constructor
     *
     * Using other methods initializes and sets default values and positions
     */
    this->initVariables();
    this->initGUI();
    this->setPos();
}

Saver::~Saver() {
    /**
     * \brief Destructor
     */
    delete this;
}

///Public functions
void Saver::update(sf::Vector2f pos, int & state) {
    /**
     * \brief Updates state
     *
     * \param pos Mouse position
     * \param state State from Window class
     */
    this->mousePos = pos;
    this->eventListener();
    state = this->state;
}

void Saver::render(sf::RenderTarget &target) {
    /**
     * \brief Draws GUI elements
     *
     * \param target Target where components are drawn
     */
    target.draw(this->bg);
    for(sf::Text & text : texts)
        target.draw(text);
}

void Saver::saveGame() {
    /**
     * \brief Saves the game data to a file
     *
     * Saves the game data to the file that user entered to the console
     */
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
    /**
     * \brief Chages state
     *
     * \param state New state
     */
    this->state = state;
}

void Saver::loadGame() {
    /**
     * \brief Loads game data from file
     *
     * Loads game data from file that user entered to the console to a vector of ints,
     * then calls loadGame() method in Hexagon class to convert this data
     */
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

