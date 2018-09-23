#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

enum grade { A = 4, B = 3, C = 2, D = 1, F = 0 };
grade stog(string);

class Student; //REMOVE

const string PRINT_HEADER = "UID\tName\t\tE-mail\t\tPresentation\tEssay\tProject";
typedef vector<Student*> sv;
typedef vector<Student*>::iterator si;

class Student {
    public:

    string name;
    string uid;
    string email;
    grade presentation;
    grade essay;
    grade project;

    Student(string n, string u, string e, grade pres = F, grade es = F, grade proj = F)
    : name(n), uid(u), email(e), presentation(pres), essay(es), project(proj) {}

    void updateStudent(Student newStudent);
    string studentToString();
    string studentToPrintableString();

    static void readFile(string filepath);
    static void writeFile(string filepath);
    static si searchByName(string name);
    static si searchByID(string uid);
    static si searchByEmail(string email);
};

sv studentList;

int main()
{
    int choice, choice2;
    string filename, name, uid, email;
    grade presentation, essay, project;

    while (true) {
        cout << "===========================" << endl;
        cout << "Choose an option:" << endl;
        cout << "1 - Load from file" << endl;
        cout << "2 - Save to file" << endl;
        cout << "3 - Add student" << endl;
        cout << "4 - Search/Manage student" << endl;
        cout << "0 - QUIT" << endl;
        cout << "===========================" << endl;
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Type the name of the file you wish to load: ";
                cin >> filename;
                Student::readFile(filename);//REMOVE "Student::"
                break;
            case 2:
                cout << "Type the name of the file you wish to save: ";
                cin >> filename;
                Student::writeFile(filename);
                break;
            case 3:
                addStudent();
                break;
            case 4:
                cout << "Search for a student to manage them:" << endl;
                cout << "1 - Search by name" << endl;
                cout << "2 - Search by UID" << endl;
                cout << "3 - Search by email" << endl;
                cout << "0 - BACK" << endl;
                cin >> choice2;

                switch (choice2) {
                    case 1:
                        cout << "Name of student: ";
                        cin >> name;
                        manageStudent(Student::searchByName(name));
                        break;
                    case 2:
                        cout << "UID of student: ";
                        cin >> uid;
                        manageStudent(Student::searchByID(uid));
                        break;
                    case 3:
                        cout << "Email of student: ";
                        cin >> email;
                        manageStudent(Student::searchByEmail(email));
                        break;
                    case 0:
                    default: break;
                }

            case 0:
            default: return 0;
        }
    }
    return 0; //REMOVE
}

void addStudent() {
    string name, uid, email, temp;
    grade presentation, essay, project;

    cout << "Name: ";
    cin >> name;

    cout << "UID: ";
    cin >> uid;

    cout << "Email: ";
    cin >> email;

    cout << "Grade on presentation (A/B/C/D/F): ";
    cin >> temp;
    presentation = stog(temp);

    cout << "Grade on essay (A/B/C/D/F): ";
    cin >> temp;
    essay = stog(temp);

    cout << "Grade on project (A/B/C/D/F): ";
    cin >> temp;
    project = stog(temp);

    studentList.push_back(new Student(name, uid, email, presentation, essay, project));
}

void manageStudent(si iter) {
    if (iter == studentList.end()) {
        cout << "Student not found" << endl;
        return;
    }

    cout << PRINT_HEADER << endl;
    cout << (*iter)->toPrintableString() << endl;
    cout << endl;
    cout << "Choose an option to manage"
}


void Student::updateStudent(Student newStudent) {
    this->name = newStudent.name;
    this->uid = newStudent.uid;
    this->email = newStudent.email;
    this->presentation = newStudent.presentation;
    this->essay = newStudent.essay;
    this->project = newStudent.project;
}

string Student::studentToString() {
    string ret = uid;
    ret += "\n" + name;
    ret += "\n" + email;
    ret += "\n" + presentation;
    ret += "\n" + essay;
    ret += "\n" + project;
    return ret;
}

string Student::studentToPrintableString() {
    string ret = uid;
    ret += "\t";
    ret += name;
    ret += "\t\t";
    ret += email;
    ret += "\t\t";
    ret += presentation;
    ret += "\t";
    ret += essay;
    ret += "\t";
    ret += project;
    return ret;
}

void Student::readFile(string filepath) {
    studentList.clear();//REMOVE
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

void Student::writeFile(string filepath) {
    ofstream file;
    file.open(filepath);
    si iter;

    for (iter = studentList.begin(); iter != studentList.end(); iter++) {
        file << (*iter)->studentToString() << "\n";//CHANGE THIS TO . INSTEAD OF ->
    }

    file.close(); //REMOVE
}

si Student::searchByName(string name) {
    si iter;

    for (iter = studentList.begin(); iter != studentList.end(); iter++) {
        if ((*iter)->name == name) {
            return iter;
        }
    }
    return iter;
}

si Student::searchByID(string uid) {
    si iter;

    for (iter = studentList.begin(); iter != studentList.end(); iter++) {
        if ((*iter)->uid == uid) {
            return iter;
        }
    }
    return iter;
}

si Student::searchByEmail(string email) {
    si iter;

    for (iter = studentList.begin(); iter != studentList.end(); iter++) {
        if ((*iter)->email == email) {
            return iter;
        }
    }
    return iter;
}

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
