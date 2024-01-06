#ifndef MINESWEEPER_MAINMENUSTATE_H
#define MINESWEEPER_MAINMENUSTATE_H
#include "Gamestate.h"
#include "../RessourceFile/Gui.h"
#include "EditorState.h"
#include "SettingState.h"

class MainMenuState :
        public State {
private:
    //Variables

    sf::RectangleShape background;
    sf::Font font;
    sf::Texture bgTexture;
    std::map<std::string, gui::Button*> buttons;

   //Functions
    void initVariables();
    void initBackground();
    void initFonts();
    void initKeybinds();
    void initButtons();
public :
    MainMenuState(StateData* state_data);
    virtual ~MainMenuState();

    //Functions
    void updateButtons();
    void updateInput(const float& dt);
    void update(const float& dt);
    void render(sf::RenderTarget* target = nullptr);
    void renderButtons(sf::RenderTarget& target);

};



#endif //MINESWEEPER_MAINMENUSTATE_H
