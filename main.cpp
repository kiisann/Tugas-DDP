#include <iostream>
#include <fstream>
#include <string>
#include <ncurses/curses.h>
#include <windows.h>
using namespace std;

bool isLoggedIn() {
    tring username, password;
    tring un, pw;

    out << "Enter a username: ";
    in >> username; 
    out << "Enter a password: ";
    in >> password;

    ifstream read("akun.txt");
    if (!read.is_open()) {
        cerr << "Error opening file!" << endl;
        return false;
    }

    while (read >> un >> pw) { 
        if (un == username && pw == password) {
            return true;
        }
    }
    return false;
}

void registerAccount() {
    string username, password;

    cout << "Registration: " << endl;
    cout << "Select a username: "; 
    cin >> username;
    cout << "Select a password: ";
    cin >> password;

    ofstream file;
    file.open("akun.txt", ios::app);
    if (!file.is_open()) {
        cerr << "Error opening file!" << endl;
        return;
    }
    file << username << " " << password << endl;
    file.close();
    cout << "Welcome " << username << "!" << endl;
}

void loadingAnimation() {
    
    char bar1 = 177, bar2 = 219;

    cout << "\n\n\n\n\n\n\t\t\t\tLoading...";
    cout << "\n\n\t\t\t\t";

    for (int i = 0; i < 25; i++)
        cout << (char)bar1;

    cout << "\r\t\t\t\t";

    for (int i = 0; i < 25; i++) {
        cout << (char)bar2;
        Sleep(100);
    }

    cout << "\n\n\t\t\t\tDone!";
    system("Pause");
}

void dashboard() {
    int x = 10, y = 10; 
    int ch;
    
    initscr(); 
    raw(); 
    keypad(stdscr, TRUE);
    noecho();

    mvprintw(0, 0, "Gunakan tombol panah untuk bergerak. Tekan 'q' untuk keluar.");

    while ((ch = getch()) != 'q') {
        clear();
        refresh();
        mvprintw(0, 0, "Gunakan tombol panah untuk bergerak. Tekan 'q' untuk keluar.");

        switch (ch) {
            case KEY_UP:
                y = (y > 0) ? y - 1 : y;
                break; 
            case KEY_DOWN:
                y = (y < LINES - 1) ? y + 1 : y;
                break; 
            case KEY_LEFT:
                x = (x > 0) ? x - 1 : x;
                break;
            case KEY_RIGHT:
                x = (x < COLS - 1) ? x + 1 : x;
                break;
        }

        mvprintw(y, x, "A");
        refresh();
    }
    
    endwin();
}

int main() {
    int choice;

    while (true) {
        cout << endl;
        cout << "Main Menu: " << endl;
        cout << "-------------------------------" << endl;
        cout << "1. Register" << endl;
        cout << "2. Login" << endl;
        cout << "3. Exit" << endl;
        cout << endl;
        cout << "Your choice: ";
        cin >> choice; 

        if (choice == 1) {
            registerAccount();
        } else if (choice == 2) { 
            bool status = isLoggedIn();

            if (!status) { 
                cout << endl;
                cout << "Invalid login!" << endl;
            } else { // if isLoggedIn() returns true
                cout << "Successfully logged in!" << endl;
                loadingAnimation(); 
                dashboard(); 
            }
        } else if (choice == 3) {
            cout << "Exiting program." << endl;
            break;
        } else {
            cout << "Invalid choice! Please try again." << endl;
        }
    }

    return 0;
}
