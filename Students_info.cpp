#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Student class
class Student {
private:
    string name;
    int id;
    float grade;

public:
    Student(string n, int i, float g) {
        name = n;
        id = i;
        grade = g;
    }

    void display() {
        cout << "ID: " << id 
             << "Name: " << name
             << "Grade: " << grade << endl;
    }
};


int main() {
    vector<Student> students;
    int choice;

    do {
        cout << "\n--- Student Management System ---\n";
        cout << "1. Add Student\n";
        cout << "2. View Students\n";
        cout << "3. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            int id;
            string name;
            float grade;
            
   
            cout << "Enter student ID: ";
            cin >> id;

            cout << "Enter student name: ";
            getline(cin >>ws,name) ; 
            //cin >> name;

            cout << "Enter student grade: ";
            cin >> grade;

            students.push_back(Student(name, id, grade));
            cout << "Student added successfully!\n";
        }
        else if (choice == 2) {
            cout << "\n--- Student List ---\n";
            if (students.empty()) {
                cout << "No students added yet.\n";
            } else {
                for (auto &s : students) {
                    s.display();
                }
            }
        }
        else if (choice == 3) {
            cout << "Exiting program...\n";
        }
        else {
            cout << "Invalid choice!\n";
        }

    } while (choice != 3);


    return 0;
}