/*
 * Student Name: Vi Lam
 * Date: 7/12/2026
 * Assignment: Homework Assignment 5
 * Program Description: One of the most important decisions
 * in our life is buying a house. Besides other factors,
 * having a payment plan is also important. This program
 * will help you build a payment plan that matches your
 * information, including PMI, HOA, and property tax
 * calculations. Note: This is 2026 version. Please find
 * the version that matches with your requirements.
 */

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <cassert>
#include <limits>
#include <cmath>
using namespace std;

// Named constants - loan terms
const int    TERM_15         = 180;
const int    TERM_30         = 360;
const double MONTHS_PER_YEAR = 12.0;

// Named constants - real bank rates
const double CHASE_RATE      = 6.90;
const double BOA_RATE        = 6.75;
const double USBANK_RATE     = 6.85;
const double WELLSFARGO_RATE = 6.65;

// Named constants - PMI and property tax
const double PMI_THRESHOLD   = 0.20;
const double PMI_RATE        = 0.01;
const double PROPERTY_TAX    = 0.011;

// Named constants - home value ranges
const double MIN_HOME_VALUE  = 15000.0;
const double MAX_HOME_VALUE  = 2000000.0;
const double MOBILE_MAX      = 149999.0;
const double STARTER_MAX     = 250000.0;
const double SINGLE_MAX      = 600000.0;
const double MAX_HOA         = 1000.0;

// Prototypes
void programGreeting();
void collectLoanID(string &loanID);
void selectBank(string &bankName, double &interestRate);
double collectHomeValue(string &homeType, double &landRent);
void collectDownPayment(double homeValue, double &downPayment,
                        double &principal, double &monthlyPMI,
                        bool &hasPMI);
int selectLoanTerm();
double collectHOAFee(string &homeType);
double calcMonthlyPayment(double principal, double annualRate,
                          int loanTerm);
double calcTotalMonthly(double mortgage, double monthlyPMI,
                        double monthlyTax, double hoaFee,
                        double landRent);
double calcMonthlyTax(double homeValue);
void displayPaymentBreakdown(string loanID, string bankName,
                             string homeType, double homeValue,
                             double downPayment, double principal,
                             double interestRate, int loanTerm,
                             double mortgage, double monthlyPMI,
                             double monthlyTax, double hoaFee,
                             double landRent, double totalMonthly);
void processPayments(double &balance, double monthlyPayment,
                     double interestRate, int &monthsRemaining,
                     double hoaFee,
                     vector<double> &paymentHistory);
void displayPaymentHistory(const vector<double> &history,
                           double monthlyPayment);
void buildYearlySummary(vector<vector<double>> &grid,
                        double principal, double interestRate,
                        int loanTerm);
void displayYearlySummary(const vector<vector<double>> &grid);

