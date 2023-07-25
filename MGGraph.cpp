#include "MGGraph.h"

namespace za
{
    namespace mg
    {
        using namespace cmp;

        Graph::Graph(const std::vector < std::vector<char>>& vals)
        {
            rows = vals.size();
            cols = vals[0].size();
            nodes.resize(rows, std::vector<Cell>(cols, Cell()));

            populate(vals);
            set_direction();

            vertice = find_all_vertice();

            directed_edges = make_all_directed_edges();
            undirected_edges = make_all_undirected_edges();
            
            directed_adj_list = make_all_directed_adj_list();
            undirected_adj_list = make_all_undirected_adj_list();
            directed_adj_mat = make_all_adj_mat();


        }
        
        Graph::~Graph()
        {
            //for (size_t i = 0; i < rows; i++)
            //{
            //    delete nodes[i];
            //}
            //delete[]nodes;
        }
        
        void Graph::display()
        {
            for (int i = 0; i < rows; i++)
            {
                for (int j = 0; j < cols; j++)
                {
                    Point center = { i, j };

                    std::cout << get_cell_char(center) << ' ';

                }
                std::cout << '\n';
            }
            std::cout << '\n';
        }
        
        void Graph::mark_entrance(Point& pnt)
        {
            at(pnt).val = MAZE_WAY::ENTRANCE;
        }
        
        void Graph::mark_exit(Point& pnt)
        {
            at(pnt).val = MAZE_WAY::EXIT;
        }
        
        void Graph::mark_entrance_exit(Point& pnt_entr, Point& pnt_exit)
        {
            mark_entrance(pnt_entr);
            mark_exit(pnt_exit);
        }
        
        void Graph::display_path(std::vector<Point>& path_tras_)
        {
            for (auto& path_el : path_tras_)
            {
                process(path_el);
                display();
                std::this_thread::sleep_for(std::chrono::milliseconds(800));
            }

        }
                
        void Graph::populate(const std::vector < std::vector<char>>& vals)
        {

            for (int i = 0; i < rows; i++)
            {

                for (int j = 0; j < rows; j++)
                {
                    nodes[i][j] = encode(vals[i][j]);
                    
                }
            }
        }                
        
        void Graph::set_direction()
        {
            dir_move = { DIR::LEFT, DIR::UP, DIR::RIGHT, DIR::DOWN };
        }
        
        bool Graph::inside_graph(const Point& pnt)
        {
            return pnt.x < rows && pnt.y < cols && pnt.x >= 0 && pnt.y >= 0;
        }
        
        bool Graph::is_on_route(const Point& pnt)
        {
            return inside_graph(pnt) && at(pnt).val != MAZE_WAY::WALL;
        }       
        
        bool Graph::is_ready_processed(Point& pnt)
        {

            return is_on_route(pnt) && at(pnt).visited == false;
        }
                
        void Graph::visit(Point& pnt)
        {
           at(pnt).visited = true;
        }
        
        char Graph::decode(MAZE_WAY& w)
        {
            char ch;

            switch (w)
            {
            case MAZE_WAY::WALL:
                ch = '#';
                break;
            case MAZE_WAY::NORMAL:
                ch = '*';
                break;
            case MAZE_WAY::PATH:
                ch = 'o';
                break;
            case MAZE_WAY::ENTRANCE:
                ch = 's';
                break;
            case MAZE_WAY::EXIT:
                ch = 'e';
                break;
            default:
                ch = '$';

                break;
            }

            return ch;
        }        
        
        char Graph::get_cell_char(Point& pnt)
        {
            char ch;
            ch = decode(at(pnt).val);
            
            return ch;
        }
                
        MAZE_WAY Graph::encode(char ch)
        {
            MAZE_WAY w;
            switch (ch)
            {
            case '#':
                w = MAZE_WAY::WALL;
                break;
            case '&':
                w = MAZE_WAY::ENEMY_1;
                break;
            case '*':
                w = MAZE_WAY::NORMAL;
                break;
            case 'o':
                w = MAZE_WAY::PATH;
                break;
            default:
                if (isdigit(ch))
                {
                    w = MAZE_WAY::BONUS_1;
                }
                else
                {
                    w = MAZE_WAY::WALL;
                }
                break;
            }


            return w;
        }

