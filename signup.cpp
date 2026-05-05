#include <iostream>
#include <fstream>
#include "auth.h"

void registerUser() {
    std::string username, password;

    std::cout << "Enter new username: ";
    std::cin >> username;

    std::cout << "Enter new password: ";
    std::cin >> password;

    std::ofstream file("users.txt", std::ios::app);
    file << username << " " << password << std::endl;

    std::cout << "Registered successfully!\n";
}