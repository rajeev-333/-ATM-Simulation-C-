# ATM Simulator System (C++)

A secure, console-based ATM simulation built using Object-Oriented Programming in C++.
Designed to replicate real-world ATM functionality with authentication, transaction management, and persistent storage.

  ##Project Overview

This project simulates the working of a real ATM machine.
It supports secure user authentication, core banking operations, and persistent account storage using file handling.

The system is designed with scalability and security logic in mind, demonstrating clean code structure and practical OOP implementation.

## Key Highlights

    Secure Login with masked PIN input

    Automatic Account Lock after 3 failed attempts

    Deposit & Withdrawal with validation rules

    Balance Inquiry & Account Details

    Persistent Data Storage using file handling

    Object-Oriented Design with encapsulated logic

    Modular and maintainable code structure

##🛠 Tech Stack

Language: C++

Concepts Used:

    Object-Oriented Programming (Encapsulation, Abstraction)

    File Handling (ifstream, ofstream)

    STL Containers (vector, string)

    Input validation & security logic

## System Architecture
🔹 Core Components

1. ATM Class

* Stores account details (Account No, Name, PIN, Balance, Mobile No)

* Handles:

    Deposit

    Withdraw

    Mobile update

    Account lock/unlock logic

* Maintains transaction data

2. Authentication Module

    * Validates Account Number & PIN

    * Tracks incorrect attempts

    * Locks account after threshold limit

3. Persistence Layer

    * Stores account records in structured text format

    * Loads data at startup

    * Writes updates back to file


##💾 Data Storage Format

Accounts are stored in CSV format:

    AccountNo,Name,PIN,Balance,MobileNo

Example:

987654321,John,1234,50000,9876543210


##🔐 Security Features

* Masked PIN entry using _getch()

* 3-attempt login restriction

* Temporary account lock mechanism

* Withdrawal limit enforcement

* Balance validation checks

##▶️ How to Run
  Compile
               g++ main.cpp -o atm
  Execute
               ./atm

(On Windows: atm.exe)

## Real-World Simulation Aspects

This project models:

  -Authentication flow

  -Session-based user interaction

  -Persistent banking data

  -Business rule enforcement

  -Basic brute-force attack prevention


 ## What This Project Demonstrates

  -Strong understanding of OOP principles

  -Clean modular program structure

  -Practical file handling implementation

  -Security-focused design thinking

  -Ability to simulate real-world systems
