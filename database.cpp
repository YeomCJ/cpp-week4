#include "database.h"
#include <cstring>
#include <cstdlib>
#include <string>
#include <cstdio>
#include <iostream>

using namespace std;


// 엔트리를 생성한다.
Entry* create(Type type, std::string key, void* value) {
    Entry* newentry = new Entry;
    newentry->type = type;
    newentry->key = key;
    newentry->value = value;

    return newentry;
}

// 데이터베이스의 리스트를 출력한다.
void list(Database& database) {

    for (int i = 0; i < database.count; i++) {
        if (database.entry[i].type == Type::INT) {
            std::cout << database.entry[i].key << ": " << *((int*)database.entry[i].value) << '\n';
        }
        else if (database.entry[i].type == Type::DOUBLE) {
            
            std::cout << database.entry[i].key << ": " << *((double*)database.entry[i].value) << '\n';
        }
        else if (database.entry[i].type == Type::STRING) {
            std::cout << database.entry[i].key << ": " << *((std::string*)database.entry[i].value) << '\n';
        }
        else if (database.entry[i].type == Type::ARRAY) {

            for (int j = i; j < database.array->size; j++) {
                std::cout << database.entry[i].key << ": ";
                std::cout << *((int*)database.array->items);
                

            }
        }
    }
}

// 데이터베이스를 초기화한다.
void init(Database& database) {
    database.count = 1;
    database.entry = nullptr;
}

// 데이터베이스에 엔트리를 추가한다.
void add(Database& database, Entry* entry) {
    std::string key, b;
    Type t;

    Entry* newEntry = new Entry;

    std::cout << "key: ";
    std::cin >> key;
    std::cout << "type (int, double, string, array): ";
    std::cin >> b;
    std::cout << "value: ";


    if (b == "int") {
        t = Type::INT;
        int* c = new int;
        std::cin >> *c;
        newEntry = create(t, key, c);
    }

    else if (b == "double") {
        t = Type::DOUBLE;
        double* c = new double;
        std::cin >> *c;
        std::cout << std::fixed;
        std::cout.precision(3);
        newEntry = create(t, key, c);
    }

    else if (b == "string") {
        t = Type::STRING;
        std::string* c = new std::string;
        std::cin.ignore();
        std::getline(std::cin, *c);
        newEntry = create(t, key, c);
    }

    // ---------------------------- array ------------------------------

    else if (b == "array") {
        
        t = Type::ARRAY;
        std::string c;
        std::cout << "type (int, double, string, array): ";
        std::cin >> c; 
        
        if (c != "array") {
            
            std::cout << "size: ";
            std::cin >> database.array ->size;

            if (c == "int") {
                database.array->type = Type::INT;
                int* c = new int[database.array->size];
                for (int i = 0; i < database.array->size; i++) {
                    std::cout << "item[" << i << "]: ";
                    std::cin >> c[i];
                }
                newEntry = create(t, key, c);
            }

            else if (c == "double") {

                database.array->type = Type::DOUBLE;
                double* c = new double[database.array->size];
                std::cin >> *c;
                std::cout << std::fixed;
                std::cout.precision(3);
                newEntry = create(t, key, c);
            }

            else if (c == "string") {

                database.array->type = Type::STRING;
                std::string* c = new std::string[database.array->size];
            }
        }

        else {
            return add(database, nullptr);
        }
        
    }

    else {
        std::cout << "Invalid out";
        return;
    }

    

    if (database.entry == nullptr) {
        database.entry = new Entry[1];
        database.entry[0] = *newEntry;

    }
    else {
        Entry* tmp = new Entry[database.count + 1];
        for (int i = 0; i < database.count; ++i) {
            tmp[i] = database.entry[i];
        }

        tmp[database.count] = *newEntry;
        delete[] database.entry;
        database.entry = tmp;

    }
    
    database.count++;

}

// 데이터베이스에서 키에 해당하는 엔트리를 찾는다.
Entry* get(Database& database, std::string& key) {
    return 0;
}

// 데이터베이스에서 키에 해당하는 엔트리를 제거한다.
void remove(Database& database, std::string& key) {

}

// 데이터베이스를 해제한다.
void destroy(Database& database) {
    delete[] database.entry;
}
