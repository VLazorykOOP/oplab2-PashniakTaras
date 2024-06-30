#include <iostream>
#include <thread>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <mutex>

using namespace std;

const double PI = 3.14159265358979323846;
const int MALE_STUDENTS = 5;
const int FEMALE_STUDENTS = 5;
const double V = 1.0;  // Speed
const double R = 10.0; // Radius for female students
const int N = 3;       // Time interval for direction change in seconds

mutex mtx; // Mutex for thread-safe output

void male_student_movement(int id) {
    srand(time(0) + id); // Seed for random direction change
    double x = 0.0, y = 0.0; // Initial position
    double angle = (rand() % 360) * PI / 180.0; // Initial random direction

    while (true) {
        // Move in the current direction
        x += V * cos(angle);
        y += V * sin(angle);

        // Change direction randomly every N seconds
        this_thread::sleep_for(chrono::seconds(N));
        angle = (rand() % 360) * PI / 180.0;

        // Output the current position
        mtx.lock();
        cout << "Male Student " << id << ": (" << x << ", " << y << ")\n";
        mtx.unlock();
    }
}

void female_student_movement(int id) {
    double angle = 0.0; // Start at angle 0
    double x = R, y = 0.0; // Initial position on the circle

    while (true) {
        // Move along the circle
        angle += V / R;
        x = R * cos(angle);
        y = R * sin(angle);

        // Output the current position
        mtx.lock();
        cout << "Female Student " << id << ": (" << x << ", " << y << ")\n";
        mtx.unlock();

        // Sleep for a short time to simulate continuous movement
        this_thread::sleep_for(chrono::milliseconds(100));
    }
}

int main() {
    vector<thread> threads;

    // Create threads for male students
    for (int i = 0; i < MALE_STUDENTS; ++i) {
        threads.push_back(thread(male_student_movement, i));
    }

    // Create threads for female students
    for (int i = 0; i < FEMALE_STUDENTS; ++i) {
        threads.push_back(thread(female_student_movement, i));
    }

    // Join all threads
    for (auto& thread : threads) {
        thread.join();
    }

    return 0;
}
