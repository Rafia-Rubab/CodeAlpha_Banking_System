#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <conio.h> // For getch()
#include <ctime>
using namespace std;

// ================= ACCOUNT CLASS =================
class Account {
public:
    int accountNumber;
    double balance;

    Account(int accNo = 0, double bal = 0) {
        accountNumber = accNo;
        balance = bal;
    }

    void deposit(double amount) {
        balance += amount;
        cout << "Deposit Successful!\n";
    }

    void withdraw(double amount) {
        if (amount > balance) {
            cout << "Insufficient Balance!\n";
            return;
        }
        balance -= amount;
        cout << "Withdrawal Successful!\n";
    }
};

// ================= CUSTOMER CLASS =================
class Customer {
public:
    int id;
    string name;
    string password;
    vector<Account> accounts;

    Customer(int i = 0, string n = "", string p = "") {
        id = i;
        name = n;
        password = p;
    }
};

// ================= FILE HANDLING =================
void saveCustomers(vector<Customer> &customers) {
    ofstream file("customers.txt");
    for (size_t i = 0; i < customers.size(); i++) {
        file << customers[i].id << " " << customers[i].name << " " << customers[i].password << endl;
    }
    file.close();
}

void loadCustomers(vector<Customer> &customers) {
    ifstream file("customers.txt");
    int id;
    string name, pass;
    while (file >> id >> ws) {
        getline(file, name, ' ');
        getline(file, pass);
        customers.push_back(Customer(id, name, pass));
    }
    file.close();
}

void saveAccounts(vector<Customer> &customers) {
    ofstream file("accounts.txt");
    for (size_t i = 0; i < customers.size(); i++) {
        for (size_t j = 0; j < customers[i].accounts.size(); j++) {
            file << customers[i].id << " " 
                 << customers[i].accounts[j].accountNumber << " " 
                 << customers[i].accounts[j].balance << endl;
        }
    }
    file.close();
}

void loadAccounts(vector<Customer> &customers) {
    ifstream file("accounts.txt");
    int cid, accNo;
    double bal;
    while (file >> cid >> accNo >> bal) {
        for (size_t i = 0; i < customers.size(); i++) {
            if (customers[i].id == cid) {
                customers[i].accounts.push_back(Account(accNo, bal));
            }
        }
    }
    file.close();
}

// ================= TRANSACTION HISTORY =================

void logTransaction(int custID, int accNo, string type, double amount) {
    ofstream file("transactions.txt", ios::app); // append mode
    time_t now = time(0);
    string dt = ctime(&now);  // convert ctime() char* to string
    if (!dt.empty() && dt.back() == '\n') dt.pop_back(); // remove newline
    file << custID << " " << accNo << " " << type << " " << amount << " " << dt << endl;
    file.close();
}

void viewTransactions(int custID) {
    ifstream file("transactions.txt");
    int id, accNo;
    double amt;
    string type, datetime;
    cout << "Recent Transactions:\n";
    while (file >> id >> accNo >> type >> amt) {
        getline(file, datetime); // read rest of the line (date & time)
        if (id == custID) {
            cout << "Account: " << accNo << " | " << type << " | Amount: " << amt 
                 << " | Time:" << datetime << endl;
        }
    }
    file.close();
}

// ================= PASSWORD INPUT =================
string getPassword() {
    string pass = "";
    char ch;
    while (true) {
        ch = getch();
        if (ch == 13) break; // Enter
        if (ch == 8) { // Backspace
            if (!pass.empty()) {
                pass.pop_back();
                cout << "\b \b";
            }
        } else {
            pass.push_back(ch);
            cout << '*';
        }
    }
    cout << endl;
    return pass;
}

// ================= LOGIN =================
Customer* login(vector<Customer> &customers) {
    int id;
    string pass;
    cout << "Enter Customer ID: ";
    cin >> id;
    cin.ignore();
    cout << "Enter Password: ";
    pass = getPassword();

    for (size_t i = 0; i < customers.size(); i++) {
        if (customers[i].id == id && customers[i].password == pass) {
            cout << "Login Successful!\n";
            return &customers[i];
        }
    }
    cout << "Invalid Credentials!\n";
    return nullptr;
}