int main() {
    programGreeting();

    // Collect loan information
    string fullName     = "";
    string loanID       = "";
    string bankName     = "";
    string homeType     = "";
    double interestRate = 0.0;
    double homeValue    = 0.0;
    double downPayment  = 0.0;
    double principal    = 0.0;
    double monthlyPMI   = 0.0;
    double landRent     = 0.0;
    double hoaFee       = 0.0;
    bool   hasPMI       = false;
    int    loanTerm     = 0;

    // Collect owner name
    cout << "\n--- Owner Information ---"  << endl;
    cout << "Enter your full name: ";
    getline(cin, fullName);

    collectLoanID(loanID);
    selectBank(bankName, interestRate);
    homeValue = collectHomeValue(homeType, landRent);
    collectDownPayment(homeValue, downPayment,
                       principal, monthlyPMI, hasPMI);
    loanTerm  = selectLoanTerm();
    hoaFee    = collectHOAFee(homeType);

    // Calculate payments
    double monthlyTax   = calcMonthlyTax(homeValue);
    double mortgage     = calcMonthlyPayment(principal,
                                             interestRate,
                                             loanTerm);
    double totalMonthly = calcTotalMonthly(mortgage,
                                           monthlyPMI,
                                           monthlyTax,
                                           hoaFee,
                                           landRent);
    double balance         = principal;
    int    monthsRemaining = loanTerm;

    // Build yearly summary
    vector<vector<double>> yearlyGrid;
    buildYearlySummary(yearlyGrid, principal,
                       interestRate, loanTerm);

    // Payment history vector
    vector<double> paymentHistory;

    // Main menu loop
    int choice;
    do {
        cout << "\n=============================" << endl;
        cout << "   Home Loan Payment Planner  " << endl;
        cout << "-----------------------------" << endl;
        cout << "  Owner:   " << fullName        << endl;
        cout << "  Loan ID: " << loanID          << endl;
        cout << "  Bank:    " << bankName        << endl;
        cout << "  Balance: $" << fixed
             << setprecision(2) << balance       << endl;
        cout << "=============================" << endl;
        cout << "1. View Payment Breakdown"     << endl;
        cout << "2. Process Payments"           << endl;
        cout << "3. View Payment History"       << endl;
        cout << "4. View Yearly Summary"        << endl;
        cout << "5. Check Loan Status"          << endl;
        cout << "6. Exit"                       << endl;
        cout << "=============================" << endl;
        cout << "Enter choice (1-6): ";
        cin  >> choice;
        cin.ignore(1000, '\n');

        // Validate menu choice
        while (cin.fail() || choice < 1 || choice > 6) {
            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(),
                           '\n');
            }
            cout << "Invalid! Please enter 1-6." << endl;
            cout << "Enter choice (1-6): ";
            cin  >> choice;
            cin.ignore(1000, '\n');
        }

        switch (choice) {
            case 1:
                displayPaymentBreakdown(loanID, bankName,
                                        homeType, homeValue,
                                        downPayment, principal,
                                        interestRate, loanTerm,
                                        mortgage, monthlyPMI,
                                        monthlyTax, hoaFee,
                                        landRent, totalMonthly);
                break;

            case 2:
                processPayments(balance, mortgage,
                               interestRate, monthsRemaining,
                               hoaFee, paymentHistory);
                break;

            case 3:
                if (paymentHistory.empty()) {
                    cout << "No payments recorded yet!" << endl;
                } else {
                    displayPaymentHistory(paymentHistory,
                                         mortgage);
                }
                break;

            case 4:
                displayYearlySummary(yearlyGrid);
                break;

            case 5: {
                // Nested if - check loan status
                if (balance <= 0) {
                    cout << "\n================================" << endl;
                    cout << "  Your home is fully paid off!  " << endl;
                    cout << "  You own your home free & clear!" << endl;
                    cout << "================================"  << endl;
                } else if (monthsRemaining <= 0) {
                    cout << "\nLoan term complete!"             << endl;
                    cout << "Final payment needed: $"
                         << fixed << setprecision(2)
                         << balance                            << endl;
                    cout << "Please make one final payment"    << endl;
                    cout << "to fully own your home!"         << endl;
                } else if (monthsRemaining > loanTerm / 2) {
                    cout << "Status: Early stage"              << endl;
                    cout << "More than half remaining"         << endl;
                } else {
                    cout << "Status: Late stage"               << endl;
                    cout << "Less than half remaining"         << endl;
                }

                // Conditional operator - PMI status
                string pmiStatus = (hasPMI) ? "Active"
                                            : "Not Required";
                cout << "PMI Status: " << pmiStatus            << endl;
                break;
            }

            case 6:
                cout << "Thank you for using"                  << endl;
                cout << "Home Loan Payment Planner!"           << endl;
                cout << "Goodbye " << fullName << "!"          << endl;
                break;

            default:
                cout << "Invalid choice!"                      << endl;
                break;
        }
    } while (choice != 6);

    return 0;
}

// Function Greeting - displays welcome screen
void programGreeting() {
    cout << "================================"       << endl;
    cout << "   Home Loan Payment Planner   "       << endl;
    cout << "   By: Vi (Ivy) Lam           "       << endl;
    cout << "================================"       << endl;
    cout << endl;
    cout << "One of the most important decisions"   << endl;
    cout << "in our life is buying a house."        << endl;
    cout << "This program helps you build a"        << endl;
    cout << "payment plan that matches your needs," << endl;
    cout << "including PMI, HOA, and property tax." << endl;
    cout << "Note: This is 2026 version."           << endl;
    cout << endl;
}

