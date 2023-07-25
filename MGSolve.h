#pragma once
#include "MGUtility.h"
#include "MGGraph.h"


namespace za
{
    namespace mg
    {
        namespace sol
        {

            enum class SOLVER
            {
                DFS,
                DFS_LOWEST_NEIG,
                DFS_HIGHEST_NEIG,
                BFS,
                BELLMANFORD,
                DIJKSTRA,
                FLOYDWARSHALL,
            };

            static std::ostream& operator<<(std::ostream& os, const SOLVER type)
            {
                std::string disp = "";
                switch (type)
                {

                case SOLVER::DFS:
                    disp = "Depth First Search";
                    break;
                case SOLVER::DFS_LOWEST_NEIG:
                    disp = "Depth First Search By Lowest Neigbors";
                    break;
                case SOLVER::DFS_HIGHEST_NEIG:
                    disp = "Depth First Search By Highest Neigbors";
                    break;
                case SOLVER::BFS:
                    disp = "Breath First Search";
                    break;
                case SOLVER::BELLMANFORD:
                    disp = "Bellman Ford";
                    break;
                case SOLVER::DIJKSTRA:
                    disp = "Dijkstra";
                    break;
                case SOLVER::FLOYDWARSHALL:
                    disp = "Floydwarshall";
                    break;


                default:

                    break;


                }
                os << disp;
                return os;
            }


            //read maze data from file 
            std::unique_ptr<Graph> init_graph(std::string filename);

            std::vector<Point> DFS(std::unique_ptr<Graph>& graph, Point src, Point dest);

            std::vector<Point> DFS_LOWEST_NEIG(std::unique_ptr<Graph>& graph, Point src, Point dest);

            std::vector<Point> DFS_HIGHEST_NEIG(std::unique_ptr<Graph>& graph, Point src, Point dest);

            std::vector<Point> BFS(std::unique_ptr<Graph>& graph, Point src, Point dest);

            std::vector<Point> BellmanFord(std::unique_ptr<Graph>& graph, Point src, Point dest);

            std::vector<Point> Dijkstra(std::unique_ptr<Graph>& graph, Point src, Point dest);

            std::vector<Point> FloydWarshall(std::unique_ptr<Graph>& graph, Point src, Point dest);

            void save(std::string filename, std::unique_ptr<Graph>& graph, SOLVER sol);

        }
    }
}