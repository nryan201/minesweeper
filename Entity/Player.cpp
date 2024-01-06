#include "../pch.h"
#include "Player.h"

//Initializer functions

void Player::initVariables() {

}

void Player::initComponents() {
this->createMouvementComponent(300.f,15.f,5.f);

}

//Constructors / Destructors
Player::Player(float x, float y, sf::Texture& texture_sheet) :
Entity()
{
    this->initVariables();
    this->setPosition(x,y);
    this->createHitboxComponent(this->sprite,0.f,0.f,48.f,48.f);
    this->createMouvementComponent(350.f,1500.f,500.f);
    this->createAnimationComponent(texture_sheet);


    this->animationComponent->addAnimation("WALK_FRONT",10.f,0,0,0,3,16,16);

    this->animationComponent->addAnimation("WALK_LEFT",10.f,2,0,0,3,16,16);

    this->animationComponent->addAnimation("WALK_RIGHT",10.f,3,0,0,3,16,16);

    this->animationComponent->addAnimation("WALK_BACK",10.f,1,0,0,3,16,16);

    this->animationComponent->addAnimation("IDLE_FRONT",1.f,0,0,0,0,16,16);

    this->animationComponent->addAnimation("IDLE_LEFT",1.f,2,0,0,0,16,16);

    this->animationComponent->addAnimation("IDLE_RIGHT",1.f,3,0,0,0,16,16);

    this->animationComponent->addAnimation("IDLE_BACK",1.f,1,0,0,0,16,16);



}

Player::~Player() {

}

void Player::updateAnimation(const float &dt)
{
    if (this->mouvementComponent->getState(IDLE))
    {
        this->animationComponent->play("IDLE", dt);
    }
    else if (this->mouvementComponent->getState(MOVING_LEFT))
    {
        this->animationComponent->play("WALK_LEFT", dt, this->mouvementComponent->getVelocity().x, this->mouvementComponent->getMaxVelocity());
    }
    else if (this->mouvementComponent->getState(MOVING_RIGHT))
    {
        this->animationComponent->play("WALK_RIGHT", dt, this->mouvementComponent->getVelocity().x, this->mouvementComponent->getMaxVelocity());
    }
    else if (this->mouvementComponent->getState(MOVING_DOWN))
    {
        this->animationComponent->play("WALK_FRONT", dt, this->mouvementComponent->getVelocity().y, this->mouvementComponent->getMaxVelocity());
    }
    else if (this->mouvementComponent->getState(MOVING_UP))
    {
        this->animationComponent->play("WALK_BACK", dt, this->mouvementComponent->getVelocity().y, this->mouvementComponent->getMaxVelocity());
    }

}
void Player::update(const float &dt)
{
        this->mouvementComponent->update(dt);

        this->updateAnimation(dt);

        this->hitboxComponent->update();
}

void Player::render(sf::RenderTarget &target) {
    target.draw(this->sprite);

    if(this->hitboxComponent)
    {
        this->hitboxComponent->render(target);
    }

}
