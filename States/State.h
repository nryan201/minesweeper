#ifndef MINESWEEPER_STATE_H
#define MINESWEEPER_STATE_H

#include "../Entity/Player.h"
#include "../RessourceFile/GraphicSettings.h"


class Player;
class GraphicSettings;
class State;
class StateData
{
public:
    StateData() {};
    //Variables
    float gridSize;
    GraphicSettings* gfxSettings;
    sf::RenderWindow* window;
    std::map<std::string, int>* supportedKeys;
    std::stack<State*>* states;
}
;



class State {
private:
Player* player;

    protected:
    StateData* stateData;
    std::stack<State*>* states;
    sf::RenderWindow* window;
    bool quit;
    bool paused;
    float keytime;
    float keytimeMax;
    float gridSize;
    std::map<std::string, int>* supportedKeys;
    std::map <std::string, int> keybinds;
    sf::Vector2i mousePosScreen;
    sf::Vector2i mousePosWindow;
    sf::Vector2f mousePosView;
    sf::Vector2i mousePosGrid;
    sf::View* view;
    //Resources
    std::map<std::string, sf::Texture> textures, textures2;


    //Functions

    virtual void initKeybinds() = 0;
    public:
        State(StateData* state_data);
        virtual ~State();

        //Accessors
        const bool& getWantToQuit() const;
        const bool getKeytime();

        //Function

        void endState();
        void pauseState();
        void unpauseState();
        virtual void updateKeytime(const float& dt);
        virtual void updateInput(const float& dt)=0;
        virtual void updateMousePositions(sf::View* view = nullptr);
        virtual void update(const float& dt) = 0;
        virtual void render(sf::RenderTarget* target = nullptr) = 0;




};

#endif //MINESWEEPER_STATE_H
