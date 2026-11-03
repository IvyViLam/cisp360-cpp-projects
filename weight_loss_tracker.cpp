/*
 * Student Name: Vi Lam
 * Date: 07/12/2026
 * Assignment: Homework Assignment 2
 * Program Description: Maintaining a healthy weight can be challenging
   in today's busy world. This program helps users build a weight-loss
   plan by tracking calories consumed and calories burned through physical
   activities. By monitoring their progress, users can make healthier
   lifestyle choices and achieve their weight goals.
*/

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>
using namespace std;

// Function Prototypes
void ProgramGreeting();
double CalCaloriesCurr(float currWeight, int steps, string gender);
double calDeficit(double caloriesInput, double weightGoal, double caloriesPerPound);
double calWeightLoss(vector<double> calories);
void displaySummary(string userName, float currWeight, double caloriesBurned, double deficit, double weightLoss, vector<double> calories);

int main() {
    ProgramGreeting();

    const double CALORIES_PER_POUND = 3500.0;

    // Variables
    float currWeight;
    int steps;
    string userName;
    string gender;
    double weightGoal;

    // User inputs
    cout << "Enter your name: ";
    getline(cin, userName);
    cout << "Hello " << userName << "! Let's build your weight-loss plan!" << endl;

    cout << "Enter your gender (Male: M, Female: F): ";
    cin >> gender;

    // Validate gender input
    while (gender != "M" && gender != "m" && gender != "F" && gender != "f") {
    	cout << "Invalid input! Please enter M for Male or F for Female: ";
    	cin >> gender;
}


    cout << "Enter your current weight (lbs): ";
    cin >> currWeight;

    cout << "Enter how many steps you walk in a day: ";
    cin >> steps;


     cout << "Enter your weight loss goal per week (lbs): ";
     cin >> weightGoal;

    // Input validation for weight goal
     if (weightGoal > 2) {
        cout << " !!!  Warning: Safe weight loss is 1-2 lbs/week !!!" << endl;
        cout << "The maximum goal I can set is 4 lbs/week." << endl;
        cout << "Would you like to set it to 4 lbs/week?" << endl;
        cout << "Enter Y for Yes, N for No: ";

        char choice;
        cin >> choice;

        if (choice == 'Y' || choice == 'y') {
            weightGoal = 4.0;
            cout << "Goal set to 4 lbs/week!" << endl;
        }
        else {
            cout << "Sorry, I can't assist with that planning due to safety reasons." << endl;
            cout << "Thank you for using Weight Loss Tracker. Goodbye!" << endl;
            return 0;
        }
    }

    // Random number section
    srand(time(0));

    int bonusSteps = (rand() % 2001) + 1000;
    cout << "\nToday's bonus challenge: Walk an extra "
         << bonusSteps << " steps!" << endl;

    int msgNumber = (rand() % 5) + 1;
    if (msgNumber == 1) {
        cout << "     👏 One step at a time!" << endl;
    }
    else if (msgNumber == 2) {
        cout << "    ❤️  Choose health every day!" << endl;
    }
    else if (msgNumber == 3) {
        cout << "    🚀 Small changes, big results!" << endl;
    }
    else if (msgNumber == 4) {
        cout << "    🎯 Stay focused. Stay strong!" << endl;
    }
    else {
        cout << "    💯 The best project is you!" << endl;
    }

    // Function calls
    double caloriesBurned = CalCaloriesCurr(currWeight, steps, gender);
    double deficit = calDeficit(caloriesBurned, weightGoal, CALORIES_PER_POUND);

    // Vector - track deficit for each day
    vector<double> calories;
    calories.push_back(deficit);  // day 1
    calories.push_back(deficit);  // day 2
    calories.push_back(deficit);  // day 3
    calories.push_back(deficit);  // day 4
    calories.push_back(deficit);  // day 5
    calories.push_back(deficit);  // day 6
    calories.push_back(deficit);  // day 7

    // Calculate weight loss
    double weightLoss = calWeightLoss(calories);

    // Display summary
    displaySummary(userName, currWeight, caloriesBurned, deficit, weightLoss, calories);

    return 0;
}

// Function Definitions
void ProgramGreeting() {
    string programName = "Weight Loss Plan Tracker";
    string studentName = "Vi (Ivy) Lam";
    string programDescription = "Users can use this program to track their calories intake\nand develop an effective weight-loss plan based on their goals 🏆 🎉!!!";
    cout << "=====================================================" << endl;
    cout << "Welcome to " << programName << endl;
    cout << "By: " << studentName << endl;
    cout << "Introduction: " << programDescription << endl;
    cout << "-----------------------------------------------------" << endl;
}

double CalCaloriesCurr(float currWeight, int steps, string gender) {
    double caloriesBurned;
    double caloriesCurr;
    double caloriesoutput;

    caloriesBurned = static_cast<double>(steps) * currWeight * 0.0005;

    if (gender == "M" || gender == "m") {
        caloriesCurr = 11.0 * currWeight;
    }
    else if (gender == "F" || gender == "f") {
        caloriesCurr = 9.0 * currWeight;
    }

    caloriesoutput =abs(caloriesBurned - caloriesCurr);
    return caloriesoutput;
}

double calDeficit(double caloriesInput, double weightGoal, double caloriesPerPound) {
    double dailyDeficit;
    dailyDeficit = (weightGoal * caloriesPerPound) / 7.0;
    return dailyDeficit;
}

double calWeightLoss(vector<double> calories) {
    double total = 0;
    for (double cal : calories) {
        total += cal;
    }
    double weightLoss = total / 3500.0;
    return weightLoss;
}

void displaySummary(string userName, float currWeight, double caloriesBurned, double deficit, double weightLoss, vector<double> calories) {
    cout << fixed << setprecision(2);
    cout << "....................................................." << endl;
    cout << "         Weight Loss Plan Summary" << endl;
    cout << "....................................................." << endl;
    cout << setw(20) << left << "Name:" << userName << endl;
    cout << setw(20) << left << "Current Weight:" << currWeight << " lbs" << endl;
    cout << setw(20) << left << "Calories Burned:" << caloriesBurned << " cal" << endl;
    cout << setw(20) << left << "Daily Deficit:" << deficit << " cal" << endl;
    cout << setw(20) << left << "Projected Loss:" << weightLoss << " lbs" << endl;
    cout << setw(20) << left << "Days Tracked:" << calories.size() << " days" << endl;
    cout << "=====================================================" << endl;
    cout << "Please come back next week to track your progress!" << endl;
}
