#include "../pch.h"
#include "Gamestate.h"
#include "MainMenuState.h"
#include "../GUI/PauseMenu.h"
 //Initializer functions
void MainMenuState::initKeybinds() {
    std::ifstream ifs("C:\\Users\\nedye\\CLionProjects\\Minesweeper\\Config\\mainmenustate_keybinds.ini");
    if (ifs.is_open()) {
        std::string key = "";
        std::string key2 = "";
        while (ifs >> key >> key2) {
            this->keybinds[key] = this->supportedKeys->at(key2);
        }
    }
    ifs.close();

}
void MainMenuState::initFonts() {
    if (!this->font.loadFromFile("C:\\Users\\nedye\\CLionProjects\\Minesweeper\\Font\\Dosis-Light.ttf"))
    {
        throw("ERROR::MAINMENUSTATE::COULD NOT LOAD FONT");
    }

}

void MainMenuState::initButtons() {
    this->buttons["GAME_STATE"] = new gui::Button(100.f, 380.f, 200.f, 50.f,
                                               &this->font, "New Game", 50,
                                               sf::Color(70,70,70,200),
                                               sf::Color(250,250,250,250),
                                               sf::Color(20,20,20,50),
                                               sf::Color(70,70,70,0),
                                               sf::Color(150,150,150,0),
                                               sf::Color(20,20,20,0));

    this->buttons["SETTINGS_STATE"] = new gui::Button(100, 480, 200, 50,
                                                   &this->font, "Settings", 50,
                                                   sf::Color(70,70,70,200),
                                                   sf::Color(250,250,250,250),
                                                   sf::Color(20,20,20,50),
                                                   sf::Color(70,70,70,0),
                                                   sf::Color(150,150,150,0),
                                                   sf::Color(20,20,20,0));

    this->buttons["EXIT_STATE"] = new gui::Button(100, 580, 200, 50,
                                               &this->font, "Close", 50,
                                               sf::Color(70,70,70,200),
                                               sf::Color(250,250,250,250),
                                               sf::Color(20,20,20,50),
                                               sf::Color(70,70,70,0),
                                               sf::Color(150,150,150,0),
                                               sf::Color(20,20,20,0));

    this->buttons["EDITOR_STATE"] = new gui::Button(100, 700, 200, 50,
                                                 &this->font, "Editor", 50,
                                                 sf::Color(70,70,70,200),
                                                 sf::Color(250,250,250,250),
                                                 sf::Color(20,20,20,50),
                                                 sf::Color(70,70,70,0),
                                                 sf::Color(150,150,150,0),
                                                 sf::Color(20,20,20,0));
}
void MainMenuState::initBackground() {
    this->background.setSize(
            sf::Vector2f
            (static_cast<float>(this->window->getSize().x),static_cast<float>(this->window->getSize().y)));

    if(!this->bgTexture.loadFromFile("C:\\Users\\nedye\\CLionProjects\\Minesweeper\\Ressources\\Image\\Backgrounds\\TEST.png")
    )
    {
        throw "ERROR::MAINMENUSTATE::FAILED_TO_LOAD_BACKGROUND_TEXTURE";
    }
    this->background.setTexture(&this->bgTexture);

}
void MainMenuState::initVariables() {

}
MainMenuState::MainMenuState(StateData* state_data)
    : State(state_data) {
    this->initVariables();
    this->initBackground();
    this->initFonts();
    this->initKeybinds();\
    this->initButtons();



}

MainMenuState::~MainMenuState() {
    auto it = this->buttons.begin();
    for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
    {
        delete it->second;
    }

}

//Functions*
void MainMenuState::updateInput(const float &dt) {


}

void MainMenuState::update(const float& dt) {
    this->updateMousePositions();
    this->updateInput(dt);
    this->updateButtons();

//New Game

    //SETTINGS
//    if (this->buttons["SETTINGS"]->isPressed())
//    {
//        this->states->push(new SettingsState(this->window,this->supportedKeys,this->states)) ;
//    }
}

void MainMenuState::render(sf::RenderTarget *target) {
    if (!target)
        target = this->window;
    target->draw(this->background);

    this->renderButtons(*target);
}


void MainMenuState::updateButtons() {
    //Updates all the buttons in the state and handles their functionality
    for (auto &it : this->buttons)
    {
        it.second->update(this->mousePosView);
    }
    if (this->buttons["GAME_STATE"]->isPressed())
    {
        this->states->push(new GameState(this->stateData));
    }
    if (this->buttons["SETTINGS_STATE"]->isPressed())
    {
        this->states->push(new SettingState(this->stateData));
    }
    //CLOSE
    if (this->buttons["EXIT_STATE"]->isPressed())
    {
        this->endState();
    }
    if (this->buttons["EDITOR_STATE"]->isPressed())
    {
        this->states->push(new EditorState(this->stateData)) ;
    }
}

void MainMenuState::renderButtons(sf::RenderTarget& target) {
    for (auto &it : this->buttons)
    {
        it.second->render(target);
    }
}
