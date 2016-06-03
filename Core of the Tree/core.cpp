#include<iostream>
#include<vector>
#include<list>
#include<queue>

#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

using namespace std;
class AdjacencyList
{
    public:
        AdjacencyList(int total_vertices)
        {
            for (int v=0; v < total_vertices; v++)
            {
                int total_edges;
                int edges;
                list<int> edge;
                cin>>total_edges;
                for (int e=0; e < total_edges; e++)
                {
                    cin>>edges;
                    edge.push_back(edges);
                }
                graph.push_back(edge);
            }
        }
        vector<list<int> > graph;
};


//Global Variables
int total_vertices = 0;
//vector< list<int> > graph; 

int BFS(int s, int *visited, int* distance, int*parent, AdjacencyList *adj)
{
    queue<int> Que;
    for(int i=0; i<total_vertices; i++)
    {
        visited[i]=0;
        parent[i]=0;
        distance[i]=0;
    }
    visited[s]=1;
    parent[s]=s;
    Que.push(s);
    while(!Que.empty())
    {
        int x=Que.front();
        Que.pop(); // pop here. we have x now

        vector<list<int> >::iterator it1=adj->graph.begin()+x;
        list<int> it2=*it1;
        list<int>::iterator iter=it2.begin();
        while(iter!=it2.end())
        {
            if(visited[*iter]==0)
            {
                visited[*iter]=1;
                parent[*iter]=x;
                int parent_index = parent[*iter];
                distance[*iter]=distance[parent_index]+1;
                visited[*iter]=1;
                Que.push(*iter);
            }
            ++iter;
        }

        visited[x]=2; 
    }
    return 0;
}

int main()
{
    int no =0;
    AdjacencyList *a;
    cin>>total_vertices;
    if(total_vertices<1)
        return 0;
    else if (total_vertices == 1)
    {
        cout<<total_vertices<<endl;
        return 0;
    }

    a = new AdjacencyList(total_vertices);
    srand (time(NULL));

    int *visited = new int[total_vertices];
    int *distance = new int[total_vertices];
    int *parent = new int[total_vertices];
    no = rand() % total_vertices + 1;  
    BFS(no, visited, distance, parent, a);
    int diameter_vertex=0;
    int max = 0;
    for(int i=0; i < total_vertices; i++)
    {
        if(max < distance[i]) 
        {
            max = distance[i];
            diameter_vertex = i;
        }
    }
    //Now that we have one of the diameters we need to rerun bfs on it again.
    BFS(diameter_vertex, visited, distance, parent, a);
    int second_diameter_vertex=0;
    max = 0;
    for(int i=0; i < total_vertices; i++)
    {
        if(max < distance[i]) 
        {
            max = distance[i];
            second_diameter_vertex = i;
        }
    }
    vector<int> core_path;
    int vertex = second_diameter_vertex;
    core_path.push_back(vertex);
    while(parent[vertex] != diameter_vertex)
    {
        vertex = parent[vertex];
        core_path.push_back(vertex);
    }
    core_path.push_back(diameter_vertex);
    int length = core_path.size()/2;
    bool isEven = ((core_path.size() % 2 == 0) ? true : false);
    //Check smaller
    int smaller = core_path[length-1]; 
    int larger = core_path[length];
    if(smaller > larger)
    {
        smaller = core_path[length];
        larger = core_path[length-1];
    }
    if(isEven)
    {
        cout << smaller << " " << larger << endl;
    }
    else
    {
        cout << core_path[length] << endl;
    }
    return 0;
}