// Collect Loan ID - Gauntlet of Trust validation
void collectLoanID(string &loanID) {
    bool valid = false;

    while (!valid) {
        cout << "Enter Loan ID (format LN####): ";
        getline(cin, loanID);

        // Level 1 - Presence check
        if (loanID.empty()) {
            cout << "Error: Loan ID cannot be empty!" << endl;
            continue;
        }

        // Level 2 - Shape check
        if (loanID.length() != 6) {
            cout << "Error: Must be 6 characters!"    << endl;
            continue;
        }

        // Convert to uppercase before checking
        for (int i = 0; i < (int)loanID.length(); i++) {
            loanID[i] = toupper(loanID[i]);
        }

        // Level 3 - Set check
        if (loanID[0] != 'L' || loanID[1] != 'N') {
            cout << "Error: Must start with LN!"      << endl;
            continue;
        }

        // Check digits
        bool allDigits = true;
        for (int i = 2; i < 6; i++) {
            if (!isdigit(loanID[i])) {
                allDigits = false;
            }
        }
        if (!allDigits) {
            cout << "Error: Last 4 must be digits!"   << endl;
            continue;
        }

        valid = true;
    }
    cout << "Loan ID accepted: " << loanID << endl;
}

// Select Bank - switch statement for bank selection
void selectBank(string &bankName, double &interestRate) {
    cout << "\n===== Select Your Bank (2026 Version) =====" << endl;
    cout << "1. Chase Bank        (6.90%)" << endl;
    cout << "2. Bank of America   (6.75%)" << endl;
    cout << "3. US Bank           (6.85%)" << endl;
    cout << "4. Wells Fargo       (6.65%)" << endl;
    cout << "5. Other Bank"                << endl;

    int  choice      = 0;
    bool validChoice = false;

    while (!validChoice) {
        cout << "Enter your choice (1-5): ";
        cin  >> choice;
        cin.ignore(1000, '\n');

        if (choice >= 1 && choice <= 5) {
            validChoice = true;
        } else {
            cout << "Invalid! Please enter 1-5." << endl;
        }
    }

    switch (choice) {
        case 1:
            bankName     = "Chase Bank";
            interestRate = CHASE_RATE;
            break;
        case 2:
            bankName     = "Bank of America";
            interestRate = BOA_RATE;
            break;
        case 3:
            bankName     = "US Bank";
            interestRate = USBANK_RATE;
            break;
        case 4:
            bankName     = "Wells Fargo";
            interestRate = WELLSFARGO_RATE;
            break;
        case 5:
            cout << "Enter your bank name: ";
            getline(cin, bankName);
            {
                bool validRate = false;
                while (!validRate) {
                    cout << "Enter interest rate (%): ";
                    cin  >> interestRate;
                    cin.ignore(1000, '\n');

                    if (cin.fail()) {
                        cin.clear();
                        cin.ignore(
                            numeric_limits<streamsize>::max(),
                            '\n');
                        cout << "Invalid! Enter a number." << endl;
                    } else if (interestRate > 0 &&
                               interestRate <= 20.0) {
                        validRate = true;
                    } else {
                        cout << "Error: Rate must be 0-20%!" << endl;
                    }
                }
            }
            break;
        default:
            bankName     = "Chase Bank";
            interestRate = CHASE_RATE;
            break;
    }
    cout << "Bank selected: " << bankName     << endl;
    cout << "Interest rate: " << interestRate << "%" << endl;
}

