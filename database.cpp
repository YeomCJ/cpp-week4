#include "database.h"
#include <cstring>
#include <cstdlib>
#include <string>
#include <cstdio>
#include <iostream>

using namespace std;

// 엔트리를 생성한다.
Entry* create(Type type, std::string key, void* value)
{
    Entry* newentry = new Entry;
    newentry->type = type;
    newentry->key = key;
    newentry->value = value;

    return newentry;
}

// 데이터베이스의 리스트를 출력한다.
void list(Database& database)
{

    for (int i = 0; i < database.count; i++)
    {
        if (database.entry[i].type == Type::INT)
        {
            std::cout << database.entry[i].key << ": " << *((int*)database.entry[i].value) << '\n';
        }
        else if (database.entry[i].type == Type::DOUBLE)
        {

            std::cout << database.entry[i].key << ": " << *((double*)database.entry[i].value) << '\n';
        }
        else if (database.entry[i].type == Type::STRING)
        {
            std::cout << database.entry[i].key << ": " << *((std::string*)database.entry[i].value) << '\n';
        }

        else
        {
            Array* currentarray = (Array*)database.entry[i].value;

            std::cout << database.entry[i].key << ": ";
            if (currentarray->type == Type::INT) {
                int* items = (int*)currentarray->items;

                std::cout << "[";
                for (int j = 0; j < currentarray->size; j++)
                {
                    std::cout << items[j];
                    if (j != currentarray->size - 1)
                        std::cout << ", ";
                }
                std::cout << "]";
            }

            else if (currentarray->type == Type::DOUBLE)
            {
                double* items = (double*)currentarray->items;

                std::cout << "[";
                for (int j = 0; j < currentarray->size; j++)
                {
                    std::cout << items[j];
                    if (j != currentarray->size - 1)
                        std::cout << ", ";
                }
                std::cout << "]";
            }
            else if (currentarray->type == Type::STRING)
            {
                std::string* items = (std::string*)currentarray->items;

                std::cout << "[";
                for (int j = 0; j < currentarray->size; j++)
                {
                    std::cout << items[j];
                    if (j != currentarray->size - 1)
                        std::cout << ", ";
                }
                std::cout << "]";
            }

            std::cout << '\n';
        }

    }
}

// 데이터베이스를 초기화한다.
void init(Database& database)
{
    database.count = 0;
    database.entry = nullptr;
    database.array = new Array[1];
    database.arraycount = 0;

}

// 데이터베이스에 엔트리를 추가한다.
void add(Database& database, Entry* entry)
{
    std::string key, b;
    Type t;

    Entry* newEntry = new Entry;
    Array* newarray = new Array;

    std::cout << "key: ";
    std::cin >> key;
    std::cout << "type (int, double, string, array): ";
    std::cin >> b;
    std::cout << "value: ";

    if (b == "int")
    {
        t = Type::INT;
        int* c = new int;
        std::cin >> *c;
        newEntry = create(t, key, c);
    }

    else if (b == "double")
    {
        t = Type::DOUBLE;
        double* c = new double;
        std::cin >> *c;
        std::cout << std::fixed;
        std::cout.precision(3);
        newEntry = create(t, key, c);
    }

    else if (b == "string")
    {
        t = Type::STRING;
        std::string* c = new std::string;
        std::cin.ignore();
        std::getline(std::cin, *c);
        newEntry = create(t, key, c);
    }

    // ---------------------------- array ------------------------------

    else if (b == "array")
    {
        database.arraycount++;
        t = Type::ARRAY;
        std::string c;
        std::cout << "type (int, double, string, array): ";
        std::cin >> c;

        std::cout << "size: ";
        std::cin >> newarray->size;

        if (c == "int")
        {

            newarray->type = Type::INT;
            database.array->type = Type::INT;
            int* c = new int[newarray->size];
            for (int i = 0; i < newarray->size; i++)
            {
                std::cout << "item[" << i << "]: ";
                std::cin >> c[i];
            }
            newarray->items = c;

        }

        else if (c == "double")
        {

            newarray->type = Type::DOUBLE;
            double* c = new double[newarray->size];
            for (int i = 0; i < newarray->size; i++)
            {
                std::cout << "item[" << i << "]: ";
                std::cin >> c[i];
            }
            std::cout << std::fixed;
            std::cout.precision(3);

            newarray->items = c;

        }

        else if (c == "string")
        {

            newarray->type = Type::STRING;
            std::string* c = new std::string[newarray->size];
            for (int i = 0; i < newarray->size; i++)
            {
                std::cout << "item[" << i << "]: ";
                std::cin >> c[i];
                c[i] = "\"" + c[i] + "\"";
            }
            newarray->items = c;
        }


        else {
            return add(database, nullptr);
        }
        newEntry = create(t, key, newarray);
    }
    else
    {
        std::cout << "Invalid out";
        return;
    }
    //--------------------------------------------------------------
    if (database.entry == nullptr)
    {
        database.entry = new Entry[1];
        database.entry[0] = *newEntry;
    }
    else
    {
        Entry* tmp = new Entry[database.count + 1];
        for (int i = 0; i < database.count; ++i)
        {
            tmp[i] = database.entry[i];
        }

        tmp[database.count] = *newEntry;
        delete[] database.entry;
        database.entry = tmp;
    }

    database.count++;
}

// 데이터베이스에서 키에 해당하는 엔트리를 찾는다.
Entry* get(Database& database, std::string& key)
{
    for (int i = 0; i < database.count; i++) {
        if (database.entry[i].key == key) {
            if (database.entry[i].type == Type::INT)
                std::cout << key << ": " << *(int*)database.entry[i].value << "\n";
            else if (database.entry[i].type == Type::DOUBLE)
                std::cout << key << ": " << *(double*)database.entry[i].value << "\n";
            else if (database.entry[i].type == Type::STRING)
                std::cout << key << ": " << *(std::string*)database.entry[i].value << "\n";
            else {
                Array* array = (Array*)database.entry[i].value;
                std::cout << database.entry[i].key << ": ";
                if (array->type == Type::INT) {
                    int* items = (int*)array->items;

                    std::cout << "[";
                    for (int j = 0; j < array->size; j++)
                    {
                        std::cout << items[j];
                        if (j != array->size - 1)
                            std::cout << ", ";
                    }
                    std::cout << "]";
                }

                else if (array->type == Type::DOUBLE)
                {
                    double* items = (double*)array->items;

                    std::cout << "[";
                    for (int j = 0; j < array->size; j++)
                    {
                        std::cout << items[j];
                        if (j != array->size - 1)
                            std::cout << ", ";
                    }
                    std::cout << "]";
                }
                else if (array->type == Type::STRING)
                {
                    std::string* items = (std::string*)array->items;

                    std::cout << "[";
                    for (int j = 0; j < array->size; j++)
                    {
                        std::cout << items[j];
                        if (j != array->size - 1)
                            std::cout << ", ";
                    }
                    std::cout << "]";
                }
            }

            std::cout << '\n';
            return 0;
        }
    }
    std::cout << "not found\n";
    return 0;
}

// 데이터베이스에서 키에 해당하는 엔트리를 제거한다.
void remove(Database& database, std::string& key)
{
}

// 데이터베이스를 해제한다.
void destroy(Database& database)
{
    delete[] database.entry;
}
