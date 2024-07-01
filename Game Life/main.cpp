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
            std::cout << " " <<  MAP[i][j];
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
    return size - 2;//������ ������� ��������
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
}//������� ������� �������(����� �������� ����)

void output(int n, int size) {
    std::cout << "Generation: " << n << "." << " ";
    std::cout << "Alive cells: " << size << std::endl;
}//����� ���������� � ���������� � �������

int main() {
    bool isRunning = true;
    int ROWS, COLS, size = (siz()) / 2, c = 0, number_of_generation = 1, flag1 = 0, flag2 = 0;
    std::vector<std::pair<int, int>> vec;
    std::vector<std::pair<int, int>> copy;
    vec.resize(size);
    std::ifstream fin("input.txt");
    fin >> ROWS;
    fin >> COLS;
    char** MAP = create_MAP(ROWS, COLS);//������� ���� �����
    char** COPY_MAP = create_MAP(ROWS, COLS);
    for (int i = 0; i < size; ++i) {
        fin >> vec[i].first;
        fin >> vec[i].second;//�� �� �������� ������ ��������
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
                if (COPY_MAP[i][j] == '-' && count(i, j, ROWS, COLS, COPY_MAP) == 3) {
                    MAP[i][j] = '*';
                    std::pair<int, int> coor = std::make_pair(i, j);
                    vec.push_back(coor);//��������� � ������ ����� �����
                    ++size;
                    vec.resize(size);
                }
                else if ((COPY_MAP[i][j] == '*' && (count(i, j, ROWS, COLS, COPY_MAP) < 2)) || (COPY_MAP[i][j] == '*'  && count(i, j, ROWS, COLS, COPY_MAP) > 3)) {
                    MAP[i][j] = '-';
                    for (int k = 0; k < vec.size(); ++k) {
                        if (vec[k].first == i && vec[k].second == j) {
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
                if (copy[i] == vec[i]) ++c;
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
    copy.clear();//�������� ������
    return 0;
}