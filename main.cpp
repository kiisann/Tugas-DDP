#include <ncurses/curses.h>

void print_menu(WINDOW *menu_win, int pilihanTerpilih, const char *opsi[], int jumlahopsi);

int main() {
    initscr();
    clear();
    noecho();
    cbreak();

    int awalx = 0, awaly = 0;
    int lebar = 20, tinggi = 10;

    WINDOW *menu_win = newwin(tinggi, lebar, awaly, awalx);

    keypad(menu_win, TRUE);

    const char *opsi[] = {
        "Continue",
        "Login",
        "Exit",
    };

    int jumlahopsi = sizeof(opsi) / sizeof(char *);
    int pilihanTerpilih = 0;
    int pilihan = -1;

    while (1) {
        print_menu(menu_win, pilihanTerpilih, opsi, jumlahopsi);

        int tombol = wgetch(menu_win);

        switch (tombol) {
            case KEY_UP:
                if (pilihanTerpilih == 0) {
                    pilihanTerpilih = jumlahopsi - 1;
                } else {
                    --pilihanTerpilih;
                }
                break;

            case KEY_DOWN:
                if (pilihanTerpilih == jumlahopsi - 1) {
                    pilihanTerpilih = 0;
                } else {
                    ++pilihanTerpilih;
                }
                break;

            case 10: // Enter
                pilihan = pilihanTerpilih;
                break;
        }

        clrtoeol();
        refresh();

        if (pilihan == 3) {
            break;
        }
    }

    endwin(); 
    return 0;
}

void print_menu(WINDOW *menu_win, int pilihanTerpilih, const char *opsi[], int jumlahopsi) {
    for (int i = 0; i < jumlahopsi; ++i) {
        if (i == pilihanTerpilih) {
            wattron(menu_win, A_REVERSE);
        }

        mvwprintw(menu_win, i + 1, 1, opsi[i]);

        if (i == pilihanTerpilih) {
            wattroff(menu_win, A_REVERSE);
        }
    }

    wrefresh(menu_win);
}

