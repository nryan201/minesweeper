#include "../pch.h"
#include "EditorState.h"


void EditorState::initVariables() {
    this->cameraSpeed = 1000.f;
    this->textureRect = sf::IntRect(0, 0, static_cast<int>(this->stateData->gridSize), static_cast<int>(this->stateData->gridSize));
    this->collision = false;
    this->type  = TileTypes::DEFAULT;
}
void EditorState::initKeybinds() {
    std::ifstream ifs("C:\\Users\\nedye\\CLionProjects\\Minesweeper\\Config\\editorstate_keybinds.ini");
    if (ifs.is_open()) {
        std::string key = "";
        std::string key2 = "";
        while (ifs >> key >> key2) {
            this->keybinds[key] = this->supportedKeys->at(key2);
        }
    }
    ifs.close();

}
void EditorState::initFonts() {
    if (!this->font.loadFromFile("C:\\Users\\nedye\\CLionProjects\\Minesweeper\\Font\\Dosis-Light.ttf"))
    {
        throw("ERROR::EDITORSTATE::COULD NOT LOAD FONT");
    }

}
void EditorState::initText() {
    this->cursorText.setFont(this->font);
    this->cursorText.setFillColor(sf::Color::White);
    this->cursorText.setCharacterSize(12);
    this->cursorText.setPosition(this->mousePosView.x, this->mousePosView.y - 50);


}

void EditorState::initPauseMenu() {
    this->pmenu = new PauseMenu(*this->window,this->font);
    this->pmenu->addButton("SAVE",550.f,"Save");
    this->pmenu->addButton("LOAD",700.f,"Load");
    this->pmenu->addButton("QUIT",850.f,"Quit");
}
void EditorState::initButtons() {

}
void EditorState::initBackground() {

}

void EditorState::initTileMap() {
    this->tilemap = new TileMap(this->stateData->gridSize, 10, 10,"C:\\Users\\nedye\\CLionProjects\\Minesweeper\\Ressources\\Image\\Tile\\tilesheet2.png");

}
void EditorState::initGui()
{
    this->selectorRect.setSize(sf::Vector2f(this->stateData->gridSize, this->stateData->gridSize));
    this->selectorRect.setFillColor(sf::Color(255, 255, 255, 150));
    this->selectorRect.setOutlineThickness(1.f);
    this->selectorRect.setOutlineColor(sf::Color::Green);

    this->selectorRect.setTexture(this->tilemap->getTileSheet());
    this->selectorRect.setTextureRect(this->textureRect);

    this->textureSelector = new gui::TextureSelector(200.f, 200.f, 500.f, 200.f,
                                                     this->stateData->gridSize, this->tilemap->getTileSheet(),
                                                     this->font, "TS");




}
void EditorState::initVieuw()
 {
        this->view.setSize(
                sf::Vector2f(
                        static_cast<float>(this->stateData->gfxSettings->resolution.width),
                        static_cast<float>(this->stateData->gfxSettings->resolution.height)
                )
        );

        this->view.setCenter(
                static_cast<float>(this->stateData->gfxSettings->resolution.width) / 2.f,
                static_cast<float>(this->stateData->gfxSettings->resolution.height) / 2.f
        );

}



EditorState::EditorState(StateData* state_data)
        : State(state_data) {
    this->initVariables();
    this->initBackground();
    this->initVieuw();
    this->initFonts();
    this->initText();
    this->initKeybinds();
    this->initPauseMenu();
    this->initButtons();
    this->initTileMap();
    this->initGui();




}

EditorState::~EditorState() {
    auto it = this->buttons.begin();
    for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
    {
        delete it->second;
    }
    delete this->pmenu;
    delete this ->tilemap;
    delete this->textureSelector;

}
void EditorState::updateGui(const float &dt)
{
    this->textureSelector->update(this->mousePosView, dt);

    if(!this->textureSelector->getActive())
    {
        this->selectorRect.setTextureRect(this->textureRect);
        this->selectorRect.setPosition(this->mousePosGrid.x * this->stateData->gridSize, this->mousePosGrid.y * this->stateData->gridSize);

    }
    this->cursorText.setPosition(this->mousePosView.x, this->mousePosView.y - 50);
    std::stringstream ss;
    ss << this->mousePosView.x << " " << this->mousePosView.y
    << "\n"<< this->mousePosGrid.x << " " << this->mousePosGrid.y<< "\n"
    <<this->textureRect.left << " "<<this->textureRect.top <<"\n"<<
    "Collision : "<<this->collision <<"\n"
    << "Type : " << this->type;
    this->cursorText.setString(ss.str());


}

