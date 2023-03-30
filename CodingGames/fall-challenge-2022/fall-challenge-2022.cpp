#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <cmath>
#include <list>
#include <map>
#include <chrono>
#include <iomanip>

using namespace std;

typedef struct CellInfo
{
    int scrap_amount;
    int owner; // 1 = me, 0 = foe, -1 = neutral
    int units;
    int recycler;
    int can_build;
    int can_spawn;
    int in_range_of_recycler;
}CellInfo;

enum class CELLOWNER { NEU = -1, FOE = 0, ME, };

typedef struct Position
{
    int x;
    int y;
    bool operator<(const Position& pos)const
    {
        if (x != pos.x) 
            return x < pos.x;
        return y < pos.y;
        //return ((pos.x < x&& pos.y < y) || (pos.x < x) || (pos.y < y));
    }
}Position;

stringstream ss;
class Producer
{
public:
    void Spawn(const Position& pos, int amount)const
    {
        ss << "SPAWN " << amount << " " << pos.x << " " << pos.y << ";";
    }
    void Build(const Position& pos)const
    {
        ss << "BUILD " << pos.x << " " << pos.y << ";";
    }
};

class Recycler
{
public:
    Recycler(CELLOWNER owner, int x, int y) :m_pos{x,y},m_owner(owner) {}
    CELLOWNER GetOwner()const { return m_owner; }
    Position GetPosition()const
    {
        return m_pos;
    }
private:
    CELLOWNER m_owner;
    Position m_pos;
};

class Robot
{
public:
    Robot(int x, int y) :m_pos{ x,y } {}
    void Move(Position& dest, int amount)const
    {
        ss << "MOVE " << amount << " " << m_pos.x << " " << m_pos.y << " " << dest.x << " " << dest.y << ";";
    }
    void Wait()const
    {
        ss << "WAIT" << endl;
    }
    void SetPosition(const Position& pos)
    {
        m_pos.x = pos.x;
        m_pos.y = pos.y;
    }
    Position GetPosition()const
    {
        return m_pos;
    }
private:
    Position m_pos;
};

