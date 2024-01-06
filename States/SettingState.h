#include "../pch.h"
#ifndef MINESWEEPER_SETTINGSTATE_H
#define MINESWEEPER_SETTINGSTATE_H

#include "State.h"
#include "../RessourceFile/Gui.h"

class SettingState :
        public State {

private:
    sf::RectangleShape background;
    sf::Font font;
    sf::Texture bgTexture;
    std::map<std::string, gui::Button*> buttons;
    std::map<std::string, gui::DropDownList*> dropDownLists;

    sf::Text optionsText;

    std::vector<sf::VideoMode> modes;

    //Functions
    void initVariables();
    void initBackground();
    void initFonts();
    void initKeybinds();
    void initGui();
    void initText();


public:
    SettingState(StateData* state_data);
    virtual ~SettingState();

    //Accessor

    //Function
    void updateGui(const float& dt);
    void updateInput(const float& dt);
    void update(const float& dt);
    void render(sf::RenderTarget* target = nullptr);
    void renderGui(sf::RenderTarget& target);


};


#endif //MINESWEEPER_SETTINGSTATE_H
