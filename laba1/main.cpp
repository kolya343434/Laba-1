
#include "interface.h"
#include <locale>  
#include <clocale> // ��� setlocale

int main() {

    std::setlocale(LC_ALL, "Russian");
    interface();
    
    
    return 0;
}

