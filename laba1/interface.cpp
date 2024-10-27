#include "Tests.h"
#include "interface.h"
#include <string>

using namespace std;
void interface() {

    all_tests();

    int n;  


    SmartPointer::LinkedList<string> list_linkedlist_with_SmrtPtr;
    stdSmartPointer::SinglyLinkedList<string> list_linkedlist_with_std_SmrtPtr;

    
    while (true) {
        cout << "1)linkedlist_with_SmrtPtr" << endl;
        cout << "2)linkedlist_with_std_SmrtPtr" << endl;
        cout << "3)comparing" << endl;
        cout << "0)exit" << endl;  
        cout << "Write number: ";

        if (!(cin >> n)) {
            cout << "Error: Please enter a valid number." << endl;
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  
            continue;
        }

      
        if (n == 0) {
            cout << "Program finished." << endl;
            break;  
        }

        switch (n) {
        case 1: {
            int switcher_in_linkedlist_with_SmrtPtr;
            cout << "1)push_front\n";
            cout << "2)pop_front\n";
            cout << "3)print\n";
            cout << "4)find\n";
            cout << "5)exit to main menu\n";
            cout << "Write number: ";

            if (!(cin >> switcher_in_linkedlist_with_SmrtPtr)) {
                cout << "Error: Please enter a valid number." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }

            switch (switcher_in_linkedlist_with_SmrtPtr) {
            case 1: {
                string chislo_in_linkedlist_with_SmrtPtr;
                cout << "write: ";
                cin >> chislo_in_linkedlist_with_SmrtPtr;
                list_linkedlist_with_SmrtPtr.push_front(chislo_in_linkedlist_with_SmrtPtr);
                break;
            }
            case 2:
                list_linkedlist_with_SmrtPtr.pop_front();
                break;
            case 3:
                list_linkedlist_with_SmrtPtr.print();
                break;

            case 4: {
                cout << "write: ";
                string p;
                cin >> p;

                if (list_linkedlist_with_SmrtPtr.find(p)) {
                    cout << "Value found in the list: " << p << endl;
                }
                else {
                    cout << "Value not found in the list: " << p << endl;
                }
                break;
            }
            case 5:
                cout << "Returning to the main menu" << endl;
                break;
            default:
                cout << "Incorrect selection, please try again." << endl;
                break;
            }
            break;
        }
        case 2: {
            int switcher_in_linkedlist_with_std_SmrtPtr;
            cout << "1)push_front\n";
            cout << "2)pop_front\n";
            cout << "3)print\n";
            cout << "4)exit to main menu\n";
            cout << "Write number: ";

            if (!(cin >> switcher_in_linkedlist_with_std_SmrtPtr)) {
                cout << "Error: Please enter a valid number." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }

            switch (switcher_in_linkedlist_with_std_SmrtPtr) {
            case 1: {
                cout << "write: ";
                string chislo_in_linkedlist_with_SmrtPtr;
                cin >> chislo_in_linkedlist_with_SmrtPtr;
                list_linkedlist_with_std_SmrtPtr.push_front(chislo_in_linkedlist_with_SmrtPtr);
                break;
            }
            case 2:
                list_linkedlist_with_std_SmrtPtr.pop_front();
                break;
            case 3:
                list_linkedlist_with_std_SmrtPtr.print_list();
                break;
            case 4:
                cout << "Returning to the main menu" << endl;
                break;
            default:
                cout << "Incorrect selection, please try again." << endl;
                break;
            }
            break;
        }
        case 3: {
            time_test();
            break;
        }
        default:
            cout << "Incorrect selection in the main menu, please try again." << endl;
        }
    }
}


