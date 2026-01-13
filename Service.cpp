#include "Service.h"
#include <iostream>

Service::Service(FleetManager& fm) : fleetManager(fm) {}

void Service::selectService() {
    fleetManager.showAllServices();
    vector<string> serviceNames = fleetManager.getAllServiceNames();

    if (serviceNames.empty()) {
        cout << "No services available.\n";
        return;
    }

    string input;
    do {
        cout << "\nSelect Service (enter exact name or 'exit' to cancel): ";
        getline(cin, input);

        if (input.empty()) continue;

        if (input == "exit") {
            serviceName = "";
            return;
        }

        if (fleetManager.serviceExists(input)) {
            serviceName = input;
            departure = fleetManager.getDepartureTime(serviceName);
            arrival = fleetManager.getArrivalTime(serviceName);
            price = fleetManager.getBasePrice(serviceName);
            category = fleetManager.getCategory(serviceName);
            return;
        }

        cout << "Invalid service name. Please try again.\n";
    } while (true);
}