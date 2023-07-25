#pragma once
//#include <vector>
////pair
//#include <algorithm>
//#include <utility>
//#include <unordered_set>
//#include <set>
//#include <iostream>
//#include <map>
//#include <unordered_map>
//#include <numeric>
//#include <ctype.h>
//#include <iostream>
//#include <cmath>
//#include <limits>
//#include <chrono>
//#include <thread>
#include "MGUtility.h"
#include "MGCell.h"
#include "MGSTLCompare.h"
//using namespace std;
//using namespace za::mg::cmp;
namespace za
{
    namespace mg
    {
        using namespace cmp;

        enum class DIR
        {
            UP_LEFT,
            LEFT,
            DOWN_LEFT,


            UP,
            HOST,
            DOWN,

            UP_RIGHT,
            RIGHT,
            DOWN_RIGHT,

        };
         
        using edge_set_t = std::tuple<Point, Point, double>;
        using edges_set_t = std::set<edge_set_t, comp_less_tuple_point_2_double>;
        using adj_set_t = std::tuple<Point,  double>;
        using adjs_set_t = std::set<adj_set_t, comp_less_tuple_point_double>;

        class Graph
        {
            size_t rows, cols;
            char route;
            std::vector<std::vector<Cell>> nodes;
            std::unordered_set <DIR> dir_move;

            std::vector <DIR> all_dir_move = { DIR::UP_LEFT,
            DIR::LEFT,
            DIR::DOWN_LEFT,


            DIR::UP,
            DIR::HOST,
            DIR::DOWN,

            DIR::UP_RIGHT,
            DIR::RIGHT,
            DIR::DOWN_RIGHT} ;

            edges_set_t directed_edges;
            edges_set_t undirected_edges;
            
            std::map<Point, adjs_set_t, comp_less_point> directed_adj_list;
            std::map<Point, adjs_set_t, comp_less_point> undirected_adj_list;            
            std::map<Point, std::map<Point, double, comp_less_point>, comp_less_point> directed_adj_mat;
            std::set<Point, comp_less_point> vertice;

        public:
            Graph() = delete;
            Graph(const std::vector < std::vector<char>>& vals);
            ~Graph();
            void display();
            void mark_entrance(Point& pnt);
            void mark_exit(Point& pnt);
            void mark_entrance_exit(Point& pnt_entr, Point& pnt_exit);
            void display_path(std::vector<Point>& path_tras_);
            void populate(const std::vector < std::vector<char>>& vals);
            void set_direction();
            bool inside_graph(const Point& pnt);
            bool is_on_route(const Point& pnt);
            bool is_ready_processed(Point& pnt);
            void visit(Point& pnt);
            char decode(MAZE_WAY& w);
            char get_cell_char(Point& w);
            MAZE_WAY encode(char ch);
            
            std::set<Point, comp_less_point> find_all_vertice();
            edges_set_t make_edges_weighted_from_vertex(Point center);
            edges_set_t make_all_directed_edges();
            edges_set_t make_all_undirected_edges();
            std::map<Point, adjs_set_t, comp_less_point> make_all_directed_adj_list();
            std::map<Point, adjs_set_t, comp_less_point> make_all_undirected_adj_list();
            std::map<Point, std::map<Point, double, comp_less_point>, comp_less_point> make_all_adj_mat();
            

           
            double calc_weight(const Point& a, const Point& b);
            double calc_dist_from_src_to_dest(Point& src_, Point& dest__, std::vector<Point>& path_);
            double calc_dist(const Point& a, const Point& b);
            void process(Point& pnt);


            Cell& at(const Point& pnt);

            Cell& at(Point&& pnt);
            std::set<Point, comp_less_point> adj(const Point& pnt);
            Point size();

            std::set<Point, comp_less_point> get_vertice();
            edges_set_t get_directed_edges();
            edges_set_t get_undirected_edges();
            std::map<Point, adjs_set_t, comp_less_point> get_directed_adj_list();
            std::map<Point, adjs_set_t, comp_less_point> get_undirected_adj_list();
            std::map<Point, std::map<Point, double, comp_less_point>, comp_less_point> get_directed_adj_mat();

        };
    }
}