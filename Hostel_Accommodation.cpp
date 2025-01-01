#include <iostream>
#include <fstream>
#include <windows.h>
#include <sstream>
using namespace std;

class Hostel
{
private:
    string Name;
    int Rent, Bed;

public:
    Hostel(string name, int rent, int bed)
    {
        Name = name;
        Rent = rent;
        Bed = bed;
    }

    string getName()
    {
        return Name;
    }

    int getRent()
    {
        return Rent;
    }

    int getBed()
    {
        return Bed;
    }

    void reserve()
    {
        ifstream in("Hostel.txt");
        ofstream out("Hostel Temp.txt");

        string line;
        while (getline(in, line))
        {
            int pos = line.find("3star");
            if (pos != string::npos)
            {
                int bed = Bed - 1;
                Bed = bed;

                stringstream ss;
                ss << bed;
                string strBed = ss.str();

                int bedPos = line.find_last_of(':');
                line.replace(bedPos + 1, string::npos, strBed);
            }
            out << line << endl;
        }
        out.close();
        in.close();
        remove("Hostel.txt");
        rename("Hostel Temp.txt", "Hostel.txt");
        cout << "\tBed Reserved Successfully!!" << endl;
    }
};

class Student
{
private:
    string Name, RollNo, Address;

public:
    Student() : Name(""), RollNo(""), Address("") {}

    void setName(string name)
    {
        Name = name;
    }

    void setRollNo(string rollNo)
    {
        RollNo = rollNo;
    }

    void setAddress(string address)
    {
        Address = address;
    }

    string getName()
    {
        return Name;
    }

    string getRollNo()
    {
        return RollNo;
    }

    string getAddress()
    {
        return Address;
    }
};

int main()
{
    Hostel h("3star", 5000, 2);
    ofstream out("Hostel.txt");
    out << "\t" << h.getName() << ":" << h.getRent() << ":" << h.getBed() << endl
        << endl;
    cout << "Hostel Data Saved." << endl;
    out.close();

    Student s;

    bool exit = false;
    while (!exit)
    {
        system("cls");

        int val;
        cout << "\tWelcome to Hostel Accommodation System\n";
        cout << "\t***************************************\n";
        cout << "\t1) Reserve a Bed.\n";
        cout << "\t2) Exit.\n";
        cout << "\tEnter your choice: ";
        cin >> val;

        if (val == 1)
        {
            system("cls");
            string name, rollNo, address;
            cout << "\tEnter name of the Student: ";
            cin >> name;
            s.setName(name);

            cout << "\tEnter RollNo of the Student: ";
            cin >> rollNo;
            s.setRollNo(rollNo);

            cout << "\tEnter Address of the Student: ";
            cin >> address;
            s.setAddress(address);

            if (h.getBed() > 0)
            {
                h.reserve();
            }
            else if (h.getBed() == 0)
            {
                cout << "\tSorry, Bed is Currently Not Available!!" << endl;
            }

            ofstream outFile("Student.txt", ios::app);
            outFile << "\t" << s.getName() << ":" << s.getRollNo() << ":" << s.getAddress() << endl
                    << endl;
            Sleep(5000);
        }

        else if (val == 2)
        {
            system("cls");
            exit = true;
            cout << "Good Luck!" << endl;
            Sleep(3000);
        }
    }
}
