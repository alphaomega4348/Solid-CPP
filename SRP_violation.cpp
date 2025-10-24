//IMPORTANT: SRP doez not mean that a class should have only one method. It means that a class should have only one reason to change, meaning it should only have one responsibility or job. A class can have multiple methods as long as they all contribute to that single responsibility.

//TODO: Violates the Dependency Inversion Principle (SRP)

/*
Class Diagram:
Product- Price,Name

Shopping Cart (1...*) has a relationship  with Product

Shopping Cart:
calculateTotalPrice() : double
printInvoice() : void
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

//Violating SRP: Handling multiple responsibilities in one class
class ShoppingCart{
    public:
    vector<Product*> products;

    void addProduct(Product* product){
        products.push_back(product);
    }
    const vector<Product*>& getProducts() const {
        return products;
    }
    //1. Responsibility: Calculate total price
    double calculateTotalPrice(){
        double total = 0.0;
        for(auto product: products){
            total += product->price;
        }
        return total;
    }
    //2. Responsibility: Print invoice
    void printInvoice(){
        cout << "Invoice:" << endl;
        for(auto product: products){
            cout << product->name << " - $" << product->price << endl;
        }
        cout << "Total: $" << calculateTotalPrice() << endl;
    }
    //3. Responsibility: Save to database
    void saveToDatabase(){
        // Simulate saving to database
        cout << "Saving shopping cart to database..." << endl;
    }
};

int main(){

    ShoppingCart* cart = new ShoppingCart();
    cart->addProduct(new Product("Laptop", 999.99));
    cart->addProduct(new Product("Mouse", 49.99));
    cart->printInvoice();
    cart->saveToDatabase();
    return 0;

}