#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <cmath>
#include <numeric>
#include <algorithm>
#include <iomanip>

#define RAND_NUMBER 100

using namespace std;


template <class T>
class BinSTree{
public:
    explicit BinSTree(){
        root = nullptr;
    };
    ~BinSTree();
    void insert_to_tree(T val);
    bool isInTree(T val, int& count);
private:
    class Node{
    public:
        T _item;
        Node *left, *right;
        Node(T val): _item(val), left(NULL), right(NULL){};
    };
    Node *root;
    void delete_node(Node *node);
};


template <class T>
void BinSTree<T>::insert_to_tree(T val) {
        Node* new_node = new Node(val);
        if(root == nullptr){
            root = new_node;
        }else{
            Node *current_node = root;
            Node *prev = nullptr;
            while(current_node!=NULL){
                if (val < current_node->_item){
                    prev = current_node;
                    current_node = current_node->left;
                }else{
                    prev = current_node;
                    current_node = current_node->right;
                }
            }
            if (val < prev->_item){
                prev->left= new_node;
            }else{
                prev->right = new_node;
            }
        }
}

template <class T>
bool BinSTree<T>::isInTree(T val, int& count){
    int comparison = 0;
    if(root != nullptr){
        bool found = false;
        Node* current = root;
        while(current != NULL){
            comparison++;
            if(val < current->_item){
                current = current->left;
            }else if(val > current->_item){
                current = current->right;
            }else{
                found = true;
                break;
            }
        }
        count = comparison;
        return found;
    }else{
        count = comparison;
        return false;
    }
};

template <class T>
BinSTree<T>::~BinSTree(){
    delete_node(root);
};

template<class T>
void BinSTree<T>::delete_node(BinSTree::Node *node) {
    if(node != NULL){
        delete_node(node->right);
        delete_node(node ->left);
        delete node;
    }
}

int main() {
    std::cout << "Hello, World!" << std::endl;
    BinSTree<int> binary_tree;
    int i;
    srand(time(NULL));
    // generates 10000 random numbers
    cout << "BST exerciser (" << RAND_NUMBER << " stored to the tree, " << RAND_NUMBER << " items searched for)" <<endl;
    cout << "Numbers inserted to the BST:" << endl;
    for (i = 0; i < RAND_NUMBER; i++){
        int val = rand() % RAND_NUMBER;
        cout << val  << " ";
        binary_tree.insert_to_tree(val);
    }
    cout << endl;
    vector<int>comparison_vector;
    for(int j=0; j<RAND_NUMBER; j++ ){
        int comparison;
        bool found = binary_tree.isInTree(j, comparison);
        string s  = found ? "" : " not ";
        cout << j << ": " << s << "found " << comparison << " comparison needed" << endl;
        comparison_vector.push_back(comparison);
    }
    cout << "Theoretical number of comparisions needed is  "<< setprecision(2) << log2(RAND_NUMBER) << endl;
    cout << "Average number of actual comparision is " << reduce(comparison_vector.begin(), comparison_vector.end())/(float)comparison_vector.size() << endl;
    cout << "Min depth " << *min_element(comparison_vector.begin(), comparison_vector.end()) << ", Max depth " << *max_element(comparison_vector.begin(), comparison_vector.end()) << endl;
    return 0;
}
