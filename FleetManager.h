#ifndef FLEETMANAGER_H
#define FLEETMANAGER_H

#include <string>
#include <map>
#include <vector>
#include <iomanip>
#include <iostream>

using namespace std;

class FleetManager {
private:
    struct ServiceInfo {
        string departureTime;
        string arrivalTime;
        double basePrice;
        string category;
        map<string, int> seatAvailability;
    };

    map<string, ServiceInfo> services;

public:
    FleetManager();
    void addService(const string& name, const string& departure, const string& arrival,
        double price, const string& category, const map<string, int>& seats);
    bool removeService(const string& name);
    void showAllServices() const;
    void showAvailableSeats(const string& serviceName) const;
    bool reserveSeat(const string& serviceName, const string& seatClass, bool release = false);
    bool serviceExists(const string& name) const;
    vector<string> getAllServiceNames() const;
    string getDepartureTime(const string& name) const;
    string getArrivalTime(const string& name) const;
    double getBasePrice(const string& name) const;
    string getCategory(const string& name) const;
};

#endif