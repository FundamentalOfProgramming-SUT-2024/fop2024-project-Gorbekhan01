#include <ncurses.h>
#include <locale.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <wchar.h>
#include <time.h>

void draw_character(int y, int x, int color) {
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_CYAN, COLOR_BLACK);
    init_pair(3, COLOR_GREEN, COLOR_BLACK);
    if(color==0){
        attron(COLOR_PAIR(1));
        mvprintw(y , x, "⌬");
        attroff(COLOR_PAIR(1));
    }
    else if(color==1){
        attron(COLOR_PAIR(2));
        mvprintw(y , x, "⌬");
        attroff(COLOR_PAIR(2));
    }
    else if(color==2){
        attron(COLOR_PAIR(3));
        mvprintw(y , x, "⌬");
        attroff(COLOR_PAIR(3));
    }
    else if(color==3){
        wchar_t cat = 0x0001F431;
        mvprintw(y, x, "%lc", cat);
    }

}

typedef struct game{
   char username[100];
   int music;
   int game_level;
   int player_color;
}game;

typedef struct user{
    char username[100];
    char total_score[100];
    char total_gold[100];
    char total_finished_games[100];
    char total_time[100];
    struct game game_setting;
}user;



void opening();
int choosing_user(char *username);
int new_user(char *username);
int old_user(char *username);
int game_menu(char *username);
int  leaderboard(struct user *current_user);
int gamesetting(struct user *current_user);
void easy_game(struct user *current_user);



int main() {

    start_color();
    setlocale(LC_ALL, "");
    initscr();
    noecho();
    cbreak();
    struct user current_user;
    opening();
    char username[50] = {};
    choosing_user(username);
    strcpy(current_user.username,username);
    int choice = game_menu(username);
    if(choice==0){
        leaderboard(&current_user);
        int level = gamesetting(&current_user);
        if (current_user.game_setting.game_level==0){
            easy_game(&current_user);
        }
    }

    endwin();
    return 0;
}

void opening() {
    initscr();
    curs_set(0);
    noecho();
    cbreak();

    clear();
    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);
    int center_y = max_y / 2 - 4;
    int center_x = max_x / 2 - 15;

    mvhline(center_y - 1, center_x, '-', 30);
    mvprintw(center_y, center_x, "______                       ");
    mvprintw(center_y + 1, center_x, "| ___ \\                      ");
    mvprintw(center_y + 2, center_x, "| |_/ /___   __ _ _   _  ___ ");
    mvprintw(center_y + 3, center_x, "|    // _ \\ / _` | | | |/ _ \\");
    mvprintw(center_y + 4, center_x, "| |\\ \\ (_) | (_| | |_| |  __/");
    mvprintw(center_y + 5, center_x, "\\_| \\_\\___/ \\__, |\\__,_|\\___| ");
    mvprintw(center_y + 6, center_x, "             __/ |           ");
    mvprintw(center_y + 7, center_x, "            |___/            ");
    mvhline(center_y + 8, center_x, '-', 30);
    mvprintw(center_y + 9, center_x + 5, " G     A     M     E");
    mvprintw(center_y + 11, center_x + 3, "▪ Powered by Gorbekhan ▪");

    refresh();
    sleep(2);
    clear();
    refresh();
}

int choosing_user(char *username){
    initscr();
    keypad(stdscr, TRUE);
    curs_set(0);
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    int selected = 0;
    int key;
    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);
    int center_y = max_y / 2 - 7;
    int center_x = max_x / 2 - 15;
    attron(COLOR_PAIR(1));
    while(1) {
        clear();
        mvprintw(center_y-6,center_y , "=== W E L C O M E ! ===");
        mvprintw(center_y-3,center_y , "Please choose one of this options to start the game!");
        mvprintw(center_y,center_y , selected == 0 ? "> new user" : "new user");
        mvprintw(center_y+2, center_y, selected == 1 ? "> old user " : "old user");
        mvprintw(center_y+4, center_y, selected == 2 ? "> continue as a guest"  : "continue as a guest");

        refresh();
        key = getch();

        switch(key) {
            case KEY_UP:
                selected--;
                if(selected < 0) {
                    selected = 2;
                }
                break;
            case KEY_DOWN:
                selected++;
                if(selected > 2) {
                    selected = 0;
                }
                break;
            case '\n':
                clear();
                if(selected == 0) {
                    new_user(username);
                    return 0;
                }
                else if(selected == 1) {
                    old_user(username);
                    return 0;
                }
                else if(selected == 2) {
                    strcpy(username,"guest");
                    return 0;
                }
                refresh();
                getch();
                break;
        }
    }
    refresh();
    attroff(COLOR_PAIR(1));
    endwin();
}

