#include "Admin.h"
#include <sstream>
#include <string>

SystemAnalytics::SystemAnalytics() :
    totalTickets(0),
    cancelledTickets(0),
    confirmedTickets(0),
    totalFeedbacks(0) {
    for (int i = 0; i < 5; i++) {
        averageRatings[i] = 0.0;
    }
}

Admin::Admin() : fleetManager() {
    username = "admin";
    password = "admin123";
}

bool Admin::login() {
    bool loginSuccess = User::login();
    if (loginSuccess) {
        loadAnalytics();
    }
    return loginSuccess;
}

void Admin::loadAnalytics() {
    loadTicketStats();
    loadFeedbackStats();
}

void Admin::loadTicketStats() {
    ifstream userFile("users.dat");
    if (!userFile.is_open()) return;

    string username, password;
    while (userFile >> username >> password) {
        string ticketFile = username + "_tickets.txt";
        ifstream fin(ticketFile);
        if (!fin.is_open()) continue;

        string line;
        while (getline(fin, line)) {
            if (line.empty()) continue;

            stringstream ss(line);
            string ticketID, name, service, status;
            string temp;

            getline(ss, ticketID, '|');
            getline(ss, name, '|');
            getline(ss, temp, '|');
            getline(ss, temp, '|');
            getline(ss, service, '|');
            getline(ss, temp, '|');
            getline(ss, temp, '|');
            getline(ss, temp, '|');
            getline(ss, temp, '|');
            getline(ss, status);

            analytics.totalTickets++;
            if (status == "Cancelled") {
                analytics.cancelledTickets++;
            }
            else {
                analytics.confirmedTickets++;
            }

            if (!service.empty()) {
                analytics.serviceCount[service]++;
            }
        }
        fin.close();
    }
    userFile.close();
}

void Admin::loadFeedbackStats() {
    ifstream fin("feedback_stats.txt");
    if (!fin.is_open()) return;

    int totalSurveys;
    vector<int> totalRatings(5);

    fin >> totalSurveys;
    for (int i = 0; i < 5; i++) {
        fin >> totalRatings[i];
    }
    fin.close();

    analytics.totalFeedbacks = totalSurveys;
    if (totalSurveys > 0) {
        for (int i = 0; i < 5; i++) {
            analytics.averageRatings[i] = static_cast<double>(totalRatings[i]) / totalSurveys;
        }
    }
}

string Admin::getMostPopularService() const {
    string mostPopular = "None";
    int maxCount = 0;

    for (const auto& pair : analytics.serviceCount) {
        if (!pair.first.empty() && pair.second > maxCount) {
            maxCount = pair.second;
            mostPopular = pair.first;
        }
    }

    return maxCount == 0 ? "No bookings yet" : mostPopular + " (" + to_string(maxCount) + " bookings)";
}

void Admin::showDashboard() const {
    cout << "\n" << string(60, '=') << endl;
    cout << "               ADMIN DASHBOARD - ANALYTICS" << endl;
    cout << string(60, '=') << endl;

    cout << "\nTICKET STATISTICS:" << endl;
    cout << string(40, '-') << endl;
    cout << "Total Tickets Booked    : " << analytics.totalTickets << endl;
    cout << "Confirmed Tickets       : " << analytics.confirmedTickets << endl;
    cout << "Cancelled Tickets       : " << analytics.cancelledTickets << endl;

    if (analytics.totalTickets > 0) {
        double cancellationRate = (static_cast<double>(analytics.cancelledTickets) / analytics.totalTickets) * 100;
        cout << "Cancellation Rate       : " << fixed << setprecision(1) << cancellationRate << "%" << endl;
    }

    cout << "\nSERVICE POPULARITY:" << endl;
    cout << string(40, '-') << endl;
    cout << "Most Popular Service    : " << getMostPopularService() << endl;
    cout << "\nDetailed Breakdown:" << endl;
    for (const auto& pair : analytics.serviceCount) {
        double percentage = analytics.totalTickets > 0 ?
            (static_cast<double>(pair.second) / analytics.totalTickets) * 100 : 0.0;
        cout << "  " << left << setw(20) << pair.first << ": "
            << right << setw(3) << pair.second << " bookings ("
            << fixed << setprecision(1) << percentage << "%)" << endl;
    }

    cout << "\nCUSTOMER FEEDBACK ANALYTICS:" << endl;
    cout << string(40, '-') << endl;
    cout << "Total Feedback Surveys  : " << analytics.totalFeedbacks << endl;

    if (analytics.totalFeedbacks > 0) {
        vector<string> categories = {
            "Ease of Booking", "Clarity of Info", "Payment Process",
            "Support Service", "Overall Experience"
        };

        cout << "\nAverage Ratings (out of 5):" << endl;
        double overallAvg = 0.0;
        for (int i = 0; i < 5; i++) {
            cout << "  " << left << setw(20) << categories[i] << ": "
                << fixed << setprecision(2) << analytics.averageRatings[i] << "/5.00" << endl;
            overallAvg += analytics.averageRatings[i];
        }

        overallAvg /= 5.0;
        cout << "\n  " << left << setw(20) << "OVERALL AVERAGE" << ": "
            << fixed << setprecision(2) << overallAvg << "/5.00" << endl;

        cout << "\nPerformance Indicator: ";
        if (overallAvg >= 4.5) cout << "EXCELLENT";
        else if (overallAvg >= 4.0) cout << "GOOD";
        else if (overallAvg >= 3.0) cout << "AVERAGE";
        else cout << "NEEDS IMPROVEMENT";
        cout << endl;
    }
    else {
        cout << "No feedback surveys submitted yet." << endl;
    }

    cout << "\n" << string(60, '=') << endl;
}

