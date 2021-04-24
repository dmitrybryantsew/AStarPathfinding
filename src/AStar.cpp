#include "AStar.hpp"

AStar::AStar(std::vector<std::vector<Tile>>* mapVector) : mapVector(mapVector)
{
}

AStar::~AStar()
{
}

void AStar::reconstructPath(std::vector<std::vector<Tile>>* map, std::pair<int, int> destination)
{
  std::cout << "\nThe Path is " << std::endl;
  int row = destination.first;
  int col = destination.second;

  std::stack<std::pair<int, int>> Path;

  while (!((*map)[row][col].parentCoords.first == row && (*map)[row][col].parentCoords.second == col))
  {
    
    Path.push(std::make_pair(row, col));
    int temp_row = (*map)[row][col].parentCoords.first;
    int temp_col = (*map)[row][col].parentCoords.second;
    setAsPath(temp_row, temp_col);
    row = temp_row;
    col = temp_col;
    std::cout << "in cycle " << (*map)[row][col].parentCoords.first << " " 
    << row << " " 
    << (*map)[row][col].parentCoords.second << " "
    << col <<" "  << std::endl;
  }

  Path.push(std::make_pair(row, col));
  while (!Path.empty())
  {
    std::pair<int, int> p = Path.top();
    Path.pop();
    std::cout << p.first << " " <<  p.second << std::endl;
  }
}



void AStar::findPathV2(std::pair<int, int> start, std::pair<int, int> destination)
{
  clearPathfinding();
//check if start and end are valid and not blocked and source != destination
  if (!isValid(start.first, start.second) && !isValid(destination.first, destination.second))
  {
    std::cout << "start or end is not on a " << std::endl;
  }

  //init params of starting node

  initClosedList();
  (*mapVector)[destination.first][destination.second].aData = AstarData::end;
  //init start cell
  initStartCell(start);
  //put starting cell in the open list
  addToOpenList(std::make_pair(0.0, std::make_pair(start.first, start.second)));
  
  bool foundDest = false;

  int i, j;
  while (!openList.empty())
  {
    pPair p = *openList.begin();

    // Remove this vertex from the open list
    openList.erase(openList.begin());
    i = p.second.first;
    j = p.second.second;
    // Add this vertex to the closed list
    addToClosedList(i, j);

    /* 
        Generating all the 8 successor of this cell 
  
            N.W   N   N.E 
              \   |   / 
               \  |  / 
            W----Cell----E 
                 / | \ 
               /   |  \ 
            S.W    S   S.E 
  
        Cell-->Popped Cell (i, j) 
        N -->  North       (i-1, j) 
        S -->  South       (i+1, j) 
        E -->  East        (i, j+1) 
        W -->  West           (i, j-1) 
        N.E--> North-East  (i-1, j+1) 
        N.W--> North-West  (i-1, j-1) 
        S.E--> South-East  (i+1, j+1) 
        S.W--> South-West  (i+1, j-1)*/

    // To store the 'g', 'h' and 'f' of the 8 successors
    double gNew, hNew, fNew;
    
 for (int dx  = -1; dx <= 1; ++dx){
    for (int dy = -1; dy <= 1; ++dy){
      if(dx == 0 && dy == 0) continue;
        // Only process this cell if this is a valid one
      if (isValid(i + dx, j + dy) == true)
      {
        // If the destination cell is the same as the
        // current successor
        if (isDestination(i + dx, j + dy, destination) == true)
        {
          // Set the Parent of the destination cell
          (*mapVector)[i + dx][j + dy].parentCoords.first = i;
          (*mapVector)[i +dx][j + dy].parentCoords.second = j;
          std::cout  << "The destination cell is found\n";

          reconstructPath(mapVector, destination);
          foundDest = true;
          return;
        }
        // If the successor is already on the closed
        // list or if it is blocked, then ignore it.
        // Else do the following
        else if (closedList[i + dx][j + dy] == false &&
                !isWall(i + dx, j + dy))
        {
          gNew = (*mapVector)[i][j].g + 1.0;
          hNew = calculateH({i +dx, j+dy}, destination);
          fNew = gNew + hNew;

          // If it isn’t on the open list, add it to
          // the open list. Make the current square
          // the parent of this square. Record the
          // f, g, and h costs of the square cell
          //                OR
          // If it is on the open list already, check
          // to see if this path to that square is better,
          // using 'f' cost as the measure.
          if ((*mapVector)[i + dx][j + dy].f == std::numeric_limits<double>::max() ||
              (*mapVector)[i + dx][j + dy].f > fNew)
          {
            addToOpenList(make_pair(fNew, std::make_pair(i + dx, j + dy)));

            // Update the details of this cell
            (*mapVector)[i + dx][j + dy].f = fNew;
            (*mapVector)[i + dx][j + dy].g = gNew;
            (*mapVector)[i + dx][j + dy].h = hNew;
            (*mapVector)[i + dx][j + dy].parentCoords.first = i;
            (*mapVector)[i + dx][j + dy].parentCoords.second = j;
          }
        }
       }
      }
    }
  }

  std::cout << "size is " << openList.size() << std::endl;
  if (foundDest == false)
    std::cout << "size is " << openList.size() << "Failed to find the Destination Cell" << std::endl;
  NeedToClear = true;
  return;
}

