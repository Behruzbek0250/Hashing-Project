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
const int CAPACITY = 200;
using namespace std;
struct Item {
    string Title_of_book, Authors, Average_rating, Num_pages, Ratings_count;
    Item *next;
    Item *prev;
    Item(string Title_of_book, string Authors, string Average_rating, string Num_pages, string Ratings_count) {
        this->Title_of_book = Title_of_book;
        this->Authors = Authors;
        this->Average_rating = Average_rating;
        this->Num_pages = Num_pages;
        this->Ratings_count = Ratings_count;
        this->next = NULL;
    }
};
class HashTable {
public:
    Item **ht, **top;
    HashTable() {
        ht = new Item*[CAPACITY];
        for (int i = 0; i < CAPACITY; i++) {
            ht[i] = NULL;
        }
    }
    int HashFunc(string key) {
        int a = 0;
        for (int i = 0; i < key.length(); ++i) {
            a += key[i];
        }
        return a % CAPACITY;
    }
    void Insert(string Title_of_book, string Authors, string Average_rating, string Num_pages, string Ratings_count) {
        int hashKey = HashFunc(Title_of_book);
        Item* prev = NULL;
        Item* en = ht[hashKey];
        while (en != NULL) {
            prev = en;
            en = en->next;
        }
        if (en == NULL) {
            en = new Item(Title_of_book, Authors, Average_rating, Num_pages, Ratings_count);
            if (prev == NULL)
                ht[hashKey] = en;
            else
                prev->next = en;
        } else {
            en->Authors = Authors;
            en->Average_rating = Average_rating;
            en->Num_pages = Num_pages;
            en->Ratings_count = Ratings_count;
        }
    }
    void Remove(string key) {
        int hash_v = HashFunc(key);
        Item* en = ht[hash_v];
        Item* p = NULL;
        if (en == NULL || en->Title_of_book != key) {
            cout << "No Element found at key " << key << endl;
            return;
        }
        while (en->next != NULL) {
            p = en;
            en = en->next;
        }
        if (p != NULL)
            p->next = en->next;
        delete en;
        cout << "Element Deleted" << endl;
    }
    void SearchKey(string k) {
        int hash_v = HashFunc(k);
        bool flag = false;
        Item* en = ht[hash_v];
        if (en != NULL) {
            while (en != NULL) {
                if (en->Title_of_book == k)
                    flag = true;
                if (flag)
                    cout << "Element found at Title " << k << ": " << endl << "Authors: " << en->Authors << endl
                            << "Average rating: " << en->Average_rating << endl
                            << "Number of pages: " << en->Num_pages << endl
                            << "Ratings count: " << en->Ratings_count << endl;
                en = en->next;
            }
        }
        if (!flag)
            cout << "No Element found at key " << k << endl;
    }
    ~HashTable() {
        delete [] ht;
    }
};

//void create()
//{
//    fstream fout;
//    fout.open("Good_books.csv", ios::out | ios::app);
//    cout << "Enter the details of 5 students: " << "roll Title_of_book maths phy chem bio" << endl;
//    string Title_of_book, Authors;
//    float Average_rating;
//    int i, Num_pages;
//    long int Ratings_count;
//    for (i = 1; i < 201; i++) {
//        cin >> Title_of_book >> Authors >> Average_rating >> Num_pages >> Ratings_count;
//        fout << Title_of_book << ", " << Authors << ", " << Average_rating << ", " << Num_pages << ", " << Ratings_count << "\n";
//    }
//}

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
