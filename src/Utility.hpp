#ifndef UTILITY_HPP
#define UTILITY_HPP
enum tileType
{
  grass = 1,
  rock,
  wall,
  empty,
  selected,
  numberOfTiles
};

enum AstarData{
  none,
  start,
  end,
  open, 
  closed,
  path
};
#endif // !UTILITY_HPP
