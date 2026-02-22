#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <ctime>

using namespace std;


// Student Class - Represents a single student record

class Student {
private:
    string id;
    string name;
    float grade;
    vector<string> attendanceDates;

public:
    // Constructor
    Student(const string& studentId = "", const string& studentName = "", 
            float studentGrade = 0.0f)
        : id(studentId), name(studentName), grade(studentGrade) {}

    // Getters
    string getId() const { return id; }
    string getName() const { return name; }
    float getGrade() const { return grade; }
    vector<string> getAttendanceDates() const { return attendanceDates; }

    // Setters
    void setId(const string& newId) { id = newId; }
    void setName(const string& newName) { name = newName; }
    void setGrade(float newGrade) { grade = newGrade; }

    // Add attendance date
    void addAttendanceDate(const string& date) {
        if (find(attendanceDates.begin(), attendanceDates.end(), date) 
            == attendanceDates.end()) {
            attendanceDates.push_back(date);
        }
    }

    // Remove attendance date
    void removeAttendanceDate(const string& date) {
        auto it = find(attendanceDates.begin(), attendanceDates.end(), date);
        if (it != attendanceDates.end()) {
            attendanceDates.erase(it);
        }
    }

    // Get attendance count
    int getAttendanceCount() const { return attendanceDates.size(); }

    // Display student information
    void display() const {
        cout << left << setw(15) << id 
             << setw(25) << name 
             << "Grade: " << fixed << setprecision(2) << grade << endl;
    }

    // Display with attendance
    void displayWithAttendance() const {
        cout << "\n--- Student: " << name << " (ID: " << id << ") ---\n";
        cout << "Grade: " << fixed << setprecision(2) << grade << "\n";
        cout << "Attendance Count: " << getAttendanceCount() << " days\n";
        if (!attendanceDates.empty()) {
            cout << "Attended: ";
            for (size_t i = 0; i < attendanceDates.size(); ++i) {
                cout << attendanceDates[i];
                if (i < attendanceDates.size() - 1) cout << ", ";
            }
            cout << "\n";
        } else {
            cout << "No attendance records.\n";
        }
    }
};


// FileManager Class - Handles file I/O operations for student data


class FileManager {
private:
    string filename;
    const char DELIMITER = '|';
    const char DATE_DELIMITER = ';';

public:
    // Constructor
    explicit FileManager(const string& file = "students.txt") 
        : filename(file) {}

    // Set filename
    void setFilename(const string& file) { filename = file; }

    // Save students to file
    bool saveStudents(const vector<Student>& students) {
        ofstream file(filename);
        
        if (!file.is_open()) {
            cerr << "Error: Could not open file '" << filename 
                 << "' for writing.\n";
            return false;
        }

        try {
            for (const auto& student : students) {
                // Format: ID|Name|Grade|Date1;Date2;Date3
                file << student.getId() << DELIMITER 
                     << student.getName() << DELIMITER 
                     << fixed << setprecision(2) << student.getGrade() 
                     << DELIMITER;

                const auto& dates = student.getAttendanceDates();
                for (size_t i = 0; i < dates.size(); ++i) {
                    file << dates[i];
                    if (i < dates.size() - 1) file << DATE_DELIMITER;
                }
                file << "\n";
            }

            file.close();
            cout << " Successfully saved " << students.size() 
                 << " student(s) to '" << filename << "'\n";
            return true;

        } catch (const exception& e) {
            cerr << "Error while saving: " << e.what() << "\n";
            return false;
        }
    }

    // Load students from file
    vector<Student> loadStudents() {
        vector<Student> students;
        ifstream file(filename);

        if (!file.is_open()) {
            cerr << "Error: Could not open file '" << filename 
                 << "' for reading.\n";
            return students;
        }

        try {
            string line;
            int lineNumber = 0;

            while (getline(file, line)) {
                ++lineNumber;
                
                if (line.empty()) continue;

                stringstream ss(line);
                string id, name, gradeStr, datesStr;

                // Parse line
                if (!getline(ss, id, DELIMITER) || 
                    !getline(ss, name, DELIMITER) || 
                    !getline(ss, gradeStr, DELIMITER)) {
                    cerr << "Warning: Skipping malformed line " << lineNumber 
                         << "\n";
                    continue;
                }

                try {
                    float grade = stof(gradeStr);
                    Student student(id, name, grade);

                    // Parse attendance dates
                    if (getline(ss, datesStr)) {
                        stringstream dateSS(datesStr);
                        string date;
                        while (getline(dateSS, date, DATE_DELIMITER)) {
                            if (!date.empty()) {
                                student.addAttendanceDate(date);
                            }
                        }
                    }

                    students.push_back(student);

                } catch (const invalid_argument& e) {
                    cerr << "Warning: Invalid grade value at line " 
                         << lineNumber << ": " << gradeStr << "\n";
                }
            }

            file.close();
            cout << " Successfully loaded " << students.size() 
                 << " student(s) from '" << filename << "'\n";
            return students;

        } catch (const exception& e) {
            cerr << "Error while loading: " << e.what() << "\n";
            return students;
        }
    }

