#include <iostream>
#include <fstream>
#include <string.h>
using namespace std;

class Student {
    int rno;
    char sname[20];
    char subject[20];
    int sub_code;
    float internal;
    float university;

public:
    Student() {
        rno = 0;
        strcpy(sname, "\0");
        strcpy(subject, "\0");
        sub_code = 0;
        internal = 0.0;
        university = 0.0;
    }

    int acceptRollno() {
        return rno;
    }

    void acceptDetails() {
        cout << "\nEnter Details:";
        cout << "\nRoll no: ";
        cin >> rno;
        cout << "Name: ";
        cin >> sname;
        cout << "Subject Code: ";
        cin >> sub_code;
        cout << "Subject name: ";
        cin >> subject;
        cout << "Internal Assessment Marks: ";
        cin >> internal;
        cout << "University Exam Marks: ";
        cin >> university;
    }

    void putData() {
        cout << "\nRoll No.: " << rno;
        cout << "\tName: " << sname;
        cout << "\nSubject Code: " << sub_code;
        cout << "\nSubject name: " << subject;
        cout << "\nInternal Assessment Marks: " << internal;
        cout << "\nUniversity Exam Marks: " << university << "\n";
    }
};

class Operations {
    ifstream fin;
    ofstream fout;
    fstream fs;

public:
    void addRecord();
    void show();
    void search(int);
    int DelRecord(int);
    int edit(int);
};

void Operations::addRecord() {
    Student r;
    r.acceptDetails();
    fout.open("Data", ios::binary | ios::app);
    fout.write((char*)&r, sizeof(r));
    fout.close();
}

void Operations::show() {
    Student r;
    fin.open("Data", ios::binary);
    fin.seekg(0, ios::beg);
    while (fin.read((char*)&r, sizeof(r))) {
        r.putData();
    }
    fin.close();
}

void Operations::search(int rno) {
    Student r;
    int flag = 0;
    fin.open("Data", ios::binary);
    fin.seekg(0, ios::beg);
    while (fin.read((char*)&r, sizeof(r))) {
        if (r.acceptRollno() == rno) {
            flag = 1;
            break;
        }
    }
    fin.close();
    if (flag == 1) {
        cout << "\nStudent Found:";
        r.putData();
    } else {
        cout << "\nStudent not Found";
    }
}

int Operations::DelRecord(int rno) {
    Student r;
    int flag = 0;
    fin.open("Data", ios::binary);
    fout.open("Temp", ios::binary | ios::app);
    fin.seekg(0, ios::beg);
    while (fin.read((char*)&r, sizeof(r))) {
        if (r.acceptRollno() == rno) {
            flag = 1;
        } else {
            fout.write((char*)&r, sizeof(r));
        }
    }
    fin.close();
    fout.close();
    remove("Data");
    rename("Temp", "Data");
    return flag;
}

int Operations::edit(int rno) {
    Student r;
    int flag = 0;
    fs.open("Data", ios::in | ios::out | ios::binary);
    fs.seekg(0, ios::beg);
    while (fs.read((char*)&r, sizeof(r))) {
        if (r.acceptRollno() == rno) {
            flag = 1;
            cout << "\nEnter New Details: ";
            r.acceptDetails();
            fs.seekp((int)fs.tellg() - sizeof(r), ios::beg);
            fs.write((char*)&r, sizeof(r));
            break;
        }
    }
    fs.close();
    return flag;
}

int main() {
    Operations f;
    int ch, n, i, flag = 0;
    do {
        cout << "\n\n\t------MENU-------";
        cout << "\n1. Build a Master Table";
        cout << "\n2. List a Table";
        cout << "\n3. Insert a new Entry";
        cout << "\n4. Delete Old Entry";
        cout << "\n5. Edit Entry";
        cout << "\n6. Search Entry";
        cout << "\n7. Exit";
        cout << "\nEnter your choice: ";
        cin >> ch;

        switch (ch) {
            case 1:
                if (flag == 0) {
                    cout << "\nEnter No. of Students to insert: ";
                    cin >> n;
                    for (i = 0; i < n; i++) {
                        f.addRecord();
                    }
                    flag = 1;
                } else {
                    cout << "\nSorry, table is already built.";
                }
                break;

            case 2:
                f.show();
                break;

            case 3:
                f.addRecord();
                break;

            case 4:
                cout << "\nEnter Roll No of Student to be Deleted: ";
                cin >> n;
                i = f.DelRecord(n);
                if (i == 1)
                    cout << "\nStudent Deleted Successfully";
                else
                    cout << "\nStudent not Found";
                break;

            case 5:
                cout << "\nEnter Roll No of Student to be Edited: ";
                cin >> n;
                i = f.edit(n);
                if (i == 1)
                    cout << "\nStudent Modified Successfully";
                else
                    cout << "\nStudent not Found";
                break;

            case 6:
                cout << "\nEnter Roll No of Student to be Searched: ";
                cin >> n;
                f.search(n);
                break;

            case 7:
                cout << "\nExiting...";
                break;

            default:
                cout << "\nInvalid Choice...";
        }
    } while (ch != 7);
    return 0;
}
