
#include "interface.h"
#include <locale>  // ��� ������ � ��������
#include <clocale> // ��� setlocale

int main() {

    std::setlocale(LC_ALL, "ru_RU.UTF-8");
    interface();
    
    
    return 0;
}

