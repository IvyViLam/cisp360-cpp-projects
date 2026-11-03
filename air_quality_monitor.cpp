/*
 * Student Name: Vi Lam
 * Date: 07/26/2026
 * Assignment: Homework Assignment 7
 * Program Description: Sacramento frequently experiences
 * poor air quality due to wildfires, traffic, and valley
 * geography. This program helps monitor and alert residents
 * about daily air quality conditions.
 */

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <limits>
#include <algorithm>
using namespace std;

// Named constants
const int AQI_GOOD      = 50;  // Good threshold
const int AQI_MODERATE  = 100; // Moderate threshold
const int AQI_SENSITIVE = 150; // Sensitive threshold
const int AQI_UNHEALTHY = 200; // Unhealthy threshold
const int AQI_VERY_BAD  = 300; // Very unhealthy
const int AQI_MAX       = 500; // Maximum AQI
const int ZONES         = 3;   // Pollution zones
const int POLLUTANTS    = 4;   // Types of pollutants

// Prototypes
void programGreeting();
void demonstratePointer();
void updateAQIReading(double *aqiPtr, double newValue);
void dynamicScalarDemo();
void dynamicArrayDemo();
void collectWeeklyAQI(vector<int> &readings);
void displayWeeklyAQI(const vector<int> &readings);
void collectZoneData(vector<vector<int>> &grid);
void displayZoneGrid(const vector<vector<int>> &grid);
void displayBarGraph(const vector<int> &readings);
void applyAQIAlert(int &currentAQI,
                   string &alertLevel);

int main() {
    programGreeting();

    // Collect owner name
    string ownerName  = "";
    string alertLevel = "NORMAL";
    double currentAQI = 0.0;

    cout << "\n--- Owner Information ---"        << endl;
    cout << "Enter your full name: ";
    getline(cin, ownerName);

    // Declare vector and 2D vector
    vector<int>         weeklyReadings;
    vector<vector<int>> zoneGrid;

    int choice;
    do {
        cout << "\n=============================" << endl;
        cout << "  Sacramento Air Monitor      " << endl;
        cout << "-----------------------------" << endl;
        cout << "  Owner: " << ownerName         << endl;
        cout << "  AQI:   " << currentAQI
             << " | "       << alertLevel        << endl;
        cout << "=============================" << endl;
        cout << "1. Pointer Demonstration"      << endl;
        cout << "2. Enter Sensor Reading"       << endl;
        cout << "3. Dynamic Array Management"   << endl;
        cout << "4. Enter Weekly Readings"      << endl;
        cout << "5. View Weekly Report"         << endl;
        cout << "6. View Zone Grid"             << endl;
        cout << "7. View AQI Bar Graph"         << endl;
        cout << "8. Apply AQI Alert"            << endl;
        cout << "9. Exit"                       << endl;
        cout << "=============================" << endl;
        cout << "Enter choice (1-9): ";
        cin  >> choice;
        cin.ignore(1000, '\n');

        // Validate menu choice
        while (cin.fail() ||
               choice < 1 || choice > 9) {
            if (cin.fail()) {
                cin.clear();
                cin.ignore(
                    numeric_limits<streamsize>::max(),
                    '\n');
            }
            cout << "Invalid! Please enter 1-9." << endl;
            cout << "Enter choice (1-9): ";
            cin  >> choice;
            cin.ignore(1000, '\n');
        }

        switch (choice) {
            case 1:
                demonstratePointer();
                break;

            case 2:
                cout << "Before update: "
                     << currentAQI               << endl;
                updateAQIReading(&currentAQI,
                                 142.0);
                cout << "After update:  "
                     << currentAQI               << endl;
                break;

            case 3:
                dynamicScalarDemo();
                dynamicArrayDemo();
                break;

            case 4:
                weeklyReadings.clear();
                collectWeeklyAQI(weeklyReadings);
                break;

            case 5:
                if (weeklyReadings.empty()) {
                    cout << "No readings yet!"   << endl;
                } else {
                    displayWeeklyAQI(weeklyReadings);
                }
                break;

            case 6:
                if (zoneGrid.empty()) {
                    collectZoneData(zoneGrid);
                }
                displayZoneGrid(zoneGrid);
                break;

            case 7:
                if (weeklyReadings.empty()) {
                    cout << "No readings yet!"   << endl;
                } else {
                    displayBarGraph(weeklyReadings);
                }
                break;

            case 8: {
                int aqiInt = (int)currentAQI;
                cout << "Before alert: "
                     << aqiInt                   << endl;
                cout << "Level:        "
                     << alertLevel               << endl;
                applyAQIAlert(aqiInt, alertLevel);
                currentAQI = aqiInt;
                cout << "After alert:  "
                     << currentAQI               << endl;
                cout << "Level:        "
                     << alertLevel               << endl;
                break;
            }

            case 9:
                cout << "Thank you "
                     << ownerName << "!"         << endl;
                cout << "Stay safe and monitor"  << endl;
                cout << "your air quality!"      << endl;
                cout << "Goodbye!"               << endl;
                break;

            default:
                cout << "Invalid choice!"        << endl;
                break;
        }
    } while (choice != 9);

    return 0;
}

