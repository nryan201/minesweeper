#ifndef MINESWEEPER_GAME_H
#define MINESWEEPER_GAME_H

#include "../States/MainMenuState.h"



class Game {
private :

          //Initialization
          void initStateData();
          void initGraphicsSettings();
          void initVariables();
          void initWindow();
          void initStates();
          void initKeys();
          //Variables
          GraphicSettings gfxSettings;
          StateData stateData;
          sf::RenderWindow *window{};
          sf::Event sfEvent{};
          float dt{};
          sf::Clock dtClock{};
          std::stack<State*> states;
          std::map<std::string, int> supportedKeys;
          float gridSize;

          
public:
    //Constructors / Destructors
    Game();
    virtual ~Game();

    //Functions

    void endApplication();
    //Update
    void updateDt();
    void UpdateSFMLEvents();
    void update();

    //Render
    void render();

    //Core
    void run();

};


#endif
