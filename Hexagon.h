

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
    /**
     * \brief Initializes starting values
     */
    void initVariables();

    /**
     * \brief Initializes GUI elements of hexagon game
     */
    void initGUI();

    /**
     * \brief Creates new figures
     *
     * Creates a circle shape with 6 corners,
     * sets default parameters and adds a texture,
     * then adds figure to the vector of figures
     */
    void newFigure();

    /**
     * \brief Sets a positions of all the elements
     *
     * Uses 2 for loops to set figures positions
     * so they will be on the same distance from
     * each other. Sets a positions of other elements
     */
    void setPos();

    /**
     * \brief Finds a position of figure on the screen in array of ints
     *
     * \param fig Circle shape - figure that you want to find
     *
     * \return Vector with 2 ints - column and line in array
     */
    static sf::Vector2i findInArr(sf::CircleShape & fig);

    /**
     * \brief Adds or removes a selection on the figure that you have chosen
     *
     * Checks if you can select this figure, changes it out line color
     * to show that it is selected or not
     *
     * \param fig The figure you clicked on
     */
    void selectFigure(sf::CircleShape & fig);

    /**
     * \brief Finds possible positions where you can moke a move
     *
     * \param pos A vector with 2 ints which are positions of your figure in array
     *
     * This function takes a vector with 2 ints. Using two for loops finds
     * empty fields where you able to move your figure and counts how many
     * moves you can make, then returns amount of moves
     *
     * \return Amount of possible moves
     */
    int possibleMoves(sf::Vector2i pos);

    /**
     * \brief Finds selected figure
     *
     * \param Change Does it need to replace a figure to an empty cell
     *
     * Using enhanced for loop searches for figure that has selection,
     * calls selectFigure() method which removes a selection,
     * then if change is true makes figure as an empty cell
     * with changing its color to Black and replacing it in array
     */
    void unselectFigure(bool change);

    /**
     * \brief Makes a move
     *
     * \param pos Vector of 2 ints that is a position where you want to move to
     *
     * Takes a position where want to move your figure. Checks if you can move here,
     * checks if you moving on 2 cells, uses unselectFigure() method to remove
     * selection, replaces in array empty cell to your figure, adds points to you if needed,
     * uses captureFigures() method to capture opponent figures, changes turn to opponent,
     * then uses noMoves() to check if your opponent can move
     */
    void makeMove(sf::Vector2i pos);

    /**
     * \brief Captures opponent figures
     *
     * \param pos Vector with 2 ints which are a position where you moved your figure
     *
     * Takes a vector with the position in array of the cell where you moved. Finds if you
     * have near you opponent figures, than replaces them to yours and adds points to you
     */
    void captureFigures(sf::Vector2i pos);

    /**
     * \brief Changes turn
     */
    void changeTurn();

    /**
     * \brief Count how many points can be earned
     *
     * \param pos Vector with 2 ints of position to move to
     * \param clone If figure clones
     *
     * \return Amount of possible points
     *
     * Takes a position of theoretical figure place, finds if it will capture
     * opponent figures and counts how many point will be received, adds a point
     * if figure will be cloned, then returns an amount of possible points
     */
    int countPoints(sf::Vector2i pos, bool clone);

    /**
     * \brief Calculates a move of the computer
     *
     * Using enhanced for loop finds figure that can be moved, finds possible positions
     * where it can be moved, using countPoints() method finds how many points can be earned,
     * finds the move where computer gets the most points, then makes this move using
     * selectFigure() and makeMove() methods
     */
    void computerTurn();

    /**
     * \brief Listens for mouse event happened
     *
     * \return Value that changes state in Window class
     *
     * Checks if left mouse button is pressed and not held,
     * checks which components can be clicked, finds on what
     * component you clicked, then returns a value that is a
     * value of state on which it needs to be changed
     */
    int eventListener();

    /**
     * \brief Updates score on the screen
     *
     * Using string stream makes a string with scores,
     * then updates text with scores on the screen
     */
    void updateScore();

    /**
     * \brief Updates figures outlines and colors
     *
     * Using 2 for loops finds values of gaming components and updates
     * figures outlines and color in vector of them
     */
    void updateFigures();

    /**
     * \brief Checks if there are possible moves
     *
     * \return Possibility of moving
     *
     * Finds figures of turn color, using possibleMoves() method finds
     * how many moves you can do, returns if there are possible moves
     */
    bool noMoves();

    /**
     * \brief Draws components of exit window
     *
     * \param target Target where components are drawn
     */
    void exitWindow(sf::RenderTarget & target);

    /**
     * \brief Draws components of game ending
     *
     * \param target Target where components are drawn
     *
     * Checks who has won the game, sets text and color, then draws components
     */
    void endGame(sf::RenderTarget & target);

public:
    ///Constructor and Destructor
    /**
     * \brief Default constructor
     *
     * Using initVariables(), initGUI() and setPos() methods to initialise default
     * values of variables, create and set GUI components and set them positions in the window
     */
    Hexagon();

    /**
     * \brief Destructor
     */
    ~Hexagon();

    ///Public functions
    /**
     * \brief Updates components of the game
     *
     * Checks if computer needs to make turn, updates mouse position,
     * changes state in Window class if needed, uses other methods to update
     * screen components and listen for the events
     */
    void update(sf::Vector2f pos, int & state);

    /**
     * \brief Draws components of the game in the window
     *
     * \param target Target where components are drawn
     */
    void render(sf::RenderTarget & target);

    /**
     * \brief Erases field in case to start a new game
     */
    void eraseField();

    /**
     * \brief Sets type of the game
     */
    void setGameType(bool player);

    /**
     * \brief Loads game from vector
     *
     * \param vec Vector that contains saved points and field state
     */
    static void loadGame(std::vector<int> vec);

    /**
     * \brief Returns field state and points
     *
     * \return Vector of ints with points and field status from array
     */
    static std::vector<int> getField();
};


#endif //HEXAGON_HEXAGON_H
