#include "../pch.h"
#include "SettingState.h"

//Initializer functions
void SettingState::initKeybinds() {
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
void SettingState::initFonts() {
    if (!this->font.loadFromFile("C:\\Users\\nedye\\CLionProjects\\Minesweeper\\Font\\Dosis-Light.ttf"))
    {
        throw("ERROR::MAINMENUSTATE::COULD NOT LOAD FONT");
    }

}

void SettingState::initGui() {

    this->buttons["BACK"] = new gui::Button(1000, 690, 200, 50,
                                               &this->font, "BACK", 50,
                                               sf::Color(70,70,70,200),
                                               sf::Color(250,250,250,250),
                                               sf::Color(20,20,20,50),
                                               sf::Color(70,70,70,0),
                                               sf::Color(150,150,150,0),
                                               sf::Color(20,20,20,0));

    this->buttons["APPLY"] = new gui::Button(440, 690, 200, 50,
                                            &this->font, "APPLY", 50,
                                            sf::Color(70,70,70,200),
                                            sf::Color(250,250,250,250),
                                            sf::Color(20,20,20,50),
                                            sf::Color(70,70,70,0),
                                            sf::Color(150,150,150,0),
                                            sf::Color(20,20,20,0));


    std::vector<std::string> modes_str;
    for (auto &i : this->modes)
    {
        modes_str.push_back(std::to_string(i.width)+"x" + std::to_string(i.height));
    }

    this->dropDownLists["RESOLUTION"] = new gui::DropDownList(440, 380, 200, 50, font, modes_str.data(),modes_str.size());

}
void SettingState::initBackground() {
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
void SettingState::initVariables()
{
    this->modes = sf::VideoMode::getFullscreenModes();



}

void SettingState::initText() {
    this->optionsText.setFont(this->font);
    this->optionsText.setPosition(sf::Vector2f(100,400));
    this->optionsText.setCharacterSize(30);
    this->optionsText.setFillColor(sf::Color::White);
    this->optionsText.setString(
            "Resolution \n\nFullscreen \n\nVsync \n\nAntialiasing \n\n"
    );

}

SettingState::SettingState(StateData* state_data)
 : State(state_data) {
    this->initVariables();
    this->initBackground();
    this->initFonts();
    this->initKeybinds();
    this->initGui();
    this->initText();

}

SettingState::~SettingState() {
    auto it = this->buttons.begin();
    for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
    {
        delete it->second;
    }
    auto it2 = this->dropDownLists.begin();
    for (it2 = this->dropDownLists.begin(); it2 != this->dropDownLists.end(); ++it2)
    {
        delete it2->second;
    }
}
//Accessors


//Functions
void SettingState::updateInput(const float &dt) {


}

void SettingState::update(const float& dt) {
    this->updateMousePositions();
    this->updateInput(dt);
    this->updateGui(dt);

//New Game

    //SETTINGS
//    if (this->buttons["SETTINGS"]->isPressed())
//    {
//        this->states->push(new SettingsState(this->window,this->supportedKeys,this->states)) ;
//    }
}

void SettingState::render(sf::RenderTarget* target)
{
    if (!target)
        target = this->window;

    target->draw(this->background);

    this->renderGui(*target);

    target->draw(this->optionsText);

    sf::Text mouseText;
    mouseText.setPosition(this->mousePosView.x, this->mousePosView.y - 50);
    mouseText.setFont(this->font);
    mouseText.setCharacterSize(12);
    std::stringstream ss;
    ss << this->mousePosView.x << " " << this->mousePosView.y;
    mouseText.setString(ss.str());
    target->draw(mouseText);
}

void SettingState::updateGui(const float& dt) {
    //Updates all the buttons in the state and handles their functionality
    for (auto &it : this->buttons)
    {
        it.second->update(this->mousePosView);
    }

    for (auto &it : this->buttons)
    {
        it.second->update(this->mousePosView);
    }

    //CLOSE
    if (this->buttons["BACK"]->isPressed())
    {
        this->endState();
    }
    if (this->buttons["APPLY"]->isPressed())
    {
        this->stateData->gfxSettings->resolution = this->modes[this->dropDownLists["RESOLUTION"]->getActiveElementId()];
        this->window->create(this->stateData->gfxSettings->resolution, this->stateData->gfxSettings->title, sf::Style::Default);


    }
    //DROPDOWNLIST
    for (auto &it : this->dropDownLists)
    {
        it.second->update(this->mousePosView,dt);
    }

    //dropdownlist functionality
}

void SettingState::renderGui(sf::RenderTarget& target) {
    for (auto &it : this->buttons)
    {
        it.second->render(target);
    }
    for (auto &it : this->dropDownLists)
    {
        it.second->render(target);
    }
}