bool AStar::isValid(int i, int j)
{
  return (i >= 0) && (i < size) &&
         (j >= 0) && (j < size);
}

bool AStar::isWall(int i, int j)
{
  return (*mapVector)[i][j].getTileType() == tileType::wall || (*mapVector)[i][j].getTileType() == tileType::empty;
}

bool AStar::isDestination(int i, int j, std::pair<int, int> coords)
{
  if (i == coords.first && j == coords.second)
    return true;
  else
    return false;
}

void AStar::setDestination(std::pair<int, int> coords)
{
  destination = coords;
}

std::pair<int, int> AStar::getDestination(std::pair<int, int> coords)
{
  return destination;
}



void AStar::initStartCell(std::pair<int, int> coords)
{
  std::cout << "coords " << coords.first<< " " << coords.second << std::endl; 
  (*mapVector)[coords.first][coords.second].g = 0.0;
  (*mapVector)[coords.first][coords.second].h = 0.0;
  (*mapVector)[coords.first][coords.second].f = 0.0;
  (*mapVector)[coords.first][coords.second].parentCoords = coords;
  (*mapVector)[coords.first][coords.second].aData = AstarData::start;
}

void AStar::initClosedList()
{
  std::vector<bool> tmp(size, false);

  for (int i = 0; i < size; i++)
  {
    closedList.push_back(tmp);
  }
}

double AStar::calculateH(std::pair<int, int> source, std::pair<int, int> destination)
{
  return (double)std::sqrt((source.first - destination.first) * (source.first - destination.first) +
                           (source.second - destination.second) * (source.second - destination.second));
}

void AStar::addToOpenList(std::pair<double, std::pair<int, int>> data) {
    openList.insert(data);
    (*mapVector)[data.second.first][data.second.second].aData = AstarData::open;
}

void AStar::addToClosedList(int x, int y) {
    closedList[x][y] = true;
    (*mapVector)[x][y].aData = AstarData::closed;
}

void AStar::setAsPath(int x, int y) {
    (*mapVector)[x][y].aData = AstarData::path;
}

void AStar::clearPathfinding() {
  if(NeedToClear){
    for(int i = 0; i < size; ++i)
    for(int j = 0; j < size; ++j)
    {
      (*mapVector)[i][j].aData = AstarData::none;
      (*mapVector)[i][j].f = std::numeric_limits<double>::max();
      (*mapVector)[i][j].g = std::numeric_limits<double>::max();
      (*mapVector)[i][j].h = std::numeric_limits<double>::max();
      AstarData aData = AstarData::none;
      closedList[i][j] = false; 
    }
    openList.clear();
  }
  
}
