#ifndef SERVICE_H
#define SERVICE_H

#include <string>
#include <vector>
#include "FleetManager.h"

using namespace std;

class Service {
private:
    string serviceName;
    string departure;
    string arrival;
    double price;
    string category;
    FleetManager& fleetManager;

public:
    Service(FleetManager& fm);
    void selectService();

    string getServiceName() const { return serviceName; }
    string getDeparture() const { return departure; }
    string getArrival() const { return arrival; }
    double getPrice() const { return price; }
    string getCategory() const { return category; }
};

#endif