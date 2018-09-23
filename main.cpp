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

    Student(string n, string u, string e, grade pres, grade es, grade proj)
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
    return 0; //REMOVE
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
