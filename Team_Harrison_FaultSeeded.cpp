//=================================== File: Team_Harrison_FaultSeeded.cpp ======
//= Authors: Team Harrison...
//=   Ashton Honeggar
//=   Ricardo Carrion
//=   Francis Villalpando
//=-----------------------------------------------------------------------------
//= Running notes:
//=   GNU compile: g++ Team_Harrison_NoFault.cpp -o Team_Harrison_NoFault
//=   Run: ./Team_Harrison_NoFault
//=-----------------------------------------------------------------------------
//= Program description:
//=   Command Line Interfaced program that acts as a gradebook.
//=   User can add students, search for students, edit or delete entries, as
//=   well as save to/load from a plaintext file.
//=-----------------------------------------------------------------------------
//= Import gradebook -> File syntax:
//=   The syntax for the file to load students from is in plaintext, with one
//=   field per line, and a blank line between students.
//=   The order of fields is: uid, name, email, presentation, essay, project
//==============================================================================

#include <iostream> // Needed for cin/cout
#include <fstream>  // Needed for file I/O
#include <vector>   // Needed for memory store of students

using namespace std;

// grade
// enumeration to specify integer values of letter grades
enum grade { A = 4, B = 3, C = 2, D = 1, F = 0 };
grade stog(string); // string to grade function
string gtos(grade); // grade to string function

class Student; //REMOVE

typedef vector<Student*> sv;            // Student vector
typedef vector<Student*>::iterator si;  // Student iterator


// class to define Student entries
class Student {
    public:

    // Data members
    string name;
    string uid;
    string email;
    grade presentation;
    grade essay;
    grade project;

    // Constructor
    Student(string n, string u, string e, grade pres = F, grade es = F, grade proj = F)
    : name(n), uid(u), email(e), presentation(pres), essay(es), project(proj) {}

    // Object methods
    void updateStudent(Student *newStudent);//REMOVE "*"
    string toString();
    string toPrintableString();

    // Static methods
    static void readFile(string filepath);
    static void writeFile(string filepath);
    static si searchByName(string name);
    static si searchByID(string uid);
    static si searchByEmail(string email);
};

// function declarations
void addStudent();
void manageStudent(si);//REMOVE "si"

sv studentList; // In-memory list of students

// main()
// Prompts user for action, loops cli and calls functions when needed
int main()
{
    int choice, choice2; // store user input

    // Store Student members
    string filename, name, uid, email, trash;
    grade presentation, essay, project;

    while (true) { // Main loop
        cout << endl;
        cout << "===========================" << endl;
        cout << "Choose an option:" << endl;
        cout << "1 - Load from file" << endl;
        cout << "2 - Save to file" << endl;
        cout << "3 - Add student" << endl;
        cout << "4 - Search/Manage student" << endl;
        cout << "0 - QUIT" << endl;
        cout << "===========================" << endl;
        cin >> choice;
        getline(cin, trash); // Deletes the '\n' character from cin

        switch (choice) { // Main switch
            case 1:
                cout << endl;
                cout << "Type the name of the file you wish to load: ";
                getline(cin, filename);
                Student::readFile(filename);//REMOVE "Student::"
                break;
            case 2:
                cout << endl;
                cout << "Type the name of the file you wish to save: ";
                getline(cin, filename);
                Student::writeFile(filename);
                break;
            case 3:
                addStudent();
                break;
            case 4:
                cout << endl;
                cout << "Search for a student to manage them:" << endl;
                cout << "1 - Search by name" << endl;
                cout << "2 - Search by UID" << endl;
                cout << "3 - Search by email" << endl;
                cout << "0 - BACK" << endl;
                cin >> choice2;
                getline(cin, trash);

                switch (choice2) { // secondary switch
                    case 1:
                        cout << "Name of student: ";
                        getline(cin, name);
                        manageStudent(Student::searchByName(name));
                        break;
                    case 2:
                        cout << "UID of student: ";
                        getline(cin, uid);//CHANGE "uid" TO "name"
                        manageStudent(Student::searchByID(uid));
                        break;
                    case 3:
                        cout << "Email of student: ";
                        getline(cin, email);//CHANGE "email" TO "name"
                        manageStudent(Student::searchByEmail(email));
                        break;
                    case 0:
                    default: break;
                }
                cout << endl;
                break; //REMOVE

            case 0:
            default: return 0;
        }
    }
    return 0; //REMOVE
} // end of main()

// addStudent()
// Prompts user for input of each data member
void addStudent() {
    string name, uid, email, temp;
    grade presentation, essay, project;

    cout << "Name: ";
    getline(cin, name);

    cout << "UID: ";
    getline(cin, uid);

    cout << "Email: ";
    getline(cin, email);

    cout << "Grade on presentation (A/B/C/D/F): ";
    getline(cin, temp);
    presentation = stog(temp);

    cout << "Grade on essay (A/B/C/D/F): ";
    getline(cin, temp);
    essay = stog(temp);

    cout << "Grade on project (A/B/C/D/F): ";
    getline(cin, temp);
    project = stog(temp);

    // Adds new Student to list
    studentList.push_back(new Student(name, uid, email, presentation, essay, project));
}