// Function Greeting - displays welcome screen
void programGreeting() {
    cout << "=========================================" << endl;
    cout << "  Sacramento Air Quality Monitor         " << endl;
    cout << "  By: Vi (Ivy) Lam                      " << endl;
    cout << "=========================================" << endl;
    cout << endl;
    cout << "Sacramento frequently experiences poor"   << endl;
    cout << "air quality due to wildfires, traffic,"  << endl;
    cout << "and valley geography. This program helps" << endl;
    cout << "monitor and alert residents about daily"  << endl;
    cout << "air quality conditions."                  << endl;
    cout << endl;
}

// Demonstrate Pointer - Task 1
void demonstratePointer() {
    // Task 1.1 - declare theme-related variable
    double aqiReading = 75.0;

    // Task 1.2 - declare pointer initialized to nullptr
    double *aqiPtr = nullptr;

    // Task 1.3 - assign address to pointer
    aqiPtr = &aqiReading;

    // Task 1.4 - display value and address
    cout << "\n--- Pointer Demonstration ---"      << endl;
    cout << "AQI Reading:   " << aqiReading        << endl;
    cout << "Memory Address:" << aqiPtr             << endl;

    // Task 1.5 - modify through pointer
    *aqiPtr = 125.5;
    cout << "Updated AQI:   " << aqiReading         << endl;
}

// Update AQI Reading - pointer function parameter
void updateAQIReading(double *aqiPtr,
                      double newValue) {
    // Task 2.4 - check not nullptr
    if (aqiPtr != nullptr) {
        // Task 2.5 - modify through pointer
        *aqiPtr = newValue;
        cout << "\nAQI updated successfully!"      << endl;
        cout << "New AQI reading: "
             << *aqiPtr                            << endl;
    } else {
        cout << "Error: Null pointer!"             << endl;
    }
}

