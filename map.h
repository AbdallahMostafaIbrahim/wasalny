#ifndef MAP_H
#define MAP_H
#include <unordered_map>
#include <string>
#include <vector>

using namespace std;

struct MapCoordinates {
    float x;
    float y;
};

class Map
{
private:
    unordered_map<string, vector<pair<string, int>>> graph;
    unordered_map<string, MapCoordinates> cityCoordinates;
public:
    Map();
    void addCity(string cityName, float x, float y);
    void addEdge(string from, string to, int distance);
    void findShortestPath(string from, string to, int& distance, vector<string>& path);
    void extracted(vector<string> &cities);
    MapCoordinates getCityCoordinate(const string& city);
    void setCityCoordinate(const string& city, float x, float y);
    vector<string> getCities();
    vector<pair<string,int>> getEdges(string city);
};



#endif // MAP_H