class Strategy
{
    vector<Robot> m_myRobots;
    vector<Robot> m_enemies;
    Producer m_producer;
    std::vector<std::vector<int>> m_cpMaze;
    std::map<Position, double> m_borderPatches;
    vector<Recycler> m_recyclers;
public:
    Strategy(std::vector<vector<CellInfo>>& maze) {
        m_cpMaze.resize(maze.size());
        for (auto& cpMaze : m_cpMaze)
            cpMaze.resize(maze[0].size());
        int sz = maze.size() * maze[0].size();
    }
    void SubmitCmd()const
    {
        if (ss.str().length() == 0)
        {
            cout << "WAIT" << endl;
        }
        else
        {
            cout << ss.str().substr(0, ss.str().size() - 1) << endl;
        }
    }
    void InitPosUnits(CELLOWNER owner, int j, int i)
    {
        switch (owner)
        {
        case CELLOWNER::ME:
        {
            m_myRobots.emplace_back(Robot{ j, i });
            break;
        }
        case CELLOWNER::FOE:
        {
            m_enemies.emplace_back(Robot{ j, i });
            break;
        }
        default:
            break;
        }
    }
    void ProduceRobotByCondition()
    {
        if (m_myRobots.size() < m_enemies.size() + 1)
        {
            m_producer.Spawn(m_myRobots[0].GetPosition(), 1);
        }
    }
    void SavePositionRecycler(CELLOWNER owner, int j, int i)
    {
        m_recyclers.emplace_back(Recycler(owner, j, i));
    }
    void bfs(Position start, Position& dest, std::vector<vector<CellInfo>>& maze)
    {
        std::list<Position> positions;
        positions.push_back(start);
        for (auto& cpMaze : m_cpMaze)//used to point the patch in which you have already been
            fill(cpMaze.begin(), cpMaze.end(), 0);
        bool firstChecking = true;
        while (!positions.empty())
        {
            Position pos = positions.front();
            m_cpMaze[pos.y][pos.x] = 1;
            positions.pop_front();
            if (pos.x + 1 < maze[0].size())
            {
                if (maze[pos.y][pos.x + 1].scrap_amount >= 1)
                {
                    if (maze[pos.y][pos.x + 1].owner == (int)(CELLOWNER::ME))
                    {
                        if (m_cpMaze[pos.y][pos.x + 1] == 0)
                        {
                            positions.emplace_back(Position{ pos.x + 1, pos.y });
                        }
                    }
                    else
                    {
                        //the patches with recycker are not avaulable for step in like grass.
                        if (maze[pos.y][pos.x + 1].recycler == 0)
                        {
                            dest = Position{ pos.x + 1, pos.y };
                            if (firstChecking)
                                maze[pos.y][pos.x + 1].owner = (int)(CELLOWNER::ME);
                            break;
                        }
                    }
                }
            }
            if (pos.x - 1 >= 0)
            {
                if (maze[pos.y][pos.x - 1].scrap_amount >= 1)
                {
                    if (maze[pos.y][pos.x - 1].owner == (int)(CELLOWNER::ME))
                    {
                        if (m_cpMaze[pos.y][pos.x - 1] == 0)
                        {
                            positions.emplace_back(Position{ pos.x - 1, pos.y });
                        }
                    }
                    else
                    {
                        if (maze[pos.y][pos.x - 1].recycler == 0)
                        {
                            dest = Position{ pos.x - 1, pos.y };
                            if (firstChecking)
                                maze[pos.y][pos.x - 1].owner = (int)(CELLOWNER::ME);
                            break;
                        }
                    }
                }
            }
            if (pos.y + 1 < maze.size())
            {
                if (maze[pos.y + 1][pos.x].scrap_amount >= 1)
                {
                    if (maze[pos.y + 1][pos.x].owner == (int)(CELLOWNER::ME))
                    {
                        if (m_cpMaze[pos.y + 1][pos.x] == 0)
                        {
                            positions.emplace_back(Position{ pos.x, pos.y + 1 });
                        }
                    }
                    else
                    {
                        if (maze[pos.y + 1][pos.x].recycler == 0)
                        {
                            dest = Position{ pos.x, pos.y + 1 };
                            if (firstChecking)
                                maze[pos.y + 1][pos.x].owner = (int)(CELLOWNER::ME);
                            break;
                        }
                    }
                }
            }
            if (pos.y - 1 >= 0)
            {
                if (maze[pos.y - 1][pos.x].scrap_amount >= 1)
                {
                    if (maze[pos.y - 1][pos.x].owner == (int)(CELLOWNER::ME))
                    {
                        if (m_cpMaze[pos.y - 1][pos.x] == 0)
                        {
                            positions.emplace_back(Position{ pos.x, pos.y - 1 });
                        }
                    }
                    else
                    {
                        if (maze[pos.y - 1][pos.x].recycler == 0)
                        {
                            dest = Position{ pos.x, pos.y - 1 };
                            if (firstChecking)
                                maze[pos.y - 1][pos.x].owner = (int)(CELLOWNER::ME);
                            break;
                        }
                    }
                }
            }
            firstChecking = false;
        }
    }
    bool IsEnemyNear(Position &start, Position& dest, std::vector<vector<CellInfo>>& maze)
    {
        int right = (start.x + 1 < maze[0].size()) ? start.x + 1 : start.x;
        int left = (start.x - 1 >= 0) ? start.x - 1 : start.x;
        int bottom = (start.y + 1 < maze.size()) ? start.y + 1 : start.y;
        int top = (start.y - 1 >= 0) ? start.y - 1 : start.y;
        bool found = false;
        for (int i = top; i <= bottom; ++i)
        {
            for (int j = left; j <= right; ++j)
            {
                if ((maze[i][j].owner == (int)CELLOWNER::FOE) && (maze[i][j].units > 0))
                {
                    found = true;
                    dest = Position{ j,i };
                    break;
                }
            }
            if (found)
                break;
        }
        return found;
    }
    void FindPositionForRecycler(std::vector<vector<CellInfo>>& maze, Position& pos, std::list<Position>& usedPos)
    {
        auto it = m_borderPatches.begin();
        while (it != m_borderPatches.end())
        {
            if (it->first.x > 1 && it->first.x < maze[0].size() - 1 && it->first.y > 1 && it->first.y < maze.size() - 1 && maze[it->first.y][it->first.x].units == 0
                && maze[it->first.y][it->first.x].recycler == 0 
                && find_if(usedPos.begin(), usedPos.end(), [&](const auto &rhs) {return (rhs.x== it->first.x && rhs.y == it->first.y);}) == usedPos.end())
            {
                if (maze[it->first.y][it->first.x + 1].units > 0 && maze[it->first.y][it->first.x + 1].owner == (int)CELLOWNER::FOE)
                {
                    pos = Position{ it->first.x ,it->first.y };
                    break;
                }
                if (maze[it->first.y][it->first.x - 1].units > 0 && maze[it->first.y][it->first.x - 1].owner == (int)CELLOWNER::FOE)
                {
                    pos = Position{ it->first.x ,it->first.y };
                    break;
                }
                if (maze[it->first.y + 1][it->first.x].units > 0 && maze[it->first.y + 1][it->first.x].owner == (int)CELLOWNER::FOE)
                {
                    pos = Position{ it->first.x ,it->first.y };
                    break;
                }
                if (maze[it->first.y - 1][it->first.x].units > 0 && maze[it->first.y - 1][it->first.x].owner == (int)CELLOWNER::FOE)
                {
                    pos = Position{ it->first.x,it->first.y };
                    break;
                }
            }
            it++;
        }
    }
    void Run(std::vector<vector<CellInfo>>& maze, int my_matter)  
    {
        int needResources = 0;
        //Move Part
        if (!m_borderPatches.empty())
        {
            for (auto& robot : m_myRobots)
            {
                Position dest{ 0,0 };
                Position start = robot.GetPosition();
                //if enemy is near
                if (IsEnemyNear(start, dest, maze))
                {
                    //let's fight
                    robot.Move(dest, 1);
                }
                else
                {
                    //let's explore map
                    bfs(start, dest, maze);
                    robot.Move(dest, 1);
                }
            }

            //Spawn Part
            std::list<Position> usedForPlaceRecycler;
            while (needResources + 10 <= my_matter)
            {
                Position pos{ -1,-1 };
                FindPositioniBestScore(pos);
                if (pos.x != -1 && pos.y != -1)
                {
                    m_producer.Spawn(pos, 1);
                }

                Position posRecycler{ -1,-1 };
                FindPositionForRecycler(maze, posRecycler, usedForPlaceRecycler);
                if (posRecycler.x != -1 && posRecycler.y != -1)
                {
                    m_producer.Build(posRecycler);
                    usedForPlaceRecycler.push_back(posRecycler);
                }
                needResources += 10;
            }
        }
        SubmitCmd();
    }
    void FindPositioniBestScore(Position &pos)
    {
        auto it = m_borderPatches.begin();
        int maxScore = 0;
        while (it != m_borderPatches.end())
        {
            if (it->second > maxScore)
            {
                maxScore = it->second;
                pos = it->first;
            }
            it++;
        }
    }
    void FindAdjacentEnemyOrNeu(std::vector<vector<CellInfo>>& maze)
    {
        auto it = m_borderPatches.begin();
        while (it != m_borderPatches.end())
        {
            if (it->second <= 0)
                it = m_borderPatches.erase(it);
            else
                it++;
        }
    }
    void UpdatePrevNeighbor(int x, int y, int owner, int scrap_amount, int recycler)
    {
        if (owner == (int)CELLOWNER::ME || scrap_amount == 0 || recycler != 0)
        {
            Position pos{ x, y };
            m_borderPatches[pos]--;
        }
    }
    void CheckNeighbors(int x, int y, std::vector<vector<CellInfo>>& maze)
    {   
        /*for all boarder patches i set up cost. if on the adjacent patch is enemy i need to add "1" to final cost*/
        if (maze[y][x].scrap_amount != 0 && maze[y][x].owner == (int)CELLOWNER::ME && maze[y][x].recycler == 0)
        {
            Position pos{ x, y };
            if ((x == 0 && y == 0) || (x == maze[0].size() - 1 && y == 0) || (x == 0 && y == maze.size() - 1) || (x == maze[0].size() - 1 && y == maze.size() - 1))
            {
                m_borderPatches[pos] = 2;
            }
            else if (y == 0 || x == 0 || x == maze[0].size() - 1 || y == maze.size() - 1)
            {
                m_borderPatches[pos] = 3;
            }
            else
            {
                m_borderPatches[pos] = 4;
            }
            if (x - 1 >= 0)
            {
                if ((maze[y][x - 1].owner == (int)CELLOWNER::ME) || (maze[y][x - 1].scrap_amount == 0) || (maze[y][x - 1].recycler != 0))
                {
                    m_borderPatches[pos]--;
                    UpdatePrevNeighbor(x - 1, y, maze[y][x].owner, maze[y][x].scrap_amount, maze[y][x - 1].recycler);
                }
            }
            if (y - 1 >= 0)
            {
                if ((maze[y - 1][x].owner == (int)CELLOWNER::ME) || (maze[y - 1][x].scrap_amount == 0) || (maze[y - 1][x].recycler != 0))
                {
                    m_borderPatches[pos]--;
                    UpdatePrevNeighbor(x, y - 1, maze[y][x].owner, maze[y][x].scrap_amount, maze[y-1][x].recycler);
                }
            }
        }
        else if(maze[y][x].scrap_amount == 0)
        {
            if (x - 1 >= 0)
            {
                if ((maze[y][x - 1].owner == (int)CELLOWNER::ME))
                {
                    UpdatePrevNeighbor(x - 1, y, maze[y][x].owner, maze[y][x].scrap_amount, maze[y][x - 1].recycler);
                }
            }
            if (y - 1 >= 0)
            {
                if ((maze[y - 1][x].owner == (int)CELLOWNER::ME))
                {
                    UpdatePrevNeighbor(x, y - 1, maze[y][x].owner, maze[y][x].scrap_amount, maze[y - 1][x].recycler);
                }
            }
        }
    }
    void Update()
    {
        m_myRobots.clear();
        m_enemies.clear();
        m_borderPatches.clear();
        m_recyclers.clear();
    }
};