void Admin::exportAnalyticsReport() const {
    ofstream fout("analytics_report.txt");
    if (!fout.is_open()) {
        cout << "Failed to create analytics report file." << endl;
        return;
    }

    time_t now = time(nullptr);
    tm timeinfo;
    localtime_s(&timeinfo, &now);
    char timeStr[100];
    strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S", &timeinfo);

    fout << "SMARTTICKET+ SYSTEM ANALYTICS REPORT" << endl;
    fout << "Generated on: " << timeStr << endl;
    fout << string(50, '=') << endl << endl;

    fout << "TICKET STATISTICS:" << endl;
    fout << string(40, '-') << endl;
    fout << "Total Tickets Booked    : " << analytics.totalTickets << endl;
    fout << "Confirmed Tickets       : " << analytics.confirmedTickets << endl;
    fout << "Cancelled Tickets       : " << analytics.cancelledTickets << endl;

    if (analytics.totalTickets > 0) {
        double cancellationRate = (static_cast<double>(analytics.cancelledTickets) / analytics.totalTickets) * 100;
        fout << "Cancellation Rate       : " << fixed << setprecision(1) << cancellationRate << "%" << endl;
    }

    fout << "\nSERVICE POPULARITY:" << endl;
    fout << string(40, '-') << endl;
    fout << "Most Popular Service    : " << getMostPopularService() << endl;
    fout << "\nDetailed Breakdown:" << endl;
    for (const auto& pair : analytics.serviceCount) {
        double percentage = analytics.totalTickets > 0 ?
            (static_cast<double>(pair.second) / analytics.totalTickets) * 100 : 0.0;
        fout << "  " << left << setw(20) << pair.first << ": "
            << right << setw(3) << pair.second << " bookings ("
            << fixed << setprecision(1) << percentage << "%)" << endl;
    }

    fout << "\nCUSTOMER FEEDBACK ANALYTICS:" << endl;
    fout << string(40, '-') << endl;
    fout << "Total Feedback Surveys  : " << analytics.totalFeedbacks << endl;

    if (analytics.totalFeedbacks > 0) {
        vector<string> categories = {
            "Ease of Booking", "Clarity of Info", "Payment Process",
            "Support Service", "Overall Experience"
        };

        fout << "\nAverage Ratings (out of 5):" << endl;
        double overallAvg = 0.0;
        for (int i = 0; i < 5; i++) {
            fout << "  " << left << setw(20) << categories[i] << ": "
                << fixed << setprecision(2) << analytics.averageRatings[i] << "/5.00" << endl;
            overallAvg += analytics.averageRatings[i];
        }

        overallAvg /= 5.0;
        fout << "\n  " << left << setw(20) << "OVERALL AVERAGE" << ": "
            << fixed << setprecision(2) << overallAvg << "/5.00" << endl;

        fout << "\nPerformance Indicator: ";
        if (overallAvg >= 4.5) fout << "EXCELLENT";
        else if (overallAvg >= 4.0) fout << "GOOD";
        else if (overallAvg >= 3.0) fout << "AVERAGE";
        else fout << "NEEDS IMPROVEMENT";
        fout << endl;
    }

    fout.close();
}

void Admin::refreshAnalytics() {
    analytics = SystemAnalytics();
    loadAnalytics();
    cout << "\nAnalytics data refreshed successfully!" << endl;
}

void Admin::manageServices() {
    int option;
    do {
        cout << "\n" << string(60, '=') << endl;
        cout << "               SERVICE MANAGEMENT" << endl;
        cout << string(60, '=') << endl;

        fleetManager.showAllServices();

        cout << "\n1. Add New Service\n";
        cout << "2. Remove Service\n";
        cout << "3. View Seat Availability\n";
        cout << "4. Back to Main Menu\n";
        cout << "Choice: ";
        cin >> option;

        switch (option) {
        case 1: addNewService(); break;
        case 2: removeService(); break;
        case 3: viewSeatAvailability(); break;
        }
    } while (option != 4);
}

void Admin::addNewService() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    string name, departure, arrival, category;
    double price;
    int businessSeats, standardSeats;

    cout << "\nEnter Service Name: ";
    getline(cin, name);
    cout << "Enter Departure Time (HH:MM): ";
    getline(cin, departure);
    cout << "Enter Arrival Time (HH:MM): ";
    getline(cin, arrival);
    cout << "Enter Base Price: ";
    cin >> price;
    cin.ignore();
    cout << "Enter Category: ";
    getline(cin, category);
    cout << "Enter Business Class Seats: ";
    cin >> businessSeats;
    cout << "Enter Standard Class Seats: ";
    cin >> standardSeats;

    fleetManager.addService(name, departure, arrival, price, category,
        { {"business", businessSeats}, {"standard", standardSeats} });

    cout << "\nService added successfully!\n";
    cout << "Press Enter to continue...";
    cin.ignore();
    cin.get();
}

void Admin::removeService() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    string name;
    cout << "\nEnter Service Name to Remove: ";
    getline(cin, name);

    if (fleetManager.removeService(name)) {
        cout << "Service removed successfully.\n";
    }
    else {
        cout << "Service not found.\n";
    }

    cout << "Press Enter to continue...";
    cin.ignore();
    cin.get();
}

void Admin::viewSeatAvailability() const {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    string name;
    cout << "\nEnter Service Name: ";
    getline(cin, name);
    fleetManager.showAvailableSeats(name);
    cout << "Press Enter to continue...";
    cin.ignore();
    cin.get();
}