// Collect Home Value - validates and determines home type
double collectHomeValue(string &homeType, double &landRent) {
    double value;
    bool   valid = false;

    while (!valid) {
        cout << "Enter your home value ($): ";
        cin  >> value;
        cin.ignore(1000, '\n');

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid! Please enter a number." << endl;
            continue;
        }

        if (value >= MIN_HOME_VALUE && value <= MAX_HOME_VALUE) {
            valid = true;
        } else {
            cout << "Error: Home value must be between" << endl;
            cout << "$15,000 and $2,000,000!"          << endl;
        }
    }

    // Nested if - determine home type
    if (value >= MIN_HOME_VALUE && value <= MOBILE_MAX) {
        homeType = "Mobile Home";

        // Inner if - land rent required
        cout << "\nMobile home requires land rent."    << endl;
        bool validRent = false;
        while (!validRent) {
            cout << "Enter monthly land rent ($): ";
            cin  >> landRent;
            cin.ignore(1000, '\n');

            if (cin.fail()) {
                cin.clear();
                cin.ignore(
                    numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input!"               << endl;
            } else if (landRent > 0) {
                validRent = true;
            } else {
                cout << "Error: Land rent must be positive!" << endl;
            }
        }

    } else if (value > MOBILE_MAX && value <= STARTER_MAX) {
        int  typeChoice = 0;
        bool validType  = false;

        cout << "\nSelect your home type:"   << endl;
        cout << "1. Starter Home"            << endl;
        cout << "2. Condo"                   << endl;

        while (!validType) {
            cout << "Enter choice (1-2): ";
            cin  >> typeChoice;
            cin.ignore(1000, '\n');

            if (typeChoice == 1 || typeChoice == 2) {
                validType = true;
            } else {
                cout << "Invalid! Enter 1 or 2." << endl;
            }
        }

        // Conditional operator - home type selection
        homeType = (typeChoice == 1) ? "Starter Home" : "Condo";
        landRent = 0.0;

    } else if (value > STARTER_MAX && value <= SINGLE_MAX) {
        homeType = "Single Family Home";
        landRent = 0.0;

    } else {
        homeType = "Luxury Home";
        landRent = 0.0;
    }

    cout << "Home type: " << homeType << endl;
    return value;
}

// Collect Down Payment - calculates principal and checks PMI
void collectDownPayment(double homeValue,
                        double &downPayment,
                        double &principal,
                        double &monthlyPMI,
                        bool   &hasPMI) {
    bool valid = false;

    while (!valid) {
        cout << "Enter down payment ($): ";
        cin  >> downPayment;
        cin.ignore(1000, '\n');

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid! Please enter a number." << endl;
            continue;
        }

        if (downPayment >= 0 && downPayment < homeValue) {
            valid = true;
        } else {
            cout << "Error: Invalid down payment amount!" << endl;
        }
    }

    // Calculate principal
    principal = homeValue - downPayment;

    // Check PMI - nested if
    double downPercent = downPayment / homeValue;

    if (downPercent < PMI_THRESHOLD) {
        hasPMI     = true;
        monthlyPMI = (principal * PMI_RATE) / MONTHS_PER_YEAR;

        if (downPercent < 0.05) {
            cout << "\nWarning: Very low down payment!"    << endl;
            cout << "Consider saving more before buying." << endl;
        } else {
            cout << "\nPMI required until 20% equity."    << endl;
        }
        cout << fixed << setprecision(2);
        cout << "Monthly PMI: $" << monthlyPMI            << endl;
    } else {
        hasPMI     = false;
        monthlyPMI = 0.0;
        cout << "No PMI required!"                        << endl;
    }
}

// Select Loan Term - returns months for chosen term
int selectLoanTerm() {
    int  termChoice = 0;
    bool valid      = false;

    cout << "\n===== Select Loan Term =====" << endl;
    cout << "1. 15 Years (180 months)"      << endl;
    cout << "2. 30 Years (360 months)"      << endl;

    while (!valid) {
        cout << "Enter choice (1-2): ";
        cin  >> termChoice;
        cin.ignore(1000, '\n');

        if (termChoice == 1 || termChoice == 2) {
            valid = true;
        } else {
            cout << "Invalid! Please enter 1 or 2." << endl;
        }
    }

    if (termChoice == 1) {
        cout << "Loan term: 15 years selected." << endl;
        return TERM_15;
    } else {
        cout << "Loan term: 30 years selected." << endl;
        return TERM_30;
    }
}

