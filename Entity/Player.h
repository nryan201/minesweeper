
#ifndef MINESWEEPER_PLAYER_H
#define MINESWEEPER_PLAYER_H

#include "Entity.h"

class Player :

    public Entity
    {
private:
        //variables


        //init functions
        void initVariables();
        void initComponents();

    public:
    Player(float x, float y, sf::Texture& texture_sheet);
    virtual ~Player();

    //Functions
    void updateAnimation(const float& dt);
    void update(const float& dt);

    void render(sf::RenderTarget& target);

};


#endif //MINESWEEPER_PLAYER_H
