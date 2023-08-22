#include "matrix.h"

#include <iostream>
#include <tuple>
#include <format>

int main(int argc, char** argv)
{
    matrix<int, 0> m;

    // Заполняем главную диагональ
    for (int i = 0; i <= 9; i++)
        m[i][i] = i;

    // Заполняем побочную диагональ
    for (int i = 9; i >= 0; i--)
        m[i][9 - i] = i;

    // Печатаем матрицу
    for (int i = 0; i <= 9; i++) {
        for (int j = 0; j <= 9; j++) {
            std::cout << m[i][j] << " ";
        }
        std::cout << std::endl;
    }

    // Количество занятых ячеек
    std::cout << std::endl;
    std::cout << "Non-default cells: " << m.size() << std::endl;

    // Занятые ячейки и их позиции
    for (auto it = m.begin(); it != m.end(); ++it) {
        std::cout << std::format("Cell ({}, {}) contains value {}",
                                 std::get<0>(*it), std::get<1>(*it), std::get<2>(*it)) << std::endl;
    }
}