// ================= MAIN =================
int main() {
    vector<Customer> customers;
    loadCustomers(customers);
    loadAccounts(customers);

    int choice;
    cout << "1. Register\n2. Login\nChoice: ";
    cin >> choice;
    cin.ignore();

    if (choice == 1) {
        int id;
        string name, pass;
        cout << "Enter ID (numbers only, no leading zero): ";
        cin >> id;
        cin.ignore();
        cout << "Enter Name: ";
        getline(cin, name);
        cout << "Enter Password: ";
        pass = getPassword();

        customers.push_back(Customer(id, name, pass));
        saveCustomers(customers);
        cout << "Registration Successful!\n";
    }

    Customer* current = login(customers);
    if (current == nullptr) return 0;

    int option;
    do {
        cout << "\n1. Create Account\n2. Deposit\n3. Withdraw\n4. Fund Transfer\n5. Show Accounts\n6. View Transactions\n7. Exit\nChoice: ";
        cin >> option;
        cin.ignore();

        if (option == 1) {
            int accNo;
            cout << "Enter Account Number: ";
            cin >> accNo;
            cin.ignore();
            current->accounts.push_back(Account(accNo, 0));
            saveAccounts(customers);
            cout << "Account Created Successfully!\n";
        }
        else if (option == 2) { // Deposit
            int accNo; double amt;
            cout << "Account Number: "; cin >> accNo;
            cout << "Amount: "; cin >> amt;
            bool found = false;
            for (size_t i = 0; i < current->accounts.size(); i++) {
                if (current->accounts[i].accountNumber == accNo) {
                    current->accounts[i].deposit(amt);
                    logTransaction(current->id, accNo, "Deposit", amt);
                    found = true;
                    break;
                }
            }
            if (!found) cout << "Error: Account does not exist!\n";
            else saveAccounts(customers);
        }
        else if (option == 3) { // Withdraw
            int accNo; double amt;
            cout << "Account Number: "; cin >> accNo;
            cout << "Amount: "; cin >> amt;
            bool found = false;
            for (size_t i = 0; i < current->accounts.size(); i++) {
                if (current->accounts[i].accountNumber == accNo) {
                    if (amt > current->accounts[i].balance)
                        cout << "Insufficient balance!\n";
                    else {
                        current->accounts[i].withdraw(amt);
                        logTransaction(current->id, accNo, "Withdraw", amt);
                    }
                    found = true;
                    break;
                }
            }
            if (!found) cout << "Error: Account does not exist!\n";
            else saveAccounts(customers);
        }
        else if (option == 4) { // Fund Transfer
            int fromAcc, toAcc; double amt;
            cout << "From Account Number: "; cin >> fromAcc;
            cout << "To Account Number: "; cin >> toAcc;
            cout << "Amount: "; cin >> amt;
            bool fromFound = false, toFound = false;
            Account* sender = nullptr;
            Account* receiver = nullptr;

            for (size_t i = 0; i < current->accounts.size(); i++) {
                if (current->accounts[i].accountNumber == fromAcc) {
                    sender = &current->accounts[i];
                    fromFound = true;
                    break;
                }
            }
            // Search receiver in all customers
            for (size_t i = 0; i < customers.size(); i++) {
                for (size_t j = 0; j < customers[i].accounts.size(); j++) {
                    if (customers[i].accounts[j].accountNumber == toAcc) {
                        receiver = &customers[i].accounts[j];
                        toFound = true;
                        break;
                    }
                }
            }
            if (!fromFound) cout << "Error: Sender account does not exist!\n";
            else if (!toFound) cout << "Error: Receiver account does not exist!\n";
            else if (amt > sender->balance) cout << "Error: Insufficient balance!\n";
            else {
                sender->withdraw(amt);
                receiver->deposit(amt);
                logTransaction(current->id, fromAcc, "TransferOut", amt);
                logTransaction(current->id, toAcc, "TransferIn", amt);
                saveAccounts(customers);
                cout << "Transfer Successful!\n";
            }
        }
        else if (option == 5) { // Show Accounts
            for (size_t i = 0; i < current->accounts.size(); i++) {
                cout << "Account Holder: " << current->name
                     << " | Account: " << current->accounts[i].accountNumber
                     << " | Balance: " << current->accounts[i].balance << endl;
            }
        }
        else if (option == 6) { // View Transactions
            viewTransactions(current->id);
        }
    } while (option != 7);

    return 0;
}
