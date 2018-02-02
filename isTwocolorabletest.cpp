#include <iostream>
#include <list>
#include <limits.h>
#include <fstream>
#include <string>
#include <vector>
using namespace std;
 

class Graph
{
    int Connected_Components_count;//int counter to keep track of connecetd components in graph
    bool TwoColorableOrNot;//boolean variable for if graph is two coloarable or not
    char B;//character variable B for Blue
    char R;//character variable R for Red
    int V; //Number of vertices in graph
    list<int> *adj;    // Pointer to an array containing adjacency lists
    void Explore(int v, bool visited[], int parent);//explore function for DFS
    void set_color(int v, int parent);//function to set colors(either red or blue) to vertices
    char* Colors;//Created a undefined char pointer
    
public:
    
    Graph(int V);   // Constructor
    void addEdge(int v, int w);   // to add an edge to graph
    void DFS();//depth first seach main function
    bool TwoColorable();//returns TwoColorableOrNot value of true or false
    int Connected_components_in_Graph();//returns Connected_Components_count 
    
};
 //constructor which sets all variables
Graph::Graph(int V)
{
    Connected_Components_count = 0;
    TwoColorableOrNot = true;
    B = 'B';
    R = 'R';
    this->V = V;//creates a constant pointer that holds the memory address of the current object
    adj = new list<int>[V];//creates a new list with V
    Colors = new char[V];//creates new array of colors with size of V

}
//function which add's edges of graph into a node list
//each index(node) has its own list
void Graph::addEdge(int v, int u)
{
    adj[v].push_back(u); // Add u to v’s list.
    adj[u].push_back(v); // Add v to u’s list.
}
//function for returning integer value of how many connected components were in this graph
int Graph::Connected_components_in_Graph()
{
    return Connected_Components_count;
}
//returns if this graph was two colorable or not
bool Graph::TwoColorable()
{
    return TwoColorableOrNot;
}
//sets each vertices in graph with red or blue accordingly
//if at start of new connected component assign first vertices with RED
//then assign all others alternating 
void Graph::set_color(int v, int parent)
{
    if(parent == -1)
    {
        Colors[v] = R;
    }
    else if(Colors[parent] == R)
    {
        Colors[v] = B;
    }
    else if(Colors[parent] == B)
    {
        Colors[v] = R;
    }
}
//main Depth first search function
void Graph::DFS()
{
    //created a boolean pointer array of length V to keep track which vertices were visited
    bool *discovered = new bool[V];
    //set all vertices to not visited
    for(int v = 0; v < V; v++)
        discovered[v] = false;
    //starting point for looping through first connected component
    for(int v = 0; v < V; v++)
    {
        if (discovered[v] == false)
        {
            Explore(v, discovered, -1);//calls Explore function with starting vertices, visited array, and -1 for parent 
            Connected_Components_count = Connected_Components_count + 1; //counter      
        }        
    }    
}
//explore function which explores through all the vertices and edges of the array will stopp
//when its found the end of its first connected component in graph
void Graph::Explore(int v, bool discovered[], int parent)
{
    discovered[v] = true;//set vertices to visited
    set_color(v, parent);//calls set_color function to set vertices with a color
    
    list<int>::iterator i;//creates a list pointer which we will use to help through all the adjencey vertices
    for(i = adj[v].begin(); i != adj[v].end(); i++)
    {
        if(!discovered[*i])//if vertices has not been visited recursivly call function with updated parameters
        {
            Explore(*i, discovered, v);
        }
        else if(discovered[*i] && *i != parent)//if vertices has been visited and its not a parent check for matching colors 
        {
            if(Colors[*i] == Colors[v])//if colors of vertices match up then we have found an odd cycle and graph is not two colorable
            {
                TwoColorableOrNot = false;
            }
        }       
    }
}


int main()
{
    ifstream getGraph;//create file variable
    int v, u, Components;//integer variables
    int V_size;//variable for number of vertices in graph
    int counter;//counter to tell me how many edges graph will have
    vector<int> arr;//vector array for the v component in graph
    vector<int> arr2;//vector array for the u component in graph
    getGraph.open("test3.txt");
    //if file was not opened say so and end program
    //else if was opened loop through each line store integers which resemble a graph and store them into my vectors accordingly 
    //while also update the number of vertices in the graph
    if(!getGraph)
    {
        cout << "file did not open" << endl;
        return 0;
    }
    else
    {
        cout <<"file opened" << endl;
        while(getGraph >>v>>u)
        {
            counter++;
            arr.push_back(v);
            arr2.push_back(u);

            if (v > u && v > V_size)
            {
                V_size = v;
            }
            else if( u > v && u > V_size)
            {
                V_size = u;
            }
        }
        V_size = V_size + 1;
    }
    cout << "Number of vertices: " << V_size << ", Number of edges: " << counter << endl;
    //call my Graph class with number vertices as parameter, this call will set all my variables in the constructor
    //also creates an object g1 of class Graph
    Graph g1(V_size);
    //creating graph verticey's and there adjacency vertices with addEdge function
    for (int i = 0; i < counter; i++)
    {
        g1.addEdge(arr[i], arr2[i]);
    }
    //call my DFS function to start Depth First Search on the graph to find out if two colorable or not
    g1.DFS();
    g1.TwoColorable()? cout << "graph is two colorable":
                       cout << "graph is not two colorable";
    //get number of connected components in graph
    cout << endl;
    Components = g1.Connected_components_in_Graph();
    cout << "There are " << Components << " connected components in this graph" << endl;
       
}
