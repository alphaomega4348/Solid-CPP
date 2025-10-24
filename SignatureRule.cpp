/*


1.Method Argument  Rule:
//Argument of method of child class should either be same or broaden version of that of parent class.
Parent Class:
solve(string s): void

class Child extends Parent {
    // Overriding the solve method
    solve(string s): void 
}

2.Return Type Rule:
//Return type of method of child class should either be same or narrower version of that of parent class.
Parent Class:
solve(string s): Animal

Class Child extends Parent {
    // Overriding the solve method
    solve(string s): Dog
}

3.Exception Rule:
//Exception thrown by method of child class should either be same or narrower version of that of parent class.
Parent Class:
solve(string s) throws outOfRangeError: void
class Child extends Parent {
    // Overriding the solve method
    solve(string s) throws outOfRangeError: void 
    it can't throw broader exception like logicError 
}
*/



#include<bits/stdc++.h>
using namespace std;

// Parent Class
class Parent {
    public:
    virtual void solve(string s) {
        cout << "Parent solving with string: " << s << endl;
    }
};

// Child Class
class Child : public Parent {
    public:
    /*
    Violation of Signature Rule
    void solve(int s) override {
        cout << "Child solving with string: " << s << endl;
    }
    */
    void solve(string s) override {
        cout << "Child solving with string: " << s << endl;
    }

};

class Organism {
public:
    virtual Organism* speak() { // Return a pointer to Organism
        cout << "Organism speaks" << endl;
        return this;
    }
};

class Animal : public Organism {
public:
    Animal* speak() override { // Covariant return type: Animal*
        cout << "Animal speaks" << endl;
        return this;
    }
};

class Dog : public Animal {
public:
    //We can  return Dog* here
    Dog* speak() override { // Covariant return type: Dog*
        cout << "Dog barks" << endl;
        return this;
    }
    //We can also return Animal* here
    // Animal* speak() override { // Covariant return type: Animal*
    //     cout << "Dog barks" << endl;
    //     return this;

    //We can't return Organism* here
    // Organism* invalidSpeak() override { // This would violate the return type rule
    //     cout << "Dog barks" << endl;
    //     return this;
    // }
};

// Base Class
class Base {
public:
    virtual void process(string s) noexcept(false) { // Explicitly allows exceptions
        cout << "Base processing with string: " << s << endl;
        throw out_of_range("Base exception: out_of_range");
    }
};

// Derived Class
class Derived : public Base {
public:
    void process(string s) noexcept(false) override { // Same exception specification
        cout << "Derived processing with string: " << s << endl;
        // This is allowed
        throw out_of_range("Derived exception: out_of_range");
        // following line violates the intended rule 
        //  throw runtime_error("Derived exception: logic_error");
    }
};


int main() {

    //1.Method Argument Rule Demonstration
    Parent* p = new Parent();
    p->solve("Hello from Parent");

    Child* c = new Child();
    c->solve("Hello from Child");

    // Using Parent pointer to Child object
    Parent* pc = new Child();
    pc->solve("Hello from Parent pointer to Child");

    //2.Return Type Rule Demonstration
    Organism* organism = new Organism();
    organism->speak();

    Animal* animal = new Animal();
    animal->speak();

    Dog* dog = new Dog();
    dog->speak(); // This works because Dog::speak returns Animal
    // dog->invalidSpeak(); // Invalid as it violates return type rule

    //3.Exception Rule Demonstration
   Base* base = new Base();
    try {
        base->process("test");
    } catch (const logic_error& e) {
        cout << "Caught exception from Base: " << e.what() << endl;
    }

    Base* derived = new Derived();
    try {
        derived->process("test");
    } catch (const logic_error& e) {
        cout << "Caught exception from Derived: " << e.what() << endl;
    }




    return 0;
}