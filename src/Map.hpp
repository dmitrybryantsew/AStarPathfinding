#if !defined(MAP_HPP)
#define MAP_HPP
#include "AStar.hpp"
#include "Utility.hpp"
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

class Map : public sf::Drawable, public sf::Transformable
{
public:
  Map();
  void calculateStep();
  void calculatePath();
  void create(sf::Vector2u tileSize, std::vector<std::vector<Tile>> &tiles, unsigned int width, unsigned int height);
  void randomize();
  void changeTerrainType(int x, int y);
  void setEmpty(int x, int y);
  void selectStart(int x, int y);
  void selectEnd(int x, int y);
  void getCoordsFromMousePos();
  void fillMapVector();
  void clearPathfinding();
  void update();
  //setters
  void setTileColor(sf::Vertex *quad, int t);
  void setAStarDataTileColor(sf::Vertex *quad, int t);
  void setQuadColor(sf::Vertex *quad, sf::Color color);
  void setStart(std::pair<int, int> start);
  void setEnd(std::pair<int, int> start);
  //getters
  void getMapSize() const;
  std::pair<int, int> getStart() const;
  std::pair<int, int> getEnd() const;

private:
  virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

  unsigned int size = 100;
  int tileSize = 8;
  sf::VertexArray m_vertices;
  std::vector<std::vector<Tile>> mapVector;
  std::pair<int, int> start{0, 0};
  std::pair<int, int> end{10, 10};

  AStar* s = new AStar(&this->mapVector);
};

#endif // MAP_HPP