int old_user(char *username) {
    clear();
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);
    int center_y = max_y / 2 - 7;
    int center_x = max_x / 2 - 15;

    attron(COLOR_PAIR(1) | A_BOLD | A_BLINK);
    mvprintw(center_y, center_x, "                      ");
    mvprintw(center_y + 1, center_x, " P l a y e r  i n f o ");
    mvprintw(center_y + 2, center_x, "                      ");
    attroff(COLOR_PAIR(1) | A_BOLD | A_BLINK);

    mvprintw(center_y + 11, center_x-1, "\\    /\\");
    mvprintw(center_y + 12, center_x-1, " )  ( ') ");
    mvprintw(center_y + 13, center_x-1, "(  /  )");
    mvprintw(center_y + 14, center_x-1, " \\(__)|");
    mvprintw(center_y + 14, center_x-1, " \\(__)|");
    mvprintw(center_y + 18, center_x-20, "if you forget your password enter < forget > in password section!");

    mvprintw(center_y + 4, center_x, "◦ Username: ");
    mvprintw(center_y + 6, center_x, "◦ Password: ");

    refresh();

    echo();
    move(center_y + 4, center_x + 12);
    curs_set(1);
    getstr(username);
    FILE* fptr = fopen("users.txt", "r");
    if(fptr == NULL) {
        FILE* fptr = fopen("users.txt", "w");
        refresh();
    }
    char password[50];
    int len = 0;
    char temp_username[50];
    char temp_password[50];
    char temp_email[50];
    int temp = 0;
    char tempi[100];
    rewind(fptr);
    while (fgets(tempi, 100, fptr) != NULL) {
        sscanf(tempi, "%s %s %s", temp_username, temp_password, temp_email);
        if (strcmp(temp_username, username) == 0) {
            break;
        }
    }
    refresh();

    while(1) {

        move(center_y + 6, center_x + 12);
        clrtoeol();
        getstr(password);
        refresh();
        len = strlen(password);
        if (len < 7) {
            refresh();
            if (strcmp("forget", password) == 0) {
                mvprintw(center_y + 12, center_x + 9, "Your password is < %s >",temp_password);

            }
            else{
                mvprintw(center_y + 12, center_x + 9, "Password must be at least 7 letters!");
            }
        }
        else if(strcmp(temp_password,password)==0){
            mvprintw(center_y + 12, center_x + 9, "Correct!!                            ");
            break;

        }
        refresh();

    }

    mvprintw(center_y + 12, center_x+9, ". . .                                     ");
    clear();
    refresh();
    getch();
}

