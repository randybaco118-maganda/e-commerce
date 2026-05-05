#include <iostream>
#include "auth.h"

int main() {
    int choice;

    do {
        std::cout << "\n1. Login\n2. Register\n3. Exit\nChoice: ";
        std::cin >> choice;

        if (choice == 1) {
            if (login()) {
                std::cout << "Welcome to the system!\n";
            }
        }
        else if (choice == 2) {
            registerUser();
        }

    } while (choice != 3);

    return 0;
}