/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <bits/stdc++.h>
using namespace std;

struct Expense {
    int id;
    string date;
    string category;
    string description;
    double amount;
};

vector<Expense> expenses;
const string filename = "expenses.txt";

void loadData() {
    expenses.clear();
    ifstream fin(filename);

    Expense e;
    while (fin >> e.id >> e.date >> e.category) {
        fin.ignore();
        getline(fin, e.description, '|');
        fin >> e.amount;
        expenses.push_back(e);
    }

    fin.close();
}

void saveData() {
    ofstream fout(filename);

    for (auto &e : expenses) {
        fout << e.id << " "
             << e.date << " "
             << e.category << " ";
        fout << e.description << "|";
        fout << e.amount << "\n";
    }

    fout.close();
}

void addExpense() {
    Expense e;

    e.id = expenses.empty() ? 1 : expenses.back().id + 1;

    cout << "Enter Date (DD-MM-YYYY): ";
    cin >> e.date;

    cout << "Enter Category: ";
    cin >> e.category;

    cin.ignore();

    cout << "Enter Description: ";
    getline(cin, e.description);

    cout << "Enter Amount: ";
    cin >> e.amount;

    expenses.push_back(e);
    saveData();

    cout << "\nExpense Added Successfully!\n";
}

void viewExpenses() {
    if (expenses.empty()) {
        cout << "\nNo expenses found.\n";
        return;
    }

    cout << "\n-------------------------------------------------------------\n";
    cout << "ID\tDate\t\tCategory\tAmount\tDescription\n";
    cout << "-------------------------------------------------------------\n";

    for (auto &e : expenses) {
        cout << e.id << "\t"
             << e.date << "\t"
             << e.category << "\t\t"
             << e.amount << "\t"
             << e.description << "\n";
    }
}

void totalExpense() {
    double sum = 0;

    for (auto &e : expenses)
        sum += e.amount;

    cout << "\nTotal Spending = " << sum << "\n";
}

void searchCategory() {
    string cat;
    cout << "Enter Category: ";
    cin >> cat;

    bool found = false;

    for (auto &e : expenses) {
        if (e.category == cat) {
            found = true;
            cout << "\nID: " << e.id
                 << "\nDate: " << e.date
                 << "\nDescription: " << e.description
                 << "\nAmount: " << e.amount
                 << "\n";
        }
    }

    if (!found)
        cout << "No records found.\n";
}

void deleteExpense() {
    int id;
    cout << "Enter Expense ID to delete: ";
    cin >> id;

    bool found = false;

    for (int i = 0; i < expenses.size(); i++) {
        if (expenses[i].id == id) {
            expenses.erase(expenses.begin() + i);
            found = true;
            break;
        }
    }

    if (found) {
        saveData();
        cout << "Expense Deleted.\n";
    } else {
        cout << "Expense ID not found.\n";
    }
}

int main() {

    loadData();

    while (true) {
        cout << "\n========== Expense Tracker ==========\n";
        cout << "1. Add Expense\n";
        cout << "2. View Expenses\n";
        cout << "3. Search by Category\n";
        cout << "4. Total Spending\n";
        cout << "5. Delete Expense\n";
        cout << "6. Exit\n";
        cout << "Choose option: ";

        int choice;
        cin >> choice;

        switch (choice) {
            case 1:
                addExpense();
                break;

            case 2:
                viewExpenses();
                break;

            case 3:
                searchCategory();
                break;

            case 4:
                totalExpense();
                break;

            case 5:
                deleteExpense();
                break;

            case 6:
                cout << "Thank you!\n";
                return 0;

            default:
                cout << "Invalid Choice!\n";
        }
    }
}