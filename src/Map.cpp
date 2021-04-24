#include "Map.hpp"

Map::Map()
{
  fillMapVector();
  create({8, 8}, mapVector, size, size);

}

void Map::calculateStep()
{
  delete(s);
}

void Map::calculatePath()
{
  clearPathfinding();
  s->findPathV2(start, end);
}
void Map::create(sf::Vector2u tileSize, std::vector<std::vector<Tile>> &tiles, unsigned int width, unsigned int height)
{
  m_vertices.setPrimitiveType(sf::Quads);
  m_vertices.resize(width * height * 4);

  // populate the vertex array, with one quad per tile
  for (unsigned int i = 0; i < width; ++i)
    for (unsigned int j = 0; j < height; ++j)
    {
      // get the current tile number
      //int tileNumber = tiles[i][j];

      // find its position in the tileset texture
      //int tu = tileNumber % (m_tileset.getSize().x / tileSize.x);
      //int tv = tileNumber / (m_tileset.getSize().x / tileSize.x);

      // get a pointer to the current tile's quad
      sf::Vertex *quad = &m_vertices[(i + j * width) * 4];

      // define its 4 corners
      quad[0].position = sf::Vector2f(i * tileSize.x + 1, j * tileSize.y + 1);
      quad[1].position = sf::Vector2f((i + 1) * tileSize.x - 1, j * tileSize.y + 1);
      quad[2].position = sf::Vector2f((i + 1) * tileSize.x - 1, (j + 1) * tileSize.y - 1);
      quad[3].position = sf::Vector2f(i * tileSize.x + 1, (j + 1) * tileSize.y - 1);

      mapVector[i][j].setQuadPointer(quad);
      mapVector[i][j].setTileColor();
      
    }
}
void Map::setQuadColor(sf::Vertex *quad, sf::Color color)
{
  quad[0].color = color;
  quad[1].color = color;
  quad[2].color = color;
  quad[3].color = color;
}

void Map::setTileColor(sf::Vertex *quad, int t)
{
  if (t == tileType::grass)
  {
    setQuadColor(quad, sf::Color(34, 139, 34, 255));
  }
  else if (t == tileType::rock)
  {
    setQuadColor(quad, sf::Color(128, 128, 128, 255));
  }
  else if (t == tileType::wall)
  {
    setQuadColor(quad, sf::Color(47, 79, 79, 255));
  }
  else if (t == tileType::empty)
  {
    setQuadColor(quad, sf::Color::Black);
  }
  else if (t == tileType::selected)
  {
    setQuadColor(quad, sf::Color::Yellow);
  }
}

void Map::setAStarDataTileColor(sf::Vertex *quad, int t)
{
  if (t == AstarData::start)
  {
    setQuadColor(quad, sf::Color(255,105,180, 255)); //hotpink
  }
  else if (t == AstarData::end)
  {
    setQuadColor(quad, sf::Color(199,21,133, 255)); //mediumvioletred
  }
  else if (t == AstarData::open)
  {
    setQuadColor(quad, sf::Color(124,252,0, 255)); //lawngreen
  }
  else if (t == AstarData::closed)
  {
    setQuadColor(quad, sf::Color::Red);
  } else if (t == AstarData::path)
  {
    setQuadColor(quad, sf::Color(255,69,0, 255)); // orangered
  }

  
}

void Map::randomize()
{
}

void Map::changeTerrainType(int x, int y)
{
  
  if (x >= 0 && x < size && y >= 0 && y < size) // todo is valid
  {
      tileType currentTileType = mapVector[x][y].getTileType();
      mapVector[x][y].setTileType(static_cast<tileType>((currentTileType + 1) % tileType::numberOfTiles));

    std::cout << "tiletype " << mapVector[x][y].getTileType() << std::endl;
  }
}
void Map::setEmpty(int x, int y){
   if (x >= 0 && x < size && y >= 0 && y < size) // todo is valid
  {
    mapVector[x][y].setTileType(tileType::empty);
  }
}
void Map::selectStart(int x, int y)
{
  //todo move to is valid
  if (x >= 0 && x < size && y >= 0 && y < size)
  {
    
    if (mapVector[x][y].getAstarData() != AstarData::start)
    {
      mapVector[start.first][start.second].aData = AstarData::none;
      mapVector[x][y].aData = AstarData::start;
      setStart({x, y});
    }
  }
}
void Map::selectEnd(int x, int y)
{
  //todo move to is valid
  if (x >= 0 && x < size && y >= 0 && y < size)
  {
    
    if (mapVector[x][y].getAstarData() != AstarData::end)
    {
      mapVector[end.first][end.second].aData = AstarData::none;
      mapVector[x][y].aData = AstarData::end;
      setEnd({x, y});
    }
  }
}


void Map::getCoordsFromMousePos()
{
}

void Map::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
  // apply the transform
  states.transform *= getTransform();

  // apply the tileset texture
  //states.texture = &m_tileset;

  // draw the vertex array
  target.draw(m_vertices, states);
}

void Map::fillMapVector()
{
mapVector.resize(size);
//Tile::Tile(float posX, float posY, tileType t, sf::Vertex *quad)
for (int i = 0; i < size; ++i)
  for(int j = 0; j < size; ++j){
    mapVector[i].push_back(Tile(i, j, tileType::grass));
  }
  std::cout << mapVector.size() << " here " << std::endl;

}
void Map::update()
{
  for (int i = 0; i < size; i++)
    for (int j = 0; j < size; j++)
    {
      sf::Vertex *quad = &m_vertices[(i + j * size) * 4];

      setTileColor(quad, mapVector[i][j].getTileType());
      if(mapVector[i][j].getAstarData() != AstarData::none)
      {
        setAStarDataTileColor(quad, mapVector[i][j].getAstarData());
      }
      //todo fix this is ugly
      if (mapVector[start.first][start.second].getAstarData() != AstarData::start)
        mapVector[start.first][start.second].aData = AstarData::start;
      if (mapVector[end.first][end.second].getAstarData() != AstarData::start)
        mapVector[end.first][end.second].aData = AstarData::end;

    }
}

void Map::setStart(std::pair<int, int> start){
  //todo check if its valid
  this->start = start;
}

void Map::setEnd(std::pair<int, int> end){
  //todo check if its valid
  this->end = end;
}

void Map::clearPathfinding()
{
  for(int i = 0; i < size; ++i)
    for(int j = 0; j < size; ++j)
    {
      mapVector[i][j].aData = AstarData::none;
    }
    mapVector[start.first][start.second].aData = AstarData::start;
    mapVector[end.first][end.second].aData = AstarData::end;
}

std::pair<int, int> Map::getStart() const
{
  return start;
}

std::pair<int, int> Map::getEnd() const
{
  return end;
}