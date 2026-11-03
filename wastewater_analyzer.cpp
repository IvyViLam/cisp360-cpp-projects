/*
 * Student Name: Vi Lam
 * Date: [Submission Date]
 * Assignment: Homework Assignment 3
 * Program Description: This program supports lab technicians
   in analyzing wastewater BOD and COD data, generating reports,
   and providing treatment recommendations 
 */

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;

// Named constants
const double BIODEGRADABLE_THRESHOLD = 0.5;
const double CRITICAL_THRESHOLD      = 40.0;

// Struct definition
struct Sample {
    string location;
    double bod;
    double cod;
};

// Prototypes
void ProgramGreeting();
void collectSamples(vector<Sample> &data);
double calcRatio(double bod, double cod);
double calcRemoval(double influent, double effluent);
double calcRemoval(double influent, double effluent, double tempFactor);
void showReport(const vector<Sample> &data);
string getTreatmentStatus(double removal, double threshold = 75.0);

int main() {
    ProgramGreeting();

    // Collect samples
    vector<Sample> samples;
    collectSamples(samples);

    // Menu
    int pick;
    do {
        cout << "\n================================" << endl;
        cout << "   Wastewater Analysis Menu  " << endl;
        cout << "================================" << endl;
        cout << "1. Calculate BOD/COD Ratio"      << endl;
        cout << "2. Calculate Removal Efficiency" << endl;
        cout << "3. View Sample Report"           << endl;
        cout << "4. Get Treatment Recommendation" << endl;
        cout << "5. Exit Program"                 << endl;
        cout << "================================" << endl;
        cout << "Enter your choice (1-5): ";
        cin  >> pick;

        if (pick == 1) {
            int index;
            cout << "Enter sample number (1-"
                 << samples.size() << "): ";
            cin  >> index;
            index--;

            if (index < 0 || index >= (int)samples.size()) {
                cout << "Invalid sample number!" << endl;
            } else {
                double ratio = calcRatio(samples[index].bod,
                                         samples[index].cod);
                cout << "\nLocation: "
                     << samples[index].location << endl;
                cout << "BOD/COD Ratio: "
                     << fixed << setprecision(2)
                     << ratio << endl;

                if (ratio > BIODEGRADABLE_THRESHOLD) {
                    cout << "Status: Biodegradable" << endl;
                } else if (ratio >= 0.3) {
                    cout << "Status: Moderate" << endl;
                } else {
                    cout << "Status: Non-biodegradable" << endl;
                }
            }

        } else if (pick == 2) {
            double influent, effluent;
            cout << "Enter influent COD (mg/L): ";
            cin  >> influent;
            cout << "Enter effluent COD (mg/L): ";
            cin  >> effluent;

            if (effluent > influent) {
                cout << "Warning: Effluent cannot "
                     << "exceed influent!" << endl;
            } else {
                int subChoice;
                cout << "\n1. Basic Removal Efficiency"      << endl;
                cout << "2. Temperature-Adjusted Efficiency" << endl;
                cout << "Enter choice: ";
                cin  >> subChoice;

                double result;
                if (subChoice == 1) {
                    result = calcRemoval(influent, effluent);
                    cout << "Removal Efficiency: "
                         << fixed << setprecision(2)
                         << result << "%" << endl;
                } else if (subChoice == 2) {
                    double tempFactor;
                    cout << "Enter temperature factor: ";
                    cin  >> tempFactor;
                    result = calcRemoval(influent, effluent,
                                        tempFactor);
                    cout << "Adjusted Efficiency: "
                         << fixed << setprecision(2)
                         << result << "%" << endl;
                } else {
                    cout << "Invalid choice!" << endl;
                }
            }

        } else if (pick == 3) {
            showReport(samples);

        } else if (pick == 4) {
            double removal;
            cout << "Enter removal efficiency (%): ";
            cin  >> removal;

            int subChoice;
            cout << "1. Use standard threshold (75%)" << endl;
            cout << "2. Enter custom threshold"       << endl;
            cout << "Enter choice: ";
            cin  >> subChoice;

            string status;
            if (subChoice == 1) {
                status = getTreatmentStatus(removal);
            } else {
                double custom;
                cout << "Enter custom threshold (%): ";
                cin  >> custom;
                status = getTreatmentStatus(removal, custom);
            }
            cout << "Treatment Status: " << status << endl;

        } else if (pick == 5) {
            cout << "Thank you for using "
                 << "Wastewater Treatment Report." << endl;
            cout << "Goodbye, Vi!" << endl;
        } else {
            cout << "Invalid choice. Please enter 1-5." << endl;
        }

    } while (pick != 5);

    return 0;
}

