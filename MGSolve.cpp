#pragma once
#include "MGSolve.h"


namespace za
{
    namespace mg
    {
        namespace sol
        {
            static int dfs_cnt = 0, bfs_cnt = 0;

            std::unique_ptr<Graph> init_graph(std::string filename)
            {

                dfs_cnt = bfs_cnt = 0;
                std::ifstream maze_file(filename);

                size_t n, m;

                std::string line = std::string();
                std::stringstream iss = std::stringstream();

                //Get the string line from the file 
                std::getline(maze_file, line);

                //Insert string line into stringstream buffer
                iss << line;

                //Clear original string and keep only the buffer for processing 
                line.clear();

                //Get item from the buffer using a delimiter and put it into the line, the line acts now as a buffer  
                std::getline(iss, line, ' ');

                //Convert data in the line buffer to integer, atoi only takes C char as input, convert the line string using the method c_str()
                n = atoi(line.c_str());

                //Empty the line buffer to further process the stringstream buffer
                line.clear();

                std::getline(iss, line);
                m = atoi(line.c_str());
                line.clear();

                std::vector<std::vector<char>> grid(n, std::vector<char>(m, ' '));

                for (size_t i = 0; i < n; i++)
                {

                    line.clear();

                    std::getline(maze_file, line);

                    for (int j = 0; j < m; j++)
                    {
                        grid[i][j] = line[j];
                    }

                }

                maze_file.close();

                return std::unique_ptr<Graph>(new Graph(grid));

            }

            std::vector<Point> DFS(std::unique_ptr<Graph>& graph, Point src, Point dest)
            {

                auto find_short_path = [&](Point& src_, Point& dest_)
                {

                    std::vector<Point> path_dfs;
                    std::stack<Point> s;
                    s.push(src_);

                    while (!s.empty())
                    {
                        auto curr_src = s.top();
                        s.pop();

                        if (graph->is_ready_processed(curr_src))
                        {
                            //dfs_cnt++;
                            path_dfs.push_back(curr_src);

                            graph->visit(curr_src);

                            if (curr_src == dest)
                            {
                                break;
                            }
                        }

                        for (auto neig : graph->adj(curr_src))
                        {
                            if (graph->is_ready_processed(neig))
                            {
                                s.push(neig);
                            }
                        }

                    }

                    return path_dfs;
                };

                auto path_dfs = find_short_path(src, dest);

                graph->display_path(path_dfs);

                //double dist = graph->calc_dist_from_src_to_dest(src, dest, path_dfs);

                //std::cout << "DIST [" << dist << "]" << std::endl;

                return path_dfs;
            }

            std::vector<Point> DFS_LOWEST_NEIG(std::unique_ptr<Graph>& graph, Point src, Point dest)
            {
                auto directed_adj_list = graph->get_directed_adj_list();

                auto find_short_path = [&](Point& src_, Point& dest_)
                {

                    std::vector<Point> path_dfs;
                    std::stack<Point> s;
                    s.push(src_);

                    while (!s.empty())
                    {
                        auto vertex_a = s.top();
                        s.pop();

                        if (graph->is_ready_processed(vertex_a))
                        {
                            //dfs_cnt++;
                            path_dfs.push_back(vertex_a);

                            graph->visit(vertex_a);

                            if (vertex_a == dest)
                            {
                                break;
                            }
                        }

                        std::vector<adj_set_t>adj_list_of_vertex_a(directed_adj_list[vertex_a].begin(), directed_adj_list[vertex_a].end());
                        std::sort(adj_list_of_vertex_a.begin(), adj_list_of_vertex_a.end(), comp_less_tuple_point_double());

                        for (auto vertex_b_weight : adj_list_of_vertex_a)
                        {
                            auto vertex_b = std::get<0>(vertex_b_weight);
                            if (graph->is_ready_processed(vertex_b))
                            {
                                s.push(vertex_b);
                            }
                        }


                    }

                    return path_dfs;
                };

                auto path_dfs = find_short_path(src, dest);

                graph->display_path(path_dfs);

                //double dist = graph->calc_dist_from_src_to_dest(src, dest, path_dfs);

                //std::cout << "DIST [" << dist << "]" << std::endl;
                return path_dfs;
            }

