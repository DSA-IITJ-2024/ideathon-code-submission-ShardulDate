#include <iostream>
#include <fstream>
#include <unordered_map>
#include <set>
#include <map>
#include <vector>
#include <string>

using namespace std;
using std::to_string;

// Structure to represent a course schedule entry with room number
struct CourseScheduleEntry {
    string courseName;
    string classTime;
    int roomNumber;
};

// Function to perform graph coloring using backtracking
void colorCourseGraph(const unordered_map<string, set<string > > &courseGraph, map<string, int> &coloring, const string &node, int &chromaticNumber) {
    set<int> usedColors;

    // Check colors of adjacent nodes
    for (const string &adjacentCourse : courseGraph.at(node)) {
        if (coloring.find(adjacentCourse) != coloring.end()) {
            usedColors.insert(coloring[adjacentCourse]);
        }
    }

    // Assign the smallest available color
    for (int color = 1;; ++color) {
        if (usedColors.find(color) == usedColors.end()) {
            coloring[node] = color;
            chromaticNumber = max(chromaticNumber, color);
            break;
        }
    }

    // Recursively color the adjacent nodes
    for (const string &adjacentCourse : courseGraph.at(node)) {
        if (coloring.find(adjacentCourse) == coloring.end()) {
            colorCourseGraph(courseGraph, coloring, adjacentCourse, chromaticNumber);
        }
    }
}

// Function to display the schedule in a tabular form with auto-assigned room numbers
void displayCourseScheduleWithRooms(const unordered_map<string, set<string> > &courseGraph, const map<string, int> &coloring,
                              int chromaticNumber, const vector<int> &availableRooms) {
    cout << "\nNumber of time slots needed: " << chromaticNumber << endl;

    // Organize courses by color (time slot)
    map<int, vector<string> > coursesByColor;
    for (const auto &entry : coloring) {
        coursesByColor[entry.second].push_back(entry.first);
    }

    // Map room numbers to their corresponding time slots
    map<int, vector<CourseScheduleEntry> > scheduleWithRooms;

    int currentDay = 1; // 1 represents Monday
    int currentHour = 8;
    int currentMinute = 30;

    // Map course to the number of times it has been scheduled on a particular day
    unordered_map<string, int> coursesScheduledPerDay;

    for (int color = 1; color <= chromaticNumber; ++color) {
        for (const string &courseName : coursesByColor[color]) {
            int classesPerWeek;
            cout << "Enter the number of classes per week for " << courseName << ": ";
            cin >> classesPerWeek;

            for (int i = 0; i < classesPerWeek; ++i) {
                // Adjust the schedule if it's the lunch break
                if (currentHour == 12 && currentMinute >= 35 && currentMinute < 90) {
                    currentHour = 13;
                    currentMinute = 30;
                }

                int roomIndex = (i % availableRooms.size());
                int roomNumber = availableRooms[roomIndex];

                CourseScheduleEntry entry;
                entry.courseName = courseName;
                entry.classTime = to_string(currentHour) + ":" + (currentMinute < 10 ? "0" : "") + to_string(currentMinute);
                entry.roomNumber = roomNumber;

                // Check the number of times the course has been scheduled on the current day
                if (coursesScheduledPerDay[courseName] < 2) {
                    scheduleWithRooms[currentDay].push_back(entry);
                    coursesScheduledPerDay[courseName]++;
                } else {
                    // Move to the next day if more than two classes are scheduled for the current day
                    currentDay = (currentDay % 5) + 1;
                    currentHour = 8;
                    currentMinute = 30;
                    coursesScheduledPerDay.clear(); // Reset the count for the new day
                    --i; // Revisit the current class on the new day
                    continue;
                }

                // Move to the next time slot
                currentMinute += 60;
                if (currentMinute >= 60) {
                    currentHour += 1;
                    currentMinute -= 60;
                }

                // Add a 5-minute break between classes
                currentMinute += 5;

                // Move to the next day if the schedule exceeds the current day
                if (currentHour >= 14) {
                    currentDay = (currentDay % 5) + 1;
                    currentHour = 8;
                    currentMinute = 30;
                }
            }

            // Reset the count of scheduled classes for the next day
            coursesScheduledPerDay.clear();
        }
    }

    // Display the final schedule with room numbers
    cout << "\nClass Schedule with Room Numbers:\n";
    cout << "+-------------+-------------+-----------------------------+----------------------+\n";
    cout << "|     Day     |  Time Slot  |          Courses           |      Room Number     |\n";
    cout << "+-------------+-------------+-----------------------------+----------------------+\n";

    for (int day = 1; day <= 5; ++day) {
        cout << "| ";
        bool emptyEntry;

        switch (day) {
            case 1: cout << "Monday    "; break;
            case 2: cout << "Tuesday   "; break;
            case 3: cout << "Wednesday "; break;
            case 4: cout << "Thursday  "; break;
            case 5: cout << "Friday    "; break;
            
        }
        emptyEntry=false;

        cout << "| ";

        for (int color = 1; color <= chromaticNumber; ++color) {
            if (scheduleWithRooms[day].empty()) {
                cout << "| No class there            |                       No room assigned                   |\n";
                break;
            }

            if (color <= coursesByColor.size()) {
                for (const auto &classInfo : scheduleWithRooms[day]) {
                    if (!scheduleWithRooms[day].empty()) {
                        for (const string &scheduledCourse : coursesByColor[color]) {
                            if (scheduledCourse == classInfo.courseName) {
                                if (emptyEntry){
                                    cout<<"|           | ";

                                }
                                emptyEntry=true;

                                cout << "| " << classInfo.classTime << " | " << scheduledCourse << " ";
                                for (int i = scheduledCourse.length(); i < 22; ++i) {
                                    cout << " ";
                                }
                                cout << "| " << classInfo.roomNumber;
                                for (int i = to_string(classInfo.roomNumber).length(); i < 21; ++i) {
                                    cout << " ";
                                }
                                cout << "|\n";
                            }
                        }
                    }
                }
            }
        }

        cout << "+-------------+-------------+-----------------------------+----------------------+\n";
    }
}

void removeCourse(unordered_map<string, set<string > > &courseGraph, map<string, int> &coloring, const string &course) {
    // Remove the course from the graph
    courseGraph.erase(course);

    // Remove the course from the