        void Graph::process(Point& pnt)
        {
            at(pnt).visited = true;

            if (at(pnt).val != MAZE_WAY::ENTRANCE && at(pnt).val != MAZE_WAY::EXIT)
            {
                at(pnt).val = MAZE_WAY::PATH;
            }
        }
        
        Cell& Graph::at(const Point& pnt)
        {
            return nodes[pnt.x][pnt.y];
        }
        
        Cell& Graph::at(Point&& pnt)
        {
            return nodes[pnt.x][pnt.y];
        }
        
        std::set<Point, comp_less_point> Graph::adj(const Point& pnt)
        {

            std::set<Point, comp_less_point> neighbors;
         
            int neighbors_num = 8;

            for (int direction = 0; direction <= neighbors_num; direction++)
            {

                DIR curr_dir = all_dir_move[direction];

                if (curr_dir == DIR::HOST || dir_move.find(curr_dir) == dir_move.end())
                {
                    continue;
                }

                int n_row = pnt.x + ((direction % 3) - 1);
                int n_col = pnt.y + ((direction / 3) - 1); 

                Point curr_neig = { n_row, n_col };

                if (is_on_route(curr_neig))
                {
                    //neighbors.push_back(curr_neig);
                    neighbors.insert(curr_neig);
                }
            }

            return neighbors;

        }
        
        Point Graph::size()
        {
            return { (int)rows, (int)cols };
        }
        
        double Graph::calc_dist(const Point& a, const Point& b)
        {
            double dist = std::sqrt(a.x*b.x + a.y*b.y);
            return dist;
        }       
        
        double Graph::calc_weight(const Point& a, const Point& b)
        {

            int w_b = as_integer(at(b).val);
            double dist = calc_dist(a, b);
            double weight = dist + w_b;
            return weight;
        }   
        
        double Graph::calc_dist_from_src_to_dest(Point& src_, Point& dest_, std::vector<Point>& path_)
        {

            auto adj_mat = get_directed_adj_mat();
            double dist = 0;
            double weight_a_b = 0;
            Point vertex_a, vertex_b;
            vertex_a = path_[0];

            for (int i = 1; i < path_.size(); i++)
            {
                
                vertex_b = path_[i];
                weight_a_b = adj_mat[vertex_a][vertex_b];
                std::cout << weight_a_b << std::endl;
                dist += weight_a_b;
                vertex_a = vertex_b;

            }

            return dist;

        }
        
        edges_set_t  Graph::make_edges_weighted_from_vertex(Point center)
        {
            auto all_center_neig = adj(center);
            edges_set_t all_edges_from_center;
            for (auto neig : all_center_neig)
            {
                double weight_center_neig = calc_weight(center, neig);
                auto curr_edge = std::make_tuple(center, neig, weight_center_neig);
                all_edges_from_center.insert(curr_edge);
            }

            return all_edges_from_center;
        }
        
        edges_set_t Graph::make_all_directed_edges()
        {
            edges_set_t all_edges;

            for (int i = 0; i < rows; i++)
            {

                for (int j = 0; j < cols; j++)
                {
                    Point center = { i, j };

                    if (is_on_route(center))
                    {
                        auto curr_edges = make_edges_weighted_from_vertex(center);

                        for (auto& edg : curr_edges)
                        {
                            Point a = std::get<0>(edg);
                            Point b = std::get<1>(edg);
                            double w_ba = calc_weight(b, a);
                            edge_set_t edg_permuted = { b, a, w_ba };
                            all_edges.insert(edg);
                            all_edges.insert(edg_permuted);

                        }

                    }
                }
            }

            return all_edges;
        }       
        
