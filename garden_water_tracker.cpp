/*
 * Student Name: Vi Lam
 * Date: 07/05/2026
 * Assignment: Homework Assignment 4
 * Program Description: This program helps homeowners calculate
 * and track water usage for grass, vegetables, trees, and flowers
 * based on daily temperature and watering time in Sacramento.
 */

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;

// Struct definition
struct Plant {
    string type;
    double gallonsUsed;
};

// Named constants
const double MIN_TEMP             = 35.0;
const double MAX_TEMP             = 115.0;
const double HIGH_WATER_THRESHOLD = 15.0;

// Prototypes
void programGreeting();
double getValidTemperature(bool &isValid);
double categorizeWeather(double temperature, string &category);
double calcWaterUsed(double flowRate, double minutes, double multiplier);
void selectPlantType(string &plantType, double &flowRate);
void collectWeeklyMinutes(vector<double> &minutes, string &plantName, double flowRate, double multiplier);
double calcAverage(const vector<double> &data);
void displayWeeklyTable(const vector<double> &minutes, const string &plantName, double flowRate);
void buildGardenGrid(vector<vector<Plant>> &garden, int numZones, double flowRate, double multiplier);
void displayGardenReport(const vector<vector<Plant>> &garden);

int main() {
    programGreeting();

    // Collect owner information
    string fullName;
    string gardenName;

    cout << "\n--- Owner Information ---" << endl;
    cout << "Enter your full name: ";
    getline(cin, fullName);

    cout << "Enter your garden name: ";
    getline(cin, gardenName);

    cout << "\nHello " << fullName  << "!" << endl;
    cout << "Garden: " << gardenName       << endl;
    cout << "Let's calculate your water needs!" << endl;

    // Variables for menu
    bool   isValid    = false;
    double temp       = 0.0;
    double multiplier = 1.0;
    double flowRate   = 1.0;
    double gallons    = 0.0;
    double minutes    = 0.0;
    string plantType  = "Not set";
    string category   = "Not set";
    vector<double> weeklyMinutes;
    vector<vector<Plant>> garden;

    // Main menu loop
    int choice;
    do {
        cout << "\n=============================" << endl;
        cout << "  Sacramento Garden Menu     " << endl;
        cout << "-----------------------------" << endl;
        cout << "  Owner:  " << fullName        << endl;
        cout << "  Garden: " << gardenName      << endl;
        if (temp <= 0.0) {
            cout << "  Temp:   Not set"          << endl;
        } else {
            cout << "  Temp:   " << fixed
                 << setprecision(1)
                 << temp << "F | " << category   << endl;
        }
        cout << "  Plant:  " << plantType        << endl;
        cout << "=============================" << endl;
        cout << "1. Enter Temperature"           << endl;
        cout << "2. Select Plant Type"           << endl;
        cout << "3. Calculate Water Used"        << endl;
        cout << "4. View Weekly Report"          << endl;
        cout << "5. View Garden Grid Report"     << endl;
        cout << "6. Exit"                        << endl;
        cout << "=============================" << endl;
        cout << "Enter choice (1-6): ";
        cin  >> choice;
        cin.ignore(1000, '\n');

        while (cin.fail() || choice < 1 || choice > 6) {
            if (cin.fail()) {
                cin.clear();
                cin.ignore(1000, '\n');
            }
            cout << "Invalid! Please enter 1-6." << endl;
            cout << "Enter choice (1-6): ";
            cin  >> choice;
            cin.ignore(1000, '\n');
        }

        switch (choice) {
            case 1:
                temp = getValidTemperature(isValid);
                if (isValid) {
                    multiplier = categorizeWeather(temp, category);
                    cout << "Weather category: " << category << endl;
                }
                break;
            case 2:
                selectPlantType(plantType, flowRate);
                collectWeeklyMinutes(weeklyMinutes, plantType,
                                     flowRate, multiplier);
                break;
            case 3:
                cout << "Enter watering minutes: ";
                cin  >> minutes;
                cin.ignore(1000, '\n');
                gallons = calcWaterUsed(flowRate, minutes, multiplier);
                cout << fixed << setprecision(2);
                cout << "Water used: " << gallons << " gallons" << endl;
                break;
            case 4:
                if (weeklyMinutes.empty()) {
                    cout << "Please collect weekly minutes first!" << endl;
                } else {
                    displayWeeklyTable(weeklyMinutes, plantType, flowRate);
                    double avg = calcAverage(weeklyMinutes);
                    cout << "Average daily watering: "
                         << fixed << setprecision(2)
                         << avg << " minutes" << endl;
                }
                break;
            case 5: {
                int numZones;
                cout << "Enter number of garden zones: ";
                cin  >> numZones;
                cin.ignore(1000, '\n');
                buildGardenGrid(garden, numZones, flowRate, multiplier);
                displayGardenReport(garden);
                break;
            }
            case 6:
                cout << "Thank you " << fullName << "!" << endl;
                cout << "Goodbye from Sacramento Garden Tracker!" << endl;
                break;
            default:
                cout << "Invalid choice. Please enter 1-6." << endl;
                break;
        }
    } while (choice != 6);

    return 0;
}

