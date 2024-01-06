
#ifndef MINESWEEPER_EDITORSTATE_H
#define MINESWEEPER_EDITORSTATE_H

#include "State.h"
#include "../RessourceFile/Gui.h"
#include "../GUI/PauseMenu.h"
#include "../map/TileMap.h"


class State;
class PauseMenu;
class TileMap;

class EditorState :
        public State {
private:
    //Variables

    sf::Text cursorText;
    sf::Font font;
    PauseMenu* pmenu;
    std::map<std::string, gui::Button*> buttons;


    TileMap* tilemap;

    sf::IntRect textureRect;
    sf::RectangleShape selectorRect;

    gui::TextureSelector* textureSelector;

    bool textureSelectorVisible;
    bool collision;
    short type;
    sf::View view;
    float cameraSpeed;

    //Functions
    void initVieuw();
    void initPauseMenu();
    void initVariables();
    void initBackground();
    void initFonts();
    void initText();
    void initKeybinds();
    void initButtons();
    void initGui();
    void initTileMap();
public :
    EditorState(StateData* state_data);
    virtual ~EditorState();

    //Functions
    void updateButtons();
    void updateEditorInput(const float& dt);
    void updateInput(const float& dt);
    void update(const float& dt);
    void updatePauseButtons();
    void updateGui(const float& dt);
    void render(sf::RenderTarget* target = nullptr);
    void renderGui(sf::RenderTarget& target);
    void renderButtons(sf::RenderTarget& target);



};

#endif //MINESWEEPER_EDITORSTATE_H
