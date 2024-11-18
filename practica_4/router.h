#ifndef ROUTER_H
#define ROUTER_H

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <unordered_map>

using namespace std;

// Estructura donde almaceno la información de la ruta
struct RouteInfo
{
    int cost;
    string next_hop;
    vector<string> path;
};

class Router
{
public:
    string id;
    map<string, int> neighbors; // Mapa de vecinos con costo
    map<string, pair<int, string>> routing_table; // {destino: (costo, router)}

    Router(const string& routerId);

    void updateRoutingTable();
    void addNeighbor(const string& neighborId, int cost);
    void removeNeighbor(const string& neighborId);
};

#endif // ROUTER_H
