/*Subclasses should be substitutable for their base classes without altering the correctness of the program.
i.e, subclass should extend the base class not narrow it.
*/


/*

<<abstract>>
Account:
deposit (amount: double) : void
withdraw(amount: double) : void

SavingAccount:      (is a relationship with Account)
deposit (amount: double) : void
withdraw(amount: double) : void

CurrentAccount:     (is a relationship with Account)
deposit (amount: double) : void
withdraw(amount: double) : void

Suppose a new type of account is introduced, e.g., FixedDepositAccount, which does not support withdrawals.
FixedDepositAccount should not inherit from Account if it cannot fulfill the contract of the withdraw method.
in most of the cases we throw exceptions in such case which violates the LSP principle.

FixedDepositAccount:      (is a relationship with Account)
deposit (amount: double) : void
withdraw(amount: double) : throw Exception


*/


#include<bits/stdc++.h>
using namespace std;

//Base Class
class Account{
    public:
    virtual void deposit(double amount) = 0;
    virtual void withdraw(double amount) = 0;
};

//Derived Class: SavingAccount
class SavingAccount : public Account{
    private:
    double balance;
    public:
    SavingAccount(): balance(0.0) {}
    void deposit(double amount) override {
        balance += amount;
        cout << "Deposited $" << amount << " to Saving Account. New Balance: $" << balance << endl;
    }
    void withdraw(double amount) override {
        if(amount <= balance){
            balance -= amount;
            cout << "Withdrew $" << amount << " from Saving Account. New Balance: $" << balance << endl;
        } else {
            cout << "Insufficient funds in Saving Account!" << endl;
        }
    }
};

//Derived Class: CurrentAccount
class CurrentAccount : public Account{
    private:
    double balance;
    public:
    CurrentAccount(): balance(0.0) {}
    void deposit(double amount) override {
        balance += amount;
        cout << "Deposited $" << amount << " to Current Account. New Balance: $" << balance << endl;
    }
    void withdraw(double amount) override {
        if(amount <= balance){
            balance -= amount;
            cout << "Withdrew $" << amount << " from Current Account. New Balance: $" << balance << endl;
        } else {
            cout << "Insufficient funds in Current Account!" << endl;
        }
    }
};

//New Class: FixedDepositAccount (Does not support withdrawals)
class FixedDepositAccount: public Account{
    private:
    double balance;
    public:
    FixedDepositAccount(): balance(0.0) {}
    void deposit(double amount) {
        balance += amount;
        cout << "Deposited $" << amount << " to Fixed Deposit Account. New Balance: $" << balance << endl;
    }
    void withdraw(double amount) {
        // Withdrawal not supported
        throw runtime_error("Withdrawals are not allowed from Fixed Deposit Account!");
    }
};

class BankClient {
    private:
    vector<Account*> accounts;
    public:
    BankClient(vector<Account*>& accounts) {
        this->accounts = accounts;
    }
    void performTransactions() {
        for(Account *acc : accounts) {
            acc->deposit(1000);
            try{
                acc->withdraw(500);
            } catch (const runtime_error& e) {
                cout << e.what() << endl;
            }
        } 
    }
};

int main(){
    SavingAccount* savingAcc = new SavingAccount();
    CurrentAccount* currentAcc = new CurrentAccount();
    FixedDepositAccount* fixedDepositAcc = new FixedDepositAccount();

    vector<Account*> accounts;
    accounts.push_back(savingAcc);
    accounts.push_back(currentAcc);
    // fixedDepositAcc cannot be added to accounts as it does not inherit from Account

    BankClient* client = new BankClient(accounts);
    client->performTransactions();

    // Directly using FixedDepositAccount
    fixedDepositAcc->deposit(2000);
    try{
        fixedDepositAcc->withdraw(500); // This will throw an exception
    } catch (const runtime_error& e) {
        cout << e.what() << endl;
    }

    return 0;
}