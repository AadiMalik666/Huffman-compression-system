#ifndef SURVEY_H
#define SURVEY_H

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <limits>

using namespace std;

class Survey {
private:
    vector<int> ratings;
    vector<string> questions;

public:
    static int totalSurveys;
    static vector<int> totalRatings;

    Survey();
    void collectFeedback();
    void displayResults();
    static void showOverallStats();
    static void loadFeedbackStats();
    static void saveFeedbackStats();
};

#endif