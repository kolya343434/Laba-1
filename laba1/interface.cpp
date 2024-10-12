#include "Tests.h"
#include "interface.h"

using namespace std;

void interface() {
    int n;  // Переменная для выбора в меню
    SmartPointer::LinkedList<int> list_linkedlist_with_SmrtPtrst;
    stdSmartPointer::SinglyLinkedList<int> list_linkedlist_with_std_SmrtPtrst;
    // Бесконечный цикл (можно также использовать do-while)
    while (true) {
        cout << "1)linkedlist_with_SmrtPtr" << endl;
        cout << "2)linkedlist_with_std_SmrtPtr" << endl;
        cout << "3)comparing" << endl;
        cout << "0)exit" << endl;  // Добавляем пункт выхода
        cin >> n;

        // Проверка на выход
        if (n == 0) {
            cout << "programm finished" << endl;
            break;  // Выход из цикла
        }



        switch (n) {
        case 1: {
            int switcher_in_linkedlist_with_SmrtPtr;
            cout << "1)push_front\n";
            cout << "2)pop_front\n";
            cout << "3)print\n";
            cout << "4)find\n";
            cout << "5)exit to main menu\n";
            cin >> switcher_in_linkedlist_with_SmrtPtr;

            switch (switcher_in_linkedlist_with_SmrtPtr) {
            case 1: {
                int chislo_in_linkedlist_with_SmrtPtr;
                cout << "write number: ";
                cin >> chislo_in_linkedlist_with_SmrtPtr;
                list_linkedlist_with_SmrtPtrst.push_front(chislo_in_linkedlist_with_SmrtPtr);
                break;
            }
            case 2:

                list_linkedlist_with_SmrtPtrst.pop_front();
                break;

            case 3:

                list_linkedlist_with_SmrtPtrst.print();
                break;

            case 4:

                cout << "write number:" << endl;
                int n;
                cin >> n;

                if (list_linkedlist_with_SmrtPtrst.find(n)) {
                    std::cout << "Value found in the list:" << n << std::endl;
                }
                else {
                    std::cout << "Value  not found in the list:" << n << std::endl;
                }

                break;

            case 5:

                cout << "Returning to the main menu" << endl;
                break;

            default:

                cout << "incorrect choose" << endl;
                break;
            }
            break;
        }
        case 2: {
            int switcher_in_linkedlist_with_std_SmrtPtr;

            cout << "1)push_front" << endl;
            cout << "2)pop_front" << endl;
            cout << "3)print" << endl;
            cout << "4)exit to main menu" << endl;

            cin >> switcher_in_linkedlist_with_std_SmrtPtr;

            switch (switcher_in_linkedlist_with_std_SmrtPtr) {
            case 1: {
                cout << "write number: ";

                int chislo_in_linkedlist_with_SmrtPtr;
                cin >> chislo_in_linkedlist_with_SmrtPtr;

                list_linkedlist_with_std_SmrtPtrst.push_front(chislo_in_linkedlist_with_SmrtPtr);
                break;
            }
            case 2:
                list_linkedlist_with_std_SmrtPtrst.pop_front();
                break;
            case 3:
                list_linkedlist_with_std_SmrtPtrst.print_list();
                break;
            case 4:
                cout << "Returning to the main menu" << endl;
                break;
            default:
                cout << "incorrect choose" << endl;
                break;
            }
            break;
        }
        case 3: {
            int switcher_compar;

            cout << "1)start testing" << endl;
            cout << "2)Returning to the main menu" << endl;

            cin >> switcher_compar;

            switch (switcher_compar) {
            case 1:
                time_test();

            case 2:
                break;
            case 3:
            default:
                cout << "Incorrect selection in the main menu" << endl;
            }
        }
        default:
            cout << "Incorrect selection in the main menu" << endl;
        }
    }
}


