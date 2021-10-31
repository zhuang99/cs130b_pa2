#include <iostream>
#include <string>
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
int find(subset s[], int i)
{
    if (s[i].parent != i)
    {
        s[i].parent = find(s, s[i].parent);
    }
    return s[i].parent;
}
void Union(subset s[], int x, int y)
{
    int xroot = find(s, x);
    int yroot = find(s, y);
    if (s[xroot].rank < s[yroot].rank)
    {
        s[xroot].parent = yroot;
    }
    else if (s[xroot].rank > s[yroot].rank)
    {
        s[yroot].parent = xroot;
    }
    else
    {
        s[yroot].parent = xroot;
        s[xroot].rank++;
    }
}
int inputsort(const void *a, const void *b)
{
    Edge *a1 = (Edge *)a;
    Edge *b1 = (Edge *)b;
    return a1->weight > b1->weight;
}
int resultsort(const void *a, const void *b)
{
    Edge *a1 = (Edge *)a;
    Edge *b1 = (Edge *)b;
    if (a1->src == b1->src)
    {
        return a1->dest > b1->dest;
    }
    return a1->src > b1->src;
}
void KruskalMST(Graph *graph2)
{
    int V = graph2->V;
    Edge *result = new Edge[V];
    int e = 0;
    int i = 0;
    
    subset *subsets = new subset[(V * sizeof(subset))];
    for (size_t v = 0; v < V; v++)
    {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }
    qsort(graph2->edge, graph2->E, sizeof(graph2->edge[0]), inputsort);
    while (e < V - 1 && i < graph2->E)
    {
        Edge next_edge = graph2->edge[i++];
        int x = find(subsets, next_edge.src);
        int y = find(subsets, next_edge.dest);

        if (x != y)
        {
            result[e++] = next_edge;
            Union(subsets, x, y);
        }
    }

    qsort(result, e, sizeof(result[0]), resultsort);
    for (size_t i = 0; i < e; i++)
    {
        cout << result[i].src << " " << result[i].dest << endl;
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
    }
    int m = 0; //input Edges.
    cin >> m;
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
        }
    }

    if (m == 0)
    {
        cout << "m==0" << endl;

        for (size_t i = 0; i < n; i++)
        {

            for (size_t j = 0; j < n; j++)
            {
                b.push_back(i);
                b.push_back(j);
            }
        }
        for (int i = 0; i < b.size(); i += 2)
        {
            edges.push_back(make_pair(b[i], b[i + 1]));
        }

        for (size_t i = 0; i < n * n; i++)
        {
            eg[i].src = edges[i].first;
            eg[i].dest = edges[i].second;
            eg[i].weight = distance(v[eg[i].src], v[eg[i].dest]);
        }
        Graph *graph = createGraph(n, n * n);
        for (size_t i = 0; i < n * n; i++)
        {
            graph->edge[i].src = eg[i].src;
            graph->edge[i].dest = eg[i].dest;
            graph->edge[i].weight = eg[i].weight;
        }
        KruskalMST(graph);
    }
    else
    {
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

        Graph *graph = createGraph(n, m);
        for (size_t i = 0; i < m; i++)
        {
            graph->edge[i].src = eg[i].src;
            graph->edge[i].dest = eg[i].dest;
            graph->edge[i].weight = eg[i].weight;
        }
        KruskalMST(graph);
    }
}
