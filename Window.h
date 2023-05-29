

#ifndef HEXAGON_WINDOW_H
#define HEXAGON_WINDOW_H

#include "Menu.cpp"
#include "GameType.cpp"
#include "Saver.cpp"

class Window {
private:
    ///Variables
    int state;                  ///Current game state
    int prevState;              ///Previous game state
    bool player;                ///Flag indicating who is playing

    ///GUI components
    sf::RenderWindow* window;   ///Pointer to the window
    sf::VideoMode vm;           ///Video mode for the window
    sf::Event ev;               ///Event object for tracking events
    sf::Vector2f mousePos;      ///Vector of mouse position relative to the window
    sf::Texture texture;        ///Background texture
    sf::RectangleShape bg;      ///Background shape

    ///Objects of helping classes
    Menu menu;                  ///Menu object for the game menu
    Hexagon hexagon;            ///Hexagon object for the game
    GameType gameType;          ///GameType object for choosing game type
    Saver saver;                ///Saver object for saving and loading the game
    ScoreBoard scores;          ///ScoreBoard object for saving and listing scores

    ///Private functions
    /**
     * \brief Initializes default values of variables
     */
    void initGUI();

    /**
     * \brief Initializes GUI components
     */
    void initVariables();

    /**
     * \brief Listens if window was closed
     */
    void eventListener();

    /**
     * \brief Updates mouse position
     */
    void updateMousePos();

public:
    ///Constructor and destructor

    /**
     * \brief Default constructor
     */
    Window();

    /**
     * \brief Destructor
     */
    ~Window();

    ///Public functions
    /**
     * \brief Checks if window is opened
     *
     * \return True if window is opened and false if opposite
     */
    bool working() const;

    /**
     * \brief Updates window
     *
     * Updates window based on current state, checks if state changed and in some situation calls necessary methods
     */
    void update();

    /**
     * \brief Renders objects
     *
     * Renders components based on current state
     */
    void render();
};


#endif //HEXAGON_WINDOW_H
