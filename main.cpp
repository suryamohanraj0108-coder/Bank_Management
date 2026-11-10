#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

class BankAccount {
private:
    int accNo;
    char name[50];
    float balance;

public:
    void createAccount() {
        cout << "Enter Account Number: ";
        cin >> accNo;

        cout << "Enter Customer Name: ";
        cin.ignore();
        cin.getline(name, 50);

        cout << "Enter Initial Balance: ";
        cin >> balance;
    }

    void showAccount() const {
        cout << "\nAccount Number : " << accNo;
        cout << "\nCustomer Name  : " << name;
        cout << "\nBalance         : " << balance << endl;
    }

    int getAccNo() const {
        return accNo;
    }

    void deposit(float amount) {
        balance += amount;
    }

    bool withdraw(float amount) {
        if (amount > balance) {
            return false;
        }
        balance -= amount;
        return true;
    }

    float getBalance() const {
        return balance;
    }
};

void createNewAccount() {
    BankAccount acc;

    ofstream outFile("bank.dat", ios::binary | ios::app);

    acc.createAccount();

    outFile.write(reinterpret_cast<char*>(&acc), sizeof(acc));

    outFile.close();

    cout << "\nAccount Created Successfully!\n";
}

void displayAllAccounts() {
    BankAccount acc;

    ifstream inFile("bank.dat", ios::binary);

    if (!inFile) {
        cout << "\nFile not found!\n";
        return;
    }

    cout << "\n===== Account Details =====\n";

    while (inFile.read(reinterpret_cast<char*>(&acc), sizeof(acc))) {
        acc.showAccount();
        cout << "\n---------------------------\n";
    }

    inFile.close();
}

void depositAmount() {
    int number;
    float amount;
    bool found = false;

    BankAccount acc;

    fstream file("bank.dat", ios::binary | ios::in | ios::out);

    cout << "Enter Account Number: ";
    cin >> number;

    while (file.read(reinterpret_cast<char*>(&acc), sizeof(acc))) {
        if (acc.getAccNo() == number) {
            cout << "Enter Amount to Deposit: ";
            cin >> amount;

            acc.deposit(amount);

            int pos = -1 * static_cast<int>(sizeof(acc));
            file.seekp(pos, ios::cur);

            file.write(reinterpret_cast<char*>(&acc), sizeof(acc));

            cout << "\nAmount Deposited Successfully!\n";
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "\nAccount Not Found!\n";
    }

    file.close();
}

void withdrawAmount() {
    int number;
    float amount;
    bool found = false;

    BankAccount acc;

    fstream file("bank.dat", ios::binary | ios::in | ios::out);

    cout << "Enter Account Number: ";
    cin >> number;

    while (file.read(reinterpret_cast<char*>(&acc), sizeof(acc))) {
        if (acc.getAccNo() == number) {
            cout << "Enter Amount to Withdraw: ";
            cin >> amount;

            if (acc.withdraw(amount)) {
                int pos = -1 * static_cast<int>(sizeof(acc));
                file.seekp(pos, ios::cur);

                file.write(reinterpret_cast<char*>(&acc), sizeof(acc));

                cout << "\nWithdrawal Successful!\n";
            }
            else {
                cout << "\nInsufficient Balance!\n";
            }

            found = true;
            break;
        }
    }

    if (!found) {
        cout << "\nAccount Not Found!\n";
    }

    file.close();
}

void balanceInquiry() {
    int number;
    bool found = false;

    BankAccount acc;

    ifstream inFile("bank.dat", ios::binary);

    cout << "Enter Account Number: ";
    cin >> number;

    while (inFile.read(reinterpret_cast<char*>(&acc), sizeof(acc))) {
        if (acc.getAccNo() == number) {
            cout << "\n===== Account Details =====\n";
            acc.showAccount();
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "\nAccount Not Found!\n";
    }

    inFile.close();
}

int main() {
    int choice;

    do {
        cout << "\n====== Bank Management System ======";
        cout << "\n1. Create Account";
        cout << "\n2. Deposit Amount";
        cout << "\n3. Withdraw Amount";
        cout << "\n4. Balance Inquiry";
        cout << "\n5. Display All Accounts";
        cout << "\n6. Exit";

        cout << "\n\nEnter Your Choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            createNewAccount();
            break;

        case 2:
            depositAmount();
            break;

        case 3:
            withdrawAmount();
            break;

        case 4:
            balanceInquiry();
            break;

        case 5:
            displayAllAccounts();
            break;

        case 6:
            cout << "\nThank You for Using Bank Management System!\n";
            break;

        default:
            cout << "\nInvalid Choice! Please Try Again.\n";
        }

    } while (choice != 6);

    return 0;
}