#include "Survey.h"

int Survey::totalSurveys = 0;
vector<int> Survey::totalRatings(5, 0);

Survey::Survey() {
    ratings.resize(5);
    questions = {
        "Ease of Booking",
        "Clarity of Info",
        "Payment Process",
        "Support Service",
        "Overall Experience"
    };
}

void Survey::collectFeedback() {
    cout << "\n--- Please Rate Our Service (1-5) ---\n";
    for (size_t i = 0; i < questions.size(); ++i) {
        int rate;
        do {
            cout << questions[i] << ": ";
            cin >> rate;
            if (cin.fail() || rate < 1 || rate > 5) {
                cout << "Invalid rating. Enter number 1 to 5.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            else {
                break;
            }
        } while (true);

        ratings[i] = rate;
        totalRatings[i] += rate;
    }
    totalSurveys++;
}

void Survey::displayResults() {
    cout << "\n--- Your Feedback Summary ---\n";
    for (size_t i = 0; i < questions.size(); ++i) {
        cout << questions[i] << ": " << ratings[i] << "/5\n";
    }
}

void Survey::showOverallStats() {
    if (totalSurveys == 0) {
        cout << "\nNo surveys submitted yet.\n";
        return;
    }
    cout << "\n--- Overall Feedback Summary ---\n";
    for (size_t i = 0; i < totalRatings.size(); ++i) {
        double avg = static_cast<double>(totalRatings[i]) / totalSurveys;
        cout << "Q" << i + 1 << ": Avg Rating = " << fixed << setprecision(2) << avg << "/5\n";
    }
    cout << "Total Surveys: " << totalSurveys << "\n";
}

void Survey::loadFeedbackStats() {
    ifstream fin("feedback_stats.txt");
    if (fin.is_open()) {
        fin >> totalSurveys;
        for (size_t i = 0; i < totalRatings.size(); ++i) {
            fin >> totalRatings[i];
        }
        fin.close();
    }
}

void Survey::saveFeedbackStats() {
    ofstream fout("feedback_stats.txt");
    if (fout.is_open()) {
        fout << totalSurveys << endl;
        for (size_t i = 0; i < totalRatings.size(); ++i) {
            fout << totalRatings[i] << endl;
        }
        fout.close();
    }
    else {
        cout << "Warning: Unable to save feedback statistics to file.\n";
    }
}