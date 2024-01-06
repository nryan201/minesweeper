#include "../pch.h"

#include "AnimationComponent.h"

AnimationComponent::AnimationComponent(sf::Sprite& sprite, sf::Texture& texture_sheet)
        :sprite(sprite), textureSheet(texture_sheet), lastAnimation(NULL), priorityAnimation(NULL)
{

}

AnimationComponent::~AnimationComponent()
{
    for (auto &i : this->animations)
    {
        delete i.second;
    }
}

//Accessors
const bool & AnimationComponent::isDone(const std::string key)
{
    return this->animations[key]->isDone();
}

//Functions
void AnimationComponent::addAnimation(const std::string key,
                                      float animationTimer,
                                      int start_frames_x, int start_frames_y, int frames_x,int frames_y,int width,int height)

{
    this->animations[key] = new Animation(this->sprite,this->textureSheet,animationTimer,start_frames_x,start_frames_y,frames_x,frames_y,width,height);

}

const bool& AnimationComponent::play(const std::string key, const float & dt, const bool priority)
{
    if (this->priorityAnimation) //If there is a priority animation
    {
        if (this->priorityAnimation == this->animations[key])
        {
            if (this->lastAnimation != this->animations[key])
            {
                if (this->lastAnimation == NULL)
                    this->lastAnimation = this->animations[key];
                else
                {
                    this->lastAnimation->reset();
                    this->lastAnimation = this->animations[key];
                }
            }

            //If the priority animation is done, remove it
            if (this->animations[key]->play(dt))
            {
                this->priorityAnimation = NULL;
            }
        }
    }
    else //Play animation of no other priority animation is set
    {
        //If this is a priority animation, set it.
        if (priority)
        {
            this->priorityAnimation = this->animations[key];
        }

        if (this->lastAnimation != this->animations[key])
        {
            if (this->lastAnimation == NULL)
                this->lastAnimation = this->animations[key];
            else
            {
                this->lastAnimation->reset();
                this->lastAnimation = this->animations[key];
            }
        }

        this->animations[key]->play(dt);
    }

    return this->animations[key]->isDone();
}

const bool& AnimationComponent::play(const std::string key, const float & dt, const float& modifier, const float& modifier_max, const bool priority)
{
    if (this->priorityAnimation) //If there is a priority animation
    {
        if (this->priorityAnimation == this->animations[key])
        {
            if (this->lastAnimation != this->animations[key])
            {
                if (this->lastAnimation == NULL)
                    this->lastAnimation = this->animations[key];
                else
                {
                    this->lastAnimation->reset();
                    this->lastAnimation = this->animations[key];
                }
            }

            //If the priority animation is done, remove it
            if (this->animations[key]->play(dt, abs(modifier / modifier_max)))
            {
                this->priorityAnimation = NULL;
            }
        }
    }
    else //Play animation of no other priority animation is set
    {
        //If this is a priority animation, set it.
        if (priority)
        {
            this->priorityAnimation = this->animations[key];
        }

        if (this->lastAnimation != this->animations[key])
        {
            if (this->lastAnimation == NULL)
                this->lastAnimation = this->animations[key];
            else
            {
                this->lastAnimation->reset();
                this->lastAnimation = this->animations[key];
            }
        }

        this->animations[key]->play(dt, abs(modifier / modifier_max));
    }

    return this->animations[key]->isDone();
}

