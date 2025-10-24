//TODO: Refactored to adhere to the Single Responsibility Principle (SRP)

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
    DatabaseSaver(ShoppingCart* cart){
        this->cart = cart;
    }
    void saveToDatabase(){
        // Simulate saving to database
        cout << "Saving shopping cart to database..." << endl;
    }
};

int main(){

    ShoppingCart* cart = new ShoppingCart();
    cart->addProduct(new Product("Laptop", 999.99));
    cart->addProduct(new Product("Mouse", 49.99));
    InvoicePrinter* printer = new InvoicePrinter(cart);
    printer->printInvoice();
    DatabaseSaver* dbSaver = new DatabaseSaver(cart);
    dbSaver->saveToDatabase();
    return 0;
}