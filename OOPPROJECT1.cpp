#include<iostream>
#include<vector>
#include<string>
#include<stdexcept>
using namespace std;
class person {                   //person class
public:                          //virtual void display() prints person
    virtual void display() {
        cout<<"Person"<<endl;
    }
    virtual ~person(){}           // virtual enables runtime behavior
};
class student : public person {       // inherits student class from person
private:
    int id;
    string name;                       //4 data members
    int attended;
    int total;
public:
    student(int i,string n,int a,int t) {
        if (i<0)
            throw runtime_error("invalid id");
        if (a<0||t<0||a>t)
            throw runtime_error("invalid attendance");
        id=i;
        name=n;
        attended=a;
        total=t;
    }
    int getAttended() {return attended;}
    int getTotal() {return total;}
    string getName(){return name;}

    void display() override {
        cout<<"student :"<<name<<endl;
    }
};
class instructor : public person {                     //inherits instructor class from person
public:
    void display() override {                      //override is important for safety
        cout<<"instructor"<<endl;
    }
};
class reporthelper {
public:
    static double calcpercent(student s) {
        if (s.getTotal()==0)
            throw runtime_error ("no classes");           //runtime is It represents errors that happen during program execution
        return (s.getAttended() * 100.0)/s.getTotal();
    }
    static void printreport(student s) {
        try   {
            double p=calcpercent(s);
            cout<<"name :"<<s.getName()<<endl;
            cout<<"attendance :"<<p<<"%"<<endl;
        }catch (...) {
            cout<<"error in report"<<endl;
        }
    }
};
