#include "map.h"

Map::Map() {}

void Map::addCity(string cityName)
{
    vector<pair<string, int>> edges;
    graph.insert({ cityName, edges });
}

void Map::addEdge(string from, string to, int distance)
{
    if(graph.find(from) != graph.end()) {
        graph[from].push_back(make_pair(to, distance));
        graph[to].push_back(make_pair(from, distance));
    }
}

void Map::findShortestPath(string from, string to, int &distance, vector<string> &path)
{
    // TODO
}


