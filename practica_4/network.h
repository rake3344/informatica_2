#ifndef NETWORK_H
#define NETWORK_H

#include <iostream>
#include <map>
#include <string>
#include "router.h"

using namespace std;

class Network
{
public:
    Network();

    map<string, Router> routers;

    void addRouter(const Router &router);
    void removeRouter(const string& routerId);
    void updateNetwork();
    int calculateCost(const string& sourceId, const string& destinationId);
    vector<string> findShortestPath(const string& sourceId, string& destiantionId);
    void generateRandomNetwork(int numRouters, int maxNeighbors);
    void loadFromFile(const string& filename);

};

#endif // NETWORK_H
