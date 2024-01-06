#ifndef MINESWEEPER_GAMESTATE_H
#define MINESWEEPER_GAMESTATE_H
#include "State.h"
#include "../GUI/PauseMenu.h"
#include "../map/TileMap.h"

class PauseMenu;
class TileMap;
class Player;
class View;
class RenderTexture;
class Sprite;
class Font;

class GameState :
        public State {
private:
        //Variables
        sf::View view;
        sf::Vector2i viewGridPosition;
        sf::RenderTexture renderTexture;
        sf::Sprite renderSprite;
        std::map<std::string, gui::Button*> buttons;

        Player* player;
        PauseMenu* pmenu;
        sf::Font font;
        TileMap* tileMap;


        //Functions
        void initDeferredRender();
        void initButtons();
        void initVieuw();
        void initFonts();
        void initKeybinds();
        void initTextures();
        void initPlayers();
        void initPauseMenu();
        void initTileMap();

public :
    GameState(StateData* state_data);
    virtual ~GameState();

    //Functions
    void updateTileMap(const float& dt);
    void updateButtons();
    void updateVieuw(const float& dt);
    void updatePauseInput(const float dt);
    void updateInput(const float& dt);
    void updatePauseButtons();
    void update(const float& dt);
    void render(sf::RenderTarget* target = nullptr);


};


#endif //MINESWEEPER_GAMESTATE_H
