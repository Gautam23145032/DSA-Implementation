/*
    We can understand the OOPs and four pillar of OOPs using following
    analogy

    lets assume there is a Car class;

*/

#include<bits/stdc++.h>
using namespace std;

class car {
private:
    int speed; // encapsulation

public:
    car(){
        speed = 0;
    }

    void accelerate(){
        speed += 10;
    }

    int getSpeed(){
        return speed;
    }

    virtual void startEngine(){  // polymorphism
        cout << "Car engine started";
    }

};

class BMW : public car{ // inheritance
public:

    void startEngine(){
        cout << "BMW engine started";
    }

};

class mercedes : public car{
public:
    void startEngine(){
        cout << "mercedes engine started";
    }
    
};

/*
Now lets understand each pillar using this example

1. Encapsulation -> protect the data

    look at car class
    class car{
    private:
        int speed;
    }

    here speed is private 
    so someone cannot do 
    car c;
    c.speed = 500;

    instead we provide controlled method
    c.getSpeed();
    c.getSpeed();

    so, the car class controls how its speed can be changed

    -> Data _ methods that operate on that data are kept together,
    while direct access to the data is restricted


2. Abstraction -> Hide unnecessary details

    imagine you are driving a car
    you simply do
    car.startEngine();

    you don't need to know whats happening internally
    Press start
        ↓
    Send signal to ECU
        ↓
    Activate starter motor
        ↓
    Inject fuel
        ↓
    Ignition
        ↓
    Engine starts

    all that complexity is hidden

    you only interact with
    startEngine();
    accelerate();

    so, Abstraction means exposing only what the user needs and 
    hiding unnecessary implementation details

3. Inheritance -> BMW is a car

    class BMW : public car
    means BMW inherits from car
    so BMW automatically gets thing from car such as
    accelerate();
    getSpeed();
    we don't need to rewrite them

    so, Inheritance allows a derived class to reuse and exted 
    functionality of an existing class
    The relationship is :- BMW IS-A car

4. Polymorphism -> Same function, different behaviour

    we have 
    class car{
    public:
        virtual void startEngine(){
            cout << "car engine started";
        }
    }

    BMW changes the implementation
    class BMW : public car{
    public:
        void startEngine(){
            cout << "BMW engine started";
        }
    }

    mercedes also changes it;
    class mercedes : public car{
    public:
        void startEngine() override{
            cout << "mercedes engine started";
        }
    }

    now,
    car* car1 = new BMW();
    car* car2 = new Mercedes();

    car1->startEngine();  // BMW engine started;
    car2->startEngine();  // mercedes engine started;

    notice something both pointer are car*
    and we are making the same call
    but it gives different behavior That's polymorphism

    Same interface, different implementation

*/