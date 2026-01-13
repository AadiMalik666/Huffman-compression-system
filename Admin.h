#ifndef ADMIN_H
#define ADMIN_H

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <iomanip>
#include <ctime>
#include "User.h"
#include "FleetManager.h"

using namespace std;

struct SystemAnalytics {
    int totalTickets = 0;
    int cancelledTickets = 0;
    int confirmedTickets = 0;
    int totalFeedbacks = 0;
    map<string, int> serviceCount;
    double averageRatings[5] = { 0.0 };

    SystemAnalytics();
};

class Admin : public User {
private:
    SystemAnalytics analytics;
    FleetManager fleetManager;

public:
    Admin();
    bool login() override;
    void loadAnalytics();
    void loadTicketStats();
    void loadFeedbackStats();
    string getMostPopularService() const;
    void showDashboard() const;
    void exportAnalyticsReport() const;
    void refreshAnalytics();
    void manageServices();
    void addNewService();
    void removeService();
    void viewSeatAvailability() const;
};

#endif