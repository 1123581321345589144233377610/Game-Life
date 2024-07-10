#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <Windows.h>

struct point {
    int x;
    int y;
};//������� ���� �� ���������

void print(char** MAP, int ROWS, int COLS) {
    for (int i = 0; i < ROWS; ++i) {
        std::cout << std::endl;
        for (int j = 0; j < COLS; ++j) {
            std::cout << " " <<  MAP[i][j];
        }
    }
    std::cout << std::endl;
}

void change_MAP(std::vector<point> vec,int size, char** &MAP, int ROWS, int COLS) {
    for (int i = 0; i < vec.size(); ++i) {
        MAP[vec[i].x][vec[i].y] = '*';
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
    return size - 2;//������ ������� ��������
}

int count(int x, int y, int ROWS, int COLS, char** MAP) {
    if (x < 0 || x >= ROWS || y < 0 || y >= COLS) return 0;
    else if (MAP[x][y] == '*') return 1;
    return 0;
}

int count_neighbours(int x, int y, int ROWS, int COLS, char** MAP) {
    int neighbours = 0;
    neighbours += count(x - 1, y - 1, ROWS, COLS, MAP);
    neighbours += count(x - 1, y, ROWS, COLS, MAP);
    neighbours += count(x - 1, y + 1, ROWS, COLS, MAP);
    neighbours += count(x, y - 1, ROWS, COLS, MAP);
    neighbours += count(x, y + 1, ROWS, COLS, MAP);
    neighbours += count(x + 1, y - 1, ROWS, COLS, MAP);
    neighbours += count(x + 1, y, ROWS, COLS, MAP);
    neighbours += count(x + 1, y + 1, ROWS, COLS, MAP);
    return neighbours;
}//����� ������� �������

void output(int n, int size) {
    std::cout << "Generation: " << n << "." << " ";
    std::cout << "Alive cells: " << size << std::endl;
}//����� ���������� � ���������� � �������

int main() {
    bool isRunning = true;
    int ROWS, COLS, size = (siz()) / 2, c = 0, number_of_generation = 1, flag1 = 0, flag2 = 0;
    std::vector<point> vec;
    std::vector<point> copy;
    vec.resize(size);
    std::ifstream fin("input.txt");
    fin >> ROWS;
    fin >> COLS;
    char** MAP = create_MAP(ROWS, COLS);//������� ���� �����
    char** COPY_MAP = create_MAP(ROWS, COLS);
    for (int i = 0; i < size; ++i) {
        fin >> vec[i].x;
        fin >> vec[i].y;//�� �� �������� ������ ��������
    }

    change_MAP(vec, size, MAP, ROWS, COLS);
    print(MAP, ROWS, COLS);
    output(number_of_generation, size);
    Sleep(1000);//��� ���������� �����, � ������ ��� ����

    while (isRunning) {
        system("cls");
        copy.resize(size);
        if (vec.size() < 1) {
            isRunning = false;
            ++flag1;
            continue;
        }
        ++number_of_generation;
        for (int i = 0; i < ROWS; ++i) {
            for (int j = 0; j < COLS; ++j) {
                COPY_MAP[i][j] = MAP[i][j];//�������� �������������� ��������� ���������
            }
        }

        for (int i = 0; i < vec.size(); ++i) {
            copy[i] = vec[i];
        }

        for (int i = 0; i < ROWS; ++i) {
            for (int j = 0; j < COLS; ++j) {
                if (COPY_MAP[i][j] == '-' && count_neighbours(i, j, ROWS, COLS, COPY_MAP) == 3) {
                    MAP[i][j] = '*';
                    point coor; coor.x = i; coor.y = j;
                    vec.push_back(coor);//��������� � ������ ����� �����
                    ++size;
                    vec.resize(size);
                }
                else if ((COPY_MAP[i][j] == '*' && (count_neighbours(i, j, ROWS, COLS, COPY_MAP) < 2)) || (COPY_MAP[i][j] == '*'  && count_neighbours(i, j, ROWS, COLS, COPY_MAP) > 3)) {
                    MAP[i][j] = '-';
                    for (int k = 0; k < vec.size(); ++k) {
                        if (vec[k].x == i && vec[k].y == j) {
                            vec.erase(vec.begin() + k);//������� ����� �� �������
                            --size;
                            vec.resize(size);
                        }
                    }
                }
            }
        }//������ ������ � ������
        if (copy.size() == vec.size()) {
            for (int i = 0; i < size; ++i) {
                if (copy[i].x == vec[i].x && copy[i].y == vec[i].y) ++c;
            }
            if (c == vec.size()) {
                isRunning = false;
                ++flag2;
            }
            c = 0;
        }//����� ��� ������������
        change_MAP(vec, size, MAP, ROWS, COLS);
        print(MAP, ROWS, COLS);
        output(number_of_generation, size);
        Sleep(1000);
    }
    Sleep(1000);
    if(flag1 == 1) std::cout << "All cells are died. Game over";
    if(flag2 == 1) std::cout << "The world has stagnated. Game over";//������� ������� ���������� ����
    for (int i = 0; i < ROWS; ++i) {
        delete[] MAP[i];
    }
    delete[] MAP;
    for (int i = 0; i < ROWS; ++i) {
        delete[] COPY_MAP[i];
    }
    delete[] COPY_MAP;
    vec.clear();
    copy.clear();//������ ������
    fin.close();
    return 0;
}