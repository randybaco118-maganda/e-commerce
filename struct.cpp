#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <limits>

using namespace std;

// ================= STRUCTS =================
struct User {
    int id;
    string username, password, address, contact;
};

struct Product {
    int id;
    string name;
    float price;
    int stock;
};

struct CartItem {
    int id;
    string name;
    float price;
    int quantity;
};

// ================= PRODUCTS =================
vector<Product> products = {
    {1, "iPhone 13 (128GB)", 39990, 10},
    {2, "iPhone 14 (128GB)", 45990, 10},
    {3, "iPhone 15 (128GB)", 52990, 10},
    {4, "iPhone 16 (128GB)", 59990, 10},
    {5, "iPhone 17 (128GB)", 67990, 10}
};

vector<CartItem> cart;

User currentUser;
bool loggedIn = false;

// ================= UTIL =================
void clearInput() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// ================= SIGNUP =================
void signup() {
    ofstream file("users.txt", ios::app);
    User u;

    cout << "Enter ID: ";
    cin >> u.id;

    cout << "Username: ";
    cin >> u.username;

    cout << "Password: ";
    cin >> u.password;

    clearInput();
    cout << "Address: ";
    getline(cin, u.address);

    cout << "Contact: ";
    cin >> u.contact;

    file << u.id << " " << u.username << " " << u.password << " "
        << u.address << " " << u.contact << endl;

    file.close();

    cout << "Signup successful!\n";
}

// ================= LOGIN (FIXED) =================
void login() {
    ifstream file("users.txt");

    string username, password;

    cout << "Username: ";
    cin >> username;

    cout << "Password: ";
    cin >> password;

    User u;

    while (file >> u.id >> u.username >> u.password >> u.address >> u.contact) {
        if (u.username == username && u.password == password) {
            currentUser = u;
            loggedIn = true;
            cout << "Login successful!\n";
            return;
        }
    }

    cout << "Invalid login!\n";
}

// ================= PRODUCTS =================
void viewProducts() {
    cout << "\n===== iSTORE PRODUCTS =====\n";
    for (auto p : products) {
        cout << p.id << " | " << p.name
            << " | PHP " << p.price
            << " | Stock: " << p.stock << endl;
    }
}

// ================= CART =================
void addToCart() {
    int id, qty;
    cout << "Product ID: ";
    cin >> id;

    for (auto& p : products) {
        if (p.id == id) {
            cout << "Quantity: ";
            cin >> qty;

            if (qty <= 0 || qty > p.stock) {
                cout << "Invalid quantity!\n";
                return;
            }

            for (auto& c : cart) {
                if (c.id == id) {
                    c.quantity += qty;
                    p.stock -= qty;
                    cout << "Cart updated!\n";
                    return;
                }
            }

            cart.push_back({ p.id, p.name, p.price, qty });
            p.stock -= qty;

            cout << "Added to cart!\n";
            return;
        }
    }

    cout << "Product not found!\n";
}

// ================= VIEW CART =================
void viewCart() {
    cout << "\n===== CART =====\n";

    if (cart.empty()) {
        cout << "Cart is empty.\n";
        return;
    }

    for (auto c : cart) {
        cout << c.name
            << " | Qty: " << c.quantity
            << " | Total: PHP " << c.price * c.quantity << endl;
    }
}

// ================= TOTAL =================
float computeTotal() {
    float total = 0;
    for (auto c : cart)
        total += c.price * c.quantity;
    return total;
}

// ================= CHECKOUT =================
void checkout() {
    if (!loggedIn) {
        cout << "Login first!\n";
        return;
    }

    if (cart.empty()) {
        cout << "Cart empty!\n";
        return;
    }

    float subtotal = computeTotal();
    float vat = subtotal * 0.12;
    float shipping = 200;
    float total = subtotal + vat + shipping;

    cout << "\n===== CHECKOUT =====\n";
    cout << "Name: " << currentUser.username << endl;
    cout << "Address: " << currentUser.address << endl;
    cout << "Contact: " << currentUser.contact << endl;

    cout << "Subtotal: PHP " << subtotal << endl;
    cout << "VAT (12%): PHP " << vat << endl;
    cout << "Shipping: PHP " << shipping << endl;
    cout << "TOTAL: PHP " << total << endl;

    cout << "Confirm purchase? (1=yes): ";
    int confirm;
    cin >> confirm;

    if (confirm == 1) {
        string filename = "history_" + to_string(currentUser.id) + ".txt";
        ofstream history(filename, ios::app);

        for (auto c : cart) {
            history << c.id << " | " << c.name << " | "
                << c.price << " | " << c.quantity << " | "
                << c.price * c.quantity << endl;
        }

        history.close();
        cart.clear();

        cout << "Order placed successfully!\n";
    }
}

// ================= HISTORY =================
void viewHistory() {
    string filename = "history_" + to_string(currentUser.id) + ".txt";
    ifstream file(filename);

    cout << "\n===== PURCHASE HISTORY =====\n";

    if (!file) {
        cout << "No history found.\n";
        return;
    }

    string line;
    while (getline(file, line)) {
        cout << line << endl;
    }
}

// ================= REFUND =================
void refund() {
    int id, qty;
    cout << "Product ID: ";
    cin >> id;

    cout << "Quantity: ";
    cin >> qty;

    for (auto& p : products) {
        if (p.id == id) {
            p.stock += qty;
            cout << "Refund successful!\n";
            return;
        }
    }

    cout << "Product not found!\n";
}
