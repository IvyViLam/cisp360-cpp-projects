# CISP 360 — C++ Programming Projects

A collection of C++ programs written for CISP 360 (Programming in C++), covering core language fundamentals through more advanced topics like structs, 2D vectors, pointers, dynamic memory, and file I/O.

Each project applies programming concepts to a practical, real-world scenario rather than abstract exercises.

## Projects

### 🏦 [Home Loan Payment Planner](./mortgage_planner.cpp) — *Featured*
A mortgage calculator that models a full loan lifecycle: PMI, property tax, HOA fees, multi-bank interest rate comparison, monthly payment processing, and a year-by-year amortization schedule using a 2D vector. Demonstrates structs, function overloading-style design, `assert()`, and defensive input handling.

### 🚰 [Wastewater Treatment Analyzer](./wastewater_analyzer.cpp) — *Featured*
Menu-driven tool for lab technicians to analyze BOD/COD wastewater samples, calculate removal efficiency, and generate treatment recommendations. Demonstrates structs, function overloading, and default parameters.

### 🌱 [Sacramento Garden Water Tracker](./garden_water_tracker.cpp) — *Featured*
Calculates and tracks irrigation water usage across plant types and garden zones based on daily temperature. Demonstrates 2D vectors, static local variables, and nested loops.

### 🔥 [Sacramento Gas Usage Tracker](./gas_usage_tracker.cpp) — *Featured*
Tracks winter gas usage and billing with daily/weekly breakdowns. Demonstrates file I/O (read/write), C-style arrays, linear search, and STL algorithms (`sort`, `accumulate`, `min_element`, `max_element`).

### 🌫️ [Sacramento Air Quality Monitor](./air_quality_monitor.cpp) — *Featured*
Monitors AQI readings across pollution zones and issues alerts. Demonstrates pointers, dynamic memory allocation (`new`), pass-by-reference, and 2D vector reporting.

### ⚖️ [Weight Loss Plan Tracker](./weight_loss_tracker.cpp)
Tracks calorie intake vs. burn to build a weight-loss plan with safety-guarded goal setting. Demonstrates functions, vectors, and input validation.

## Build & Run

Each project is a single `.cpp` file. Compile with:

```bash
g++ -o program_name filename.cpp
./program_name
```

## Concepts Covered Across This Collection

- Functions, parameters, and return values
- Structs and vectors of structs
- 2D vectors and nested loops
- Pointers and dynamic memory (`new`)
- File I/O (`ifstream`/`ofstream`)
- STL algorithms (`sort`, `accumulate`, `min_element`, `max_element`)
- Robust input validation (`cin.fail()`, `cin.clear()`, `cin.ignore()`)
- Pass-by-reference and pass-by-value design

## Author

Vi (Ivy) Lam — Computer Science & AI/ML, Folsom Lake College
