#include "map.h"
#include <queue>
#include <unordered_map>
#include <vector>
#include <set>
#include <algorithm>

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

void Map::removeCity(string city)
{
    auto iter = graph.find(city);
    if (iter != graph.end()) {
        for (auto &edge : iter->second) {
            string connectedCity = edge.first;
            auto &edges = graph[connectedCity];
            for (auto it = edges.begin(); it != edges.end();) {
                if (it->first == city) {
                    it = edges.erase(it);
                } else {
                    ++it;
                }
            }
        }
        graph.erase(iter);
    }
    auto iter2 = cityCoordinates.find(city);
    if(iter2 != cityCoordinates.end()) {
        cityCoordinates.erase(iter2);
    }
}

void Map::findShortestPath(string from, string to, int &distance, vector<string> &path)
{
    // TODO
    unordered_map<string, int> dist;
    unordered_map<string, string> prev;
    priority_queue<pair<int, string>, vector<pair<int, string>>, greater<pair<int, string>>> pq;

    // Initialize distances
    for ( auto &city : getCities()) {
        dist[city] = 100;
        prev[city] = "";
    }
    dist[from] = 0;
    pq.push({0, from});

    while (!pq.empty()) {
        string u = pq.top().second;
        pq.pop();

        if (u == to) break;

        for (auto &neighbor : getEdges(u)) {
            string v = neighbor.first;
            int weight = neighbor.second;

            int alt_Path = dist[u] + weight;
            if (alt_Path < dist[v]) {
                dist[v] = alt_Path;
                prev[v] = u;
                pq.push({alt_Path, v});
            }
        }
    }

    // Build path
    path.clear();
    string current = to;
    while (!current.empty()) {
        path.push_back(current);
        current = prev[current];
    }
    reverse(path.begin(), path.end());

    // Set distance
    distance = dist[to];
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


