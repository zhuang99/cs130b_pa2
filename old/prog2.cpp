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

float distance(Vertics v1, Vertics v2)
{
    return sqrt(pow(v2.x - v1.x, 2) + pow(v2.y - v1.y, 2));
}
void printMST(vector<int> parent, vector<vector<double>> graph, int n)
{
    cout << "Edge \tWeight\n";
    for (int i = 1; i < n; i++)
        cout << parent[i] << " - " << i << " \t" << graph[i][parent[i]] << " \n";
}
int minKey(vector<double> key, vector<bool> mstSet, int n)
{
    // Initialize min value
    int min = INT_MAX;
    int min_index;

    for (int v = 0; v < n; v++)
        if (mstSet[v] == false && key[v] < min)
            min = key[v], min_index = v;

    return min_index;
}
void primMST(vector<vector<double>> graph, int n)
{
    vector<int> parent;
    vector<double> key;
    vector<bool> mstSet;
    for (size_t i = 0; i < n; i++)
    {
        parent.push_back(-1);
        key.push_back(INT_MAX);
        mstSet.push_back(false);
    }
    
    key.at(0) = 0;
    parent.at(0) = -1;

    for (size_t i = 0; i < n - 1; i++)
    {
        int u = minKey(key, mstSet, n);
        mstSet.at(u) = true;
        for (size_t j = 0; j < n; j++)
        {
            if (graph.at(u).at(j) && mstSet.at(j) == false && graph.at(u).at(j) < key.at(j))
            {
                parent.at(j) = u;
                key.at(j) = graph.at(u).at(j);
            }
        }
    }
    printMST(parent,graph,n);
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
            if(eg[j].src == i){
                temp_graph[eg[j].dest] = eg[j].weight;

                
            }
          
        }
        graph.push_back(temp_graph);


    }
    for (size_t i = 0; i < n; i++)
    {
        if(graph[i][n-1] != 0){
            graph[n-1][i] = graph[i][n-1];
        }
    }
    

    for (size_t i = 0; i < graph.size(); i++)
    {
        cout<<"{ ";
        for(int j = 0; j < graph[i].size();j++){
            cout<<graph[i][j]<<" ";
        }
        cout<<"} "<<endl;

    }
    
    
   
    // time_t c_start, c_end;
    // c_start = clock();
    primMST(graph, n);
    // c_end = clock();
}