        edges_set_t Graph::make_all_undirected_edges()
        {
            std::set<edge_set_t, comp_less_tuple_point_2_double> all_edges;

            for (int i = 0; i < rows; i++)
            {

                for (int j = 0; j < cols; j++)
                {
                    Point center = { i, j };

                    if (is_on_route(center))
                    {
                        auto curr_edges = make_edges_weighted_from_vertex(center);

                        for (auto& edg : curr_edges)
                        {

                         all_edges.insert(edg);

                        }


                    }
                }
            }



            return all_edges;
        }
        
        std::map<Point, std::map<Point, double, comp_less_point>, comp_less_point> Graph::make_all_adj_mat()
        {
            std::map<Point, std::map<Point, double, comp_less_point>, comp_less_point>  mat;

            auto vertice = get_vertice();

            for (auto& vertex_a : vertice)
            {

                for (auto& vertex_b : vertice)
                {

                    auto adj_a = make_edges_weighted_from_vertex(vertex_a);

                    //is there edge between a and b ?
                    auto egde_ab_pos = std::find_if(adj_a.begin(), adj_a.end(), [&](std::tuple<Point, Point, double> edg)
                        {
                            return vertex_b == std::get<1>(edg);
                        });


                    if (vertex_a == vertex_b)
                    {
                        mat[vertex_a][vertex_b] = 0;
                    }
                    else if (egde_ab_pos != adj_a.end())
                    {
                        mat[vertex_a][vertex_b] = std::get<2>(*egde_ab_pos);
                    }
                    else
                    {
                        mat[vertex_a][vertex_b] = std::numeric_limits<double>::max();
                    }


                }

            }


            return mat;

        }
        
        std::set<Point, comp_less_point> Graph::find_all_vertice()
        {


            std::set<Point, comp_less_point> all_vertice;
            Point center;
            for (int i = 0; i < rows; i++)
            {
                for (int j = 0; j < cols; j++)
                {
                    center = { i, j };
                    if (is_on_route(center))
                    {
                        all_vertice.insert(center);
                    }
                }
            }


            return all_vertice;
        }
        
        std::map<Point, adjs_set_t, comp_less_point> Graph::make_all_directed_adj_list()
        {

            auto all_edges = make_all_directed_edges();
            std::map<Point, adjs_set_t, comp_less_point> adj_list;

            for (auto edg : all_edges)
            {
                auto vertex_a = std::get<0>(edg);
                auto vertex_b = std::get<1>(edg);
                auto weight_ab = std::get<2>(edg);
                auto adj_vertex_weighted = std::make_tuple(vertex_b, weight_ab);
                adj_list[vertex_a].insert(adj_vertex_weighted);
            }

            return adj_list;
        }

        std::map<Point, adjs_set_t, comp_less_point> Graph::make_all_undirected_adj_list()
        {

            auto all_edges = make_all_undirected_edges();
            std::map<Point, adjs_set_t, comp_less_point> adj_list;

            for (auto edg : all_edges)
            {
                auto vertex_a = std::get<0>(edg);
                auto vertex_b = std::get<1>(edg);
                auto weight_ab = std::get<2>(edg);
                auto adj_vertex_weighted = std::make_tuple(vertex_b, weight_ab);
                adj_list[vertex_a].insert(adj_vertex_weighted);
            }

            return adj_list;
        }

        std::set<Point, comp_less_point> Graph::get_vertice()
        {
            return vertice;
        }

        edges_set_t Graph::get_directed_edges()
        {
            return directed_edges;
        }

        edges_set_t Graph::get_undirected_edges()
        {
            return undirected_edges;
        }

        std::map<Point, adjs_set_t, comp_less_point> Graph::get_directed_adj_list()
        {
            return directed_adj_list;
        }

        std::map<Point, adjs_set_t, comp_less_point> Graph::get_undirected_adj_list()
        {
            return undirected_adj_list;
        }

        std::map<Point, std::map<Point, double, comp_less_point>, comp_less_point> Graph::get_directed_adj_mat()
        {
            return directed_adj_mat;
        }


    }
}