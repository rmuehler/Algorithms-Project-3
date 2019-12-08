//#include "maze.h"
#include <iostream>                  // for std::cout
#include <utility>                   // for std::pair
#include <algorithm>                 // for std::for_each
#include <fstream>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/depth_first_search.hpp>
#include <boost/graph/graph_utility.hpp>


using namespace std;
using namespace boost;
// typedef graph_traits<Graph>::vertex_descriptor MyVertex;


// class MyVisitor : public default_dfs_visitor
// {
// public:
//   void discover_vertex(MyVertex v, const Graph& g) const
//   {
//     cout << v << endl;
//     return;
//   }
// };

int main(){
    ifstream maze_input("input.txt");

    //clear old output file:
    remove("output.txt");


    int no_mazes; 
    int start_r, start_c, start_l;
    int end_r, end_c, end_l;
    int maze_r, maze_c, maze_l;
    int start_vertex, end_vertex;
    int no_level; //number of cells/vertexes per level
    int no_vertices; 
    char current_directions[6];
    struct EdgeProperties {
         string label; //direction being travelled
         int weight = 1; //needs to be the same since path doesnt matter
    };
    struct VertexProperties { int vertex; };
    typedef adjacency_list<vecS, vecS, directedS, no_property, EdgeProperties> Graph; //create a Boost graph
    EdgeProperties e; //edge property to set label of the edges to the direction travelled.

    typedef graph_traits<Graph>::edge_descriptor MyEdge;
    class MyVisitor : public boost::default_dfs_visitor  //visitor used during DFS to examine each edge and output direction travelled.
    {
    public:
    
    void examine_edge(MyEdge e, const Graph& g) const
        {
            ofstream maze_output;
            maze_output.open("output.txt", ios_base::app); // append instead of overwrite
            maze_output << e ; 
            maze_output << " ";
            maze_output.close();
            // auto source_n = source(e, g);
            // cout << g[source_n].label << " ";
            return;
        }
    };

    Graph g;
    maze_input >> no_mazes; //get # of mazes
    for (int i = 0; i < no_mazes; i++){
        g.clear();
        maze_input >> maze_l >> maze_r >> maze_c; //gets the dimensions of current maze

        no_vertices = maze_l * maze_r * maze_c; //calculates number of vertices we will need in graph
        no_level = maze_r * maze_c; //calculates no. of cells per level, useful for going up a level

        maze_input >> start_l >> start_r >> start_c; //gets start point
        maze_input >> end_l >> end_r >> end_c; //get goal point

        start_vertex = (no_level * start_l) + (start_r * maze_c) + start_c; //get the label of starting vertex
        end_vertex = (no_level * end_l) + (end_r * maze_c) + end_c; //get the label of the ending vertex

        for (int vertex = 0; vertex < no_vertices; vertex = vertex + 1){

            maze_input >> current_directions;

            if(current_directions[0] == '1'){ //check if current cell goes north
                e.label = "N";
                add_edge(vertex, vertex - maze_c, e, g); //add edge between current vertex and north vertex
            }

            if(current_directions[1] == '1'){ //check if current cell goes east
                e.label = "E";
                add_edge(vertex, vertex + 1,e, g); //add edge between current vertex and east vertex
            }

            if(current_directions[2] == '1'){ //check if current cell goes south
                e.label = "S";
                add_edge(vertex, vertex + maze_c,e, g); //add edge between current vertex and south vertex
            }

            if(current_directions[3] == '1'){ //check if current cell goes west
                e.label = "W";
                add_edge(vertex, vertex - 1,e, g); //add edge between current vertex and west vertex
            }

            if(current_directions[4] == '1'){ //check if current cell goes up
                e.label = "U";
                add_edge(vertex, vertex + no_level,e, g); //add edge between current vertex and up vertex
            }

            if(current_directions[5] == '1'){ //check if current cell goes down
                e.label = "D";
                add_edge(vertex, vertex - no_level,e, g); //add edge between current vertex and down vertex
            }

        }
        //print_graph(g);
        MyVisitor vis;
        depth_first_search(g, visitor(vis));
        ofstream maze_output;
        maze_output.open("output.txt", ios_base::app); // append instead of overwrite
        maze_output << endl;
        maze_output.close();

    }
    maze_input.close();
    return 0;
}