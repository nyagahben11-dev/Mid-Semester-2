#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <ctime>    
using namespace std;


// Simple structure to represent a Student

struct Student {
    string id;          
    string name;
    bool present = false;
};


// AttendanceSession class (main requirement of Week 2)

class AttendanceSession {
private:
    string courseCode;
    string courseTitle;
    string lecturerName;
    string date;           // format: YYYY-MM-DD
    string startTime;      // format: HH:MM
    vector<Student> students;
    bool sessionActive = false;

public:
    // Constructor
    AttendanceSession(string code, string title, string lecturer) {
        courseCode = code;
        courseTitle = title;
        lecturerName = lecturer;
        
        // Set current date automatically (optional)
        time_t now = time(0);
        tm* ltm = localtime(&now);
        char dateStr[11];
        strftime(dateStr, sizeof(dateStr), "", ltm);
        date = dateStr;

        startTime = "Pending";
        sessionActive = false;
    }

    // Start the attendance session
    void startSession() {
        if (sessionActive) {
            cout << "Session is already active!\n";
            return;
        }

        sessionActive = true;
        time_t now = time(0);
        tm* ltm = localtime(&now);
        char timeStr[6];
        strftime(timeStr, sizeof(timeStr), "", ltm);
        startTime = timeStr;

        
        cout << "Attendance session STARTED\n";
        cout << courseCode << " EEE227 " << courseTitle << endl;
        cout << "Date:02-22-2026 " << date << "   Time:12:00pm " << startTime << endl;
        cout << "Lecturer: " << lecturerName << endl;
       
    }

    // Mark a student present by ID
    void markPresent(string studentId) {
        if (!sessionActive) {
            cout << "No active session! Start session first.\n";
            return;
        }

        for (auto& student : students) {
            if (student.id == studentId) {
                if (student.present) {
                    cout << "Student " << studentId << " is already marked present.\n";
                } else {
                    student.present = true;
                    cout << "Student " << student.name << " (" << studentId << ") marked PRESENT.\n";
                }
                return;
            }
        }
        cout << "Student with ID " << studentId << " not found in this class.\n";
    }

    // Add student to the class list
    void addStudent(string id, string name) {
        students.push_back({id, name, false});
        cout << "Added student: " << name << " (" << id << ")\n";
    }

    // Show current attendance summary
    void showAttendance() {
        cout << "\n───────────── ATTENDANCE SUMMARY ─────────────\n";
        cout << left << setw(15) << "ID" 
             << setw(30) << "Name" 
             << "Status\n";
        cout << string(60, '-') << endl;

        int presentCount = 0;
        for (const auto& s : students) {
            cout << left << setw(15) << s.id
                 << setw(30) << s.name
                 << (s.present ? "Present" : "Absent") << endl;
            if (s.present) presentCount++;
        }

        cout << string(60, '-') << endl;
        cout << "Total students: " << students.size() 
             << "   Present: " << presentCount 
             << " (" << fixed << setprecision(1) 
             << (students.size() > 0 ? (presentCount * 100.0 / students.size()) : 0) 
             << "%)\n\n";
    }

    // End session
    void endSession() {
        if (!sessionActive) {
            cout << "No active session to end.\n";
            return;
        }
        sessionActive = false;
        cout << "\nAttendance session ENDED.\n";
        showAttendance();
    }

    // Getters (optional)
    string getCourseCode() const { return courseCode; }
    string getDate() const { return date; }
    bool isActive() const { return sessionActive; }
};


// Main menu-driven program

int main() {
    
    cout << "     SIMPLE ATTENDANCE SYSTEM\n";
    
    // Create one lecture session (you can later make vector of sessions)
    AttendanceSession lecture("COMP 251", "Data Structures", "Dr. Kwame Ansah");

    // Sample students (in real program you would load from file)
    lecture.addStudent("01276345D", "Ama Serwaa");
    lecture.addStudent("01298766D", "Kofi Mensah");
    lecture.addStudent("01287657D", "Efua Ofori");
    lecture.addStudent("01292008D", "Yaw Boateng");
    lecture.addStudent("01240179D", "Abena Darko");
    lecture.addStudent("01240176D", "Nyagah Benedict Manny");

    int choice;
    string studentId;

    do {
        cout << "\nMENU:\n";
        cout << "1. Start Attendance Session\n";
        cout << "2. Mark Student Present\n";
        cout << "3. Show Current Attendance\n";
        cout << "4. End Session & Show Summary\n";
        cout << "5. Exit\n";
        cout << "Choice: ";
        cin >> choice;
        cin.ignore(); // clear newline

        switch (choice) {
            case 1:
                lecture.startSession();
                break;

            case 2:
                cout << "Enter student ID: ";
                getline(cin, studentId);
                lecture.markPresent(studentId);
                break;

            case 3:
                lecture.showAttendance();
                break;

            case 4:
                lecture.endSession();
                break;

            case 5:
                cout << "Goodbye!\n";
                break;

            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 5);

    return 0;
}