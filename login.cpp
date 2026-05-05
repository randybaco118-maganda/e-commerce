#include <iostream>
#include <fstream>
#include "auth.h"

bool login() {
    std::string username, password;
    std::string fileUser, filePass;

    std::cout << "Username: ";
    std::cin >> username;

    std::cout << "Password: ";
    std::cin >> password;

    std::ifstream file("users.txt");

    while (file >> fileUser >> filePass) {
        if (fileUser == username && filePass == password) {
            std::cout << "Login successful!\n";
            return true;
        }
    }

    std::cout << "Login failed.\n";
    return false;
}