
#include "interface.h"
#include <locale>  // Для работы с локалями
#include <clocale> // Для setlocale

int main() {

    std::setlocale(LC_ALL, "Russian");
    interface();
    
    
    return 0;
}

