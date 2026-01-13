#include "Ticket.h"

int Ticket::lastTicketID = 0;

void Ticket::loadLastTicketID() {
    ifstream fin("ticket_id.txt");
    if (fin.is_open()) {
        fin >> lastTicketID;
        fin.close();
    }
    else {
        lastTicketID = 0;
    }
}

void Ticket::saveLastTicketID() {
    ofstream fout("ticket_id.txt");
    if (fout.is_open()) {
        fout << lastTicketID << endl;
        fout.close();
    }
    else {
        cout << "Warning: Unable to save ticket ID to file.\n";
    }
}

string Ticket::generateTicketID() {
    lastTicketID++;
    saveLastTicketID();

    stringstream ss;
    ss << "TK-" << setfill('0') << setw(4) << lastTicketID;
    return ss.str();
}

Ticket::Ticket(Passenger* p, Service s, FleetManager& fm)
    : passenger(p), service(s), fleetManager(fm) {
    ticketID = generateTicketID();
}

void Ticket::initializeTicketSystem() {
    loadLastTicketID();
}

double Ticket::getFinalPrice() {
    return passenger->calculateFare(service.getPrice());
}

void Ticket::printTicket() {
    cout << "\n========= TICKET =========\n";
    cout << "Ticket ID: " << ticketID << endl;
    cout << "Name: " << passenger->name << endl;
    cout << "Age: " << passenger->age << endl;
    cout << "Email: " << passenger->email << endl;
    cout << "Transport: " << service.getServiceName() << endl;
    cout << "Class: " << passenger->seatClass << endl;
    cout << "Departure: " << service.getDeparture() << "  Arrival: " << service.getArrival() << endl;
    cout << "Category: " << service.getCategory() << endl;
    cout << "Original Price: Rs. " << fixed << setprecision(2) << service.getPrice() << endl;

    double finalPrice = getFinalPrice();
    double discount = service.getPrice() - finalPrice;
    if (discount < 0) {
        cout << "Class Premium: Rs. " << fixed << setprecision(2) << -discount << endl;
    }
    else if (discount > 0) {
        double discountPercentage = (discount / service.getPrice()) * 100;
        cout << "Discount: Rs. " << fixed << setprecision(2) << discount
            << " (" << fixed << setprecision(1) << discountPercentage << "%)" << endl;
    }

    cout << "Final Price: Rs. " << fixed << setprecision(2) << finalPrice << endl;
    cout << "Status: " << status << endl;
    if (status == "Cancelled") {
        cout << "Reason: " << cancelReason << endl;
    }
    cout << "==========================\n";
}

void Ticket::cancelTicket() {
    if (status == "Cancelled") {
        cout << "Ticket already cancelled.\n";
        return;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Enter reason for cancellation: ";
    getline(cin, cancelReason);
    status = "Cancelled";

    fleetManager.reserveSeat(service.getServiceName(), passenger->seatClass, true);
    cout << "Ticket " << ticketID << " cancelled successfully.\n";
}

string Ticket::getTicketSummary() {
    return ticketID + "|" +
        passenger->name + "|" +
        to_string(passenger->age) + "|" +
        passenger->email + "|" +
        service.getServiceName() + "|" +
        service.getDeparture() + "|" +
        service.getArrival() + "|" +
        to_string(service.getPrice()) + "|" +
        service.getCategory() + "|" +
        passenger->seatClass + "|" +
        status;
}

void Ticket::saveTicketToUserFile(const string& username) {
    string filename = username + "_tickets.txt";
    ofstream fout(filename, ios::app);
    if (fout.is_open()) {
        fout << getTicketSummary() << "\n";
        fout.close();
    }
    else {
        cout << "Warning: Unable to save ticket to user history file.\n";
    }
}

string Ticket::getTicketID() const {
    return ticketID;
}