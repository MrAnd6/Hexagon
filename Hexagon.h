

#ifndef HEXAGON_HEXAGON_H
#define HEXAGON_HEXAGON_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <sstream>
#include <cmath>
class Hexagon {
private:
    //Variables
    int field[17][9];
    int blue;
    int red;
    bool quit;
    bool mouseHeld;
    bool isSelected;
    bool end;
    sf::RectangleShape background;
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
    void initvariables();
    void initGUI();
    void setPos();
    void newFigure();
    int eventListener();
    void updateScore();
    void updateFigures();
    void chooseFigure(sf::CircleShape & fig);
    void possibleMoves(sf::CircleShape & fig);
    void exitWindow(sf::RenderTarget & target);
    void endGame(sf::RenderTarget & target);
    void makeMove(sf::CircleShape & fig);\
    void unselectFigure(bool change);
    void changeTurn();
    void captureFigures(sf::CircleShape & fig);
public:
    //Constructor and Destructor
    Hexagon();
    ~Hexagon();
    //Public functions
    void eraseField();
    void update(sf::Vector2f pos, int & state);
    void render(sf::RenderTarget & target);
};


#endif //HEXAGON_HEXAGON_H