// Collect HOA Fee - validates HOA fee based on home type
double collectHOAFee(string &homeType) {
    double hoaFee = 0.0;
    char   hasHOA;
    bool   valid  = false;

    // Condo always has HOA
    if (homeType == "Condo") {
        cout << "Condos require HOA fee."         << endl;

        while (!valid) {
            cout << "Enter monthly HOA fee ($): ";
            cin  >> hoaFee;
            cin.ignore(1000, '\n');

            if (cin.fail()) {
                cin.clear();
                cin.ignore(
                    numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid! Please enter a number." << endl;
            } else if (hoaFee > 0 && hoaFee <= MAX_HOA) {
                valid = true;
            } else {
                cout << "Error: HOA must be $1-$1000!"    << endl;
            }
        }

    } else {
        // Validate Y/N input
        bool validYN = false;
        while (!validYN) {
            cout << "Does your property have HOA?"    << endl;
            cout << "Y. Yes  N. No: ";
            cin  >> hasHOA;
            cin.ignore(1000, '\n');

            if (hasHOA == 'Y' || hasHOA == 'y' ||
                hasHOA == 'N' || hasHOA == 'n') {
                validYN = true;
            } else {
                cout << "Invalid! Please enter Y or N." << endl;
            }
        }

        if (hasHOA == 'Y' || hasHOA == 'y') {
            while (!valid) {
                cout << "Enter monthly HOA fee ($): ";
                cin  >> hoaFee;
                cin.ignore(1000, '\n');

                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(
                        numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid! Enter a number."   << endl;
                } else if (hoaFee > 0 && hoaFee <= MAX_HOA) {
                    valid = true;
                } else {
                    cout << "Error: HOA must be $1-$1000!" << endl;
                }
            }
        } else {
            hoaFee = 0.0;
            cout << "No HOA fee applied."             << endl;
        }
    }

    // Conditional operator - HOA status
    string hoaStatus = (hoaFee > 0) ? "HOA Applied" : "No HOA";
    cout << "HOA Status: " << hoaStatus               << endl;

    return hoaFee;
}

// Calculate Monthly Payment - mortgage formula
double calcMonthlyPayment(double principal,
                          double annualRate,
                          int    loanTerm) {
    double monthlyRate = annualRate / MONTHS_PER_YEAR / 100.0;

    // Assumption: principal must be positive
    assert(principal > 0);
    // Assumption: monthly rate must be positive
    assert(monthlyRate > 0);

    double factor  = pow(1 + monthlyRate, loanTerm);
    double payment = principal * (monthlyRate * factor)
                   / (factor - 1);

    return payment;
}

// Calculate Total Monthly - accumulates all costs
double calcTotalMonthly(double mortgage,
                        double monthlyPMI,
                        double monthlyTax,
                        double hoaFee,
                        double landRent) {
    double total = 0.0;

    total += mortgage;
    total += monthlyPMI;
    total += monthlyTax;
    total += hoaFee;
    total += landRent;

    return total;
}

// Calculate Monthly Tax - property tax calculation
double calcMonthlyTax(double homeValue) {
    return (homeValue * PROPERTY_TAX) / MONTHS_PER_YEAR;
}

// Display Payment Breakdown - bordered table
void displayPaymentBreakdown(string loanID,
                             string bankName,
                             string homeType,
                             double homeValue,
                             double downPayment,
                             double principal,
                             double interestRate,
                             int    loanTerm,
                             double mortgage,
                             double monthlyPMI,
                             double monthlyTax,
                             double hoaFee,
                             double landRent,
                             double totalMonthly) {
    cout << "\n";
    cout << "+-------------------------------------+" << endl;
    cout << "|    Monthly Payment Breakdown        |" << endl;
    cout << "+-------------------------------------+" << endl;
    cout << fixed << setprecision(2);
    cout << "| " << left  << setw(20) << "Loan ID:"
         << right << setw(14) << loanID        << " |" << endl;
    cout << "| " << left  << setw(20) << "Bank:"
         << right << setw(14) << bankName      << " |" << endl;
    cout << "| " << left  << setw(20) << "Home Type:"
         << right << setw(14) << homeType      << " |" << endl;
    cout << "| " << left  << setw(20) << "Home Value:"
         << right << setw(13) << "$"
         << homeValue                          << " |" << endl;
    cout << "| " << left  << setw(20) << "Down Payment:"
         << right << setw(13) << "$"
         << downPayment                        << " |" << endl;
    cout << "| " << left  << setw(20) << "Principal:"
         << right << setw(13) << "$"
         << principal                          << " |" << endl;
    cout << "| " << left  << setw(20) << "Interest Rate:"
         << right << setw(13) << interestRate
         << "%"                                << " |" << endl;
    cout << "| " << left  << setw(20) << "Loan Term:"
         << right << setw(11) << loanTerm
         << " months"                          << " |" << endl;
    cout << "+-------------------------------------+" << endl;
    cout << "|    Monthly Costs                    |" << endl;
    cout << "+-------------------------------------+" << endl;
    cout << "| " << left  << setw(20) << "Mortgage:"
         << right << setw(13) << "$"
         << mortgage                           << " |" << endl;
    cout << "| " << left  << setw(20) << "PMI:"
         << right << setw(13) << "$"
         << monthlyPMI                         << " |" << endl;
    cout << "| " << left  << setw(20) << "Property Tax:"
         << right << setw(13) << "$"
         << monthlyTax                         << " |" << endl;
    cout << "| " << left  << setw(20) << "HOA Fee:"
         << right << setw(13) << "$"
         << hoaFee                             << " |" << endl;
    cout << "| " << left  << setw(20) << "Land Rent:"
         << right << setw(13) << "$"
         << landRent                           << " |" << endl;
    cout << "+-------------------------------------+" << endl;
    cout << "| " << left  << setw(20) << "TOTAL MONTHLY:"
         << right << setw(13) << "$"
         << totalMonthly                       << " |" << endl;
    cout << "+-------------------------------------+" << endl;
}

// Process Payments - automated simulation
void processPayments(double &balance,
                     double monthlyPayment,
                     double interestRate,
                     int    &monthsRemaining,
                     double hoaFee,
                     vector<double> &paymentHistory) {

    // Check if loan already paid off
    if (balance <= 0 || monthsRemaining <= 0) {
        if (balance > 0 && monthsRemaining <= 0) {
            cout << "\nLoan term complete!"              << endl;
            cout << "Final payment needed: $"
                 << fixed << setprecision(2)
                 << balance                             << endl;
            cout << "Please make one final payment"     << endl;
            cout << "to fully own your home!"           << endl;
        } else {
            cout << "\n================================" << endl;
            cout << "  Your home is fully paid off!  " << endl;
            cout << "  You own your home free & clear!" << endl;
            cout << "================================"  << endl;
        }
        return;
    }

    int    accepted    = 0;
    int    skipped     = 0;
    double totalPaid   = 0.0;
    double monthlyRate = interestRate / MONTHS_PER_YEAR / 100.0;

    cout << "\n--- Payment Plan Setup ---"              << endl;
    cout << fixed << setprecision(2);
    cout << "Recommended payment: $" << monthlyPayment  << endl;
    if (hoaFee > 0) {
        cout << "HOA Fee:             $" << hoaFee      << endl;
        cout << "Total with HOA:      $"
             << monthlyPayment + hoaFee                 << endl;
    }

    // Ask one time for payment amount
    double payment = 0.0;
    bool   valid   = false;

    while (!valid) {
        cout << "\nEnter your monthly payment amount: $";
        cin  >> payment;
        cin.ignore(1000, '\n');

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid! Please enter a number."   << endl;
            continue;
        }

        if (payment < 0) {
            cout << "Error: Payment cannot be negative!" << endl;
        } else if (payment > 0 &&
                   payment < monthlyPayment) {
            cout << "Warning: Payment below minimum!"    << endl;
            cout << "This will extend your loan term."  << endl;
            valid = true;
        } else if (payment >= monthlyPayment) {
            valid = true;
        } else {
            cout << "Error: Invalid payment amount!"     << endl;
        }
    }

    // Ask how many months to simulate
    int  simMonths = 0;
    bool validSim  = false;

    while (!validSim) {
        cout << "Simulate how many months? (1-"
             << monthsRemaining << "): ";
        cin  >> simMonths;
        cin.ignore(1000, '\n');

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid! Please enter a number."   << endl;
            continue;
        }

        if (simMonths >= 1 && simMonths <= monthsRemaining) {
            validSim = true;
        } else {
            cout << "Error: Enter between 1 and "
                 << monthsRemaining << "."              << endl;
        }
    }

    cout << "\n--- Payment Simulation ---"              << endl;

    // Table header with HOA column if applicable
    if (hoaFee > 0) {
        cout << "+-------+----------+----------+----------+----------+"
             << endl;
        cout << "| Month | Payment  | HOA      | Interest | Balance  |"
             << endl;
        cout << "+-------+----------+----------+----------+----------+"
             << endl;
    } else {
        cout << "+-------+------------+------------+------------+"
             << endl;
        cout << "| Month | Payment    | Interest   | Balance    |"
             << endl;
        cout << "+-------+------------+------------+------------+"
             << endl;
    }

    // Simulate payments automatically
    for (int month = 1; month <= simMonths; month++) {

        // Skip condition - missed payment
        if (payment == 0) {
            skipped++;
            cout << "| " << left << setw(5) << month
                 << " | " << setw(10) << "SKIPPED"
                 << " |"                               << endl;
            continue;
        }

        // Stop condition - loan paid off
        if (balance <= 0) {
            break;
        }

        double interest = balance * monthlyRate;
        double prinPaid = payment - interest;
        balance        -= prinPaid;
        monthsRemaining--;
        totalPaid      += payment;
        accepted++;

        if (balance < 0) balance = 0.0;

        paymentHistory.push_back(payment);

        // Display row with or without HOA
        if (hoaFee > 0) {
            cout << "| " << left  << setw(5)  << month   << " |"
                 << right << setw(8) << fixed
                 << setprecision(2) << payment           << " |"
                 << right << setw(8) << hoaFee           << " |"
                 << right << setw(8) << interest         << " |"
                 << right << setw(8) << balance          << " |"
                 << endl;
        } else {
            cout << "| " << left  << setw(5)  << month   << " |"
                 << right << setw(10) << fixed
                 << setprecision(2) << payment           << " |"
                 << right << setw(10) << interest        << " |"
                 << right << setw(10) << balance         << " |"
                 << endl;
        }

        // Check final payment with rounding
        if (balance > 0 && balance < monthlyPayment &&
            monthsRemaining <= 0) {
            cout << "\nFinal payment needed: $"
                 << fixed << setprecision(2)
                 << balance                             << endl;
            cout << "Please make one final payment"     << endl;
            cout << "to fully own your home!"           << endl;
            break;
        }

        // Congratulations when fully paid
        if (balance <= 0) {
            balance         = 0.0;
            monthsRemaining = 0;
            cout << "\n================================" << endl;
            cout << "  Congratulations!"                << endl;
            cout << "  Your home is fully paid off!"    << endl;
            cout << "  You now own your home free"      << endl;
            cout << "  and clear!"                      << endl;
            cout << "================================"  << endl;
            break;
        }
    }

    // Bottom border
    if (hoaFee > 0) {
        cout << "+-------+----------+----------+----------+----------+"
             << endl;
    } else {
        cout << "+-------+------------+------------+------------+"
             << endl;
    }

    // Summary
    double totalWithHOA = totalPaid + (hoaFee * accepted);
    cout << fixed << setprecision(2);
    cout << "\nPayments accepted:  "  << accepted        << endl;
    cout << "Payments skipped:   "   << skipped         << endl;
    cout << "Total paid:        $"   << totalPaid        << endl;
    if (hoaFee > 0) {
        cout << "Total HOA paid:    $"
             << hoaFee * accepted                        << endl;
        cout << "Total with HOA:    $" << totalWithHOA   << endl;
    }
    cout << "Balance remaining: $"   << balance          << endl;
    cout << "Months remaining:   "   << monthsRemaining  << endl;
}

