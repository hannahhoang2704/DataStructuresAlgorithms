//
// Created by Hanh Hoang on 22.1.2025.
//
#include <iostream>
using namespace std;

class NodeData {
    friend ostream& operator<< (ostream& stream, const NodeData *p);
public:
    virtual ostream& print(ostream &stream) const = 0;
    virtual bool operator<(NodeData *) = 0;
};

class String:public NodeData{
public:
    String(string str): s(str){};
    ostream& print(ostream &stream) const override;
    bool operator<(NodeData *another_str) override;
private:
    string s;
};

class Complex:public NodeData{
public:
    Complex(float real, float imaginary): real(real), imaginary(imaginary){};
    ostream& print(ostream &stream) const override;
    bool operator<(NodeData *another_complex) override;
private:
    float real;
    float imaginary;
};

//implementation of class String and class Complex
ostream& operator<<(ostream& stream, const NodeData *p){
    p->print(stream);
    return stream;
}

ostream& String::print(ostream &stream) const{
    stream << s;
    return stream;
}

bool String::operator<(NodeData *another_str) {
    String *otherString = dynamic_cast<String *>(another_str);
    if(s < otherString->s){
        return true;
    }
    return false;
}

ostream& Complex::print(ostream &stream) const{
    stream << real << "+" << imaginary << "i";
    return stream;
}

bool Complex::operator<(NodeData *another_complex) {
    Complex *another = dynamic_cast<Complex *>(another_complex);
    if(real < another->real) return true;
    return false;
}