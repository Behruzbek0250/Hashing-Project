#include <iostream>
#include <istream>
#include <chrono>
#include <ctime>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <bits/stdc++.h>
#include <cstdlib>
#include <limits>
const int CAPACITY = 10000, PRIME = 199;
using namespace std;
struct Item {
    string Title_of_book, Authors, Average_rating, Num_pages, Ratings_count;
    Item(string Title_of_book, string Authors, string Average_rating, string Num_pages, string Ratings_count) {
        this->Title_of_book = Title_of_book;
        this->Authors = Authors;
        this->Average_rating = Average_rating;
        this->Num_pages = Num_pages;
        this->Ratings_count = Ratings_count;
    }
};
class HashTable {
public:
    Item **ht;
    bool flag[CAPACITY];
    int count = 0;
    HashTable() {
        ht = new Item*[CAPACITY];
        for (int i = 0; i < CAPACITY; i++) {
            ht[i] = NULL;
        }
        for (int i = 0; i < CAPACITY; i++) {
            flag[i] = false;
        }
    }
    int HashFunc(string key) {
        int a = 0;
        for (int i = 0; i < key.length(); ++i) {
            a += key[i];
        }
        return a % CAPACITY;
    }
    int HashFunc2(string key) {
        int a = 0;
        for (int i = 0; i < key.length(); ++i) {
            a += key[i];
        }
        return abs(PRIME - (a % CAPACITY)) % CAPACITY;
    }
    void Insert(string Title_of_book, string Authors, string Average_rating, string Num_pages, string Ratings_count) {
        int c1 = 0;
        if (count >= CAPACITY)
            return;
        int hashKey = HashFunc(Title_of_book);
        Item *en = ht[hashKey];
        while (en != NULL) {
            hashKey += HashFunc2(Title_of_book);
            hashKey %= CAPACITY;
            en = ht[hashKey];
            c1++;
            if (c1 >= CAPACITY) {
                cout << "The table is full!" << endl;
                return;
            }
        }
        if (en == NULL){
            en = new Item(Title_of_book, Authors, Average_rating, Num_pages, Ratings_count);
            ht[hashKey] = en;
            count++;
        }
        else {
            en->Authors = Authors;
            en->Average_rating = Average_rating;
            en->Num_pages = Num_pages;
            en->Ratings_count = Ratings_count;
        }
    }

    void Remove(string key) {
        int c1 = 0;
        int hashKey = HashFunc(key);
        Item* en = ht[hashKey];
        while (en != NULL || flag[hashKey]) {
            if (en->Title_of_book == key) {
                ht[hashKey] = NULL;
                if (HashFunc(en->Title_of_book) != hashKey)
                    flag[hashKey] = true;
                if (flag[hashKey - 1] || ht[hashKey - 1] == NULL || hashKey <= 0)
                    flag[hashKey + 1] = false;
                cout << "Element Deleted" << endl;
                count--;
                return;
            }
            hashKey++;
            hashKey %= CAPACITY;
            en = ht[hashKey];
            c1++;
            if (c1 >= CAPACITY){
                cout << "The item was not found!" << endl;
                return;
            }
        }
        cout << "The item was not found!" << endl;
        return;
    }
    void SearchKey(string key) {
        int c1 = 0;
        int hashKey = HashFunc(key);
        Item* en = ht[hashKey];
        while (en != NULL || flag[hashKey]) {
            if (en->Title_of_book == key) {
                cout << "Element found with Title " << key << ": " << endl << "Authors: " << en->Authors << endl
                     << "Average rating: " << en->Average_rating << endl
                     << "Number of pages: " << en->Num_pages << endl
                     << "Ratings count: " << en->Ratings_count << endl;
                return;
            }
            hashKey++;
            hashKey %= CAPACITY;
            en = ht[hashKey];
            c1++;
            if (c1 >= CAPACITY){
                cout << "The item was not found!" << endl;
                return;
            }
        }
        cout << "The item was not found!" << endl;
        return;
    }
    ~HashTable() {
        delete [] ht;
    }
};

void read_record(HashTable ht) {
    fstream fin;
    fin.open("Good_books.csv", ios::in);
    vector<string> row;
    string line, word, temp;
    for (int i = 1; i < 201; i++) {
        row.clear();
        getline(fin, line);
        stringstream s(line);
        while (getline(s, word, ',')) {
            row.push_back(word);
        }
        ht.Insert(row[0], row[1],row[2], row[3],  row[4]);
    }
}

int main() {
    HashTable ht;
    int c;
    string k;
    while (1) {
        cout << "1. Insert element into the table" << endl;
        cout << "2. Search element from the key" << endl;
        cout << "3. Delete element at a key" << endl;
        cout << "4. Exit" << endl << "Enter your choice: ";
        cin >> c;
        cout << endl;
        chrono::time_point<chrono::steady_clock> r1, r2;
        chrono::duration<double>dfr;
        switch(c) {
            case 1:
                r1 = chrono::steady_clock::now();
                read_record(ht);
                r2 = chrono::steady_clock::now();
                dfr = r2 - r1;
                cout << "Time complexity is " << dfr.count() << endl;
                break;
            case 2:
                cout << "Enter key of the element to be searched: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                getline(cin, k);
                r1 = chrono::steady_clock::now();
                ht.SearchKey(k);
                r2 = chrono::steady_clock::now();
                dfr = r2 - r1;
                cout << "Time complexity is " << dfr.count() << endl;
                break;

            case 3:
                cout << "Enter key of the element to be deleted: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                getline(cin, k);
                r1 = chrono::steady_clock::now();
                ht.Remove(k);
                r2 = chrono::steady_clock::now();
                dfr = r2 - r1;
                cout << "Time complexity is " << dfr.count() << endl;
                break;
            case 4:
                exit(1);
            default:
                cout << "\nEnter correct option\n";
        }
    }
    return 0;
}