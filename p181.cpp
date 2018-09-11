#include <iostream>
#include <iomanip>

int main()
{
    constexpr size_t rowCnt = 3, colCnt = 4;
    int ia[rowCnt][colCnt];
    int *p = (int*)ia;

    for (size_t i = 0; i != rowCnt; ++i) {
        for (size_t j = 0; j !=colCnt; ++j) {
            ia[i][j] = i * colCnt + j;
            std::cout << "ia[" << i << "][" << j << "] = " << std::setw(2) << i*colCnt + j << "  ";
        }
        std::cout << std::endl;
    }

    for (int i = 0; i < 12; ++i) {
        std::cout << "ia + " << std::setw(2) << i << " : " << ia + i << "  |  ";
        std::cout << "*(ia + " << std::setw(2) << i << ") = " << std::setw(2) << *(p + i) << "  |  ";
        std::cout << "*((int*)ia + " << std::setw(2) << i << ") : " << std::setw(2) << *((int*)ia + i) <<  "  |  ";
        std::cout << "ia[" << std::setw(2) << i << "] = " << ia[i] <<  "  |  ";
        std::cout << "*ia[" << std::setw(2) << i << "] = " << *ia[i] << '\n';
    }
}