    // Append a single student to file
    bool appendStudent(const Student& student) {
        ofstream file(filename, ios::app);

        if (!file.is_open()) {
            cerr << "Error: Could not open file '" << filename 
                 << "' for appending.\n";
            return false;
        }

        try {
            file << student.getId() << DELIMITER 
                 << student.getName() << DELIMITER 
                 << fixed << setprecision(2) << student.getGrade() 
                 << DELIMITER;

            const auto& dates = student.getAttendanceDates();
            for (size_t i = 0; i < dates.size(); ++i) {
                file << dates[i];
                if (i < dates.size() - 1) file << DATE_DELIMITER;
            }
            file << "\n";

            file.close();
            cout << " Student added successfully.\n";
            return true;

        } catch (const exception& e) {
            cerr << "Error while appending: " << e.what() << "\n";
            return false;
        }
    }

    // Clear file
    bool clearFile() {
        ofstream file(filename, ios::trunc);
        
        if (!file.is_open()) {
            cerr << "Error: Could not clear file '" << filename << "'\n";
            return false;
        }

        file.close();
        cout << " File '" << filename << "' cleared.\n";
        return true;
    }

    // Check if file exists
    bool fileExists() const {
        ifstream file(filename);
        return file.good();
    }

    // Get file size in bytes
    long getFileSize() const {
        ifstream file(filename, ios::binary | ios::ate);
        if (!file.is_open()) return -1;
        return file.tellg();
    }

    // Export students to CSV format
    bool exportToCSV(const vector<Student>& students, 
                     const string& csvFile) {
        ofstream file(csvFile);

        if (!file.is_open()) {
            cerr << "Error: Could not open file '" << csvFile 
                 << "' for writing.\n";
            return false;
        }

        try {
            // Write header
            file << "ID,Name,Grade,Attendance Count,Dates\n";

            for (const auto& student : students) {
                file << student.getId() << ","
                     << student.getName() << ","
                     << fixed << setprecision(2) << student.getGrade() << ","
                     << student.getAttendanceCount() << ",\"";

                const auto& dates = student.getAttendanceDates();
                for (size_t i = 0; i < dates.size(); ++i) {
                    file << dates[i];
                    if (i < dates.size() - 1) file << "; ";
                }
                file << "\"\n";
            }

            file.close();
            cout << " Exported to CSV file: " << csvFile << "\n";
            return true;

        } catch (const exception& e) {
            cerr << "Error while exporting: " << e.what() << "\n";
            return false;
        }
    }
};


// Demo and Testing


void demonstrateFileManager() {
    cout << "\n" << string(70, '=') << "\n";
    cout << "     FILE MANAGER DEMONSTRATION\n";
    cout << string(70, '=') << "\n\n";

    FileManager manager("students.txt");

    // Create sample students
    vector<Student> students;
    
    Student s1("01276345D", "Ama Serwaa", 85.5f);
    s1.addAttendanceDate("2026-02-15");
    s1.addAttendanceDate("2026-02-16");
    s1.addAttendanceDate("2026-02-17");
    students.push_back(s1);

    Student s2("01298766D", "Kofi Mensah", 92.0f);
    s2.addAttendanceDate("2026-02-15");
    s2.addAttendanceDate("2026-02-16");
    students.push_back(s2);

    Student s3("01287657D", "Efua Ofori", 78.5f);
    s3.addAttendanceDate("2026-02-15");
    students.push_back(s3);

    // Save students
    cout << "\n1. SAVING DATA\n";
    cout << string(50, '-') << "\n";
    manager.saveStudents(students);

    // Load students
    cout << "\n2. LOADING DATA\n";
    cout << string(50, '-') << "\n";
    vector<Student> loadedStudents = manager.loadStudents();

    // Display loaded data
    cout << "\n3. DISPLAYING LOADED DATA\n";
    cout << string(50, '-') << "\n";
    cout << left << setw(15) << "ID" << setw(25) << "Name" 
         << "Grade\n";
    cout << string(50, '-') << "\n";
    for (const auto& student : loadedStudents) {
        student.display();
    }

    // Display with attendance details
    cout << "\n4. DETAILED VIEW WITH ATTENDANCE\n";
    cout << string(50, '-') << "\n";
    for (const auto& student : loadedStudents) {
        student.displayWithAttendance();
    }

    // Export to CSV
    cout << "\n5. EXPORTING TO CSV\n";
    cout << string(50, '-') << "\n";
    manager.exportToCSV(loadedStudents, "students_export.csv");

    // File info
    cout << "\n6. FILE INFORMATION\n";
    cout << string(50, '-') << "\n";
    cout << "File: students.txt\n";
    cout << "Exists: " << (manager.fileExists() ? "Yes" : "No") << "\n";
    cout << "Size: " << manager.getFileSize() << " bytes\n";

    cout << "\n" << string(70, '=') << "\n\n";
}


