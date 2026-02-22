# Student Attendance Management System

A comprehensive C++ application suite for managing student attendance, grades, and class information. This project includes multiple integrated modules for tracking attendance sessions, managing student records, and generating detailed reports.

---

## 📋 Table of Contents

- [Features](#features)
- [Project Structure](#project-structure)
- [System Requirements](#system-requirements)
- [Installation](#installation)
- [Usage Guide](#usage-guide)
- [Module Documentation](#module-documentation)
- [File Format](#file-format)
- [Examples](#examples)
- [Troubleshooting](#troubleshooting)
- [Future Enhancements](#future-enhancements)

---

## ✨ Features

### Core Features

- **Student Management**: Add, view, update, and delete student records
- **Attendance Tracking**: Mark attendance by date and student ID
- **Grade Management**: Record and manage student grades
- **File I/O**: Save and load student data from persistent storage
- **Report Generation**: Generate attendance summaries and detailed reports in CSV format
- **Session Management**: Start/end attendance sessions with automatic timestamp tracking
- **Input Validation**: Robust input validation with error handling
- **Statistics**: Calculate class averages, highest/lowest grades, and attendance percentages

### Advanced Features

- **Performance Reporting**: Group students by performance level (A-F grades)
- **Multiple Export Formats**: CSV export for spreadsheet integration
- **Date-based Attendance**: Track attendance across multiple dates
- **Detailed Student Views**: View comprehensive student information with attendance history
- **Interactive Menu System**: User-friendly command-line interface with clear navigation

---

## 📁 Project Structure

```
Mid-Semester/
│
├── AttendanceSession.cpp          # Session-based attendance tracking (Week 2)
├── Students_info.cpp              # Student record management and statistics
├── Marking-logic.cpp              # Attendance marking and reporting (Week 3)
├── File_saving_and_loading.cpp    # Advanced file I/O management
│
├── students.txt                   # Student data storage (auto-created)
├── students_export.csv            # CSV export file (auto-created)
├── attendance_report_week3.txt    # Weekly attendance report (auto-created)
├── save.txt                        # Additional save data
│
└── README.md                       # This file
```

---

## 💻 System Requirements

- **C++ Compiler**: C++11 or later (GCC, Clang, MSVC)
- **Operating System**: Windows, Linux, macOS
- **RAM**: Minimum 128 MB
- **Storage**: Minimum 5 MB for executable and data files

### Compilation

```bash
# Using G++ (Windows/Linux/macOS)
g++ -std=c++11 File_saving_and_loading.cpp -o FileManager.exe
g++ -std=c++11 Students_info.cpp -o StudentInfo.exe
g++ -std=c++11 Marking-logic.cpp -o MarkingLogic.exe
g++ -std=c++11 AttendanceSession.cpp -o AttendanceSession.exe

# Using Clang
clang++ -std=c++11 File_saving_and_loading.cpp -o FileManager
```

---

## 📦 Installation

### Step 1: Clone or Download
Download all `.cpp` files from the repository to your working directory.

### Step 2: Compile
Use your preferred C++ compiler to compile each module:

```bash
# Windows
g++ -std=c++11 File_saving_and_loading.cpp -o FileManager.exe

# Linux/macOS
g++ -std=c++11 File_saving_and_loading.cpp -o FileManager
```

### Step 3: Run
Execute the compiled executable:

```bash
# Windows
FileManager.exe

# Linux/macOS
./FileManager
```

---

## 🎯 Usage Guide

### 1. File Saving and Loading Module
**Main Program**: `File_saving_and_loading.cpp`

The most comprehensive module with advanced file management capabilities.

#### Features:
- Add students with ID, name, and grade
- Mark attendance for specific dates
- View all students in table format
- View detailed student information with attendance history
- Save data to persistent storage
- Load data from file
- Export to CSV format
- Run demonstration with sample data

#### Main Menu:
```
1. Add Student          - Register a new student
2. View All Students    - Display all students in table
3. View Student Details - Show detailed info for one student
4. Mark Attendance      - Record attendance by date
5. Save Data to File    - Persist data to students.txt
6. Load Data from File  - Read students from file
7. Export to CSV        - Generate spreadsheet file
8. Demo (Run Test)      - Execute demonstration
0. Exit                 - Close application
```

#### Example Workflow:
```
1. Add Sample Students
2. Mark Attendance for multiple dates
3. View all students
4. Export to CSV
5. Save and exit
```

---

### 2. Student Information Module
**Main Program**: `Students_info.cpp`

Dedicated student management with statistics and performance tracking.

#### Features:
- Add students with validation
- Update student grades
- Delete student records
- Display students by performance (A-F grades)
- Calculate class statistics (average, highest, lowest grades)
- Show passing/failing statistics
- Input validation with error messages

#### Main Menu:
```
1. Add Student              - Register a new student
2. View All Students        - Display all students
3. View Student Details     - Show detailed info
4. Update Student Grade     - Change a student's grade
5. Delete Student           - Remove a student record
6. Display Statistics       - Show class averages and counts
7. Display by Performance   - Group students by letter grade
0. Exit                     - Close application
```

#### Example Workflow:
```
1. Add 5 students with different grades
2. Display statistics
3. Update a student's grade
4. Display by performance to see updated groups
5. Exit
```

---

### 3. Marking Logic Module
**Main Program**: `Marking-logic.cpp`

Attendance marking for weekly tracking and automated reporting.

#### Features:
- Add students to attendance system
- Mark attendance by date (YYYY-MM-DD format)
- Generate attendance summary with percentages
- Export detailed report to file
- Automatic file saving after each operation
- Data persistence between sessions

#### Main Menu:
```
1. Add Student                    - Register a student
2. Mark Attendance                - Record attendance
3. Generate Attendance Summary    - Display table summary
4. Generate Detailed Report       - Save detailed report to file
0. Exit                           - Close application
```

#### Example Workflow:
```
1. Add students
2. Mark attendance for a specific date
3. Generate summary to view attendance
4. Export to file for records
5. Exit
```

---

### 4. Attendance Session Module
**Main Program**: `AttendanceSession.cpp`

Session-based attendance taking system (Week 2 requirement).

#### Features:
- Create attendance sessions for specific courses
- Start/end session with automatic timestamps
- Mark students present during active session
- View attendance with real-time statistics
- Display session information
- Input validation for student IDs

#### Main Menu:
```
1. Start Attendance Session         - Begin a new session
2. Mark Student Present             - Mark one student present
3. Show Current Attendance          - Display attendance table
4. Display Session Information      - Show course details
5. End Session & Show Summary       - Finish and summarize
0. Exit                             - Close application
```

#### Example Workflow:
```
1. Start session
2. Mark students present as they arrive
3. View attendance anytime during session
4. End session to see final report
5. Exit
```

---

## 📄 Module Documentation

### Class: FileManager (File_saving_and_loading.cpp)

```cpp
class FileManager {
public:
    FileManager(const string& file = "students.txt");
    
    // File Operations
    bool saveStudents(const vector<Student>& students);
    vector<Student> loadStudents();
    bool appendStudent(const Student& student);
    bool clearFile();
    
    // File Information
    bool fileExists() const;
    long getFileSize() const;
    
    // Export Functions
    bool exportToCSV(const vector<Student>& students, 
                     const string& csvFile);
};
```

### Class: Student (File_saving_and_loading.cpp)

```cpp
class Student {
public:
    Student(const string& id = "", const string& name = "", 
            float grade = 0.0f);
    
    // Getters
    string getId() const;
    string getName() const;
    float getGrade() const;
    vector<string> getAttendanceDates() const;
    int getAttendanceCount() const;
    
    // Setters
    void setId(const string& newId);
    void setName(const string& newName);
    void setGrade(float newGrade);
    void addAttendanceDate(const string& date);
    void removeAttendanceDate(const string& date);
    
    // Display
    void display() const;
    void displayWithAttendance() const;
};
```

### Class: StudentManager (Students_info.cpp)

```cpp
class StudentManager {
public:
    void addStudent(int id, const string& name, float grade);
    void deleteStudent(int id);
    void updateGrade(int id, float newGrade);
    
    // Display Functions
    void displayAll() const;
    void displayStudent(int id) const;
    void displayStatistics() const;
    void displayByPerformance() const;
    
    // Statistics
    float getAverageGrade() const;
    float getHighestGrade() const;
    float getLowestGrade() const;
};
```

### Class: AttendanceSession (AttendanceSession.cpp)

```cpp
class AttendanceSession {
public:
    AttendanceSession(const string& code, const string& title, 
                      const string& lecturer);
    
    void startSession();
    void endSession();
    void addStudent(const string& id, const string& name);
    void markPresent(const string& studentId);
    void showAttendance();
    
    // Getters
    string getCourseCode() const;
    string getDate() const;
    bool isActive() const;
};
```

---

## 📊 File Format

### students.txt Format
**Storage Format**: Pipe-delimited with semicolon-separated dates

```
StudentID|StudentName|Grade|Date1;Date2;Date3
01276345D|Ama Serwaa|85.50|2026-02-15;2026-02-16;2026-02-17
01298766D|Kofi Mensah|92.00|2026-02-15;2026-02-16
```

### students_export.csv Format
**CSV Format**: Standard comma-separated with quoted text

```csv
ID,Name,Grade,Attendance Count,Dates
01276345D,Ama Serwaa,85.50,3,"2026-02-15; 2026-02-16; 2026-02-17"
01298766D,Kofi Mensah,92.00,2,"2026-02-15; 2026-02-16"
```

### attendance_report_week3.txt Format
**Report Format**: Human-readable detailed report

```
╔════════════════════════════════════════════════════╗
║           WEEK 3 ATTENDANCE REPORT                 ║
╚════════════════════════════════════════════════════╝

─ Student: Ama Serwaa (ID: 01276345D)
  Number of days attended: 3
  Dates present: 2026-02-15, 2026-02-16, 2026-02-17
```

---

## 💡 Examples

### Example 1: Adding and Viewing Students

```
Choose option 1: Add Student
Enter Student ID: 01234567D
Enter Student Name: John Doe
Enter Grade (0-100): 85

✓ Student added successfully!

Choose option 2: View All Students
─────────────────────────────────────────────────────────
ID             Name                    Grade
─────────────────────────────────────────────────────────
01234567D      John Doe                Grade: 85.00
```

### Example 2: Marking Attendance

```
Choose option 2: Mark Attendance
Enter Student ID: 01234567D
Enter Date (YYYY-MM-DD): 2026-02-22
✓ Attendance marked.

Choose option 3: View Student Details
Enter Student ID to view: 01234567D

─ Student: John Doe (ID: 01234567D)
  Grade: 85.00
  Attendance Count: 1 days
  Attended: 2026-02-22
```

### Example 3: Generating Reports

```
Choose option 3: Generate Attendance Summary

╔═══════════════════════════════════════════════════════════╗
║                  ATTENDANCE SUMMARY                      ║
╚═══════════════════════════════════════════════════════════╝

ID          Name                      Present      Total      Percentage
─────────────────────────────────────────────────────────────────────────
01234567D   John Doe                  1            1          100.0%
```

---

## 🔧 Troubleshooting

### Issue: "Could not open file 'students.txt'"
**Solution**: The file will be created automatically on first save. Try:
1. Use option to add a student
2. Save the data (option 5 in File Manager)
3. This creates students.txt file

### Issue: Grade validation error
**Solution**: Grades must be between 0 and 100:
- Invalid: 150, -10, letters
- Valid: 85.5, 92.0, 78

### Issue: Attendance date format error
**Solution**: Use exact format YYYY-MM-DD:
- Valid: 2026-02-22
- Invalid: 22-02-2026, 2/22/2026

### Issue: Student ID not found
**Solution**: Verify:
1. Student was added correctly
2. ID is entered exactly as stored (case-sensitive)
3. Student hasn't been deleted

### Issue: Session won't start
**Solution**: Ensure:
1. No session is already active
2. Students have been added
3. Try option 1: "Start Attendance Session"

---

## 🚀 Future Enhancements

### Planned Features

1. **Database Integration**
   - Replace text files with SQLite database
   - Support for thousands of students
   - Better data relationships

2. **Advanced Reporting**
   - Generate PDF reports
   - Email notifications
   - Export to Excel with formatting

3. **Multi-Session Management**
   - Track multiple courses simultaneously
   - Compare attendance across sessions
   - Historical trend analysis

4. **User Authentication**
   - Lecturer login system
   - Role-based access (Admin, Lecturer, Student)
   - Audit logging

5. **GUI Interface**
   - Graphical user interface with Qt/GTK
   - Real-time graphing of statistics
   - Drag-and-drop file import

6. **Mobile Application**
   - Mobile app for attendance marking
   - QR code scanning support
   - Biometric authentication

7. **Attendance Patterns**
   - Identify frequently absent students
   - Predict future absences using ML
   - Alternative intervention recommendations

8. **Integration Features**
   - API for third-party tools
   - Canvas/Blackboard integration
   - Slack notifications

---

## 📝 Code Quality

### Best Practices Implemented

✓ **Object-Oriented Design**: Proper use of classes and encapsulation
✓ **Input Validation**: Comprehensive error checking and user guidance
✓ **Memory Management**: Proper use of vectors and STL containers
✓ **Error Handling**: Try-catch blocks and validation functions
✓ **Code Documentation**: Detailed comments and headers
✓ **User Interface**: Clear menus and formatted output
✓ **File Management**: Robust file I/O with error checking
✓ **String Handling**: Proper string parsing and validation

---

## 📸 System Architecture

```

            Main User Interface (Menu)                

                                                      
│  ┌──────────────┐  ┌──────────────┐  ┌────────────┐│
│  │   Student    │  │  Attendance  │  │   File     ││
│  │   Manager    │  │   Session    │  │  Manager   ││
│  └──────────────┘  └──────────────┘  └────────────┘│
│         │                 │                 │        │
│         └─────────────────┴─────────────────┘        │
│                     │                                │
├─────────────────────┼────────────────────────────────┤
│          Data Layer (File I/O & Validation)         │
├─────────────────────┼────────────────────────────────┤
│                     │                                │
│    students.txt (Data)  CSV Export (Reports)        │
│                                                      │
└─────────────────────────────────────────────────────┘
```

---

## 📞 Support and Contact

For issues, suggestions, or contributions:
- Review the troubleshooting section
- Check the code comments for functionality details
- Verify file formats match specification
- Ensure C++11 or later compiler is used

---

## 📄 License

This project is provided for educational purposes as part of coursework.

---

## ✍️ Changelog

### Version 1.0 (February 2026)

**File_saving_and_loading.cpp**
- Implemented comprehensive FileManager class
- Added Student class with full functionality
- Created menu-driven interface
- Implemented file I/O with error handling
- Added CSV export functionality

**Students_info.cpp**
- Refactored original code for better structure
- Added StudentManager class
- Implemented statistics calculation
- Added performance-based grouping
- Improved validation and error messages

**Marking-logic.cpp**
- Refactored for code consistency
- Improved output formatting
- Enhanced error messages
- Added visual separators and indicators
- Better organized functions

**AttendanceSession.cpp**
- Complete reformat for readability
- Improved class structure
- Added session information display
- Enhanced output formatting
- Improved code organization

**README.md**
- Comprehensive documentation created
- Usage guide for all modules
- Installation instructions
- File format specifications
- Troubleshooting guide
- Future enhancement roadmap

---

**Last Updated**: February 22, 2026
**Version**: 1.0
**Status**: Ready for Production
