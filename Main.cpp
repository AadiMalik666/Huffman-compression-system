#include <iostream>
#include <memory>
#include <limits>
#include "FleetManager.h"
#include "Survey.h"
#include "Payment.h"
#include "Service.h"
#include "Ticket.h"
#include "Passenger.h"
#include "Admin.h"

using namespace std;


void displayMainMenu();
void passengerFlow(FleetManager& fleetManager);
void adminFlow();
void initializeSystem();

int main() {
    initializeSystem();
    FleetManager fleetManager;

    while (true) {
        displayMainMenu();
        int choice;
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input! Please enter a number.\n";
            continue;
        }

        cin.ignore();

        switch (choice) {
        case 1:
            passengerFlow(fleetManager);
            break;
        case 2:
            adminFlow();
            break;
        case 3:
            Survey::showOverallStats();
            break;
        case 4:
            cout << "Exiting system. Goodbye!\n";
            return 0;
        default:
            cout << "Invalid choice! Try again.\n";
        }
    }
}

void initializeSystem() {
    Ticket::initializeTicketSystem();
    Survey::loadFeedbackStats();
}

void displayMainMenu() {
    cout << "\n===== TRANSPORTATION BOOKING SYSTEM =====" << endl;
    cout << "1. Passenger Menu" << endl;
    cout << "2. Admin Login" << endl;
    cout << "3. View Survey Statistics" << endl;
    cout << "4. Exit" << endl;
    cout << "Enter your choice (1-4): ";
}

void passengerFlow(FleetManager& fleetManager) {
    
    unique_ptr<User> user = make_unique<User>();
    cout << "\n===== ACCOUNT =====" << endl;
    cout << "1. Login\n2. Signup\nChoice: ";

    int accountChoice;
    cin >> accountChoice;
    cin.ignore();

    if (accountChoice == 1) {
        if (!user->login()) return;
    }
    else if (accountChoice == 2) {
        user->signup();
    }
    else {
        cout << "Invalid choice!\n";
        return;
    }

    unique_ptr<Passenger> passenger(createPassengerByAge(0));
    passenger->getDetails();

    Service service(fleetManager);
    service.selectService();
    if (service.getServiceName().empty()) return;

    if (!fleetManager.reserveSeat(service.getServiceName(), passenger->seatClass)) {
        cout << "No seats available in " << passenger->seatClass << " class!\n";
        return;
    }

    Ticket ticket(passenger.get(), service, fleetManager);
    ticket.printTicket();

    Payment payment;
    payment.processPayment();

    ticket.saveTicketToUserFile(user->getUsername());

    char feedbackChoice;
    cout << "\nWould you like to provide feedback? (y/n): ";
    cin >> feedbackChoice;
    if (tolower(feedbackChoice) == 'y') {
        Survey survey;
        survey.collectFeedback();
        survey.displayResults();
        Survey::saveFeedbackStats();
    }

    cout << "\nBooking completed successfully!\n";
}

void adminFlow() {
    Admin admin;
    if (!admin.login()) return;

    while (true) {
        cout << "\n===== ADMIN MENU =====" << endl;
        cout << "1. View Dashboard\n";
        cout << "2. Manage Services\n";
        cout << "3. Export Analytics Report\n";
        cout << "4. Refresh Analytics\n";
        cout << "5. Logout\n";
        cout << "Choice: ";

        int choice;
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1:
            admin.showDashboard();
            break;
        case 2:
            admin.manageServices();
            break;
        case 3:
            admin.exportAnalyticsReport();
            cout << "Report exported to 'analytics_report.txt'\n";
            break;
        case 4:
            admin.refreshAnalytics();
            break;
        case 5:
            return;
        default:
            cout << "Invalid choice!\n";
        }
    }
}