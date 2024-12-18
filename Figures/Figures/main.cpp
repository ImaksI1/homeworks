#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class Shape {
public:
    virtual void Show() const = 0;     
    virtual void Save(ofstream& out) const = 0; 
    virtual void Load(ifstream& in) = 0;        
    virtual ~Shape() {}
};


class Square : public Shape {
private:
    double x, y, side;

public:
    Square(double x = 0, double y = 0, double side = 0) : x(x), y(y), side(side) {}

    void Show() const override {
        cout << "Square: x: " << x << ", y: " << y << ", side: " << side << endl;
    }

    void Save(ofstream& out) const override {
        out << "Square " << x << " " << y << " " << side << endl;
    }

    void Load(ifstream& in) override {
        in >> x >> y >> side;
    }
};


class Rectangle : public Shape {
private:
    double x, y, width, height;

public:
    Rectangle(double x = 0, double y = 0, double width = 0, double height = 0)
        : x(x), y(y), width(width), height(height) {
    }

    void Show() const override {
        cout << "Rectangle: x: " << x << ", y: " << y << ", width: " << width << ", height: " << height << endl;
    }

    void Save(ofstream& out) const override {
        out << "Rectangle " << x << " " << y << " " << width << " " << height << endl;
    }

    void Load(ifstream& in) override {
        in >> x >> y >> width >> height;
    }
};

class Circle : public Shape {
private:
    double cx, cy, radius;

public:
    Circle(double cx = 0, double cy = 0, double radius = 0) : cx(cx), cy(cy), radius(radius) {}

    void Show() const override {
        cout << "Circle: cx: " << cx << ", cy:" << cy << ", radius: " << radius << endl;
    }

    void Save(ofstream& out) const override {
        out << "Circle " << cx << " " << cy << " " << radius << endl;
    }

    void Load(ifstream& in) override {
        in >> cx >> cy >> radius;
    }
};

class Ellipse : public Shape {
private:
    double x, y, width, height;

public:
    Ellipse(double x = 0, double y = 0, double width = 0, double height = 0)
        : x(x), y(y), width(width), height(height) {
    }

    void Show() const override {
        cout << "Ellipse: x: " << x << ", y: " << y << ", width: " << width << ", height: " << height << endl;
    }

    void Save(ofstream& out) const override {
        out << "Ellipse " << x << " " << y << " " << width << " " << height << endl;
    }

    void Load(ifstream& in) override {
        in >> x >> y >> width >> height;
    }
};

int main() {
    vector<Shape*> shapes;

    shapes.push_back(new Square(0, 0, 5));
    shapes.push_back(new Rectangle(1, 1, 4, 6));
    shapes.push_back(new Circle(2, 2, 3));
    shapes.push_back(new Ellipse(3, 3, 5, 7));

    ofstream outFile("shapes.txt");
    for (const auto& shape : shapes) {
        shape->Save(outFile);
    }
    outFile.close();

    for (auto& shape : shapes) {
        delete shape;
    }

    vector<Shape*> loadedShapes;
    ifstream inFile("shapes.txt");
    string shapeType;
    while (inFile >> shapeType) {
        Shape* shape = nullptr;
        if (shapeType == "Square") {
            shape = new Square();
        }
        else if (shapeType == "Rectangle") {
            shape = new Rectangle();
        }
        else if (shapeType == "Circle") {
            shape = new Circle();
        }
        else if (shapeType == "Ellipse") {
            shape = new Ellipse();
        }
        if (shape) {
            shape->Load(inFile);
            loadedShapes.push_back(shape);
        }
    }
    inFile.close();

    for (const auto& shape : loadedShapes) {
        shape->Show();
        delete shape;
    }

    return 0;
}