// Dynamic Scalar Demo - Task 3
void dynamicScalarDemo() {
    // Task 3.1 - declare pointer
    double *sensorReading = nullptr;

    // Task 3.2 - allocate with new
    sensorReading = new double;

    // Task 3.3 - store validated user input
    bool valid = false;
    while (!valid) {
        cout << "Enter sensor AQI (0-500): ";
        cin  >> *sensorReading;
        cin.ignore(1000, '\n');

        if (cin.fail()) {
            cin.clear();
            cin.ignore(
                numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid! Enter a number."     << endl;
        } else if (*sensorReading >= 0 &&
                   *sensorReading <= AQI_MAX) {
            valid = true;
        } else {
            cout << "Error: AQI must be 0-500!"    << endl;
        }
    }

    // Task 3.4 - check nullptr and display
    if (sensorReading != nullptr) {
        cout << "Sensor reading: "
             << *sensorReading                     << endl;
    }

    // Task 3.5 - delete and set nullptr
    delete sensorReading;
    sensorReading = nullptr;
    cout << "Memory released!"                     << endl;
}

// Dynamic Array Demo - Task 4
void dynamicArrayDemo() {
    // Task 4.1 - declare pointer and size
    int  size     = 3;
    int *aqiArray = new int[size];

    // Task 4.2 - store values and display
    cout << "\n--- Dynamic AQI Array ---"          << endl;
    cout << "Enter " << size
         << " AQI readings:"                       << endl;

    for (int i = 0; i < size; i++) {
        bool valid = false;
        while (!valid) {
            cout << "Reading " << i + 1 << ": ";
            cin  >> aqiArray[i];
            cin.ignore(1000, '\n');

            if (cin.fail()) {
                cin.clear();
                cin.ignore(
                    numeric_limits<streamsize>::max(),
                    '\n');
                cout << "Invalid!"                 << endl;
            } else if (aqiArray[i] >= 0 &&
                       aqiArray[i] <= AQI_MAX) {
                valid = true;
            } else {
                cout << "Error: 0-500!"            << endl;
            }
        }
    }

    // Display initial array
    cout << "\nInitial array:"                     << endl;
    for (int i = 0; i < size; i++) {
        cout << "Reading " << i + 1 << ": "
             << aqiArray[i]                        << endl;
    }

    // Task 4.3 - get new size
    int  newSize   = 0;
    bool validSize = false;
    while (!validSize) {
        cout << "\nEnter new array size (>"
             << size << "): ";
        cin  >> newSize;
        cin.ignore(1000, '\n');

        if (cin.fail()) {
            cin.clear();
            cin.ignore(
                numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid!"                     << endl;
        } else if (newSize > size) {
            validSize = true;
        } else {
            cout << "Error: Must be > "
                 << size                           << endl;
        }
    }

    // Allocate temporary array
    int *temp = new int[newSize];

    // Task 4.4 - copy old elements
    for (int i = 0; i < size; i++) {
        temp[i] = aqiArray[i];
    }

    // Initialize new elements
    for (int i = size; i < newSize; i++) {
        bool valid = false;
        while (!valid) {
            cout << "New reading " << i + 1
                 << ": ";
            cin  >> temp[i];
            cin.ignore(1000, '\n');

            if (cin.fail()) {
                cin.clear();
                cin.ignore(
                    numeric_limits<streamsize>::max(),
                    '\n');
                cout << "Invalid!"                 << endl;
            } else if (temp[i] >= 0 &&
                       temp[i] <= AQI_MAX) {
                valid = true;
            } else {
                cout << "Error: 0-500!"            << endl;
            }
        }
    }

    // Release original array
    delete[] aqiArray;
    aqiArray = temp;
    size     = newSize;
    temp     = nullptr;

    // Task 4.5 - display resized array
    cout << "\nResized array ("
         << size << " readings):"                  << endl;
    for (int i = 0; i < size; i++) {
        cout << "Reading " << i + 1 << ": "
             << aqiArray[i]                        << endl;
    }

    // Release final array
    delete[] aqiArray;
    aqiArray = nullptr;
    cout << "Dynamic array released!"              << endl;
}

// Collect Weekly AQI - fills vector
void collectWeeklyAQI(vector<int> &readings) {
    cout << "\n--- Enter Weekly AQI Readings ---"  << endl;
    cout << "Enter 7 daily AQI values."            << endl;

    for (int i = 0; i < 7; i++) {
        int  aqi   = 0;
        bool valid = false;

        while (!valid) {
            cout << "Day " << i + 1
                 << " AQI (0-500): ";
            cin  >> aqi;
            cin.ignore(1000, '\n');

            if (cin.fail()) {
                cin.clear();
                cin.ignore(
                    numeric_limits<streamsize>::max(),
                    '\n');
                cout << "Invalid! Enter a number." << endl;
            } else if (aqi >= 0 && aqi <= AQI_MAX) {
                readings.push_back(aqi);
                valid = true;
            } else {
                cout << "Error: AQI must be 0-500!" << endl;
            }
        }
    }
    cout << "Weekly readings recorded!"             << endl;
}

// Display Weekly AQI - vector with loops
void displayWeeklyAQI(const vector<int> &readings) {
    vector<string> days = {"Mon", "Tue", "Wed",
                           "Thu", "Fri", "Sat",
                           "Sun"};

    cout << "\n--- Weekly AQI Report ---"           << endl;

    // Range-based for - display all
    int day = 1;
    for (int r : readings) {
        cout << "Day " << day << ": "
             << r << " AQI"                        << endl;
        day++;
    }

    // Index-based for with .at() - find unhealthy days
    cout << "\n--- Unhealthy Days ---"              << endl;
    int unhealthyCount = 0;
    for (int i = 0; i < (int)readings.size(); i++) {
        if (readings.at(i) > AQI_MODERATE) {
            unhealthyCount++;
            cout << "Day " << i + 1
                 << ": " << readings.at(i)
                 << " AQI - Unhealthy!"            << endl;
        }
    }

    // Calculate results
    int total   = 0;
    int highest = readings.at(0);
    int lowest  = readings.at(0);

    for (int r : readings) {
        total += r;
        if (r > highest) highest = r;
        if (r < lowest)  lowest  = r;
    }

    double average = static_cast<double>(total) /
                     static_cast<double>(readings.size());

    cout << fixed << setprecision(1);
    cout << "\nWeekly Statistics:"                  << endl;
    cout << "Total AQI:       " << total            << endl;
    cout << "Average AQI:     " << average          << endl;
    cout << "Highest AQI:     " << highest          << endl;
    cout << "Lowest AQI:      " << lowest           << endl;
    cout << "Unhealthy days:  " << unhealthyCount   << endl;
}

// Collect Zone Data - fills 2D vector
void collectZoneData(vector<vector<int>> &grid) {
    vector<string> zones = {"Downtown  ",
                            "Suburbs   ",
                            "Industrial"};

    vector<string> pollutants = {"PM2.5",
                                 "Ozone",
                                 "CO   ",
                                 "NO2  "};

    cout << "\n--- Enter Pollution Zone Data ---"   << endl;

    for (int z = 0; z < ZONES; z++) {
        vector<int> row;
        cout << "\nZone: " << zones[z]              << endl;

        for (int p = 0; p < POLLUTANTS; p++) {
            int  val   = 0;
            bool valid = false;

            while (!valid) {
                cout << pollutants[p]
                     << " AQI (0-500): ";
                cin  >> val;
                cin.ignore(1000, '\n');

                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(
                        numeric_limits<streamsize>::max(),
                        '\n');
                    cout << "Invalid!"              << endl;
                } else if (val >= 0 &&
                           val <= AQI_MAX) {
                    valid = true;
                } else {
                    cout << "Error: 0-500!"         << endl;
                }
            }
            row.push_back(val);
        }
        grid.push_back(row);
    }
    cout << "\nZone data recorded!"                 << endl;
}

// Display Zone Grid - 2D vector with nested loops
void displayZoneGrid(
        const vector<vector<int>> &grid) {
    vector<string> zones = {"Downtown  ",
                            "Suburbs   ",
                            "Industrial"};

    cout << "\n--- Pollution Zone Grid ---"         << endl;
    cout << "+------------+-------+-------+"
         << "-------+-------+-------+"              << endl;
    cout << "| Zone       | PM2.5 | Ozone "
         << "| CO    | NO2   | Total |"             << endl;
    cout << "+------------+-------+-------+"
         << "-------+-------+-------+"              << endl;

    // Column totals
    vector<int> colTotals(POLLUTANTS, 0);

    // Nested loops with .at()
    for (int z = 0; z < ZONES; z++) {
        int rowTotal = 0;
        cout << "| " << left << setw(10)
             << zones[z] << " |";

        for (int p = 0; p < POLLUTANTS; p++) {
            cout << right << setw(5)
                 << grid.at(z).at(p) << " |";
            rowTotal     += grid.at(z).at(p);
            colTotals[p] += grid.at(z).at(p);
        }
        cout << right << setw(5)
             << rowTotal << " |"                    << endl;
    }

    cout << "+------------+-------+-------+"
         << "-------+-------+-------+"              << endl;

    // Display column totals
    cout << "| " << left << setw(10)
         << "TOTAL" << " |";
    for (int p = 0; p < POLLUTANTS; p++) {
        cout << right << setw(5)
             << colTotals[p] << " |";
    }
    cout << "       |"                              << endl;
    cout << "+------------+-------+-------+"
         << "-------+-------+-------+"              << endl;
}

// Display Bar Graph - text based
void displayBarGraph(
        const vector<int> &readings) {
    vector<string> days = {"Mon", "Tue", "Wed",
                           "Thu", "Fri", "Sat",
                           "Sun"};

    cout << "\n=============================="     << endl;
    cout << "  Sacramento AQI Bar Graph"          << endl;
    cout << "  Each * = 10 AQI units"            << endl;
    cout << "=============================="      << endl;

    // Outer loop - process each category
    for (int i = 0; i < (int)readings.size(); i++) {
        int bars = readings.at(i) / 10;

        // Label and value
        cout << left << setw(4) << days[i]
             << " | ";

        // Inner loop - print bars
        for (int b = 0; b < bars; b++) {
            cout << "*";
        }

        // Show numeric value
        cout << " " << readings.at(i)             << endl;
    }

    cout << "=============================="      << endl;
    cout << "* Each * represents 10 AQI"         << endl;
    cout << "  Good:      0-50"                  << endl;
    cout << "  Moderate:  51-100"                << endl;
    cout << "  Unhealthy: 101+"                  << endl;
    cout << "=============================="      << endl;
}

// Apply AQI Alert - reference parameter
void applyAQIAlert(int &currentAQI,
                   string &alertLevel) {
    cout << "\n--- AQI Alert System ---"           << endl;

    // Nested if
    if (currentAQI > AQI_GOOD) {
        if (currentAQI > AQI_UNHEALTHY) {
            alertLevel  = "EMERGENCY ALERT!";
            currentAQI += 50;
            cout << "Emergency conditions!"        << endl;
        } else {
            alertLevel  = "WARNING";
            currentAQI += 25;
            cout << "Warning conditions!"          << endl;
        }
    } else {
        alertLevel = "NORMAL";
        cout << "Air quality is good!"             << endl;
    }

    // Conditional operator
    string action = (currentAQI > AQI_SENSITIVE) ?
                    "Stay indoors!" :
                    "Outdoor activity OK";
    cout << "Recommendation: " << action           << endl;
}
