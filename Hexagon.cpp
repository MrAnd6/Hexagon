
#include "Hexagon.h"
//Private functions
void Hexagon::initvariables() {
    /**
        Initialise starting values.
        -in for loop places numbers -1, 0 that represents non-game, game positions
        -changes 3 positions in center to non-game
        -places 3 blue figures(1) and 3 red figures(2) on their starting positions
        -sets turn to blue
        -sets blue and green scores to 3
     */
    for (int i = 0; i < 17; ++i) {
        for (int j = 0; j < 9; ++j) {
            if((i+j) % 2 == 0) {
                if ((i < 4 && j > 3 - i && j < 5 + i) || (i > 13 && j > i-13 && j < 22-i))
                    field[i][j] = 0;
                else
                    field[i][j] = -1;
                if (i > 3 && i < 14)
                    field[i][j] = 0;
            }else
                field[i][j] = -1;
        }
    }
    //Empty positions in center
    field[6][4] = -1;
    field[9][3] = -1;
    field[9][5] = -1;
    //Red figures
    field[0][4] = 2;
    field[12][0] = 2;
    field[12][8] = 2;
    //Blue figures
    field[4][0] = 1;
    field[4][8] = 1;
    field[16][4] = 1;
    turn=sf::Color::Blue;
    quit=false;
    mouseHeld=false;
    isSelected=false;
    blue=3;
    red=3;
}

void Hexagon::initGUI() {
    /**
        Initializes GUI elements of hexagon game
        -sets background
        -create elements of field
        -upload font
        -initialize text
     */
    this->background = sf::RectangleShape({1200, 800});
    this->background.setFillColor(sf::Color::White);
    for (int i = 0; i < 17; ++i) {
        for (int j = 0; j < 9; ++j) {
            if (field[i][j] == 1 || field[i][j] == 2 || field[i][j] == 0)
                this->newFigure();
        }
    }
    this->exitbg.setSize({200,100});
    this->exitbg.setFillColor(sf::Color::White);
    this->exitbg.setOutlineColor(sf::Color::Black);
    this->exitbg.setOutlineThickness(2);
    this->endbg.setSize({300,200});
    this->endbg.setFillColor(sf::Color::White);
    this->endbg.setOutlineColor(sf::Color::Black);
    this->endbg.setOutlineThickness(2);
    if(!this->font.loadFromFile("CALIST.TTF"))
        std::cout << " ERROR::HEXAGON::FONT::COULD NOT LOAD FONT FROM FILE" << "\n";
    texts.push_back(sf::Text(font, "Quit", 40));
    texts.push_back(sf::Text(font, "", 30));
    texts.push_back(sf::Text(font, "Save game?", 30));
    texts.push_back(sf::Text(font, "Yes", 20));
    texts.push_back(sf::Text(font, "No", 20));
    texts.push_back(sf::Text(font, "", 50));
    texts.push_back(sf::Text(font, "Menu", 30));
    for(sf::Text & text : texts)
        text.setFillColor(sf::Color::Black);
}

void Hexagon::newFigure() {
    sf::CircleShape figure = sf::CircleShape(30,6);
    figure.setOutlineThickness(7);
    figure.setOutlineColor(sf::Color::Transparent);
    figure.setFillColor(sf::Color::Black);
    figures.push_back(figure);
}

void Hexagon::setPos() {
    /**
        Sets positions of game elements in window
        -sets positions of figures

     */
    int idx = 0;
    float x = 280;
    float y = 50;
    for (int i = 0; i < 17; ++i) {
        for (int j = 0; j < 9; ++j) {
            if(field[i][j] == 0 || field[i][j] == 1 || field[i][j] == 2){
                figures.at(idx++).setPosition({x,y});
            }
            x+=70;
        }
        x = 280;
        y += 40;
    }
    this->texts.at(0).setPosition({50,50});
    this->texts.at(1).setPosition({50,700});
    this->exitbg.setPosition({950,50});
    this->endbg.setPosition({450, 300});
    texts.at(2).setPosition({exitbg.getPosition().x+20, exitbg.getPosition().y+20});
    texts.at(3).setPosition({exitbg.getPosition().x+50, exitbg.getPosition().y+70});
    texts.at(4).setPosition({exitbg.getPosition().x+100, exitbg.getPosition().y+70});
    texts.at(5).setPosition({500, 330});
    texts.at(6).setPosition({560, 400});
}

