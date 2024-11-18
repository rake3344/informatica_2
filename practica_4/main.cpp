#include <iostream>
#include "network.h"
#include "router.h"

using namespace std;

void displayMenu() {
    cout << "Opciones:\n";
    cout << "1. Agregar enrutador\n";
    cout << "2. Eliminar enrutador\n";
    cout << "3. Agregar vecino a un enrutador\n";
    cout << "4. Calcular costo de envío\n";
    cout << "5. Encontrar camino\n";
    cout << "6. Salir\n";
}

int main()
{
    Network network;


    while (true) {
        displayMenu();

        int choice;
        cout << "Seleccione una opcion: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            string routerId;
            cout << "Ingrese el ID del enrutador: ";
            cin >> routerId;
            network.addRouter(Router(routerId));
            cout << "Enrutador " << routerId << " agregado. \n";
            break;
        }
        case 2: {
            string routerId;
            cout << "Ingrese el ID del enrutador a eliminar: ";
            cin >> routerId;
            network.removeRouter(routerId);
            cout << "Enrutador " << routerId << " eliminado.\n";
            break;
        }
        case 3: {
            string routerId, neighborId;
            int cost;
            cout << "Ingrese el ID del enrutador: ";
            cin >> routerId;
            cout << "Ingrese el ID del vecino: ";
            cin >> neighborId;
            cout << "Ingrese el costo del enlace: ";
            cin >> cost;

            if (network.routers.find(routerId) != network.routers.end()) {
                network.routers[routerId].addNeighbor(neighborId, cost);
                cout << "Vecino " << neighborId << " agregado al enrutador " << routerId << " con costo " << cost << ".\n";
            } else {
                cout << "Enrutador " << routerId << " no encontrado.\n";
            }
            break;
        }
        case 4: {
            string sourceId, destinationId;
            cout << "Ingrese el ID del enrutador origen: ";
            cin >> sourceId;
            cout << "Ingrese el ID del enrutador destino: ";
            cin >> destinationId;

            int cost = network.calculateCost(sourceId, destinationId);
            if (cost != -1) {
                cout << "Costo de enviar un paquete de " << sourceId << " a " << destinationId << ": " << cost << "\n";
            } else {
                cout << "Error: enrutador no encontrado.\n";
            }
            break;
        }
        }
    }



    return 0;
}
