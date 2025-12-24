#include <iostream>
#include <fstream>
#include <string>
using namespace std;

const string DB_FILE = "users.txt";

bool usernameExists(const string &username) {
    ifstream fin(DB_FILE);
    if (!fin) return false;

    string u, p;
    while (fin >> u >> p) {
        if (u == username) {
            return true;
        }
    }
    return false;
}

bool registerUser() {
    string username, password;

    cout << "=== Registration ===\n";
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    if (username.size() < 3) {
        cout << "Error: Username must be at least 3 characters.\n";
        return false;
    }
    if (password.size() < 4) {
        cout << "Error: Password must be at least 4 characters.\n";
        return false;
    }

    if (usernameExists(username)) {
        cout << "Error: Username already exists. Choose another.\n";
        return false;
    }

    ofstream fout(DB_FILE, ios::app);
    if (!fout) {
        cout << "Error: Could not open user database file.\n";
        return false;
    }

    fout << username << " " << password << "\n";
    fout.close();

    cout << "Registration successful.\n";
    return true;
}

bool loginUser() {
    string username, password;
    cout << "=== Login ===\n";
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    ifstream fin(DB_FILE);
    if (!fin) {
        cout << "Error: No users registered yet.\n";
        return false;
    }

    string u, p;
    while (fin >> u >> p) {
        if (u == username && p == password) {
            cout << "Login successful. Welcome, " << username << "!\n";
            return true;
        }
    }

    cout << "Error: Invalid username or password.\n";
    return false;
}

int main() {
    int choice;

    do {
        cout << "\n===== Login & Registration System =====\n";
        cout << "1. Register\n";
        cout << "2. Login\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                registerUser();
                break;
            case 2:
                loginUser();
                break;
            case 0:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice.\n";
        }
    } while (choice != 0);

    return 0;
}