void Hexagon::chooseFigure(sf::CircleShape & fig) {
    /**
        Highlights or removes a highlight of figure that you hove chosen
        -checks if you have chosen your figure
        -checks if figure was already selected
        -highlights or remove a highlight of figure
        -assigns coordinates of chosen figure to the variable
        -uses possibleMoves() to highlight or remove a highlight of possible moves
     */
    if(fig.getFillColor() != this->turn)
        std::cout << "ITS NOT YOUR FIGURE!\n";
    else if(fig.getFillColor() == this->turn && !isSelected){
        fig.setOutlineColor(sf::Color::Yellow);
        int x = (static_cast<int>(fig.getPosition().x) - 280) / 70;
        int y = (static_cast<int>(fig.getPosition().y) - 50) / 40;
        selectedFigure = {x,y};
        isSelected = true;
        possibleMoves(fig);
    } else if (fig.getOutlineColor() == sf::Color::Yellow && isSelected){
        fig.setOutlineColor(sf::Color::Transparent);
        selectedFigure = {0,0};
        isSelected = false;
        possibleMoves(fig);
    }
}

void Hexagon::possibleMoves(sf::CircleShape &fig) {
    /**
        Highlights or removes a highlight of possible moves
        -finds a position of figure in field array
        -finds a positions of possible moves in array
        if you selected your figure:
        -changes a value of empty slots from 0 to 3(possible move cell)
        if your removed a selection from your figure
        -changes a valur of selected slots from 3 to 0(empty cells)
     */
    int x = (static_cast<int>(fig.getPosition().x) - 280) / 70;
    int y = (static_cast<int>(fig.getPosition().y) - 50) / 40;
    for (int i = y-4; i <= y+4; ++i) {
        if(i<0 || i>16)
            continue;
        for (int j = x-4; j <= x+4; ++j) {
            if(j<0 || j>8 || (abs(x - j) + abs(y - i) > 4 || abs(x-j) > 2))
                continue;
            if (field[i][j] == 0 && isSelected)
                field[i][j] = 3;
            if(field[i][j] == 3 && !isSelected)
                field[i][j] = 0;
        }
    }
    this->updateFigures();
}


void Hexagon::updateScore() {
    /**
        Update score on the window
     */
    std::stringstream ss;
    ss<<"Blue: " << this->blue <<"\n"
        <<"Red: "<<this->red <<"\n";
    this->texts.at(1).setString(ss.str());
}

void Hexagon::updateFigures() {
    /**
        Updates outlines and figure colors
     */
    int idx = 0;
    for (int i = 0; i < 17; ++i) {
        for (int j = 0; j < 9; ++j) {
            if(field[i][j] == 0)
                figures.at(idx++).setOutlineColor(sf::Color::Transparent);
            if(field[i][j] == 1)
                figures.at(idx++).setFillColor(sf::Color::Blue);
            if(field[i][j] == 2)
                figures.at(idx++).setFillColor(sf::Color::Red);
            if(field[i][j] == 3)
                figures.at(idx++).setOutlineColor(sf::Color::Green);
        }
    }
}

void Hexagon::makeMove(sf::CircleShape & fig) {
    /**
        Makes a move
        -finds where you want to go
        -checks is its a valid move
        -checks if you move to 2 cells
        -uses unselectFigure() to remove selection
        -clones figure if you move to 1 cell and adds you a point
        -uses captureFigures() to capture opponent figures
        -uses changeTurn() to end turn
     */
    int x = (static_cast<int>(fig.getPosition().x) - 280) / 70;
    int y = (static_cast<int>(fig.getPosition().y) - 50) / 40;
    if(field[y][x] == 3) {
        bool change = !(abs(selectedFigure.x - x) < 2 && abs(selectedFigure.y - y) < 3);
        unselectFigure(change);
        if(turn == sf::Color::Blue) {
            field[y][x] = 1;
            if(!change)
                blue++;
        }
        else {
            field[y][x] = 2;
            if(!change)
                red++;
        }
        captureFigures(fig);
        changeTurn();

    } else
        std::cout << "YOU CANT MOVE HERE\n";
}


