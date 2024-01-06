
#ifndef MINESWEEPER_TILE_H
#define MINESWEEPER_TILE_H

enum TileTypes{DEFAULT=0, DAMAGING, DOODAD};

class Tile
        {
    private:

        protected:
            sf::RectangleShape shape;
            bool collision;
            short type;
            float scale;

    public:
            Tile();
        Tile(unsigned grid_x,unsigned grid_y,float gridSizeF, const sf::Texture& texture,const sf::IntRect& texture_rect,
             bool collision, short type,float scale = 1.f);
        virtual ~Tile();
    //Functions
    const sf::Vector2f& getPosition() const;
    bool getCollision() const;
    const sf::FloatRect getGlobalBounds() const;
    const std::string getAsString() const;
    const bool intersects(const sf::FloatRect bounds) const;

    void update();
    void render(sf::RenderTarget& target);



};




#endif //MINESWEEPER_TILE_H
