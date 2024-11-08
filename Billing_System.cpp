#include <iostream>
#include <fstream>
#include <sstream>
#include <windows.h>
using namespace std;

class Bill
{
private:
    string Item;
    int Rate, Quantity;

public:
    Bill() : Item(""), Rate(0), Quantity(0) {}

    void setItem(string item)
    {
        Item = item;
    }

    void setRate(int rate)
    {
        Rate = rate;
    }

    void setQuant(int quant)
    {
        Quantity = quant;
    }

    string getItem()
    {
        return Item;
    }

    int getRate()
    {
        return Rate;
    }

    int getQuant()
    {
        return Quantity;
    }
};

void addItem(Bill b)
{
    bool close = false;
    while (!close)
    {
        int choice;
        cout << "\t1. Add" << endl;
        cout << "\t2. close" << endl;
        cout << "\tEnter Choice: ";
        cin >> choice;

        if (choice == 1)
        {
            system("cls");
            string item;
            int rate, quant;

            cout << "\tEnter Item Name: ";
            cin >> item;
            b.setItem(item);

            cout << "\tEnter Rate of Item: ";
            cin >> rate;
            b.setRate(rate);

            cout << "\tEnter Quantity of Item: ";
            cin >> quant;
            b.setQuant(quant);

            ofstream out("F:/C++ Projects/Bill.txt", ios::app);

            if (!out)
            {
                cout << "\tError: File Can't Open!" << endl;
            }
            else
            {
                out << "\t" << b.getItem() << " : " << b.getRate() << " : " << b.getQuant() << endl
                    << endl;
            }
            out.close();
            cout << "\tItem Added Successfully!!" << endl;
            Sleep(3000);
            system("cls");
        }

        else if (choice == 2)
        {
            system("cls");
            close = true;
            cout << "\tBack To Main Menu" << endl;
            Sleep(2000);
        }
    }
}

void printBill()
{
    system("cls");
    int count = 0;
    bool close = false;

    while (!close)
    {
        system("cls");
        int choice;
        cout << "\t1. Add Bill" << endl;
        cout << "\t2. Close Session" << endl;
        cout << "\tEnter Choice: ";
        cin >> choice;

        if (choice == 1)
        {
            string item;
            int quant;
            cout << "\tEnter Item: ";
            cin >> item;
            cout << "\tEnter Quantity: ";
            cin >> quant;

            ifstream in("F:/C++ Projects/Bill.txt");
            ofstream out("F:/C++ Projects/Bill_Show.txt");

            string line;
            bool found = false;
            bool quantityUpdated = false;

            while (getline(in, line))
            {
                stringstream ss(line);
                string itemName;
                int itemRate, itemQuant;
                char delimeter;

                ss >> itemName >> delimeter >> itemRate >> delimeter >> itemQuant;

                if (item == itemName)
                {
                    found = true;
                    if (quant <= itemQuant)
                    {
                        int amount = itemRate * quant;
                        cout << "\t Item | Rate | Quantity | Amount" << endl;
                        cout << "\t" << itemName << " | " << itemRate << " | " << quant << " | " << amount << endl;

                        int newQuantity = itemQuant - quant;
                        count += amount;
                        out << itemName << " : " << itemRate << " : " << newQuantity << endl;
                        quantityUpdated = true;
                    }
                    else
                    {
                        cout << "\tSorry, " << item << " is not available in the requested quantity" << endl;
                        out << line << endl; // original line back if quantity is insufficient
                    }
                }
                else
                {
                    out << line << endl; // Write other items as-is
                }
            }

            if (!found)
            {
                cout << "\tItem Not Available!" << endl;
            }

            out.close();
            in.close();

            if (quantityUpdated)
            {
                remove("F:/C++ Projects/Bill.txt");
                rename("F:/C++ Projects/Bill_Show.txt", "F:/C++ Projects/Bill.txt");
            }
            else
            {
                remove("F:/C++ Projects/Bill_Show.txt");
            }
            Sleep(5000);
        }
        else if (choice == 2)
        {
            close = true;
            cout << "\tCounting Total Bill" << endl;
            Sleep(2000);
        }
    }

    system("cls");
    cout << endl << endl;
    cout << "\tTotal Bill ------------------ : " << count << endl << endl;
    cout << "\tThank You For Shopping With Us!!" << endl;
    Sleep(5000);
}

int main()
{
    Bill b;
    boolean exit = false;
    while (!exit)
    {
        system("cls");
        int val;
        cout << "\tWelcome To Super Merket Billing System" << endl;
        cout << "\t**************************************" << endl;
        cout << "\t\t1. Add Item" << endl;
        cout << "\t\t2. Generate Bill" << endl;
        cout << "\t\t3. Exit" << endl;
        cout << "\t\tEnter Choice: ";
        cin >> val;

        if (val == 1)
        {
            system("cls");
            addItem(b);
            Sleep(3000);
        }
        else if (val == 2)
        {
            printBill();
        }
        else if (val == 3)
        {
            system("cls");
            cout << "\tGood Luck!!" << endl;
            Sleep(3000);
            exit = true;
            system("cls");
        }
    }
}