void Hexagon::unselectFigure(bool change) {
    /**
        Unselects figures in the end of the move
        -finds figure that was selected
        -uses chooseFigure to unselect figures
        -if you moved your figure to 2 cells, removes your figure from previous position
     */
    for (sf::CircleShape & fig : figures){
        if(fig.getOutlineColor() == sf::Color::Yellow){
            chooseFigure(fig);
            if(change){
                fig.setFillColor(sf::Color::Black);
                int x = (static_cast<int>(fig.getPosition().x) - 280) / 70;
                int y = (static_cast<int>(fig.getPosition().y) - 50) / 40;
                field[y][x] = 0;
            }
            break;
        }
    }
}

void Hexagon::captureFigures(sf::CircleShape &fig) {
    /**
        Captures figures of opponent if your figure moves to a position near them
        -finds a positions in array, where you want to move
        -checks which color makes move now
        -captures figures of opponent
        -adds points to you
        -removes points from your opponent
     */
    int x = (static_cast<int>(fig.getPosition().x) - 280) / 70;
    int y = (static_cast<int>(fig.getPosition().y) - 50) / 40;
    for (int i = y - 2; i <= y + 2; ++i) {
        for (int j = x - 1; j <= x + 1; ++j) {
            if(turn == sf::Color::Blue && field[i][j] == 2) {
                field[i][j] = 1;
                    red--;
                    blue++;
            }
            if(turn == sf::Color::Red && field[i][j] == 1) {
                field[i][j] = 2;
                blue--;
                red++;
            }
        }
    }
}

void Hexagon::changeTurn() {
    /**
        Changes turn to opponent
     */
    if(turn == sf::Color::Blue)
        turn = sf::Color::Red;
    else
        turn = sf::Color::Blue;
}

int Hexagon::eventListener() {
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
        if(!mouseHeld){
            mouseHeld = true;
            if(!end){
                if (quit) {
                    if (texts.at(3).getGlobalBounds().contains(mousePos))
                        return 1;
                    else if (texts.at(4).getGlobalBounds().contains(mousePos)) {
                        quit = false;
                        return 0;
                    } else if (!exitbg.getGlobalBounds().contains(mousePos))
                        quit = false;
                }
                if (this->texts.at(0).getGlobalBounds().contains(mousePos))
                    this->quit = true;
                for (sf::CircleShape &fig: figures) {
                    if (fig.getGlobalBounds().contains(mousePos)) {
                        if (isSelected && fig.getOutlineColor() != sf::Color::Yellow) {
                            this->makeMove(fig);
                        } else
                            this->chooseFigure(fig);
                    }
                }
            } else{
                if (this->texts.at(6).getGlobalBounds().contains(mousePos)){
                    //write to file results
                    return 0;
                }
            }
        }
    }else mouseHeld = false;
    return 1;
}

void Hexagon::exitWindow(sf::RenderTarget & target) {
    target.draw(exitbg);
    target.draw(texts.at(2));
    target.draw(texts.at(3));
    target.draw(texts.at(4));
}

void Hexagon::endGame(sf::RenderTarget & target) {
    if(blue == red) {
        texts.at(5).setString("Draw");
        texts.at(5).setFillColor(sf::Color(200, 0 ,250));
    }
    else if(blue>red) {
        texts.at(5).setString("Blue wins");
        texts.at(5).setFillColor(sf::Color::Blue);
    }
    else {
        texts.at(5).setString("Red wins");
        texts.at(5).setFillColor(sf::Color::Red);
    }
    target.draw(endbg);
    target.draw(texts.at(5));
    target.draw(texts.at(6));
}

//Constructor and Destructor
Hexagon::Hexagon() {
    this->initvariables();
    this->initGUI();
    this->setPos();
    for (int i = 0; i < 17; ++i) {
        for (int j = 0; j < 9; ++j) {
            std::cout<<field[i][j]<<"   ";
        }
        std::cout<<"\n";
    }
}

Hexagon::~Hexagon() {
    delete this;
}

//Public functions
void Hexagon::update(sf::Vector2f pos, int & state) {
    this->mousePos = pos;
    state = this->eventListener();
    this->updateScore();
    this->updateFigures();
    end = (blue == 0 || red == 0 || blue+red == 58);
}

void Hexagon::render(sf::RenderTarget &target) {
    target.draw(background);
    target.draw(texts.at(0));
    target.draw(texts.at(1));
    for (sf::CircleShape & i : figures) {
        target.draw(i);
    }
    if(quit)
        this->exitWindow(target);
    if(end)
        this->endGame(target);
}

void Hexagon::eraseField() {
    this->figures.erase(figures.begin(), figures.end());
    this->initvariables();
    this->initGUI();
    this->setPos();
}

