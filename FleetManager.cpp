#include "FleetManager.h"

FleetManager::FleetManager() {
 
    addService("Air Blue", "10:00", "13:00", 15000.0, "Refundable", { {"business", 20}, {"standard", 100} });
    addService("Green Line Express", "08:00", "14:30", 5000.0, "Sleeper", { {"business", 15}, {"standard", 80} });
    addService("Daewoo", "09:00", "15:00", 3500.0, "Luxury", { {"business", 10}, {"standard", 50} });
}

void FleetManager::addService(const string& name, const string& departure, const string& arrival,
    double price, const string& category, const map<string, int>& seats) {
    ServiceInfo newService;
    newService.departureTime = departure;
    newService.arrivalTime = arrival;
    newService.basePrice = price;
    newService.category = category;
    newService.seatAvailability = seats;
    services[name] = newService;
}

bool FleetManager::removeService(const string& name) {
    return services.erase(name) > 0;
}

void FleetManager::showAllServices() const {
    cout << "\nAvailable Services:\n";
    cout << "----------------------------------------------------------------------------\n";
    cout << left << setw(20) << "Service Name"
        << setw(10) << "Departure"
        << setw(10) << "Arrival"
        << setw(15) << "Price"
        << setw(15) << "Category" << endl;
    cout << "----------------------------------------------------------------------------\n";

    for (const auto& service : services) {
        cout << left << setw(20) << service.first
            << setw(10) << service.second.departureTime
            << setw(10) << service.second.arrivalTime
            << "Rs." << setw(12) << fixed << setprecision(2) << service.second.basePrice
            << setw(15) << service.second.category << endl;
    }
}

void FleetManager::showAvailableSeats(const string& serviceName) const {
    auto it = services.find(serviceName);
    if (it != services.end()) {
        cout << "\nAvailable seats for " << serviceName << ":\n";
        cout << "--------------------------------------------------\n";
        for (const auto& seat : it->second.seatAvailability) {
            cout << seat.first << " class: " << seat.second << " seats available\n";
        }
    }
    else {
        cout << "Service not found.\n";
    }
}

bool FleetManager::reserveSeat(const string& serviceName, const string& seatClass, bool release) {
    auto it = services.find(serviceName);
    if (it != services.end()) {
        if (release) {
            it->second.seatAvailability[seatClass]++;
            return true;
        }
        else if (it->second.seatAvailability[seatClass] > 0) {
            it->second.seatAvailability[seatClass]--;
            return true;
        }
    }
    return false;
}

bool FleetManager::serviceExists(const string& name) const {
    return services.find(name) != services.end();
}

vector<string> FleetManager::getAllServiceNames() const {
    vector<string> names;
    for (const auto& service : services) {
        names.push_back(service.first);
    }
    return names;
}

string FleetManager::getDepartureTime(const string& name) const {
    auto it = services.find(name);
    return it != services.end() ? it->second.departureTime : "";
}

string FleetManager::getArrivalTime(const string& name) const {
    auto it = services.find(name);
    return it != services.end() ? it->second.arrivalTime : "";
}

double FleetManager::getBasePrice(const string& name) const {
    auto it = services.find(name);
    return it != services.end() ? it->second.basePrice : 0.0;
}

string FleetManager::getCategory(const string& name) const {
    auto it = services.find(name);
    return it != services.end() ? it->second.category : "";
}