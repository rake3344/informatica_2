#include "network.h"
#include "router.h"

Network::Network() {}

void Network::addRouter(const Router &router) {
    routers[router.id] = router;
}

void Network::removeRouter(const string &routerId) {
    routers.erase(routerId);
}

void Network::updateNetwork() {
    for (auto& routerPair : routers) {
        routerPair.second.updateRoutingTable();
    }
}

int Network::calculateCost(const string &sourceId, const string &destinationId) {
    if (routers.find(sourceId) != routers.end() && routers.find(destinationId) != routers.end()) {
        return routers[sourceId].routing_table[destinationId].first; // devuelve el costo
    }

    return -1; // Enrutador no encontrado
}
