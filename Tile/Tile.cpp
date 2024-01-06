#include "../pch.h"
#include "Tile.h"

Tile::Tile(unsigned grid_x,unsigned grid_y,float gridSizeF, const sf::Texture& texture,const sf::IntRect& texture_rect,
           bool collision, short type,float scale)
           :scale(scale) {
    this->shape.setSize(sf::Vector2f(gridSizeF, gridSizeF));
    this->shape.setFillColor(sf::Color::White);
//    this->shape.setOutlineThickness(1.f);
//    this->shape.setOutlineColor(sf::Color::Black);
    this->shape.setPosition(static_cast<float>(grid_x * gridSizeF), static_cast<float>(grid_y* gridSizeF));
    this->shape.setTexture(&texture);
    this->shape.setTextureRect(texture_rect);
    this->collision = collision;
    this->type = type;


}
Tile::Tile() {
    this->collision = false;
    this->type = 0;

}

Tile::~Tile() {

}

void Tile::update()
{

}

void Tile::render(sf::RenderTarget &target)
{
//    this->shape.setScale(1, 1);
    target.draw(this->shape);

}


const std::string Tile::getAsString() const
{
    std::stringstream ss;
    ss<< this->shape.getTextureRect().left << " " << this->shape.getTextureRect().top << " " << this->collision << " " << this->type;

    return ss.str();
}

const sf::Vector2f &Tile::getPosition() const {
    return this->shape.getPosition();
}

bool Tile::getCollision() const {
    return collision;
}

const sf::FloatRect Tile::getGlobalBounds() const
{
    return this->shape.getGlobalBounds();
}
const bool Tile::intersects(const sf::FloatRect bounds) const
{
    return this->shape.getGlobalBounds().intersects(bounds);
}