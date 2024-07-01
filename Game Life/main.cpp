#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <utility>
#include <Windows.h>

void print(char** MAP, int ROWS, int COLS) {
    for (int i = 0; i < ROWS; ++i) {
        std::cout << std::endl;
        for (int j = 0; j < COLS; ++j) {
            std::cout << MAP[i][j];
        }
    }
    std::cout << std::endl;
}

void change_MAP(std::vector<std::pair<int, int>> vec,int size, char** &MAP, int ROWS, int COLS) {
    for (int i = 0; i < vec.size(); ++i) {
        MAP[vec[i].first][vec[i].second] = '*';
    }
}

char** create_MAP(int ROWS, int COLS) {
    char** MAP;
    MAP = new char* [ROWS];
    for (int i = 0; i < ROWS; ++i) {
        MAP[i] = new char[COLS];
    }
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            MAP[i][j] = '-';
        }
    }
    return MAP;
}

int siz() {
    std::ifstream fin("input.txt");
    int a, size = 0;
    while (fin >> a) {
        ++size;
    }
    return size - 2;//размер массива звёздочек
}

int count(int x, int y, int ROWS, int COLS, char** MAP) {
    int res = 0;
    if (y == 0 && x != 0 && x != ROWS - 1) {
        if (MAP[x - 1][y] == '*') ++res; if (MAP[x - 1][y + 1] == '*') ++res; if (MAP[x][y + 1] == '*') ++res; if (MAP[x + 1][y + 1] == '*') ++res; if (MAP[x + 1][y] == '*') ++res;
        return res;
    }
    else if (x == 0 && y != 0 && y != COLS - 1) {
        if (MAP[x][y - 1] == '*') ++res; if (MAP[x][y + 1] == '*') ++res; if (MAP[x + 1][y - 1] == '*') ++res; if (MAP[x + 1][y] == '*') ++res; if (MAP[x + 1][y + 1] == '*') ++res;
        return res;
    }
    else if (y == COLS - 1 && x != 0 && x != ROWS - 1) {
        if (MAP[x - 1][y - 1] == '*') ++res; if (MAP[x - 1][y] == '*') ++res; if (MAP[x][y - 1] == '*') ++res; if (MAP[x + 1][y - 1] == '*') ++res; if (MAP[x + 1][y] == '*') ++res;
        return res;
    }
    else if (x == ROWS - 1 && y != 0 && y != COLS - 1) {
        if (MAP[x - 1][y - 1] == '*') ++res; if (MAP[x - 1][y] == '*') ++res; if (MAP[x - 1][y + 1] == '*') ++res; if (MAP[x][y - 1] == '*') ++res; if (MAP[x][y + 1] == '*') ++res;
        return res;
    }
    else if (x == 0 && y == 0) {
        if (MAP[1][0] == '*') ++res; if (MAP[1][1] == '*') ++res; if (MAP[0][1] == '*') ++res;
        return res;
    }
    else if (x == ROWS - 1 && y == 0) {
        if (MAP[ROWS - 2][0] == '*') ++res; if (MAP[ROWS - 2][1] == '*') ++res; if (MAP[ROWS - 1][1] == '*') ++res;
        return res;
    }
    else if (x == ROWS - 1 && y == COLS - 1) {
        if (MAP[ROWS - 1][COLS - 2] == '*') ++res; if (MAP[ROWS - 2][COLS - 2] == '*') ++res; if (MAP[ROWS - 2][COLS - 1] == '*') ++res;
        return res;
    }
    else if (x == 0 && y == COLS - 1) {
        if (MAP[0][COLS - 2] == '*') ++res; if (MAP[1][COLS - 2] == '*') ++res; if (MAP[1][COLS - 1] == '*') ++res;
        return res;
    }
    if (MAP[x - 1][y - 1] == '*') ++res; if (MAP[x - 1][y] == '*') ++res; if (MAP[x - 1][y + 1] == '*') ++res; if (MAP[x][y - 1] == '*') ++res; if (MAP[x][y + 1] == '*') ++res; if (MAP[x + 1][y - 1] == '*') ++res; if (MAP[x + 1][y] == '*') ++res; if (MAP[x + 1][y + 1] == '*') ++res;
    return res;
}//считаем сколько соседей(вроде работает норм)

int main() {
    bool isRunning = true;
    int ROWS, COLS, size = (siz()) / 2, c = 0;
    std::vector<std::pair<int, int>> vec;
    std::vector<std::pair<int, int>> copy;
    vec.resize(size);
    std::ifstream fin("input.txt");
    fin >> ROWS;
    fin >> COLS;
    char** MAP = create_MAP(ROWS, COLS);//создали нашу карту
    for (int i = 0; i < size; ++i) {
        fin >> vec[i].first;
        fin >> vec[i].second;//всё ок получили массив звёздочек
        //std::cout << vec[i].first;
        //std::cout << " " << vec[i].second << std::endl;
    }//это постоянная часть, а дальше идёт цикл

    change_MAP(vec, size, MAP, ROWS, COLS);
    print(MAP, ROWS, COLS);

    while (isRunning) {
        copy.resize(size);
        if (vec.size() < 1) {
            isRunning = false;
        }
        for (int i = 0; i < vec.size(); ++i) {
            copy[i] = vec[i];
        }
        //change_MAP(vec, size, MAP, ROWS, COLS);
        //print(MAP, ROWS, COLS);

        for (int i = 0; i < ROWS; ++i) {
            for (int j = 0; j < COLS; ++j) {
                if (MAP[i][j] == '-' && count(i, j, ROWS, COLS, MAP) == 3) {
                    MAP[i][j] = '*';
                    std::pair<int, int> coor = std::make_pair(i, j);
                    vec.push_back(coor);//добавляем в вектор новую точку
                    ++size;
                    vec.resize(size);
                }
                else if ((MAP[i][j] == '*' && (count(i, j, ROWS, COLS, MAP) < 2)) || (MAP[i][j] == '*'  && count(i, j, ROWS, COLS, MAP) > 3)) {
                    MAP[i][j] = '-';
                    for (int k = 0; k < vec.size(); ++k) {
                        if (vec[k].first == i && vec[k].second == j) {
                            vec.erase(vec.begin() + k);//убиарем точку из вектора
                            --size;
                            vec.resize(size);
                        }
                    }
                }
            }
        }//меняем клетки и вектор
        if (copy.size() == vec.size()) {
            for (int i = 0; i < size; ++i) {
                if (copy[i] == vec[i]) ++c;
            }
            if (c == vec.size()) isRunning = false;
            c = 0;
        }//выход при стабилизации
        change_MAP(vec, size, MAP, ROWS, COLS);
        print(MAP, ROWS, COLS);
        Sleep(500);
    }

    //std::cout << count(5, 0, ROWS, COLS, MAP);
    return 0;
}