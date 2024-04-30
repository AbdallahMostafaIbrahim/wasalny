#include "map.h"
#include <iostream>

Map::Map() {}

void Map::addCity(string cityName, float x, float y)
{
    if (cityCoordinates.find(cityName) == cityCoordinates.end()) {
        cityCoordinates[cityName] = {x, y};
        graph[cityName];
    }
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

MapCoordinates Map::getCityCoordinate(const string& city)
{
    auto it = cityCoordinates.find(city);
    if (it != cityCoordinates.end()) {
        return it->second;
    } else {
        throw std::runtime_error("City not found");
    }
}

void Map::setCityCoordinate(const string &city, float x, float y)
{
    auto it = cityCoordinates.find(city);
    if (it != cityCoordinates.end()) {
        cityCoordinates[city] = {x, y};
    } else {
        throw std::runtime_error("City not found");
    }
}

vector<string> Map::getCities()
{
    vector<string> cities;
    for(const auto &kv : graph) {
        cities.push_back(kv.first);
    }
    return cities;
}

vector<pair<string, int>> Map::getEdges(string city)
{
    return graph[city];
}