// manageStudent()
// Prompts the user for options on managing the selected student
// si iter is the iterator returned by a Student::searchBy___() call
void manageStudent(si iter) {
    int choice;
    string name, uid, email, temp, trash;
    grade presentation, essay, project;

    // Check that the iterator did not reach end of list
    if (iter == studentList.end()) {
        cout << "Student not found" << endl;
        return;
    }

    // Prompt user for management option
    cout << endl;
    cout << (*iter)->toPrintableString() << endl;
    cout << endl;
    cout << "Choose an option to manage: " << endl;
    cout << "1 - Edit" << endl;
    cout << "2 - Delete" << endl;
    cout << "0 - CANCEL" << endl;
    cin >> choice;
    getline(cin, trash); // clears '\n' from cin

    switch (choice) {
        case 1:
            cout << "Name (" << (*iter)->name << "): ";
            getline(cin, name);
            name = (name == "" ? (*iter)->name : name);

            cout << "UID (" << (*iter)->uid << "): ";
            getline(cin, uid);
            uid = (uid == "" ? (*iter)->uid : uid);

            cout << "Email (" << (*iter)->email << "): ";
            getline(cin, email);
            email = (email == "" ? (*iter)->email : email);

            cout << "Grade on presentation (" << gtos((*iter)->presentation) << "): ";
            getline(cin, temp);
            presentation = (temp == "" ? (*iter)->presentation : stog(temp));

            cout << "Grade on essay (" << gtos((*iter)->essay) << "): ";
            getline(cin, temp);
            essay = (temp == "" ? (*iter)->essay : stog(temp));

            cout << "Grade on project (" << gtos((*iter)->project) << "): ";
            getline(cin, temp);
            project = (temp == "" ? (*iter)->project : stog(temp));

            (*iter)->updateStudent(new Student(name, uid, email, presentation, essay, project));
            break;
        case 2:
            studentList.erase(iter);
            break;
        case 0:
        default: return;
    }
}

// stog()
// turns a String inTO a Grade
// defaults to F
grade stog(string str) {
    if (str == "A" || str == "a" || str == "4") {
        return A;
    }

    if (str == "B" || str == "b" || str == "3") {
        return B;
    }

    if (str == "C" || str == "c" || str == "2") {
        return C;
    }

    if (str == "D" || str == "d" || str == "1") {
        return D;
    }

    return F;
}

// gtos()
// turns a Grade inTO a String
string gtos(grade g) {
    switch (g) {
        case A: return "A";
        case B: return "B";
        case C: return "C";
        case D: return "D";
        case F: return "F";
        default: return "";
    }
}

// Student methods

// updateStudent()
// copies student values into existing student
void Student::updateStudent(Student *newStudent) {
    this->name = newStudent->name;
    this->uid = newStudent->uid;
    this->email = newStudent->email;
    this->presentation = newStudent->presentation;
    this->essay = newStudent->essay;
    this->project = newStudent->project;
    delete newStudent;//REMOVE
}

// toString()
// makes student a string for file output
string Student::toString() {
    string ret = uid;
    ret += "\n" + name;
    ret += "\n" + email;
    ret += "\n" + gtos(presentation);
    ret += "\n" + gtos(essay);
    ret += "\n" + gtos(project);
    return ret;
}

// toPrintableString()
// makes student a string with formatting for printing
string Student::toPrintableString() {
    string ret = "UID: " + uid + "\n";
    ret += "Name: " + name + "\n";
    ret += "Email: " + email + "\n";
    ret += "Presentation: " + gtos(presentation) + "\n";
    ret += "Essay: " + gtos(essay) + "\n";
    ret += "Project: " + gtos(project) + "\n";
    return ret;
}

// readFile()
// loads students from file into memory
void Student::readFile(string filepath) {
    studentList.clear(); //clear current list //REMOVE
    ifstream file;
    file.open(filepath);
    si iter;
    string u, n, e, line;
    grade pres, es, proj;

    while (getline(file, line)) {
        u = line;
        getline(file, n);
        getline(file, e);

        getline(file, line);
        pres = stog(line);

        getline(file, line);
        es = stog(line);

        getline(file, line);
        proj = stog(line);

        studentList.push_back(new Student(n, u, e, pres, es, proj));
        getline(file, line); // Gets rid of extra newline
    }

    file.close();//REMOVE
}

// writeFile()
// writes current list into specified file
void Student::writeFile(string filepath) {
    ofstream file;
    file.open(filepath);
    si iter;

    for (iter = studentList.begin(); iter != studentList.end(); iter++) {
        file << (*iter)->toString() << "\n\n";//CHANGE THIS TO . INSTEAD OF ->
    }

    file.close(); //REMOVE
}

// searchByName()
// searches list for the name given. Must match exactly (case-sensitive)
si Student::searchByName(string name) {
    si iter;

    for (iter = studentList.begin(); iter != studentList.end(); iter++) {
        if ((*iter)->name == name) {
            return iter;
        }
    }
    return iter;
}

// searchByID()
// searches list for the uid given. Must match exactly (case-sensitive)
si Student::searchByID(string uid) {
    si iter;

    for (iter = studentList.begin(); iter != studentList.end(); iter++) {
        if ((*iter)->uid == uid) {
            return iter;
        }
    }
    return iter;
}

// searchByEmail()
// searches list for the email given. Must match exactly (case-sensitive)
si Student::searchByEmail(string email) {
    si iter;

    for (iter = studentList.begin(); iter != studentList.end(); iter++) {
        if ((*iter)->email == email) {
            return iter;
        }
    }
    return iter;
}
