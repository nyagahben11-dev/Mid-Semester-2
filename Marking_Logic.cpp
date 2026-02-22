#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <limits>
#include <sstream>

using namespace std;

// Structure to hold student data
struct Student {
    string id;
    string name;
    vector<string> dates;  // Dates present
};

// Function to validate integer input
int getValidInt(int minVal, int maxVal, const string& prompt) {
    int value;
    while (true) {
        cout << prompt;
        if (cin >> value && value >= minVal && value <= maxVal) {
            return value;
        }
cout << "Invalid input. Please enter a number between " << minVal << " and " << maxVal << ".\n";
cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

// Function to validate string input (non-empty)
string getValidString(const string& prompt) {
    string input;
    while (true) {
        cout << prompt;
        getline(cin, input);
        if (!input.empty()) {
            return input;
        }
cout << "Input cannot be empty.\n";
    }
}

// Load students from file
vector<Student> loadStudents() {
    vector<Student> students;
    ifstream file("students.txt");
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            Student s;
            getline(ss, s.id, ',');
            getline(ss, s.name, ',');
            string date;
            while (getline(ss, date, ',')) {
                if (!date.empty()) {
                    s.dates.push_back(date);
                }
            }
            students.push_back(s);
        }
        file.close();
    }
    return students;
}

// Save students to file
void saveStudents(const vector<Student>& students) {
    ofstream file("students.txt");
    for (const auto& s : students) {
        file << s.id << "," << s.name;
        for (const auto& d : s.dates) {
            file << "," << d;
        }
file << "\n";
    }
    file.close();
}

// Add a new student
void addStudent(vector<Student>& students) {
    Student s;
    s.id = getValidString("Enter student ID: ");
    s.name = getValidString("Enter student name: ");
    students.push_back(s);
    saveStudents(students);
cout << "Student added successfully.\n";
}

// Mark attendance for a date
void markAttendance(vector<Student>& students) {
    string date = getValidString("Enter date (YYYY-MM-DD): ");
cout << "Marking attendance for " << date << ":\n";
    for (auto& s : students) {
        int present = getValidInt(0, 1, "Is " + s.name + " present? (0=No, 1=Yes): ");
        if (present == 1) {
            s.dates.push_back(date);
        }
    }
    saveStudents(students);
cout << "Attendance marked for " << date << ".\n";
}

// Generate summary report
void generateSummary(const vector<Student>& students) {
    if (students.empty()) {
cout << "No students found.\n";
        return;
    }
cout << "\nAttendance Summary:\n";
cout << left << setw(10) << "ID" << setw(20) << "Name" << setw(10) << "Present" << setw(10) << "Total" << setw(10) << "Percentage" << "\n";
cout << string(60, '-') << "\n";
    for (const auto& s : students) {
        int totalDays = 1;  // Assume week 3 has 1 marking for simplicity; extend as needed
        int present = s.dates.size();
        double perc = (present * 100.0) / totalDays;
cout << left << setw(10) << s.id << setw(20) << s.name << setw(10) << present << setw(10) << totalDays << fixed << setprecision(1) << setw(10) << perc << "%\n";
    }
}

// Generate detailed report to file
void generateReport(const vector<Student>& students) {
ofstream file("attendance_report_week3.txt");
file << "Week 3 Attendance Report\n";
file << "========================\n\n";
    for (const auto& s : students) {
file << "Student: " << s.name << " (ID: " << s.id << ")\n";
file << "Present on: ";
for (size_t i = 0; i < s.dates.size(); ++i) {
    file << s.dates[i];
    if (i < s.dates.size() - 1) file << ", ";
}
file << "\n";
    }
    file.close();
cout << "Detailed report saved to attendance_report_week3.txt\n";
}

// Main menu
int main() {
    vector<Student> students = loadStudents();
    int choice;
    do {
cout << "\n=== Week 3 Attendance System ===\n";
cout << "1. Add Student\n";
cout << "2. Mark Attendance\n";
cout << "3. Generate Summary\n";
cout << "4. Generate Detailed Report\n";
cout << "0. Exit\n";
        choice = getValidInt(0, 4, "Enter choice: ");
        switch (choice) {
            case 1: addStudent(students); break;
            case 2: markAttendance(students); break;
            case 3: generateSummary(students); break;
            case 4: generateReport(students); break;
case 0: cout << "Exiting...\n"; break;
        }
    } while (choice != 0);
    return 0;
}