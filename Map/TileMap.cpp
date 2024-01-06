#include "../pch.h"
#include "TileMap.h"


void TileMap::clear()
{
    if (!this->map.empty())
    {
        for (int x = 0; x < this->map.size(); x++)
        {
            for (int y = 0; y < this->map[x].size(); y++)
            {
                for (int z = 0; z < this->map[x][y].size(); z++)
                    {
                        delete this->map[x][y][z];
                        this->map[x][y][z] = NULL;
                    }
                    this->map[x][y].clear();
            }
            this->map[x].clear();
        }
        this->map.clear();
    }
    //std::cout << this->map.size() << "\n";
}



TileMap::TileMap(float gridSize, unsigned width, unsigned height, std::string texture_file) {
    this->gridSizeF = gridSize;
    this->gridSizeU = static_cast<int>(this->gridSizeF);
    this->layers = 1;
    this->maxSizegrid.x = width;
    this->maxSizegrid.y = height;
    this->maxSizeWorldF.x = static_cast<float>(width) * gridSize;
    this->maxSizeWorldF.y = static_cast<float>(height) * gridSize;
    this->textureFile = texture_file;

    this->fromX = 0;
    this->toX = 0;
    this->fromY = 0;
    this->toY = 0;
    this->layer = 0;



    this->map.resize(this->maxSizegrid.x,std::vector<std::vector<Tile* >>());
    for (size_t x = 0; x < this->maxSizegrid.x; x++) {
      for (size_t y = 0; y < this->maxSizegrid.y; y++) {
          this->map[x].resize(this->maxSizegrid.y, std::vector<Tile*>());
          for (size_t z = 0; z < this->layers; z++)
          {
              this->map[x][y].resize(this->layers, NULL);
          }
       }
        this->collisionBox.setSize(sf::Vector2f(gridSize,gridSize));
        this->collisionBox.setFillColor(sf::Color(255,0,0,50));
        this->collisionBox.setOutlineColor(sf::Color::Red);
        this->collisionBox.setOutlineThickness(1.f);
    }
    if(!this->tileSheet.loadFromFile(texture_file))
    {
        std::cout << "ERROR::TILEMAP::FAILED TO LOAD TILETEXTURESHEET" << "\n";
    }

    std::cout << "DEBUG: TILEMAP CREATED" << "\n";

}

TileMap::~TileMap() {
    for (size_t x = 0; x < this->maxSizegrid.x; x++) {

        for (size_t y = 0; y < this->maxSizegrid.y; y++) {

            for (size_t z = 0; z < this->layers; z++) {
                delete this->map[x][y][z];
            }
        }

    }
}
//Functions

void TileMap::saveToFile(const std::string file_name) {
    /*Saves the entire tilemap to a text-file.
     * Format:
     Basic:
     * Size x y
     * gridSize
     * layers
     * gridPos x y
     * textureFile

    All tiles:
     * GridPos x y
     * Texture rect x y
     * Collision
     * Type
     */
        std::ofstream out_file;
        out_file.open(file_name);

    if (out_file.is_open())
    {
        out_file << this->maxSizegrid.x << " " << this->maxSizegrid.y << "\n"
                 << this->gridSizeU << "\n"
                 << this->layers << "\n"
                 << this->textureFile << "\n";

        for (size_t x = 0; x < this->maxSizegrid.x; x++)
        {
            for (size_t y = 0; y < this->maxSizegrid.y; y++)
            {
                for (size_t z = 0; z < this->layers; z++)
                {
                    if (this->map[x][y][z])
                            out_file << x << " " << y << " " << z << " " << this->map[x][y][z]->getAsString()<< " ";
                        }
                    }
                }
            }
    else
    {
        std::cout << "ERROR::TILEMAP::COULD NOT SAVE TO FILE::FILENAME: " << file_name << "\n";
    }

    out_file.close();
}