int new_user(char *username) {
    clear();
    start_color();
    curs_set(1);
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);
    int center_y = max_y / 2 - 7;
    int center_x = max_x / 2 - 15;

    attron(COLOR_PAIR(1) | A_BOLD | A_BLINK);
    mvprintw(center_y, center_x, "                      ");
    mvprintw(center_y + 1, center_x, " P l a y e r  i n f o ");
    mvprintw(center_y + 2, center_x, "                      ");
    attroff(COLOR_PAIR(1) | A_BOLD | A_BLINK);

    mvprintw(center_y + 11, center_x-1, "\\    /\\");
    mvprintw(center_y + 12, center_x-1, " )  ( ') ");
    mvprintw(center_y + 13, center_x-1, "(  /  )");
    mvprintw(center_y + 14, center_x-1, " \\(__)|");

    mvprintw(center_y + 4, center_x, "◦ Username: ");
    mvprintw(center_y + 6, center_x, "◦ Password: ");
    mvprintw(center_y + 8, center_x, "◦ Email: ");

    refresh();

    echo();
    int temp = 0;
    FILE* fptr = fopen("users.txt", "r");
    if(fptr == NULL) {
        FILE* fptr = fopen("users.txt", "w");
        refresh();
    }
    //taken username !!!!
    while (1) {
        move(center_y + 4, center_x + 12);
        clrtoeol();
        getstr(username);
        char temp_username[50];
        char temp_password[50];
        char temp_email[50];
        int temp = 0;
        char tempi[100];

        rewind(fptr);

        while (fgets(tempi, 100, fptr) != NULL) {
            sscanf(tempi, "%s %s %s", temp_username, temp_password, temp_email);
            if (strcmp(temp_username, username) == 0) {
                mvprintw(center_y + 12, center_x+9, "This username is taken! ");
                refresh();
                temp++;
                break;
            }
        }
        refresh();

        if(temp == 0) {
            break;
        }
    }
    mvprintw(center_y + 12, center_x+9, ". . .                       ");

    fclose(fptr);

    char password[50];
    int len = 0;
    while (len < 7) {
        clrtoeol();
        move(center_y + 6, center_x + 12);
        getstr(password);
        len = strlen(password);
        if (len < 7) {
            mvprintw(center_y + 12, center_x+9, "Password must be at least 7 letters!");
            refresh();
        }
    }
    mvprintw(center_y + 12, center_x+9, ". . .                                     ");

    char email[50];
    int t = 0;
    while (t != 1) {
        clrtoeol();
        move(center_y + 8, center_x + 12);
        getstr(email);
        if (strstr(email, "@") != 0 && strstr(email, ".") != 0) {
            t = 1;
        } else {
            mvprintw(center_y + 12, center_x+9, "Email is not valid!");
            t = 0;
        }
    }
    mvprintw(center_y + 12, center_x+9, "                    ");
    fptr= fopen("users.txt","a");
    fprintf(fptr,"%s %s %s\n",username,password,email);
    fclose(fptr);
    sleep(2);
    clear();
    refresh();
    getch();
}

int game_menu(char *username){
    initscr();
    keypad(stdscr, TRUE);
    curs_set(0);
    refresh();
    noecho();
    cbreak();
    clear();
    start_color();
    curs_set(1);
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);
    int center_y = max_y / 2 - 7;
    int center_x = max_x / 2 - 15;
    int selected =0;
    int key;
    while(1) {
        clear();
        attron(COLOR_PAIR(1) | A_BOLD);
        mvprintw(center_y - 2, center_x-4, "══════════════════════════════");
        attron(COLOR_PAIR(1) | A_BOLD | A_BLINK);
        mvprintw(center_y, center_x, "    WELCOME  %s ! ", username);
        attroff(COLOR_PAIR(1) | A_BOLD | A_BLINK);
        mvprintw(center_y + 2, center_x-4, "══════════════════════════════");
        attroff(COLOR_PAIR(1) | A_BOLD);
        mvprintw(center_y+20,center_x , selected == 0 ? "[ start a new game ]" : "start a new game");
        mvprintw(center_y+22, center_x-3, selected == 1 ? "[ continue your last Game ]" : "continue your last Game");
        refresh();
        key = getch();

        switch(key) {
            case KEY_UP:
                selected--;
                if(selected < 0) {
                    selected = 1;
                }
                break;
            case KEY_DOWN:
                selected++;
                if(selected > 1) {
                    selected = 0;
                }
                break;
            case '\n':
                clear();
                if(selected == 0) {
                    return 0;
                }
                else if(selected == 1) {
                    return 1;
                }
                refresh();
                getch();
                break;
        }
    }
    refresh();
    return 0;
}