/*1 Strategy:
    - find nearest enemy and move to the position
    - if matter is more than 50 create robot at the nearest position of robots are exist
    - if no enemy wait.
  2 Strategy:
    - for each robot try to find the nearest patch
    - move here and spawn a new robot if it available by resources estimating
    - the spawn of robot in the place where 
*/
/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/

int main()
{
    int width;
    int height;
    cin >> width >> height; cin.ignore();
    vector<CellInfo> row(width, { 0,0,0,0,0,0,0 });
    vector<vector<CellInfo>> maze(height, row);
    Strategy strategy(maze);

    // game loop
    while (1) {
        auto start = chrono::high_resolution_clock::now();
        //ios_base::sync_with_stdio(false);
        int my_matter;
        int opp_matter;
        cin >> my_matter >> opp_matter; cin.ignore();
        size_t ind = 0;//number of patch owned by me
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                int scrap_amount;
                int owner; // 1 = me, 0 = foe, -1 = neutral
                int units;
                int recycler;
                int can_build;
                int can_spawn;
                int in_range_of_recycler;
                cin >> scrap_amount >> owner >> units >> recycler >> can_build >> can_spawn >> in_range_of_recycler; cin.ignore();
                maze[i][j].scrap_amount = scrap_amount;
                maze[i][j].owner = owner;
                maze[i][j].units = units;
                maze[i][j].recycler = recycler;
                maze[i][j].can_build = can_build;
                maze[i][j].can_spawn = can_spawn;
                maze[i][j].in_range_of_recycler = in_range_of_recycler;
                //save positions of all robots.
                if (units > 0)
                {
                    int n = units;
                    while (n--)
                    {
                        strategy.InitPosUnits(static_cast<CELLOWNER>(owner), j, i);//i is "Y" coordinate and j is "X" coordinate
                    }
                }
                if (recycler)
                {
                    strategy.SavePositionRecycler(static_cast<CELLOWNER>(owner), j, i);
                }
                //find and save coordivates of patches are near the enemy or enemies patches or neutral patches
                strategy.CheckNeighbors(j, i, maze);
            }
        }
        strategy.FindAdjacentEnemyOrNeu(maze);
        strategy.Run(maze, my_matter);

        strategy.Update();
        ss.str("");
        ss.clear();
        auto end = chrono::high_resolution_clock::now();
        // Calculating total time taken by the program.
        double time_taken =
            chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        cerr << "Time taken by program is : " << fixed
            << time_taken << setprecision(9);
        cerr << " sec" << endl;
    }
}