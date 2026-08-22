#include<iostream>
#include<cstdio>
#include<string>
#include<vector>
#include<fstream>
#include<boost/lexical_cast.hpp>

using namespace std;
using namespace boost;

#include <iostream>

// Base class for shapes
class Rectangle {
protected:
    double width;
    double height;

public:
    Rectangle(double w, double h) : width(w), height(h) {}

    virtual double area() const {
        return width * height;
    }

    double getWidth() const {
        return width;
    }

    double getHeight() const {
        return height;
    }

    virtual void setWidth(double w) {
        width = w;
    }

    void setHeight(double h) {
        height = h;
    }
};

// Derived class for squares
class Square : public Rectangle {
public:
    Square(double size) : Rectangle(size, size) {}

    void setWidth(double w) override {
        width = height = w; // Ensure both width and height remain the same
    }