void TileMap::loadFromFile(const std::string file_name) {

    std::ifstream in_file;
    in_file.open(file_name);

    if (in_file.is_open())
    {
        sf::Vector2u size;
        unsigned  gridSize = 0;
        unsigned  layers = 0;
        std::string texture_file = "";
        unsigned x = 0;
        unsigned y = 0 ;
        unsigned z  = 0;
        unsigned trX = 0;
        unsigned trY = 0;
        bool collision = false;
        short type =0;

        in_file >> size.x >> size.y >> gridSize >> layers >> texture_file;

            this->gridSizeF = static_cast<float>(gridSize);
            this->gridSizeU = gridSize;
            this->maxSizegrid.x = size.x;
            this->maxSizegrid.y = size.y;

            this->layers = layers;
            this->textureFile = texture_file;

            this->clear();

        this->map.resize(this->maxSizegrid.x,std::vector<std::vector<Tile* >>());
        for (size_t x = 0; x < this->maxSizegrid.x; x++)
        {
            for (size_t y = 0; y < this->maxSizegrid.y; y++)
            {
                this->map[x].resize(this->maxSizegrid.y,std::vector<Tile*>());
                for (size_t z = 0; z < this->layers; z++)
                {
                    this->map[x][y].resize(this->layers, NULL);
                }
            }
        }
        while (in_file>>x>>y>>z>>trX>>trY>>collision>>type)
        {

            this->map[x][y][z] = new Tile(x, y, this->gridSizeF, this->tileSheet, sf::IntRect(trX,trY,this->gridSizeU,this->gridSizeU),collision,type);
        }
        }
        else
        {
            std::cout << "ERROR::TILEMAP::COULD NOT LOAD FROM FILE::FILENAME: " << file_name << "\n";
        }

   in_file.close();
}

void TileMap::addTile(const unsigned int x, const unsigned int y,const unsigned int z, const sf::IntRect& texture_rect, const bool& collision, const short& type) {
    if (x < this->maxSizegrid.x && x >= 0 &&
        y < this->maxSizegrid.y && y >= 0 &&
        z < this->layers && z >= 0)
    {
        if (this->map[x][y][z] == NULL)
            this->map[x][y][z] = new Tile(x, y, this->gridSizeF, this->tileSheet, texture_rect, collision, type);
    }

}

void TileMap::removeTile(const unsigned int x, const unsigned int y, const unsigned int z)
{
    if (x < this->maxSizegrid.x && x >= 0 &&
        y < this->maxSizegrid.y && y >= 0 &&
        z < this->layers && z >= 0)
    {
        if (this->map[x][y][z] != NULL)
        {
            delete this ->map[x][y][z];
            this->map[x][y][z] = NULL;
            std::cout << "DEBUG: REMOVE TILE SUCCESS" << "\n";
        }

    }

}

const sf::Texture * TileMap::getTileSheet() const
{
    return &this->tileSheet;
}