            std::vector<Point> DFS_HIGHEST_NEIG(std::unique_ptr<Graph>& graph, Point src, Point dest)
            {
                auto directed_adj_list = graph->get_directed_adj_list();

                auto find_short_path = [&](Point& src_, Point& dest_)
                {

                    std::vector<Point> path_dfs;
                    std::stack<Point> s;
                    s.push(src_);

                    while (!s.empty())
                    {
                        auto vertex_a = s.top();
                        s.pop();

                        if (graph->is_ready_processed(vertex_a))
                        {
                            //dfs_cnt++;
                            path_dfs.push_back(vertex_a);

                            graph->visit(vertex_a);

                            if (vertex_a == dest)
                            {
                                break;
                            }
                        }

                        std::vector<adj_set_t>adj_list_of_vertex_a(directed_adj_list[vertex_a].begin(), directed_adj_list[vertex_a].end());
                        std::sort(adj_list_of_vertex_a.begin(), adj_list_of_vertex_a.end(), comp_greater_tuple_point_double());

                        for (auto vertex_b_weight : adj_list_of_vertex_a)
                        {
                            auto vertex_b = std::get<0>(vertex_b_weight);
                            if (graph->is_ready_processed(vertex_b))
                            {
                                s.push(vertex_b);
                            }
                        }



                    }

                    return path_dfs;
                };

                auto path_dfs = find_short_path(src, dest);

                graph->display_path(path_dfs);

                //double dist = graph->calc_dist_from_src_to_dest(src, dest, path_dfs);

                //std::cout << "DIST [" << dist << "]" << std::endl;

                return path_dfs;

            }

            std::vector<Point> BFS(std::unique_ptr<Graph>& graph, Point src, Point dest)
            {

                auto find_short_path = [&](Point& src_, Point& dest_)
                {
                    std::queue<Point> q;
                    q.push(src_);
                    Point curr_src = src_;
                    std::vector<Point> path_bfs;
                    while (!q.empty())
                    {
                        curr_src = q.front();
                        q.pop();

                        if (graph->is_ready_processed(curr_src))
                        {
                            bfs_cnt++;
                            graph->visit(curr_src);
                            path_bfs.push_back(curr_src);
                            if (curr_src == dest_)
                            {
                                break;
                            }
                        }


                        for (auto neig : graph->adj(curr_src))
                        {
                            if (graph->is_ready_processed(neig))
                            {
                                q.push(neig);
                            }
                        }

                    }

                    return path_bfs;
                };

                auto path_bfs = find_short_path(src, dest);

                graph->display_path(path_bfs);

                //double dist = graph->calc_dist_from_src_to_dest(src, dest, path_bfs);

                //std::cout << "DIST [" << dist << "]" << std::endl;

                return path_bfs;

            }

            std::vector<Point> BellmanFord(std::unique_ptr<Graph>& graph, Point src, Point dest)
            {
                using dist_t = std::map <Point, double, comp_less_point>;
                using edges_t = std::set<edge_set_t, comp_less_tuple_point_2_double>;
                using vertices_t = std::set<Point, comp_less_point>;
                using prev_t = std::map<Point, Point, comp_less_point>;


                auto all_graph_edges = graph->get_directed_edges();
                auto vertice = graph->get_vertice();


                dist_t dist_mat;
                prev_t prev_mat;

                auto init_dist_proc_prev = [&](const vertices_t& vertice_, dist_t& dist_, prev_t& prev_)
                {

                    for (auto& vertex : vertice_)
                    {
                        dist_[vertex] = std::numeric_limits<double>::max();
                        prev_[vertex] = { -1, -1 };
                    }

                };
                auto find_short_path = [&](const Point& src_, const vertices_t& vertice_, dist_t& dist_, edges_t& edges_, prev_t& prev_)
                {

                    dist_[src] = 0;

                    for (int i = 0; i < vertice_.size(); i++)
                    {

                        for (auto& e : edges_)
                        {
                            Point a, b;
                            double w;
                            std::tie(a, b, w) = e;


                            if (dist_[a] != std::numeric_limits<double>::max() && dist_[a] + w < dist_[b])
                            {
                                dist_[b] = dist_[a] + w;
                                prev_[b] = a;
                            }
                        }

                    }
                };
                auto get_short_path = [&](Point& dest_, prev_t& prev_)
                {
                    std::deque<Point> path_from_src_to_dest_;

                    path_from_src_to_dest_.push_front(dest_);
                    Point prev_el = dest_;

                    while ((prev_el = prev_[prev_el]) != Point{ -1, -1 })
                    {
                        path_from_src_to_dest_.push_front(prev_el);

                    }

                    return std::vector<Point>(path_from_src_to_dest_.begin(), path_from_src_to_dest_.end());

                };


                init_dist_proc_prev(vertice, dist_mat, prev_mat);
                find_short_path(src, vertice, dist_mat, all_graph_edges, prev_mat);
                auto path_from_src_to_dest = get_short_path(dest, prev_mat);
                graph->display_path(path_from_src_to_dest);

                //double dist = graph->calc_dist_from_src_to_dest(src, dest, path_from_src_to_dest);

                //std::cout << "DIST [" << dist << "]" << std::endl;

                return path_from_src_to_dest;
            }

