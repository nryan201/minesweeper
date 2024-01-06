#include "../pch.h"
#include "MouvementComponent.h"

MouvementComponent::MouvementComponent(sf::Sprite& sprite,
                                       float maxVelocity,float acceleration,float deceleration)
: sprite(sprite),maxVelocity(maxVelocity),acceleration(acceleration),deceleration(deceleration) {
    this->maxVelocity = maxVelocity;
    lastVelocity = sf::Vector2f(0.f, 0.f);
}
MouvementComponent::~MouvementComponent() {


}
// This will now correctly return a const reference to the velocity
const sf::Vector2f& MouvementComponent::getVelocity() const {
    return this->velocity;
}


//functions

void MouvementComponent::move(const float dir_x, const float dir_y, const float &dt) {
    // Acceleration
    this->velocity.x += this->acceleration * dir_x * dt;
    this->velocity.y += this->acceleration * dir_y* dt;

    // Update lastVelocity only if there is a change in direction
    if (dir_x != 0.f || dir_y != 0.f) {
        lastVelocity.x = dir_x;
        lastVelocity.y = dir_y;
    }
}

void MouvementComponent::update(const float &dt) {
    //Decelerates the sprite and controls the maximum velocity
    if (this->velocity.x > 0.f)
    {
        //Max velocity check negative
        if (this->velocity.x > this->maxVelocity)
            this->velocity.x = this->maxVelocity;
        //Deceleration x positive
        this->velocity.x -= deceleration*dt;
        if (this->velocity.x < 0.f)
            this->velocity.x = 0.f;

        //Deceleration y positive
    }
    if (this->velocity.x < 0.f)
    {
        //Max velocity check positive
        if (this->velocity.x < -this->maxVelocity)
            this->velocity.x = -this->maxVelocity;
        this->velocity.x += deceleration* dt;
        if (this->velocity.x > 0.f)
            this->velocity.x = 0.f;
    }
    if (this->velocity.y > 0.f)
    {
        //Max velocity check negative
        if (this->velocity.y > this->maxVelocity)
            this->velocity.y = this->maxVelocity;
        //Deceleration x positive
        this->velocity.y -= deceleration* dt;
        if (this->velocity.y < 0.f)
            this->velocity.y = 0.f;

        //Deceleration y positive
    }
    if (this->velocity.y < 0.f)
    {
        //Max velocity check positive
        if (this->velocity.y < -this->maxVelocity)
            this->velocity.y = -this->maxVelocity;
        this->velocity.y += deceleration* dt;
        if (this->velocity.y > 0.f)
            this->velocity.y = 0.f;
    }




    //Final move
    this->sprite.move(this->velocity * dt);

    if (this->velocity.x == 0.f && this->velocity.y == 0.f) {
        lastVelocity.x = 0.f;
        lastVelocity.y = 0.f;
    }

}

const bool MouvementComponent::Idle() const {
    if (this->velocity.x == 0.f && this->velocity.y == 0.f)
        return true;

    return false;
}


// Mouvement SPRITE
const bool MouvementComponent::moving() const {
    if (this->velocity.x != 0.f || this->velocity.y != 0.f)
        return true;

    return false;
}

const bool MouvementComponent::movingLeft() const {
    if (this->velocity.x < 0.f)
        return true;
    return false;
}

const bool MouvementComponent::movingRight() const {
    if (this->velocity.x > 0.f)
        return true;
    return false;
}

const bool MouvementComponent::movingUp() const {
    if (this->velocity.y < 0.f)
        return true;
    return false;
}

const bool MouvementComponent::movingDown() const {
    if (this->velocity.y > 0.f)
        return true;
    return false;
}
const bool MouvementComponent::idleLeft() const {
    return this->Idle() && lastVelocity.x < 0.f;
}
const bool MouvementComponent::idleFront() const {
    // Check if the sprite is idle and the last vertical movement was downward (indicating a front-facing direction)
    return this->Idle() && lastVelocity.y > 0.f;
}

const bool MouvementComponent::getState(const unsigned short state) const {
    switch (state) {
        case IDLE:
            return this->idleFront();
            break;
        case IDLE_LEFT:
            return this->idleLeft();
        case MOVING:
            return this->moving();
            break;
        case MOVING_LEFT:
            return this->movingLeft();
            break;
        case MOVING_RIGHT:
            return this->movingRight();
            break;
        case MOVING_UP:
            return this->movingUp();
            break;
        case MOVING_DOWN:
            return this->movingDown();
            break;
    }
}

const float &MouvementComponent::getMaxVelocity() const {
    return this->maxVelocity;
}
void MouvementComponent::stopVelocity()
{
    /* Resets the velocity to 0.*/

    this->velocity.x = 0.f;
    this->velocity.y = 0.f;
}

void MouvementComponent::stopVelocityX()
{
    /* Resets the velocity x to 0.*/

    this->velocity.x = 0.f;
}

void MouvementComponent::stopVelocityY()
{
    /* Resets the velocity y to 0.*/

    this->velocity.y = 0.f;
}

