#ifndef MINESWEEPER_ENTITY_H
#define MINESWEEPER_ENTITY_H
#include "../Component/HitboxComponent.h"
#include "../Component/MouvementComponent.h"
#include "../Component/AnimationComponent.h"

class Entity {
private:
        void initVariables();

protected:
    sf::Sprite sprite;
    HitboxComponent* hitboxComponent{};
     AnimationComponent* animationComponent{};
     AnimationComponent* animationComponent2{};
    MouvementComponent* mouvementComponent{};
public:
    Entity();
    virtual ~Entity();

    //Components functions
    void createMouvementComponent(const float maxVelocity,const float acceleration,const float deceleration);
    void createHitboxComponent(sf::Sprite& Sprite, float offset_x, float offset_y, float width, float height);
    void setTexture(sf::Texture& texture);
    void createAnimationComponent(sf::Texture& texture_sheet);


    //Accessors
    virtual const sf::Vector2f& getPosition() const;
    virtual const sf::Vector2i getGridPosition(const int gridSizeI) const;

    virtual const sf::FloatRect getGlobalBounds() const;
    const sf::FloatRect getNextPositionBounds(const float& dt) const;




    //Modifiers
    virtual void setPosition(const float x, const float y);

    //Functions
    virtual void stopVelocity();
    virtual void stopVelocityX();
    virtual void stopVelocityY();

    virtual void move(const float dir_x, const float dir_y,const float& dt);

    virtual void update(const float& dt) = 0 ;
    virtual void render(sf::RenderTarget& target) = 0;

};


#endif //MINESWEEPER_ENTITY_H
