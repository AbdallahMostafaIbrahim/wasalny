#ifndef MAP_H
#define MAP_H
#include <unordered_map>
#include <string>
#include <vector>

using namespace std;

class Map
{
private:
    unordered_map<string, vector<pair<string, int>>> graph;
public:
    Map();
    void addCity(string cityName);
    void addEdge(string from, string to, int distance);
    void findShortestPath(string from, string to, int& distance, vector<string>& path);
};



#endif // MAP_H
