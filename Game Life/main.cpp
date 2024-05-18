#include <iostream>
#include <string>
#include <fstream>
#include <vector>

struct point {
    int x;
    int y;
};

int siz(){
    int size = 0;
    std::string s;
    std::ifstream fin("input.txt");
    while (fin >> s) {
        ++size;
    }
    return size;
}

point* copy(point* v, int size){
    point* copy = new point[size];
    for (int i = 0; i < size; ++i) {
        copy[i] = v[i];
    }
    return copy;
}

int main() {
    int ROWS, COLS;
    int temp1, temp2;
    std::ifstream fin("input.txt");
    int size = siz();
    point* v = new point[size];
    fin.seekg(0);
    fin >> ROWS >> COLS;

    if (fin.is_open()) {
        for (int i = 0; i < size; ++i) {
            while (fin >> temp1 >> temp2) {
                v[i].x = temp1;
                v[i].y = temp2;
                std::cout << v[i].x << "\n" << v[i].y << std::endl;
            }
        }
    }
    fin.close();
}