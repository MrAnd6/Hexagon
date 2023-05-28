

#ifndef HEXAGON_HEXAGON_H
#define HEXAGON_HEXAGON_H

#include <iostream>
#include "ScoreBoard.cpp"

class Hexagon {
private:
    //Variables
    static int field[17][9];
    static int blue;
    static int red;
    bool player;
    bool quit;
    bool mouseHeld;
    bool isSelected;
    bool end;

    //GUI components
    sf::RectangleShape background;
    sf::Texture bg;
    sf::Texture gem;
    sf::RectangleShape exitbg;
    sf::RectangleShape endbg;
    sf::Vector2i selectedFigure;
    std::vector<sf::CircleShape> figures;
    std::vector<sf::Text> texts;
    sf::CircleShape chosen;
    sf::Vector2f mousePos;
    sf::Font font = sf::Font();
    sf::Color turn;


    //Private functions
    void initVariables();
    void initGUI();
    void setPos();
    void newFigure();
    int eventListener();
    void updateScore();
    void updateFigures();
    void selectFigure(sf::CircleShape & fig);
    int possibleMoves(sf::Vector2i pos);
    void exitWindow(sf::RenderTarget & target);
    void endGame(sf::RenderTarget & target);
    void makeMove(sf::Vector2i pos);
    void unselectFigure(bool change);
    void changeTurn();
    static sf::Vector2i findInArr(sf::CircleShape & fig);
    int countPoints(sf::Vector2i pos, bool clone);
    void captureFigures(sf::Vector2i pos);
    void computerTurn();
    bool noMoves();
public:
    //Constructor and Destructor
    Hexagon();
    ~Hexagon();

    //Public functions
    void eraseField();
    void setGameType(bool player);
    void update(sf::Vector2f pos, int & state);
    void render(sf::RenderTarget & target);
    static void loadGame(std::vector<int> vec);
    static std::vector<int> getField();
};


#endif //HEXAGON_HEXAGON_H
