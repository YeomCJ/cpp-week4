#include <iostream>
#include <cstring>
#include <cstdlib>
#include <string>
#include <cstdio>
#include "database.h"


Database data;
Array ar;

int main() {

    init(data);
    while (true) {
        std::string s;

        std::string key, b;
        Type t;

        std::cout << "command (list, add, get, del, exit): ";
        std::cin >> s;

        
        if (s == "list") list(data);
        
        else if (s == "add") add(data, nullptr);
        
        else if (s == "get") {

        }
        else if (s == "del") {

        }
        else if (s == "exit") {
            destroy(data);
            exit(0);
        }
        else {

        }

        std::cout << '\n';

    }
}