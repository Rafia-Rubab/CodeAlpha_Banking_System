 # Banking System in C++

A **console-based banking system** developed in **C++**, compatible with **Dev C++**, demonstrating object-oriented programming, file handling, and basic banking operations.

## Features

- **Customer Registration and Login**
  - Secure login with **masked password input** (`*` shows instead of password characters)
- **Account Management**
  - Create new accounts
  - View accounts with **account holder name**, account number, and balance
- **Bank Transactions**
  - Deposit money
  - Withdraw money
  - Fund transfer between accounts
- **Transaction History**
  - All transactions (deposit, withdraw, transfer) are stored in a file
  - Customers can view their recent transactions
- **File Handling**
  - Customers, accounts, and transactions are saved in text files for persistent storage

## Project Structure
BankingSystem/
├── main.cpp # C++ source code
├── customers.txt # Stores customer IDs, names, passwords
├── accounts.txt # Stores account numbers and balances
├── transactions.txt # Stores transaction history
└── README.md # Project description and instructions

## How to Run

1. Download or clone the repository:
https://github.com/Rafia-Rubab/CodeAlpha_Banking_System.git

Open main.cpp in Dev C++.
Compile and run the program.
Use the console menu to:
Register a new customer
Login with customer ID and password
Create accounts, deposit, withdraw, transfer funds
View account details and transaction history
How Password Works
Password input is masked with * for privacy.
Backspace works to remove characters while typing.

## Example Usage
1. Register
2. Login
Choice: 1
Enter ID: 101
Enter Name: Rafia Rubab
Enter Password: ********
Registration Successful!

Enter Customer ID: 101
Enter Password: ********
Login Successful!

1. Create Account
2. Deposit
3. Withdraw
4. Fund Transfer
5. Show Accounts
6. View Transactions
7. Exit
Choice: 1
Enter Account Number: 5001
Account Created Successfully!

## Technologies Used
C++ (OOP concepts),
File Handling (fstream) for persistent storage,
Console I/O,
Dev C++ compatible.

## Notes
Ensure the text files (customers.txt, accounts.txt, transactions.txt) are in the same folder as the executable for data persistence.
Only valid account numbers allow transactions. Errors are shown for invalid accounts or insufficient balance.

## Author
Rafia Rubab
Internship Project at CodeAlpha