// Function Greeting displays
void programGreeting() {
    cout << "================================" << endl;
    cout << "  Sacramento Garden Water Tracker" << endl;
    cout << "  By: Vi (Ivy) Lam              " << endl;
    cout << "================================" << endl;
    cout << endl;
    cout << "This program helps homeowners calculate" << endl;
    cout << "and track water usage for grass, vegetables," << endl;
    cout << "flower, and trees based on daily temperature." << endl;
    cout << endl;
}

//  Function Temperature
double getValidTemperature(bool &isValid) {
    double temp;
    cout << "Enter today's temperature (35-115 F): ";
    cin  >> temp;
    cin.ignore(1000, '\n');

    if (cin.fail()) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid input. Please enter a numeric value." << endl;
        isValid = false;
        temp = 0.0;
    } else if (temp >= MIN_TEMP && temp <= MAX_TEMP) {
        cout << "Temperature accepted." << endl;
        isValid = true;
    } else {
        cout << "Temperature out of realistic range ("
             << MIN_TEMP << "-" << MAX_TEMP << ")." << endl;
        isValid = false;
    }

    return temp;
}

// Categorize Weather - assigns category and water multiplier
double categorizeWeather(double temperature, string &category) {
    double multiplier;

    // Nested if - outer checks cool/warm
    if (temperature <= 85.0) {
        // Inner checks cool vs mild
        if (temperature <= 60.0) {
            category   = "Cool";
            multiplier = 0.7;
        } else {
            category   = "Mild";
            multiplier = 1.0;
        }
    } else {
        // Inner checks hot vs extreme
        if (temperature <= 100.0) {
            category   = "Hot";
            multiplier = 1.3;
        } else {
            category   = "Extreme";
            multiplier = 1.6;
        }
    }

    // Conditional operator - drought warning
    string drought = (temperature > 100.0) ? "Drought Warning!" : "Normal";
    cout << "Drought Status: " << drought << endl;

    return multiplier;
}

// Select Plant Type - plant selection
void selectPlantType(string &plantType, double &flowRate) {
    cout << "\n===== Select Plant Type =====" << endl;
    cout << "1. Grass"      << endl;
    cout << "2. Vegetables" << endl;
    cout << "3. Trees"      << endl;
    cout << "4. Flowers"    << endl;

    int choice;
    bool validChoice = false;

    while (!validChoice) {
        cout << "Enter choice (1-4): ";
        cin  >> choice;
        cin.ignore(1000, '\n');

        if (choice >= 1 && choice <= 4) {
            validChoice = true;
        } else {
            cout << "Invalid! Please enter 1-4." << endl;
        }
    }

    switch (choice) {
        case 1:
            plantType = "Grass";
            flowRate  = 2.0;
            break;
        case 2:
            plantType = "Vegetables";
            flowRate  = 1.5;
            break;
        case 3:
            plantType = "Trees";
            flowRate  = 1.0;
            break;
        case 4:
            plantType = "Flowers";
            flowRate  = 0.8;
            break;
        default:
            plantType = "Grass";
            flowRate  = 2.0;
            break;
    }
    cout << "Plant selected: " << plantType << endl;
}

// Calculate Water Used - returns gallons with static counter
double calcWaterUsed(double flowRate, double minutes,
                     double multiplier) {
    // Static local variable - tracks calculations
    static int calcCount = 0;
    calcCount++;
    cout << "Calculation #" << calcCount << endl;

    // static_cast prevents integer division
    double mins    = static_cast<double>(minutes);
    double gallons = flowRate * mins * multiplier;

    return gallons;
}

