
/*#TODO:Good Way of Handling:
    Guidelines to adhere to LSP Rule:
    1.> Signature RUle
    2.> Property Rule
    3.> Method Rule

*/


/*



<<abstract>>
NonWithdrawableAccount: 
deposit (amount: double) : void


<<abstract>>
WithdrawableAccount:    (is a relationship with NonWithdrawableAccount)
deposit (amount: double) : void
withdraw(amount: double) : void

SavingAccount:      (is a relationship with WithdrawableAccount)
deposit (amount: double) : void
withdraw(amount: double) : void

CurrentAccount:     (is a relationship with WithdrawableAccount)
deposit (amount: double) : void
withdraw(amount: double) : void

FixedDepositAccount:      (is a relationship with NonWithdrawableAccount)
deposit (amount: double) : void

*/

#include<bits/stdc++.h>
using namespace std;
//Base Class for Non-Withdrawable Accounts
class NonWithdrawableAccount{
    public:
    virtual void deposit(double amount) = 0;
};
//Derived Class for Withdrawable Accounts
class WithdrawableAccount : public NonWithdrawableAccount{
    public:
    virtual void withdraw(double amount) = 0;
};
//Derived Class: SavingAccount
class SavingAccount : public WithdrawableAccount{
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
class CurrentAccount : public WithdrawableAccount{
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
class FixedDepositAccount: public NonWithdrawableAccount{
    private:
    double balance;
    public:
    FixedDepositAccount(): balance(0.0) {}
    void deposit(double amount) override {
        balance += amount;
        cout << "Deposited $" << amount << " to Fixed Deposit Account. New Balance: $" << balance << endl;
    }
};

class BankClient{
   private:
    vector<NonWithdrawableAccount*> accounts;
    vector<WithdrawableAccount*> withdrawableAccounts;
    public:
    BankClient(vector<NonWithdrawableAccount*> accounts, vector<WithdrawableAccount*> withdrawableAccounts){
        this->accounts = accounts;
        this->withdrawableAccounts = withdrawableAccounts;
    }

    void performTransactions(){
        for(WithdrawableAccount *account: withdrawableAccounts){
            account->deposit(1000);
            account->withdraw(500);
        }
        for(NonWithdrawableAccount *account: accounts){
            account->deposit(1000);
            // No withdrawal attempted here
        }
    }

};

int main(){
    // Creating accounts
    SavingAccount* savingAcc = new SavingAccount();
    CurrentAccount* currentAcc = new CurrentAccount();
    FixedDepositAccount* fixedDepositAcc = new FixedDepositAccount();

    vector<WithdrawableAccount*> withdrawableAccounts = {savingAcc, currentAcc};
    vector<NonWithdrawableAccount*> nonWithdrawableAccounts = {fixedDepositAcc};

    BankClient client(nonWithdrawableAccounts, withdrawableAccounts);
    client.performTransactions();

    // Clean up
    delete savingAcc;
    delete currentAcc;
    delete fixedDepositAcc;

    return 0;
}