// Display Payment History - 1D vector with two loop types
void displayPaymentHistory(const vector<double> &history,
                           double monthlyPayment) {
    // Assumption: payment history must not be empty
    assert(history.size() > 0);

    cout << "\n--- Payment History ---"    << endl;

    // Range-based for loop - display all payments
    int month = 1;
    for (double p : history) {
        cout << "Month " << month << ": $"
             << fixed << setprecision(2)
             << p << endl;
        month++;
    }

    // Index-based for loop with .at() - find late payments
    cout << "\n--- Late Payments ---"      << endl;
    int lateCount = 0;
    for (int i = 0; i < (int)history.size(); i++) {
        if (history.at(i) < monthlyPayment) {
            lateCount++;
            cout << "Month " << i + 1
                 << ": $" << history.at(i)
                 << " (underpaid)"         << endl;
        }
    }

    // Calculate summary results
    double total   = 0.0;
    double highest = history.at(0);
    double lowest  = history.at(0);

    for (double p : history) {
        total += p;
        if (p > highest) highest = p;
        if (p < lowest)  lowest  = p;
    }

    double average = total /
                     static_cast<double>(history.size());

    cout << fixed << setprecision(2);
    cout << "\nTotal paid:      $" << total    << endl;
    cout << "Average payment: $"  << average  << endl;
    cout << "Highest payment: $"  << highest  << endl;
    cout << "Lowest payment:  $"  << lowest   << endl;
    cout << "Late payments:    "  << lateCount << endl;
}

