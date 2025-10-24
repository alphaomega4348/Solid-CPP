/*
2 types of rules:
1. Class Invariant rule
Rule which states that the properties (invariants) of the base class must be preserved in the derived class.
Parent Class: r1 Rule
Child Class: r1, r2 Rules

Ex-
Account Class: // Balance Constraint rule i.e, balance should never be negative

CheatAccount Class:  //Derived class which violates the Balance Constraint rule by allowing negative balance







2. History Constraint rule
State/Constraint of parent class which shouldn't change
Account Class: 
balance():double
withdraw(amount): void //Withdrawal should always be used

FixedDepositAccount Class:
//Derived class which violates the history constraint rule by not allowing withdrawal
withdraw(amount) throws Exception :void 
 
*/

#include<bits/stdc++.h>
using namespace std;

//Invariant: Balance should never be negative
class Account {
    protected:
    double balance;
    public:
    Account(double balance){
        if(balance < 0){
            throw invalid_argument("Initial balance cannot be negative");
        }
        this->balance = balance;
    }
    //History Constraint: Withdrawal should always be allowed
    virtual bool withdraw(double amount) {
        if(amount <= balance){
            balance -= amount;
            cout << "Withdrew $" << amount << ". New Balance: $" << balance << endl;
            return true;
        } else {
            cout << "Insufficient funds!" << endl;
            return false;
        }
    }
};

//Breaks Invariant: Should never be allowed
class CheatAccount : public Account {
    public:
    CheatAccount(double balance) : Account(balance) {}
    bool withdraw(double amount) override {
        // Violates the invariant by allowing overdraft
        balance -= amount;
        cout << "CheatAccount withdrew $" << amount << ". New Balance: $" << balance << endl;
        return true;
    }
};

//Breaks History Constraint: Withdrawal not allowed
class FixedDepositAccount : public Account {
    public:
    FixedDepositAccount(double balance) : Account(balance) {}
    bool withdraw(double amount) override {
        // Violates history constraint by disallowing withdrawal 
        //LSP violation
        throw runtime_error("Withdrawals not allowed from Fixed Deposit Account");
    }
};

int main() {
    try {
        Account* acc1 = new Account(1000);
        acc1->withdraw(200); // Valid

        Account* cheatAcc = new CheatAccount(500);
        cheatAcc->withdraw(600); // Violates invariant

        Account* fdAcc = new FixedDepositAccount(2000);
        fdAcc->withdraw(100); // Violates history constraint
    } catch (const exception& e) {
        cout << "Exception: " << e.what() << endl;
    }

    return 0;
}