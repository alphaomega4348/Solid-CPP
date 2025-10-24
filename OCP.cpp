/*
Class Diagram:
Product- Price,Name

Shopping Cart (1...*) has a relationship  with Product
InvoicePrinter (1..1) has a relationship with Shopping Cart
DatabaseSaver (1..1) has a relationship with Shopping Cart

Shopping Cart:
calculateTotalPrice() : double

InvoicePrinter:
printInvoice() : void

DatabaseSaver:
saveToDatabase() : void


Created interface/abstract class for DatabaseSaver to adhere to OCP principle

<<abstract>> DBSaver

SavetoSQL() : void
SavetoMongoDB() : void
SavetoFile() : void

*/

#include<bits/stdc++.h>
using namespace std;

class Product{
    public:
    double price;
    string name;

   Product(string name, double price){
        this->name = name;
        this->price = price;
    }
};

//Adhering to SRP: Separate responsibilities into different classes
class ShoppingCart{
    public:
    vector<Product*> products;

    void addProduct(Product* product){
        products.push_back(product);
    }
    const vector<Product*>& getProducts() const {
        return products;
    }
    // Responsibility: Calculate total price
    double calculateTotalPrice(){
        double total = 0.0;
        for(auto product: products){
            total += product->price;
        }
        return total;
    }
};
class InvoicePrinter{
    private:
    ShoppingCart* cart;
    public:
    InvoicePrinter(ShoppingCart* cart){
        this->cart = cart;
    }
    void printInvoice(){
        cout << "Invoice:" << endl;
        for(auto product: cart->getProducts()){
            cout << product->name << " - $" << product->price <<  endl;
        }
        cout << "Total: $" << cart->calculateTotalPrice() << endl;
    }
};
 class DatabaseSaver{
    private:
    ShoppingCart* cart;
    public:
    virtual void saveToDatabase( ShoppingCart* cart) = 0; // Pure virtual function
    
};

class SQLDatabaseSaver : public DatabaseSaver {
    public:
    void saveToDatabase( ShoppingCart* cart) override {
        // Simulate saving to SQL database
        cout << "Saving shopping cart to SQL database..." << endl;
    }
};

class MongoDBSaver : public DatabaseSaver {
    public:
    void saveToDatabase( ShoppingCart* cart) override {
        // Simulate saving to MongoDB
        cout << "Saving shopping cart to MongoDB..." << endl;
    }
};

class FileSaver : public DatabaseSaver {
    public:
    void saveToDatabase( ShoppingCart* cart) override {
        // Simulate saving to file
        cout << "Saving shopping cart to file..." << endl;
    }
};
 

int main(){

    ShoppingCart* cart = new ShoppingCart();
    cart->addProduct(new Product("Laptop", 999.99));
    cart->addProduct(new Product("Mouse", 49.99));

    DatabaseSaver* sqlSaver = new SQLDatabaseSaver();
    sqlSaver->saveToDatabase(cart);
    DatabaseSaver* mongoSaver = new MongoDBSaver();
    mongoSaver->saveToDatabase(cart);
    DatabaseSaver* fileSaver = new FileSaver();
    fileSaver->saveToDatabase(cart);
    return 0;
}