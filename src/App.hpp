#if !defined(APP_HPP)
#define APP_HPP
#include <SFML/Graphics.hpp>
#include "Map.hpp"
#include "Tile.hpp"
class App
{
public:
  App();
  void run();
  void update();
  void display();
  void processInput(sf::Event event);

private:
  sf::RenderWindow renderWindow;
  Map map;
  Tile *t = new Tile(64, 64, tileType::wall);
};

#endif // APP_HPP