int leaderboard(struct user *current_user) {
    initscr();
    keypad(stdscr, TRUE);
    curs_set(0);
    refresh();
    noecho();
    cbreak();
    clear();

    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);
    int center_y = max_y / 2 -10;
    int center_x = max_x / 2 -40;

    const int COL_WIDTH = 15;
    mvprintw(center_y, center_x + 25, "=== LEADERBOARD ===");
    mvprintw(center_y + 2, center_x, "%-10s %-15s %-15s %-15s %-15s %-15s",
             "Rank", "Username", "Score", "Gold", "Games", "Time");
    mvprintw(center_y + 3, center_x, "----------------------------------------------------------------");

    FILE* fptr = fopen("leaderboard.txt", "r");
    if (fptr == NULL) {
        mvprintw(center_y + 5, center_x, "No leaderboard data available!");
        refresh();
        getch();
        return 0;
    }

    int found = 0;
    char rank[100];
    char username1[100];
    char total_score[100];
    char total_gold[100];
    char total_finished_games[100];
    char total_time[100];
    char tempi[100];

    rewind(fptr);
    while (fgets(tempi, 100, fptr) != NULL) {
        sscanf(tempi, "%s %s %s %s %s %s", rank, username1, total_score, total_gold, total_finished_games, total_time);
        if (strcmp(username1, current_user->username) == 0) {
            found = 1;
            strcpy(current_user->total_score, total_score);
            strcpy(current_user->total_gold, total_gold);
            strcpy(current_user->total_time, total_time);
            strcpy(current_user->total_finished_games, total_finished_games);

            mvprintw(center_y + 4, center_x, "%-10s %-15s %-15s %-15s %-15s %-15s",
                     rank,
                     current_user->username,
                     current_user->total_score,
                     current_user->total_gold,
                     current_user->total_finished_games,
                     current_user->total_time);
            break;
        }
    }

    if (!found) {
        mvprintw(center_y + 5, center_x, "Player not found in leaderboard!");
    }

    fclose(fptr);
    mvprintw(center_y + 30, center_x+10, "[ Press enter to start the game ]");
    refresh();
    getch();
    return 0;
}

int gamesetting(struct user *current_user) {
    char *choices[] = {"easy", "medium", "hard"};
    char *colors[] = {"white", "cyan", "green","SPECIAL!"};

    int n_choices = 3;
    int current_choice = 0;
    int color_choice = 0;
    int current_menu = 0;
    int ch;

    initscr();
    clear();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);
    curs_set(0);

    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);
    int center_y = max_y / 2 - 7;
    int center_x = max_x / 2 - 15;

    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_BLACK, COLOR_WHITE);

        while (1) {
            clear();


            mvprintw(center_y - 6, center_x , "╔══════════════════════════════╗");
            mvprintw(center_y - 5, center_x , "║   G A M E  S E T T I N G S   ║");
            mvprintw(center_y - 4, center_x , "╚══════════════════════════════╝");

            attron(A_BOLD);
            attron(A_STANDOUT);
            mvprintw(center_y - 2, center_x , " Choose the game level");
            attroff(A_STANDOUT);
            attroff(A_BOLD);

            attron(A_BOLD);
            attron(A_STANDOUT);
            mvprintw(center_y + 8, center_x , " Choose your character's color");
            attroff(A_STANDOUT);
            attroff(A_BOLD);


            int level_start_x = center_x ;
            for (int i = 0; i < n_choices; i++) {
                if (current_menu == 0 && i == current_choice) {
                    attron(A_REVERSE);
                    mvprintw(center_y + 1, level_start_x + i * 9, "%s", choices[i]);
                    attroff(A_REVERSE);
                } else {
                    mvprintw(center_y + 1, level_start_x + i * 9, "%s", choices[i]);
                }
            }


            int color_start_x = center_x ;
            for (int i = 0; i < n_choices+1; i++) {
                if (current_menu == 1 && i == color_choice) {
                    attron(A_REVERSE);
                    mvprintw(center_y + 11, color_start_x + i * 9, "%s", colors[i]);
                    attroff(A_REVERSE);
                } else {
                    mvprintw(center_y + 11, color_start_x + i * 9, "%s", colors[i]);
                }
            }

            attron(A_BOLD);
            attron(A_STANDOUT);
            mvprintw(center_y + 20, center_x , "[ Press Enter to start the game ]");
            attroff(A_STANDOUT);
            attroff(A_BOLD);

            refresh();

            ch = getch();
            switch (ch) {
                case KEY_RIGHT:
                    if (current_menu == 0 && current_choice < n_choices - 1)
                        current_choice++;
                    else if (current_menu == 1 && color_choice < n_choices)
                        color_choice++;
                    break;
                case KEY_LEFT:
                    if (current_menu == 0 && current_choice > 0)
                        current_choice--;
                    else if (current_menu == 1 && color_choice > 0)
                        color_choice--;
                    break;
                case KEY_ENTER:
                case '\n':
                    if (current_menu == 0) {
                        current_user->game_setting.game_level = current_choice;
                        current_menu = 1;
                    } else if (current_menu == 1) {
                        current_user->game_setting.player_color = color_choice;
                        current_menu = 2;
                    } else if (current_menu == 2) {
                        endwin();
                        return 0;
                    }
                    break;
            }
        }

        endwin();
        return 0;
    }


