#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <limits>
#include <numeric> 

using namespace std;


struct Location {
    int id;
    double x, y; 
};


struct Driver {
    int id;
    Location currentLocation;
    vector<Location> route;
};

// Function to calculate distance between two locations
double calculateDistance(const Location &a, const Location &b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

// Floyd-Warshall Algorithm for finding shortest paths
void floydWarshall(vector<vector<double>> &dist, int V) {
    for (int k = 0; k < V; ++k) {
        for (int i = 0; i < V; ++i) {
            for (int j = 0; j < V; ++j) {
                if (dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }
}

vector<int> jobSequenceScheduling(const vector<int> &profits) {
    vector<int> jobs(profits.size());
    iota(jobs.begin(), jobs.end(), 0);
    sort(jobs.begin(), jobs.end(), [&](int a, int b) {
        return profits[a] > profits[b];
    });
    return jobs;
}

// K-means Clustering for initial delivery assignment
void kMeansClustering(vector<Location> &locations, vector<vector<Location>> &clusters, int k) {
    vector<Location> centroids(k);
    for (int i = 0; i < k; ++i) {
        centroids[i] = locations[i];
    }

    bool changed;
    do {
        changed = false;
        clusters.clear();
        clusters.resize(k);

        for (const auto &location : locations) {
            int nearest = 0;
            double minDist = calculateDistance(location, centroids[0]);
            for (int i = 1; i < k; ++i) {
                double dist = calculateDistance(location, centroids[i]);
                if (dist < minDist) {
                    minDist = dist;
                    nearest = i;
                }
            }
            clusters[nearest].push_back(location);
        }

        for (int i = 0; i < k; ++i) {
            double sumX = 0, sumY = 0;
            for (const auto &location : clusters[i]) {
                sumX += location.x;
                sumY += location.y;
            }
            Location newCentroid = {i, sumX / clusters[i].size(), sumY / clusters[i].size()};
            if (newCentroid.x != centroids[i].x || newCentroid.y != centroids[i].y) {
                changed = true;
                centroids[i] = newCentroid;
            }
        }
    } while (changed);
}


vector<Location> travelingSalesman(const vector<Location> &locations, const vector<vector<double>> &distMatrix) {
    vector<bool> visited(locations.size(), false);
    vector<Location> route;
    Location current = locations[0];
    route.push_back(current);
    visited[0] = true;

    for (int i = 1; i < locations.size(); ++i) {
        int nearest = -1;
        double minDist = numeric_limits<double>::max();
        for (int j = 0; j < locations.size(); ++j) {
            if (!visited[j]) {
                double dist = distMatrix[current.id][locations[j].id];
                if (dist < minDist) {
                    minDist = dist;
                    nearest = j;
                }
            }
        }
        if (nearest != -1) {
            visited[nearest] = true;
            route.push_back(locations[nearest]);
            current = locations[nearest];
        }
    }
    return route;
}

int main() {
    int numDrivers, numLocations;
    cout << "Enter number of drivers: ";
    cin >> numDrivers;
    cout << "Enter number of delivery locations: ";
    cin >> numLocations;

    vector<Driver> drivers(numDrivers);
    vector<Location> locations(numLocations);

    for (int i = 0; i < numDrivers; ++i) {
        drivers[i].id = i + 1;
        cout << "Enter starting location (x, y) for driver " << i + 1 << ": ";
        cin >> drivers[i].currentLocation.x >> drivers[i].currentLocation.y;
    }

    for (int i = 0; i < numLocations; ++i) {
        locations[i].id = i + 1;
        cout << "Enter coordinates (x, y) for location " << i + 1 << ": ";
        cin >> locations[i].x >> locations[i].y;
    }

    // Generate a profits vector for Job Sequence Scheduling
    vector<int> profits(numLocations);
    for (int i = 0; i < numLocations; ++i) {
        cout << "Enter profit/priority for location " << i + 1 << ": ";
        cin >> profits[i];
    }

    vector<int> jobSequence = jobSequenceScheduling(profits);


    int V = numLocations + numDrivers;
    vector<vector<double>> distMatrix(V, vector<double>(V, numeric_limits<double>::max()));
    for (int i = 0; i < V; ++i) {
        distMatrix[i][i] = 0;
    }

    for (int i = 0; i < numLocations; ++i) {
        for (int j = i + 1; j < numLocations; ++j) {
            double dist = calculateDistance(locations[i], locations[j]);
            distMatrix[locations[i].id][locations[j].id] = dist;
            distMatrix[locations[j].id][locations[i].id] = dist;
        }
    }

    for (const auto &driver : drivers) {
        for (const auto &location : locations) {
            double dist = calculateDistance(driver.currentLocation, location);
            distMatrix[driver.id][location.id] = dist;
            distMatrix[location.id][driver.id] = dist;
        }
    }

    floydWarshall(distMatrix, V);

   
    vector<vector<Location>> clusters(numDrivers);
    kMeansClustering(locations, clusters, numDrivers);

    
    for (int i = 0; i < numDrivers; ++i) {
        drivers[i].route = travelingSalesman(clusters[i], distMatrix);
    }

   
    for (const auto &driver : drivers) {
        cout << "Driver " << driver.id << " delivery route: ";
        for (const auto &location : driver.route) {
            cout << "(" << location.x << ", " << location.y << ") ";
        }
        cout << endl;
    }

    return 0;
}
