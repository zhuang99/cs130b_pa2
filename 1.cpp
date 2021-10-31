#include <iostream>
#include <string>
#include <ctime>
#include <cmath>
#include <set>
#include <vector>
#include <sstream>
#include <climits>

using namespace std;

#define MAX_V 1000
#define MAX_E 10000

struct Vertics
{
    float x;
    float y;
};

struct Edges
{
    int src;
    int dest;
    double weight;
};
class Edge
{
public:
    int src, dest;
    double weight;
};
class Graph
{
public:
    int V; //number of vertices
    int E; //number of edges
    Edge *edge;
};
Graph *createGraph(int V, int E)
{
    Graph *graph = new Graph;
    graph->V = V;
    graph->E = E;
    graph->edge = new Edge[E];
    return graph;
}

class subset
{
public:
    int parent;
    int rank;
};
float distance(Vertics v1, Vertics v2)
{
    return sqrt(pow(v2.x - v1.x, 2) + pow(v2.y - v1.y, 2));
}
int find(subset subsets[],int i){
    if(subsets[i].parent != i){
        subsets[i].parent = find(subsets,subsets[i].parent);
    }
    return subsets[i].parent;
}
void Union(subset subsets[],int x,int y){
    int xroot = find(subsets,x);
    int yroot = find(subsets,y);
    if(subsets[xroot].rank<subsets[yroot].rank){
        subsets[xroot].parent = yroot;
    }else if(subsets[xroot].rank > subsets[yroot].rank){
        subsets[yroot].parent = xroot;
    } else {
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
        
    
}
int myComp(const void* a, const void* b){
    Edge* a1 = (Edge*)a;
    Edge* b1 = (Edge*)b;
    return a1->weight > b1->weight;
}
void KruskalMST(Graph *graph2)
{
    int V = graph2->V;
    Edge * result =new Edge[V];
    int e=0;
    int i=0;
    qsort(graph2->edge,graph2->E,sizeof(graph2->edge[0]),myComp);
    subset* subsets = new subset[(V*sizeof(subset))];
    for (size_t v = 0; v < V; v++)
    {
        subsets[v].parent = v;
        subsets[v].rank = 0;

    }
    while(e<V-1 && i<graph2->E){
        Edge next_edge = graph2->edge[i++];
        int x = find(subsets,next_edge.src);
        int y = find(subsets,next_edge.dest);
        cout<<"x= "<<x<<" y= "<<y<<endl;
        if(x!= y){
            result[e++] = next_edge;
            Union(subsets,x,y);
        }
    }
    
    cout<<"result"<<endl;
    int minimumCost = 0;
    for (size_t i = 0; i <e; i++)
    {
      cout << result[i].src << " -- " << result[i].dest
             << " == " << result[i].weight << endl;
        minimumCost = minimumCost + result[i].weight;
    }
    
    

}

//the mst will ouput n-1 Edges
//the weight of an edge is euclidean distance between the two vertices
int main()
{

    int n = 0; //number of Vertics
    cin >> n;
    Vertics v[MAX_V];
    string input;
    vector<float> a;
    vector<pair<float, float>> vertics;
    float x;

    for (size_t i = 0; i < 2 * n; i++)
    {
        cin >> input;
        //  cout << stof(input) << endl;
        x = (stof(input));

        stringstream ss(input);
        for (float j; ss >> j;)
        {

            a.push_back(j);
            if (ss.peek() == ' ')
                ss.ignore();
        }
    }
    for (int i = 0; i < a.size(); i += 2)
    {
        vertics.push_back(make_pair(a[i], a[i + 1]));
    }

    for (size_t i = 0; i < n; i++)
    {

        v[i].x = vertics[i].first;
        v[i].y = vertics[i].second;
        //cout << v[i].x << " " << v[i].y << endl;
    }

    int m = 0; //input Edges.
    cin >> m;
    //cout << "m = " << m << endl;
    vector<int> b;
    vector<pair<int, int>> edges;
    Edges eg[MAX_E];
    string input2;

    for (size_t i = 0; i < 2 * m; i++)
    {
        cin >> input2;
        stringstream ss2(input2);
        for (int j; ss2 >> j;)
        {
            b.push_back(j);
            if (ss2.peek() == ' ')
            {
                ss2.ignore();
            }
            //cout << j << endl;
        }
    }
    for (int i = 0; i < b.size(); i += 2)
    {
        edges.push_back(make_pair(b[i], b[i + 1]));
    }

    for (size_t i = 0; i < m; i++)
    {

        eg[i].src = edges[i].first;
        eg[i].dest = edges[i].second;
        eg[i].weight = distance(v[eg[i].src], v[eg[i].dest]);
    }

    vector<vector<double>> graph;

    for (size_t i = 0; i < n; i++)
    {

        vector<double> temp_graph;
        for (size_t i = 0; i < n; i++)
        {
            temp_graph.push_back(0);
        }

        for (size_t j = 0; j < m; j++)
        {
            if (eg[j].src == i)
            {
                temp_graph[eg[j].dest] = eg[j].weight;
            }
        }
        graph.push_back(temp_graph);
    }
    for (size_t i = 0; i < n; i++)
    {
        if (graph[i][n - 1] != 0)
        {
            graph[n - 1][i] = graph[i][n - 1];
        }
    }

    for (size_t i = 0; i < graph.size(); i++)
    {
        cout << "{ ";
        for (int j = 0; j < graph[i].size(); j++)
        {
            cout << graph[i][j] << " ";
        }
        cout << "} " << endl;
    }

    Graph *graph2 = createGraph(n, m);
    for (size_t i = 0; i < m; i++)
    {
        graph2->edge[i].src = eg[i].src;
        graph2->edge[i].dest = eg[i].dest;
        graph2->edge[i].weight = eg[i].weight;
        cout<<graph2->edge[i].src<<", "<< graph2->edge[i].dest<<" , "<<graph2->edge[i].weight<<endl;
    }

    
    KruskalMST(graph2);
}
