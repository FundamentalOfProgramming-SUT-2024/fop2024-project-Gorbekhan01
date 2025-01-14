#include <ncurses.h>
#include <locale.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <wchar.h>
#include <time.h>


void draw_black_gold(int y, int x) {
    wchar_t gold = 0x0001F312;
    mvprintw(y, x, "%lc", gold);
}

void draw_character(int y, int x, int color) {
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_CYAN, COLOR_BLACK);
    init_pair(3, COLOR_GREEN, COLOR_BLACK);
    if(color==0){
        attron(COLOR_PAIR(1));
        mvprintw(y , x, "◍");
        attroff(COLOR_PAIR(1));
    }
    else if(color==1){
        attron(COLOR_PAIR(2));
        mvprintw(y , x, "◍");
        attroff(COLOR_PAIR(2));
    }
    else if(color==2){
        attron(COLOR_PAIR(3));
        mvprintw(y , x, "◍");
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
int easy_game(struct user *current_user);
int food_bar(int* food1, int* health , int* food);
int lose();


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
    int repeat=0;
    while(repeat==0) {
        if (choice == 0) {
            leaderboard(&current_user);
            int level = gamesetting(&current_user);
            if (current_user.game_setting.game_level == 0) {
                int result_game = easy_game(&current_user);
                if (result_game == 0) {
                    if(lose()==1){
                        repeat = 0;
                    }
                    else {
                        repeat =1;
                    }

                }
            }
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
        mvprintw(center_y-3,center_y , "Please choose one of these options to start the game!");
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
    mvprintw(center_y + 18, center_x-20, "❗if you forget your password enter < forget > in password section!");

    mvprintw(center_y + 4, center_x, "◦ Username: ");
    mvprintw(center_y + 6, center_x, "◦ Password: ");

    refresh();
    int count=0;

    char password[50];
    int len = 0;
    char temp_username[50];
    char temp_password[50];
    char temp_email[50];
    int temp = 0;
    char tempi[100];

    while (count ==0) {
        echo();
        move(center_y + 4, center_x + 12);
        curs_set(1);
        clrtoeol();
        getstr(username);
        FILE *fptr = fopen("users.txt", "r");
        if (fptr == NULL) {
            FILE *fptr = fopen("users.txt", "w");
            refresh();
        }
        password[50];
        len = 0;
        temp_username[50];
        temp_password[50];
        temp_email[50];
        temp = 0;
        tempi[100];
        rewind(fptr);
        while (fgets(tempi, 100, fptr) != NULL) {
            sscanf(tempi, "%s %s %s", temp_username, temp_password, temp_email);
            if (strcmp(temp_username, username) == 0) {
                count++;
                break;
            }
        }
        if(count ==0){
            mvprintw(center_y + 20, center_x-20, "entered username is not registered");
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
    mvprintw(center_y + 13, center_x+9, "❗Enter < random > in password section to get random passwords !!");
    fclose(fptr);

    char password[50];
    int len = 0;
    while (len < 7) {
        clrtoeol();
        move(center_y + 6, center_x + 12);
        getstr(password);
        len = strlen(password);
        if (len < 7 & strcmp("random",password)!=0) {
            mvprintw(center_y + 12, center_x+9, "Password must be at least 7 letters!");
            refresh();
        }
        else if(strcmp("random",password)==0){
            clrtoeol();
            int random_num = 7 + (rand() % 30);
            char chars[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789*&@#$%";
            int lenii = strlen(chars);
            char temp_pass[1000];
            for(int i=0;i<random_num;i++){
                int temp = rand() % lenii;
                temp_pass[i]=chars[temp];
            }
            mvprintw(center_y + 12, center_x+9, "your random password is <  %s  > ",temp_pass);
        }
    }
    mvprintw(center_y + 12, center_x+9, ". . .                                     ");
    mvprintw(center_y + 13, center_x+9, "                                                            ");

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


int food_bar(int* food1,int* health,int* food){
    initscr();
    keypad(stdscr, TRUE);
    refresh();
    noecho();
    cbreak();
    clear();
    start_color();
    curs_set(0);
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);
    int center_y = max_y / 2 - 7;
    int center_x = max_x / 2 - 15;
    int selected =0;
    int key;
    init_pair(1,COLOR_YELLOW,COLOR_RED);
    while(1) {
        mvprintw(center_y-12,22,"** S T A T U S ***************************");
        mvprintw(center_y-10,22,"health: ");
        refresh();
        for(int i =0;i<=*health;i++){
            mvprintw(center_y-10,30+i,"♥");
            mvprintw(center_y-10,30+*health," ");
        }

        //food
        mvprintw(center_y-10,44,"food: ");

        for(int i =0;i<=*food;i++){
            mvprintw(center_y-10,50+i,"+");
            mvprintw(center_y-10,50+*food," ");
        }
        mvprintw(center_y-8,22,"******************************************");

        refresh();
        mvprintw(center_y, center_x, "----- FOODS BASKET -----",*food1);
        if (selected == 0) {
            mvprintw(center_y+5, center_x+5, "> Food 1 = [ %d ]",*food1);
            attron(COLOR_PAIR(1));
            mvprintw(center_y+5, center_x+2, "F");
            attroff(COLOR_PAIR(1));

        } else {
            mvprintw(center_y+5, center_x+5, "Food 1 = [ %d ]",*food1);
            attron(COLOR_PAIR(1));
            mvprintw(center_y+5, center_x+2, "F");
            attroff(COLOR_PAIR(1));
        }
        mvprintw(center_y+10, center_x, "------- --------- -------",*food1);

        mvprintw(center_y+16, center_x, "-- Use KEY UP & KEY DOWN to choose food --");
        mvprintw(center_y+18, center_x, "-- Press ENTER to eat! --");
        mvprintw(center_y+20, center_x, "-- Press Q to exit --");
        refresh();
        key = getch();


        switch(key) {
            case 'q':
                clear();
                return 3;
            case KEY_UP:
                selected--;
                if(selected < 0) {
                    selected = 0;
                }
                break;
            case KEY_DOWN:
                selected++;
                if(selected > 0) {
                    selected = 0;
                }
                break;
            case '\n':
                refresh();
                if(selected == 0) {

                    if(*food1<=0){
                        *food1=0;
                    }
                    else{
                        *health = 10;
                        *food = 10;
                        *food1=*food1-1;
                    }

                }

                refresh();
                getch();
                break;
        }
    }

}

int easy_game(struct user *current_user) {
    setlocale(LC_ALL, "");
    initscr();
    keypad(stdscr, TRUE);
    noecho();
    curs_set(0);
    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);
    char map[max_y][max_x];

    for(int i = 0; i < max_y; i++) {
        for(int j = 0; j < max_x; j++) {
            map[i][j] = ' ';
        }
    }

    //number of rooms randomly
    srand(time(NULL));
    int number_of_rooms = 6 + (rand() % 2);
    int num = 0;

    typedef struct {
        int center_x;
        int center_y;
    } RoomCenter;
    RoomCenter centers[number_of_rooms];

    //generating rooms
    while (num < number_of_rooms) {
        int ok = 0;
        int size_room_y, size_room_x, room_y, room_x;

        while (ok == 0) {
            size_room_y = 8 + (rand() % 6);
            size_room_x = 8 + (rand() % 6);
            room_y = 3 + (rand() % (max_y - size_room_y - 8));
            room_x = 3 + (rand() % (max_x - size_room_x - 8));

            int padding = 5;
            int overlap = 0;

            for (int i = -padding; i < size_room_y + padding && !overlap; i++) {
                for (int j = -padding; j < size_room_x + padding && !overlap; j++) {
                    if (room_y + i >= 0 && room_y + i < max_y &&
                        room_x + j >= 0 && room_x + j < max_x) {
                        if (map[room_y + i][room_x + j] != ' ') {
                            overlap = 1;
                        }
                    }
                }
            }

            if (overlap == 0) {
                ok++;
            }
        }
        for (int i = 0; i < size_room_y; i++) {
                for (int j = 0; j < size_room_x; j++) {
                    if (room_y + i < max_y && room_x + j < max_x) {
                        if (i == 0 || i == size_room_y - 1) {
                            map[room_y + i][room_x + j] = '_';
                        } else if (j == 0 || j == size_room_x - 1) {
                            map[room_y + i][room_x + j] = '|';
                        } else {
                            map[room_y + i][room_x + j] = '.';
                        }
                    }
                }
            }

        //corridors
        centers[num].center_y = room_y + (size_room_y / 2);
        centers[num].center_x = room_x + (size_room_x / 2);

        if (num > 0) {
            int y1 = centers[num].center_y;
            int x1 = centers[num].center_x;
            int y2 = centers[num-1].center_y;
            int x2 = centers[num-1].center_x;

            int current_x = x1;
            while (current_x != x2) {
                if (current_x < x2) current_x++;
                else current_x--;

                if (current_x <= 0 || current_x >= max_x - 1) {
                    continue;
                }

                if (map[y1][current_x] == '|') {
                    char left = map[y1][current_x-1];
                    char right = map[y1][current_x+1];

                    if ((left == '.' && right == ' ') ||
                        (left == ' ' && right == '.') ||
                        (left == '#' && right == '.') ||
                        (left == '.' && right == '#')) {
                        map[y1][current_x] = '+';
                    }
                    else if(left == '_' && right == '#'){
                        map[y1][current_x] = '+';
                        map[y1][current_x-1] = '+';
                    }
                    else if(left == '#' && right == '+'){
                        map[y1][current_x] = '+';
                        map[y1][current_x+1] ='+';
                    }
                }

                else if (map[y1][current_x] == '_') {
                    char left = map[y1][current_x - 1];
                    char right = map[y1][current_x + 1];

                    if ((left == '_' && right == '#') ||
                        (left == '#' && right == '_') ) {
                        map[y1][current_x] = '+';
                        map[y1][current_x+1] = '+';
                        map[y1][current_x-1] = '+';
                    }
                }

                else if (map[y1][current_x] == ' ') {
                    map[y1][current_x] = '#';
                }
            }

            int current_y = y1;
            while (current_y != y2) {
                if (current_y < y2) current_y++;
                else current_y--;

                if (current_y <= 0 || current_y >= max_y - 1) {
                    continue;
                }

                if (map[current_y][x2] == '_') {
                    char up = map[current_y-1][x2];
                    char down = map[current_y+1][x2];

                    if ((down == ' ' && up == '.') ||
                        (down == '.' && up == ' ') ||
                        (down == '.' && up == '#') ||
                        (down == '#' && up == '.')) {
                        map[current_y][x2] = '+';
                    }
                    else if(down == '#' && up == '|'){
                        map[current_y][x2] = '+';
                        map[current_y-1][x2] = '+';
                        map[current_y+1][x2] = '+';
                    }
                    else if(down == '|' && up == '#'){
                        map[current_y][x2] = '+';
                        map[current_y+1][x2] = '+';
                        map[current_y-1][x2] = '+';
                    }

                }
                else if (map[current_y][x2] == ' ') {
                    map[current_y][x2] = '#';
                }
            }
        }


        num++;
    }

    //pillars
    int num_pillars= 6+ (rand() % 4);
    int np=0 ,py ,px;
    while(np<num_pillars){
        py = rand() % max_y  + 1;
        px = rand() % max_x  + 1;
        if(map[py][px]=='.'){
            map[py][px]='O';
            np++;
        }
    }
    //traps
    int num_traps= 3+ (rand() % 4);
    int nt=0 ,ty ,tx;
    while(nt<num_traps){
        ty = rand() % max_y  + 1;
        tx = rand() % max_x  + 1;
        if(map[ty][tx]=='.'){
            map[ty][tx]='T';
            nt++;
        }
    }

    //foods
    int num_foods= 10+ (rand() % 6);
    int nf=0 ,fy ,fx;
    while(nf<num_foods){
        fy = rand() % max_y  + 1;
        fx = rand() % max_x  + 1;
        if(map[fy][fx]=='.'){
            map[fy][fx]='F';
            nf++;
        }
    }

    //yellow golds
    int num_ygolds= 6 + (rand() % 4);
    int nyg=0 ,gy ,gx;
    while(nyg<num_ygolds){
        gy = rand() % max_y  + 1;
        gx = rand() % max_x  + 1;
        if(map[gy][gx]=='.'){
            map[gy][gx]='$';
            nyg++;
        }
    }

    //black golds
    int num_bgolds= 4 + (rand() % 1);
    int nbg=0 ,by ,bx;
    while(nbg<num_bgolds){
        by = rand() % max_y  + 1;
        bx = rand() % max_x  + 1;
        if(map[by][bx]=='.'){
            map[by][bx]='@';
            nbg++;
        }
    }

    //place player randomly on map
    int x = 0, y = 0;
    int player_placed = 0;
    while(!player_placed) {
        y = rand() % max_y  + 1;
        x = rand() % max_x  + 1;
        if(map[y][x] == '.') {
            player_placed = 1;
        }
    }

    clear();

    init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(6, COLOR_YELLOW, COLOR_BLACK);
    init_pair(7, COLOR_BLACK, COLOR_WHITE);
    init_pair(8, COLOR_YELLOW, COLOR_RED);
    ////////////////////
    int total_yellow_gold=0;
    int total_black_gold=0;
    /////////////////////

    int food=10;
    int food1=0;
    int health=10;
 // printing map (player movement -- map)
    int c;
    int counter=0;
    do {
        for(int i = 0; i < max_y; i++) {
            for(int j = 0; j < max_x; j++) {
                if(map[i][j] != ' ') {
                    if(map[i][j]=='|'){
                        attron(COLOR_PAIR(5));
                        mvaddch(i, j, map[i][j]);
                        attroff(COLOR_PAIR(5));
                    }
                    else if(map[i][j]=='O'){
                        attron(COLOR_PAIR(5));
                        mvaddch(i, j, map[i][j]);
                        attroff(COLOR_PAIR(5));
                    }
                    else if(map[i][j]=='$'){
                        attron(COLOR_PAIR(6));
                        mvaddch(i, j, map[i][j]);
                        attroff(COLOR_PAIR(6));
                    }
                    else if(map[i][j]=='@'){
                        attron(COLOR_PAIR(7));
                        mvaddch(i, j, map[i][j]);
                        attroff(COLOR_PAIR(7));
                    }
                    else if(map[i][j]=='F'){
                        attron(COLOR_PAIR(8));
                        mvaddch(i, j, map[i][j]);
                        attroff(COLOR_PAIR(8));
                    }
                    else if(map[i][j]=='T'){
                        mvaddch(i, j, '.');
                    }
                    else if(map[i][j]=='^'){
                        mvaddch(i, j, map[i][j]);
                    }
                    else {
                        mvaddch(i, j, map[i][j]);
                    }

                }
            }
        }

        int new_y = y;
        int new_x = x;

        if(c ==101) { ///food window
            clear();
            int p= food_bar(&food1, &health, &food);
            if(p==3){
                continue;
            }
            c = getch();
        }
        if (c == KEY_UP && y > 0) new_y--;
        if (c == KEY_DOWN && y < max_y - 1) new_y++;
        if (c == KEY_RIGHT && x < max_x - 1) new_x++;
        if (c == KEY_LEFT && x > 0) new_x--;

        if(map[new_y][new_x] == '.' || map[new_y][new_x] == '$'|| map[new_y][new_x] == '@' || map[new_y][new_x] == '+' ||
           map[new_y][new_x] == '#'  || map[new_y][new_x] == 'F' || map[new_y][new_x]=='T' || map[new_y][new_x]=='^') {
            if(map[new_y][new_x] == '$'){
                int temp = 2 + (rand() % 3 );
                mvprintw(2,3,"You received %d GOLDS !",temp);
                total_yellow_gold+= temp;
            }
            if(map[new_y][new_x] == '@'){
                int temp = 6 + (rand() % 4 );
                mvprintw(2,3,"You received %d GOLDS !",temp);
                total_black_gold+= temp;
            }
            if(map[new_y][new_x] == 'F'){
                int temp = 1;
                mvprintw(2,3,"You received %d FOOD !",temp);
                food1+= 1;
               if(food1>5){
                   food1=5;
               }
            }

            if(map[new_y][new_x] == 'T'){
                int temp = 1;
                mvprintw(2,3,"You stepped on a TRAP !",temp);
                health=health-2;
                refresh();
                map[new_y][new_x]='^';
            }


            y = new_y;
            x = new_x;
        }

        if(map[y][x]!='+' && map[y][x]!='#'&&map[y][x]!='^'){
            map[y][x]='.';
        }
        mvprintw(max_y-2,max_x-10,"GOLD: %d",total_black_gold+total_yellow_gold);
        draw_character(y, x, current_user->game_setting.player_color);

        if(counter==20){
            health--;
            counter=0;
        }
        if(counter==15){
            food--;
        }
        if(health==0){
            return 0;
        }

        //health
        mvprintw(max_y-2,2,"health: ");
        refresh();
        for(int i =0;i<=health;i++){
            mvprintw(max_y-2,10+i,"♥");
            mvprintw(max_y-2,10+health," ");
            for(int j=0;j<10-i;j++){
                mvprintw(max_y-2,10+health+j," ");
            }
        }

        //food
        mvprintw(max_y-2,24,"food: ");

        for(int i =0;i<=food;i++){
            mvprintw(max_y-2,30+i,"+");
            mvprintw(max_y-2,30+food," ");
        }

        counter++;

        refresh();

    } while ((c = getch()) != 27);

    endwin();
}

int lose(){
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
        mvprintw(center_y, center_x+4, " Y O U  L O S E! ");
        attroff(COLOR_PAIR(1) | A_BOLD | A_BLINK);
        mvprintw(center_y + 2, center_x-4, "══════════════════════════════");
        attroff(COLOR_PAIR(1) | A_BOLD);
        mvprintw(center_y+20,center_x , selected == 0 ? "[ start again ]" : "start again");
        mvprintw(center_y+22, center_x+3, selected == 1 ? "[ exit ]" : "exit");
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
                    return 1;
                }
                else if(selected == 1) {
                    return 0;
                }
                refresh();
                getch();
                break;
        }
    }
    refresh();
}



