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

        std::string key;

        std::cout << "command (list, add, get, del, exit): ";
        std::cin >> s;


        if (s == "list") list(data, -1);

        else if (s == "add") add(data, nullptr);

        else if (s == "get") {
            std::cout << "key: ";
            std::cin >> key;
            get(data, key);
        }

        else if (s == "del") {
            std::cout << "key: ";
            std::cin >> key;
            remove(data, key);
        }
        else if (s == "exit") {
            destroy(data);
            exit(0);
        }
        else {
            std::cout << "Invalid out";
        }

        std::cout << '\n';

    }
}