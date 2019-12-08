//#include "maze.h"
#include <iostream>                  // for std::cout
#include <utility>                   // for std::pair
#include <algorithm>                 // for std::for_each
#include <fstream>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>

using namespace std;
using namespace boost;
typedef adjacency_list<vecS, vecS, undirectedS> Graph;

int main(){
    ifstream maze_input("input.txt");

    int no_mazes; 
    int start_r, start_c, start_l;
    int end_r, end_c, end_l;
    int maze_r, maze_c, maze_l;
    int start_vertex, end_vertex;
    int no_level; //number of cells/vertexes per level
    int no_vertices;
    char current_directions[6];

    maze_input >> no_mazes; //get # of mazes

    maze_input >> maze_l >> maze_r >> maze_c; //gets the dimensions of current maze

    no_vertices = maze_l * maze_r * maze_c; //calculates number of vertices we will need in graph
    no_level = maze_r * maze_c; //calculates no. of cells per level, useful for going up a level

    cout << "****ROWS PER LEVEL:" << no_level << endl << endl;

    maze_input >> start_l >> start_r >> start_c; //gets start point
    maze_input >> end_l >> end_r >> end_c; //get goal point

    start_vertex = (no_level * start_l) + (start_r * maze_c) + start_c;
    end_vertex = (no_level * end_l) + (end_r * maze_c) + end_c;

    cout << "START VERTEX: " << start_vertex << endl;
    cout << "END VERTEX: " << end_vertex << endl;

    Graph g(no_vertices);

    for (int vertex = 0; vertex < no_vertices; vertex = vertex + 1){
     
        maze_input >> current_directions;
        //cout << endl << current_directions << endl;
        cout << endl << vertex << ": ";

        if(current_directions[0] == '1'){ //check if current cell goes north
            add_edge(vertex, vertex - maze_c, g); //add edge between current vertex and north vertex
            cout << "N";
        }

        if(current_directions[1] == '1'){ //check if current cell goes east
            add_edge(vertex, vertex + 1, g); //add edge between current vertex and east vertex
            cout <<  "E";
        }

        if(current_directions[2] == '1'){ //check if current cell goes south
            add_edge(vertex, vertex + maze_c, g); //add edge between current vertex and south vertex
            cout << "S";
        }

        if(current_directions[3] == '1'){ //check if current cell goes west
            add_edge(vertex, vertex - 1, g); //add edge between current vertex and west vertex
            cout << "W";
        }

        if(current_directions[4] == '1'){ //check if current cell goes up
            add_edge(vertex, vertex + no_level, g); //add edge between current vertex and up vertex
            cout <<  "U";
        }

        if(current_directions[5] == '1'){ //check if current cell goes down
            add_edge(vertex, vertex - no_level, g); //add edge between current vertex and down vertex
            cout << "D";
        }

               
                

    }

    cout <<  "no mazes: " << no_mazes << endl;
    cout << "dimensions: "<< maze_l << maze_r << maze_c <<endl;
    cout << "vertices: " << no_vertices <<endl;
    //...
    //cout << "no edges: " << edges(g) << endl;

    // cout << "edges(g) = ";
    // graph_traits<Graph>::edge_iterator ei, ei_end;
    // for (tie(ei, ei_end) = edges(g); ei != ei_end; ++ei)
    //     cout << "(" << index[source(*ei, g)] << "," << index[target(*ei, g)] << ") ";
    // cout << endl;

    // ...

    typedef graph_traits<Graph>::vertex_descriptor Vertex;

    // get the property map for vertex indices
    typedef property_map<Graph, vertex_index_t>::type IndexMap;
    IndexMap index = get(vertex_index, g);

    std::cout << "vertices(g) = ";
    typedef graph_traits<Graph>::vertex_iterator vertex_iter;
    std::pair<vertex_iter, vertex_iter> vp;
    for (vp = vertices(g); vp.first != vp.second; ++vp.first) {
      Vertex v = *vp.first;
      std::cout << index[v] <<  " ";
    }
    std::cout << std::endl;
    // ...


    // ...
    std::cout << "edges(g) = ";
    graph_traits<Graph>::edge_iterator ei, ei_end;
    for (boost::tie(ei, ei_end) = edges(g); ei != ei_end; ++ei){
            std::cout << "(" << index[source(*ei, g)]  << "," << index[target(*ei, g)] << ") ";
    }

    std::cout << std::endl;
    // // ...






    return 0;
}