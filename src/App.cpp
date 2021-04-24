#include "App.hpp"

App::App()
{
  renderWindow.create(sf::VideoMode(600, 600), "my cool title", sf::Style::Close);
}

void App::run()
{
  while (renderWindow.isOpen())
  {
    sf::Event event;
    while (renderWindow.pollEvent(event))
    {
      processInput(event);
      update();
    }
    display();
  }
}

void App::update()
{
  map.update();
}

void App::display()
{
  renderWindow.clear();
  renderWindow.draw(map);
  renderWindow.display();
}

void App::processInput(sf::Event event)
{
  if (event.type == sf::Event::Closed)
    renderWindow.close();
  if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
  {
    sf::Vector2i position = sf::Mouse::getPosition(renderWindow);
    std::cout << position.x / 8 << " " << position.y / 8 << std::endl;
    map.setEmpty(position.x / 8, position.y / 8);
  }
  if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
  {
    sf::Vector2i position = sf::Mouse::getPosition(renderWindow);
    std::cout << position.x / 8 << " " << position.y / 8 << std::endl;
    map.selectStart(position.x / 8, position.y / 8);
  }
  if (sf::Mouse::isButtonPressed(sf::Mouse::Middle))
  {
    sf::Vector2i position = sf::Mouse::getPosition(renderWindow);
    std::cout << position.x / 8 << " " << position.y / 8 << std::endl;
    map.selectEnd(position.x / 8, position.y / 8);
  }
  if (event.type == sf::Event::KeyPressed)
  {
    if(event.key.code == sf::Keyboard::C){
      map.calculatePath();
    }
  }
}
