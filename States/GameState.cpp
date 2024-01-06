#include "../pch.h"
#include "GameState.h"



//Initializer functions


void GameState::initTileMap() {
    this->tileMap = new TileMap(this->stateData->gridSize, 10, 10,R"(C:\Users\nedye\CLionProjects\Minesweeper\Ressources\Image\Tile\tilesheet2.png)");
    this->tileMap->loadFromFile(R"(C:\Users\nedye\CLionProjects\Minesweeper\Ressources\test2.mp)");
}

void GameState::updateVieuw(const float &dt)
{
    this->view.setCenter(std::floor(this->player->getPosition().x),std::floor(this->player->getPosition().y));
}


void GameState::initVieuw()
{
    // Réduction de 50% de la taille de la vue
    this->view.setSize(
            sf::Vector2f(
                    static_cast<float>(this->stateData->gfxSettings->resolution.width) /(3.f/2.f),
                    static_cast<float>(this->stateData->gfxSettings->resolution.height)/(3.f/2.f)
            )
    );

    this->view.setCenter(
            sf::Vector2f(
                    static_cast<float>(this->stateData->gfxSettings->resolution.height) / 2.f,
                    static_cast<float>(this->stateData->gfxSettings->resolution.height) / 2.f
            )
    );
}


void GameState::initDeferredRender()
{
    this->renderTexture.create(
            this->stateData->gfxSettings->resolution.width,
            this->stateData->gfxSettings->resolution.height
    );

    this->renderSprite.setTexture(this->renderTexture.getTexture());
    this->renderSprite.setTextureRect(
            sf::IntRect(
                    0,
                    0,
                    this->stateData->gfxSettings->resolution.width,
                    this->stateData->gfxSettings->resolution.height
            )
    );
}




void GameState::initKeybinds() {
    std::ifstream ifs("C:\\Users\\nedye\\CLionProjects\\Minesweeper\\Config\\gamestates_keybinds.ini");
    if (ifs.is_open()) {
        std::string key = "";
        std::string key2 = "";
        while (ifs >> key >> key2) {
            this->keybinds[key] = this->supportedKeys->at(key2);
        }
    }
    ifs.close();

}
void GameState::initFonts() {
    if (!this->font.loadFromFile("C:\\Users\\nedye\\CLionProjects\\Minesweeper\\Font\\Dosis-Light.ttf"))
    {
        throw("ERROR::MAINMENUSTATE::COULD NOT LOAD FONT");
    }

}
void GameState::initTextures() {
    if (!this->textures["PLAYER_SHEET"].loadFromFile(
            "C:\\Users\\nedye\\CLionProjects\\Minesweeper\\Ressources\\Image\\Sprite\\Player\\Player_sheet2.png")) {
        throw "ERROR::GAME_STATE::COULD_NOT_LOAD_PLAYER_TEXTURE";
    }
}
void GameState::initPauseMenu() {
    this->pmenu = new PauseMenu(*this->window,this->font);
    this->pmenu->addButton("QUIT",850.f,"Quit");

}
void GameState::initButtons() {

}
void GameState::initPlayers()
{
    this->player = new Player(5,5,this->textures["PLAYER_SHEET"]);

}


GameState::GameState(StateData* state_data)
        : State(state_data) {
    this->initDeferredRender();
    this->initKeybinds();
    this->initVieuw();
    this->initTextures();
    this->initPlayers();
    this->initFonts();
    this->initPauseMenu();
    this->initButtons();
    this->initTileMap();

}


GameState::~GameState()
{
    auto it = this->buttons.begin();
    for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
    {
        delete it->second;
    }
        delete this->player;
        delete this->pmenu;
        delete this->tileMap;
}

//Functions*
void GameState::updateTileMap(const float & dt)
{
    this->tileMap->update();
    this->tileMap->updateCollision(this->player, dt);
}


void GameState::updatePauseInput(const float dt) {
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("Close"))) && this->getKeytime()) {
        if (!this->paused)
            this->pauseState();
        else
            this->unpauseState();

    }

}
void GameState::updateInput(const float &dt) {
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("Gauche"))))
    {
        this->player->move(-1.f, 0.f, dt);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("Droite")))){
        this->player->move( 1.f, 0.f, dt);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("Haut")))){
        this->player->move( 0.f, -1.f, dt);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("Bas")))){
        this->player->move(0.f, 1.f, dt);
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MainMenu")))) {
        this->endState();
    }

}

void GameState::update(const float& dt) {
    this->updateMousePositions(&this->view);
    this->updateKeytime(dt);
    this->updatePauseInput(dt);

    if (!this->paused) {
        this->updateVieuw(dt);
        this->updateInput(dt);
        this->player->update(dt);
        this->updateTileMap(dt);

    } else if (this->paused) {
        this->updateInput(dt);
        this->pmenu->update(this->mousePosView);
        this->updatePauseButtons();

    }
}
void GameState::render(sf::RenderTarget *target) {
    if (!target)
        target = this->window;

    this->renderTexture.clear();

    this->renderTexture.setView(this->view);

    this->tileMap->render(this->renderTexture,this->player);
    std::cout << "test" << std::endl;
    this->player->render(this->renderTexture);

    if (this->paused) {
        this->renderTexture.setView(this->renderTexture.getDefaultView());
        this->pmenu->render(this->renderTexture);
    }
    //FINAL RENDER
    this->renderTexture.display();
    this->renderSprite.setTexture(this->renderTexture.getTexture());
    target->draw(this->renderSprite);

}

void GameState::updatePauseButtons() {
        if (this->pmenu->isButtonPressed("QUIT"))
            this->endState();
    }
void GameState::updateButtons()
{
    for (auto &it : this->buttons)
    {
        it.second->update(this->mousePosView);
    }
}