//Functions*
 void EditorState::updatePauseButtons() {
     if(this->pmenu->isButtonPressed("QUIT")){
         this->endState();
     }
        if(this->pmenu->isButtonPressed("SAVE")){
            this->tilemap->saveToFile("C:\\Users\\nedye\\CLionProjects\\Minesweeper\\Ressources\\test2.mp");
        }
        if(this->pmenu->isButtonPressed("LOAD")){
            this->tilemap->loadFromFile("C:\\Users\\nedye\\CLionProjects\\Minesweeper\\Ressources\\test2.mp");
        }
}
void EditorState::updateInput(const float &dt) {
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("Close"))) && this->getKeytime()) {
        if (!this->paused)
            this->pauseState();
        else
            this->unpauseState();
    }

}

void EditorState::update(const float& dt) {
    this->updateMousePositions(&this->view);
    this->updateKeytime(dt);
    this->updateInput(dt);
    if(!this->paused) {

        this->updateButtons();
        this->updateGui(dt);
        this->updateEditorInput(dt);
    }
    else{
        this->pmenu->update(this->mousePosView);
        this->updatePauseButtons();
    }

}


void EditorState::updateEditorInput(const float &dt) {
    //View controls
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_CAMERA_UP")))) {
        this->view.move(0.f, -this->cameraSpeed * dt);
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_CAMERA_DOWN")))) {
        this->view.move(0.f, this->cameraSpeed * dt);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_CAMERA_LEFT")))) {
        this->view.move(-this->cameraSpeed * dt, 0.f);
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_CAMERA_RIGHT")))) {
        this->view.move(this->cameraSpeed * dt, 0.f);
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->getKeytime()) {

        if (!this->textureSelector->getActive()) {
            this->tilemap->addTile(this->mousePosGrid.x, this->mousePosGrid.y, 0, this->textureRect, this->collision,
                                   this->type);
        } else {
            this->textureRect = this->textureSelector->getTextureRect();
        }
    } else if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && this->getKeytime()) {
        if (!this->textureSelector->getActive())
            this->tilemap->removeTile(this->mousePosGrid.x, this->mousePosGrid.y, 0);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("TOGGLE_COLLISION"))) && this->getKeytime()) {
        if (this->collision)
            this->collision = false;
        else
            this->collision = true;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("INCREASE_TYPE"))) &&
               this->getKeytime()) {
        ++this->type;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("DECREASE_TYPE"))) &&
               this->getKeytime()) {
        if (this->type > 0)
            --this->type;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("Save")))) {
        this->tilemap->saveToFile("C:\\Users\\nedye\\CLionProjects\\Minesweeper\\Ressources\\test2.mp");
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("Load")))) {
        this->tilemap->loadFromFile("C:\\Users\\nedye\\CLionProjects\\Minesweeper\\Ressources\\test2.mp");
    }
}
void EditorState::updateButtons() {
    //Updates all the buttons in the state and handles their functionality
    for (auto &it : this->buttons)
    {
        it.second->update(this->mousePosView);
    }
}
void EditorState::render(sf::RenderTarget* target) {
    if (!target)
        target = this->window;

    target->setView(this->view);
    this->tilemap->render(*target,0);
    this->renderButtons(*target);
    this->renderGui(*target);

    if (this->paused) {
        target->setView(this->window->getDefaultView());
        this->pmenu->render(*target);
    }


}
void EditorState::renderButtons(sf::RenderTarget& target) {
    for (auto &it : this->buttons)
    {
        it.second->render(target);
    }
}

void EditorState::renderGui(sf::RenderTarget &target)
{
    if(!this->textureSelector->getActive())
    target.draw(this->selectorRect);

    this->textureSelector->render(target);
    target.draw(this->cursorText);


}

