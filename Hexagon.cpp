
#include "Hexagon.h"
//Private functions
void Hexagon::initVariables() {
    /**
        Initialises starting values.
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
    end=false;
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
    /**
        Creates new figures
        -creates new figures
        -adds figures to the vector of figures
     */
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

sf::Vector2i Hexagon::findInArr(sf::CircleShape & fig) {
    return sf::Vector2i{(static_cast<int>(fig.getPosition().x) - 280) / 70, (static_cast<int>(fig.getPosition().y) - 50) / 40};
}

 void Hexagon::selectFigure(sf::CircleShape & fig) {
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
    else {
        if (!isSelected) {
            fig.setOutlineColor(sf::Color::Yellow);
            selectedFigure = findInArr(fig);
        }
        else{
            fig.setOutlineColor(sf::Color::Transparent);
            selectedFigure = {0, 0};
        }
        isSelected = !isSelected;
        possibleMoves(findInArr(fig));
    }
}

int Hexagon::possibleMoves(sf::Vector2i pos) {
    /**
        Highlights or removes a highlight of possible moves
        -finds a position of figure in field array
        -finds a positions of possible moves in array
        if you selected your figure:
        -changes a value of empty slots from 0 to 3(possible move cell)
        if your removed a selection from your figure
        -changes a valur of selected slots from 3 to 0(empty cells)
     */
    int moves = 0;
    for (int i = pos.y-4; i <= pos.y+4; ++i) {
        if(i<0 || i>16)
            continue;
        for (int j = pos.x-2; j <= pos.x+2; ++j) {
            if(j<0 || j>8 || (abs(pos.x - j) + abs(pos.y - i) > 4))
                continue;
            else {
                if (field[i][j] == 0) {
                    field[i][j] = 3;
                    moves++;
                }
                else if (field[i][j] == 3) {
                    field[i][j] = 0;
                }
            }
        }
    }
    this->updateFigures();
    return moves;
}

void Hexagon::unselectFigure(bool change) {
    /**
        Unselects figures in the end of the move
        -finds figure that was selected
        -uses selectFigure to unselect figures
        -if you moved your figure to 2 cells, removes your figure from previous position
     */
    for (sf::CircleShape & fig : figures){
        if(fig.getOutlineColor() == sf::Color::Yellow){
            selectFigure(fig);
            if(change){
                fig.setFillColor(sf::Color::Black);
                sf::Vector2i pos = findInArr(fig);
                field[pos.y][pos.x] = 0;
            }
            break;
        }
    }
}

void Hexagon::makeMove(sf::Vector2i pos) {
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
    if(field[pos.y][pos.x] == 3) {
        bool change = !(abs(selectedFigure.x - pos.x) < 2 && abs(selectedFigure.y - pos.y) < 3);
        unselectFigure(change);
        if(turn == sf::Color::Blue) {
            field[pos.y][pos.x] = 1;
            if(!change)
                blue++;
        }
        else {
            field[pos.y][pos.x] = 2;
            if(!change)
                red++;
        }
        captureFigures(pos);
        changeTurn();
        if (noMoves())
            end=true;
    } else
        std::cout << "YOU CANT MOVE HERE\n";
}

void Hexagon::captureFigures(sf::Vector2i pos) {
    /**
        Captures figures of opponent if your figure moves to a position near them
        -finds a positions in array, where you want to move
        -checks which color makes move now
        -captures figures of opponent
        -adds points to you
        -removes points from your opponent
     */
    for (int i = pos.y - 2; i <= pos.y + 2; ++i) {
        if(i<0 || i>16)
            continue;
        for (int j = pos.x - 1; j <= pos.x + 1; ++j) {
            if(j<0 || j>8 || (abs(pos.x - j) + abs(pos.y - i) > 2))
                continue;
            if(turn == sf::Color::Blue && field[i][j] == 2) {
                field[i][j] = 1;
                blue++;
                red--;
            }
            else if(turn == sf::Color::Red && field[i][j] == 1) {
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

int Hexagon::countPoints(sf::Vector2i pos, bool clone) {
    int points = 0;
    for (int i = pos.y - 2; i <= pos.y + 2; ++i) {
        if(i<0 || i>16)
            continue;
        for (int j = pos.x - 1; j <= pos.x + 1; ++j) {
            if(j<0 || j>8 || (abs(pos.x - j) + abs(pos.y - i) > 2))
                continue;
            if(turn == sf::Color::Red && field[i][j] == 1) {
                points++;
            }
        }
    }
    if(clone)
        points++;
    return points;
}

void Hexagon::computerTurn() {
    sf::Vector2i move;
    sf::CircleShape* select;
    int possiblePoints = 0;
    for(sf::CircleShape & fig : figures){
        if(fig.getFillColor() == sf::Color::Red){
            sf::Vector2i pos = findInArr(fig);
            for (int i = pos.y-4; i <= pos.y+4; ++i) {
                if(i<0 || i>16)
                    continue;
                for (int j = pos.x-2; j <= pos.x+2; ++j) {
                    if(j<0 || j>8 || (abs(pos.x - j) + abs(pos.y - i) > 4))
                        continue;
                    if(field[i][j] == 3 || field[i][j] == 0){
                        int points = countPoints({j,i}, (abs(pos.x - j) < 2 && abs(pos.y - i) < 3));
                        if(points > possiblePoints){
                            select = &fig;
                            possiblePoints = points;
                            move = {j,i};
                        }
                    }
                }
            }
        }
    }
    selectFigure(*select);
    makeMove(move);
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
                            this->makeMove(findInArr(fig));
                        } else
                            this->selectFigure(fig);
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

void Hexagon::updateScore() {
    /**
        Updates score on the window
     */
    std::stringstream ss;
    ss<<"Blue: " << this->blue <<"\n"
      <<"Red: "<<this->red <<"\n";
    this->texts.at(1).setString(ss.str());
}

void Hexagon::updateFigures() {
    /**
        Updates outlines and figure colors
        -0 empty field
        -1 blue figure
        -2 red figure
        -3 possible fields to move
        -4 selected blue figure
        -5 selected red figure
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
//            if(field[i][j] == 4 || field[i][j] == 5)
//                figures.at(idx++).setOutlineColor(sf::Color::Yellow);
        }
    }
}

bool Hexagon::noMoves() {
    for (sf::CircleShape & fig : figures){
        if(fig.getFillColor() == turn) {
            int moves = possibleMoves(findInArr(fig));
            possibleMoves(findInArr(fig));
            if (moves != 0)
                return false;
        }
    }
    return true;
}

void Hexagon::exitWindow(sf::RenderTarget & target) {
    /**
        Draws an exit window in the window
     */
    target.draw(exitbg);
    target.draw(texts.at(2));
    target.draw(texts.at(3));
    target.draw(texts.at(4));
}

void Hexagon::endGame(sf::RenderTarget & target) {
    /**
        Draws an end game window in the window
        -checks who won a game
        -changes the end game text
        -draws end game components in the window
     */
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
    this->initVariables();
    this->initGUI();
    this->setPos();
}

Hexagon::~Hexagon() {
    delete this;
}

//Public functions
void Hexagon::update(sf::Vector2f pos, int & state) {
    /**
        Updates components of the game
     */
    if(!player && turn == sf::Color::Red)
        computerTurn();
    this->mousePos = pos;
    state = this->eventListener();
    this->updateScore();
    this->updateFigures();
    if (!end)
        end = (blue == 0 || red == 0 || blue+red == 58);
}

void Hexagon::render(sf::RenderTarget &target) {
    /**
        Draws components of the game in the window
     */
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
    /**
        Erases field in case to start a new game
     */
    this->figures.erase(figures.begin(), figures.end());
    this->initVariables();
    this->initGUI();
    this->setPos();

}

void Hexagon::setGameType(bool player) {
    /**
        Sets type of the game
        -player vs player
        -player vs computer
     */
    this->player = player;
}

void Hexagon::loadGame(int *arr[17][9]) {
    for (int i=0; i<17; ++i){
        for (int j = 0; j < 9; ++j) {
            field[i][j] = *arr[i][j];
        }
    }
}


