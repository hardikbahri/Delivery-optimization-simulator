# Delivery Route Optimization Simulator

## Overview

This project implements a Delivery Route Optimization Simulator that calculates the optimum route for multiple drivers to make all deliveries simultaneously, in the minimum possible time and distance. The algorithm combines techniques from Floyd-Warshall, Job Sequence Scheduling, Traveling Salesman, and K-means Clustering to achieve efficient route planning. This can be particularly useful for delivery applications like Swiggy, Zomato, Instamart, etc.

## Features

- Calculates the shortest paths between delivery locations using Floyd-Warshall Algorithm.
- Schedules jobs based on profit/priority using Job Sequence Scheduling.
- Clusters delivery locations using K-means Clustering for initial delivery assignment.
- Plans the optimum route for each driver using a greedy approach to solve the Traveling Salesman Problem (TSP).

## Algorithms Used

- **Floyd-Warshall Algorithm**: Finds the shortest paths between all pairs of locations.
- **Job Sequence Scheduling**: Orders delivery locations based on profit/priority.
- **K-means Clustering**: Groups locations into clusters to assign them to different drivers.
- **Traveling Salesman Problem (TSP)**: Finds the shortest possible route that visits each location once and returns to the starting point.

## Usage

### Input

- Number of drivers
- Number of delivery locations
- Starting coordinates for each driver
- Coordinates for each delivery location
- Profit/priority for each delivery location

### Output

- Optimized delivery route for each driver

## Getting Started

### Prerequisites

- C++ compiler (e.g., GCC)
- Basic understanding of C++ and algorithms

### Compilation and Execution

1. **Clone the Repository:**

    ```sh
    git clone <repository-url>
    cd delivery-route-optimization-simulator
    ```

2. **Compile the Code:**

    ```sh
    g++ -o delivery_simulator delivery_simulator.cpp -std=c++11
    ```

3. **Run the Executable:**

    ```sh
    ./delivery_simulator
    ```

4. **Follow the Prompts:**

    Enter the required inputs as prompted by the program.

## Example

### Input

```
Enter number of drivers: 2
Enter number of delivery locations: 3
Enter starting location (x, y) for driver 1: 0 0
Enter starting location (x, y) for driver 2: 5 5
Enter coordinates (x, y) for location 1: 1 1
Enter coordinates (x, y) for location 2: 2 2
Enter coordinates (x, y) for location 3: 3 3
Enter profit/priority for location 1: 10
Enter profit/priority for location 2: 20
Enter profit/priority for location 3: 30
```

### Output

```
Driver 1 delivery route: (1, 1) (2, 2) 
Driver 2 delivery route: (3, 3) 
```
