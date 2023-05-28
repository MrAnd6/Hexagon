

#ifndef HEXAGON_HEXAGON_H
#define HEXAGON_HEXAGON_H

#include <iostream>
#include "ScoreBoard.cpp"

class Hexagon {
private:
    ///Variables
    static int field[17][9];                ///Static array representing the game board
    static int blue;                        ///Number representing amount of blue figures
    static int red;                         ///Number representing amount of red figures
    bool player;                            ///Flag indicating who is playing
    bool quit;                              ///Flag indicating if player wants to quit
    bool mouseHeld;                         ///Flag indicating if mouse button is held
    bool isSelected;                        ///Flag indicating if figure is selected now
    bool end;                               ///Flag indicating if the game has ended

    ///GUI components
    sf::RectangleShape background;          ///Background shape for the game
    sf::Texture bg;                         ///Texture for the background
    sf::Texture gem;                        ///Texture for the figures
    sf::RectangleShape exitbg;              ///Background for the exit window
    sf::RectangleShape endbg;               ///Background for the end game window
    sf::Vector2i selectedFigure;            ///Index of the selected game piece in the field array.
    std::vector<sf::CircleShape> figures;   ///Vector of figures
    std::vector<sf::Text> texts;            ///Vector of texts
    sf::Vector2f mousePos;                  ///Vector of mouse position relative to the window
    sf::Font font = sf::Font();             ///Font for the game texts
    sf::Color turn;                         ///Color representing current turn


    ///Private functions
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
    ///Constructor and Destructor
    Hexagon();
    ~Hexagon();

    ///Public functions
    void eraseField();
    void setGameType(bool player);
    void update(sf::Vector2f pos, int & state);
    void render(sf::RenderTarget & target);
    static void loadGame(std::vector<int> vec);
    static std::vector<int> getField();
};


#endif //HEXAGON_HEXAGON_H
