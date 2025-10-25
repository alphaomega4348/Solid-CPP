/*
It also has 2 types-
1. Pre-condition rule
If we apply any pre condition on parent class than child class should either follow it or weaken  it
User:
//pre-condition:  length of password>=8
void createPassword(password:string) :void

AdminUser:
Must follow pre-condition:  length of password>=6
void createPassword(password:string) :void

2. Post-condition rule
If we apply any post condition on parent class than child class should either follow it or strengthen it
Car:
void break(): //post-condition: car must slow down

ElectricCar:
void break(): //post-condition: car must slow down and battery should be preserved
*/


#include <iostream>
#include <string>
using namespace std;

class User {
public:
    void createPassword(string password) {
        if (password.length() >= 8) {
            cout << "Password created successfully" << endl;
        } else {
            cout << "Password length should be at least 8 characters" << endl;
        }
    }
};

class AdminUser : public User { // Proper inheritance syntax
public:
    void createPassword(string password) {
        if (password.length() >= 6) { // AdminUser has a different password length rule
            cout << "Password created successfully" << endl;
        } else {
            cout << "Password length should be at least 6 characters" << endl;
        }
    }
};

class Car {
protected:
    int speed;
public:
    Car() : speed(100) {} // Initial speed is 100

    virtual void brake() {
        // Post-condition: Car must slow down
        if (speed > 0) {
            speed -= 10; // Reduce speed by 10
            cout << "Car is slowing down. Current speed: " << speed << " km/h" << endl;
        } else {
            cout << "Car is already stopped." << endl;
        }
    }
};

class ElectricCar : public Car {
private:
    int batteryLevel;
public:
    ElectricCar() : batteryLevel(80) {} // Initial battery level is 80%

    void brake() override {
        // Post-condition: Car must slow down and battery should be preserved
        if (speed > 0) {
            speed -= 10; // Reduce speed by 10
            batteryLevel += 1; // Regenerate battery by 1% during braking
            cout << "ElectricCar is slowing down. Current speed: " << speed << " km/h" << endl;
            cout << "Battery level preserved. Current battery level: " << batteryLevel << "%" << endl;
        } else {
            cout << "ElectricCar is already stopped." << endl;
        }
    }
};

int main() {
    User u;
    u.createPassword("mypwd"); // Should fail (less than 8 characters)

    AdminUser au;
    au.createPassword("adminpwd"); // Should succeed (at least 6 characters)

    Car car;
    ElectricCar eCar;

    cout << "Applying brake on Car:" << endl;
    car.brake(); // Car slows down
    car.brake(); // Car slows down again

    cout << "\nApplying brake on ElectricCar:" << endl;
    eCar.brake(); // ElectricCar slows down and preserves battery
    eCar.brake(); // ElectricCar slows down and preserves battery again


    return 0;
}