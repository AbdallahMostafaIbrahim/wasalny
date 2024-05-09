#include "map.h"
#include <algorithm>
#include <queue>
#include <unordered_map>
#include <vector>

Map::Map() {}

void Map::addCity(string cityName, float x, float y) {
  if (cityCoordinates.find(cityName) == cityCoordinates.end()) {
    cityCoordinates[cityName] = {x, y};
    graph[cityName];
  }
}

void Map::addEdge(string from, string to, int distance) {
  if (from == to)
    return;

  auto &fromEdges = graph[from];
  bool found = false;
  for (auto it = fromEdges.begin(); it != fromEdges.end(); ++it) {
    if (it->first == to) {
      it->second = distance;
      found = true;
      break;
    }
  }

  if (!found) {
    fromEdges.push_back(make_pair(to, distance));
  }

  found = false;
  auto &toEdges = graph[to];
  for (auto it = toEdges.begin(); it != toEdges.end(); ++it) {
    if (it->first == from) {
      it->second = distance;
      found = true;
      break;
    }
  }

  if (!found) {
    toEdges.push_back(make_pair(from, distance));
  }
}

void Map::deleteEdge(string from, string to) {
  auto &fromEdges = graph[from];
  for (auto it = fromEdges.begin(); it != fromEdges.end(); ++it) {
    if (it->first == to) {
      fromEdges.erase(it);
      break;
    }
  }

  auto &toEdges = graph[to];
  for (auto it = toEdges.begin(); it != toEdges.end(); ++it) {
    if (it->first == from) {
      toEdges.erase(it);
      break;
    }
  }
}

void Map::removeCity(string city) {
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
  if (iter2 != cityCoordinates.end()) {
    cityCoordinates.erase(iter2);
  }
}

void Map::findShortestPath(string from, string to, int &distance,
                           vector<string> &path) {
  // TODO
  unordered_map<string, int> dist;
  unordered_map<string, string> prev;
  priority_queue<pair<int, string>, vector<pair<int, string>>,
                 greater<pair<int, string>>>
      pq;

  // Initialize distances
  for (auto &city : getCities()) {
    dist[city] = 999999;
    prev[city] = "";
  }
  dist[from] = 0;
  pq.push({0, from});

  while (!pq.empty()) {
    string u = pq.top().second;
    pq.pop();

    if (u == to)
      break;

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

MapCoordinates Map::getCityCoordinate(const string &city) {
  auto it = cityCoordinates.find(city);
  if (it != cityCoordinates.end()) {
    return it->second;
  } else {
    throw std::runtime_error("City not found");
  }
}

void Map::setCityCoordinate(const string &city, float x, float y) {
  auto it = cityCoordinates.find(city);
  if (it != cityCoordinates.end()) {
    cityCoordinates[city] = {x, y};
  }
}

vector<string> Map::getCities() {
  vector<string> cities;
  for (const auto &kv : graph) {
    cities.push_back(kv.first);
  }
  return cities;
}

vector<pair<string, int>> Map::getEdges(string city) { return graph[city]; }
