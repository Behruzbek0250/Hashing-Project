#include<bits/stdc++.h>
#include <chrono>
#include <ctime>
#define MAX_NUMBER 10
#define ver 2


int hashtable[ver][MAX_NUMBER];
int idx[ver];
void initialize_table() {
    for (int j = 0; j < MAX_NUMBER; j++) {
        for (int i = 0; i < ver; i++) {
            hashtable[i][j] = INT_MIN;
        }
    }
}

int hash_it(int function, int key) {
    switch (function) {
        case 1: return key % MAX_NUMBER;
        case 2: return (key / MAX_NUMBER) % MAX_NUMBER;
    }
}

void place_it(int key, int ID_value, int count, int n)
{
    if (count == n) {
        printf("%d unpositioned\n", key);
        printf("Cycle present. REHASH.\n");
        return;
    }
    for (int i = 0; i < ver; i++) {
        idx[i] = hash_it(i + 1, key);
        if (hashtable[i][idx[i]] == key)
            return;
    }
    if (hashtable[ID_value][idx[ID_value]] != INT_MIN) {
        int dis = hashtable[ID_value][idx[ID_value]];
        hashtable[ID_value][idx[ID_value]] = key;
        place_it(dis, (ID_value + 1) % ver, count + 1, n);
    }
    else
        hashtable[ID_value][idx[ID_value]] = key;
}

void print_hash() {
    printf("Final hash_it tables:\n");
    for (int i = 0; i < ver; i++, printf("\n")) {
        for (int j = 0; j < MAX_NUMBER; j++) {
            (hashtable[i][j] == INT_MIN) ? printf("- ") : printf("%d ", hashtable[i][j]);
        }
    }
    printf("\n");
}

void cuckoo_hash(int keys[], int n) {
    initialize_table();
    for (int i = 0, count = 0; i < n; i++, count = 0) {
        place_it(keys[i], 0, count, n);
    }
    print_hash();
}

int main()
{
    int keys_one[] = {20, 50, 53, 75, 100, 67, 105, 3, 36, 39};
    int n = sizeof(keys_one)/sizeof(int);
    cuckoo_hash(keys_one, n);

    int keys_two[] = {20, 50, 53, 75, 100, 67, 105, 3, 36, 39, 6};
    int m = sizeof(keys_two) / sizeof(int);
    cuckoo_hash(keys_two, m);
    return 0;
}
