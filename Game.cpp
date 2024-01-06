#include "pch.h"
#include "Header File/Game.h"



//Initializer functions
void Game::initGraphicsSettings() {
    this->gfxSettings.loadFromFile("C:\\Users\\nedye\\CLionProjects\\Minesweeper\\Config\\graphics.ini");

}


void Game::initStateData()
{
    this->stateData.window = this->window;
    this->stateData.gfxSettings = &this->gfxSettings;
    this->stateData.supportedKeys = &this->supportedKeys;
    this->stateData.states = &this->states;
    this->stateData.gridSize = this->gridSize;


}


void Game::initWindow() {
    //create a SFML window
    if (this->gfxSettings.fullscreen) {
        this->window = new sf::RenderWindow(this->gfxSettings.resolution, this->gfxSettings.title, sf::Style::None, this->gfxSettings.contextSettings);
    } else {
        this->window = new sf::RenderWindow(this->gfxSettings.resolution, this->gfxSettings.title, sf::Style::Titlebar | sf::Style::Close, this->gfxSettings.contextSettings);
    }


    this->window->setFramerateLimit(this->gfxSettings.frameRateLimit);
        this->window->setVerticalSyncEnabled(this->gfxSettings.verticalSync);

        // Check if the window was created successfully
        if (!this->window) {
            // Handle the error if the window was not created
            std::cerr << "Failed to create the SFML window" << std::endl;
        }
    }
void Game::initStates() {
    this->states.push(new MainMenuState(&this->stateData)) ;
    //this->states.push(new GameState(this->window,&this->supportedKeys)) ;

}
void Game::initKeys() {
    std::ifstream ifs("C:\\Users\\nedye\\CLionProjects\\Minesweeper\\Config\\supported_keys.ini");
    if (ifs.is_open()) {
        std::string key = "";
        int key_value = 0;
        while (ifs >> key >> key_value) {
            this->supportedKeys[key] = key_value;
        }
    }
    ifs.close();

    for (auto i : this->supportedKeys){
        std::cout << i.first << " " << i.second << "\n";
    }
}
void Game::initVariables()
{
    this->window = nullptr;
    this->dt = 0.f;
    this->gridSize = 32.f;
}

//static functions

//Constructors / Destructors
Game::Game() {
    this->initVariables();
    this->initGraphicsSettings();
    this->initWindow();
    this->initKeys();
    this->initStateData();
    this->initStates();

}

Game::~Game() {
    delete this->window;   //delete the window
    while (!this->states.empty()) {
        delete this->states.top();
        this->states.pop();
    }

}

//Functions
void Game::render() {
    this->window->clear();  //clear the window
    //render items
    if(!this->states.empty())
         this->states.top()->render();
    this->window->display();    //display the window
    //Render items


}

void Game::update() {
    this->UpdateSFMLEvents();

    // Mise à jour de l'état actuel du jeu
    if(!this->states.empty() ) {
        if(this->window->hasFocus())
        {
        this->states.top()->update(this->dt);

        if (this->states.top()->getWantToQuit()) {
            this->states.top()->endState();
            delete this->states.top();
            this->states.pop();
        }
    }
        }
    //Application End
    else {
        this->endApplication();
        this->window->close();
    }
}

    void Game::run() {
    while (this->window->isOpen())
    {
        this->updateDt();
        this->update();
        this->render();
    }

}

void Game::UpdateSFMLEvents() {
        while (this->window->pollEvent(this->sfEvent))
        {
            if (this->sfEvent.type == sf::Event::Closed)
                this->window->close();
        }
    }

void Game::updateDt() {
    /*Updatethe dt variable with the time it takes to update and render one frame*/
    this->dt = this->dtClock.restart().asSeconds();
}

void Game::endApplication() {
    std::cout << "Ending Application!" << "\n";
}