            std::vector<Point> Dijkstra(std::unique_ptr<Graph>& graph, Point src, Point dest)
            {

                using dist_t = std::map <Point, double, comp_less_point>;
                using proc_t = std::map <Point, bool, comp_less_point>;
                using vertices_t = std::set<Point, comp_less_point>;
                using prev_t = std::map<Point, Point, comp_less_point>;

                auto all_graph_edges_list = graph->get_directed_adj_list();

                auto vertice = graph->get_vertice();

                dist_t dist_mat;
                proc_t proc_mat;
                prev_t prev_mat;

                auto init_dist_proc_prev = [&](const vertices_t& vertice_, dist_t& dist_, proc_t& proc_, prev_t& prev_)
                {

                    for (auto& vertex : vertice_)
                    {
                        dist_[vertex] = std::numeric_limits<double>::max();
                        proc_[vertex] = false;
                        prev_[vertex] = { -1, -1 };
                    }

                };
                auto find_short_path = [&](const Point& src_, const vertices_t& vertice_, dist_t& dist_, proc_t& proc_, prev_t& prev_)
                {
                    using qdata_t = std::tuple<Point, double>;

                    std::priority_queue<qdata_t, std::vector<qdata_t>, comp_greater_tuple_point_double> q;

                    dist_[src_] = 0;
                    qdata_t next_vertex_with_lowest_dist_to_src = { src_ , dist_[src_] };
                    q.push(next_vertex_with_lowest_dist_to_src);
                    while (!q.empty())
                    {

                        auto curr_ele = q.top();
                        q.pop();
                        Point vertex_a;
                        double dist_vertex_a_to_src;
                        std::tie(vertex_a, std::ignore) = curr_ele;
                        // second element is used to keep tracking the node 
                        // closed to the source 

                        if (proc_[vertex_a])
                        {
                            continue;
                        }
                        else
                        {
                            proc_[vertex_a] = true;
                        }


                        for (auto adj_a : all_graph_edges_list[vertex_a])
                        {
                            Point vertex_b;
                            double dist_src_toward_vertex_b;

                            std::tie(vertex_b, dist_src_toward_vertex_b) = adj_a;

                            //go from src, vertex a, then vertex b 
                            if (dist_[vertex_a] != std::numeric_limits<double>::max() && dist_[vertex_a] + dist_src_toward_vertex_b < dist_[vertex_b])
                            {
                                dist_mat[vertex_b] = dist_mat[vertex_a] + dist_src_toward_vertex_b;
                                qdata_t next_vertex_with_lowest_dist_to_src = { vertex_b, dist_[vertex_b] };
                                q.push(next_vertex_with_lowest_dist_to_src);
                                //to arrive at vertex b, we pass throught vertex a first since it reduces the distance 
                                //between the source and vertex a
                                prev_[vertex_b] = vertex_a;
                            }


                        }

                    };
                };
                auto get_short_path = [&](Point& dest_, prev_t& prev_)
                {
                    std::deque<Point> path_from_src_to_dest_;
                    path_from_src_to_dest_.push_front(dest_);
                    Point prev_el = dest_;

                    while ((prev_el = prev_[prev_el]) != Point{ -1, -1 })
                    {
                        path_from_src_to_dest_.push_front(prev_el);
                    }

                    return std::vector<Point>(path_from_src_to_dest_.begin(), path_from_src_to_dest_.end());

                };


                init_dist_proc_prev(vertice, dist_mat, proc_mat, prev_mat);
                find_short_path(src, vertice, dist_mat, proc_mat, prev_mat);
                auto path_from_src_to_dest = get_short_path(dest, prev_mat);

                graph->display_path(path_from_src_to_dest);

                //double dist = graph->calc_dist_from_src_to_dest(src, dest, path_from_src_to_dest);

                //std::cout << "DIST [" << dist << "]" << std::endl;

                return path_from_src_to_dest;


            }

