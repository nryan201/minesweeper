#ifndef MINESWEEPER_TILEMAP_H
#define MINESWEEPER_TILEMAP_H
#include "../Tile/Tile.h"
#include "../Entity/Entity.h"

class Entity;
class Tile;


class TileMap
        {
private:
            void clear();
            float gridSizeF;
            std::vector <std::vector <std::vector<Tile*>>> map;
            sf::Vector2u maxSizegrid;
            unsigned gridSizeU;
            sf::Vector2f maxSizeWorldF;

            int layers;
            std::string textureFile;
            sf::Texture tileSheet;
            sf::RectangleShape collisionBox;

            int fromX;
            int toX;
            int fromY;
            int toY;
            int layer;



    public:
        TileMap(float gridSize, unsigned width, unsigned height, std::string texture_file);
        virtual ~TileMap();

        //Accessors
        const sf::Texture* getTileSheet() const;

        void addTile(const unsigned int x, const unsigned int y,const unsigned int z, const sf::IntRect& texture_rect, const bool& collision = false, const short& type = TileTypes::DEFAULT);
        void removeTile(const unsigned x, const unsigned y, const unsigned z);

        void saveToFile(const std::string file_name);
        void loadFromFile(const std::string file_name);

        void updateCollision(Entity* entity, const float& dt);
        void updateTileCollision(Entity* entity, const float& dt);
    void updateWorldBoundsCollision(Entity * entity, const float & dt);

        void update();
        void render(sf::RenderTarget& target,Entity *entity = NULL);

};


#endif //MINESWEEPER_TILEMAP_H
