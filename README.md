# Low-Latency Order Book in C++

A modular **limit order book and matching engine** built in **C++17** to simulate the core mechanics of electronic trading systems. This project processes order events, maintains bid and ask books, executes trades using **price-time priority**, and provides analytics such as spread, mid-price, depth, and imbalance.

The goal of this project is to explore the software engineering and systems design principles behind **low-latency trading infrastructure**. It focuses on deterministic matching logic, clean system decomposition, maintainable C++ design, and a strong foundation for future benchmarking and profiling.

---

## Table of Contents

- [Overview](#overview)
- [Key Features](#key-features)
- [Tech Stack](#tech-stack)
- [Repository Structure](#repository-structure)
- [Installation](#installation)
- [Usage](#usage)
- [Testing](#testing)
- [Configuration](#configuration)
- [Future Development](#future-development)
- [Contributing](#contributing)
- [License](#license)
- [Contact](#contact)

---

## Overview

This project implements the core components of an electronic exchange-style matching engine:

- event-driven order processing
- bid and ask book maintenance
- price-time priority matching
- trade generation and execution reporting
- order book analytics
- modular architecture for future performance extensions

It is designed as a systems-oriented C++ project that reflects how trading infrastructure is often structured in practice: a performance-sensitive core engine, an input pipeline, analytics utilities, and a future benchmarking layer.

---

## Key Features

- **Limit Order Book Engine**  
  Maintains bid and ask sides of the market and supports efficient order state management.

- **Price-Time Priority Matching**  
  Matches incoming orders deterministically according to standard exchange-style matching rules.

- **Order Lifecycle Support**  
  Supports adding, cancelling, and modifying orders, with trade and execution report generation.

- **Analytics Layer**  
  Computes spread, mid-price, depth-based volume, imbalance, and latency-tracking hooks.

- **Extensible Project Structure**  
  Organized into core, IO, analytics, and benchmark modules for maintainability and future performance work.

---

## Tech Stack

- **Language:** C++17
- **Compiler:** g++ / clang++ with C++17 support
- **Libraries:** C++ Standard Library
- **Architecture:** modular header/source separation
- **Domain:** matching engines, trading systems, market microstructure simulation

---

## Repository Structure

```text
low-latency-order-book/
├── benchmarks/          # Benchmark entry points and future performance experiments
├── data/                # Sample input data and replay files
├── docs/                # Supporting notes and diagrams
├── include/
│   ├── analytics/       # BookStats, LatencyTracker
│   ├── benchmark/       # BenchmarkRunner
│   ├── common/          # Shared types and utilities
│   ├── core/            # Matching engine, order book, trades, reports
│   └── io/              # Event parsing, reading, snapshot writing
├── src/
│   ├── analytics/
│   ├── benchmark/
│   ├── core/
│   └── io/
├── tests/               # Unit and edge-case tests
└── README.md
```

## Installation

### Prerequisites

Make sure you have
- a C++ 17-compatible compiler: g++ 9+ recommended OR clang++ with c++ 17 support
- a Unix-like shell, macOS terminal, Linux terminal, or Git Bash / WSL on Windows
- Git

### Clone the Repository

```bash
git clone https://github.com/nam643/low-latency-order-book.git
cd low-latency-order-book
```

### Build the project

Compile the full project from the repository root:

```bash
g++ -std=c++17 -Wall -Wextra -Iinclude \
src/main.cpp \
src/core/*.cpp \
src/io/*.cpp \
src/analytics/*.cpp \
src/benchmark/*.cpp \
-o orderbook
```

If your shell does not expand *.cpp, use explicit source files instead:

```bash
g++ -std=c++17 -Wall -Wextra -Iinclude \
src/main.cpp \
src/core/OrderBook.cpp \
src/core/MatchingEngine.cpp \
src/core/PriceLevel.cpp \
src/io/Event.cpp \
src/io/CSVParser.cpp \
src/io/EventReader.cpp \
src/io/SnapshotWriter.cpp \
src/analytics/BookStats.cpp \
src/analytics/LatencyTracker.cpp \
src/benchmark/BenchmarkRunner.cpp \
-o orderbook
```

---

## Usage

### Run the Main Executable

```bash
./orderbook
```

### Run the Main executable

```bash
./orderbook
```

### Example Workflow

1. Read a stream of order events
2. Process each event through the matching engine
3. Update the order book state
4. Generate execution reports and trades
5. Inspect analytics and output snapshots

Example output may include:
- accepted or rejected order events
- generated trades
- final bid/ask state
- computed analytics such as spread and mid-price

---

## Testing

This project can be tested at three levels: build validation, unit tests, and end-to-end execution.

### 1. Build Validation

This confirms that the project compiles and links successfully end-to-end:

```bash
g++ -std=c++17 -Wall -Wextra -Iinclude \
src/main.cpp \
src/core/*.cpp \
src/io/*.cpp \
src/analytics/*.cpp \
src/benchmark/*.cpp \
-o orderbook
./orderbook
```

### 2. Unit Tests

Compile and run test_order_book:

```bash
g++ -std=c++17 -Wall -Wextra -Iinclude \
tests/test_order_book.cpp \
src/core/OrderBook.cpp \
src/core/PriceLevel.cpp \
-o test_order_book
./test_order_book
```

Compile and run test_cancel_modify:

```bash
g++ -std=c++17 -Wall -Wextra -Iinclude \
tests/test_cancel_modify.cpp \
src/core/OrderBook.cpp \
src/core/PriceLevel.cpp \
-o test_cancel_modify
./test_cancel_modify
```

Compile and run test_matching_engine:

```bash
g++ -std=c++17 -Wall -Wextra -Iinclude \
tests/test_matching_engine.cpp \
src/core/OrderBook.cpp \
src/core/MatchingEngine.cpp \
src/core/PriceLevel.cpp \
src/io/Event.cpp \
-o test_matching_engine
./test_matching_engine
```

Compile and run test_edge_cases:

```bash
g++ -std=c++17 -Wall -Wextra -Iinclude \
tests/test_edge_cases.cpp \
src/core/OrderBook.cpp \
src/core/MatchingEngine.cpp \
src/core/PriceLevel.cpp \
src/io/Event.cpp \
-o test_edge_cases
./test_edge_cases
```

### 3. End-to-End testing

A reviewer can validate the project by checking that:

- the code compiles cleanly
- the executable runs successfully
- order insertion updates the book correctly
- cancel and modify operations behave correctly
- matches generate the correct trade output
- analytics produce sensible values

---

## Future Development

Final phase, focused on benchmarking and deeper performance evaluation, is intentionally left as future development.

Planned work includes:
- reproducible benchmark suite for add, cancel, modify, and match paths
- latency measurement with percentile statistics
- throughput testing under synthetic workloads
- profiling of hot paths and allocation behavior
- experiments with more cache-friendly data structures
- performance regression tracking
- richer historical replay support
- CI-based automated build and test validation

---

## Contact

For questions, suggestions, or bug reports:

- open an issue on this repository
- contact the maintainer via GitHub
- email: hainamail1710@gmail.com

---

## Author

Nam Pham

Built as a C++ systems project exploring the foundations of low-latency trading infrastructure, matching engine design, and market simulation.
