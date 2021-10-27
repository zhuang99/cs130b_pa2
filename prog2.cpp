#include <iostream>
#include <string>
#include <ctime>
#include <cmath>
#include <set>
#include <vector>
#include <sstream>

using namespace std;

#define MAX_V 100
#define MAX_E 10000

struct Vertics
{
    double x;
    double y;
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

void primMST() {}

//the mst will ouput n-1 Edges
//the weight of an edge is euclidean distance between the two vertices
int main()
{

    int n = 0; //number of Vertics
    cin >> n;
    Vertics v[MAX_V];
    string input;
    vector<double> a;
    vector<pair<double, double>> vertics;
    double x;

    for (size_t i = 0; i < n; i++)
    {
        cin >> input;
        x = (stod(input));
        stringstream ss(input);
        for (double i; ss >> i;)
        {
            a.push_back(i);
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
    vector<double> b;
    vector<pair<double, double>> edges;
    Edges eg[MAX_E];

    for (size_t i = 0; i < m; i++)
    {
        cin >> input;
        stringstream ss(input);
        for (double i; ss >> i;)
        {
            b.push_back(i);
            if (ss.peek() == ' ')
                ss.ignore();
        }
    }
    for (int i = 0; i < a.size(); i += 2)
    {
        edges.push_back(make_pair(b[i], b[i + 1]));
    }

    for (size_t i = 0; i < m; i++)
    {
        eg[i].src = edges[i].first;
        eg[i].dest = edges[i].second;
        eg[i].weight = distance(v[eg[i].src], v[eg[i].dest]);
    }

    time_t c_start, c_end;
    c_start = clock();
    primMST();
    c_end = clock();
}
