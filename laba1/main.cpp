
#include "interface.h"
#include <locale>  // Для работы с локалями
#include <clocale> // Для setlocale

int main() {

    std::setlocale(LC_ALL, "ru_RU.UTF-8");
    interface();
    
    
    return 0;
}