void easy_game(struct user *current_user) {
    setlocale(LC_ALL, "");
    int max_y, max_x;

    initscr();
    keypad(stdscr, TRUE);
    noecho();
    curs_set(0);

    getmaxyx(stdscr, max_y, max_x);
    char map[max_y][max_x];

    for(int i = 0; i < max_y; i++) {
        for(int j = 0; j < max_x; j++) {
            map[i][j] = ' ';
        }
    }

    //number of rooms randomly
    srand(time(NULL));
    int number_of_rooms = 6 + (rand() % 3);
    int num = 0;

    while(num < number_of_rooms) {
        int size_room_y = 8 + (rand() % 6);
        int size_room_x = 8 + (rand() % 6);


        int room_y = 1 + (rand() % (max_y - size_room_y - 2));
        int room_x = 1 + (rand() % (max_x - size_room_x - 2));

        //generating rooms
        for(int i = 0; i < size_room_y; i++) {
            for(int j = 0; j < size_room_x; j++) {
                if(room_y + i < max_y && room_x + j < max_x) {
                    if(i == 0 || i == size_room_y-1) {
                        map[room_y + i][room_x + j] = '_';
                    }
                    else if(j == 0 || j == size_room_x-1) {
                        map[room_y + i][room_x + j] = '|';
                    }
                    else {
                        map[room_y + i][room_x + j] = '.';
                    }
                }
            }
        }
        num++;
    }


    clear();
    for(int i = 0; i < max_y; i++) {
        for(int j = 0; j < max_x; j++) {
            if(map[i][j] != ' ') {
                mvaddch(i, j, map[i][j]);
            }
        }
    }
    refresh();

    int x = 0, y = 0;
    int player_placed = 0;
    while(!player_placed) {
        y = rand() % max_y  + 1;
        x = rand() % max_x  + 1;
        if(map[y][x] == '.') {
            player_placed = 1;
        }
    }

    int c;
    do {
        for(int i = 0; i < max_y; i++) {
            for(int j = 0; j < max_x; j++) {
                if(map[i][j] != ' ') {
                    mvaddch(i, j, map[i][j]);
                }
            }
        }

        int new_y = y;
        int new_x = x;

        if (c == KEY_UP && y > 0) new_y--;
        if (c == KEY_DOWN && y < max_y-1) new_y++;
        if (c == KEY_RIGHT && x < max_x-1) new_x++;
        if (c == KEY_LEFT && x > 0) new_x--;

        if(map[new_y][new_x] == '.') {
            y = new_y;
            x = new_x;
        }

        draw_character(y, x, current_user->game_setting.player_color);
        refresh();

    } while ((c = getch()) != 27);

    endwin();
}
