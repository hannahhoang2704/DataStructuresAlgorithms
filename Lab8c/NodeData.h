//
// Created by Hanh Hoang on 22.1.2025.
//
#include <iostream>
using namespace std;

class NodeData {
    friend ostream& operator<< (ostream& stream, const NodeData &p);
public:
    virtual ~NodeData(){}
    virtual ostream& print(ostream &stream) const = 0;
};

class String:public NodeData{
public:
    String(string str): s(str){};
    ostream& print(ostream &stream) const override;
private:
    string s;
};

class Char:public NodeData{
public:
    Char(char ch): ch(ch){};
    ostream& print(ostream &stream) const override{
        stream << ch;
        return stream;
    };
private:
    char ch;
};


class Int:public NodeData{
public:
    Int(int nr): number(nr){};
    ostream& print(ostream &stream) const override{
        stream << number;
        return stream;
    };
private:
    int number;
};

class Complex:public NodeData{
public:
    Complex(float real, float imaginary): real(real), imaginary(imaginary){};
    ostream& print(ostream &stream) const override;
private:
    float real;
    float imaginary;
};

ostream& operator<<(ostream& stream, const NodeData &p){
    p.print(stream);
    return stream;
}

ostream& String::print(ostream &stream) const{
    stream << s;
    return stream;
}

ostream& Complex::print(ostream &stream) const{
    stream << "<" << real << ", " << imaginary << ">";
    return stream;
}

