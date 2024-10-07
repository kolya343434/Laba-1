// ConsoleApplication1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//



#include <iostream>
#include <vector>
#include <random>
#include <numeric> // Для std::partial_sum
#include "gnuplot-iostream.h"

int main() {
    Gnuplot gp("\"D:\\Microsoft VS Code\\labrurary_graphics\\gnuplot\\bin"\");  // Если Gnuplot добавлен в PATH, просто используйте Gnuplot gp;

    // Инициализация генератора случайных чисел
    std::random_device rd;
    std::mt19937 mt(rd());
    std::normal_distribution<double> normdist(0., 1.);

    // Векторы для хранения данных
    std::vector<double> ve(1000), v1(1000); // Изменено на 1000, чтобы заполнить векторы

    // Заполнение векторов случайными значениями
    for (int i = 0; i < 1000; i++) {
        ve[i] = normdist(mt);
        v1[i] = normdist(mt);
    }

    // Вычисление частичных сумм
    std::partial_sum(ve.begin(), ve.end(), ve.begin());
    std::partial_sum(v1.begin(), v1.end(), v1.begin());

    // Установка заголовка и построение графика
    gp << "set title 'Graph of two random lines'\n";
    gp << "plot '-' with lines title 've', '-' with lines title 'v1'\n";

    // Отправка данных в Gnuplot
    gp.send1d(ve);
    gp.send1d(v1);

    std::cin.get(); // Ожидание ввода перед завершением
    return 0;
}
