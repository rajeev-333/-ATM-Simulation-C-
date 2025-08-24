#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <windows.h> // For Sleep
#include <limits>
#include <conio.h>   // For getch() to mask PIN

using namespace std;

class ATM {
private:
    long int account_No;
    string name;
    int PIN;
    double balance;
    string mobile_No;
    vector<string> transactionHistory;
    bool isLocked = false;
    int pinAttempts = 0;

public:
    ATM() {}
    ATM(long int acc, string nm, int pin, double bal, string mob)
        : account_No(acc), name(nm), PIN(pin), balance(bal), mobile_No(mob) {}

    string serialize() {
        return to_string(account_No) + "," + name + "," + to_string(PIN) + "," +
               to_string(balance) + "," + mobile_No;
    }

    void fromString(string line) {
        size_t pos = 0;
        int fieldCount = 0;
        string token;
        while ((pos = line.find(",")) != string::npos && fieldCount < 4) {
            token = line.substr(0, pos);
            switch (fieldCount) {
                case 0: account_No = stol(token); break;
                case 1: name = token; break;
                case 2: PIN = stoi(token); break;
                case 3: balance = stod(token); break;
            }
            line.erase(0, pos + 1);
            fieldCount++;
        }
        mobile_No = line;
    }

    long int getAccountNo() { return account_No; }
    string getName() { return name; }
    int getPIN() { return PIN; }
    double getBalance() { return balance; }
    string getMobileNo() { return mobile_No; }
    bool getLockStatus() { return isLocked; }

    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            transactionHistory.push_back("Deposited: " + to_string(amount));
            cout << "\nDeposit successful. New balance: " << balance;
        } else {
            cout << "\nInvalid amount!";
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
    }

    void cashWithDraw(double amount) {
        if (amount > 0 && amount <= balance && amount <= 20000) {
            balance -= amount;
            transactionHistory.push_back("Withdrew: " + to_string(amount));
            cout << "\nPlease collect your cash.";
            cout << "\nAvailable Balance: " << balance;
        } else if (amount > 20000) {
            cout << "\nWithdrawal limit exceeded (max 20000).";
        } else {
            cout << "\nInvalid input or insufficient balance.";
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
    }

    void setMobile(string mob_prev, string mob_new) {
        if (mob_prev == mobile_No) {
            mobile_No = mob_new;
            cout << "\nMobile number updated successfully.";
        } else {
            cout << "\nIncorrect old mobile number!";
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
    }

    void lockAccount() {
        isLocked = true;
        cout << "\nAccount locked due to multiple failed attempts.";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
    }

    void trackPinAttempts() {
        pinAttempts++;
        if (pinAttempts >= 3) {
            lockAccount();
        }
    }

    void resetPinAttempts() { pinAttempts = 0; }

    void unlockAccount() {
        isLocked = false;
        pinAttempts = 0;
        cout << "\nAccount unlocked. Please try again.";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
    }

    void showUserDetails() {
        cout << "\n*** User Details ***";
        cout << "\nAccount No: " << account_No;
        cout << "\nName: " << name;
        cout << "\nBalance: " << balance;
        cout << "\nMobile No.: " << mobile_No;
    }
};

vector<ATM> loadAccounts(string filename) {
    vector<ATM> accounts;
    ifstream file(filename);
    string line;
    if (!file) return accounts;
    while (getline(file, line)) {
        ATM acc;
        acc.fromString(line);
        accounts.push_back(acc);
    }
    file.close();
    return accounts;
}

void saveAccounts(string filename, vector<ATM>& accounts) {
    ofstream file(filename, ios::trunc);
    for (ATM& acc : accounts) {
        file << acc.serialize() << "\n";
    }
    file.close();
}

// Function to securely enter PIN with masking
int inputPIN() {
    string pinStr;
    char ch;
    while ((ch = _getch()) != 13) { // 13 = Enter key
        if (ch >= '0' && ch <= '9') { // Digit
            pinStr.push_back(ch);
            cout << '*';
        } else if (ch == 8 && !pinStr.empty()) { // Backspace
            pinStr.pop_back();
            cout << "\b \b"; // Erase last '*'
        }
    }
    return stoi(pinStr);
}

int main() {
    vector<ATM> accounts = loadAccounts("accounts.txt");

    if (accounts.empty()) {
        accounts.push_back(ATM(987654321, "Hardik", 1234, 50000, "9370054900"));
        accounts.push_back(ATM(123456789, "Aarav", 4321, 30000, "9876543210"));
        saveAccounts("accounts.txt", accounts);
    }

    while (true) {
        system("cls");
        long int accNo;
        int pin;
        cout << "\n*** ATM Login ***";
        cout << "\nEnter Account No: ";
        cin >> accNo;
        cout << "Enter PIN: ";
        pin = inputPIN(); // masked PIN input
        cout << endl;

        bool found = false;
        for (ATM& user : accounts) {
            if (user.getAccountNo() == accNo && user.getPIN() == pin) {
                if (user.getLockStatus()) {
                    cout << "\nAccount is locked. Please wait or contact support.";
                    found = true;
                    break;
                }
                user.resetPinAttempts();
                found = true;

                int choice;
                do {
                    system("cls");
                    cout << "\n\n*** ATM Menu ***";
                    cout << "\n1. Check Balance";
                    cout << "\n2. Cash Withdraw";
                    cout << "\n3. Deposit";
                    cout << "\n4. Update Mobile No.";
                    cout << "\n5. Show User Details";
                    cout << "\n6. Exit";
                    cout << "\nChoice: ";
                    cin >> choice;

                    if (choice == 1) {
                        cout << "\nBalance: " << user.getBalance();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cin.get();
                    } else if (choice == 2) {
                        double amt;
                        cout << "\nEnter amount: ";
                        cin >> amt;
                        user.cashWithDraw(amt);
                    } else if (choice == 3) {
                        double amt;
                        cout << "\nEnter deposit amount: ";
                        cin >> amt;
                        user.deposit(amt);
                    } else if (choice == 4) {
                        string oldMob, newMob;
                        cout << "\nEnter Old Mobile No.: ";
                        cin >> oldMob;
                        cout << "\nEnter New Mobile No.: ";
                        cin >> newMob;
                        user.setMobile(oldMob, newMob);
                    } else if (choice == 5) {
                        user.showUserDetails();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cin.get();
                    } else if (choice == 6) {
                        saveAccounts("accounts.txt", accounts);
                        break;
                    }

                } while (true);
                break;
            }
        }
        if (!found) {
            cout << "\nInvalid credentials!";
            for (ATM& user : accounts) {
                if (user.getAccountNo() == accNo) {
                    user.trackPinAttempts();
                    if (user.getLockStatus()) {
                        cout << "\nAccount locked. Waiting 30 seconds...";
                        Sleep(30000); // Windows sleep in ms
                        user.unlockAccount();
                    }
                }
            }
        }
        saveAccounts("accounts.txt", accounts);
    }
    return 0;
}
