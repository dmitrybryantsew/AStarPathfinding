#include "Tile.hpp"

//todo remove if cant find use to default
Tile::Tile()
{}

Tile::Tile(float posX, float posY, tileType t) : posX(posX), posY(posY), ttype(t)
{
  
}

void Tile::setQuadColor(sf::Color color)
{
  this->quad[0].color = color;
  this->quad[1].color = color;
  this->quad[2].color = color;
  this->quad[3].color = color;
}

void Tile::setTileColor()
{
  if (ttype == tileType::grass)
  {
    setQuadColor(sf::Color(34, 139, 34, 255));
  }
  else if (ttype == tileType::rock)
  {
    setQuadColor(sf::Color(128, 128, 128, 255));
  }
  else if (ttype == tileType::wall)
  {
    setQuadColor(sf::Color(47, 79, 79, 255));
  }
  else if (ttype == tileType::empty)
  {
    setQuadColor(sf::Color::Black);
  }
  else if (ttype == tileType::selected)
  {
    setQuadColor(sf::Color::Yellow);
  }
}

tileType Tile::getTileType() const {
  return ttype;    
}

void Tile::setTileType(tileType t) {
    this->ttype = t;
}

void Tile::setQuadPointer(sf::Vertex* quad) {
  this->quad = quad;    
}

void Tile::setParentPair(int parent_x, int parent_y) {
    
}

void Tile::setParentPair(std::pair<int, int> parentCoords) {
    
}

AstarData Tile::getAstarData() const {
    return aData;
}
