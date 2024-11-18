#include "router.h"

Router::Router(const string &routerId) {
    this->id = routerId;
}

void Router::updateRoutingTable() {
    for (const auto& neighbor : neighbors) {
        routing_table[neighbor.first] = {neighbor.second, neighbor.first};
    }
}

void Router::addNeighbor(const string &neighborId, int cost) {
    neighbors[neighborId] = cost;
    updateRoutingTable(); // Actualizo la tabla de enrutamiento
}

void Router::removeNeighbor(const string &neighborId) {
    neighbors.erase(neighborId);
    updateRoutingTable();
}