//Function Greeting - displays welcome screen and program purpose (shortcut than HW1, HW2)
void ProgramGreeting() {
    cout << "================================"  << endl;
    cout << " Welcome to Wastewater          " << endl;
    cout << "   Treatment Report             " << endl;
    cout << " By: Vi (Ivy) Lam               " << endl;
    cout << "================================"  << endl;
    cout << endl;
    cout << "This program supports lab technicians"     << endl;
    cout << "in analyzing wastewater BOD and COD data," << endl;
    cout << "and providing treatment recommendations."  << endl;
    cout << endl;
}

// Collect Samples - gathers BOD and COD readings into vector
void collectSamples(vector<Sample> &data) {
    int count;
    cout << "How many samples to enter? ";
    cin  >> count;

    // Input validation
    // Detects non-numeric input (e.g. letters, symbols)
    if (cin.fail()) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid input. Please enter a number." << endl;
        count = 0;
    }

    for (int i = 0; i < count; i++) {
        Sample s;
        cout << "\n--- Sample " << i + 1 << " ---" << endl;
        cin.ignore();
        cout << "Enter location name: ";
        getline(cin, s.location);
        cout << "Enter BOD (mg/L): ";
        cin  >> s.bod;
        cout << "Enter COD (mg/L): ";
        cin  >> s.cod;
        data.push_back(s);
    }
    cout << "\nAll wastewater samples recorded!" << endl;
}

// Calculator Ratio - returns BOD divided by COD value
double calcRatio(double bod, double cod) {
    return bod / cod;
}

double calcRemoval(double influent, double effluent) {
    return (influent - effluent) / influent * 100;
}

double calcRemoval(double influent, double effluent,
                   double tempFactor) {
    return ((influent - effluent) / influent * 100) * tempFactor;
}

// Show Report - displays formatted table of all samples
void showReport(const vector<Sample> &data) {
    cout << "\n===========================================" << endl;
    cout << "         Sample Report                " << endl;
    cout << "===========================================" << endl;

    cout << left
         << setw(15) << "Location"
         << setw(12) << "BOD(mg/L)"
         << setw(12) << "COD(mg/L)"
         << setw(10) << "Ratio"
         << endl;
    cout << "--------------------------------------------" << endl;

    for (int i = 0; i < (int)data.size(); i++) {
        cout << fixed << setprecision(2);
        cout << left
             << setw(15) << data[i].location
             << setw(12) << data[i].bod
             << setw(12) << data[i].cod
             << setw(10) << data[i].bod / data[i].cod
             << endl;
    }

    // Averages with static_cast
    int count       = (int)data.size();
    double totalBOD = 0.0;
    double totalCOD = 0.0;

    for (int i = 0; i < count; i++) {
        totalBOD += data[i].bod;
        totalCOD += data[i].cod;
    }

    double avgBOD = totalBOD / static_cast<double>(count);
    double avgCOD = totalCOD / static_cast<double>(count);

    cout << "-------------------------------------------" << endl;
    cout << fixed << setprecision(2);
    cout << left
         << setw(15) << "Average"
         << setw(12) << avgBOD
         << setw(12) << avgCOD
         << endl;
    cout << "===========================================" << endl;
}

// Get Treatment Status - evaluates removal efficiency against threshold
string getTreatmentStatus(double removal, double threshold) {
    if (removal >= threshold) {
        return "Good";
    } else if (removal >= CRITICAL_THRESHOLD) {
        return "Needs Treatment";
    } else {
        return "Critical";
    }
}
