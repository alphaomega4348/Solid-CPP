
/*
TODO:Violates OCP
Bad Way of Handling:
Change Client Side Code
i.e, 
if(account Type== FixedDepositAccount){
    account->deposit(amount);
} else {
    account->withdraw(amount);
    account->deposit(amount);
}
It will violate the OCP as it tightly couples the client with application code

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
            
            //Checking account type explicitly
            if(typeid(*acc) == typeid(FixedDepositAccount)) {
               cout<<"Skipping withdrawal for Fixed Deposit Account"<<endl;
        } 
        else {
            try{
                acc->withdraw(500);
            } catch (const runtime_error& e) {
                cout << e.what() << endl;
            }
            }
        }
    }
};

int main(){
    vector<Account*> accounts;
    accounts.push_back(new SavingAccount());
    accounts.push_back(new CurrentAccount());
    accounts.push_back(new FixedDepositAccount()); // This will cause issues

    BankClient client(accounts);
    client.performTransactions();

    return 0;
}