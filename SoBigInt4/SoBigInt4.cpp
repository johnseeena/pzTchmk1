#include <iostream>
#include "BigInt.h"
#include <locale>


void print_menu()
{
    system("cls"); // очищаем экран
    std::cout << "Что сделать хозяин? " << std::endl;
    std::cout << "1. Сложить " << std::endl;
    std::cout << "2. Вычесть " << std::endl;
    std::cout << "3. Умножить " << std::endl;
    std::cout << "4. Разделить " << std::endl;
    std::cout << "5. Модульное возведение в степень" << std::endl;
    /*std::cout << "6. Вычисление квадратного корня " << std::endl;*/
    std::cout << "6. Выход" << std::endl;
    std::cout << "<";
}
int main()
{
    setlocale(LC_ALL, "Russian");

    std::string strNum;
    BigInt modulo = BigInt(strNum);

    std::cout << "Введите первое число: ";

    std::cin >> strNum;

    BigInt soBigNum = BigInt(strNum);

    std::cout << "Введите второе число: ";

    std::cin >> strNum;
    /*BigInt sqrt = BigInt(1.2);*/
    BigInt soBigNum2 = BigInt(strNum);

    int var;

    do
    {
        
        print_menu();
        std::cout << "Выберите пункт: ";
        std::cin >> var;

        switch (var)
        {
        case 1:
            std::cout << soBigNum + soBigNum2 << std::endl;
            break;

        case 2:
            std::cout << soBigNum - soBigNum2 << std::endl;
            break;
        case 3:
            std::cout << soBigNum * soBigNum2 << std::endl;
            break;
        case 4:
            std::cout << soBigNum / soBigNum2 << std::endl;
            break;
        case 5:
            std::cout << "Введите модуль";
            std::cin >> strNum;
            std::cout << (soBigNum.pow(soBigNum2)) % modulo << std::endl;
            break;
        }
        if (var != 6)
            system("pause");
    } while (var != 6);



}

