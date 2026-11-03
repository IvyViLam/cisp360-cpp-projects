/*
 * Student Name: Vi Lam
 * Date: 07/17/2026
 * Assignment: Homework Assignment 6
 * Program Description: Although California has a mild
 * climate, winter temperatures in Sacramento sometimes
 * stay around 30-33F, which causes higher gas usage
 * than normal. This program helps users calculate and
 * control their gas bill budget more effectively
 * during the winter.
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>
#include <numeric>
#include <limits>
using namespace std;

// Named constants - array sizes
const int    DAYS_PER_MONTH = 30;
const int    WEEKS          = 4;
const int    DAYS_PER_WEEK  = 7;

// Named constants - gas rates
const double GAS_RATE       = 1.85;
const double WINTER_RATE    = 0.45;
const double TOTAL_RATE     = 2.30;
const double CCF_TO_THERM   = 1.02;

// Named constant - file name
const string DATA_FILE      = "gas_data.txt";

// Prototypes
void programGreeting();
void collectMeterID(string &meterID);
void collectDailyUsage(double usage[], int size);
void displayDailyUsage(const double usage[], int size);
double calcTotalUsage(const double usage[], int size);
double calcAverageUsage(const double usage[], int size);
double findMaxUsage(const double usage[], int size);
double findMinUsage(const double usage[], int size);
int searchUsage(const double usage[], int size,
                double target);
void applyWinterAdjustment(double usage[], int size,
                           double factor);
void buildWeeklyGrid(double grid[][DAYS_PER_WEEK],
                     const double usage[],
                     int totalDays);
void displayWeeklyGrid(
        const double grid[][DAYS_PER_WEEK]);
void saveToFile(const double usage[], int size,
                string meterID, double total);
void loadFromFile();
void collectMonthlyBills(vector<double> &bills);
void displayBillHistory(vector<double> &bills);
void processUsageLoop(const double usage[], int size);
void displayGasReport(const double usage[], int size);

int main() {
    programGreeting();

    // Collect owner information
    string ownerName = "";
    string meterID   = "";

    cout << "\n--- Owner Information ---"   << endl;
    cout << "Enter your full name: ";
    getline(cin, ownerName);

    collectMeterID(meterID);

    // Declare arrays and vector
    double dailyUsage[DAYS_PER_MONTH]       = {0.0};
    double weeklyGrid[WEEKS][DAYS_PER_WEEK] = {{0.0}};
    vector<double> monthlyBills;

    // sizeof in declaring scope
    int arraySize = sizeof(dailyUsage) /
                    sizeof(dailyUsage[0]);
    cout << "Array capacity: " << arraySize
         << " days"                          << endl;

    int choice;
    do {
        cout << "\n=============================" << endl;
        cout << "  Sacramento Gas Tracker     " << endl;
        cout << "-----------------------------" << endl;
        cout << "  Owner:  " << ownerName       << endl;
        cout << "  Meter:  " << meterID         << endl;
        cout << "=============================" << endl;
        cout << "1. Enter Daily Readings"       << endl;
        cout << "2. View Gas Report"            << endl;
        cout << "3. View Weekly Grid"           << endl;
        cout << "4. Process Usage Analysis"     << endl;
        cout << "5. View Bill History"          << endl;
        cout << "6. Save Data to File"          << endl;
        cout << "7. Load Data from File"        << endl;
        cout << "8. Exit"                       << endl;
        cout << "=============================" << endl;
        cout << "Enter choice (1-8): ";
        cin  >> choice;
        cin.ignore(1000, '\n');

        // Validate menu choice
        while (cin.fail() ||
               choice < 1 || choice > 8) {
            if (cin.fail()) {
                cin.clear();
                cin.ignore(
                    numeric_limits<streamsize>::max(),
                    '\n');
            }
            cout << "Invalid! Please enter 1-8." << endl;
            cout << "Enter choice (1-8): ";
            cin  >> choice;
            cin.ignore(1000, '\n');
        }

        switch (choice) {
            case 1:
                collectDailyUsage(dailyUsage,
                                  DAYS_PER_MONTH);
                buildWeeklyGrid(weeklyGrid,
                                dailyUsage,
                                DAYS_PER_MONTH);
                break;

            case 2:
                displayGasReport(dailyUsage,
                                 DAYS_PER_MONTH);
                break;

            case 3:
                displayWeeklyGrid(weeklyGrid);
                break;

            case 4: {
                processUsageLoop(dailyUsage,
                                 DAYS_PER_MONTH);

                // Nested if - check usage level
                double total = calcTotalUsage(
                                   dailyUsage,
                                   DAYS_PER_MONTH);
                if (total > 0) {
                    if (total > 150.0) {
                        cout << "Warning: Very high"
                             << " usage this month!" << endl;
                        cout << "Consider lowering"
                             << " thermostat."       << endl;
                    } else {
                        cout << "Usage within normal"
                             << " range."            << endl;
                    }
                } else {
                    cout << "No usage data yet."     << endl;
                }

                // Conditional operator - usage level
                double avg = calcAverageUsage(
                                 dailyUsage,
                                 DAYS_PER_MONTH);
                string level = (avg > 7.0) ? "High"
                                           : "Normal";
                cout << "Average usage level: "
                     << level                        << endl;

                // Search
                double searchVal;
                cout << "Search for daily usage: ";
                cin  >> searchVal;
                cin.ignore(1000, '\n');
                int found = searchUsage(dailyUsage,
                                        DAYS_PER_MONTH,
                                        searchVal);
                if (found != -1) {
                    cout << "Found on Day "
                         << found + 1               << endl;
                } else {
                    cout << "Value not found."       << endl;
                }

                // Before and after adjustment
                cout << "\nBefore adjustment: "
                     << fixed << setprecision(2)
                     << dailyUsage[0]
                     << " therms"                   << endl;
                applyWinterAdjustment(dailyUsage,
                                      DAYS_PER_MONTH,
                                      1.1);
                cout << "After 10% adjustment: "
                     << dailyUsage[0]
                     << " therms"                   << endl;
                break;
            }

            case 5:
                collectMonthlyBills(monthlyBills);
                displayBillHistory(monthlyBills);
                break;

            case 6: {
                double total = calcTotalUsage(
                                   dailyUsage,
                                   DAYS_PER_MONTH);
                saveToFile(dailyUsage,
                           DAYS_PER_MONTH,
                           meterID, total);
                break;
            }

            case 7:
                loadFromFile();
                break;

            case 8:
                cout << "Thank you "
                     << ownerName << "!"            << endl;
                cout << "Stay warm this winter!"    << endl;
                cout << "Goodbye!"                  << endl;
                break;

            default:
                cout << "Invalid choice!"           << endl;
                break;
        }
    } while (choice != 8);

    return 0;
}

// Function Greeting - displays welcome screen
void programGreeting() {
    cout << "================================"      << endl;
    cout << "  Sacramento Gas Usage Tracker  "     << endl;
    cout << "  By: Vi (Ivy) Lam             "     << endl;
    cout << "================================"      << endl;
    cout << endl;
    cout << "Although California has mild climate," << endl;
    cout << "Sacramento winters reach 30-33F,"     << endl;
    cout << "causing higher gas usage than normal." << endl;
    cout << "This program helps you track and"     << endl;
    cout << "budget your winter gas bills."         << endl;
    cout << endl;
}

// Collect Meter ID - Gauntlet of Trust validation
void collectMeterID(string &meterID) {
    bool valid = false;

    while (!valid) {
        cout << "Enter PGE Meter ID (##########-#): ";
        getline(cin, meterID);

        // Level 1 - Presence check
        if (meterID.empty()) {
            cout << "Error: Meter ID cannot be empty!" << endl;
            continue;
        }

        // Level 2 - Shape check
        if (meterID.length() != 12) {
            cout << "Error: Must be 12 characters!"    << endl;
            continue;
        }

        // Level 3 - Set check
        bool validFormat = true;

        // Check first 10 are digits
        for (int i = 0; i < 10; i++) {
            if (!isdigit(meterID[i])) {
                validFormat = false;
            }
        }

        // Check position 10 is dash
        if (meterID[10] != '-') {
            validFormat = false;
        }

        // Check last character is digit
        if (!isdigit(meterID[11])) {
            validFormat = false;
        }

        if (!validFormat) {
            cout << "Error: Format must be ##########-#!" << endl;
            continue;
        }

        valid = true;
    }
    cout << "Meter ID accepted: " << meterID << endl;
}

// Collect Daily Usage - validates meter readings
void collectDailyUsage(double usage[], int size) {
    cout << "\n--- Enter Monthly Gas Readings ---"  << endl;
    cout << "Check your PGE meter at start"        << endl;
    cout << "and end of the month."                << endl;

    double startReading = 0.0;
    double endReading   = 0.0;

    // Validate starting reading
    bool validStart = false;
    while (!validStart) {
        cout << "\nStarting meter reading (CCF): ";
        cin  >> startReading;
        cin.ignore(1000, '\n');

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),
                       '\n');
            cout << "Invalid! Enter a number."      << endl;
        } else if (startReading >= 0) {
            validStart = true;
        } else {
            cout << "Error: Reading cannot be negative!" << endl;
        }
    }

    // Validate ending reading
    bool validEnd = false;
    while (!validEnd) {
        cout << "Ending meter reading (CCF): ";
        cin  >> endReading;
        cin.ignore(1000, '\n');

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),
                       '\n');
            cout << "Invalid! Enter a number."      << endl;
        } else if (endReading > startReading) {
            validEnd = true;
        } else {
            cout << "Error: Ending must be greater"  << endl;
            cout << "than starting reading!"         << endl;
        }
    }

    // Calculate total and daily average
    double totalCCF    = endReading - startReading;
    double totalTherms = totalCCF * CCF_TO_THERM;
    double dailyAvg    = totalTherms /
                         static_cast<double>(size);

    // Fill all days with daily average
    for (int i = 0; i < size; i++) {
        usage[i] = dailyAvg;
    }

    cout << fixed << setprecision(2);
    cout << "\nMonthly Summary:"                    << endl;
    cout << "Total CCF used:    "
         << totalCCF    << " CCF"                   << endl;
    cout << "Total therms:      "
         << totalTherms << " therms"                << endl;
    cout << "Daily average:     "
         << dailyAvg    << " therms/day"            << endl;
    cout << "Days in month:     " << size           << endl;
    cout << "\nAll " << size
         << " days filled with daily average!"      << endl;
}

// Calculate Total Usage - const array parameter
double calcTotalUsage(const double usage[], int size) {
    double total = 0.0;
    for (int i = 0; i < size; i++) {
        total += usage[i];
    }
    return total;
}

// Calculate Average Usage
double calcAverageUsage(const double usage[], int size) {
    return calcTotalUsage(usage, size) /
           static_cast<double>(size);
}

// Find Maximum Usage
double findMaxUsage(const double usage[], int size) {
    double maxVal = usage[0];
    for (int i = 1; i < size; i++) {
        if (usage[i] > maxVal) {
            maxVal = usage[i];
        }
    }
    return maxVal;
}

// Find Minimum Usage
double findMinUsage(const double usage[], int size) {
    double minVal = usage[0];
    for (int i = 1; i < size; i++) {
        if (usage[i] < minVal) {
            minVal = usage[i];
        }
    }
    return minVal;
}

// Search Usage - linear search returns index or -1
int searchUsage(const double usage[],
                int size, double target) {
    for (int i = 0; i < size; i++) {
        if (abs(usage[i] - target) < 0.001) {
            return i;
        }
    }
    return -1;
}

// Apply Winter Adjustment - modifies array
void applyWinterAdjustment(double usage[],
                           int size,
                           double factor) {
    for (int i = 0; i < size; i++) {
        usage[i] *= factor;
    }
}

// Build Weekly Grid - fills 2D array
void buildWeeklyGrid(double grid[][DAYS_PER_WEEK],
                     const double usage[],
                     int totalDays) {
    // Outer loop - weeks
    for (int w = 0; w < WEEKS; w++) {
        // Inner loop - days
        for (int d = 0; d < DAYS_PER_WEEK; d++) {
            int index = w * DAYS_PER_WEEK + d;
            if (index < totalDays) {
                grid[w][d] = usage[index];
            } else {
                grid[w][d] = 0.0;
            }
        }
    }
}

// Display Weekly Grid - shows 2D array with totals
void displayWeeklyGrid(
        const double grid[][DAYS_PER_WEEK]) {
    cout << "\n--- Weekly Gas Usage Grid ---"  << endl;
    cout << "+------+-------+-------+-------+"
         << "-------+-------+-------+-------+"
         << endl;
    cout << "| Week |  Mon  |  Tue  |  Wed  "
         << "|  Thu  |  Fri  |  Sat  |  Sun  |"
         << endl;
    cout << "+------+-------+-------+-------+"
         << "-------+-------+-------+-------+"
         << endl;

    // Column totals array
    double colTotals[DAYS_PER_WEEK] = {0.0};

    // Nested loops - display rows
    for (int w = 0; w < WEEKS; w++) {
        double rowTotal = 0.0;
        cout << "| " << left << setw(4) << w + 1
             << " |";

        for (int d = 0; d < DAYS_PER_WEEK; d++) {
            cout << right << setw(5)
                 << fixed << setprecision(1)
                 << grid[w][d] << " |";
            rowTotal     += grid[w][d];
            colTotals[d] += grid[w][d];
        }
        cout << " Row: " << fixed
             << setprecision(1)
             << rowTotal                        << endl;
    }

    cout << "+------+-------+-------+-------+"
         << "-------+-------+-------+-------+"
         << endl;

    // Display column totals
    cout << "| TOT  |";
    for (int d = 0; d < DAYS_PER_WEEK; d++) {
        cout << right << setw(5)
             << fixed << setprecision(1)
             << colTotals[d] << " |";
    }
    cout << endl;
    cout << "+------+-------+-------+-------+"
         << "-------+-------+-------+-------+"
         << endl;
}

// Save to File - writes data to gas_data.txt
void saveToFile(const double usage[],
                int size,
                string meterID,
                double total) {
    ofstream outFile(DATA_FILE);

    if (!outFile) {
        cout << "Error: Cannot open file!" << endl;
        return;
    }

    // Write meter ID and total first
    outFile << meterID << endl;
    outFile << total   << endl;

    // Write all daily values
    for (int i = 0; i < size; i++) {
        outFile << usage[i] << endl;
    }

    outFile.close();
    cout << "Data saved to "
         << DATA_FILE << endl;
}

// Load from File - reads data from gas_data.txt
void loadFromFile() {
    ifstream inFile(DATA_FILE);

    if (!inFile) {
        cout << "Error: Cannot open file!" << endl;
        return;
    }

    cout << "\n--- Loading Saved Data ---" << endl;

    string meterID;
    getline(inFile, meterID);
    cout << "Meter ID: " << meterID        << endl;

    double value;
    int    count = 0;

    // Loop condition is input operation
    while (inFile >> value) {
        count++;
        cout << "Record " << count << ": "
             << fixed << setprecision(2)
             << value << " therms"         << endl;
    }

    inFile.close();
    cout << "Total records loaded: "
         << count                          << endl;
}

// Collect Monthly Bills - fills vector
void collectMonthlyBills(vector<double> &bills) {
    int  numBills = 0;
    bool valid    = false;

    // Ask how many months
    while (!valid) {
        cout << "How many months of history? (5-12): ";
        cin  >> numBills;
        cin.ignore(1000, '\n');

        if (cin.fail()) {
            cin.clear();
            cin.ignore(
                numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid! Enter a number."     << endl;
        } else if (numBills >= 5 && numBills <= 12) {
            valid = true;
        } else {
            cout << "Error: Enter between 5-12."   << endl;
        }
    }

    // Collect each bill
    for (int i = 0; i < numBills; i++) {
        double bill    = 0.0;
        bool validBill = false;

        while (!validBill) {
            cout << "Month " << i + 1
                 << " bill ($): ";
            cin  >> bill;
            cin.ignore(1000, '\n');

            if (cin.fail()) {
                cin.clear();
                cin.ignore(
                    numeric_limits<streamsize>::max(),
                    '\n');
                cout << "Invalid! Enter a number." << endl;
            } else if (bill >= 0 && bill <= 500) {
                bills.push_back(bill);
                validBill = true;
            } else {
                cout << "Error: Bill must be $0-$500!"
                     << endl;
            }
        }
    }
    cout << "Monthly bills recorded!"              << endl;
}

// Display Bill History - vector with STL tools
void displayBillHistory(vector<double> &bills) {
    cout << "\n--- Monthly Bill History ---"       << endl;

    // Range-based for - display all
    int month = 1;
    for (double b : bills) {
        cout << "Month " << month << ": $"
             << fixed << setprecision(2)
             << b                                  << endl;
        month++;
    }

    // Index-based for with .at() - find high bills
    cout << "\n--- High Bill Months ---"           << endl;
    for (int i = 0; i < (int)bills.size(); i++) {
        if (bills.at(i) > 100.0) {
            cout << "Month " << i + 1
                 << ": $" << bills.at(i)
                 << " (high usage!)"               << endl;
        }
    }

    // STL tools
    sort(bills.begin(), bills.end());

    double minBill = *min_element(bills.begin(),
                                   bills.end());
    double maxBill = *max_element(bills.begin(),
                                   bills.end());
    double total   = accumulate(bills.begin(),
                                bills.end(), 0.0);
    double average = total /
                     static_cast<double>(bills.size());

    cout << "\n--- Bill Summary ---"               << endl;
    cout << fixed << setprecision(2);
    cout << "Lowest bill:  $" << minBill           << endl;
    cout << "Highest bill: $" << maxBill           << endl;
    cout << "Total paid:   $" << total             << endl;
    cout << "Average bill: $" << average           << endl;

    // Display sorted bills
    cout << "\n--- Bills Sorted Low to High ---"   << endl;
    for (double b : bills) {
        cout << "$" << fixed << setprecision(2)
             << b                                  << endl;
    }
}

// Process Usage Loop - break and continue
void processUsageLoop(const double usage[],
                      int size) {
    int    accepted = 0;
    int    skipped  = 0;
    double total    = 0.0;

    cout << "\n--- Processing Daily Readings ---"  << endl;

    for (int i = 0; i < size; i++) {

        // Skip condition - zero reading
        if (usage[i] == 0.0) {
            skipped++;
            cout << "Day " << i + 1
                 << ": skipped - no reading"       << endl;
            continue;
        }

        // Stop condition - meter error
        if (usage[i] > 50.0) {
            cout << "Day " << i + 1
                 << ": stopped - reading too high"  << endl;
            break;
        }

        // Process valid reading
        accepted++;
        total += usage[i];

        cout << "Day " << i + 1 << ": "
             << fixed << setprecision(2)
             << usage[i] << " therms"              << endl;
    }

    // Display results
    cout << "\nAccepted readings: " << accepted     << endl;
    cout << "Skipped readings:  " << skipped       << endl;
    cout << fixed << setprecision(2);
    cout << "Total usage:       " << total
         << " therms"                              << endl;
}

// Display Gas Report - formatted bordered table
void displayGasReport(const double usage[],
                      int size) {
    cout << "\n";
    cout << "+------+---------+----------+"
         << "----------+----------+"             << endl;
    cout << "| Day  | Therms  | Cost     "
         << "| Status   | Adj Cost |"            << endl;
    cout << "+------+---------+----------+"
         << "----------+----------+"             << endl;

    double totalTherms  = 0.0;
    double totalCost    = 0.0;
    double totalAdjCost = 0.0;

    for (int i = 0; i < size; i++) {
        double cost    = usage[i] * GAS_RATE;
        double adjCost = usage[i] * TOTAL_RATE;

        // Conditional operator - status
        string status = (usage[i] > 7.0) ? "High"
                                          : "Low";

        totalTherms  += usage[i];
        totalCost    += cost;
        totalAdjCost += adjCost;

        cout << "| " << left  << setw(4)  << i + 1
             << " | " << right << setw(7)
             << fixed << setprecision(2)
             << usage[i]
             << " | $" << setw(7) << cost
             << " | " << left  << setw(8) << status
             << " | $" << right << setw(7) << adjCost
             << " |"                              << endl;
    }

    cout << "+------+---------+----------+"
         << "----------+----------+"             << endl;
    cout << "| " << left  << setw(4)  << "TOT"
         << " | " << right << setw(7)
         << fixed << setprecision(2)
         << totalTherms
         << " | $" << setw(7) << totalCost
         << " | " << left  << setw(8) << " "
         << " | $" << right << setw(7) << totalAdjCost
         << " |"                                 << endl;
    cout << "+------+---------+----------+"
         << "----------+----------+"             << endl;

    cout << fixed << setprecision(2);
    cout << "\nGas rate:          $"
         << GAS_RATE   << "/therm"               << endl;
    cout << "Winter rate:       $"
         << TOTAL_RATE << "/therm"               << endl;
    cout << "Total therms:       "
         << totalTherms << " therms"             << endl;
    cout << "Total cost:        $"
         << totalCost                            << endl;
    cout << "Total winter cost: $"
         << totalAdjCost                         << endl;
}

