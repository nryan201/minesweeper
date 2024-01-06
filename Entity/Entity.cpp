#include "../pch.h"
#include "Entity.h"
void Entity::initVariables() {
    this->hitboxComponent = nullptr;
    this->mouvementComponent = nullptr;
    this->animationComponent = nullptr;
    this->animationComponent2 = nullptr;
}

Entity::Entity() {
    this->initVariables();
}

Entity::~Entity() {
    delete this->hitboxComponent;
    delete this->mouvementComponent;
    delete this->animationComponent;
    delete this->animationComponent2;

}
//Components functions


void Entity::setTexture(sf::Texture &texture) {
        this->sprite.setTexture(texture);
}
void Entity::createMouvementComponent(const float maxVelocity,const float acceleration,const float deceleration) {
    this->mouvementComponent = new MouvementComponent(this->sprite,maxVelocity,acceleration,deceleration);
}

void Entity::createHitboxComponent(sf::Sprite& Sprite, float offset_x, float offset_y, float width, float height) {
    this->hitboxComponent = new HitboxComponent(sprite,offset_x,offset_y,width,height);

}
void Entity::createAnimationComponent( sf::Texture &texture_sheet)
{
    this->animationComponent = new AnimationComponent(sprite,texture_sheet);
}

const sf::FloatRect Entity::getGlobalBounds() const
{
    if (this->hitboxComponent)
        return this->hitboxComponent->getGlobalBounds();

    return this->sprite.getGlobalBounds();
}


void Entity::setPosition(const float x, const float y) {
    if (this->hitboxComponent)


        this->sprite.setPosition(x,y);


}
void Entity::move(const float dir_x, const float dir_y,const float& dt) {
    if(this->mouvementComponent)
    {
        this->mouvementComponent->move(dir_x,dir_y,dt); //Sets velocity
         //Uses velocity
    }
}

void Entity::stopVelocity()
{
    if (this->mouvementComponent)
        this->mouvementComponent->stopVelocity();

}

void Entity::stopVelocityX()
{
    if (this->mouvementComponent)
        this->mouvementComponent->stopVelocityX();
}

void Entity::stopVelocityY()
{
    if (this->mouvementComponent)
        this->mouvementComponent->stopVelocityY();
}


void Entity::update(const float &dt)
{

}



void Entity::render(sf::RenderTarget &target) {
        target.draw(this->sprite);

        if(this->hitboxComponent)
        {
            this->hitboxComponent->render(target);
        }
}

const sf::Vector2f &Entity::getPosition() const {
    if (this->hitboxComponent)
        return this->hitboxComponent->getPosition();

    return this->sprite.getPosition();
}

const sf::Vector2i Entity::getGridPosition(const int gridSizeI) const
{
    if (this->hitboxComponent)
        return sf::Vector2i(
                static_cast<int>(this->hitboxComponent->getPosition().x) / gridSizeI,
                static_cast<int>(this->hitboxComponent->getPosition().y) / gridSizeI
        );

    return sf::Vector2i(
            static_cast<int>(this->sprite.getPosition().x) / gridSizeI,
            static_cast<int>(this->sprite.getPosition().y) / gridSizeI
    );
}
const sf::FloatRect Entity::getNextPositionBounds(const float& dt) const
{
    if (this->hitboxComponent && this->mouvementComponent)
        return this->hitboxComponent->getNextPosition(this->mouvementComponent->getVelocity() * dt);

    return sf::FloatRect(-1.f, -1.f, -1.f, -1.f);
}