// Collect Weekly Minutes - gathers 7 days of watering data
void collectWeeklyMinutes(vector<double> &minutes, string &plantName, double flowRate, double multiplier) {
    minutes.clear();

    cout << "\n--- Watering Recommendation ---" << endl;
    cout << "Plant type: " << plantName         << endl;

    if (plantName == "Grass") {
        cout << "Suggested: 15-20 minutes/day"  << endl;
    } else if (plantName == "Vegetables") {
        cout << "Suggested: 20-25 minutes/day"  << endl;
    } else if (plantName == "Trees") {
        cout << "Suggested: 30-45 minutes/day"  << endl;
    } else if (plantName == "Flowers") {
        cout << "Suggested: 10-15 minutes/day"  << endl;
    }

    if (multiplier <= 0.7) {
        cout << "\nCool weather alert!"                  << endl;
        cout << "Temperature is too cool for watering." << endl;
        cout << "Skipping watering schedule."           << endl;
        for (int i = 0; i < 7; i++) {
            minutes.push_back(0.0);
        }
        return;
    }

    double mins;
    cout << "\nEnter daily watering minutes: ";
    cin  >> mins;
    cin.ignore(1000, '\n');

    char sameAll;
    bool validInput = false;

    while (!validInput) {
        cout << "Apply same minutes for all 7 days?" << endl;
        cout << "Y. Yes  N. No: ";
        cin  >> sameAll;
        cin.ignore(1000, '\n');

        if (sameAll == 'Y' || sameAll == 'y' ||
            sameAll == 'N' || sameAll == 'n') {
            validInput = true;
        } else {
            cout << "Invalid input! Please enter Y or N." << endl;
        }
    }

    if (sameAll == 'Y' || sameAll == 'y') {
        // Loop type 1 - for loop fills all 7 days
        for (int i = 0; i < 7; i++) {
            minutes.push_back(mins);
        }

        double weeklyMins    = mins * 7;
        double weeklyGallons = mins * flowRate * 7;

        cout << "\nWeekly schedule set!"    << endl;
        cout << fixed << setprecision(2);
        cout << "Daily:          " << mins
             << " min"             << endl;
        cout << "Weekly total:   " << weeklyMins
             << " minutes"         << endl;
        cout << "Weekly gallons: " << weeklyGallons
             << " gallons"         << endl;

    } else {
        // Loop type 1 - for loop collects each day manually
        cout << "\nEnter minutes for each day:" << endl;
        for (int i = 0; i < 7; i++) {
            double d;
            cout << "Day " << i + 1 << ": ";
            cin  >> d;
            cin.ignore(1000, '\n');
            minutes.push_back(d);
        }
    }

    // Loop type 2 - range-based for displays schedule
    cout << "\nYour weekly schedule:"       << endl;
    int day = 1;
    for (double m : minutes) {
        cout << "Day " << day << ": "
             << fixed << setprecision(1)
             << m << " minutes"             << endl;
        day++;
    }
}

// Calculate Average - returns average of vector values
double calcAverage(const vector<double> &data) {
    double total = 0.0;

    for (double val : data) {
        total += val;
    }

    return total / static_cast<double>(data.size());
}

// Display Weekly Table - bordered table of weekly usage
void displayWeeklyTable(const vector<double> &minutes, const string &plantName, double flowRate) {
    // Static variable - tracks report generations
    static int reportCount = 0;
    reportCount++;

    cout << "\nWeekly Water Report for: "
         << plantName << endl;
    cout << "Report #" << reportCount << endl;

    // Top border
    cout << "*-------*----------*-----------*" << endl;
    // Header row
    cout << "| " << left << setw(5)  << "Day"
         << " | " << setw(8) << "Minutes"
         << " | " << setw(9) << "Gallons"
         << " |"  << endl;
    // Divider
    cout << "*-------*----------*-----------*" << endl;

    // Data rows
    cout << fixed << setprecision(2);
    int day = 1;
    for (double m : minutes) {
        double gallons = m * flowRate;
        cout << "| " << left << setw(5)  << day
             << " | " << setw(8) << m
             << " | " << setw(9) << gallons
             << " |"  << endl;
        day++;
    }

    // Bottom border
    cout << "*-------*----------*-----------*" << endl;
}

// Build Garden Grid - fills 2D vector with zone data
void buildGardenGrid(vector<vector<Plant>> &garden,
                     int numZones,
                     double flowRate,
                     double multiplier) {
    cout << "\nBuilding garden grid: " << endl;

    // Outer loop - zones
    for (int zone = 0; zone < numZones; zone++) {
        vector<Plant> row;
        cout << "\nZone " << zone + 1 << ":" << endl;

        // Inner loop - 3 days
        for (int day = 0; day < 3; day++) {
            Plant p;
            double mins;
            cout << "  Day " << day + 1
                 << " watering minutes: ";
            cin  >> mins;
            cin.ignore(1000, '\n');

            p.type        = "Zone " + to_string(zone + 1);
            p.gallonsUsed = mins * flowRate * multiplier;
            row.push_back(p);
        }
        garden.push_back(row);
    }
}

// Display Garden Report - shows 2D grid with totals
void displayGardenReport(const vector<vector<Plant>> &garden) {
    cout << "\n===== Garden Zone Report =====" << endl;

    // Top border
    cout << "+--------+-------+-------+-------+" << endl;
    cout << "| " << left << setw(6) << "Zone"
         << " | " << setw(5) << "Day1"
         << " | " << setw(5) << "Day2"
         << " | " << setw(5) << "Day3"
         << " |" << endl;
    cout << "+--------+-------+-------+-------+" << endl;

    // Nested loops to display
    for (int i = 0; i < (int)garden.size(); i++) {
        cout << "| " << left << setw(6) << i + 1 << " |";

        for (int j = 0; j < (int)garden[i].size(); j++) {
            cout << " " << setw(5) << fixed
                 << setprecision(1)
                 << garden[i][j].gallonsUsed << " |";
        }
        cout << endl;
    }

    // Bottom border
    cout << "+--------+-------+-------+-------+" << endl;

    // Calculate total with nested loops
    double total = 0.0;
    for (int i = 0; i < (int)garden.size(); i++) {
        for (int j = 0; j < (int)garden[i].size(); j++) {
            total += garden[i][j].gallonsUsed;
        }
    }
    cout << fixed << setprecision(2);
    cout << "Total water used: " << total << " gallons" << endl;
}
