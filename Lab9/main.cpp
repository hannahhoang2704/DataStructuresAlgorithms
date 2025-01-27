#include <iostream>
#include <map>
#include <iterator>
#include <algorithm>
#include <sstream>

using namespace std;

string check_command(const string input, const string delim, string& cmd);
void add_phone_address(const string input, const string delim, map<string, int>& book);
bool erase_address(const string name, map<string, int>& book);
void print_phone_book(const map<string,int> phone_book);


int main() {
    std::cout << "Hello, World!" << std::endl;
    map<string, int> phone_book;
    string command;
    string delimiter = " ";

    cout << "Phonebook application" << endl;
    getline(cin, command);
    while(true){
        string cmd;
        string arguments = check_command(command, delimiter, cmd);
        transform(cmd.begin(), cmd.end(), cmd.begin(), ::toupper);
        if(cmd == "ADD"){
            add_phone_address(arguments, delimiter, phone_book);
        }else if (cmd == "DELETE"){
            if(!(erase_address(arguments, phone_book))){
                cout << "Name  " << arguments << "does not found" << endl;
            }
        } else if (cmd == "LIST" ){
            print_phone_book(phone_book);
        }else if (cmd == "EXIT") {
            break;
        }else{
            cout << "Unrecognized command " << cmd << endl;
        }
        getline(cin, command);
    }

    return 0;
}

string  check_command(const string input, const string delim, string& cmd){
    size_t pos = input.find(delim);
    string arguments;
   if (pos != std::string::npos){
        cmd = input.substr(0, pos);
        arguments = input.substr(pos +1);
        return arguments;
   }else{
       cmd = input;
       return "";
   }
}

void add_phone_address(const string input, const string delim, map<string, int>& book){
    string name;
    string phone_nr;
    int nr;
    size_t pos = input.rfind(delim);
    if (pos != std::string::npos){
            name = input.substr(0, pos);
            phone_nr = input.substr(pos+1);
    }
    try{
        nr = stoi(phone_nr);
    }catch (const std::exception& e) {
        cout << "Invalid phone number format!" << endl;
        return;
    }
    book.insert(make_pair(name, nr));
}


bool erase_address(const string name, map<string, int>& book){
    auto it = book.find(name);
    if (it != book.end()){
        book.erase(it);
        return true;
    }else{
        return false;
    }
}

void print_phone_book(const map<string, int>phone_book){
    cout <<  "Content of the phone book:" << endl;
    for(const auto & [key, val] : phone_book ){
        cout << key << ": " << val  << endl;
    }
}