#include <iostream>
#include "NodeData.h"

using namespace std;

//template <class T>
class Matrix{
public:
    Matrix();
    ~Matrix();
    class RowProxy;
    RowProxy operator[](int row);
    void print(ostream& out) const;
    friend ostream& operator<<(ostream& out, const Matrix& matrix);

    // definition of the list node class
    class Node {
    public:
        int row;
        int column;
        NodeData*    _value;	// data
        Node *_pNextRow;	// pointer to the next node
        Node * _pNextColumn;
        Node() : _pNextRow(NULL), _pNextColumn(NULL) {}
        Node(int row, int column, NodeData* val) : row(row), column(column), _value(val), _pNextRow(NULL), _pNextColumn(NULL) {}
    };

private:
    Node *head;
};

Matrix::Matrix(){
    head = nullptr;
}

Matrix::~Matrix(){
    Node* row = head;
    while (row!= NULL){
        Node *col = row;
        while(col != NULL){
            Node* temp = col;
            col = col->_pNextColumn;
            delete temp->_value;
            delete temp;
        }
        row = row->_pNextRow;
    }
}

void Matrix::print(ostream& out) const {
    Node *row = head;
    while(row != nullptr){
        Node* col = row->_pNextColumn;
        out << col->row << ":\t";
        while(col != nullptr){
            out<< col->column << ":\t\t" << *(col->_value) << "\t";
            col = col->_pNextColumn;
        }
        out << endl;
        row = row->_pNextRow;
    }
}

ostream& operator<<(std::ostream &out, const Matrix& matrix) {
    matrix.print(out);
    return out;
}

class Matrix::RowProxy{
private:
    Node* row_head;
public:
    RowProxy(Node*& row_head): row_head(row_head){}
    NodeData*& operator[](int column);
};


Matrix::RowProxy Matrix::operator[](int row){
    Node *current = head;
    Node * prev = NULL;
    while(current != NULL && current->row < row){
        prev = current;
        current = current->_pNextRow;
    }
    if(current == NULL || current->row != row) {
        Node *new_row = new Node(row, -1, NULL);
        if (prev == NULL) {
            head = new_row;
        } else {
            prev->_pNextRow = new_row;
        }
        new_row->_pNextRow = current;
        current = new_row;
    }

    return RowProxy(current);
}


NodeData*& Matrix::RowProxy::operator[](int column) {
    Node *current = row_head->_pNextColumn;
    Node *prev = NULL;
    while(current != NULL && current-> column < column){
        prev = current;
        current = current ->_pNextColumn;
    }
    if(current == NULL || current->column != column){
        Node * new_col = new Node(row_head->row, column, NULL);
        if(prev == NULL){
            row_head->_pNextColumn = new_col;
        }else{
            new_col->_pNextColumn = current;
            prev->_pNextColumn = new_col;
        }
        current = new_col;
    }
    return current->_value;
}