/*Many client interfaces are better than one general purpose interface.
 Client should not be forced to implement methods they do not use.

<<abstract>>
Shape: 
    + draw() : void
    + resize() : void
    + calculateArea() : double
    + calculateVolume() : double

Square:         (extends Shape)
    + draw() : void
    + resize() : void
    + calculateArea() : double
    + calculateVolume() : inValidOperationException

Rectangle:       (extends Shape)
    + draw() : void
    + resize() : void
    + calculateArea() : double
    + calculateVolume() : inValidOperationException

Cube:          (extends Shape)
    + draw() : void
    + resize() : void
    + calculateArea() : double
    + calculateVolume() : double

Sphere:        (extends Shape)
    + draw() : void
    + resize() : void
    + calculateArea() : double
    + calculateVolume() : double
*/

#include <iostream>
#include <stdexcept>
using namespace std;

// Abstract Shape class
class Shape {
public:
    virtual void draw() = 0;
    virtual void resize() = 0;
    virtual double calculateArea() = 0;
    virtual double calculateVolume() = 0; // Irrelevant for 2D shapes
    virtual ~Shape() {}
};

// Square class (2D shape)
class Square : public Shape {
private:
    double side;
public:
    Square(double side) : side(side) {}
    void draw() override {
        cout << "Drawing a Square" << endl;
    }
    void resize() override {
        cout << "Resizing the Square" << endl;
    }
    double calculateArea() override {
        return side * side;
    }
    double calculateVolume() override {
        throw runtime_error("Invalid operation: Square does not have a volume");
    }
};

// Rectangle class (2D shape)
class Rectangle : public Shape {
private:
    double length, width;
public:
    Rectangle(double length, double width) : length(length), width(width) {}
    void draw() override {
        cout << "Drawing a Rectangle" << endl;
    }
    void resize() override {
        cout << "Resizing the Rectangle" << endl;
    }
    double calculateArea() override {
        return length * width;
    }
    double calculateVolume() override {
        throw runtime_error("Invalid operation: Rectangle does not have a volume");
    }
};

// Cube class (3D shape)
class Cube : public Shape {
private:
    double side;
public:
    Cube(double side) : side(side) {}
    void draw() override {
        cout << "Drawing a Cube" << endl;
    }
    void resize() override {
        cout << "Resizing the Cube" << endl;
    }
    double calculateArea() override {
        return 6 * side * side;
    }
    double calculateVolume() override {
        return side * side * side;
    }
};

// Sphere class (3D shape)
class Sphere : public Shape {
private:
    double radius;
public:
    Sphere(double radius) : radius(radius) {}
    void draw() override {
        cout << "Drawing a Sphere" << endl;
    }
    void resize() override {
        cout << "Resizing the Sphere" << endl;
    }
    double calculateArea() override {
        return 4 * 3.14159 * radius * radius;
    }
    double calculateVolume() override {
        return (4.0 / 3.0) * 3.14159 * radius * radius * radius;
    }
};

int main() {
    // Create shapes
    Shape* square = new Square(5);
    Shape* rectangle = new Rectangle(4, 6);
    Shape* cube = new Cube(3);
    Shape* sphere = new Sphere(4);

    // Demonstrate functionality
    square->draw();
    cout << "Square Area: " << square->calculateArea() << endl;
    try {
        cout << "Square Volume: " << square->calculateVolume() << endl;
    } catch (const runtime_error& e) {
        cout << e.what() << endl;
    }

    rectangle->draw();
    cout << "Rectangle Area: " << rectangle->calculateArea() << endl;
    try {
        cout << "Rectangle Volume: " << rectangle->calculateVolume() << endl;
    } catch (const runtime_error& e) {
        cout << e.what() << endl;
    }

    cube->draw();
    cout << "Cube Area: " << cube->calculateArea() << endl;
    cout << "Cube Volume: " << cube->calculateVolume() << endl;

    sphere->draw();
    cout << "Sphere Area: " << sphere->calculateArea() << endl;
    cout << "Sphere Volume: " << sphere->calculateVolume() << endl;

    // Clean up
    delete square;
    delete rectangle;
    delete cube;
    delete sphere;

    return 0;
}