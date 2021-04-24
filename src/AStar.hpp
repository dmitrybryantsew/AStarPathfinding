#if !defined(ASTAR_HPP)
#define ASTAR_HPP
#include <SFML/Graphics.hpp>
#include <utility>
#include <limits>
#include <set>
#include <cmath>
#include <iostream>
#include "Utility.hpp"
#include <stack>
#include "Tile.hpp"
class AStar
{
private:
  /* data */
public:
  
  AStar(std::vector<std::vector<Tile>>* mapVector);
  ~AStar();
  void reconstructPath(std::vector<std::vector<Tile>>* map, std::pair<int, int> destination);
  void findPath(std::pair<int, int> start, std::pair<int, int> end);
  void findPathV2(std::pair<int, int> start, std::pair<int, int> end);
  bool isValid(int i, int j);
  bool isWall(int i, int j);
  bool isDestination(int i, int j, std::pair<int, int> coords);
  void setDestination(std::pair<int, int> coords);
  void initStartCell(std::pair<int, int> coords);
  void initClosedList();
  void addToOpenList(std::pair<double, std::pair<int, int>> data);
  void addToClosedList(int x, int y);
  void setAsPath(int x, int y);
  void clearPathfinding();
  double calculateH(std::pair<int, int> source, std::pair<int, int> destination);
  std::pair<int, int> getDestination(std::pair<int, int> coords);

private:
  typedef std::pair<double, std::pair<int, int>> pPair;
  //open set
  std::set<pPair> openList;
  //Closed Set
  std::vector<std::vector<bool>> closedList;
  std::pair<int, int> destination;
  std::vector<std::vector<Tile>>* mapVector;
  int size = 100;
  bool NeedToClear = false;
};

#endif // ASTAR_HPP