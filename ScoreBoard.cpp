
#include "ScoreBoard.h"
/**
 * \brief Implementation of static variables
 */
std::vector<int> ScoreBoard::scores;

///Private functions
void ScoreBoard::initVariables() {
    this->read();
    this->mouseHeld = false;
}

void ScoreBoard::initGUI() {
     this->bg.setSize({800, 500});
     this->bg.setFillColor(sf::Color(147,9,220, 200));
     if(!this->font.loadFromFile("CALIST.TTF"))
        std::cout << " ERROR::SCOREBOARD::FONT::COULD NOT LOAD FONT FROM FILE" << "\n";
     this->texts.push_back(sf::Text(font, "Quit",40));
     this->texts.push_back(sf::Text(font, "Best Scores", 50));
     this->texts.push_back(sf::Text(font, "", 40));
     this->texts.push_back(sf::Text(font, "", 40));
     for (sf::Text & text : texts)
         text.setFillColor(sf::Color::Black);
}

void ScoreBoard::setPos() {
    this->bg.setPosition({200,150});
    this->texts.at(0).setPosition({220,170});
    this->texts.at(1).setPosition({480,180});
    this->texts.at(2).setPosition({450, 260});
    this->texts.at(3).setPosition({660, 260});
}

int ScoreBoard::eventListener() {
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
        if(!mouseHeld){
            mouseHeld = true;
            if(texts.at(0).getGlobalBounds().contains(this->mousePos))
                return 0;
        }
    }else mouseHeld = false;
    return 3;
}

void ScoreBoard::read() {
    this->scores.erase(scores.begin(), scores.end());
    std::fstream file;
    file.open("Scores", std::ios_base::in);
    if(!file.is_open())
        std::cout << "ERROR::SCOREBOARD::CANNOT OPEN THE FILE" << '\n';
    int res;
    while (file >> res){
        scores.push_back(res);
    }
    file.close();
    this->updateScores();
}

void ScoreBoard::write() {
    std::fstream file;
    file.open("Scores", std::ios_base::out);
    std::remove("Scores");
    for (int i : scores)
        file << i << " ";
}

void ScoreBoard::updateScores() {
    std::stringstream ssb;
    std::stringstream ssr;
    ssb<<"Blue:\n";
    ssr<<"Red:\n";
    for (int i = 0; i < 10; ++i) {
        if (i % 2 == 0)
            ssb <<"  "<< (i<scores.size() && !scores.empty() ? scores.at(i) : 0) << '\n';
        else
            ssr <<"  "<< (i<scores.size() && !scores.empty() ? scores.at(i) : 0) << '\n';
    }
    texts.at(2).setString(ssb.str());
    texts.at(3).setString(ssr.str());
}

///Constructor and Destructor
ScoreBoard::ScoreBoard() {
    this->initGUI();
    this->initVariables();
    this->setPos();
}

ScoreBoard::~ScoreBoard() {
    delete this;
}

//Public functions
void ScoreBoard::save(sf::Vector2i result) {
    for (int i = 0; i < 10;) {
        if(scores.size() < 10){
            scores.push_back(result.x);
            scores.push_back(result.y);
            break;
        }
        else{
            int dif = abs(scores.at(i) - scores.at(i+1));
            if (dif < abs(result.x - result.y)){
                scores.erase(scores.begin()+i);
                scores.erase(scores.begin()+i+1);
                scores.push_back(result.x);
                scores.push_back(result.y);
                break;
            }
        }
        i+=2;
    }
    write();
}

void ScoreBoard::update(sf::Vector2f pos, int &state) {
    this->mousePos = pos;
    state = this->eventListener();
    this->updateScores();

}

void ScoreBoard::render(sf::RenderTarget &target) {
    target.draw(this->bg);
    for(sf::Text & text : texts)
        target.draw(text);
}
