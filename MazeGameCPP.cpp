// MazeGameCPP.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include "MGUtility.h"
#include "MGSolve.h"

using namespace za::mg;
using namespace za::mg::sol;

void runSolver(SOLVER solver, std::unique_ptr<Graph>& graph, Point src, Point dest);

int main()
{
    SOLVER solver = SOLVER::DFS;

    std::string filename = "Maze2.txt";

    auto maze = init_graph(filename);

    Point src = { 0, maze->size().y - 1 };
    Point dest = { maze->size().x - 1, 0 };

    maze->mark_entrance_exit(src, dest);

    maze->display();

    runSolver(solver, maze, src, dest);

    save("adam", maze, solver);


}

void runSolver(SOLVER solver, std::unique_ptr<Graph>& graph, Point src, Point dest)
{
    switch (solver)
    {

    case SOLVER::DFS:
        DFS(graph, src, dest);
        break;
    case SOLVER::DFS_LOWEST_NEIG:
        DFS_LOWEST_NEIG(graph, src, dest);
        break;
    case SOLVER::DFS_HIGHEST_NEIG:
        DFS_HIGHEST_NEIG(graph, src, dest);
        break;
    case SOLVER::BFS:
        BFS(graph, src, dest);
        break;
    case SOLVER::BELLMANFORD:
        BellmanFord(graph, src, dest);
        break;
    case SOLVER::DIJKSTRA:
        Dijkstra(graph, src, dest);
        break;
    case SOLVER::FLOYDWARSHALL:
        FloydWarshall(graph, src, dest);
        break;


    default:

        break;


    }

}