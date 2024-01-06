#ifndef MINESWEEPER_PAUSEMENU_H
#define MINESWEEPER_PAUSEMENU_H

#include "C:\Users\nedye\CLionProjects\Minesweeper\RessourceFile\Gui.h"

class PauseMenu {
    private:
    sf::Font& font;
    sf::Text menuText;
    sf::RectangleShape background;
    sf::RectangleShape container;
    std::map<std::string,gui::Button*> buttons;

    public:
        PauseMenu(sf::RenderWindow& window,sf::Font& font);
        virtual ~PauseMenu();

        std::map<std::string,gui::Button*> &getButtons();

        void addButton(const std::string key,float y,const std::string text);
        const bool isButtonPressed(const std::string key);

        void update(const sf::Vector2f& mousePos);
        void render(sf::RenderTarget& target);

};


#endif //MINESWEEPER_PAUSEMENU_H
