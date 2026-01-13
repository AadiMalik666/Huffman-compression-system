#ifndef TICKET_H
#define TICKET_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include "Passenger.h"
#include "Service.h"
#include "FleetManager.h"

using namespace std;

class Ticket {
private:
    static int lastTicketID;
    string ticketID;
    Passenger* passenger;
    Service service;
    string status = "Confirmed";
    string cancelReason = "N/A";
    FleetManager& fleetManager; 

public:
    Ticket(Passenger* p, Service s, FleetManager& fm);
    static void initializeTicketSystem();
    static void loadLastTicketID();
    static void saveLastTicketID();
    static string generateTicketID();
    double getFinalPrice();
    void printTicket();
    void cancelTicket();
    string getTicketSummary();
    void saveTicketToUserFile(const string& username);
    string getTicketID() const;
};

#endif