// Build Yearly Summary - fills 2D vector
void buildYearlySummary(vector<vector<double>> &grid,
                        double principal,
                        double interestRate,
                        int    loanTerm) {
    double balance     = principal;
    double monthlyRate = interestRate / MONTHS_PER_YEAR / 100.0;
    double monthlyPmt  = calcMonthlyPayment(principal,
                                            interestRate,
                                            loanTerm);
    int years = loanTerm / 12;

    // Outer loop - years
    for (int y = 0; y < years; y++) {
        double yearPrincipal = 0.0;
        double yearInterest  = 0.0;

        // Inner loop - 12 months per year
        for (int m = 0; m < 12; m++) {
            if (balance <= 0) break;

            double interest  = balance * monthlyRate;
            double prinPaid  = monthlyPmt - interest;
            balance         -= prinPaid;
            yearPrincipal   += prinPaid;
            yearInterest    += interest;
        }

        vector<double> row;
        row.push_back(yearPrincipal);
        row.push_back(yearInterest);
        row.push_back(balance);
        grid.push_back(row);
    }
}

// Display Yearly Summary - shows 2D grid with totals
void displayYearlySummary(const vector<vector<double>> &grid) {
    cout << "\n";
    cout << "+------+--------------+--------------+--------------+"
         << endl;
    cout << "| Year | Principal    | Interest     | Balance      |"
         << endl;
    cout << "+------+--------------+--------------+--------------+"
         << endl;

    double totalPrincipal = 0.0;
    double totalInterest  = 0.0;

    // Nested loops - visit every element
    for (int i = 0; i < (int)grid.size(); i++) {
        cout << "| " << left << setw(4) << i + 1 << " |";

        for (int j = 0; j < (int)grid[i].size(); j++) {
            cout << " " << right << setw(12)
                 << fixed << setprecision(2)
                 << grid[i][j] << " |";
        }
        cout << endl;

        // Accumulate column totals
        totalPrincipal += grid[i].at(0);
        totalInterest  += grid[i].at(1);
    }

    cout << "+------+--------------+--------------+--------------+"
         << endl;
    cout << "| " << left  << setw(4)  << "TOT" << " |"
         << right << setw(12) << fixed << setprecision(2)
         << totalPrincipal << " |"
         << right << setw(12)
         << totalInterest  << " |"
         << right << setw(12) << " "  << " |" << endl;
    cout << "+------+--------------+--------------+--------------+"
         << endl;
}