// Main Menu


int main() {
   
    cout << "           STUDENT FILE MANAGEMENT SYSTEM                       \n";
    cout << "              Save and Load Student Data                         \n";
   

    FileManager manager("students.txt");
    vector<Student> students;
    int choice;

    do {
        cout << "\n MAIN MENU \n";
        cout << " 1. Add Student                                                 \n";
        cout << " 2. View All Students                                           \n";
        cout << " 3. View Student Details                                        \n";
        cout << " 4. Mark Attendance                                             \n";
        cout << " 5. Save Data to File                                           \n";
        cout << " 6. Load Data from File                                         \n";
        cout << " 7. Export to CSV                                               \n";
        cout << " 8. Demo (Run Test)                                             \n";
        cout << " 0. Exit                                                        \n";
        cout << "   \n";
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1: {
                // Add Student
                cout << "\n--- Add New Student ---\n";
                string id, name;
                float grade;

                cout << "Enter Student ID: ";
                getline(cin, id);

                cout << "Enter Student Name: ";
                getline(cin, name);

                cout << "Enter Grade: ";
                cin >> grade;
                cin.ignore();

                students.push_back(Student(id, name, grade));
                cout << "Student added successfully!\n";
                break;
            }

            case 2: {
                // View All Students
                if (students.empty()) {
                    cout << "\n No students in memory. Load from file first.\n";
                } else {
                    cout << "\n--- All Students ---\n";
                    cout << left << setw(15) << "ID" << setw(25) 
                         << "Name" << "Grade\n";
                    cout << string(50, '-') << "\n";
                    for (const auto& student : students) {
                        student.display();
                    }
                }
                break;
            }

            case 3: {
                // View Student Details
                if (students.empty()) {
                    cout << "\n No students in memory.\n";
                } else {
                    cout << "Enter Student ID: ";
                    string searchId;
                    getline(cin, searchId);

                    bool found = false;
                    for (const auto& student : students) {
                        if (student.getId() == searchId) {
                            student.displayWithAttendance();
                            found = true;
                            break;
                        }
                    }
                    if (!found) {
                        cout << " Student not found.\n";
                    }
                }
                break;
            }

            case 4: {
                // Mark Attendance
                if (students.empty()) {
                    cout << "\n No students in memory.\n";
                } else {
                    cout << "Enter Student ID: ";
                    string attId;
                    getline(cin, attId);

                    cout << "Enter Date (YYYY-MM-DD): ";
                    string date;
                    getline(cin, date);

                    bool found = false;
                    for (auto& student : students) {
                        if (student.getId() == attId) {
                            student.addAttendanceDate(date);
                            cout << " Attendance marked.\n";
                            found = true;
                            break;
                        }
                    }
                    if (!found) {
                        cout << " Student not found.\n";
                    }
                }
                break;
            }

            case 5: {
                // Save to File
                manager.saveStudents(students);
                break;
            }

            case 6: {
                // Load from File
                students = manager.loadStudents();
                break;
            }

            case 7: {
                // Export to CSV
                manager.exportToCSV(students, "students_export.csv");
                break;
            }

            case 8: {
                // Demo
                demonstrateFileManager();
                break;
            }

            case 0: {
                cout << "\nExiting... Goodbye!\n\n";
                break;
            }

            default:
                cout << "\n Invalid choice. Please try again.\n";
        }

    } while (choice != 0);

    return 0;
}