            std::vector<Point> FloydWarshall(std::unique_ptr<Graph>& graph, Point src, Point dest)
            {
                auto mat = graph->get_directed_adj_mat();
                auto vertices = graph->get_vertice();
                using vertices_t = std::set<Point, comp_less_point>;
                using mat_t = std::map<Point, std::map<Point, double, comp_less_point>, comp_less_point>;
                using next_t = std::map<Point, std::map<Point, Point, comp_less_point>, comp_less_point>;

                auto init_next_el_on_path = [&](const vertices_t& vertices_,
                    mat_t& adj_mat_)
                {
                    next_t next_el_on_path_;
                    for (auto& vertex_row : vertices)
                    {

                        for (auto& vertex_col : vertices)
                        {

                            if (mat[vertex_row][vertex_col] == std::numeric_limits<double>::max())
                            {
                                next_el_on_path_[vertex_row][vertex_col] = { -1, -1 };
                            }
                            else
                            {
                                next_el_on_path_[vertex_row][vertex_col] = vertex_col;
                            }


                        }
                    }

                    return next_el_on_path_;
                };


                auto find_short_path = [&](const vertices_t& vertices_,
                    mat_t& adj_mat_, next_t& next_el_on_path_)
                {

                    for (auto& vertex_middle : vertices)
                    {

                        for (auto& vertex_row : vertices)
                        {

                            for (auto& vertex_col : vertices)
                            {


                                if (adj_mat_[vertex_row][vertex_middle] != INT_MAX && adj_mat_[vertex_middle][vertex_col] != INT_MAX &&
                                    adj_mat_[vertex_row][vertex_middle] + adj_mat_[vertex_middle][vertex_col] < adj_mat_[vertex_row][vertex_col])
                                {
                                    adj_mat_[vertex_row][vertex_col] = adj_mat_[vertex_row][vertex_middle] + adj_mat_[vertex_middle][vertex_col];
                                    next_el_on_path_[vertex_row][vertex_col] = next_el_on_path_[vertex_row][vertex_middle];
                                }

                            }

                        }
                    }

                };

                auto get_short_path = [&](Point& src_, const Point& dest_, next_t& next_el_on_path_in)
                {
                    std::vector<Point> path_from_src_to_dest_;
                    path_from_src_to_dest_.push_back(src_);
                    Point next_el = src_;

                    while (!(next_el == dest))
                    {
                        next_el = next_el_on_path_in[next_el][dest];
                        path_from_src_to_dest_.push_back(next_el);

                    }
                    return path_from_src_to_dest_;
                };

                auto next_el_on_path = init_next_el_on_path(vertices, mat);

                find_short_path(vertices, mat, next_el_on_path);

                auto path_from_src_to_dest = get_short_path(src, dest, next_el_on_path);

                graph->display_path(path_from_src_to_dest);

                //double dist = graph->calc_dist_from_src_to_dest(src, dest, path_from_src_to_dest);

                //std::cout << "DIST [" << dist << "]" << std::endl;

                return path_from_src_to_dest;

            }

            void mark(Graph& graph, char mrk)
            {
                ////starting from the end mark the path till the start 
                //for (Cell* tmp = &graph.at({ 0, graph.size().y - 1 }); tmp != &graph.at({ graph.size().x - 1, 0 }); tmp = &graph.at(tmp->prev))
                //{
                //    tmp->val = mrk;
                //}
                //graph.at({ graph.size().x - 1, 0 }) = mrk;
            }

            void save(std::string filename, std::unique_ptr<Graph>& graph, SOLVER solver)
            {
                std::stringstream ss;
                ss << filename << "_solved_by_" << solver << ".txt";
                std::string solution_filename = ss.str();

                std::ofstream solution_file(solution_filename);

                Point siz = graph->size();
                int row = siz.x;
                int col = siz.y;
                for (int i = 0; i < row; i++)
                {
                    for (int j = 0; j < col; j++)
                    {
                        Point cell = { i, j };
                        solution_file << graph->get_cell_char(cell) << ' ';
                    }
                    solution_file << '\n';
                }

                solution_file.close();

            }
        }
    }
}
