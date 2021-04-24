#if !defined(TILE_HPP)
#define TILE_HPP

#include <vector>
#include <SFML/Graphics.hpp>
#include "Utility.hpp"
struct Tile
{
  public:
  Tile();
  Tile(float posX, float posY, tileType t);
  void setTileColor(sf::Color color);
  //getters
  tileType getTileType() const;
  AstarData getAstarData() const;
  //setters
  void setTileType(tileType ttype);
  void setTileColor();
  void setQuadColor(sf::Color color);
  void setQuadPointer(sf::Vertex* quad);
  void setParentPair(int parent_x, int parent_y);
  void setParentPair(std::pair<int, int> parentCoords);
  private:
  //sf::Color tileColor; //todo add
  tileType ttype;
  sf::Vertex *quad;  
  int posX, posY;
  public:
  //Astar data
  std::pair<int, int> parentCoords;
    //f = g + h
  double f = std::numeric_limits<double>::max();
  double g = std::numeric_limits<double>::max();
  double h = std::numeric_limits<double>::max();
  AstarData aData = AstarData::none; //todo add
};
#endif // TILE_HPP
