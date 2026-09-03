/*
    in simple term
    polymorphism -> feature that allows an entity (like function or an operator)
    to behave differently depending on the context or data type

    There are two type of polymorphism
    1. Compile-time polymorphism (static)
    2. Run-time polymorphism  (dynamic)
*/

/*
    1. compile time polymorphism

    The compiler determines exactly which function or operator 
    to execute before the program runs

    again in this we have 
    1. method / function overloading 
    -> you can create multiple function with same name but
    different parameter list (types, number or order);

*/
#include<bits/stdc++.h>
using namespace std;

class printer{
public:

    void print(int i){
        cout << "printing integer : " << i << endl;
    }
    void print(string s){
        cout << "printing string : " << s << endl;
    }

    int add(int a, int b){
        return a + b;
    }

    int add(int a, int b, int c){
        return a + b + c;
    }
};

/*
    operator overloading -> you can redefine how native operator like (+, -, *, <<, etc)
    work when used with user defined class;

    It does not allow you to create a new operator (like **), it only change the
    behavior of existing one 

*/

class vector2d{
public:

    double x, y;
    vector2d(double x = 0.0, double y = 0.0) : x(x), y(y) {};

    // Binary '+' operator as a member function
    // implicitly receives 'this' (lhs) and explicitly receive 'rhs'
    vector2d operator + (const vector2d& rhs) const {
        return vector2d(this->x + rhs.x, this->y + rhs.y);
    }

    /*
        so when we do
        vector2d v1(2.0, 3.0)
        vector2d v2(4.0, 5.0)

        vector2d v3 = v1 + v2;
        so here v1 invokes the operator function and v2 is passed as rhs

        v3.x = 6, v3.y = 8;
    */ 


};


/*
    2. Run-time polymorphism

    The exact function execution path is determined dynamically
    while the program is running. 
    It handles scenario when base class pointer points to derived 
    class object;

    virtual function and method overriding

    to achieve runtime polymorphism, you must declare a member function
    as virtual in yous parent class;
    a child class then can override that function to implement the
    specific behavior

*/

class Animal{
public:
    virtual void makeSound(){
        cout << "some sound";
    }
};

class dog : public Animal{
    void makeSound() override{
        cout << "Bark!";
    }
};
