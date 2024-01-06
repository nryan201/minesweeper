#include "../pch.h"
#include "State.h"

State::State(StateData* state_data) {
    this->stateData = state_data;
    this->window = state_data->window;
    this->quit = false;
    this->paused = false;
    this->states =state_data->states;
    this->supportedKeys = state_data->supportedKeys;
    this->keytime = 0.f;
    this->keytimeMax = 10.f;
    this->gridSize = state_data->gridSize;
}

State::~State() {

}

 //ACCESSORS
const bool &State::getWantToQuit() const {
    return this->quit;
}

const bool State::getKeytime() {
    if(this->keytime >= this->keytimeMax)
    {
        this->keytime = 0.f;
        return true;
    }
    return false;
}


//Functions
void State::updateMousePositions(sf::View* view) {
    this->mousePosScreen = sf::Mouse::getPosition();
    this->mousePosWindow = sf::Mouse::getPosition(*this->window);

    if(view)
        this->window->setView(*view);

    this->mousePosView = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));
    this->mousePosGrid =
            sf::Vector2i(
                    static_cast<int>(this->mousePosView.x) / static_cast<int>(this->gridSize),
                    static_cast<int>(this->mousePosView.y) / static_cast<int>(this->gridSize)
            );

    this->window->setView(this->window->getDefaultView());
}

void State::endState() {
    this->quit = true;

}
void State::pauseState()
{
    this->paused = true;
}

void State::unpauseState()
{
    this->paused = false;
}

void State::updateKeytime(const float &dt) {
    if(this->keytime < this->keytimeMax)
        this->keytime +=50.f*dt;

}