void TileMap::updateCollision(Entity *entity, const float & dt) {
    if (entity->getPosition().x < 0.f) {
        entity->setPosition(0.f, entity->getPosition().y);
        entity->stopVelocityX();
    } else if (entity->getPosition().x + entity->getGlobalBounds().width > this->maxSizeWorldF.x) {
        entity->setPosition(this->maxSizeWorldF.x - entity->getGlobalBounds().width, entity->getPosition().y);
        entity->stopVelocityX();
    }
    if (entity->getPosition().y < 0.f) {
        entity->setPosition(entity->getPosition().x, 0.f);
        entity->stopVelocityY();
    } else if (entity->getPosition().y + entity->getGlobalBounds().height > this->maxSizeWorldF.y) {
        entity->setPosition(entity->getPosition().x, this->maxSizeWorldF.y - entity->getGlobalBounds().height);
        entity->stopVelocityY();
    }
    //TILES
    this->layer = 0;
    this->fromX = entity->getGridPosition(this->gridSizeU).x - 1;
    if (this->fromX < 0)
        this->fromX = 0;
    else if (this->fromX > this->maxSizegrid.x) {
        this->fromX = this->maxSizegrid.x;
    }
    this->toX = entity->getGridPosition(this->gridSizeU).x + 2;
    if (this->toX < 0) {
        this->toX = 0;
    }
    else if (this->toX > this->maxSizegrid.x) {
        this->toX = this->maxSizegrid.x;
    }
    this->fromY = entity->getGridPosition(this->gridSizeU).y - 1;
    if (this->fromY < 0) {
        this->fromY = 0;
    }
    else if (this->fromY > this->maxSizegrid.y) {
        this->fromY = this->maxSizegrid.y;
    }
    this->toY = entity->getGridPosition(this->gridSizeU).y + 2;
    if (this->toY < 0) {
        this->toY = 0;
    }
    else if (this->toY > this->maxSizegrid.y) {
        this->toY = this->maxSizegrid.y;
    }
    for (size_t x = this->fromX; x < this->toX; x++) {
        for (size_t y = this->fromY; y < this->toY; y++)
        {
            sf::FloatRect playerBounds = entity->getGlobalBounds();
            sf::FloatRect wallBounds = this->map[x][y][this->layer]->getGlobalBounds();
            sf::FloatRect nextPositionBounds = entity->getNextPositionBounds(dt);
            if (this->map[x][y][this->layer]->getCollision() &&
                this->map[x][y][this->layer]->intersects(nextPositionBounds)
                    )
            {
                if (playerBounds.top < wallBounds.top
                    && playerBounds.top + playerBounds.height < wallBounds.top + wallBounds.height
                    && playerBounds.left < wallBounds.left + wallBounds.width
                    && playerBounds.left + playerBounds.width > wallBounds.left
                        )
                {
                    entity->stopVelocityY();
                    entity->setPosition(playerBounds.left, wallBounds.top - playerBounds.height);
                }
                    //Top collision
                else if (playerBounds.top > wallBounds.top
                         && playerBounds.top + playerBounds.height > wallBounds.top + wallBounds.height
                         && playerBounds.left < wallBounds.left + wallBounds.width
                         && playerBounds.left + playerBounds.width > wallBounds.left
                        )
                {
                    entity->stopVelocityY();
                    entity->setPosition(playerBounds.left, wallBounds.top + wallBounds.height);
                }

                //Right collision
                if (playerBounds.left < wallBounds.left
                    && playerBounds.left + playerBounds.width < wallBounds.left + wallBounds.width
                    && playerBounds.top < wallBounds.top + wallBounds.height
                    && playerBounds.top + playerBounds.height > wallBounds.top
                        )
                {
                    entity->stopVelocityX();
                    entity->setPosition(wallBounds.left - playerBounds.width, playerBounds.top);
                }

                    //Left collision
                else if (playerBounds.left > wallBounds.left
                         && playerBounds.left + playerBounds.width > wallBounds.left + wallBounds.width
                         && playerBounds.top < wallBounds.top + wallBounds.height
                         && playerBounds.top + playerBounds.height > wallBounds.top
                        )
                {
                    entity->stopVelocityX();
                    entity->setPosition(wallBounds.left + wallBounds.width, playerBounds.top);
                }
            }

        }
        }
}

void TileMap::update() {

}

void TileMap::render(sf::RenderTarget &target,Entity *entity) {
    if (entity) {
        this->layer = 0;
        this->fromX = entity->getGridPosition(this->gridSizeU).x - 1;
        if (this->fromX < 0)
            this->fromX = 0;
        else if (this->fromX > this->maxSizegrid.x) {
            this->fromX = this->maxSizegrid.x;
        }
        this->toX = entity->getGridPosition(this->gridSizeU).x + 2;
        if (this->toX < 0) {
            this->toX = 0;
        } else if (this->toX > this->maxSizegrid.x) {
            this->toX = this->maxSizegrid.x;
        }
        this->fromY = entity->getGridPosition(this->gridSizeU).y - 1;
        if (this->fromY < 0) {
            this->fromY = 0;
        } else if (this->fromY > this->maxSizegrid.y) {
            this->fromY = this->maxSizegrid.y;
        }
        this->toY = entity->getGridPosition(this->gridSizeU).y + 2;
        if (this->toY < 0) {
            this->toY = 0;
        } else if (this->toY > this->maxSizegrid.y) {
            this->toY = this->maxSizegrid.y;
        }
        for (size_t x = this->fromX; x < this->toX; x++) {
            for (size_t y = this->fromY; y < this->toY; y++) {
                this->map[x][y][this->layer]->render(target);
                if (this->map[x][y][this->layer]->getCollision()) {
                    this->collisionBox.setPosition(this->map[x][y][this->layer]->getPosition());
                    target.draw(this->collisionBox);
                }

            }
        }
    } else {
        for (auto &x: this->map) {
            for (auto &y: x) {
                for (auto *z: y) {
                    if (z != NULL) {
                        z->render(target);
                        if (z->getCollision()) {
                            this->collisionBox.setPosition(z->getPosition());
                            target.draw(this->collisionBox);
                        }
                    }

                }
            }
        }
    }
}



