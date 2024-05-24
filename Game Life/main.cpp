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

point* fin_to_copy(int size) {
    point* copy = (point*)malloc(sizeof(int)*size);
    std::ifstream fin("input.txt");
    for (int i = 0; i < size; ++i) {
        fin >> copy[i].x >> copy[i].y;
    }
    return copy;
}

void change(char** &MAP, point* copy, int size, int ROWS, int COLS) {
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            for (int k = 0; k < size; ++k) {
                if (i == copy[k].x && j == copy[k].y) {
                    MAP[i][j] = '*';
                }
            }
        }
    }
}

void print(char** MAP, int ROWS, int COLS) {
    for (int i = 0; i < ROWS; ++i) {
        std::cout << std::endl;
        for (int j = 0; j < COLS; ++j) {
            std::cout << MAP[i][j];
        }
    }
}

char** create_MAP(int ROWS, int COLS) {
    char** MAP;
    MAP = new char* [ROWS];
    for (int i = 0; i < ROWS; ++i) {
        MAP[i] = new char[COLS];
    }
    return MAP;
}

int main() {
    int ROWS, COLS;
    char** MAP;
    point* copy;
    int temp1, temp2;
    std::ifstream fin("input.txt");
    int size = siz();
    point* v = new point[size];
    fin.seekg(0);
    fin >> ROWS >> COLS;
    copy = fin_to_copy(size);
    MAP = create_MAP(ROWS, COLS);

    fin.close();
    change(MAP, copy, size, ROWS, COLS);
    print(MAP, ROWS, COLS);
    return 0;
}