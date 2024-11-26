#include <ncurses/curses.h>

void print_menu(WINDOW *menu_win, int pilihanTerpilih, const char *opsi[], int jumlahopsi);
void move_character(WINDOW *game_win, int &x, int &y, int input);

int main() {
    // Inisialisasi ncurses
    initscr();
    clear();
    noecho();
    cbreak();

    // Dimensi untuk menu dan layar permainan
    int menu_awalx = 5, menu_awaly = 3;
    int menu_lebar = 20, menu_tinggi = 10;
    int game_lebar = 40, game_tinggi = 20;

    // Membuat jendela menu dan layar permainan
    WINDOW *menu_win = newwin(menu_tinggi, menu_lebar, menu_awaly, menu_awalx);
    WINDOW *game_win = newwin(game_tinggi, game_lebar, menu_awaly, menu_awalx + menu_lebar + 5);
    keypad(menu_win, TRUE);
    keypad(game_win, TRUE); // Pastikan game_win juga menangkap tombol panah

    // Daftar opsi menu
    const char *opsi[] = {
        "Buat Akun",
        "Login",
        "Exit",
    };

    int jumlahopsi = sizeof(opsi) / sizeof(char *);
    int pilihanTerpilih = 0; // Indeks opsi yang disorot
    int pilihan = -1;        // Variabel untuk menyimpan pilihan pengguna

    // Posisi awal karakter dalam layar permainan
    int x = game_lebar / 2, y = game_tinggi / 2;

    // Loop menu utama
    while (1) {
        // Cetak menu
        print_menu(menu_win, pilihanTerpilih, opsi, jumlahopsi);
        int tombol = wgetch(menu_win);

        switch (tombol) {
            case KEY_UP:
                pilihanTerpilih = (pilihanTerpilih == 0) ? jumlahopsi - 1 : pilihanTerpilih - 1;
                break;
            case KEY_DOWN:
                pilihanTerpilih = (pilihanTerpilih == jumlahopsi - 1) ? 0 : pilihanTerpilih + 1;
                break;
            case 10: // Tombol Enter
                pilihan = pilihanTerpilih;
                break;
        }

        // Pilihan pengguna
        if (pilihan == 2) { // Exit
            break;
        } else if (pilihan == 0) { // Continue
            // Masuk ke mode permainan
            wclear(game_win);
            box(game_win, 0, 0);
            mvwprintw(game_win, 1, 1, "Gerakkan 'A' dengan tombol panah!");
            mvwprintw(game_win, 2, 1, "Tekan 'q' untuk kembali ke menu.");
            mvwaddch(game_win, y, x, 'A');
            wrefresh(game_win);

            // Loop permainan
            while (1) {
                int input = wgetch(game_win);
                if (input == 'q') { // Keluar permainan
                    break;
                }
                move_character(game_win, x, y, input);
            }
            pilihan = -1; // Kembali ke menu
        }
    }

    // Akhiri ncurses
    endwin();
    return 0;
}

// Fungsi untuk mencetak menu
void print_menu(WINDOW *menu_win, int pilihanTerpilih, const char *opsi[], int jumlahopsi) {
    wclear(menu_win);
    box(menu_win, 0, 0);
    mvwprintw(menu_win, 0, 1, " MENU ");

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

// Fungsi untuk menggerakkan karakter
void move_character(WINDOW *game_win, int &x, int &y, int input) {
    int max_x, max_y;
    getmaxyx(game_win, max_y, max_x);

    mvwaddch(game_win, y, x, ' '); // Hapus karakter dari posisi sebelumnya
    switch (input) {
        case KEY_UP:
            y = (y > 1) ? y - 1 : y;
            break;
        case KEY_DOWN:
            y = (y < max_y - 2) ? y + 1 : y;
            break;
        case KEY_LEFT:
            x = (x > 1) ? x - 1 : x;
            break;
        case KEY_RIGHT:
            x = (x < max_x - 2) ? x + 1 : x;
            break;
    }
    mvwaddch(game_win, y, x, 'A'); // Cetak karakter di posisi baru
    wrefresh(game_win);
}
