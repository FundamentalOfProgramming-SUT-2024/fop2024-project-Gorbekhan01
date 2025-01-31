#include <ncurses.h>
#include <locale.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <wchar.h>
#include <time.h>
#include <math.h>

void move_deamon(int y, int x ){
    init_pair(1, COLOR_MAGENTA,COLOR_BLACK);
    attron(1);
    mvprintw(y , x, "D");
    attroff(1);

}
void move_fire_breathing_monster(int y, int x ){
    init_pair(1, COLOR_MAGENTA,COLOR_BLACK);
    attron(1);
    mvprintw(y , x, "F");
    attroff(1);
}
void move_snake(int y, int x ){
    init_pair(1, COLOR_MAGENTA,COLOR_BLACK);
    attron(1);
    mvprintw(y , x, "S");
    attroff(1);
}
void move_giant(int y, int x ){
    init_pair(1, COLOR_MAGENTA,COLOR_BLACK);
    attron(1);
    mvprintw(y , x, "G");
    attroff(1);
}
void move_undeed(int y, int x ){
    init_pair(1, COLOR_MAGENTA,COLOR_BLACK);
    attron(1);
    mvprintw(y , x, "U");
    attroff(1);
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

typedef struct weapons{
    int Mace;
    int Dagger;
    int Magic_Wand;
    int Normal_Arrow;
    int Sword;
    int Dagger_count;
    int Magic_Wand_count;
    int Normal_Arrow_count;
    int Sword_count;
    int in_use_weapon;
}weapons;

typedef struct spell{
    int health_spell;
    int health_spell_counter;
    int speed_spell;
    int speed_spell_counter;
    int damage_spell;
    int damage_spell_counter;

}spells;

typedef struct game{
   char username[100];
   int music;
   int game_level;
   int player_color;
   int snake_chasing;
}game;

typedef struct user{
    char username[100];
    int total_score;
    int total_gold;
    int total_finished_games;
    char joined_date[100];
    struct game game_setting;
    int rank;
    int food;
    int health;
    int food1;
    int new_golds;
    struct weapons weapons;
    struct spell spells;
}user;



void opening();
int choosing_user(char *username);
int new_user(char *username);
int old_user(char *username);
int game_menu(char *username);
int leaderboard(struct user *current_user );
int gamesetting(struct user *current_user);
int help();
int code(char password[]);
int game_f1(struct user *current_user, int level);
int game_f2(struct user *current_user , int level);
int game_f3(struct user *current_user , int level);
int game_f4(struct user *current_user , int level);
int treasure_room(struct user *current_user, int level);
int food_bar(int* food1, int* health , int* food);
int weapon(struct user *current_user , int in_use);
int potion(struct user *current_user);
int pre_leaderboard(struct user *current_user);
int lost(struct user *current_user);
int victory(struct user *current_user);


int main() {

    start_color();
    setlocale(LC_ALL, "");
    initscr();
    noecho();
    cbreak();
    struct user current_user;
    opening();
    char username[50] = {};
    int login_repeat=0;
    choosing_user(username);
    strcpy(current_user.username,username);
    int choice = game_menu(username);
    int repeat=0;
    while(repeat==0) {
        if (choice == 0) {
            leaderboard(&current_user);
            int level = gamesetting(&current_user);
            help();
            int result_game = game_f1(&current_user,current_user.game_setting.game_level);
                if (result_game == 0) {
                    if(lost(&current_user)==1){
                        repeat = 0;
                    }
                    else {
                        repeat =1;
                        return 0;
                    }

                }
                else if(result_game==1){
                    victory(&current_user);
                    leaderboard(&current_user);
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
    mvprintw(center_y + 13, center_x + 3, "###");
    sleep(1);
    refresh();
    mvprintw(center_y + 13, center_x + 3, "############");
    sleep(1);
    refresh();
    mvprintw(center_y + 13, center_x + 3, "########################");


    refresh();
    sleep(1);
    clear();
    refresh();
}

int choosing_user(char *username){
    initscr();
    keypad(stdscr, TRUE);
    curs_set(0);
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_MAGENTA, COLOR_BLACK);
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
        attron(COLOR_PAIR(2));
        mvprintw(center_y+8,center_y , "To avoid possible problems, the size of your terminal window should be at least 50 x 170");
        attroff(COLOR_PAIR(2));


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
    srand(time(NULL));
    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);
    int center_y = max_y / 2 - 7;
    int center_x = max_x / 2 - 15;

    attron(COLOR_PAIR(1) | A_BOLD | A_BLINK);
    mvprintw(center_y, center_x, "                      ");
    mvprintw(center_y + 1, center_x, " P l a y e r  i n f o ");
    mvprintw(center_y + 2, center_x, "                      ");
    attroff(COLOR_PAIR(1) | A_BOLD | A_BLINK);

    mvprintw(center_y + 11, center_x - 1, "\\    /\\");
    mvprintw(center_y + 12, center_x - 1, " )  ( ') ");
    mvprintw(center_y + 13, center_x - 1, "(  /  )");
    mvprintw(center_y + 14, center_x - 1, " \\\\(__)|");

    mvprintw(center_y + 4, center_x, "◦ Username: ");
    mvprintw(center_y + 6, center_x, "◦ Password: ");
    mvprintw(center_y + 8, center_x, "◦ Email: ");

    refresh();

    echo();
    int temp = 0;
    FILE *fptr = fopen("users.txt", "r");
    if (fptr == NULL) {
        FILE *fptr = fopen("users.txt", "w");
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
                mvprintw(center_y + 12, center_x + 9, "This username is taken!                         ");
                refresh();
                move(center_y + 4, center_x + 12);
                clrtoeol();
                temp++;
                break;
            }
        }
        refresh();

        if (temp == 0) {
            break;
        }
    }
    mvprintw(center_y + 12, center_x + 9, ". . .                                                                                        ");
    mvprintw(center_y + 14, center_x + 9, "** Enter < random > in password section to get random passwords !!");
    fclose(fptr);

    char password[50];
    int len = 0;
    while (len < 7) {
        clrtoeol();
        move(center_y + 6, center_x + 12);
        getstr(password);
        len = strlen(password);
        if (len < 7 & strcmp("random", password) != 0) {
            mvprintw(center_y + 12, center_x + 9, "Password must be at least 7 letters!              ");
            move(center_y + 6, center_x + 12);
            clrtoeol();
            refresh();
        } else if (strcmp("random", password) == 0) {
            move(center_y + 6, center_x + 12);
            clrtoeol();
            int random_num = 7 + (rand() % 14);
            char chars[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789*&@#$%";
            int lenii = strlen(chars);
            char temp_pass[100];
            for (int i = 0; i < random_num; i++) {
                int temp =  rand() % lenii;
                temp_pass[i] = chars[temp];
            }
            mvprintw(center_y + 14, center_x + 9, "your random password is <  %s  >                                                              ", temp_pass);
        }
    }
    mvprintw(center_y + 12, center_x + 9, ". . .                                                                                         ");
    mvprintw(center_y + 13, center_x + 9, "                                                                                            ");

    char email[50];
    int t = 0;
    while (t != 1) {
        move(center_y + 8, center_x + 12);
        clrtoeol();
        getstr(email);
        int len= strlen(email);
        if (strstr(email, "@") != 0 && strstr(email, ".") != 0 ) {
            if(strstr(email,"@") + 1 < strstr(email,".") && len >=strstr(email,".")+1 ){
                t = 1;
            }
            else{
                mvprintw(center_y + 12, center_x + 9, "Email is not valid!");
                t = 0;
            }
        } else {
            mvprintw(center_y + 12, center_x + 9, "Email is not valid!");
            t = 0;
        }
    }
    mvprintw(center_y + 12, center_x + 9, "                    ");
    fptr = fopen("users.txt", "a");
    fprintf(fptr, "%s %s %s\n", username, password, email);
    fclose(fptr);
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
        curs_set(0);
        attron(COLOR_PAIR(1) | A_BOLD);
        mvprintw(center_y - 2, center_x-4, "══════════════════════════════");
        attron(COLOR_PAIR(1) | A_BOLD | A_BLINK);
        mvprintw(center_y, center_x, "    WELCOME  %s ! ", username);
        attroff(COLOR_PAIR(1) | A_BOLD | A_BLINK);
        mvprintw(center_y + 2, center_x-4, "══════════════════════════════");
        attroff(COLOR_PAIR(1) | A_BOLD);
        mvprintw(center_y+20,center_x , selected == 0 ? "[ start a new game ]" : "  start a new game  ");
        refresh();
        key = getch();

        switch(key) {
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
                clear();
                if(selected == 0) {
                    return 0;
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
    int center_y = max_y / 2 - 10;
    int center_x = max_x / 2 - 40;

    const int COL_WIDTH = 15;
    mvprintw(center_y, center_x + 24, "=== LEADERBOARD ===");
    mvprintw(center_y + 2, center_x - 2, "%-10s %-15s %-15s %-15s %-15s %-20s",
             "Rank", "Username", "Score", "Gold", "Finished Games", "joined date");
    mvprintw(center_y + 3, center_x - 2, "-----------------------------------------------------------------------------------");

    FILE* fptr = fopen("leaderboard.txt", "r");
    if (fptr == NULL) {
        fptr = fopen("leaderboard.txt", "w");
        if (fptr == NULL) {
            mvprintw(center_y + 5, center_x, "Error creating leaderboard file!");
            refresh();
            getch();
            return 0;
        }
        fclose(fptr);

        time_t current_time;
        struct tm* time_info;
        char join_date[20];

        time(&current_time);
        time_info = localtime(&current_time);
        strftime(join_date, sizeof(join_date), "%Y-%m-%d/%H:%M", time_info);

        current_user->rank = 1;
        current_user->total_score = 0;
        current_user->total_gold = 0;
        current_user->total_finished_games = 0;
        strcpy(current_user->joined_date, join_date);

        FILE* fptr_write = fopen("leaderboard.txt", "w");
        fprintf(fptr_write, "%d %s %d %d %d %s\n",
                current_user->rank,
                current_user->username,
                current_user->total_score,
                current_user->total_gold,
                current_user->total_finished_games,
                current_user->joined_date);
        fclose(fptr_write);

        attron(A_BOLD | A_BLINK);
        mvprintw(center_y + 4, center_x -2, "%-10d %-15s %-15d %-15d %-15d %-20s",
                 current_user->rank,
                 current_user->username,
                 current_user->total_score,
                 current_user->total_gold,
                 current_user->total_finished_games,
                 current_user->joined_date);
        attroff(A_BOLD | A_BLINK);

        attron(A_BOLD | COLOR_PAIR(2));
        mvprintw(center_y + 30, center_x, "New player added to leaderboard!");
        attroff(A_BOLD | COLOR_PAIR(2));

        mvprintw(center_y + 30, center_x+ 8, "[ Press enter to start the game ]");
        refresh();
        getch();
        return 0;
    }

    init_pair(1, COLOR_WHITE, COLOR_BLACK);

    int found = 0;
    int rank;
    char username1[100];
    int total_score;
    int total_gold;
    int total_finished_games;
    char total_time[100];
    char tempi[100];
    int k = 0;
    rewind(fptr);

    while (fgets(tempi, 100, fptr) != NULL) {
        sscanf(tempi, "%d %s %d %d %d %s", &rank, username1, &total_score, &total_gold, &total_finished_games, total_time);
        if(rank==1){
            mvprintw(center_y + 4 + k , center_x-5, "🥇");
        }
        if(rank==2){
            mvprintw(center_y + 4 + k , center_x-5, "🥈");
        }
        if(rank==3){
            mvprintw(center_y + 4 + k , center_x-5, "🥉");
        }
        if (strcmp(username1, current_user->username) == 0) {
            found = 1;
            current_user->total_score = total_score;
            current_user->total_gold = total_gold;
            strcpy(current_user->joined_date, total_time);
            current_user->total_finished_games = total_finished_games;
            attron(A_BOLD | A_BLINK);
            mvprintw(center_y + 4 + k, center_x -2 , "%-10d %-15s %-15d %-15d %-15d %-20s",
                     rank,
                     current_user->username,
                     current_user->total_score,
                     current_user->total_gold,
                     current_user->total_finished_games,
                     current_user->joined_date);
            attroff(A_BOLD | A_BLINK);
        } else {
            mvprintw(center_y + 4 + k, center_x -2, "%-10d %-15s %-15d %-15d %-15d %-20s",
                     rank,
                     username1,
                     total_score,
                     total_gold,
                     total_finished_games,
                     total_time);
        }
        k++;
    }

    if (!found) {
        fclose(fptr);
        time_t current_time;
        struct tm* time_info;
        char join_date[20];

        time(&current_time);
        time_info = localtime(&current_time);
        strftime(join_date, sizeof(join_date), "%Y-%m-%d/%H:%M", time_info);

        fptr = fopen("leaderboard.txt", "a");
        current_user->rank = k+1;
        current_user->total_score = 0;
        current_user->total_gold = 0;
        current_user->total_finished_games = 0;
        strcpy(current_user->joined_date, join_date);
        fprintf(fptr, "%d %s %d %d %d %s\n",
                current_user->rank,
                current_user->username,
                current_user->total_score,
                current_user->total_gold,
                current_user->total_finished_games,
                current_user->joined_date);

        attron(A_BOLD | A_BLINK);
        mvprintw(center_y + 4 + k, center_x-2, "%-10d %-15s %-15d %-15d %-15d %-20s",
                 current_user->rank,
                 current_user->username,
                 current_user->total_score,
                 current_user->total_gold,
                 current_user->total_finished_games,
                 current_user->joined_date);
        attroff(A_BOLD | A_BLINK);

        attron(A_BOLD | COLOR_PAIR(2));
        mvprintw(center_y + 30, center_x, "New player added to leaderboard!");
        attroff(A_BOLD | COLOR_PAIR(2));
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


            mvprintw(center_y - 9, center_x - 4  , "╔══════════════════════════════╗");
            mvprintw(center_y - 8, center_x - 4, "║   G A M E  S E T T I N G S   ║");
            mvprintw(center_y - 7, center_x - 4, "╚══════════════════════════════╝");

            attron(A_BOLD);
            attron(A_STANDOUT);
            mvprintw(center_y - 2, center_x , " Choose the game level");
            attroff(A_STANDOUT);
            attroff(A_BOLD);

            attron(A_BOLD);
            attron(A_STANDOUT);
            mvprintw(center_y + 8, center_x - 3 , " Choose your character's color");
            attroff(A_STANDOUT);
            attroff(A_BOLD);


            int level_start_x = center_x ;
            for (int i = 0; i < n_choices; i++) {
                if (current_menu == 0 && i == current_choice) {
                    attron(A_REVERSE);
                    mvprintw(center_y + 1, level_start_x + i * 9 , "%s", choices[i]);
                    attroff(A_REVERSE);
                } else {
                    mvprintw(center_y + 1, level_start_x + i * 9 , "%s", choices[i]);
                }
            }


            int color_start_x = center_x ;
            for (int i = 0; i < n_choices+1; i++) {
                if (current_menu == 1 && i == color_choice) {
                    attron(A_REVERSE);
                    mvprintw(center_y + 11, color_start_x + i * 9 - 5, "%s", colors[i]);
                    attroff(A_REVERSE);
                } else {
                    mvprintw(center_y + 11, color_start_x + i * 9 - 5, "%s", colors[i]);
                }
            }

            attron(A_BOLD);
            attron(A_STANDOUT);
            mvprintw(center_y + 20, center_x - 4 , "[ Press Enter to start the game ]");
            attroff(A_STANDOUT);
            mvprintw(center_y + 24 , center_x - 11 , "use -> and <- to move between options and then press enter");

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

int help(){

    initscr();
    keypad(stdscr, TRUE);
    refresh();
    noecho();
    curs_set(0);
    cbreak();
    clear();
    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);
    int center_y = max_y / 2 - 20;
    int center_x = max_x / 2 - 40;
    int temp_x;
    int temo_y;
    mvprintw(center_y++, center_x, " _                   ");
    mvprintw(center_y++, center_x, "| | | | ___| |_ __   ");
    mvprintw(center_y++, center_x, "| |_| |/ _ \\ | '_ \\ ");
    mvprintw(center_y++, center_x, "|  _  |  __/ | |_) | ");
    mvprintw(center_y++, center_x, "|_| |_|\\___|_| .__/   ");
    mvprintw(center_y++, center_x, "              |_|     ");
    center_y++;
    mvprintw(center_y++, center_x, ">>> Please read carefully! <<<");
    center_y+=3;
    temo_y=center_y; temp_x=center_x;
    mvprintw(center_y++, center_x, "< player movement >");
    center_y++;
    mvprintw(center_y++, center_x, "┌───┐");
    mvprintw(center_y++, center_x, "│ ↑ │");
    mvprintw(center_y++, center_x, "├───┼───┬───┐");
    mvprintw(center_y++, center_x, "│ ← │ ↓ │ → │");
    mvprintw(center_y++, center_x, "└───┴───┴───┘");
    center_y++;
    mvprintw(center_y++, center_x, "Right arrow →  to go right");
    mvprintw(center_y++, center_x, "Left arrow  ←  to go left");
    mvprintw(center_y++, center_x, "Up arrow    ↑  to go up");
    mvprintw(center_y++, center_x, "Down arrow  ↓  to go down");
    center_y+=3;
    mvprintw(center_y++, center_x, "< Weapons >");
    center_y++;
    mvprintw(center_y++, center_x, "[i] to weapons menu");
    center_y++;
    mvprintw(center_y++, center_x, "[p] to attack with short range weapons");
    center_y++;
    mvprintw(center_y++, center_x, "Long range weapons");
    mvprintw(center_y++, center_x, "[p] + [w] -> shoot upward");
    mvprintw(center_y++, center_x, "    + [a] -> shoot leftward");
    mvprintw(center_y++, center_x, "    + [s] -> shoot downward");
    mvprintw(center_y++, center_x, "    + [d] -> shoot rightward");
    center_y++;
    temp_x += 40;
    mvprintw(temo_y++, temp_x, "< Food >");
    temo_y++;
    mvprintw(temo_y++, temp_x, "[e] to open the food menu");
    temo_y+=3;
    mvprintw(temo_y++, temp_x, "< spell >");
    temo_y++;
    mvprintw(temo_y++, temp_x, "[o] to open the spell menu");
    temo_y+=3;
    center_y+=20;
    mvprintw(temo_y++, temp_x, "< help >");
    temo_y++;
    mvprintw(temo_y++, temp_x, "[h] access to help menu");
    mvprintw(center_y, center_x, "Press any key to start the game.");


    refresh();
    getch();
    getch();
    clear();
    endwin();

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
        mvprintw(center_y-12,22,"** S T A T U S ************************************");
        mvprintw(center_y-10,22,"health: ");
        refresh();
        for(int i =0;i<=*health;i++){
            mvprintw(center_y-10,30+i,"♥");
            mvprintw(center_y-10,30+*health," ");
            mvprintw(center_y-10,42,"%d%c",*health*10,'%');
        }

        //food
        mvprintw(center_y-10,50,"food: ");

        for(int i =0;i<=*food;i++){
            mvprintw(center_y-10,56+i,"+");
            mvprintw(center_y-10,56+*food," ");
            mvprintw(center_y-10,68,"%d%c",*food*10,'%');
        }
        mvprintw(center_y-8,22,"***************************************************");

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

        mvprintw(center_y+16, center_x, "-- Use KEY UP & KEY DOWN to move between options --");
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
                        *food = 10;
                        *food1=*food1-1;
                    }

                }

                refresh();
                break;
        }
        getch();
    }

}

int weapon(struct user *current_user , int in_use) {
    initscr();
    keypad(stdscr, TRUE);
    refresh();
    noecho();
    cbreak();
    clear();
    start_color();
    curs_set(0);
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(9, COLOR_CYAN,COLOR_BLACK);

    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);
    int center_y = max_y / 2 - 7;
    int center_x = max_x / 2 - 15;

    int total_weapons = 0;
    if(current_user->weapons.Sword==1) total_weapons++;
    if(current_user->weapons.Dagger==1) total_weapons++;
    if(current_user->weapons.Normal_Arrow==1) total_weapons++;
    if(current_user->weapons.Mace==1) total_weapons++;
    if(current_user->weapons.Magic_Wand==1) total_weapons++;

    int selected = 0;
    char status[10] = {0};

    while(1) {
        clear();
        int k = 0;

        mvprintw(center_y-4, center_x, ">>>> W E A P O N S <<<<");
        mvprintw(center_y+22, center_x, "-- Use KEY UP & KEY DOWN to move between options --");
        mvprintw(center_y+24, center_x, "-- Press < ENTER > to use! --");
        mvprintw(center_y+26, center_x, "-- Press < Q > to exit --");


        mvprintw(center_y+2, center_x,"-- Short range weapons -----------");
        if(current_user->weapons.Mace==1) {
            attron(COLOR_PAIR(1));
            mvprintw(center_y+4+k*2, center_x, selected == k ? "> Mace" : "  Mace");
            attroff(COLOR_PAIR(1));
            attron(COLOR_PAIR(9));
            mvaddch(center_y+4+k*2, center_x-3, 'M');
            attroff(COLOR_PAIR(9));
            status[k] = 'm';
            k++;
        }
        if(current_user->weapons.Sword==1) {
            attron(COLOR_PAIR(1));
            mvprintw(center_y+4+k*2, center_x, selected == k ? "> Sword" : "  Sword");
            attroff(COLOR_PAIR(1));
            attron(COLOR_PAIR(9));
            mvaddch(center_y+4+k*2, center_x-3, 'S');
            attroff(COLOR_PAIR(9));
            status[k] = 's';
            k++;
        }

        mvprintw(center_y+10, center_x,"-- Long range weapons -----------");

        if(current_user->weapons.Dagger==1) {
            attron(COLOR_PAIR(1));
            mvprintw(center_y+4+k*2+8, center_x, selected == k ? "> Dagger   count: %d" : "  Dagger   count: %d",current_user->weapons.Dagger_count);
            attroff(COLOR_PAIR(1));
            mvprintw(center_y+4+k*2+8, center_x-3, "%lc", (wint_t)0x1F5E1);
            status[k] = 'd';
            k++;
        }
        if(current_user->weapons.Magic_Wand==1) {
            attron(COLOR_PAIR(1));
            mvprintw(center_y+4+k*2+8, center_x, selected == k ? "> Magic Wand   count: %d" : "  Magic Wand   count: %d",current_user->weapons.Magic_Wand_count);
            attroff(COLOR_PAIR(1));
            attron(COLOR_PAIR(9));
            mvaddch(center_y+4+k*2+8, center_x-3, 'W');
            attroff(COLOR_PAIR(9));
            status[k] = 'w';
            k++;
        }
        if(current_user->weapons.Normal_Arrow==1) {
            attron(COLOR_PAIR(1));
            mvprintw(center_y+4+k*2+8, center_x, selected == k ? "> Normal Arrow   count: %d" : "  Normal Arrow   count: %d",current_user->weapons.Normal_Arrow_count);
            attroff(COLOR_PAIR(1));
            mvprintw(center_y+4+k*2+8, center_x-3, "%lc", (wint_t)0x27B3); // ➳ ok
            status[k] = 'n';
            k++;
        }


        refresh();
        int key = getch();

        if(key == 'q' || key == 'Q') {
            endwin();
            clear();
            return in_use;
        }

        switch(key) {
            case KEY_UP:
                if(k > 0) {
                    selected = (selected - 1 + k) % k;
                }
                break;
            case KEY_DOWN:
                if(k > 0) {
                    selected = (selected + 1) % k;
                }
                break;
            case '\n':
            case KEY_ENTER:
                if(k > 0 && selected >= 0 && selected < k) {
                    switch(status[selected]) {
                        case 'm':
                            clear();
                            endwin();
                            return 1;
                        case 'd':
                            clear();
                            endwin();
                            return 2;
                        case 'w':
                            clear();
                            endwin();
                            return 3;
                        case 'n':
                            clear();
                            endwin();
                            return 4;
                        case 's':
                            clear();
                            endwin();
                            return 5;
                    }

                }
                break;
        }
    }

    endwin();
    return 0;
}

int code(char password[]){
    initscr();
    keypad(stdscr, TRUE);
    refresh();
    cbreak();
    echo();
    clear();
    start_color();
    curs_set(1);
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);
    int center_y = max_y / 2 - 7;
    int center_x = max_x / 2 - 15;
    char pass[100];
    mvprintw(center_y+2,center_x - 4,"E N T E R  T H E  P A S S W O R D");
    move(center_y + 4, center_x -4);
    getstr(pass);
    int check=0;
    if(strcmp(pass,password)==0){
        mvprintw(center_y+10,center_x-4,"Password is correct!");
        check++;

    }
    else {
        mvprintw(center_y+10,center_x-4,"Password is wrong!");
    }

    mvprintw(center_y+12,center_x -4,"press any key to back");
    getch();
    if(check==0){
        clear();
        return 0;
    }
    else{
        clear();
        return 1;
    }



}
int potion(struct user *current_user){
    initscr();
    keypad(stdscr, TRUE);
    refresh();
    noecho();
    cbreak();
    clear();
    start_color();
    curs_set(0);
    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);
    int center_y = max_y / 2 - 7;
    int center_x = max_x / 2 - 15;
    int selected =0;
    int key;
    init_pair(1,COLOR_RED,COLOR_BLACK);
    init_pair(2,COLOR_YELLOW,COLOR_BLACK);
    init_pair(3,COLOR_GREEN,COLOR_BLACK);

    while(1) {
        mvprintw(center_y-4,center_x-4,"** Potions ***************************");

        mvprintw(center_y, center_x, selected == 0 ? "> Health potion   count: %d" : "  Health potion   count: %d",current_user->spells.health_spell);
        attron(COLOR_PAIR(1));
        mvprintw(center_y, center_x-2, "%lc", (wint_t)0x271A);
        attroff(COLOR_PAIR(1));

        mvprintw(center_y+2, center_x, selected == 1 ? "> Speed potion   count: %d" : "  Speed potion   count: %d",current_user->spells.speed_spell);
        attron(COLOR_PAIR(2));
        mvprintw(center_y+2,center_x-2, "%lc", (wint_t)0x27A4);
        attroff(COLOR_PAIR(2));

        mvprintw(center_y+4, center_x, selected == 2 ? "> Damage potion   count: %d" : "  Damage potion   count: %d",current_user->spells.damage_spell);
        init_color(24, 1000, 200, 0);
        init_pair(45,24,COLOR_BLACK);
        attron(COLOR_PAIR(45));
        mvprintw(center_y+4,center_x-2, "%lc", (wint_t) 0x23FA);
        attroff(COLOR_PAIR(45));

        mvprintw(center_y+8, center_x-4, "************* ************* *************");

        mvprintw(center_y+16, center_x, "-- Use KEY UP & KEY DOWN to move between options --");
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
                refresh();
                if(selected == 0) {
                    current_user->spells.health_spell--;
                    if(current_user->spells.health_spell<0){
                        current_user->spells.health_spell=0;
                    }
                    current_user->spells.health_spell_counter=10;
                }
                if(selected == 1) {
                    current_user->spells.speed_spell--;
                    if(current_user->spells.speed_spell<0){
                        current_user->spells.speed_spell=0;
                    }
                    current_user->spells.speed_spell_counter=10;
                }
                if(selected == 2) {
                    current_user->spells.damage_spell--;
                    if(current_user->spells.damage_spell<0){
                        current_user->spells.damage_spell=0;
                    }
                    current_user->spells.damage_spell_counter=10;
                }

                refresh();
                break;
        }
    }
    getch();

}


int game_f1(struct user *current_user, int level) {
    mvprintw(2,1,"  ");

    init_color(30, 333, 333, 333);
    init_pair(40, 30, COLOR_BLACK);
    init_color(31, 0, 1000, 400);
    init_pair(41, 31, COLOR_BLACK);
    init_color(32, 255, 87, 51);
    init_pair(42, 32, COLOR_BLACK);
    init_color(33, 1000, 600, 0);
    init_pair(43, 33, COLOR_BLACK);

    setlocale(LC_ALL, "");
    initscr();
    keypad(stdscr, TRUE);
    noecho();
    curs_set(0);
    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);
    char map[max_y][max_x];

    //--------------------------
    int visited[max_y][max_x];
    for(int j=0;j<max_y;j++){
        for(int i=0;i<max_x;i++){
            visited[j][i]=0;
        }
    }

    int room_number[max_y][max_x];
    for(int j=0;j<max_y;j++){
        for(int i=0;i<max_x;i++){
            room_number[j][i]=0;
        }
    }

    int cori_number[max_y][max_x];
    for(int j=0;j<max_y;j++){
        for(int i=0;i<max_x;i++){
            cori_number[j][i]=0;
        }
    }

//    int hidden_door[max_y][max_x];
//    for(int j=0;j<max_y;j++){
//        for(int i=0;i<max_x;i++){
//            hidden_door[j][i]=0;
//        }
//    }


    ///.........weapons

    current_user->weapons.Mace=0;
    current_user->weapons.Dagger=0;
    current_user->weapons.Magic_Wand=0;
    current_user->weapons.Normal_Arrow=0;
    current_user->weapons.Sword=0;
    current_user->spells.damage_spell=0;
    current_user->spells.health_spell=0;
    current_user->spells.speed_spell=0;
    current_user->game_setting.snake_chasing=0;
    current_user->new_golds=0;

    int in_use_weapon=0;


    //.........................


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
            room_y = 5 + (rand() % (max_y - size_room_y - 8));
            room_x = 5 + (rand() % (max_x - size_room_x - 8));

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
                        room_number[room_y + i][room_x + j]=num+1; //room number
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
            int counterrr=0;

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


                    if(left == '_' && right == '#'){
                        map[y1][current_x] = '+';
                        map[y1][current_x-1] = '+';
                    }

                    else if(left == '#' && right == '_'){
                        map[y1][current_x] = '+';
                        map[y1][current_x+1] = '+';
                    }

                }

                else if (map[y1][current_x] == ' ') {
                    counterrr++;
                    map[y1][current_x] = '#';
                    cori_number[y1][current_x]=num+1;
                    if(counterrr%34==0){
                        if(map[y1+1][current_x]==' ' && y1+1 < max_y-3 ){
                            map[++y1][current_x]='#';
                            cori_number[y1][current_x]=num+1;
                        }
                        if(map[y1+1][current_x]==' ' && y1+1 < max_y-3 ){
                            map[++y1][current_x]='#';
                            cori_number[y1][current_x]=num+1;
                        }
                        if(map[y1+1][current_x]==' ' && y1+1 < max_y-3){
                            map[++y1][current_x]='#';
                            cori_number[y1][current_x]=num+1;
                        }
                        counterrr=0;
                    }

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
                    }
                    else if(down == '|' && up == '#'){
                        map[current_y][x2] = '+';
                        map[current_y+1][x2] = '+';
                    }

                }
                else if (map[current_y][x2] == ' ') {
                    map[current_y][x2] = '#';
                    cori_number[current_y][x2]=num+1;
                }
            }
        }


        num++;
    }

    //////////////////////


    //hidden door
//    int hidden; int hx; int hy;
//    while (!hidden){
//        hy = rand() % max_y  + 1;
//        hx = rand() % max_x  + 1;
//        int doornum=0;
//        for(int j=0;j<max_y;j++){
//            for(int i=0;i<max_x;i++){
//                if(room_number[j][i]==room_number[hy][hx]){
//                    if(map[j][i]=='+'){
//                        doornum++;
//                    }
//                }
//            }
//        }
//        if(doornum==1){
//            if(map[hy][hx]=='+'){
//                hidden_door[hy][hx]=1;
//                hidden++;
//            }
//        }
//    }
//
//    int verorho;
//    if(map[hy+1][hx]=='|' && map[hy-1][hx]=='|'){
//        verorho=1;
//    }else{
//        verorho=0;
//    }

    //pillars
    int num_pillars= 6+ (rand() % 4);
    int np=0 ,py ,px;
    while(np<num_pillars){
        py = rand() % max_y  + 1;
        px = rand() % max_x  + 1;
        if(map[py][px]=='.' && map[py+1][px]!='+' && map[py][px-1]!='+' && map[py][px+1]!='+' && map[py-1][px]!='+'){
            map[py][px]='O';
            np++;
        }
    }
    //traps
    int num_traps;
    if(current_user->game_setting.game_level==0){
        num_traps= 3 + (rand() % 3);
    }
    else if(current_user->game_setting.game_level==1){
        num_traps= 6 + (rand() % 5);
    }
    else if(current_user->game_setting.game_level==2){
        num_traps= 9 + (rand() % 7);
    }
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
    int num_foods;
    if(current_user->game_setting.game_level==0){
        num_foods= 14 + (rand() % 4);
    }
    else if(current_user->game_setting.game_level==1){
        num_foods= 10 + (rand() % 3);
    }
    else if(current_user->game_setting.game_level==2){
        num_foods= 5 + (rand() % 2);
    }
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
    int num_ygolds= 12 + (rand() % 4);
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
    int num_bgolds= 6 + (rand() % 2);
    int nbg=0 ,by ,bx;
    while(nbg<num_bgolds){
        by = rand() % max_y  + 1;
        bx = rand() % max_x  + 1;
        if(map[by][bx]=='.'){
            map[by][bx]='@';
            nbg++;
        }
    }



    int x2 = 0, y2 = 0;
    int stairs = 0;
    while(!stairs) {
        y2 = rand() % max_y ;
        x2 = rand() % max_x ;
        if(map[y2][x2]=='.'){
            map[y2][x2]='<';
            stairs++;
        }
    }

    //weapon
    int weapon_num = 2 + rand() % 3;
    int x3=0,y3=0;
    int weaponi =0 ;
    while(!weaponi){
        y3 = rand() % max_y ;
        x3 = rand() % max_x ;
        if(map[y3][x3]=='.'){
            if(weapon_num==1){
                map[y3][x3]='1';
                weaponi++;
            }
            else if(weapon_num==2){
                map[y3][x3]='2';
                weaponi++;
            }
            else if(weapon_num==3){
                map[y3][x3]='3';
                weaponi++;
            }

            else if(weapon_num==4){
                map[y3][x3]='4';
                weaponi++;
            }

            else if(weapon_num==5){
                map[y3][x3]='5';
                weaponi++;
            }
        }
    }

    weapon_num= 2 + rand() % 4;
    x3=0,y3=0;
    weaponi =0 ;
    while(!weaponi){
        y3 = rand() % max_y ;
        x3 = rand() % max_x ;
        if(map[y3][x3]=='.'){
            if(weapon_num==1){
                map[y3][x3]='1';
                weaponi++;
            }
            else if(weapon_num==2){
                map[y3][x3]='2';
                weaponi++;
            }
            else if(weapon_num==3){
                map[y3][x3]='3';
                weaponi++;
            }

            else if(weapon_num==4){
                map[y3][x3]='4';
                weaponi++;
            }

            else if(weapon_num==5){
                map[y3][x3]='5';
                weaponi++;
            }
        }
    }

    if(current_user->game_setting.game_level==0){
        weapon_num= 2 + rand() % 4;
        x3=0,y3=0;
        weaponi =0 ;
        while(!weaponi){
            y3 = rand() % max_y ;
            x3 = rand() % max_x ;
            if(map[y3][x3]=='.'){
                if(weapon_num==1){
                    map[y3][x3]='1';
                    weaponi++;
                }
                else if(weapon_num==2){
                    map[y3][x3]='2';
                    weaponi++;
                }
                else if(weapon_num==3){
                    map[y3][x3]='3';
                    weaponi++;
                }

                else if(weapon_num==4){
                    map[y3][x3]='4';
                    weaponi++;
                }

                else if(weapon_num==5){
                    map[y3][x3]='5';
                    weaponi++;
                }
            }
        }
    }


    //place player randomly on map
    int x = 0, y = 0;
    int player_placed = 0;
    while(!player_placed) {
        y = rand() % max_y  + 1;
        x = rand() % max_x  + 1;
        if(map[y][x] == '.' && room_number[y][x]!=number_of_rooms) {
            player_placed = 1;
        }
    }
    int room_num=room_number[y][x];

    for(int i=0;i<max_x;i++){
        for(int j=0;j<max_y;j++){
            if(room_number[j][i]==room_num){
                visited[j][i]=1;
            }
        }
    }

    /////locked door////////////////
    int locked[max_y][max_x];
    for(int j=0;j<max_y;j++){
        for(int i=0;i<max_x;i++){
            locked[j][i]=0;
        }
    }
    int lock=0;
    int locked_room_num;
    int cordinate_locked[2];
    while(!lock){
        int y4=rand()%max_y;
        int x4=rand()%max_x;
        if(map[y4][x4]=='+' && map[y4+1][x4]!='+' && map[y4-1][x4]!='+' && map[y4][x4+1]!='+' && map[y4][x4-1]!='+' ){
            int count=0;
            locked_room_num=room_number[y4][x4];
            for(int j=0;j<max_y;j++){
                for(int i=0; i<max_x;i++){
                    if(map[j][i]=='+' && room_number[j][i]==locked_room_num){
                        count++;
                    }
                }
            }
            if(count==2){
                locked[y4][x4]=1;
                cordinate_locked[0]=y4; cordinate_locked[1]=x4;
                break;
            }
        }
    }



    while(1){
        int y5=rand()%max_y;
        int x5=rand()%max_x;
        if(map[y5][x5]=='.' && room_number[y5][x5]==locked_room_num){
            map[y5][x5]='=';
            break;
        }
    }



    ////////////////
    int no_lock=0;
    while(1){
        int y6=rand()%max_y;
        int x6=rand()%max_x;
        if(map[y6][x6]=='.' ){
            map[y6][x6]='/';
            break;
        }
    }


    ///--->> deamon <<---///
    int xd=0, yd=0;
    int countd=0;
    if(current_user->game_setting.game_level==2){
        while (countd==0){
            xd = rand() % max_x;
            yd = rand() % max_y;
            if(map[yd][xd]=='.'){
                countd++;
            }
        }
    }

    ////////////////////////

    ///--->> fire breathing monster <<---///
    int xf=0, yf=0;
    int countf=0;
    while (countf==0){
        xf = rand() % max_x;
        yf = rand() % max_y;
        if(map[yf][xf]=='.'){
            countf++;
        }
    }
    ////////////////////////

    ///--->> snake <<---///
    int xs=0, ys=0;
    int counts=0;
    while (counts==0){
        xs = rand() % max_x;
        ys = rand() % max_y;
        if(map[ys][xs]=='.'){
            counts++;
        }
    }


    ////////////////////////


//    ///--->> giant <<---///
//    int xg=0, yg=0;
//    int countg=0;
//    while (countg==0){
//        xg = rand() % max_x;
//        yg = rand() % max_y;
//        if(map[yg][xg]=='.'){
//            countg++;
//        }
//    }
//    ////////////////////////
//
//
//    ///--->> undeed <<---///
//    int xu=0, yu=0;
//    int countu=0;
//    while (countu==0){
//        xu = rand() % max_x;
//        yu = rand() % max_y;
//        if(map[yu][xu]=='.'){
//            countu++;
//        }
//    }
//    //////////////////////

    int colored_room1 = 1 + rand()% (number_of_rooms-1);
    int colored_room2 = 1 + rand()%( number_of_rooms-1);

// speed spell
    int x_speed_spell=0, y_speed_spell=0;
    int countof= 1+  rand() % 2;
    while (countof!=0){
        x_speed_spell = rand() % max_x;
        y_speed_spell = rand() % max_y;
        if(map[y_speed_spell][x_speed_spell]=='.' && (room_number[y_speed_spell][x_speed_spell]==colored_room1 ||room_number[y_speed_spell][x_speed_spell]==colored_room2) ){
            map[y_speed_spell][x_speed_spell]='n'; //n stands for speed spell
            countof--;
        }
    }
    // health spell
    int x_health_spell=0, y_health_spell=0;
    countof= 1 + rand() % 2;
    while (countof!=0){
        x_health_spell = rand() % max_x;
        y_health_spell = rand() % max_y;
        if(map[y_health_spell][x_health_spell]=='.' && (room_number[y_speed_spell][x_speed_spell]==colored_room1 ||room_number[y_speed_spell][x_speed_spell]==colored_room2)){
            map[y_health_spell][x_health_spell]='b'; //b stands for health spell
            countof--;
        }
    }

    //damage spell
    int x_damage_spell=0, y_damage_spell=0;
    countof= 1 + rand() % 2;
    while (countof!=0){
        x_damage_spell = rand() % max_x;
        y_damage_spell = rand() % max_y;
        if(map[y_damage_spell][x_damage_spell]=='.' && (room_number[y_speed_spell][x_speed_spell]==colored_room1 ||room_number[y_speed_spell][x_speed_spell]==colored_room2)){
            map[y_damage_spell][x_damage_spell]='m'; //m stands for health spell
            countof--;
        }
    }



    clear();

    init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(6, COLOR_YELLOW, COLOR_BLACK);
    init_pair(7, COLOR_BLACK, COLOR_WHITE);
    init_pair(8, COLOR_YELLOW, COLOR_RED);
    init_pair(9, COLOR_CYAN, COLOR_BLACK);
    init_pair(10,COLOR_RED,COLOR_BLACK);
    init_pair(11,COLOR_GREEN,COLOR_BLACK);
    init_pair(12,COLOR_CYAN,COLOR_BLACK);
    init_pair(20,COLOR_BLUE,COLOR_BLACK);
    init_pair(14,COLOR_WHITE,COLOR_BLACK);
    ////////////////////
    int total_yellow_gold=0;
    int total_black_gold=0;
    /////////////////////

    int food=10;
    int food1=0;
    int health=10;


   ///////////////////////MAIN///////
    setlocale(LC_ALL, "");
    // printing map (player movement -- map)
    int c;
    int counter=0;

    char password[100]={0};
    int password_counter=0;
    int previous_x=0 , previous_y=0;
    int deamon_health=5;
    int fire_health = 10;
    int giant_health = 15;
    int snake_health = 20;
    int undeed_health = 30;
    int snake_chase=0;
    char previous_c;
    current_user->weapons.Normal_Arrow_count=0;
    current_user->weapons.Magic_Wand_count=0;
    current_user->weapons.Dagger_count=0;
    int start_normal_arrow=0;  int xfor4, yfor4, counterfor4;int nw=0,na=0,ns=0,nd=0;
    int start_magic_wand=0;  int xfor3, yfor3, counterfor3;int mw=0,ma=0,ms=0,md=0;
    int start_dagger=0;  int xfor2, yfor2, counterfor2; int dw=0,da=0,ds=0,dd=0;
    int is_sth_here[max_y][max_x];
    for(int j=0;j<max_y;j++){
        for(int i=0;i<max_x;i++){
            is_sth_here[j][i]=0;
        }
    }
    int food4health_counter=0;
    int k=1;



    do {
        //print map
        for(int i = 0; i < max_y; i++) {
            for(int j = 0; j < max_x; j++) {
                if(map[i][j] != ' ' && visited[i][j]==1) {
//                    if (map[i][j] == '|' || hidden_door[i][j]==1 && verorho==1){
                    if (map[i][j] == '|' ){
                        if((room_number[i][j] == colored_room1 || room_number[i][j] == colored_room2) ) {
                            attron(COLOR_PAIR(41));
                            mvaddch(i, j, '|');
                            attroff(COLOR_PAIR(41));
                        }
                        else{
                            attron(COLOR_PAIR(5));
                            mvaddch(i, j, '|');
                            attroff(COLOR_PAIR(5));
                        }
                    } else if (map[i][j] == '.' &&
                               (room_number[i][j] == colored_room1 || room_number[i][j] == colored_room2)) {
                        attron(COLOR_PAIR(40));
                        mvaddch(i, j, map[i][j]);
                        attroff(COLOR_PAIR(40));
                    } else if (map[i][j] == '_'){
                        if(room_number[i][j] == colored_room1 || room_number[i][j] == colored_room2) {
                            attron(COLOR_PAIR(41));
                            mvaddch(i, j, '_');
                            attroff(COLOR_PAIR(41));
                        }
                        else{
                            mvaddch(i, j, '_');
                        }
                    } else if (map[i][j] == 'O'){
                        if(room_number[i][j] == colored_room1 || room_number[i][j] == colored_room2) {
                            attron(COLOR_PAIR(41));
                            mvaddch(i, j, map[i][j]);
                            attroff(COLOR_PAIR(41));
                        }
                        else{
                            attron(COLOR_PAIR(5));
                            mvaddch(i, j, map[i][j]);
                            attroff(COLOR_PAIR(5));
                        }
                    } else if (map[i][j] == '#') {

                    mvaddch(i, j, map[i][j]);
                }
                    else if (map[i][j] == '$') {
                        attron(COLOR_PAIR(6));
                        mvprintw(i, j, "%lc", (wint_t) 0x25C6);
                        attroff(COLOR_PAIR(6));
                    } else if (map[i][j] == '@') {
                        init_color(21, 1000, 400, 1000);
                        init_pair(44,21,COLOR_BLACK);
                        attron(COLOR_PAIR(44));
                        mvprintw(i, j, "%lc", (wint_t) 0x25C6);
                        attroff(COLOR_PAIR(44));
                    } else if (map[i][j] == 'F') {
                        attron(COLOR_PAIR(8));
                        mvaddch(i, j, map[i][j]);
                        attroff(COLOR_PAIR(8));
                    } else if (map[i][j] == 'T') {
                        if(room_number[i][j] == colored_room1 || room_number[i][j] == colored_room2) {
                            attron(COLOR_PAIR(40));
                            mvaddch(i, j, '.');
                            attroff(COLOR_PAIR(40));
                        }
                        else{
                            mvaddch(i, j, '.');
                        }
                    } else if (map[i][j] == '^') {
                        mvaddch(i, j, map[i][j]);
                    } else if (map[i][j] == '2' || map[i][j] == 'z') {
                        mvprintw(i, j, "%lc", (wint_t) 0x1F5E1); // 🗡 ok
                    } else if (map[i][j] == '3' || map[i][j] == 'x') {
                        attron(COLOR_PAIR(9));
                        mvaddch(i, j, 'W');
                        attroff(COLOR_PAIR(9));
                        // mvprintw(i, j, "%lc", (wint_t)0x1FA84); // 🪄
                    } else if (map[i][j] == '4' || map[i][j] == 'c') {
                        mvprintw(i, j, "%lc", (wint_t) 0x27B3); // ➳ ok
                    } else if (map[i][j] == '5') {
                        attron(COLOR_PAIR(9));
                        mvaddch(i, j, 'S');
                        attroff(COLOR_PAIR(9));
                        //mvprintw(i, j, "%lc", (wint_t)0x2694); // ⚔
                    } else if (map[i][j] == '+' && locked[i][j] == 1) {
                        attron(COLOR_PAIR(10));
                        mvaddch(i, j, '@');
                        attroff(COLOR_PAIR(10));
                    } else if (map[i][j] == '+' && locked[i][j] == 2) {
                        attron(COLOR_PAIR(11));
                        mvaddch(i, j, '@');
                        attroff(COLOR_PAIR(11));
                    } else if (map[i][j] == '=') {
//                        mvprintw(i, j, "%lc", (wint_t) 0x23F9);
                          mvaddch(i, j, '&');
                    } else if (map[i][j] == '/') {
                        attron(COLOR_PAIR(6));
                        mvprintw(i, j, "%lc", (wint_t) 0x25B3);
                        attroff(COLOR_PAIR(6));
                    } else if (map[i][j] == 'b') { //health spell
                        attron(COLOR_PAIR(10));
                        mvprintw(i, j, "%lc", (wint_t)0x271A);
                        attroff(COLOR_PAIR(10));
                    } else if (map[i][j] == 'n') { //speed spell
                        attron(COLOR_PAIR(6));
                        mvprintw(i, j, "%lc", (wint_t) 0x27A4);
                        attroff(COLOR_PAIR(6));
                    } else if (map[i][j] == 'm') { //damage spell
                        init_color(24, 1000, 200, 0);
                        init_pair(45,24,COLOR_BLACK);
                        attron(COLOR_PAIR(45));
                        mvprintw(i, j, "%lc", (wint_t) 0x23FA);
                        attroff(COLOR_PAIR(45));
                    }
                    else if (map[i][j] == '+'){
                        if(room_number[i][j] == colored_room1 || room_number[i][j] == colored_room2) {
                            attron(COLOR_PAIR(41));
                            mvaddch(i, j, map[i][j]);
                            attroff(COLOR_PAIR(41));
                        }
                        else{
                            attron(COLOR_PAIR(5));
                            mvaddch(i, j, map[i][j]);
                            attroff(COLOR_PAIR(5));
                        }
                    }else if(map[i][j]!='1') {
                        if ((room_number[i][j] == colored_room1 || room_number[i][j] == colored_room2)) {
                            attron(COLOR_PAIR(41));
                            mvaddch(i, j, map[i][j]);
                            attroff(COLOR_PAIR(41));

                        } else {
                            mvaddch(i, j, map[i][j]);
                        }
                    }
                }
            }
        }


        int new_y = y;
        int new_x = x;

        if(c=='h'){
            help();
        }

        if(c=='i'){
            clear();
            in_use_weapon= weapon(current_user,in_use_weapon);
        }

        if(c ==101) { ///food window
            clear();
            int p= food_bar(&food1, &health, &food);
            if(p==3){
                continue;
            }
        }
//        if (c == 'j' || c =='J' && y > 0) new_y--;
//        if (c == 'k' || c == 'K' && y < max_y - 1) new_y++;
//        if (c == 'l' || c == 'L' && x < max_x - 1) new_x++;
//        if (c == 'h' || c == 'H' && x > 0) new_x--;

        if(current_user->spells.speed_spell_counter>0){
            if (c == KEY_UP && y > 0) new_y-=2;
            if (c == KEY_DOWN && y < max_y - 1) new_y+=2;
            if (c == KEY_RIGHT && x < max_x - 1) new_x+=2;
            if (c == KEY_LEFT && x > 0) new_x-=2;
            current_user->spells.speed_spell_counter-=1;
            if(current_user->spells.speed_spell_counter==0) current_user->spells.speed_spell_counter=0;
        }
        else{
            if (c == KEY_UP && y > 0) new_y--;
            if (c == KEY_DOWN && y < max_y - 1) new_y++;
            if (c == KEY_RIGHT && x < max_x - 1) new_x++;
            if (c == KEY_LEFT && x > 0) new_x--;

        }

        if(current_user->spells.damage_spell_counter>0){
            k=2;
            current_user->spells.damage_spell_counter-=1;
            if (current_user->spells.damage_spell_counter<0) current_user->spells.damage_spell_counter=0;
        } else {
            k=1;
        }
        mvprintw(2,max_x-30,"[h] to open help menu");



        if( (map[new_y][new_x] == '+' && (locked[new_y][new_x]==0 || locked[new_y][new_x]==2)) || map[new_y][new_x] == '$'|| map[new_y][new_x] == '@' || map[new_y][new_x] == '.' ||
           map[new_y][new_x] == '#'  || map[new_y][new_x] == 'F' || map[new_y][new_x]=='T' || map[new_y][new_x]=='^' ||
           map[new_y][new_x] == '1'  || map[new_y][new_x] == '2' || map[new_y][new_x]=='3' || map[new_y][new_x]=='4' ||
           map[new_y][new_x] == '5'  || map[new_y][new_x]=='=' || map[new_y][new_x]=='/' || map[new_y][new_x]=='z'||
           map[new_y][new_x] == 'x'  || map[new_y][new_x] == 'c' || map[new_y][new_x] == 'b' || map[new_y][new_x] == 'n'||
           map[new_y][new_x] == 'm') {


            if(map[new_y][new_x]=='b'){
                mvprintw(2,3,"You claimed a Health potion              ");
                current_user->spells.health_spell++;
            }

            if(map[new_y][new_x]=='n'){
                mvprintw(2,3,"You claimed a Speed potion              ");
                current_user->spells.speed_spell++;

            }

            if(map[new_y][new_x]=='m'){
                mvprintw(2,3,"You claimed a Damage potion             ");
                current_user->spells.damage_spell++;
            }

            if(map[new_y][new_x]=='/'){
                mvprintw(2,3,"You found an Ancient Key !              ");
                no_lock=1;
            }

            if(map[new_y][new_x]=='=' && password_counter<=3){
                char arrpass[]="0123456789";
                for(int i9=0;i9<4;i9++){
                    int temp=rand() % 9;
                    password[i9]=arrpass[temp];
                }
                mvprintw(2,3,"Password is %s                                           ",password);

            }

            if(map[new_y][new_x] == '$'){
                int temp = 2 + (rand() % 3 );
                mvprintw(2,3,"You claimed %d GOLDS !            ",temp);
                total_yellow_gold+= temp;
            }
            if(map[new_y][new_x] == '@'){
                int temp = 6 + (rand() % 4 );
                mvprintw(2,3,"You claimed %d GOLDS !            ",temp);
                total_black_gold+= temp;
            }
            if(map[new_y][new_x] == 'F'){
                int temp = 1;
                mvprintw(2,3,"You claimed %d FOOD !             ",temp);
                food1+= 1;
               if(food1>5){
                   food1=5;
               }
            }


            if(map[new_y][new_x] == 'T'){
                int temp = 1;
                mvprintw(2,3,"You stepped on a TRAP !           ",temp);
                if(current_user->game_setting.game_level==0){
                    health -= 1;
                }
                else{
                    health -= 2;
                }
                if(health<0){
                    health=0;
                }
                refresh();
                map[new_y][new_x]='^';
            }

            current_user->weapons.Mace=1;

            if(map[new_y][new_x] == '2'){
                current_user->weapons.Dagger=1;
                mvprintw(2,3,"You found a Dagger! +10                  ");
                current_user->weapons.Dagger_count+=10;
            }
            if(map[new_y][new_x] == 'z'){
                current_user->weapons.Dagger=1;
                mvprintw(2,3,"You found a Dagger! +1                  ");
                current_user->weapons.Dagger_count+=1;
            }


            if(map[new_y][new_x] == '3'){
                current_user->weapons.Magic_Wand=1;
                mvprintw(2,3,"You found a Magic Wand! +8             ");
                current_user->weapons.Magic_Wand_count+=8;
            }
            if(map[new_y][new_x] == 'x'){
                current_user->weapons.Magic_Wand=1;
                mvprintw(2,3,"You found a Magic Wand! +1             ");
                current_user->weapons.Magic_Wand_count+=1;
            }


            if(map[new_y][new_x] == '4'){
                current_user->weapons.Normal_Arrow=1;
                mvprintw(2,3,"You found a Normal Arrow! +20          ");
                current_user->weapons.Normal_Arrow_count+=20;
            }
            if(map[new_y][new_x] == 'c'){
                current_user->weapons.Normal_Arrow=1;
                mvprintw(2,3,"You found a Normal Arrow! +1          ");
                current_user->weapons.Normal_Arrow_count+=1;
            }


            if(map[new_y][new_x] == '5'){
                current_user->weapons.Sword=1;
                mvprintw(2,3,"You found a Sword!                   ");
            }
            y = new_y;
            x = new_x;
        }
        mvprintw(3,3,"                                                      ",password);

        if(map[y][x]!='+' && map[y][x]!='#'&&map[y][x]!='^' && map[y][x]!='='){
            map[y][x]='.';
        }
        mvprintw(max_y-2,max_x-10,"GOLD: %d",total_black_gold+total_yellow_gold);


        if(c=='o'){
            potion(current_user);
        }



        //deamon ////////

        if(current_user->game_setting.game_level==2){
            if(deamon_health>0){

                if(room_number[new_y][new_x]==room_number[yd][xd]){
                    move_deamon(yd,xd);
                }

                if(deamon_health>0 && xd==new_x && yd==new_y){
                    if(current_user->game_setting.game_level==0){
                        health -= 1;
                    }
                    else{
                        health -= 2;
                    }
                    mvprintw(3,3,"Deamon hits you!                            ");
                    if(health<0){
                        health=0;
                    }
                }
                refresh();

            }
        }



        ////////--------------------------



        //fire breathing monster//////////////
        int new_x_f , new_y_f;
        int fx = new_x - xf;
        int fy = new_y - yf;

        if(fire_health>0){

            if(room_number[new_y][new_x] == room_number[yf][xf]  ) {

                new_x_f = xf;
                new_y_f = yf;

                if((abs(fx)<=6 || abs(fy)<=6 )){
                    if (abs(fx) > abs(fy)) {
                        if (fx > 0) {
                            new_x_f += 1;
                        } else {
                            new_x_f -= 1;
                        }
                    } else {
                        if (fy > 0) {
                            new_y_f += 1;
                        } else {
                            new_y_f -= 1;
                        }
                    }

                }

                move_fire_breathing_monster(new_y_f, new_x_f);
            }
            refresh();

            if(fire_health>=0 && new_x_f==new_x && new_y_f==new_y){

                if(current_user->game_setting.game_level==0){
                    health -= 1;
                }
                else{
                    health -= 2;
                }
                mvprintw(3,3,"Fire breathing monster hits you!                       ");
                if(health<0){
                    health=0;
                }
            }


        }


        //////----------------------
        ////snake////////////////////////
        int new_y_s;
        int new_x_s;
        if(room_number[new_y][new_x]==room_number[ys][xs] && snake_health>0){
            snake_chase=1;

        }
        if(snake_chase==1 && snake_health>0){
            new_x_s = previous_x;
            new_y_s = previous_y;
            refresh();
            if(map[new_y_s][new_x_s]!=' '){
                move_snake(new_y_s,new_x_s );
            }
        }

        if(snake_health>0 && new_x_s==new_x && new_y_s==new_y){
            if(current_user->game_setting.game_level==0){
                health -= 1;
            }
            else{
                health -= 2;
            }
            mvprintw(3,3,"Snake hits you!                                 ");
            if(health<0){
                health=0;
            }
        }
        refresh();

        ////////////---------------------//


        draw_character(y, x, current_user->game_setting.player_color);


        ///health

        if(current_user->game_setting.game_level==0){
            if(counter==40){
                health--;
                counter=0;
            }
        }
        else if(current_user->game_setting.game_level==1){
            if(counter==25){
                health--;
                counter=0;
            }
        }
        else if(current_user->game_setting.game_level==2){
            if(counter==15){
                health--;
                counter=0;
            }
        }

        if(current_user->game_setting.game_level==0){
            if(counter==30){
                food--;
            }
        }
        else if(current_user->game_setting.game_level==1){
            if(counter==20){
                food--;
            }
        }
        else if(current_user->game_setting.game_level==2){
            if(counter==10){
                food--;
            }
        }



        if(health==0){
            current_user->new_golds+=total_black_gold+total_yellow_gold;
            current_user->total_gold+=current_user->new_golds;
            return 0;
        }

        //door code
        int status=2;
        init_pair(12,COLOR_YELLOW,COLOR_BLACK);
        init_pair(13,COLOR_MAGENTA,COLOR_BLACK);
        init_pair(14,COLOR_RED,COLOR_BLACK);


        int dx = xd - new_x;
        int dy = yd - new_y;
        fx = new_x_f -  new_x;
        fy = new_y_f - new_y;
        int sx = new_x_s -  new_x;
        int sy = new_y_s - new_y;

        if(c=='p' || c=='P') {
            if (in_use_weapon == 1) {
                if ((abs(dy) == 1 || abs(dy) == -1 || abs(dy) == 0) &&
                    (abs(dx) == 1 || abs(dx) == -1 || abs(dx) == 0)) {
                    deamon_health -= 5*k;
                    if (deamon_health <= 0) {
                        deamon_health = 0;
                    }
                    mvprintw(3, 3, "You hit Deamon!  health: %d/5                           ", deamon_health);


                }
                if ((abs(fy) == 1 || abs(fy) == -1 || abs(fy) == 0) &&
                    (abs(fx) == 1 || abs(fx) == -1 || abs(fx) == 0)) {
                    fire_health -= 5*k;
                    if (fire_health <= 0) {
                        fire_health = 0;
                    }
                    mvprintw(3, 3, "You hit Fire breathing monster!  health: %d/10                   ", fire_health);


                }
                if ((abs(sy) == 1 || abs(sy) == -1 || abs(sy) == 0) &&
                    (abs(sx) == 1 || abs(sx) == -1 || abs(sx) == 0)) {
                    snake_health -= 5*k;
                    if (snake_health <= 0) {
                        snake_health = 0;
                    }
                    mvprintw(3, 3, "You hit Snake!  health: %d/20                                    ", snake_health);

                }
            }
            if(in_use_weapon==5){
                if ((abs(dy) == 1 || abs(dy) == -1 || abs(dy) == 0) &&
                    (abs(dx) == 1 || abs(dx) == -1 || abs(dx) == 0)) {
                    deamon_health -= 10*k;
                    if (deamon_health <= 0) {
                        deamon_health = 0;
                    }
                    mvprintw(3, 3, "You hit Deamon!  health: %d/5                           ", deamon_health);

                }
                if ((abs(fy) == 1 || abs(fy) == -1 || abs(fy) == 0) &&
                    (abs(fx) == 1 || abs(fx) == -1 || abs(fx) == 0)) {
                    fire_health -= 10*k;
                    if (fire_health <= 0) {
                        fire_health = 0;
                    }
                    mvprintw(3, 3, "You hit Fire breathing monster!  health: %d/10                   ", fire_health);


                }
                if ((abs(sy) == 1 || abs(sy) == -1 || abs(sy) == 0) &&
                    (abs(sx) == 1 || abs(sx) == -1 || abs(sx) == 0)) {
                    snake_health -= 10*k;
                    if (snake_health <= 0) {
                        snake_health = 0;
                    }
                    mvprintw(3, 3, "You hit Snake!  health: %d/20                                    ", snake_health);

                }
            }
        }

        ///////////dagger
        if(in_use_weapon == 2 && previous_c == 'p') {
            start_dagger = 1;
            xfor2 = new_x;
            yfor2 = new_y;
            counterfor2 = 1;
            switch (c) {
                case 'a':
                    da++; break;
                case 'w':
                    dw++; break;
                case 's':
                    ds++; break;
                case 'd':
                    dd++; break;
            }

            current_user->weapons.Dagger_count--;
            if(current_user->weapons.Dagger_count < 0) {
                current_user->weapons.Dagger_count = 0;
            }
        }

        if(start_dagger == 1 && counterfor2 > 0) {

            if(xfor2 == new_x_f && yfor2 == new_y_f) {
                fire_health -= 10*k;
                if(fire_health <= 0) fire_health = 0;
                mvprintw(3, 3, "You hit Fire breathing monster!  health: %d/10                   ", fire_health);
                counterfor2=0;
                start_dagger=0;
            }
            if(xfor2 == new_x_s && yfor2 == new_y_s) {
                snake_health -= 10*k;
                if(snake_health <= 0) snake_health = 0;
                mvprintw(3, 3, "You hit Snake!  health: %d/20                                    ", snake_health);
                counterfor2=0;
                start_dagger=0;
            }
            if(xfor2 == xd && yfor2 == yd) {
                deamon_health -= 10*k;
                if(deamon_health <= 0) deamon_health = 0;
                mvprintw(3, 3, "You hit Deamon!  health: %d/5                           ", deamon_health);
                counterfor2=0;
                start_dagger=0;
            }

            if(da==1) {
                xfor2--;
                if(map[yfor2][xfor2]=='|' || map[yfor2][xfor2]=='-'){
                    counterfor2=0;
                    if(map[yfor2][xfor2+1]=='.')
                    {
                        map[yfor2][xfor2+1]='z';
                    }
                }
            }
            else if(ds==1) {
                yfor2++;
                if(map[yfor2][xfor2]=='|' || map[yfor2][xfor2]=='_'){
                    counterfor2=0;
                    if(map[yfor2-1][xfor2]=='.')
                    {
                        map[yfor2-1][xfor2]='z';
                    }
                }
            }
            else if(dd==1) {
                xfor2++;
                if(map[yfor2][xfor2]=='|' || map[yfor2][xfor2]=='_'){
                    counterfor2=0;
                    if(map[yfor2][xfor2-1]=='.')
                    {
                        map[yfor2][xfor2-1]='z';
                    }
                }
            }
            else if(dw==1) {
                yfor2--;
                if(map[yfor2][xfor2]=='|' || map[yfor2][xfor2]=='_'){
                    counterfor2=0;
                    if(map[yfor2+1][xfor2]=='.')
                    {
                        map[yfor2+1][xfor2]='z';
                    }
                }
            }

            counterfor2++;
            if(counterfor2 >= 5) {
                if(map[yfor2][xfor2]=='.'){
                    map[yfor2][xfor2]='z'; // z represents 1 dagger
                }
                start_dagger = 0;
                counterfor2 = 0;
                dd=0; da=0; dw=0; ds=0;
            }
            if(map[yfor2][xfor2]=='.'){
                mvaddch(yfor2, xfor2, '*');
            }
            refresh();
        }
        ////////////


        ///////////normal arrow
        if(in_use_weapon == 4 && previous_c == 'p') {
            start_normal_arrow = 1;
            xfor4 = new_x;
            yfor4 = new_y;
            counterfor4 = 1;
            switch (c) {
                case 'a':
                    na++; break;
                case 'w':
                    nw++; break;
                case 's':
                    ns++; break;
                case 'd':
                    nd++; break;
            }

            current_user->weapons.Normal_Arrow_count--;
            if(current_user->weapons.Normal_Arrow_count < 0) {
                current_user->weapons.Normal_Arrow_count = 0;
            }
        }

        if(start_normal_arrow == 1 && counterfor4 > 0) {

            if(xfor4 == new_x_f && yfor4 == new_y_f) {
                fire_health -= 10*k;
                if(fire_health <= 0) fire_health = 0;
                mvprintw(3, 3, "You hit Fire breathing monster!  health: %d/10                   ", fire_health);
                counterfor4=0;
                start_normal_arrow=0;
            }
            if(xfor4 == new_x_s && yfor2 == new_y_s) {
                snake_health -= 10*k;
                if(snake_health <= 0) snake_health = 0;
                mvprintw(3, 3, "You hit Snake!  health: %d/20                                    ", snake_health);
                counterfor4=0;
                start_normal_arrow=0;
            }
            if(xfor4 == xd && yfor4== yd) {
                deamon_health -= 10*k;
                if(deamon_health <= 0) deamon_health = 0;
                mvprintw(3, 3, "You hit Deamon!  health: %d/5                           ", deamon_health);
                counterfor4=0;
                start_normal_arrow=0;
            }

            if(na==1) {
                xfor4--;
                if(map[yfor4][xfor4]=='|' || map[yfor4][xfor4]=='_'){
                    counterfor4=0;
                    if(map[yfor4][xfor4+1]=='.')
                    {
                        map[yfor4][xfor4+1]='c';
                    }
                }
            }
            else if(ns==1) {
                yfor4++;
                if(map[yfor4][xfor4]=='|' || map[yfor4][xfor4]=='_'){
                    counterfor4=0;
                    if(map[yfor4-1][xfor4]=='.')
                    {
                        map[yfor4-1][xfor4]='c';
                    }
                }
            }
            else if(nd==1) {
                xfor4++;
                if(map[yfor4][xfor4]=='|' || map[yfor4][xfor4]=='_'){
                    counterfor4=0;
                    if(map[yfor4][xfor4-1]=='.')
                    {
                        map[yfor4][xfor4-1]='c';
                    }
                }
            }
            else if(nw==1) {
                yfor4--;
                if(map[yfor4][xfor4]=='|' || map[yfor4][xfor4]=='_'){
                    counterfor4=0;
                    if(map[yfor4+1][xfor4]=='.')
                    {
                        map[yfor4+1][xfor4]='c';
                    }
                }
            }

            counterfor4++;
            if(counterfor4 >= 5) {
                if(map[yfor4][xfor4]=='.'){
                    map[yfor4][xfor4]='c'; // c represents 1 normal arrow
                }
                start_normal_arrow = 0;
                counterfor4 = 0;
                nd=0; na=0; nw=0; ns=0;
            }
            if(map[yfor4][xfor4]=='.'){
                mvaddch(yfor4, xfor4, '-');
            }

            refresh();
        }
        ////////////

        ///////////Magic wand
        if(in_use_weapon == 3 && previous_c == 'p') {
            start_magic_wand = 1;
            xfor3 = new_x;
            yfor3 = new_y;
            counterfor3 = 1;
            switch (c) {
                case 'a':
                    ma++; break;
                case 'w':
                    mw++; break;
                case 's':
                    ms++; break;
                case 'd':
                    md++; break;
            }

            current_user->weapons.Magic_Wand_count--;
            if(current_user->weapons.Magic_Wand_count < 0) {
                current_user->weapons.Magic_Wand_count = 0;
            }
        }

        if(start_magic_wand == 1 && counterfor3 > 0) {

            if(xfor3 == new_x_f && yfor3 == new_y_f) {
                fire_health -= 15*k;
                if(fire_health <= 0) fire_health = 0;
                mvprintw(3, 3, "You hit Fire breathing monster!  health: %d/10                   ", fire_health);
                counterfor3=0;
                start_magic_wand=0;
            }
            if(xfor3 == new_x_s && yfor3 == new_y_s) {
                snake_health -= 15*k;
                if(snake_health <= 0) snake_health = 0;
                mvprintw(3, 3, "You hit Snake!  health: %d/20                                    ", snake_health);
                counterfor3=0;
                snake_chase=0;
                start_magic_wand=0;
            }
            if(xfor3 == xd && yfor3 == yd) {
                deamon_health -= 15*k;
                if(deamon_health <= 0) deamon_health = 0;
                mvprintw(3, 3, "You hit Deamon!  health: %d/5                                  ", deamon_health);
                counterfor3=0;
                start_magic_wand=0;
            }

            if(ma==1) {
                xfor3--;
                if(map[yfor3][xfor3]=='|' || map[yfor3][xfor3]=='-'){
                    counterfor3=0;
                    if(map[yfor3][xfor3+1]=='.')
                    {
                        map[yfor3][xfor3+1]='x';
                    }
                }
            }
            else if(ms==1) {
                yfor3++;
                if(map[yfor3][xfor3]=='|' || map[yfor3][xfor3]=='-'){
                    counterfor3=0;
                    if(map[yfor3-1][xfor3+1]=='.')
                    {
                        map[yfor3-1][xfor3+1]='x';
                    }
                }
            }
            else if(md==1) {
                xfor3++;
                if(map[yfor3][xfor3]=='|' || map[yfor3][xfor3]=='-'){
                    counterfor3=0;
                    if(map[yfor3][xfor3-1]=='.')
                    {
                        map[yfor3][xfor3-1]='x';
                    }
                }
            }
            else if(mw==1) {
                yfor3--;
                if(map[yfor3][xfor3]=='|' || map[yfor3][xfor3]=='-'){
                    counterfor3=0;
                    if(map[yfor3+1][xfor3]=='.')
                    {
                        map[yfor3+1][xfor3]='x';
                    }
                }
            }

            counterfor3++;
            if(counterfor3 >= 5) {
                if(map[yfor3][xfor3]=='.'){
                    map[yfor3][xfor3]='x'; // x represents 1 magic wand
                }
                start_magic_wand = 0;
                counterfor3 = 0;
                md=0; ma=0; mw=0; ms=0;
            }
            if(map[yfor3][xfor3]=='.'){
                mvaddch(yfor3, xfor3, '+');
            }
            mvprintw(2, 3, "                                                            ");
            refresh();
        }
        ////////////


        if(locked[cordinate_locked[0]][cordinate_locked[1]]==1 && (new_y+1==cordinate_locked[0] && new_x==cordinate_locked[1] ||
          new_y-1==cordinate_locked[0] && new_x==cordinate_locked[1] ||
          new_y==cordinate_locked[0] && new_x+1==cordinate_locked[1] ||
          new_y==cordinate_locked[0] && new_x-1==cordinate_locked[1] )){
            mvprintw(3,3,"                                                               ",password);
            if (no_lock==0){
                if(password_counter>3){
                    attron(COLOR_PAIR(14));
                    mvprintw(3,3,"The door has been locked forever!!                   ");
                    attroff(COLOR_PAIR(14));
                }
                else {
                    mvprintw(3,3,"The door is locked. Press L to enter the pass !");
                }
                if(c=='l' || c == 'L' && password_counter<=3){
                    status=code(password);
                    password_counter++;
                }
                if(status==1 && password_counter<=3 ){
                    locked[cordinate_locked[0]][cordinate_locked[1]]=2;
                    mvprintw(3,3,"The door is unlocked !                                       ");

                }
                else if(status==0 && password_counter<=3){
                    if(password_counter==1){
                        attron(COLOR_PAIR(12));
                        mvprintw(3,3,"Wrong password!                                ");
                        attroff(COLOR_PAIR(12));
                    }
                    else if(password_counter==2){
                        attron(COLOR_PAIR(13));
                        mvprintw(3,3,"Wrong password!                                ");
                        attroff(COLOR_PAIR(13));
                    }
                    else if(password_counter==3){
                        attron(COLOR_PAIR(14));
                        mvprintw(3,3,"Wrong password! Door locked forever!!                          ");
                        attroff(COLOR_PAIR(14));
                    }
                }


            }
            else if(no_lock==1){
                locked[cordinate_locked[0]][cordinate_locked[1]]=2;
                mvprintw(3,3,"The door is unlocked !                                       ");
                mvprintw(3,3,"                                                            ");
            }


        }
        if(counter==40){
            strcpy(password,"0");
        }

        if(food>=10){
            if(food4health_counter>=4){
                if(current_user->spells.health_spell_counter>0){
                    health+=2;
                    current_user->spells.health_spell_counter-=1;
                    if(current_user->spells.health_spell_counter<0) current_user->spells.health_spell_counter=0;
                }
                else{
                    health+=1;
                }
                if(health>10) health=10;
                food4health_counter=0;
            }
        }

        food4health_counter++;
        refresh();

        mvprintw(max_y-2,60,"floor : 1");

        //health
        mvprintw(max_y-2,2,"health: ");
        refresh();
        for(int i =0;i<=health;i++){
            mvprintw(max_y-2,10+i,"♥");
            mvprintw(max_y-2,10+health," ");
            for(int j=0;j<10-i;j++){
                mvprintw(max_y-2,10+health+j," ");
            }
            mvprintw(max_y-2,10+12,"%d%c",health*10,'%');

        }

        //food
        mvprintw(max_y-2,32,"food: ");

        for(int i =0;i<=food;i++){
            mvprintw(max_y-2,38+i,"+");
            mvprintw(max_y-2,38+food," ");
            mvprintw(max_y-2,38 + 12,"     ");
            mvprintw(max_y-2,38 + 12,"%d%c",food*10,'%');
            refresh();
        }
        refresh();

        if(in_use_weapon==1){
            mvprintw(max_y-2,74,"weapon: Mace");
        }
        else if(in_use_weapon==2){
            mvprintw(max_y-2,74,"weapon: Dagger");
        }
        else if(in_use_weapon==3){
            mvprintw(max_y-2,74,"weapon: Magic Wand");
        }
        else if(in_use_weapon==4){
            mvprintw(max_y-2,74,"weapon: Normal Arrow");
        }
        else if(in_use_weapon==4){
            mvprintw(max_y-2,74,"weapon: Sword");
        }
        else {
            mvprintw(max_y-2,74,"weapon: no weapon in use!");
        }

        counter++;


        refresh();
        if( map[new_y][new_x]=='#'){
            int temp = cori_number[new_y][new_x];
            for(int j=-4;j<4;j++){
                for(int i=-4;i<4;i++){
                    if(cori_number[new_y+j][new_x+i]==temp && map[new_y+j][new_x+i]=='#' && visited[new_y+j][new_x+i]!=1 || map[new_y+j][new_x+i]=='+'&& visited[new_y+j][new_x+i]!=1){
                        visited[new_y+j][new_x+i]=1;
                    }
                }
            }
        }

        else if(map[new_y][new_x]=='+' ){
            int tempp=room_number[new_y][new_x];
            for(int j1=0;j1<max_y;j1++){
                for (int i1 = 0; i1 < max_x; i1++) {
                    if(visited[j1][i1]!=1 && room_number[j1][i1]==tempp){
                        visited[j1][i1]=1;
                    }
                }
            }
        }

        if(map[new_y][new_x]=='<'){
            current_user->food=food;
            current_user->health=health;
            current_user->food1=food1;
            current_user->new_golds=total_black_gold+total_yellow_gold;
            current_user->weapons.in_use_weapon=in_use_weapon;
            if(snake_chase==1) {
                current_user->game_setting.snake_chasing = 1;
            }
            return game_f2(current_user,current_user->game_setting.game_level);
        }

        if(c=='m'){
            current_user->food=food;
            current_user->health=health;
            current_user->food1=food1;
            current_user->new_golds=total_black_gold+total_yellow_gold;
            current_user->weapons.in_use_weapon=in_use_weapon;
            return game_f4(current_user,current_user->game_setting.game_level);

        }

        previous_x = new_x;
        previous_y = new_y;
        previous_c =c;
        refresh();

    } while ((c = getch()) != 27);

    endwin();
}


int game_f2(struct user *current_user , int level) {

    mvprintw(2,1,"  ");
    init_color(30, 333, 333, 333);
    init_pair(40, 30, COLOR_BLACK);
    init_color(31, 0, 1000, 400);
    init_pair(41, 31, COLOR_BLACK);
    init_color(32, 255, 87, 51);
    init_pair(42, 32, COLOR_BLACK);
    init_color(33, 1000, 600, 0);
    init_pair(43, 33, COLOR_BLACK);

    setlocale(LC_ALL, "");
    initscr();
    keypad(stdscr, TRUE);
    noecho();
    curs_set(0);
    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);
    char map[max_y][max_x];

    //--------------------------
    int visited[max_y][max_x];
    for(int j=0;j<max_y;j++){
        for(int i=0;i<max_x;i++){
            visited[j][i]=0;
        }
    }

    int room_number[max_y][max_x];
    for(int j=0;j<max_y;j++){
        for(int i=0;i<max_x;i++){
            room_number[j][i]=0;
        }
    }

    int cori_number[max_y][max_x];
    for(int j=0;j<max_y;j++){
        for(int i=0;i<max_x;i++){
            cori_number[j][i]=0;
        }
    }
    ///.........weapons

    int in_use_weapon= current_user->weapons.in_use_weapon;

    //.........................


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
            room_y = 5 + (rand() % (max_y - size_room_y - 8));
            room_x = 5 + (rand() % (max_x - size_room_x - 8));

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
                    room_number[room_y + i][room_x + j]=num+1; //room number
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
            int counterrr=0;

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


                    if(left == '_' && right == '#'){
                        map[y1][current_x] = '+';
                        map[y1][current_x-1] = '+';
                    }

                    else if(left == '#' && right == '_'){
                        map[y1][current_x] = '+';
                        map[y1][current_x+1] = '+';
                    }

                }

                else if (map[y1][current_x] == ' ') {
                    counterrr++;
                    map[y1][current_x] = '#';
                    cori_number[y1][current_x]=num+1;
                    if(counterrr%34==0){
                        if(map[y1+1][current_x]==' ' && y1+1 < max_y-3){
                            map[++y1][current_x]='#';
                            cori_number[y1][current_x]=num+1;
                        }
                        if(map[y1+1][current_x]==' ' && y1+1 < max_y-3 ){
                            map[++y1][current_x]='#';
                            cori_number[y1][current_x]=num+1;
                        }
                        if(map[y1+1][current_x]==' '&& y1+1 < max_y-3){
                            map[++y1][current_x]='#';
                            cori_number[y1][current_x]=num+1;
                        }
                        counterrr=0;
                    }

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
                    }
                    else if(down == '|' && up == '#'){
                        map[current_y][x2] = '+';
                        map[current_y+1][x2] = '+';
                    }

                }
                else if (map[current_y][x2] == ' ') {
                    map[current_y][x2] = '#';
                    cori_number[current_y][x2]=num+1;
                }
            }
        }


        num++;
    }

    //////////////////////

    //pillars
    int num_pillars= 6+ (rand() % 4);
    int np=0 ,py ,px;
    while(np<num_pillars){
        py = rand() % max_y  + 1;
        px = rand() % max_x  + 1;
        if(map[py][px]=='.' && map[py+1][px]!='+' && map[py][px-1]!='+' && map[py][px+1]!='+' && map[py-1][px]!='+'){
            map[py][px]='O';
            np++;
        }
    }
    //traps
    int num_traps;
    if(current_user->game_setting.game_level==0){
        num_traps= 3 + (rand() % 3);
    }
    else if(current_user->game_setting.game_level==1){
        num_traps= 6 + (rand() % 5);
    }
    else if(current_user->game_setting.game_level==2){
        num_traps= 9 + (rand() % 7);
    }
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
    int num_foods;
    if(current_user->game_setting.game_level==0){
        num_foods= 12 + (rand() % 4);
    }
    else if(current_user->game_setting.game_level==1){
        num_foods= 9 + (rand() % 3);
    }
    else if(current_user->game_setting.game_level==2){
        num_foods= 4 + (rand() % 2);
    }
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
    int num_ygolds= 10 + (rand() % 4);
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
    int num_bgolds= 5 + (rand() % 1);
    int nbg=0 ,by ,bx;
    while(nbg<num_bgolds){
        by = rand() % max_y  + 1;
        bx = rand() % max_x  + 1;
        if(map[by][bx]=='.'){
            map[by][bx]='@';
            nbg++;
        }
    }


    int x2 = 0, y2 = 0;
    int stairs = 0;
    while(!stairs) {
        y2 = rand() % max_y  + 1;
        x2 = rand() % max_x  + 1;
        if(map[y2][x2]=='.'){
            map[y2][x2]='<';
            stairs++;
        }
    }

    int y=y2;
    int x=x2;

    int room_num=room_number[y][x];

    for(int i=0;i<max_x;i++){
        for(int j=0;j<max_y;j++){
            if(room_number[j][i]==room_num){
                visited[j][i]=1;
            }
        }
    }

    //weapons
    int weapon_num= 2 + rand() % 4;
    int x3=0,y3=0;
    int weaponi =0 ;
    while(!weaponi){
        y3 = rand() % max_y ;
        x3 = rand() % max_x ;
        if(map[y3][x3]=='.'){
            if(weapon_num==1){
                map[y3][x3]='1';
                weaponi++;
            }
            else if(weapon_num==2){
                map[y3][x3]='2';
                weaponi++;
            }
            else if(weapon_num==3){
                map[y3][x3]='3';
                weaponi++;
            }

            else if(weapon_num==4){
                map[y3][x3]='4';
                weaponi++;
            }

            else if(weapon_num==5){
                map[y3][x3]='5';
                weaponi++;
            }
        }
    }

    weapon_num= 2 + rand() % 4;
    x3=0,y3=0;
    weaponi =0 ;
    while(!weaponi){
        y3 = rand() % max_y ;
        x3 = rand() % max_x ;
        if(map[y3][x3]=='.'){
            if(weapon_num==1){
                map[y3][x3]='1';
                weaponi++;
            }
            else if(weapon_num==2){
                map[y3][x3]='2';
                weaponi++;
            }
            else if(weapon_num==3){
                map[y3][x3]='3';
                weaponi++;
            }

            else if(weapon_num==4){
                map[y3][x3]='4';
                weaponi++;
            }

            else if(weapon_num==5){
                map[y3][x3]='5';
                weaponi++;
            }
        }
    }

    stairs = 0;
    while(!stairs) {
        y2 = rand() % max_y  + 1;
        x2 = rand() % max_x  + 1;
        if(map[y2][x2]=='.'){
            map[y2][x2]='<';
            stairs++;
        }
    }

    /////locked door////////////////
    int locked[max_y][max_x];
    for(int j=0;j<max_y;j++){
        for(int i=0;i<max_x;i++){
            locked[j][i]=0;
        }
    }
    int lock=0;
    int locked_room_num;
    int cordinate_locked[2];
    while(!lock){
        int y4=rand()%max_y;
        int x4=rand()%max_x;
        if(map[y4][x4]=='+' && map[y4+1][x4]!='+' && map[y4-1][x4]!='+' && map[y4][x4+1]!='+' && map[y4][x4-1]!='+'){
            int count=0;
            locked_room_num=room_number[y4][x4];
            for(int j=0;j<max_y;j++){
                for(int i=0; i<max_x;i++){
                    if(map[j][i]=='+' && room_number[j][i]==locked_room_num){
                        count++;
                    }
                }
            }
            if(count==2){
                locked[y4][x4]=1;
                cordinate_locked[0]=y4; cordinate_locked[1]=x4;
                break;
            }
        }
    }



    while(1){
        int y5=rand()%max_y;
        int x5=rand()%max_x;
        if(map[y5][x5]=='.' && room_number[y5][x5]==locked_room_num){
            map[y5][x5]='=';
            break;
        }
    }

    int no_lock=0;
    while(1){
        int y6=rand()%max_y;
        int x6=rand()%max_x;
        if(map[y6][x6]=='.' ){
            map[y6][x6]='/';
            break;
        }
    }


    ///--->> deamon <<---///
    int xd=0, yd=0;
    int countd=0;
    while (countd==0){
        xd = rand() % max_x;
        yd = rand() % max_y;
        if(map[yd][xd]=='.'){
            countd++;
        }
    }
    ////////////////////////

    ///--->> fire breathing monster <<---///
    int xf=0, yf=0;
    int countf=0;
    while (countf==0){
        xf = rand() % max_x;
        yf = rand() % max_y;
        if(map[yf][xf]=='.'){
            countf++;
        }
    }

    ///second

    int xf2=0, yf2=0;
    int countf2=0;

    if(current_user->game_setting.game_level==2) {
        while (countf2 == 0) {
            xf2 = rand() % max_x;
            yf2 = rand() % max_y;
            if (map[yf2][xf2] == '.') {
                countf2++;
            }
        }
    }
    ////////////////////////
    int xs=0, ys=0;
    ///--->> snake <<---///
    if(current_user->game_setting.snake_chasing==1){
        xs = x; ys=y;
    }
    else {
        int counts=0;
        while (counts==0){
            xs = rand() % max_x;
            ys = rand() % max_y;
            if(map[ys][xs]=='.'){
                counts++;
            }
        }
    }

    ////////////////////////


//    ///--->> giant <<---///
//    int xg=0, yg=0;
//    int countg=0;
//    while (countg==0){
//        xg = rand() % max_x;
//        yg = rand() % max_y;
//        if(map[yg][xg]=='.'){
//            countg++;
//        }
//    }
//    ////////////////////////
//
//
//    ///--->> undeed <<---///
//    int xu=0, yu=0;
//    int countu=0;
//    while (countu==0){
//        xu = rand() % max_x;
//        yu = rand() % max_y;
//        if(map[yu][xu]=='.'){
//            countu++;
//        }
//    }
//    //////////////////////



    int colored_room1 = 1 + rand()% (number_of_rooms-1);
    int colored_room2 = 1 + rand()%( number_of_rooms-1);

// speed spell
    int x_speed_spell=0, y_speed_spell=0;
    int countof= 1+  rand() % 2;
    while (countof!=0){
        x_speed_spell = rand() % max_x;
        y_speed_spell = rand() % max_y;
        if(map[y_speed_spell][x_speed_spell]=='.' && (room_number[y_speed_spell][x_speed_spell]==colored_room1 ||room_number[y_speed_spell][x_speed_spell]==colored_room2) ){
            map[y_speed_spell][x_speed_spell]='n'; //n stands for speed spell
            countof--;
        }
    }
    // health spell
    int x_health_spell=0, y_health_spell=0;
    countof= 1 + rand() % 2;
    while (countof!=0){
        x_health_spell = rand() % max_x;
        y_health_spell = rand() % max_y;
        if(map[y_health_spell][x_health_spell]=='.' && (room_number[y_speed_spell][x_speed_spell]==colored_room1 ||room_number[y_speed_spell][x_speed_spell]==colored_room2)){
            map[y_health_spell][x_health_spell]='b'; //b stands for health spell
            countof--;
        }
    }

    //damage spell
    int x_damage_spell=0, y_damage_spell=0;
    countof= 1 + rand() % 2;
    while (countof!=0){
        x_damage_spell = rand() % max_x;
        y_damage_spell = rand() % max_y;
        if(map[y_damage_spell][x_damage_spell]=='.' && (room_number[y_speed_spell][x_speed_spell]==colored_room1 ||room_number[y_speed_spell][x_speed_spell]==colored_room2)){
            map[y_damage_spell][x_damage_spell]='m'; //m stands for health spell
            countof--;
        }
    }




    ////////////////

    clear();

    init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(6, COLOR_YELLOW, COLOR_BLACK);
    init_pair(7, COLOR_BLACK, COLOR_WHITE);
    init_pair(8, COLOR_YELLOW, COLOR_RED);
    init_pair(9, COLOR_CYAN, COLOR_BLACK);
    init_pair(10,COLOR_RED,COLOR_BLACK);
    init_pair(11,COLOR_GREEN,COLOR_BLACK);
    ////////////////////
    int total_yellow_gold=0;
    int total_black_gold=0;
    /////////////////////

    int food=current_user->food;
    int food1=current_user->food1;
    int health=current_user->health;


    ///////////////////////MAIN///////

    // printing map (player movement -- map)
    int c;
    int counter=0;

    char password[100]={0};
    int password_counter=0;
    int previous_x=0 , previous_y=0;
    int deamon_health=5;
    int fire_health = 10;
    int fire_health2 = 10;
    int giant_health = 15;
    int snake_health = 20;
    int undeed_health = 30;
    int snake_chase=0;
    if(current_user->game_setting.snake_chasing==1){
        snake_chase=1;
    }
    char previous_c;
    int start_normal_arrow=0;  int xfor4, yfor4, counterfor4;int nw=0,na=0,ns=0,nd=0;
    int start_magic_wand=0;  int xfor3, yfor3, counterfor3;int mw=0,ma=0,ms=0,md=0;
    int start_dagger=0;  int xfor2, yfor2, counterfor2; int dw=0,da=0,ds=0,dd=0;
    int is_sth_here[max_y][max_x];
    for(int j=0;j<max_y;j++){
        for(int i=0;i<max_x;i++){
            is_sth_here[j][i]=0;
        }
    }

    int food4health_counter=0;
    int k=1;


    do {
        //print map
        for(int i = 0; i < max_y; i++) {
            for(int j = 0; j < max_x; j++) {
                if(map[i][j] != ' ' && visited[i][j]==1) {

                    if (map[i][j] == '|'){
                        if(room_number[i][j] == colored_room1 || room_number[i][j] == colored_room2) {
                            attron(COLOR_PAIR(41));
                            mvaddch(i, j, map[i][j]);
                            attroff(COLOR_PAIR(41));
                        }
                        else{
                            attron(COLOR_PAIR(5));
                            mvaddch(i, j, map[i][j]);
                            attroff(COLOR_PAIR(5));
                        }
                    } else if (map[i][j] == '.' &&
                               (room_number[i][j] == colored_room1 || room_number[i][j] == colored_room2)) {
                        attron(COLOR_PAIR(40));
                        mvaddch(i, j, map[i][j]);
                        attroff(COLOR_PAIR(40));
                    } else if (map[i][j] == '_'){
                        if(room_number[i][j] == colored_room1 || room_number[i][j] == colored_room2) {
                            attron(COLOR_PAIR(41));
                            mvaddch(i, j, map[i][j]);
                            attroff(COLOR_PAIR(41));
                        }
                        else{
                            mvaddch(i, j, map[i][j]);
                        }
                    } else if (map[i][j] == 'O'){
                        if(room_number[i][j] == colored_room1 || room_number[i][j] == colored_room2) {
                            attron(COLOR_PAIR(41));
                            mvaddch(i, j, map[i][j]);
                            attroff(COLOR_PAIR(41));
                        }
                        else{
                            attron(COLOR_PAIR(5));
                            mvaddch(i, j, map[i][j]);
                            attroff(COLOR_PAIR(5));
                        }
                    } else if (map[i][j] == '#') {

                        mvaddch(i, j, map[i][j]);
                    }
                    else if (map[i][j] == '$') {
                        attron(COLOR_PAIR(6));
                        mvprintw(i, j, "%lc", (wint_t) 0x25C6);
                        attroff(COLOR_PAIR(6));
                    }else if (map[i][j] == '@') {
                        init_color(21, 1000, 400, 1000);
                        init_pair(44,21,COLOR_BLACK);
                        attron(COLOR_PAIR(44));
                        mvprintw(i, j, "%lc", (wint_t) 0x25C6);
                        attroff(COLOR_PAIR(44));
                    }
                    else if (map[i][j] == 'F') {
                        attron(COLOR_PAIR(8));
                        mvaddch(i, j, map[i][j]);
                        attroff(COLOR_PAIR(8));
                    } else if (map[i][j] == 'T') {
                        if(room_number[i][j] == colored_room1 || room_number[i][j] == colored_room2) {
                            attron(COLOR_PAIR(40));
                            mvaddch(i, j, '.');
                            attroff(COLOR_PAIR(40));
                        }
                        else{
                            mvaddch(i, j, '.');
                        }
                    }  else if (map[i][j] == '^') {
                        mvaddch(i, j, map[i][j]);
                    } else if (map[i][j] == '2' || map[i][j] == 'z') {
                        mvprintw(i, j, "%lc", (wint_t) 0x1F5E1); // 🗡 ok
                    } else if (map[i][j] == '3' || map[i][j] == 'x') {
                        attron(COLOR_PAIR(9));
                        mvaddch(i, j, 'W');
                        attroff(COLOR_PAIR(9));
                        // mvprintw(i, j, "%lc", (wint_t)0x1FA84); // 🪄
                    } else if (map[i][j] == '4' || map[i][j] == 'c') {
                        mvprintw(i, j, "%lc", (wint_t) 0x27B3); // ➳ ok
                    } else if (map[i][j] == '5') {
                        attron(COLOR_PAIR(9));
                        mvaddch(i, j, 'S');
                        attroff(COLOR_PAIR(9));
                        //mvprintw(i, j, "%lc", (wint_t)0x2694); // ⚔
                    } else if (map[i][j] == '+' && locked[i][j] == 1) {
                        attron(COLOR_PAIR(10));
                        mvaddch(i, j, '@');
                        attroff(COLOR_PAIR(10));
                    } else if (map[i][j] == '+' && locked[i][j] == 2) {
                        attron(COLOR_PAIR(11));
                        mvaddch(i, j, '@');
                        attroff(COLOR_PAIR(11));
                    }
                    else if (map[i][j] == '=') {
//                        mvprintw(i, j, "%lc", (wint_t) 0x23F9);
                        mvaddch(i, j, '&');
                    } else if (map[i][j] == '/') {
                        attron(COLOR_PAIR(6));
                        mvprintw(i, j, "%lc", (wint_t) 0x25B3);
                        attroff(COLOR_PAIR(6));
                    } else if (map[i][j] == 'b') { //health spell
                        attron(COLOR_PAIR(10));
                        mvprintw(i, j, "%lc", (wint_t)0x271A);
                        attroff(COLOR_PAIR(10));
                    } else if (map[i][j] == 'n') { //speed spell
                        attron(COLOR_PAIR(6));
                        mvprintw(i, j, "%lc", (wint_t) 0x27A4);
                        attroff(COLOR_PAIR(6));
                    } else if (map[i][j] == 'm') { //damage spell
                        init_color(24, 1000, 200, 0);
                        init_pair(45,24,COLOR_BLACK);
                        attron(COLOR_PAIR(45));
                        mvprintw(i, j, "%lc", (wint_t) 0x23FA);
                        attroff(COLOR_PAIR(45));
                    }
                    else if (map[i][j] == '+'){
                        if(room_number[i][j] == colored_room1 || room_number[i][j] == colored_room2) {
                            attron(COLOR_PAIR(41));
                            mvaddch(i, j, map[i][j]);
                            attroff(COLOR_PAIR(41));
                        }
                        else{
                            attron(COLOR_PAIR(5));
                            mvaddch(i, j, map[i][j]);
                            attroff(COLOR_PAIR(5));
                        }
                    }else if(map[i][j]!='1') {
                        if ((room_number[i][j] == colored_room1 || room_number[i][j] == colored_room2)) {
                            attron(COLOR_PAIR(41));
                            mvaddch(i, j, map[i][j]);
                            attroff(COLOR_PAIR(41));

                        } else {
                            mvaddch(i, j, map[i][j]);
                        }
                    }
                }
            }
        }



        int new_y = y;
        int new_x = x;

        if(c=='h'){
            help();
        }

        if(c=='i'){
            clear();
            in_use_weapon= weapon(current_user,in_use_weapon);

        }

        if(c ==101) { ///food window
            clear();
            int p= food_bar(&food1, &health, &food);
            if(p==3){
                continue;
            }
            c = getch();
        }

        ///movement
        mvprintw(2,max_x-30,"[h] to open help menu");

        if(current_user->spells.speed_spell_counter>0){
            if (c == KEY_UP && y > 0) new_y-=2;
            if (c == KEY_DOWN && y < max_y - 1) new_y+=2;
            if (c == KEY_RIGHT && x < max_x - 1) new_x+=2;
            if (c == KEY_LEFT && x > 0) new_x-=2;
            current_user->spells.speed_spell_counter-=1;
            if(current_user->spells.speed_spell_counter==0) current_user->spells.speed_spell_counter=0;
        }
        else{
            if (c == KEY_UP && y > 0) new_y--;
            if (c == KEY_DOWN && y < max_y - 1) new_y++;
            if (c == KEY_RIGHT && x < max_x - 1) new_x++;
            if (c == KEY_LEFT && x > 0) new_x--;

        }

        if(current_user->spells.damage_spell_counter>0){
            k=2;
            current_user->spells.damage_spell_counter-=1;
            if (current_user->spells.damage_spell_counter<0) current_user->spells.damage_spell_counter=0;
        } else {
            k=1;
        }





        if( (map[new_y][new_x] == '+' && (locked[new_y][new_x]==0 || locked[new_y][new_x]==2)) || map[new_y][new_x] == '$'|| map[new_y][new_x] == '@' || map[new_y][new_x] == '.' ||
            map[new_y][new_x] == '#'  || map[new_y][new_x] == 'F' || map[new_y][new_x]=='T' || map[new_y][new_x]=='^' ||
            map[new_y][new_x] == '1'  || map[new_y][new_x] == '2' || map[new_y][new_x]=='3' || map[new_y][new_x]=='4' ||
            map[new_y][new_x] == '5'  || map[new_y][new_x]=='=' || map[new_y][new_x]=='/' || map[new_y][new_x]=='z'||
            map[new_y][new_x] == 'x'  || map[new_y][new_x] == 'c' || map[new_y][new_x] == 'b' || map[new_y][new_x] == 'n'||
            map[new_y][new_x] == 'm') {


            if(map[new_y][new_x]=='b'){
                mvprintw(2,3,"You claimed a Health potion              ");
                current_user->spells.health_spell++;
            }

            if(map[new_y][new_x]=='n'){
                mvprintw(2,3,"You claimed a Speed potion              ");
                current_user->spells.speed_spell++;

            }

            if(map[new_y][new_x]=='m'){
                mvprintw(2,3,"You claimed a Damage potion              ");
                current_user->spells.damage_spell++;
            }

            if(map[new_y][new_x]=='/'){
                mvprintw(2,3,"You found an Ancient Key !              ");
                no_lock=1;
            }

            if(map[new_y][new_x]=='=' && password_counter<=3){
                char arrpass[]="0123456789";
                for(int i9=0;i9<4;i9++){
                    int temp=rand() % 9;
                    password[i9]=arrpass[temp];
                }
                mvprintw(2,3,"Password is %s                                           ",password);

            }

            if(map[new_y][new_x] == '$'){
                int temp = 2 + (rand() % 3 );
                mvprintw(2,3,"You claimed %d GOLDS !            ",temp);
                total_yellow_gold+= temp;
            }
            if(map[new_y][new_x] == '@'){
                int temp = 6 + (rand() % 4 );
                mvprintw(2,3,"You claimed %d GOLDS !            ",temp);
                total_black_gold+= temp;
            }
            if(map[new_y][new_x] == 'F'){
                int temp = 1;
                mvprintw(2,3,"You claimed %d FOOD !             ",temp);
                food1+= 1;
                if(food1>5){
                    food1=5;
                }
            }


            if(map[new_y][new_x] == 'T'){
                int temp = 1;
                mvprintw(2,3,"You stepped on a TRAP !           ",temp);

                if(current_user->game_setting.game_level==0){
                    health -= 1;
                }
                else{
                    health -= 2;
                }
                if(health<0){
                    health=0;
                }
                refresh();
                map[new_y][new_x]='^';
            }

            current_user->weapons.Mace=1;

            if(map[new_y][new_x] == '2'){
                current_user->weapons.Dagger=1;
                mvprintw(2,3,"You found a Dagger! +10                  ");
                current_user->weapons.Dagger_count+=10;
            }
            if(map[new_y][new_x] == 'z'){
                current_user->weapons.Dagger=1;
                mvprintw(2,3,"You found a Dagger! +1                  ");
                current_user->weapons.Dagger_count+=1;
            }


            if(map[new_y][new_x] == '3'){
                current_user->weapons.Magic_Wand=1;
                mvprintw(2,3,"You found a Magic Wand! +8             ");
                current_user->weapons.Magic_Wand_count+=8;
            }
            if(map[new_y][new_x] == 'x'){
                current_user->weapons.Magic_Wand=1;
                mvprintw(2,3,"You found a Magic Wand! +1             ");
                current_user->weapons.Magic_Wand_count+=1;
            }


            if(map[new_y][new_x] == '4'){
                current_user->weapons.Normal_Arrow=1;
                mvprintw(2,3,"You found a Normal Arrow! +20          ");
                current_user->weapons.Normal_Arrow_count+=20;
            }
            if(map[new_y][new_x] == 'c'){
                current_user->weapons.Normal_Arrow=1;
                mvprintw(2,3,"You found a Normal Arrow! +1          ");
                current_user->weapons.Normal_Arrow_count+=1;
            }


            if(map[new_y][new_x] == '5'){
                current_user->weapons.Sword=1;
                mvprintw(2,3,"You found a Sword!                   ");
            }
            y = new_y;
            x = new_x;
        }
        mvprintw(3,3,"                                                      ",password);

        if(map[y][x]!='+' && map[y][x]!='#'&&map[y][x]!='^' && map[y][x]!='='){
            map[y][x]='.';
        }

        if(c=='o'){
            potion(current_user);
        }

        mvprintw(max_y-2,max_x-10,"GOLD: %d",current_user->new_golds+total_black_gold+total_yellow_gold);



        //deamon ////////

        if(deamon_health>0){

            if(room_number[new_y][new_x]==room_number[yd][xd]){
                move_deamon(yd,xd);
            }

            if(deamon_health>0 && xd==new_x && yd==new_y){
                if(current_user->game_setting.game_level==0){
                    health -= 1;
                } else{
                    health -= 2;
                }
                mvprintw(3,3,"Deamon hits you!                            ");
                if(health<0){
                    health=0;
                }
            }
            refresh();

        }

        ////////--------------------------

        int new_x_f2 , new_y_f2;
        int fx2 = new_x - xf2;
        int fy2 = new_y - yf2;
        if(current_user->game_setting.game_level==2){

            if(fire_health2>0){

                if(room_number[new_y][new_x] == room_number[yf2][xf2]  ) {

                    new_x_f2 = xf2;
                    new_y_f2 = yf2;

                    if((abs(fx2)<=6 || abs(fy2)<=6 )){
                        if (abs(fx2) > abs(fy2)) {
                            if (fx2 > 0) {
                                new_x_f2 += 1;
                            } else {
                                new_x_f2 -= 1;
                            }
                        } else {
                            if (fy > 0) {
                                new_y_f2 += 1;
                            } else {
                                new_y_f2 -= 1;
                            }
                        }

                    }

                    if(map[new_y_f2][new_x_f2]!=' '){
                        move_fire_breathing_monster(new_y_f2, new_x_f2);

                    }
                }
                refresh();

                if(fire_health2>=0 && new_x_f2==new_x && new_y_f2==new_y){
                    if(current_user->game_setting.game_level==0){
                        health -= 1;
                    } else{
                        health -= 2;
                    }
                    mvprintw(3,3,"Fire breathing monster hits you!                       ");
                    if(health<0){
                        health=0;
                    }
                }

            }
        }



        //fire breathing monster//////////////
        int new_x_f , new_y_f;
        int fx = new_x - xf;
        int fy = new_y - yf;

        if(fire_health>0){

            if(room_number[new_y][new_x] == room_number[yf][xf]  ) {

                new_x_f = xf;
                new_y_f = yf;

                if((abs(fx)<=3 || abs(fy)<=3 )){
                    if (abs(fx) > abs(fy)) {
                        if (fx > 0) {
                            new_x_f += 1;
                        } else {
                            new_x_f -= 1;
                        }
                    } else {
                        if (fy > 0) {
                            new_y_f += 1;
                        } else {
                            new_y_f -= 1;
                        }
                    }

                }

                if(map[new_y_f][new_x_f]!=' '){
                    move_fire_breathing_monster(new_y_f, new_x_f);

                }            }
            refresh();

            if(fire_health>=0 && new_x_f==new_x && new_y_f==new_y){
                if(current_user->game_setting.game_level==0){
                    health -= 1;
                } else{
                    health -= 2;
                }
                mvprintw(3,3,"Fire breathing monster hits you!                       ");
                if(health<0){
                    health=0;
                }
            }


        }


        //////----------------------
        ////snake////////////////////////
        int new_y_s;
        int new_x_s;
        if(room_number[new_y][new_x]==room_number[ys][xs] && snake_health>0){
            snake_chase=1;

        }
        if(snake_chase==1 && snake_health>0){
            new_x_s = previous_x;
            new_y_s = previous_y;
            refresh();
            if(map[new_y_s][new_x_s]!=' '){
                move_snake(new_y_s,new_x_s );
            }
        }

        if(snake_health>0 && new_x_s==new_x && new_y_s==new_y){
            if(current_user->game_setting.game_level==0){
                health -= 1;
            } else{
                health -= 2;
            }
            mvprintw(3,3,"Snake hits you!                                 ");
            if(health<0){
                health=0;
            }
        }
        refresh();

        ////////////---------------------//

        draw_character(y, x, current_user->game_setting.player_color);

        //health
        if(current_user->game_setting.game_level==0){
            if(counter==40){
                health--;
                counter=0;
            }
        }
        else if(current_user->game_setting.game_level==1){
            if(counter==25){
                health--;
                counter=0;
            }
        }
        else if(current_user->game_setting.game_level==2){
            if(counter==15){
                health--;
                counter=0;
            }
        }

        if(current_user->game_setting.game_level==0){
            if(counter==30){
                food--;
            }
        }
        else if(current_user->game_setting.game_level==1){
            if(counter==20){
                food--;
            }
        }
        else if(current_user->game_setting.game_level==2){
            if(counter==10){
                food--;
            }
        }
        if(health==0){
            current_user->new_golds+=total_black_gold+total_yellow_gold;
            current_user->total_gold+=current_user->new_golds;
            return 0;
        }

        int dx = xd - new_x;
        int dy = yd - new_y;
        fx = new_x_f -  new_x;
        fy = new_y_f - new_y;
        if(current_user->game_setting.game_level==2){
            fx2 = new_x_f2 -  new_x;
            fy2 = new_y_f2 - new_y;
        }
        int sx = new_x_s -  new_x;
        int sy = new_y_s - new_y;

        if(c=='p' || c=='P') {
            if (in_use_weapon == 1) {
                if ((abs(dy) == 1 || abs(dy) == -1 || abs(dy) == 0) &&
                    (abs(dx) == 1 || abs(dx) == -1 || abs(dx) == 0)) {
                    deamon_health -= 5*k;
                    if (deamon_health <= 0) {
                        deamon_health = 0;
                    }
                    mvprintw(3, 3, "You hit Deamon!  health: %d/5                           ", deamon_health);


                }
                if ((abs(fy) == 1 || abs(fy) == -1 || abs(fy) == 0) &&
                    (abs(fx) == 1 || abs(fx) == -1 || abs(fx) == 0)) {
                    fire_health -= 5*k;
                    if (fire_health <= 0) {
                        fire_health = 0;
                    }
                    mvprintw(3, 3, "You hit Fire breathing monster!  health: %d/10                   ", fire_health);


                }
                if ((abs(fy2) == 1 || abs(fy2) == -1 || abs(fy2) == 0) &&
                    (abs(fx2) == 1 || abs(fx2) == -1 || abs(fx2) == 0) && current_user->game_setting.game_level==2) {
                    fire_health2 -= 5*k;
                    if (fire_health2 <= 0) {
                        fire_health2 = 0;
                    }
                    mvprintw(3, 3, "You hit Fire breathing monster!  health: %d/10                   ", fire_health2);


                }
                if ((abs(sy) == 1 || abs(sy) == -1 || abs(sy) == 0) &&
                    (abs(sx) == 1 || abs(sx) == -1 || abs(sx) == 0)) {
                    snake_health -= 5*k;
                    if (snake_health <= 0) {
                        snake_health = 0;
                    }
                    mvprintw(3, 3, "You hit Snake!  health: %d/20                                    ", snake_health);

                }
            }
            if(in_use_weapon==5){
                if ((abs(dy) == 1 || abs(dy) == -1 || abs(dy) == 0) &&
                    (abs(dx) == 1 || abs(dx) == -1 || abs(dx) == 0)) {
                    deamon_health -= 10*k;
                    if (deamon_health <= 0) {
                        deamon_health = 0;
                    }
                    mvprintw(3, 3, "You hit Deamon!  health: %d/5                           ", deamon_health);

                }
                if ((abs(fy) == 1 || abs(fy) == -1 || abs(fy) == 0) &&
                    (abs(fx) == 1 || abs(fx) == -1 || abs(fx) == 0)) {
                    fire_health -= 10*k;
                    if (fire_health <= 0) {
                        fire_health = 0;
                    }
                    mvprintw(3, 3, "You hit Fire breathing monster!  health: %d/10                   ", fire_health);


                }
                if ((abs(fy2) == 1 || abs(fy2) == -1 || abs(fy2) == 0) &&
                    (abs(fx2) == 1 || abs(fx2) == -1 || abs(fx2) == 0) && current_user->game_setting.game_level==2) {
                    fire_health2 -= 5*k;
                    if (fire_health2 <= 0) {
                        fire_health2 = 0;
                    }
                    mvprintw(3, 3, "You hit Fire breathing monster!  health: %d/10                   ", fire_health2);


                }
                if ((abs(sy) == 1 || abs(sy) == -1 || abs(sy) == 0) &&
                    (abs(sx) == 1 || abs(sx) == -1 || abs(sx) == 0)) {
                    snake_health -= 10*k;
                    if (snake_health <= 0) {
                        snake_health = 0;
                    }
                    mvprintw(3, 3, "You hit Snake!  health: %d/20                                    ", snake_health);

                }
            }
        }

        ///////////dagger
        if(in_use_weapon == 2 && previous_c == 'p') {
            start_dagger = 1;
            xfor2 = new_x;
            yfor2 = new_y;
            counterfor2 = 1;
            switch (c) {
                case 'a':
                    da++; break;
                case 'w':
                    dw++; break;
                case 's':
                    ds++; break;
                case 'd':
                    dd++; break;
            }

            current_user->weapons.Dagger_count--;
            if(current_user->weapons.Dagger_count < 0) {
                current_user->weapons.Dagger_count = 0;
            }
        }

        if(start_dagger == 1 && counterfor2 > 0) {

            if(xfor2 == new_x_f && yfor2 == new_y_f) {
                fire_health -= 10*k;
                if(fire_health <= 0) fire_health = 0;
                mvprintw(3, 3, "You hit Fire breathing monster!  health: %d/10                   ", fire_health);
                counterfor2=0;
                start_dagger=0;
            }
            if(xfor2 == new_x_f2 && yfor2 == new_y_f2 && current_user->game_setting.game_level==2) {
                fire_health2 -= 10*k;
                if(fire_health2 <= 0) fire_health2 = 0;
                mvprintw(3, 3, "You hit Fire breathing monster!  health: %d/10                   ", fire_health2);
                counterfor2=0;
                start_dagger=0;
            }

            if(xfor2 == new_x_s && yfor2 == new_y_s) {
                snake_health -= 10*k;
                if(snake_health <= 0) snake_health = 0;
                mvprintw(3, 3, "You hit Snake!  health: %d/20                                    ", snake_health);
                counterfor2=0;start_dagger=0;
            }
            if(xfor2 == xd && yfor2 == yd) {
                deamon_health -= 10*k;
                if(deamon_health <= 0) deamon_health = 0;
                mvprintw(3, 3, "You hit Deamon!  health: %d/5                           ", deamon_health);
                counterfor2=0;
                start_dagger=0;
            }

            if(da==1) {
                xfor2--;
                if(map[yfor2][xfor2]=='|' || map[yfor2][xfor2]=='_'){
                    counterfor2=0;
                    if(map[yfor2][xfor2+1]=='.')
                    {
                        map[yfor2][xfor2+1]='z';
                    }
                }
            }
            else if(ds==1) {
                yfor2++;
                if(map[yfor2][xfor2]=='|' || map[yfor2][xfor2]=='_'){
                    counterfor2=0;
                    if(map[yfor2-1][xfor2]=='.')
                    {
                        map[yfor2-1][xfor2]='z';
                    }
                }
            }
            else if(dd==1) {
                xfor2++;
                if(map[yfor2][xfor2]=='|' || map[yfor2][xfor2]=='_'){
                    counterfor2=0;
                    if(map[yfor2][xfor2-1]=='.')
                    {
                        map[yfor2][xfor2-1]='z';
                    }
                }
            }
            else if(dw==1) {
                yfor2--;
                if(map[yfor2][xfor2]=='|' || map[yfor2][xfor2]=='_'){
                    counterfor2=0;
                    if(map[yfor2+1][xfor2]=='.')
                    {
                        map[yfor2+1][xfor2]='z';
                    }
                }
            }

            counterfor2++;
            if(counterfor2 >= 5) {
                if(map[yfor2][xfor2]=='.'){
                    map[yfor2][xfor2]='z'; // z represents 1 dagger
                }
                start_dagger = 0;
                counterfor2 = 0;
                dd=0; da=0; dw=0; ds=0;
            }
            if(map[yfor2][xfor2]=='.'){
                mvaddch(yfor2, xfor2, '*');
            }
            refresh();
        }
        ////////////


        ///////////normal arrow
        if(in_use_weapon == 4 && previous_c == 'p') {
            start_normal_arrow = 1;
            xfor4 = new_x;
            yfor4 = new_y;
            counterfor4 = 1;
            switch (c) {
                case 'a':
                    na++; break;
                case 'w':
                    nw++; break;
                case 's':
                    ns++; break;
                case 'd':
                    nd++; break;
            }

            current_user->weapons.Normal_Arrow_count--;
            if(current_user->weapons.Normal_Arrow_count < 0) {
                current_user->weapons.Normal_Arrow_count = 0;
            }
        }

        if(start_normal_arrow == 1 && counterfor4 > 0) {

            if(xfor4 == new_x_f && yfor4 == new_y_f) {
                fire_health -= 10*k;
                if(fire_health <= 0) fire_health = 0;
                mvprintw(3, 3, "You hit Fire breathing monster!  health: %d/10                   ", fire_health);
                counterfor4=0;
                start_normal_arrow=0;
            }
            if(xfor4 == new_x_f2 && yfor4 == new_y_f2 && current_user->game_setting.game_level==2) {
                fire_health2 -= 10*k;
                if(fire_health2 <= 0) fire_health2 = 0;
                mvprintw(3, 3, "You hit Fire breathing monster!  health: %d/10                   ", fire_health2);
                counterfor4=0;
                start_normal_arrow=0;
            }

            if(xfor4 == new_x_s && yfor2 == new_y_s) {
                snake_health -= 10*k;
                if(snake_health <= 0) snake_health = 0;
                mvprintw(3, 3, "You hit Snake!  health: %d/20                                    ", snake_health);
                counterfor4=0;
                start_normal_arrow=0;
            }
            if(xfor4 == xd && yfor4== yd) {
                deamon_health -= 10*k;
                if(deamon_health <= 0) deamon_health = 0;
                mvprintw(3, 3, "You hit Deamon!  health: %d/5                           ", deamon_health);
                counterfor4=0;
                start_normal_arrow=0;
            }

            if(na==1) {
                xfor4--;
                if(map[yfor4][xfor4]=='|' || map[yfor4][xfor4]=='_'){
                    counterfor4=0;
                    if(map[yfor4][xfor4+1]=='.')
                    {
                        map[yfor4][xfor4+1]='c';
                    }
                }
            }
            else if(ns==1) {
                yfor4++;
                if(map[yfor4][xfor4]=='|' || map[yfor4][xfor4]=='_'){
                    counterfor4=0;
                    if(map[yfor4-1][xfor4]=='.')
                    {
                        map[yfor4-1][xfor4]='c';
                    }
                }
            }
            else if(nd==1) {
                xfor4++;
                if(map[yfor4][xfor4]=='|' || map[yfor4][xfor4]=='_'){
                    counterfor4=0;
                    if(map[yfor4][xfor4-1]=='.')
                    {
                        map[yfor4][xfor4-1]='c';
                    }
                }
            }
            else if(nw==1) {
                yfor4--;
                if(map[yfor4][xfor4]=='|' || map[yfor4][xfor4]=='_'){
                    counterfor4=0;
                    if(map[yfor4+1][xfor4]=='.')
                    {
                        map[yfor4+1][xfor4]='c';
                    }
                }
            }

            counterfor4++;
            if(counterfor4 >= 5) {
                if(map[yfor4][xfor4]=='.'){
                    map[yfor4][xfor4]='c'; // c represents 1 normal arrow
                }
                start_normal_arrow = 0;
                counterfor4 = 0;
                nd=0; na=0; nw=0; ns=0;
            }
            if(map[yfor4][xfor4]=='.'){
                mvaddch(yfor4, xfor4, '-');
            }

            refresh();
        }
        ////////////

        ///////////Magic wand
        if(in_use_weapon == 3 && previous_c == 'p') {
            start_magic_wand = 1;
            xfor3 = new_x;
            yfor3 = new_y;
            counterfor3 = 1;
            switch (c) {
                case 'a':
                    ma++; break;
                case 'w':
                    mw++; break;
                case 's':
                    ms++; break;
                case 'd':
                    md++; break;
            }

            current_user->weapons.Magic_Wand_count--;
            if(current_user->weapons.Magic_Wand_count < 0) {
                current_user->weapons.Magic_Wand_count = 0;
            }
        }

        if(start_magic_wand == 1 && counterfor3 > 0) {

            if(xfor3 == new_x_f && yfor3 == new_y_f) {
                fire_health -= 15*k;
                if(fire_health <= 0) fire_health = 0;
                mvprintw(3, 3, "You hit Fire breathing monster!  health: %d/10                   ", fire_health);
                counterfor3=0;
                start_magic_wand=0;
            }
            if(xfor3 == new_x_f2 && yfor3 == new_y_f2 && current_user->game_setting.game_level==2) {
                fire_health2 -= 15*k;
                if(fire_health2 <= 0) fire_health2 = 0;
                mvprintw(3, 3, "You hit Fire breathing monster!  health: %d/10                   ", fire_health2);
                counterfor3=0;
                start_magic_wand=0;
            }
            if(xfor3 == new_x_s && yfor3 == new_y_s) {
                snake_health -= 15*k;
                if(snake_health <= 0) snake_health = 0;
                mvprintw(3, 3, "You hit Snake!  health: %d/20                                    ", snake_health);
                counterfor3=0;
                snake_chase=0;
                start_magic_wand=0;
            }
            if(xfor3 == xd && yfor3 == yd) {
                deamon_health -= 15*k;
                if(deamon_health <= 0) deamon_health = 0;
                mvprintw(3, 3, "You hit Deamon!  health: %d/5                           ", deamon_health);
                counterfor3=0;
                start_magic_wand=0;
            }

            if(ma==1) {
                xfor3--;
                if(map[yfor3][xfor3]=='|' || map[yfor3][xfor3]=='_'){
                    counterfor3=0;
                    if(map[yfor3][xfor3+1]=='.')
                    {
                        map[yfor3][xfor3+1]='x';
                    }
                }
            }
            else if(ms==1) {
                yfor3++;
                if(map[yfor3][xfor3]=='|' || map[yfor3][xfor3]=='_'){
                    counterfor3=0;
                    if(map[yfor3-1][xfor3+1]=='.')
                    {
                        map[yfor3-1][xfor3+1]='x';
                    }
                }
            }
            else if(md==1) {
                xfor3++;
                if(map[yfor3][xfor3]=='|' || map[yfor3][xfor3]=='_'){
                    counterfor3=0;
                    if(map[yfor3][xfor3-1]=='.')
                    {
                        map[yfor3][xfor3-1]='x';
                    }
                }
            }
            else if(mw==1) {
                yfor3--;
                if(map[yfor3][xfor3]=='|' || map[yfor3][xfor3]=='_'){
                    counterfor3=0;
                    if(map[yfor3+1][xfor3]=='.')
                    {
                        map[yfor3+1][xfor3]='x';
                    }
                }
            }

            counterfor3++;
            if(counterfor3 >= 5) {
                if(map[yfor3][xfor3]=='.'){
                    map[yfor3][xfor3]='x'; // x represents 1 magic wand
                }
                start_magic_wand = 0;
                counterfor3 = 0;
                md=0; ma=0; mw=0; ms=0;
            }
            if(map[yfor3][xfor3]=='.'){
                mvaddch(yfor3, xfor3, '+');
            }
            mvprintw(2, 3, "                                                            ");
            refresh();
        }
        ////////////





        //door code
        int status=2;
        init_pair(12,COLOR_YELLOW,COLOR_BLACK);
        init_pair(13,COLOR_MAGENTA,COLOR_BLACK);
        init_pair(14,COLOR_RED,COLOR_BLACK);




        if(locked[cordinate_locked[0]][cordinate_locked[1]]==1 && (new_y+1==cordinate_locked[0] && new_x==cordinate_locked[1] ||
                                                                   new_y-1==cordinate_locked[0] && new_x==cordinate_locked[1] ||
                                                                   new_y==cordinate_locked[0] && new_x+1==cordinate_locked[1] ||
                                                                   new_y==cordinate_locked[0] && new_x-1==cordinate_locked[1] )){
            if (no_lock==0){
                if(password_counter>3){
                    attron(COLOR_PAIR(14));
                    mvprintw(3,3,"The door has been locked forever!!                   ");
                    attroff(COLOR_PAIR(14));
                }
                else {
                    mvprintw(3,3,"The door is locked. Press L to enter the pass !");
                }
                if(c=='l' && password_counter<=3){
                    status=code(password);
                    password_counter++;
                }
                if(status==1 && password_counter<=3 ){
                    locked[cordinate_locked[0]][cordinate_locked[1]]=2;
                    mvprintw(3,3,"The door is unlocked !                                       ");

                }
                else if(status==0 && password_counter<=3){
                    if(password_counter==1){
                        attron(COLOR_PAIR(12));
                        mvprintw(3,3,"Wrong password!                                ");
                        attroff(COLOR_PAIR(12));
                    }
                    else if(password_counter==2){
                        attron(COLOR_PAIR(13));
                        mvprintw(3,3,"Wrong password!                                ");
                        attroff(COLOR_PAIR(13));
                    }
                    else if(password_counter==3){
                        attron(COLOR_PAIR(14));
                        mvprintw(3,3,"Wrong password! Door locked forever!!                          ");
                        attroff(COLOR_PAIR(14));
                    }
                }


            }
            else if(no_lock==1){
                locked[cordinate_locked[0]][cordinate_locked[1]]=2;
                mvprintw(3,3,"The door is unlocked !                                       ");
                mvprintw(3,3,"                                                            ");
            }


        }
        if(counter==40){
            strcpy(password,"0");
        }
        if(food>=10){
            if(food4health_counter>=4){
                if(current_user->spells.health_spell_counter>0){
                    health+=2;
                    current_user->spells.health_spell_counter-=1;
                    if(current_user->spells.health_spell_counter<0) current_user->spells.health_spell_counter=0;
                }
                else{
                    health+=1;
                }
                if(health>10) health=10;
                food4health_counter=0;
            }
        }

        mvprintw(max_y-2,60,"floor : 2");

        //health
        mvprintw(max_y-2,2,"health: ");
        refresh();
        for(int i =0;i<=health;i++){
            mvprintw(max_y-2,10+i,"♥");
            mvprintw(max_y-2,10+health," ");
            for(int j=0;j<10-i;j++){
                mvprintw(max_y-2,10+health+j," ");
            }
            mvprintw(max_y-2,10+12,"%d%c",health*10,'%');

        }

        //food
        mvprintw(max_y-2,32,"food: ");

        for(int i =0;i<=food;i++){
            mvprintw(max_y-2,38+i,"+");
            mvprintw(max_y-2,38+food," ");
            mvprintw(max_y-2,38 + 12,"     ");
            mvprintw(max_y-2,38 + 12,"%d%c",food*10,'%');
            refresh();
        }
        refresh();

        if(in_use_weapon==1){
            mvprintw(max_y-2,74,"weapon: Mace");
        }
        else if(in_use_weapon==2){
            mvprintw(max_y-2,74,"weapon: Dagger");
        }
        else if(in_use_weapon==3){
            mvprintw(max_y-2,74,"weapon: Magic Wand");
        }
        else if(in_use_weapon==4){
            mvprintw(max_y-2,74,"weapon: Normal Arrow");
        }
        else if(in_use_weapon==4){
            mvprintw(max_y-2,74,"weapon: Sword");
        }
        else {
            mvprintw(max_y-2,74,"weapon: no weapon in use!");
        }


        counter++;


        refresh();
        if( map[new_y][new_x]=='#'){
            int temp = cori_number[new_y][new_x];
            for(int j=-4;j<4;j++){
                for(int i=-4;i<4;i++){
                    if(cori_number[new_y+j][new_x+i]==temp && map[new_y+j][new_x+i]=='#' && visited[new_y+j][new_x+i]!=1 || map[new_y+j][new_x+i]=='+'){
                        visited[new_y+j][new_x+i]=1;
                    }
                }
            }
        }

        else if(map[new_y][new_x]=='+' &&(map[new_y+1][new_x]=='.' || map[new_y-1][new_x]=='.' || map[new_y][new_x+1]=='.' || map[new_y][new_x-1]=='.' )){
            int tempp=room_number[new_y][new_x];
            for(int j1=0;j1<max_y;j1++){
                for (int i1 = 0; i1 < max_x; i1++) {
                    if(visited[j1][i1]!=1 && room_number[j1][i1]==tempp){
                        visited[j1][i1]=1;
                    }
                }
            }
        }

        if(map[new_y][new_x]=='<'){
            current_user->food=food;
            current_user->health=health;
            current_user->food1=food1;
            current_user->new_golds+=total_black_gold+total_yellow_gold;
            current_user->weapons.in_use_weapon=in_use_weapon;
            if(snake_chase==1) current_user->game_setting.snake_chasing=1;
            else current_user->game_setting.snake_chasing=0;
            return game_f3(current_user, current_user->game_setting.game_level);
        }
        previous_x = new_x;
        previous_y = new_y;
        previous_c =c;
        food4health_counter++;
        refresh();

    } while ((c = getch()) != 27);

    endwin();
}


int game_f3(struct user *current_user , int level) {
    mvprintw(2,1,"  ");
    init_color(30, 333, 333, 333);
    init_pair(40, 30, COLOR_BLACK);
    init_color(31, 0, 1000, 400);
    init_pair(41, 31, COLOR_BLACK);
    init_color(32, 255, 87, 51);
    init_pair(42, 32, COLOR_BLACK);
    init_color(33, 1000, 600, 0);
    init_pair(43, 33, COLOR_BLACK);
    setlocale(LC_ALL, "");
    initscr();
    keypad(stdscr, TRUE);
    noecho();
    curs_set(0);
    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);
    char map[max_y][max_x];

    //--------------------------
    int visited[max_y][max_x];
    for(int j=0;j<max_y;j++){
        for(int i=0;i<max_x;i++){
            visited[j][i]=0;
        }
    }

    int room_number[max_y][max_x];
    for(int j=0;j<max_y;j++){
        for(int i=0;i<max_x;i++){
            room_number[j][i]=0;
        }
    }

    int cori_number[max_y][max_x];
    for(int j=0;j<max_y;j++){
        for(int i=0;i<max_x;i++){
            cori_number[j][i]=0;
        }
    }

//    int hidden_door[max_y][max_x];
//    for(int j=0;j<max_y;j++){
//        for(int i=0;i<max_x;i++){
//            hidden_door[j][i]=0;
//        }
//    }

    ///.........weapons

    int in_use_weapon= current_user->weapons.in_use_weapon;

    //.........................


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
            room_y = 5 + (rand() % (max_y - size_room_y - 8));
            room_x = 5 + (rand() % (max_x - size_room_x - 8));

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
                    room_number[room_y + i][room_x + j]=num+1; //room number
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
            int counterrr=0;

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


                    if(left == '_' && right == '#'){
                        map[y1][current_x] = '+';
                        map[y1][current_x-1] = '+';
                    }

                    else if(left == '#' && right == '_'){
                        map[y1][current_x] = '+';
                        map[y1][current_x+1] = '+';
                    }

                }

                else if (map[y1][current_x] == ' ') {
                    counterrr++;
                    map[y1][current_x] = '#';
                    cori_number[y1][current_x]=num+1;
                    if(counterrr%34==0){
                        if(map[y1+1][current_x]==' ' && y1+1 < max_y-3){
                            map[++y1][current_x]='#';
                            cori_number[y1][current_x]=num+1;
                        }
                        if(map[y1+1][current_x]==' ' && y1+1 < max_y-3){
                            map[++y1][current_x]='#';
                            cori_number[y1][current_x]=num+1;
                        }
                        if(map[y1+1][current_x]==' ' && y1+1 < max_y-3){
                            map[++y1][current_x]='#';
                            cori_number[y1][current_x]=num+1;
                        }
                        counterrr=0;
                    }

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
                    }
                    else if(down == '|' && up == '#'){
                        map[current_y][x2] = '+';
                        map[current_y+1][x2] = '+';
                    }

                }
                else if (map[current_y][x2] == ' ') {
                    map[current_y][x2] = '#';
                    cori_number[current_y][x2]=num+1;
                }
            }
        }


        num++;
    }

    //////////////////////
    //hidden door
//    int hidden; int hx; int hy;
//    while (!hidden){
//        hy = rand() % max_y  + 1;
//        hx = rand() % max_x  + 1;
//        int doornum=0;
//        for(int j=0;j<max_y;j++){
//            for(int i=0;i<max_x;i++){
//                if(room_number[j][i]==room_number[hy][hx]){
//                    if(map[j][i]=='+'){
//                        doornum++;
//                    }
//                }
//            }
//        }
//        if(doornum==1){
//            if(map[hy][hx]=='+'){
//                hidden_door[hy][hx]=1;
//                hidden++;
//            }
//        }
//    }
//
//    int verorho;
//    if(map[hy+1][hx]=='|' && map[hy-1][hx]=='|'){
//        verorho=1;
//    }else{
//        verorho=0;
//    }


    //pillars
    int num_pillars= 6+ (rand() % 4);
    int np=0 ,py ,px;
    while(np<num_pillars){
        py = rand() % max_y  + 1;
        px = rand() % max_x  + 1;
        if(map[py][px]=='.' && map[py+1][px]!='+' && map[py][px-1]!='+' && map[py][px+1]!='+' && map[py-1][px]!='+'){
            map[py][px]='O';
            np++;
        }
    }
    //traps
    int num_traps;
    if(current_user->game_setting.game_level==0){
        num_traps= 4 + (rand() % 2);
    }
    else if(current_user->game_setting.game_level==1){
        num_traps= 7 + (rand() % 5);
    }
    else if(current_user->game_setting.game_level==2){
        num_traps= 10 + (rand() % 7);
    }
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
    int num_foods;
    if(current_user->game_setting.game_level==0){
        num_foods= 10 + (rand() % 4);
    }
    else if(current_user->game_setting.game_level==1){
        num_foods= 7 + (rand() % 2);
    }
    else if(current_user->game_setting.game_level==2){
        num_foods= 5 + (rand() % 1);
    }

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
    int num_ygolds= 9 + (rand() % 4);
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
    int num_bgolds= 5 + (rand() % 1);
    int nbg=0 ,by ,bx;
    while(nbg<num_bgolds){
        by = rand() % max_y  + 1;
        bx = rand() % max_x  + 1;
        if(map[by][bx]=='.'){
            map[by][bx]='@';
            nbg++;
        }
    }


    int x2 = 0, y2 = 0;
    int stairs = 0;
    while(!stairs) {
        y2 = rand() % max_y  + 1;
        x2 = rand() % max_x  + 1;
        if(map[y2][x2]=='.'){
            map[y2][x2]='<';
            stairs++;
        }
    }
    int y=y2;
    int x=x2;

    int room_num=room_number[y][x];

    for(int i=0;i<max_x;i++){
        for(int j=0;j<max_y;j++){
            if(room_number[j][i]==room_num){
                visited[j][i]=1;
            }
        }
    }

    //weapons
    int weapon_num= 2 + rand() % 3;
    int x3=0,y3=0;
    int weaponi =0 ;
    while(!weaponi){
        y3 = rand() % max_y ;
        x3 = rand() % max_x ;
        if(map[y3][x3]=='.'){
            if(weapon_num==1){
                map[y3][x3]='1';
                weaponi++;
            }
            else if(weapon_num==2){
                map[y3][x3]='2';
                weaponi++;
            }
            else if(weapon_num==3){
                map[y3][x3]='3';
                weaponi++;
            }

            else if(weapon_num==4){
                map[y3][x3]='4';
                weaponi++;
            }

            else if(weapon_num==5){
                map[y3][x3]='5';
                weaponi++;
            }
        }
    }

    weapon_num= 2 + rand() % 4;
    x3=0,y3=0;
    weaponi =0 ;
    while(!weaponi){
        y3 = rand() % max_y ;
        x3 = rand() % max_x ;
        if(map[y3][x3]=='.'){
            if(weapon_num==1){
                map[y3][x3]='1';
                weaponi++;
            }
            else if(weapon_num==2){
                map[y3][x3]='2';
                weaponi++;
            }
            else if(weapon_num==3){
                map[y3][x3]='3';
                weaponi++;
            }

            else if(weapon_num==4){
                map[y3][x3]='4';
                weaponi++;
            }

            else if(weapon_num==5){
                map[y3][x3]='5';
                weaponi++;
            }
        }
    }

    stairs = 0;
    while(!stairs) {
        y2 = rand() % max_y  + 1;
        x2 = rand() % max_x  + 1;
        if(map[y2][x2]=='.'){
            map[y2][x2]='<';
            stairs++;
        }
    }

    /////locked door////////////////
    int locked[max_y][max_x];
    for(int j=0;j<max_y;j++){
        for(int i=0;i<max_x;i++){
            locked[j][i]=0;
        }
    }
    int lock=0;
    int locked_room_num;
    int cordinate_locked[2];
    while(!lock){
        int y4=rand()%max_y;
        int x4=rand()%max_x;
        if(map[y4][x4]=='+' && map[y4+1][x4]!='+' && map[y4-1][x4]!='+' && map[y4][x4+1]!='+' && map[y4][x4-1]!='+'){
            int count=0;
            locked_room_num=room_number[y4][x4];
            for(int j=0;j<max_y;j++){
                for(int i=0; i<max_x;i++){
                    if(map[j][i]=='+' && room_number[j][i]==locked_room_num){
                        count++;
                    }
                }
            }
            if(count==2){
                locked[y4][x4]=1;
                cordinate_locked[0]=y4; cordinate_locked[1]=x4;
                break;
            }
        }
    }



    while(1){
        int y5=rand()%max_y;
        int x5=rand()%max_x;
        if(map[y5][x5]=='.' && room_number[y5][x5]==locked_room_num){
            map[y5][x5]='=';
            break;
        }
    }

    int no_lock=0;
    while(1){
        int y6=rand()%max_y;
        int x6=rand()%max_x;
        if(map[y6][x6]=='.' ){
            map[y6][x6]='/';
            break;
        }
    }



    ////////////////


    ///--->> deamon <<---///
    int xd=0, yd=0;
    int countd=0;
    while (countd==0){
        xd = rand() % max_x;
        yd = rand() % max_y;
        if(map[yd][xd]=='.'){
            countd++;
        }
    }
    ////////////////////////

    ///--->> fire breathing monster <<---///
    int xf=0, yf=0;
    int countf=0;
    while (countf==0){
        xf = rand() % max_x;
        yf = rand() % max_y;
        if(map[yf][xf]=='.'){
            countf++;
        }
    }
    ////////////////////////

    int xs=0, ys=0;
    ///--->> snake <<---///
    if(current_user->game_setting.snake_chasing==1){
        xs = x; ys=y;
    }
    else {
        int counts = 0;
        while (counts == 0) {
            xs = rand() % max_x;
            ys = rand() % max_y;
            if (map[ys][xs] == '.') {
                counts++;
            }
        }
    }
   /////

    ///--->> giant <<---///
    int xg=0, yg=0;
    int countg=0;
    if(current_user->game_setting.game_level==1 || current_user->game_setting.game_level==2 ) {
        while (countg == 0) {
            xg = rand() % max_x;
            yg = rand() % max_y;
            if (map[yg][xg] == '.') {
                countg++;
            }
        }
    }
//    ////////////////////////
//
//
//    ///--->> undeed <<---///
//    int xu=0, yu=0;
//    int countu=0;
//    while (countu==0){
//        xu = rand() % max_x;
//        yu = rand() % max_y;
//        if(map[yu][xu]=='.'){
//            countu++;
//        }
//    }
//    //////////////////////


    int colored_room1 = 1 + rand()% (number_of_rooms-1);
    int colored_room2 = 1 + rand()%( number_of_rooms-1);

// speed spell
    int x_speed_spell=0, y_speed_spell=0;
    int countof= 1+  rand() % 2;
    while (countof!=0){
        x_speed_spell = rand() % max_x;
        y_speed_spell = rand() % max_y;
        if(map[y_speed_spell][x_speed_spell]=='.' && (room_number[y_speed_spell][x_speed_spell]==colored_room1 ||room_number[y_speed_spell][x_speed_spell]==colored_room2) ){
            map[y_speed_spell][x_speed_spell]='n'; //n stands for speed spell
            countof--;
        }
    }
    // health spell
    int x_health_spell=0, y_health_spell=0;
    countof= 1 + rand() % 2;
    while (countof!=0){
        x_health_spell = rand() % max_x;
        y_health_spell = rand() % max_y;
        if(map[y_health_spell][x_health_spell]=='.' && (room_number[y_speed_spell][x_speed_spell]==colored_room1 ||room_number[y_speed_spell][x_speed_spell]==colored_room2)){
            map[y_health_spell][x_health_spell]='b'; //b stands for health spell
            countof--;
        }
    }

    //damage spell
    int x_damage_spell=0, y_damage_spell=0;
    countof= 1 + rand() % 2;
    while (countof!=0){
        x_damage_spell = rand() % max_x;
        y_damage_spell = rand() % max_y;
        if(map[y_damage_spell][x_damage_spell]=='.' && (room_number[y_speed_spell][x_speed_spell]==colored_room1 ||room_number[y_speed_spell][x_speed_spell]==colored_room2)){
            map[y_damage_spell][x_damage_spell]='m'; //m stands for health spell
            countof--;
        }
    }



    clear();

    init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(6, COLOR_YELLOW, COLOR_BLACK);
    init_pair(7, COLOR_BLACK, COLOR_WHITE);
    init_pair(8, COLOR_YELLOW, COLOR_RED);
    init_pair(9, COLOR_CYAN, COLOR_BLACK);
    init_pair(10,COLOR_RED,COLOR_BLACK);
    init_pair(11,COLOR_GREEN,COLOR_BLACK);
    ////////////////////
    int total_yellow_gold=0;
    int total_black_gold=0;
    /////////////////////

    int food=current_user->food;
    int food1=current_user->food1;
    int health=current_user->health;


    ///////////////////////MAIN///////

    // printing map (player movement -- map)
    int c;
    int counter=0;

    char password[100]={0};
    int password_counter=0;
    int previous_x=0 , previous_y=0;
    int deamon_health=5;
    int fire_health = 10;
    int giant_health = 15;
    int snake_health = 20;
    int undeed_health = 30;
    int snake_chase=0;
    char previous_c;
    int start_normal_arrow=0;  int xfor4, yfor4, counterfor4;int nw=0,na=0,ns=0,nd=0;
    int start_magic_wand=0;  int xfor3, yfor3, counterfor3;int mw=0,ma=0,ms=0,md=0;
    int start_dagger=0;  int xfor2, yfor2, counterfor2; int dw=0,da=0,ds=0,dd=0;
    int is_sth_here[max_y][max_x];
    for(int j=0;j<max_y;j++){
        for(int i=0;i<max_x;i++){
            is_sth_here[j][i]=0;
        }
    }
    int food4health_counter=0;
    int k=1;





    do {
        //print map
        for(int i = 0; i < max_y; i++) {
            for(int j = 0; j < max_x; j++) {
                if(map[i][j] != ' ' && visited[i][j]==1) {


                    if (map[i][j] == '|' ){
                        if((room_number[i][j] == colored_room1 || room_number[i][j] == colored_room2) ) {
                            attron(COLOR_PAIR(41));
                            mvaddch(i, j, '|');
                            attroff(COLOR_PAIR(41));
                        }
                        else{
                            attron(COLOR_PAIR(5));
                            mvaddch(i, j, '|');
                            attroff(COLOR_PAIR(5));
                        }
                    } else if (map[i][j] == '.' &&
                               (room_number[i][j] == colored_room1 || room_number[i][j] == colored_room2)) {
                        attron(COLOR_PAIR(40));
                        mvaddch(i, j, map[i][j]);
                        attroff(COLOR_PAIR(40));
                    } else if (map[i][j] == '_' ){
                        if(room_number[i][j] == colored_room1 || room_number[i][j] == colored_room2) {
                            attron(COLOR_PAIR(41));
                            mvaddch(i, j, '_');
                            attroff(COLOR_PAIR(41));
                        }
                        else{
                            mvaddch(i, j, '_');
                        }
                    }
                    else if (map[i][j] == 'O'){
                        if(room_number[i][j] == colored_room1 || room_number[i][j] == colored_room2) {
                            attron(COLOR_PAIR(41));
                            mvaddch(i, j, map[i][j]);
                            attroff(COLOR_PAIR(41));
                        }
                        else{
                            attron(COLOR_PAIR(5));
                            mvaddch(i, j, map[i][j]);
                            attroff(COLOR_PAIR(5));
                        }
                    } else if (map[i][j] == '#') {

                        mvaddch(i, j, map[i][j]);
                    }
                    else if (map[i][j] == '$') {
                        attron(COLOR_PAIR(6));
                        mvprintw(i, j, "%lc", (wint_t) 0x25C6);
                        attroff(COLOR_PAIR(6));
                    } else if (map[i][j] == '@') {
                        init_color(21, 1000, 400, 1000);
                        init_pair(44,21,COLOR_BLACK);
                        attron(COLOR_PAIR(44));
                        mvprintw(i, j, "%lc", (wint_t) 0x25C6);
                        attroff(COLOR_PAIR(44));
                    }
                    else if (map[i][j] == 'F') {
                        attron(COLOR_PAIR(8));
                        mvaddch(i, j, map[i][j]);
                        attroff(COLOR_PAIR(8));
                    }else if (map[i][j] == 'T') {
                        if(room_number[i][j] == colored_room1 || room_number[i][j] == colored_room2) {
                            attron(COLOR_PAIR(40));
                            mvaddch(i, j, '.');
                            attroff(COLOR_PAIR(40));
                        }
                        else{
                            mvaddch(i, j, '.');
                        }
                    }  else if (map[i][j] == '^') {
                        mvaddch(i, j, map[i][j]);
                    } else if (map[i][j] == '2' || map[i][j] == 'z') {
                        mvprintw(i, j, "%lc", (wint_t) 0x1F5E1); // 🗡 ok
                    } else if (map[i][j] == '3' || map[i][j] == 'x') {
                        attron(COLOR_PAIR(9));
                        mvaddch(i, j, 'W');
                        attroff(COLOR_PAIR(9));
                        // mvprintw(i, j, "%lc", (wint_t)0x1FA84); // 🪄
                    } else if (map[i][j] == '4' || map[i][j] == 'c') {
                        mvprintw(i, j, "%lc", (wint_t) 0x27B3); // ➳ ok
                    } else if (map[i][j] == '5') {
                        attron(COLOR_PAIR(9));
                        mvaddch(i, j, 'S');
                        attroff(COLOR_PAIR(9));
                        //mvprintw(i, j, "%lc", (wint_t)0x2694); // ⚔
                    } else if (map[i][j] == '+' && locked[i][j] == 1) {
                        attron(COLOR_PAIR(10));
                        mvaddch(i, j, '@');
                        attroff(COLOR_PAIR(10));
                    } else if (map[i][j] == '+' && locked[i][j] == 2) {
                        attron(COLOR_PAIR(11));
                        mvaddch(i, j, '@');
                        attroff(COLOR_PAIR(11));
                    }


                    else if (map[i][j] == '=') {
//                        mvprintw(i, j, "%lc", (wint_t) 0x23F9);
                        mvaddch(i, j, '&');
                    } else if (map[i][j] == '/') {
                        attron(COLOR_PAIR(6));
                        mvprintw(i, j, "%lc", (wint_t) 0x25B3);
                        attroff(COLOR_PAIR(6));
                    } else if (map[i][j] == 'b') { //health spell
                        attron(COLOR_PAIR(10));
                        mvprintw(i, j, "%lc", (wint_t)0x271A);
                        attroff(COLOR_PAIR(10));
                    } else if (map[i][j] == 'n') { //speed spell
                        attron(COLOR_PAIR(6));
                        mvprintw(i, j, "%lc", (wint_t) 0x27A4);
                        attroff(COLOR_PAIR(6));
                    } else if (map[i][j] == 'm') { //damage spell
                        init_color(24, 1000, 200, 0);
                        init_pair(45,24,COLOR_BLACK);
                        attron(COLOR_PAIR(45));
                        mvprintw(i, j, "%lc", (wint_t) 0x23FA);
                        attroff(COLOR_PAIR(45));
                    }

                    else if (map[i][j] == '+'){
                        if(room_number[i][j] == colored_room1 || room_number[i][j] == colored_room2) {
                            attron(COLOR_PAIR(41));
                            mvaddch(i, j, map[i][j]);
                            attroff(COLOR_PAIR(41));
                        }
                        else{
                            attron(COLOR_PAIR(5));
                            mvaddch(i, j, map[i][j]);
                            attroff(COLOR_PAIR(5));
                        }
                    }
                    else if(map[i][j]!='1') {
                        if ((room_number[i][j] == colored_room1 || room_number[i][j] == colored_room2)) {
                            attron(COLOR_PAIR(41));
                            mvaddch(i, j, map[i][j]);
                            attroff(COLOR_PAIR(41));

                        } else {
                            mvaddch(i, j, map[i][j]);
                        }
                    }
                }
            }
        }



        int new_y = y;
        int new_x = x;

        if(c=='h'){
            help();
        }

        if(c=='i'){ //weapon
            clear();
            in_use_weapon= weapon(current_user,in_use_weapon);

        }

        if(c ==101) { ///food window
            clear();
            int p= food_bar(&food1, &health, &food);
            if(p==3){
                continue;
            }
            c = getch();
        }
        ///movement

        if(current_user->spells.speed_spell_counter>0){
            if (c == KEY_UP && y > 0) new_y-=2;
            if (c == KEY_DOWN && y < max_y - 1) new_y+=2;
            if (c == KEY_RIGHT && x < max_x - 1) new_x+=2;
            if (c == KEY_LEFT && x > 0) new_x-=2;
            current_user->spells.speed_spell_counter-=1;
            if(current_user->spells.speed_spell_counter==0) current_user->spells.speed_spell_counter=0;
        }
        else{
            if (c == KEY_UP && y > 0) new_y--;
            if (c == KEY_DOWN && y < max_y - 1) new_y++;
            if (c == KEY_RIGHT && x < max_x - 1) new_x++;
            if (c == KEY_LEFT && x > 0) new_x--;

        }
        mvprintw(2,max_x-30,"[h] to open help menu");

        if(current_user->spells.damage_spell_counter>0){
            k=2;
            current_user->spells.damage_spell_counter-=1;
            if (current_user->spells.damage_spell_counter<0) current_user->spells.damage_spell_counter=0;
        } else {
            k=1;
        }

//        if(new_x+1==hx && new_y==hy || new_x-1==hx && new_y==hy || new_x==hx && new_y+1==hy || new_x==hx && new_y-1==hy){
//            hidden_door[hy][hx]=0;
//        }



        if( (map[new_y][new_x] == '+' && (locked[new_y][new_x]==0 || locked[new_y][new_x]==2)) || map[new_y][new_x] == '$'|| map[new_y][new_x] == '@' || map[new_y][new_x] == '.' ||
            map[new_y][new_x] == '#'  || map[new_y][new_x] == 'F' || map[new_y][new_x]=='T' || map[new_y][new_x]=='^' ||
            map[new_y][new_x] == '1'  || map[new_y][new_x] == '2' || map[new_y][new_x]=='3' || map[new_y][new_x]=='4' ||
            map[new_y][new_x] == '5'  || map[new_y][new_x]=='=' || map[new_y][new_x]=='/' || map[new_y][new_x]=='z'||
            map[new_y][new_x] == 'x'  || map[new_y][new_x] == 'c' || map[new_y][new_x] == 'b' || map[new_y][new_x] == 'n'||
            map[new_y][new_x] == 'm') {


            if(map[new_y][new_x]=='b'){
                mvprintw(2,3,"You claimed a Health potion              ");
                current_user->spells.health_spell++;
            }

            if(map[new_y][new_x]=='n'){
                mvprintw(2,3,"You claimed a Speed potion              ");
                current_user->spells.speed_spell++;

            }

            if(map[new_y][new_x]=='m'){
                mvprintw(2,3,"You claimed a Damage potion              ");
                current_user->spells.damage_spell++;
            }

            if(map[new_y][new_x]=='/'){
                mvprintw(2,3,"You found an Ancient Key !              ");
                no_lock=1;
            }

            if(map[new_y][new_x]=='=' && password_counter<=3){
                char arrpass[]="0123456789";
                for(int i9=0;i9<4;i9++){
                    int temp=rand() % 9;
                    password[i9]=arrpass[temp];
                }
                mvprintw(2,3,"Password is %s                                           ",password);

            }

            if(map[new_y][new_x] == '$'){
                int temp = 2 + (rand() % 3 );
                mvprintw(2,3,"You claimed %d GOLDS !            ",temp);
                total_yellow_gold+= temp;
            }
            if(map[new_y][new_x] == '@'){
                int temp = 6 + (rand() % 4 );
                mvprintw(2,3,"You claimed %d GOLDS !            ",temp);
                total_black_gold+= temp;
            }
            if(map[new_y][new_x] == 'F'){
                int temp = 1;
                mvprintw(2,3,"You claimed %d FOOD !             ",temp);
                food1+= 1;
                if(food1>5){
                    food1=5;
                }
            }


            if(map[new_y][new_x] == 'T'){
                int temp = 1;
                mvprintw(2,3,"You stepped on a TRAP !           ",temp);
                if(current_user->game_setting.game_level==0){
                    health -= 1;
                } else{
                    health -= 2;
                }
                if(health<0){
                    health=0;
                }
                refresh();
                map[new_y][new_x]='^';
            }

            current_user->weapons.Mace=1;

            if(map[new_y][new_x] == '2'){
                current_user->weapons.Dagger=1;
                mvprintw(2,3,"You found a Dagger! +10                  ");
                current_user->weapons.Dagger_count+=10;
            }
            if(map[new_y][new_x] == 'z'){
                current_user->weapons.Dagger=1;
                mvprintw(2,3,"You found a Dagger! +1                  ");
                current_user->weapons.Dagger_count+=1;
            }


            if(map[new_y][new_x] == '3'){
                current_user->weapons.Magic_Wand=1;
                mvprintw(2,3,"You found a Magic Wand! +8             ");
                current_user->weapons.Magic_Wand_count+=8;
            }
            if(map[new_y][new_x] == 'x'){
                current_user->weapons.Magic_Wand=1;
                mvprintw(2,3,"You found a Magic Wand! +1             ");
                current_user->weapons.Magic_Wand_count+=1;
            }


            if(map[new_y][new_x] == '4'){
                current_user->weapons.Normal_Arrow=1;
                mvprintw(2,3,"You found a Normal Arrow! +20          ");
                current_user->weapons.Normal_Arrow_count+=20;
            }
            if(map[new_y][new_x] == 'c'){
                current_user->weapons.Normal_Arrow=1;
                mvprintw(2,3,"You found a Normal Arrow! +1          ");
                current_user->weapons.Normal_Arrow_count+=1;
            }


            if(map[new_y][new_x] == '5'){
                current_user->weapons.Sword=1;
                mvprintw(2,3,"You found a Sword!                   ");
            }
            y = new_y;
            x = new_x;
        }
        mvprintw(3,3,"                                                      ",password);

        if(map[y][x]!='+' && map[y][x]!='#'&&map[y][x]!='^' && map[y][x]!='='){
            map[y][x]='.';
        }
        if(c=='o'){
            potion(current_user);
        }

        mvprintw(max_y-2,max_x-10,"GOLD: %d",current_user->new_golds+total_black_gold+total_yellow_gold);



    //deamon ////////

        if(deamon_health>0){

            if(room_number[new_y][new_x]==room_number[yd][xd]){
                move_deamon(yd,xd);
            }

            if(deamon_health>0 && xd==new_x && yd==new_y){
                if(current_user->game_setting.game_level==0){
                    health -= 1;
                }
                else{
                    health -= 2;
                }
                mvprintw(3,3,"Deamon hits you!                            ");
                if(health<0){
                    health=0;
                }
            }
            refresh();
        }

    ////////--------------------------



    //fire breathing monster//////////////
        int new_x_f , new_y_f;
        int fx = new_x - xf;
        int fy = new_y - yf;

        if(fire_health>0){

            if(room_number[new_y][new_x] == room_number[yf][xf]  ) {

                new_x_f = xf;
                new_y_f = yf;

                if((abs(fx)<=6 || abs(fy)<=6 )){
                    if (abs(fx) > abs(fy)) {
                        if (fx > 0) {
                            new_x_f += 1;
                        } else {
                            new_x_f -= 1;
                        }
                    } else {
                        if (fy > 0) {
                            new_y_f += 1;
                        } else {
                            new_y_f -= 1;
                        }
                    }

                }

                if(map[new_y_f][new_x_f]!=' '){
                    move_fire_breathing_monster(new_y_f, new_x_f);

                }
            }
            refresh();

            if(fire_health>=0 && new_x_f==new_x && new_y_f==new_y){
                if(current_user->game_setting.game_level==0){
                    health -= 1;
                } else{
                    health -= 2;
                }
                mvprintw(3,3,"Fire breathing monster hits you!                       ");
                if(health<0){
                    health=0;
                }
            }


        }

        ///giant
        if(current_user->game_setting.game_level==1 || current_user->game_setting.game_level==2){
            int new_x_g , new_y_g;
            int gx = new_x - xg;
            int gy = new_y - yg;

            if(giant_health>0){
                if(room_number[new_y][new_x] == room_number[yf][xf]  ) {
                    new_x_g = xg;
                    new_y_g = yg;

                    if (abs(gx) > abs(gy)) {
                        if (gx > 0) {
                            new_x_g = new_x+1;
                        } else {
                            new_x_g = new_x-1;
                        }
                        new_y_g=new_y;
                    } else {
                        if (gy > 0) {
                            new_y_g = new_y+1;
                        } else {
                            new_y_g = new_y-1;
                        }
                        new_x_g=new_x;
                    }

                    if(map[new_y_g][new_x_g]!=' '){
                        move_giant(new_y_g, new_x_g);

                    }
                }
                refresh();

                if(giant_health>=0 && new_x_g==new_x && new_y_g==new_y){
                    if(current_user->game_setting.game_level==0){
                        health -= 1;
                    } else{
                        health -= 2;
                    }
                    mvprintw(3,3,"Giant hits you!                                     ");
                    if(health<0){
                        health=0;
                    }
                }


            }
        }




        //////----------------------
        ////snake////////////////////////
        int new_y_s;
        int new_x_s;
        if(room_number[new_y][new_x]==room_number[ys][xs] && snake_health>0){
            snake_chase=1;

        }
        if(snake_chase==1 && snake_health>0){
            new_x_s = previous_x;
            new_y_s = previous_y;
            refresh();
            if(map[new_y_s][new_x_s]!=' '){
                move_snake(new_y_s,new_x_s );
            }
        }

        if(snake_health>0 && new_x_s==new_x && new_y_s==new_y){
            if(current_user->game_setting.game_level==0){
                health -= 1;
            } else{
                health -= 2;
            }
            mvprintw(3,3,"Snake hits you!                                 ");
            if(health<0){
                health=0;
            }
        }
        refresh();

        ////////////---------------------//

        draw_character(y, x, current_user->game_setting.player_color);



        if(current_user->game_setting.game_level==0){
            if(counter==40){
                health--;
                counter=0;
            }
        }
        else if(current_user->game_setting.game_level==1){
            if(counter==25){
                health--;
                counter=0;
            }
        }
        else if(current_user->game_setting.game_level==2){
            if(counter==15){
                health--;
                counter=0;
            }
        }

        if(current_user->game_setting.game_level==0){
            if(counter==30){
                food--;
            }
        }
        else if(current_user->game_setting.game_level==1){
            if(counter==20){
                food--;
            }
        }
        else if(current_user->game_setting.game_level==2){
            if(counter==10){
                food--;
            }
        }

        if(health==0){
            current_user->new_golds+=total_black_gold+total_yellow_gold;
            current_user->total_gold+=current_user->new_golds;
            return 0;
        }

        //door code
        int status=2;
        init_pair(12,COLOR_YELLOW,COLOR_BLACK);
        init_pair(13,COLOR_MAGENTA,COLOR_BLACK);
        init_pair(14,COLOR_RED,COLOR_BLACK);



        int dx = xd - new_x;
        int dy = yd - new_y;
        fx = new_x_f -  new_x;
        fy = new_y_f - new_y;
        int sx = new_x_s -  new_x;
        int sy = new_y_s - new_y;
        if(c=='p' || c=='P') {
            if (in_use_weapon == 1) {
                if ((abs(dy) == 1 || abs(dy) == -1 || abs(dy) == 0) &&
                    (abs(dx) == 1 || abs(dx) == -1 || abs(dx) == 0)) {
                    deamon_health -= 5*k;
                    if (deamon_health <= 0) {
                        deamon_health = 0;
                    }
                    mvprintw(3, 3, "You hit Deamon!  health: %d/5                           ", deamon_health);


                }
                if ((abs(fy) == 1 || abs(fy) == -1 || abs(fy) == 0) &&
                    (abs(fx) == 1 || abs(fx) == -1 || abs(fx) == 0)) {
                    fire_health -= 5*k;
                    if (fire_health <= 0) {
                        fire_health = 0;
                    }
                    mvprintw(3, 3, "You hit Fire breathing monster!  health: %d/10                   ", fire_health);


                }
                if ((abs(gy) == 1 || abs(gy) == -1 || abs(gy) == 0) &&
                    (abs(gx) == 1 || abs(gx) == -1 || abs(gx) == 0) && (current_user->game_setting.game_level==1 || current_user->game_setting.game_level==2)) {
                    giant_health -= 5*k;
                    if (giant_health <= 0) {
                        giant_health = 0;
                    }
                    mvprintw(3, 3, "You hit Giant!  health: %d/15                                    ", giant_health);

                }
                if ((abs(sy) == 1 || abs(sy) == -1 || abs(sy) == 0) &&
                    (abs(sx) == 1 || abs(sx) == -1 || abs(sx) == 0)) {
                    snake_health -= 5*k;
                    if (snake_health <= 0) {
                        snake_health = 0;
                    }
                    mvprintw(3, 3, "You hit Snake!  health: %d/20                                    ", snake_health);

                }
            }
            if(in_use_weapon==5){
                if ((abs(dy) == 1 || abs(dy) == -1 || abs(dy) == 0) &&
                    (abs(dx) == 1 || abs(dx) == -1 || abs(dx) == 0)) {
                    deamon_health -= 10*k;
                    if (deamon_health <= 0) {
                        deamon_health = 0;
                    }
                    mvprintw(3, 3, "You hit Deamon!  health: %d/5                           ", deamon_health);

                }
                if ((abs(fy) == 1 || abs(fy) == -1 || abs(fy) == 0) &&
                    (abs(fx) == 1 || abs(fx) == -1 || abs(fx) == 0)) {
                    fire_health -= 10*k;
                    if (fire_health <= 0) {
                        fire_health = 0;
                    }
                    mvprintw(3, 3, "You hit Fire breathing monster!  health: %d/10                   ", fire_health);


                }
                if ((abs(gy) == 1 || abs(gy) == -1 || abs(gy) == 0) &&
                    (abs(gx) == 1 || abs(gx) == -1 || abs(gx) == 0) && (current_user->game_setting.game_level==1 || current_user->game_setting.game_level==2)) {
                    giant_health -= 5*k;
                    if (giant_health <= 0) {
                        giant_health = 0;
                    }
                    mvprintw(3, 3, "You hit Giant!  health: %d/15                                    ", giant_health);

                }
                if ((abs(sy) == 1 || abs(sy) == -1 || abs(sy) == 0) &&
                    (abs(sx) == 1 || abs(sx) == -1 || abs(sx) == 0)) {
                    snake_health -= 10*k;
                    if (snake_health <= 0) {
                        snake_health = 0;
                    }
                    mvprintw(3, 3, "You hit Snake!  health: %d/20                                    ", snake_health);

                }
            }
        }

        ///////////dagger
        if(in_use_weapon == 2 && previous_c == 'p') {
            start_dagger = 1;
            xfor2 = new_x;
            yfor2 = new_y;
            counterfor2 = 1;
            switch (c) {
                case 'a':
                    da++; break;
                case 'w':
                    dw++; break;
                case 's':
                    ds++; break;
                case 'd':
                    dd++; break;
            }

            current_user->weapons.Dagger_count--;
            if(current_user->weapons.Dagger_count < 0) {
                current_user->weapons.Dagger_count = 0;
            }
        }

        if(start_dagger == 1 && counterfor2 > 0) {

            if(xfor2 == new_x_f && yfor2 == new_y_f) {
                fire_health -= 10*k;
                if(fire_health <= 0) fire_health = 0;
                mvprintw(3, 3, "You hit Fire breathing monster!  health: %d/10                   ", fire_health);
                counterfor2=0;
                start_dagger=0;
            }
            if(xfor2 == new_x_s && yfor2 == new_y_s) {
                snake_health -= 10*k;
                if(snake_health <= 0) snake_health = 0;
                mvprintw(3, 3, "You hit Snake!  health: %d/20                                    ", snake_health);
                counterfor2=0;
                start_dagger=0;
            }
            if(xfor2 == xd && yfor2 == yd) {
                deamon_health -= 10*k;
                if(deamon_health <= 0) deamon_health = 0;
                mvprintw(3, 3, "You hit Deamon!  health: %d/5                           ", deamon_health);
                counterfor2=0;
                start_dagger=0;
            }
            if(xfor2 == xg && yfor2 == yg && (current_user->game_setting.game_level==1 || current_user->game_setting.game_level==2)) {
                giant_health -= 10*k;
                if(giant_health <= 0) giant_health = 0;
                mvprintw(3, 3, "You hit Giant!  health: %d/15                               ", giant_health);
                counterfor2=0;
                start_dagger=0;
            }

            if(da==1) {
                xfor2--;
                if(map[yfor2][xfor2]=='|' || map[yfor2][xfor2]=='_'){
                    counterfor2=0;
                    if(map[yfor2][xfor2+1]=='.')
                    {
                        map[yfor2][xfor2+1]='z';
                    }
                }
            }
            else if(ds==1) {
                yfor2++;
                if(map[yfor2][xfor2]=='|' || map[yfor2][xfor2]=='_'){
                    counterfor2=0;
                    if(map[yfor2-1][xfor2]=='.')
                    {
                        map[yfor2-1][xfor2]='z';
                    }
                }
            }
            else if(dd==1) {
                xfor2++;
                if(map[yfor2][xfor2]=='|' || map[yfor2][xfor2]=='_'){
                    counterfor2=0;
                    if(map[yfor2][xfor2-1]=='.')
                    {
                        map[yfor2][xfor2-1]='z';
                    }
                }
            }
            else if(dw==1) {
                yfor2--;
                if(map[yfor2][xfor2]=='|' || map[yfor2][xfor2]=='_'){
                    counterfor2=0;
                    if(map[yfor2+1][xfor2]=='.')
                    {
                        map[yfor2+1][xfor2]='z';
                    }
                }
            }

            counterfor2++;
            if(counterfor2 >= 5) {
                if(map[yfor2][xfor2]=='.'){
                    map[yfor2][xfor2]='z'; // z represents 1 dagger
                }
                start_dagger = 0;
                counterfor2 = 0;
                dd=0; da=0; dw=0; ds=0;
            }
            if(map[yfor2][xfor2]=='.'){
                mvaddch(yfor2, xfor2, '*');
            }
            mvprintw(3, 3, "                                                            ");
            refresh();
        }
        ////////////


        ///////////normal arrow
        if(in_use_weapon == 4 && previous_c == 'p') {
            start_normal_arrow = 1;
            xfor4 = new_x;
            yfor4 = new_y;
            counterfor4 = 1;
            switch (c) {
                case 'a':
                    na++; break;
                case 'w':
                    nw++; break;
                case 's':
                    ns++; break;
                case 'd':
                    nd++; break;
            }

            current_user->weapons.Normal_Arrow_count--;
            if(current_user->weapons.Normal_Arrow_count < 0) {
                current_user->weapons.Normal_Arrow_count = 0;
            }
        }

        if(start_normal_arrow == 1 && counterfor4 > 0) {

            if(xfor4 == new_x_f && yfor4 == new_y_f) {
                fire_health -= 15*k;
                if(fire_health <= 0) fire_health = 0;
                mvprintw(3, 3, "You hit Fire breathing monster!  health: %d/10                   ", fire_health);
                counterfor4=0;
                start_normal_arrow=0;
            }
            if(xfor4 == new_x_s && yfor2 == new_y_s) {
                snake_health -= 15*k;
                if(snake_health <= 0) snake_health = 0;
                mvprintw(3, 3, "You hit Snake!  health: %d/20                                    ", snake_health);
                counterfor4=0;
                start_normal_arrow=0;
            }
            if(xfor4 == xd && yfor4== yd) {
                deamon_health -= 15*k;
                if(deamon_health <= 0) deamon_health = 0;
                mvprintw(3, 3, "You hit Deamon!  health: %d/5                                    ", deamon_health);
                counterfor4=0;
                start_normal_arrow=0;
            }
            if(xfor4 == xg && yfor4 == yg && (current_user->game_setting.game_level==1 || current_user->game_setting.game_level==2)) {
                giant_health -= 15*k;
                if(giant_health <= 0) giant_health = 0;
                mvprintw(3, 3, "You hit Giant!  health: %d/15                               ", giant_health);
                counterfor4=0;
                start_normal_arrow=0;
            }

            if(na==1) {
                xfor4--;
                if(map[yfor4][xfor4]=='|' || map[yfor4][xfor4]=='_'){
                    counterfor4=0;
                    if(map[yfor4][xfor4+1]=='.')
                    {
                        map[yfor4][xfor4+1]='c';
                    }
                }
            }
            else if(ns==1) {
                yfor4++;
                if(map[yfor4][xfor4]=='|' || map[yfor4][xfor4]=='_'){
                    counterfor4=0;
                    if(map[yfor4-1][xfor4]=='.')
                    {
                        map[yfor4-1][xfor4]='c';
                    }
                }
            }
            else if(nd==1) {
                xfor4++;
                if(map[yfor4][xfor4]=='|' || map[yfor4][xfor4]=='_'){
                    counterfor4=0;
                    if(map[yfor4][xfor4-1]=='.')
                    {
                        map[yfor4][xfor4-1]='c';
                    }
                }
            }
            else if(nw==1) {
                yfor4--;
                if(map[yfor4][xfor4]=='|' || map[yfor4][xfor4]=='_'){
                    counterfor4=0;
                    if(map[yfor4+1][xfor4]=='.')
                    {
                        map[yfor4+1][xfor4]='c';
                    }
                }
            }

            counterfor4++;
            if(counterfor4 >= 5) {
                if(map[yfor4][xfor4]=='.'){
                    map[yfor4][xfor4]='c'; // c represents 1 normal arrow
                }
                start_normal_arrow = 0;
                counterfor4 = 0;
                nd=0; na=0; nw=0; ns=0;
            }
            if(map[yfor4][xfor4]=='.'){
                mvaddch(yfor4, xfor4, '-');
            }

            refresh();
        }
        ////////////

        ///////////Magic wand
        if(in_use_weapon == 3 && previous_c == 'p') {
            start_magic_wand = 1;
            xfor3 = new_x;
            yfor3 = new_y;
            counterfor3 = 1;
            switch (c) {
                case 'a':
                    ma++; break;
                case 'w':
                    mw++; break;
                case 's':
                    ms++; break;
                case 'd':
                    md++; break;
            }

            current_user->weapons.Magic_Wand_count--;
            if(current_user->weapons.Magic_Wand_count < 0) {
                current_user->weapons.Magic_Wand_count = 0;
            }
        }

        if(start_magic_wand == 1 && counterfor3 > 0) {

            if(xfor3 == new_x_f && yfor3 == new_y_f) {
                fire_health -= 10*k;
                if(fire_health <= 0) fire_health = 0;
                mvprintw(3, 3, "You hit Fire breathing monster!  health: %d/10                   ", fire_health);
                counterfor3=0;
                start_magic_wand=0;
            }
            if(xfor3 == new_x_s && yfor3 == new_y_s) {
                snake_health -= 10*k;
                if(snake_health <= 0) snake_health = 0;
                mvprintw(3, 3, "You hit Snake!  health: %d/20                                    ", snake_health);
                counterfor3=0;
                snake_chase=0;
                start_magic_wand=0;
            }
            if(xfor3 == xd && yfor3 == yd) {
                deamon_health -= 10*k;
                if(deamon_health <= 0) deamon_health = 0;
                mvprintw(3, 3, "You hit Deamon!  health: %d/5                           ", deamon_health);
                counterfor3=0;
                start_magic_wand=0;
            }
            if(xfor3 == xg && yfor3 == yg && (current_user->game_setting.game_level==1 || current_user->game_setting.game_level==2)) {
                giant_health -= 10*k;
                if(giant_health <= 0) giant_health = 0;
                mvprintw(3, 3, "You hit Giant!  health: %d/15                               ", giant_health);
                counterfor3=0;
                start_magic_wand=0;
            }

            if(ma==1) {
                xfor3--;
                if(map[yfor3][xfor3]=='|' || map[yfor3][xfor3]=='_'){
                    counterfor3=0;
                    if(map[yfor3][xfor3+1]=='.')
                    {
                        map[yfor3][xfor3+1]='x';
                    }
                }
            }
            else if(ms==1) {
                yfor3++;
                if(map[yfor3][xfor3]=='|' || map[yfor3][xfor3]=='_'){
                    counterfor3=0;
                    if(map[yfor3-1][xfor3+1]=='.')
                    {
                        map[yfor3-1][xfor3+1]='x';
                    }
                }
            }
            else if(md==1) {
                xfor3++;
                if(map[yfor3][xfor3]=='|' || map[yfor3][xfor3]=='_'){
                    counterfor3=0;
                    if(map[yfor3][xfor3-1]=='.')
                    {
                        map[yfor3][xfor3-1]='x';
                    }
                }
            }
            else if(mw==1) {
                yfor3--;
                if(map[yfor3][xfor3]=='|' || map[yfor3][xfor3]=='_'){
                    counterfor3=0;
                    if(map[yfor3+1][xfor3]=='.')
                    {
                        map[yfor3+1][xfor3]='x';
                    }
                }
            }

            counterfor3++;
            if(counterfor3 >= 5) {
                if(map[yfor3][xfor3]=='.'){
                    map[yfor3][xfor3]='x'; // x represents 1 magic wand
                }
                start_magic_wand = 0;
                counterfor3 = 0;
                md=0; ma=0; mw=0; ms=0;
            }
            if(map[yfor3][xfor3]=='.'){
                mvaddch(yfor3, xfor3, '+');
            }
            mvprintw(2, 3, "                                                            ");
            refresh();
        }
        ////////////



        if(locked[cordinate_locked[0]][cordinate_locked[1]]==1 && (new_y+1==cordinate_locked[0] && new_x==cordinate_locked[1] ||
                                                                   new_y-1==cordinate_locked[0] && new_x==cordinate_locked[1] ||
                                                                   new_y==cordinate_locked[0] && new_x+1==cordinate_locked[1] ||
                                                                   new_y==cordinate_locked[0] && new_x-1==cordinate_locked[1] )){
            mvprintw(4,3,"                                                               ",password);
            if (no_lock==0){
                if(password_counter>3){
                    attron(COLOR_PAIR(14));
                    mvprintw(3,3,"The door has been locked forever!!                   ");
                    attroff(COLOR_PAIR(14));
                }
                else {
                    mvprintw(3,3,"The door is locked. Press L to enter the pass !");
                }
                if(c=='l' && password_counter<=3){
                    status=code(password);password_counter++;
                }
                if(status==1 && password_counter<=3 ){
                    locked[cordinate_locked[0]][cordinate_locked[1]]=2;
                    mvprintw(3,3,"The door is unlocked !                                       ");

                }
                else if(status==0 && password_counter<=3){
                    if(password_counter==1){
                        attron(COLOR_PAIR(12));
                        mvprintw(3,3,"Wrong password!                                ");
                        attroff(COLOR_PAIR(12));
                    }
                    else if(password_counter==2){
                        attron(COLOR_PAIR(13));
                        mvprintw(3,3,"Wrong password!                                ");
                        attroff(COLOR_PAIR(13));
                    }
                    else if(password_counter==3){
                        attron(COLOR_PAIR(14));
                        mvprintw(3,3,"Wrong password! Door locked forever!!                          ");
                        attroff(COLOR_PAIR(14));
                    }
                }



            }
            else if(no_lock==1){
                locked[cordinate_locked[0]][cordinate_locked[1]]=2;
                mvprintw(3,3,"The door is unlocked !                                       ");
                mvprintw(3,3,"                                                            ");
            }


        }
        if(counter==40){
            strcpy(password,"0");
        }

        if(food>=10){
            if(food4health_counter>=4){
                if(current_user->spells.health_spell_counter>0){
                    health+=2;
                    current_user->spells.health_spell_counter-=1;
                    if(current_user->spells.health_spell_counter<0) current_user->spells.health_spell_counter=0;
                }
                else{
                    health+=1;
                }
                if(health>10) health=10;
                food4health_counter=0;
            }
        }

        counter++;

        mvprintw(max_y-2,60,"floor : 3");

        //health
        mvprintw(max_y-2,2,"health: ");
        refresh();
        for(int i =0;i<=health;i++){
            mvprintw(max_y-2,10+i,"♥");
            mvprintw(max_y-2,10+health," ");
            for(int j=0;j<10-i;j++){
                mvprintw(max_y-2,10+health+j," ");
            }
            mvprintw(max_y-2,10+12,"%d%c",health*10,'%');

        }

        //food
        mvprintw(max_y-2,32,"food: ");

        for(int i =0;i<=food;i++){
            mvprintw(max_y-2,38+i,"+");
            mvprintw(max_y-2,38+food," ");
            mvprintw(max_y-2,38 + 12,"     ");
            mvprintw(max_y-2,38 + 12,"%d%c",food*10,'%');
            refresh();
        }
        refresh();

        if(in_use_weapon==1){
            mvprintw(max_y-2,74,"weapon: Mace");
        }
        else if(in_use_weapon==2){
            mvprintw(max_y-2,74,"weapon: Dagger");
        }
        else if(in_use_weapon==3){
            mvprintw(max_y-2,74,"weapon: Magic Wand");
        }
        else if(in_use_weapon==4){
            mvprintw(max_y-2,74,"weapon: Normal Arrow");
        }
        else if(in_use_weapon==4){
            mvprintw(max_y-2,74,"weapon: Sword");
        }
        else {
            mvprintw(max_y-2,74,"weapon: no weapon in use!");
        }



        refresh();
        if( map[new_y][new_x]=='#'){
            int temp = cori_number[new_y][new_x];
            for(int j=-4;j<4;j++){
                for(int i=-4;i<4;i++){
                    if(cori_number[new_y+j][new_x+i]==temp && map[new_y+j][new_x+i]=='#' && visited[new_y+j][new_x+i]!=1 || map[new_y+j][new_x+i]=='+'){
                        visited[new_y+j][new_x+i]=1;
                    }
                }
            }
        }

        else if(map[new_y][new_x]=='+' &&(map[new_y+1][new_x]=='.' || map[new_y-1][new_x]=='.' || map[new_y][new_x+1]=='.' || map[new_y][new_x-1]=='.' )){
            int tempp=room_number[new_y][new_x];
            for(int j1=0;j1<max_y;j1++){
                for (int i1 = 0; i1 < max_x; i1++) {
                    if(visited[j1][i1]!=1 && room_number[j1][i1]==tempp){
                        visited[j1][i1]=1;
                    }
                }
            }
        }

        if(map[new_y][new_x]=='<'){
            current_user->food=food;
            current_user->health=health;
            current_user->food1=food1;
            current_user->new_golds+=total_black_gold+total_yellow_gold;
            current_user->weapons.in_use_weapon=in_use_weapon;
            if(snake_chase==1) current_user->game_setting.snake_chasing=1;
            else current_user->game_setting.snake_chasing=0;
            return game_f4(current_user,current_user->game_setting.game_level);
        }
        previous_x = new_x;
        previous_y = new_y;
        previous_c =c;
        food4health_counter++;


    } while ((c = getch()) != 27);

    endwin();
}


int game_f4(struct user *current_user, int level) {
    mvprintw(2,1,"  ");
    init_color(30, 333, 333, 333);
    init_pair(40, 30, COLOR_BLACK);
    init_color(31, 0, 1000, 400);
    init_pair(41, 31, COLOR_BLACK);
    init_color(32, 255, 87, 51);
    init_pair(42, 32, COLOR_BLACK);
    init_color(33, 1000, 600, 0);
    init_pair(43, 33, COLOR_BLACK);

    setlocale(LC_ALL, "");
    initscr();
    keypad(stdscr, TRUE);
    noecho();
    curs_set(0);
    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);
    char map[max_y][max_x];

    //--------------------------
    int visited[max_y][max_x];
    for(int j=0;j<max_y;j++){
        for(int i=0;i<max_x;i++){
            visited[j][i]=0;
        }
    }

    int room_number[max_y][max_x];
    for(int j=0;j<max_y;j++){
        for(int i=0;i<max_x;i++){
            room_number[j][i]=0;
        }
    }

    int cori_number[max_y][max_x];
    for(int j=0;j<max_y;j++){
        for(int i=0;i<max_x;i++){
            cori_number[j][i]=0;
        }
    }

    ///.........weapons

    int in_use_weapon= current_user->weapons.in_use_weapon;

    //.........................


    for(int i = 0; i < max_y; i++) {
        for(int j = 0; j < max_x; j++) {
            map[i][j] = ' ';
        }
    }

    //number of rooms randomly
    srand(time(NULL));
    int number_of_rooms = 5 + (rand() % 2);
    int num = 0;

    typedef struct {
        int center_x;
        int center_y;
        int room_x;
        int room_y;
        int room_x_size;
        int room_y_size;

    } RoomCenter;
    RoomCenter centers[number_of_rooms];

    //generating rooms
    while (num < number_of_rooms) {
        int ok = 0;
        int size_room_y, size_room_x, room_y, room_x;

        while (ok == 0) {

            if(num==number_of_rooms-1){
                size_room_y = 10 + (rand() % 6);
                size_room_x = 10 + (rand() % 6);

            }
            else{
                size_room_y = 8 + (rand() % 6);
                size_room_x = 8 + (rand() % 6);
            }

            room_y = 5 + (rand() % (max_y - size_room_y - 8));
            room_x = 5 + (rand() % (max_x - size_room_x - 8));

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
                    room_number[room_y + i][room_x + j]=num+1; //room number
                }
            }
        }

        //corridors
        centers[num].center_y = room_y + (size_room_y / 2);
        centers[num].center_x = room_x + (size_room_x / 2);
        centers[num].room_y=room_y;
        centers[num].room_x=room_x;
        centers[num].room_y_size=size_room_y;
        centers[num].room_x_size=size_room_x;


        if (num > 0) {
            int y1 = centers[num].center_y;
            int x1 = centers[num].center_x;
            int y2 = centers[num-1].center_y;
            int x2 = centers[num-1].center_x;

            int counterrr=0;

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


                    if(left == '_' && right == '#'){
                        map[y1][current_x] = '+';
                        map[y1][current_x-1] = '+';
                    }

                    else if(left == '#' && right == '_'){
                        map[y1][current_x] = '+';
                        map[y1][current_x+1] = '+';
                    }

                }

                else if (map[y1][current_x] == ' ') {
                    counterrr++;
                    map[y1][current_x] = '#';
                    cori_number[y1][current_x]=num+1;
                    if(counterrr%34==0){
                        if(map[y1+1][current_x]==' ' && y1+1 < max_y-3){
                            map[++y1][current_x]='#';
                            cori_number[y1][current_x]=num+1;
                        }
                        if(map[y1+1][current_x]==' ' && y1+1 < max_y-3){
                            map[++y1][current_x]='#';
                            cori_number[y1][current_x]=num+1;
                        }
                        if(map[y1+1][current_x]==' ' && y1+1 < max_y-3){
                            map[++y1][current_x]='#';
                            cori_number[y1][current_x]=num+1;
                        }
                        counterrr=0;
                    }

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
                    }
                    else if(down == '|' && up == '#'){
                        map[current_y][x2] = '+';
                        map[current_y+1][x2] = '+';
                    }

                }
                else if (map[current_y][x2] == ' ') {
                    map[current_y][x2] = '#';
                    cori_number[current_y][x2]=num+1;
                }
            }
        }


        num++;
    }

    //////////////////////

    //pillars
    int num_pillars= 6+ (rand() % 4);
    int np=0 ,py ,px;
    while(np<num_pillars){
        py = rand() % max_y  + 1;
        px = rand() % max_x  + 1;
        if(map[py][px]=='.' && map[py+1][px]!='+' && map[py][px-1]!='+' && map[py][px+1]!='+' && map[py-1][px]!='+'){
            map[py][px]='O';
            np++;
        }
    }
    //traps
    int num_traps;
    if(current_user->game_setting.game_level==0){
        num_traps= 4 + (rand() % 3);
    }
    else if(current_user->game_setting.game_level==1){
        num_traps= 7 + (rand() % 5);
    }
    else if(current_user->game_setting.game_level==2){
        num_traps= 10 + (rand() % 7);
    }
    int nt=0 ,ty ,tx;
    while(nt<num_traps){
        ty = rand() % max_y  + 1;
        tx = rand() % max_x  + 1;
        if(map[ty][tx]=='.' && room_number[ty][tx]!=number_of_rooms){
            map[ty][tx]='T';
            nt++;
        }
    }

    int num_traps1= 10+ (rand() % 6);
    nt=0; ty=0; tx=0;
    while(nt<num_traps1){
        ty = centers[number_of_rooms-1].room_y + rand() % centers[number_of_rooms-1].room_y_size  + 1;
        tx = centers[number_of_rooms-1].room_x + rand() % centers[number_of_rooms-1].room_x_size  + 1;
        if(map[ty][tx]=='.' && room_number[ty][tx]==number_of_rooms){
            map[ty][tx]='T';
            nt++;
        }
    }


    //foods
    int num_foods;
    if(current_user->game_setting.game_level==0){
        num_foods= 9 + (rand() % 4);
    }
    else if(current_user->game_setting.game_level==1){
        num_foods= 6 + (rand() % 4);
    }
    else if(current_user->game_setting.game_level==2){
        num_foods= 3 + (rand() % 2);
    }
    int nf=0 ,fy ,fx;
    while(nf<num_foods){
        fy = rand() % max_y  + 1;
        fx = rand() % max_x  + 1;
        if(map[fy][fx]=='.' && room_number[fy][fx]!=number_of_rooms){
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
        if(map[gy][gx]=='.' && room_number[gy][gx]!=number_of_rooms){
            map[gy][gx]='$';
            nyg++;
        }
    }


    int num_ygolds1= 10 + (rand() % 6);
    nyg=0;
    gy=0;
    gx=0;
    while(nyg<num_ygolds1){
        gy = centers[number_of_rooms-1].room_y + rand() % centers[number_of_rooms-1].room_y_size  + 1;
        gx = centers[number_of_rooms-1].room_x + rand() % centers[number_of_rooms-1].room_x_size  + 1;
        if(map[gy][gx]=='.' && room_number[gy][gx]==number_of_rooms){
            map[gy][gx]='$';
            nyg++;
        }
    }

    //black golds

    int num_bgolds= 5 + (rand() % 1);
    int nbg=0 ,by ,bx;
    while(nbg<num_bgolds){
        by = rand() % max_y  + 1;
        bx = rand() % max_x  + 1;
        if(map[by][bx]=='.' && room_number[by][bx]!=number_of_rooms ){
            map[by][bx]='@';
            nbg++;
        }
    }

    num_bgolds= 4 + (rand() % 1);
    nbg=0 ,by=0 ,bx=0;
    while(nbg<num_bgolds){
        by = centers[number_of_rooms-1].room_y + rand() % centers[number_of_rooms-1].room_y_size  + 1;
        bx = centers[number_of_rooms-1].room_x + rand() % centers[number_of_rooms-1].room_x_size  + 1;
        if(map[by][bx]=='.' && room_number[by][bx]==number_of_rooms){
            map[by][bx]='@';
            nbg++;
        }
    }


    int x2 = 0, y2 = 0;
    int stairs = 0;
    while(!stairs) {
        y2 = rand() % max_y  + 1;
        x2 = rand() % max_x  + 1;
        if(map[y2][x2]=='.' && room_number[y2][x2]!=number_of_rooms){
            map[y2][x2]='<';
            stairs++;
        }
    }
    int y=y2;
    int x=x2;

    int room_num=room_number[y][x];

    for(int i=0;i<max_x;i++){
        for(int j=0;j<max_y;j++){
            if(room_number[j][i]==room_num){
                visited[j][i]=1;
            }
        }
    }

    //weapons
    int weapon_num= 2 + rand() % 4;
    int x3=0,y3=0;
    int weaponi =0 ;
    while(!weaponi){
        y3 = rand() % max_y ;
        x3 = rand() % max_x ;
        if(map[y3][x3]=='.'){
            if(weapon_num==1){
                map[y3][x3]='1';
                weaponi++;
            }
            else if(weapon_num==2){
                map[y3][x3]='2';
                weaponi++;
            }
            else if(weapon_num==3){
                map[y3][x3]='3';
                weaponi++;
            }

            else if(weapon_num==4){
                map[y3][x3]='4';
                weaponi++;
            }

            else if(weapon_num==5){
                map[y3][x3]='5';
                weaponi++;
            }
        }
    }

    weapon_num= 2 + rand() % 4;
    x3=0,y3=0;
    weaponi =0 ;
    while(!weaponi){
        y3 = rand() % max_y ;
        x3 = rand() % max_x ;
        if(map[y3][x3]=='.'){
            if(weapon_num==1){
                map[y3][x3]='1';
                weaponi++;
            }
            else if(weapon_num==2){
                map[y3][x3]='2';
                weaponi++;
            }
            else if(weapon_num==3){
                map[y3][x3]='3';
                weaponi++;
            }

            else if(weapon_num==4){
                map[y3][x3]='4';
                weaponi++;
            }

            else if(weapon_num==5){
                map[y3][x3]='5';
                weaponi++;
            }
        }
    }

    /////treasure room entry
    stairs = 0;
    while(!stairs) {
        y2 = rand() % max_y  + 1;
        x2 = rand() % max_x  + 1;
        if(map[y2][x2]=='.' && room_number[y2][x2]==number_of_rooms){
            map[y2][x2]='X';
            stairs++;
            break;
        }
    }

    /////locked door////////////////
    int locked[max_y][max_x];
    for(int j=0;j<max_y;j++){
        for(int i=0;i<max_x;i++){
            locked[j][i]=0;
        }
    }
    int lock=0;
    int locked_room_num;
    int cordinate_locked[2];
    while(!lock){
        int y4=rand()%max_y;
        int x4=rand()%max_x;
        if(map[y4][x4]=='+' && map[y4+1][x4]!='+' && map[y4-1][x4]!='+' && map[y4][x4+1]!='+' && map[y4][x4-1]!='+'){
            int count=0;
            locked_room_num=room_number[y4][x4];
            for(int j=0;j<max_y;j++){
                for(int i=0; i<max_x;i++){
                    if(map[j][i]=='+' && room_number[j][i]==locked_room_num){
                        count++;
                    }
                }
            }
            if(count==2){
                locked[y4][x4]=1;
                cordinate_locked[0]=y4; cordinate_locked[1]=x4;
                break;
            }
        }
    }



    while(1){
        int y5=rand()%max_y;
        int x5=rand()%max_x;
        if(map[y5][x5]=='.' && room_number[y5][x5]==locked_room_num){
            map[y5][x5]='=';
            break;
        }
    }


    int no_lock=0;
    while(1){
        int y6=rand()%max_y;
        int x6=rand()%max_x;
        if(map[y6][x6]=='.' ){
            map[y6][x6]='/';
            break;
        }
    }



    ////////////////


    ///--->> deamon <<---///
    int xd=0, yd=0;
    int countd=0;
    while (countd==0){
        xd = rand() % max_x;
        yd = rand() % max_y;
        if(map[yd][xd]=='.'){
            countd++;
        }
    }
    ////////////////////////

    ///--->> fire breathing monster <<---///
    int xf=0, yf=0;
    int countf=0;
    while (countf==0){
        xf = rand() % max_x;
        yf = rand() % max_y;
        if(map[yf][xf]=='.'){
            countf++;
        }
    }
    ////////////////////////

    int xs=0, ys=0;
    ///--->> snake <<---///
    if(current_user->game_setting.snake_chasing==1){
        xs = x; ys=y;
    }
    else {
        int counts = 0;
        while (counts == 0) {
            xs = rand() % max_x;
            ys = rand() % max_y;
            if (map[ys][xs] == '.') {
                counts++;
            }
        }
    }
    /////


    ///--->> giant <<---///
    int xg=0, yg=0;
    int countg=0;
    while (countg==0){
        xg = rand() % max_x;
        yg = rand() % max_y;
        if(map[yg][xg]=='.'){
            countg++;
        }
    }
//    ////////////////////////
//
//
//    ///--->> undeed <<---///
//    int xu=0, yu=0;
//    int countu=0;
//    while (countu==0){
//        xu = rand() % max_x;
//        yu = rand() % max_y;
//        if(map[yu][xu]=='.'){
//            countu++;
//        }
//    }
//    //////////////////////


    int colored_room1 = 1 + rand()% (number_of_rooms-1);
    int colored_room2 = 1 + rand()%( number_of_rooms-1);

// speed spell
    int x_speed_spell=0, y_speed_spell=0;
    int countof= 1+  rand() % 2;
    while (countof!=0){
        x_speed_spell = rand() % max_x;
        y_speed_spell = rand() % max_y;
        if(map[y_speed_spell][x_speed_spell]=='.' && (room_number[y_speed_spell][x_speed_spell]==colored_room1 ||room_number[y_speed_spell][x_speed_spell]==colored_room2) ){
            map[y_speed_spell][x_speed_spell]='n'; //n stands for speed spell
            countof--;
        }
    }
    // health spell
    int x_health_spell=0, y_health_spell=0;
    countof= 1 + rand() % 2;
    while (countof!=0){
        x_health_spell = rand() % max_x;
        y_health_spell = rand() % max_y;
        if(map[y_health_spell][x_health_spell]=='.' && (room_number[y_speed_spell][x_speed_spell]==colored_room1 ||room_number[y_speed_spell][x_speed_spell]==colored_room2)){
            map[y_health_spell][x_health_spell]='b'; //b stands for health spell
            countof--;
        }
    }

    //damage spell
    int x_damage_spell=0, y_damage_spell=0;
    countof= 1 + rand() % 2;
    while (countof!=0){
        x_damage_spell = rand() % max_x;
        y_damage_spell = rand() % max_y;
        if(map[y_damage_spell][x_damage_spell]=='.' && (room_number[y_speed_spell][x_speed_spell]==colored_room1 ||room_number[y_speed_spell][x_speed_spell]==colored_room2)){
            map[y_damage_spell][x_damage_spell]='m'; //m stands for health spell
            countof--;
        }
    }







    clear();

    init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(6, COLOR_YELLOW, COLOR_BLACK);
    init_pair(7, COLOR_BLACK, COLOR_WHITE);
    init_pair(8, COLOR_YELLOW, COLOR_RED);
    init_pair(9, COLOR_CYAN, COLOR_BLACK);
    init_pair(10,COLOR_RED,COLOR_BLACK);
    init_pair(11,COLOR_GREEN,COLOR_BLACK);
    ////////////////////
    int total_yellow_gold=0;
    int total_black_gold=0;
    /////////////////////

    int food=current_user->food;
    int food1=current_user->food1;
    int health=current_user->health;


    ///////////////////////MAIN///////

    // printing map (player movement -- map)
    int c;
    int counter=0;

    char password[100]={0};
    int password_counter=0;
    int previous_x=0 , previous_y=0;
    int deamon_health=5;
    int fire_health = 10;
    int giant_health = 15;
    int snake_health = 20;
    int undeed_health = 30;
    int snake_chase=0;
    char previous_c;
    int start_normal_arrow=0;  int xfor4, yfor4, counterfor4;int nw=0,na=0,ns=0,nd=0;
    int start_magic_wand=0;  int xfor3, yfor3, counterfor3;int mw=0,ma=0,ms=0,md=0;
    int start_dagger=0;  int xfor2, yfor2, counterfor2; int dw=0,da=0,ds=0,dd=0;
    int is_sth_here[max_y][max_x];
    for(int j=0;j<max_y;j++){
        for(int i=0;i<max_x;i++){
            is_sth_here[j][i]=0;
        }
    }
    int food4health_counter=0;
    int k=1;




    do {
        //print map
        for(int i = 0; i < max_y; i++) {
            for(int j = 0; j < max_x; j++) {
                if(map[i][j] != ' ' && visited[i][j]==1) {

                    if (map[i][j] == '|'){
                        if(room_number[i][j] == colored_room1 || room_number[i][j] == colored_room2) {
                            attron(COLOR_PAIR(41));
                            mvaddch(i, j, map[i][j]);
                            attroff(COLOR_PAIR(41));
                        }
                        else{
                            attron(COLOR_PAIR(5));
                            mvaddch(i, j, map[i][j]);
                            attroff(COLOR_PAIR(5));
                        }
                    } else if (map[i][j] == '.' &&
                               (room_number[i][j] == colored_room1 || room_number[i][j] == colored_room2)) {
                        attron(COLOR_PAIR(40));
                        mvaddch(i, j, map[i][j]);
                        attroff(COLOR_PAIR(40));
                    } else if (map[i][j] == '_'){
                        if(room_number[i][j] == colored_room1 || room_number[i][j] == colored_room2) {
                            attron(COLOR_PAIR(41));
                            mvaddch(i, j, map[i][j]);
                            attroff(COLOR_PAIR(41));
                        }
                        else{
                            mvaddch(i, j, map[i][j]);
                        }
                    } else if (map[i][j] == 'O'){
                        if(room_number[i][j] == colored_room1 || room_number[i][j] == colored_room2) {
                            attron(COLOR_PAIR(41));
                            mvaddch(i, j, map[i][j]);
                            attroff(COLOR_PAIR(41));
                        }
                        else{
                            attron(COLOR_PAIR(5));
                            mvaddch(i, j, map[i][j]);
                            attroff(COLOR_PAIR(5));
                        }
                    } else if (map[i][j] == '#') {

                        mvaddch(i, j, map[i][j]);
                    }
                    else if (map[i][j] == '$') {
                        attron(COLOR_PAIR(6));
                        mvprintw(i, j, "%lc", (wint_t) 0x25C6);
                        attroff(COLOR_PAIR(6));
                    } else if (map[i][j] == '@') {
                        init_color(21, 1000, 400, 1000);
                        init_pair(44,21,COLOR_BLACK);
                        attron(COLOR_PAIR(44));
                        mvprintw(i, j, "%lc", (wint_t) 0x25C6);
                        attroff(COLOR_PAIR(44));
                    }
                    else if (map[i][j] == 'F') {
                        attron(COLOR_PAIR(8));
                        mvaddch(i, j, map[i][j]);
                        attroff(COLOR_PAIR(8));
                    }else if (map[i][j] == 'T') {
                        if(room_number[i][j] == colored_room1 || room_number[i][j] == colored_room2) {
                            attron(COLOR_PAIR(40));
                            mvaddch(i, j, '.');
                            attroff(COLOR_PAIR(40));
                        }
                        else{
                            mvaddch(i, j, '.');
                        }
                    }  else if (map[i][j] == '^') {
                        mvaddch(i, j, map[i][j]);
                    } else if (map[i][j] == '2' || map[i][j] == 'z') {
                        mvprintw(i, j, "%lc", (wint_t) 0x1F5E1); // 🗡 ok
                    } else if (map[i][j] == '3' || map[i][j] == 'x') {
                        attron(COLOR_PAIR(9));
                        mvaddch(i, j, 'W');
                        attroff(COLOR_PAIR(9));
                        // mvprintw(i, j, "%lc", (wint_t)0x1FA84); // 🪄
                    } else if (map[i][j] == '4' || map[i][j] == 'c') {
                        mvprintw(i, j, "%lc", (wint_t) 0x27B3); // ➳ ok
                    } else if (map[i][j] == '5') {
                        attron(COLOR_PAIR(9));
                        mvaddch(i, j, 'S');
                        attroff(COLOR_PAIR(9));
                        //mvprintw(i, j, "%lc", (wint_t)0x2694); // ⚔
                    } else if (map[i][j] == '+' && locked[i][j] == 1) {
                        attron(COLOR_PAIR(10));
                        mvaddch(i, j, '@');
                        attroff(COLOR_PAIR(10));
                    } else if (map[i][j] == '+' && locked[i][j] == 2) {
                        attron(COLOR_PAIR(11));
                        mvaddch(i, j, '@');
                        attroff(COLOR_PAIR(11));
                    }

                    else if (map[i][j] == '=') {
//                        mvprintw(i, j, "%lc", (wint_t) 0x23F9);
                        mvaddch(i, j, '&');
                    } else if (map[i][j] == '/') {
                        attron(COLOR_PAIR(6));
                        mvprintw(i, j, "%lc", (wint_t) 0x25B3);
                        attroff(COLOR_PAIR(6));
                    } else if (map[i][j] == 'b') { //health spell
                        attron(COLOR_PAIR(10));
                        mvprintw(i, j, "%lc", (wint_t)0x271A);
                        attroff(COLOR_PAIR(10));
                    } else if (map[i][j] == 'n') { //speed spell
                        attron(COLOR_PAIR(6));
                        mvprintw(i, j, "%lc", (wint_t) 0x27A4);
                        attroff(COLOR_PAIR(6));
                    } else if (map[i][j] == 'm') { //damage spell
                        init_color(24, 1000, 200, 0);
                        init_pair(45,24,COLOR_BLACK);
                        attron(COLOR_PAIR(45));
                        mvprintw(i, j, "%lc", (wint_t) 0x23FA);
                        attroff(COLOR_PAIR(45));
                    }

                    else if (map[i][j] == '+'){
                        if(room_number[i][j] == colored_room1 || room_number[i][j] == colored_room2) {
                            attron(COLOR_PAIR(41));
                            mvaddch(i, j, map[i][j]);
                            attroff(COLOR_PAIR(41));
                        }
                        else{
                            attron(COLOR_PAIR(5));
                            mvaddch(i, j, map[i][j]);
                            attroff(COLOR_PAIR(5));
                        }
                    }
                    else if(map[i][j]=='X'){
                        mvprintw(i, j, "👑");

                    }
                    else if(map[i][j]!='1') {
                        if ((room_number[i][j] == colored_room1 || room_number[i][j] == colored_room2)) {
                            attron(COLOR_PAIR(41));
                            mvaddch(i, j, map[i][j]);
                            attroff(COLOR_PAIR(41));

                        } else {
                            mvaddch(i, j, map[i][j]);
                        }
                    }
                }
            }
        }




        int new_y = y;
        int new_x = x;

        if(c=='h'){
            help();
        }

        if(c=='i'){//weapon
            clear();
            in_use_weapon= weapon(current_user,in_use_weapon);

        }

        if(c ==101) { ///food window
            clear();
            int p= food_bar(&food1, &health, &food);
            if(p==3){
                continue;
            }
            c = getch();
        }
        ///movement

        if(current_user->spells.speed_spell_counter>0){
            if (c == KEY_UP && y > 0) new_y-=2;
            if (c == KEY_DOWN && y < max_y - 1) new_y+=2;
            if (c == KEY_RIGHT && x < max_x - 1) new_x+=2;
            if (c == KEY_LEFT && x > 0) new_x-=2;
            current_user->spells.speed_spell_counter-=1;
            if(current_user->spells.speed_spell_counter==0) current_user->spells.speed_spell_counter=0;
        }
        else{
            if (c == KEY_UP && y > 0) new_y--;
            if (c == KEY_DOWN && y < max_y - 1) new_y++;
            if (c == KEY_RIGHT && x < max_x - 1) new_x++;
            if (c == KEY_LEFT && x > 0) new_x--;

        }
        mvprintw(2,max_x-30,"[h] to open help menu");


        if(current_user->spells.damage_spell_counter>0){
            k=2;
            current_user->spells.damage_spell_counter-=1;
            if (current_user->spells.damage_spell_counter<0) current_user->spells.damage_spell_counter=0;
        } else {
            k=1;
        }



        if( (map[new_y][new_x] == '+' && (locked[new_y][new_x]==0 || locked[new_y][new_x]==2)) || map[new_y][new_x] == '$'|| map[new_y][new_x] == '@' || map[new_y][new_x] == '.' ||
            map[new_y][new_x] == '#'  || map[new_y][new_x] == 'F' || map[new_y][new_x]=='T' || map[new_y][new_x]=='^' ||
            map[new_y][new_x] == '1'  || map[new_y][new_x] == '2' || map[new_y][new_x]=='3' || map[new_y][new_x]=='4' ||
            map[new_y][new_x] == '5'  || map[new_y][new_x]=='=' || map[new_y][new_x]=='/' || map[new_y][new_x]=='z'||
            map[new_y][new_x] == 'x'  || map[new_y][new_x] == 'c' || map[new_y][new_x] == 'b' || map[new_y][new_x] == 'n'||
            map[new_y][new_x] == 'm' || map[new_y][new_x]=='X') {

            if(map[new_y][new_x]=='X'){
                current_user->food=food;
                current_user->health=health;
                current_user->food1=food1;
                current_user->new_golds+=total_black_gold+total_yellow_gold;
                current_user->weapons.in_use_weapon=in_use_weapon;
                current_user->total_gold+=current_user->new_golds;
                return treasure_room(current_user, current_user->game_setting.game_level);
            }


            if(map[new_y][new_x]=='b'){
                mvprintw(2,3,"You claimed a Health potion              ");
                current_user->spells.health_spell++;
            }

            if(map[new_y][new_x]=='n'){
                mvprintw(2,3,"You claimed a Speed potion              ");
                current_user->spells.speed_spell++;

            }

            if(map[new_y][new_x]=='m'){
                mvprintw(2,3,"You claimed a Damage potion              ");
                current_user->spells.damage_spell++;
            }

            if(map[new_y][new_x]=='/'){
                mvprintw(2,3,"You found an Ancient Key !              ");
                no_lock=1;
            }

            if(map[new_y][new_x]=='=' && password_counter<=3){
                char arrpass[]="0123456789";
                for(int i9=0;i9<4;i9++){
                    int temp=rand() % 9;
                    password[i9]=arrpass[temp];
                }
                mvprintw(2,3,"Password is %s                                           ",password);

            }

            if(map[new_y][new_x] == '$'){
                int temp = 2 + (rand() % 3 );
                mvprintw(2,3,"You claimed %d GOLDS !            ",temp);
                total_yellow_gold+= temp;
            }
            if(map[new_y][new_x] == '@'){
                int temp = 6 + (rand() % 4 );
                mvprintw(2,3,"You claimed %d GOLDS !            ",temp);
                total_black_gold+= temp;
            }
            if(map[new_y][new_x] == 'F'){
                int temp = 1;
                mvprintw(2,3,"You claimed %d FOOD !             ",temp);
                food1+= 1;
                if(food1>5){
                    food1=5;
                }
            }


            if(map[new_y][new_x] == 'T'){
                int temp = 1;
                mvprintw(2,3,"You stepped on a TRAP !           ",temp);
                if(current_user->game_setting.game_level==0){
                    health -= 1;
                } else{
                    health -= 2;
                }
                if(health<0){
                    health=0;
                }
                refresh();
                map[new_y][new_x]='^';
            }

            current_user->weapons.Mace=1;

            if(map[new_y][new_x] == '2'){
                current_user->weapons.Dagger=1;
                mvprintw(2,3,"You found a Dagger! +10                  ");
                current_user->weapons.Dagger_count+=10;
            }
            if(map[new_y][new_x] == 'z'){
                current_user->weapons.Dagger=1;
                mvprintw(2,3,"You found a Dagger! +1                  ");
                current_user->weapons.Dagger_count+=1;
            }


            if(map[new_y][new_x] == '3'){
                current_user->weapons.Magic_Wand=1;
                mvprintw(2,3,"You found a Magic Wand! +8             ");
                current_user->weapons.Magic_Wand_count+=8;
            }
            if(map[new_y][new_x] == 'x'){
                current_user->weapons.Magic_Wand=1;
                mvprintw(2,3,"You found a Magic Wand! +1             ");
                current_user->weapons.Magic_Wand_count+=1;
            }


            if(map[new_y][new_x] == '4'){
                current_user->weapons.Normal_Arrow=1;
                mvprintw(2,3,"You found a Normal Arrow! +20          ");
                current_user->weapons.Normal_Arrow_count+=20;
            }
            if(map[new_y][new_x] == 'c'){
                current_user->weapons.Normal_Arrow=1;
                mvprintw(2,3,"You found a Normal Arrow! +1          ");
                current_user->weapons.Normal_Arrow_count+=1;
            }


            if(map[new_y][new_x] == '5'){
                current_user->weapons.Sword=1;
                mvprintw(2,3,"You found a Sword!                   ");
            }
            y = new_y;
            x = new_x;
        }
        mvprintw(3,3,"                                                      ",password);

        if(map[y][x]!='+' && map[y][x]!='#'&&map[y][x]!='^' && map[y][x]!='='){
            map[y][x]='.';
        }

        if(c=='o'){
            potion(current_user);
        }


        mvprintw(max_y-2,max_x-10,"GOLD: %d",current_user->new_golds+total_black_gold+total_yellow_gold);



        //deamon ////////

        if(deamon_health>0){

            if(room_number[new_y][new_x]==room_number[yd][xd]){
                move_deamon(yd,xd);
            }

            if(deamon_health>0 && xd==new_x && yd==new_y){
                if(current_user->game_setting.game_level==0){
                    health -= 1;
                }
                else{
                    health -= 2;
                }
                mvprintw(3,3,"Deamon hits you!                            ");
                if(health<0){
                    health=0;
                }
            }
            refresh();

        }

        ////////--------------------------



        //fire breathing monster//////////////
        int new_x_f , new_y_f;
        int fx = new_x - xf;
        int fy = new_y - yf;

        if(fire_health>0){

            if(room_number[new_y][new_x] == room_number[yf][xf]  ) {

                new_x_f = xf;
                new_y_f = yf;

                if((abs(fx)<=6 || abs(fy)<=6 )){
                    if (abs(fx) > abs(fy)) {
                        if (fx > 0) {
                            new_x_f += 1;
                        } else {
                            new_x_f -= 1;
                        }
                    } else {
                        if (fy > 0) {
                            new_y_f += 1;
                        } else {
                            new_y_f -= 1;
                        }
                    }

                }
                if(map[new_y_f][new_x_f]!=' '){
                    move_fire_breathing_monster(new_y_f, new_x_f);

                }
            }
            refresh();

            if(fire_health>=0 && new_x_f==new_x && new_y_f==new_y){
                if(current_user->game_setting.game_level==0){
                    health -= 1;
                } else{
                    health -= 2;
                }
                mvprintw(3,3,"Fire breathing monster hits you!                       ");
                if(health<0){
                    health=0;
                }
            }


        }


        //////----------------------

        //giant//////////////
        int new_x_g , new_y_g;
        int gx = new_x - xg;
        int gy = new_y - yg;

        if(giant_health>0){

            if(room_number[new_y][new_x] == room_number[yg][xg]  ) {

                new_x_g = xg;
                new_y_g = yg;

                if((abs(gx)<=20 || abs(gy)<=20 )){
                    if (abs(gx) > abs(gy)) {
                        if (gx > 0) {
                            new_x_g = new_x+1;
                        } else {
                            new_x_g = new_x-1;
                        }
                        new_y_g=new_y;
                    } else {
                        if (gy > 0) {
                            new_y_g = new_y+1;
                        } else {
                            new_y_g = new_y-1;
                        }
                        new_x_g=new_x;
                    }

                }

                if(map[new_y_g][new_x_g]!=' '){
                    move_giant(new_y_g, new_x_g);

                }
            }
            refresh();

            if(giant_health>0 && new_x_g==new_x && new_y_g==new_y){
                if(current_user->game_setting.game_level==0){
                    health -= 1;
                } else{
                    health -= 2;
                }
                mvprintw(3,3,"Giant hits you!                                 ");
                if(health<0){
                    health=0;
                }
            }


        }


        //////----------------------


        ////snake////////////////////////
        int new_y_s;
        int new_x_s;
        if(room_number[new_y][new_x]==room_number[ys][xs] && snake_health>0){
            snake_chase=1;

        }
        if(snake_chase==1 && snake_health>0){
            new_x_s = previous_x;
            new_y_s = previous_y;
            refresh();
            if(map[new_y_s][new_x_s]!=' '){
                move_snake(new_y_s,new_x_s );
            }
        }

        if(snake_health>0 && new_x_s==new_x && new_y_s==new_y){
            if(current_user->game_setting.game_level==0){
                health -= 1;
            } else{
                health -= 2;
            }
            mvprintw(3,3,"Snake hits you!                                 ");
            if(health<0){
                health=0;
            }
        }
        refresh();

        ////////////---------------------//

        draw_character(y, x, current_user->game_setting.player_color);


        if(current_user->game_setting.game_level==0){
            if(counter==40){
                health--;
                counter=0;
            }
        }
        else if(current_user->game_setting.game_level==1){
            if(counter==25){
                health--;
                counter=0;
            }
        }
        else if(current_user->game_setting.game_level==2){
            if(counter==15){
                health--;
                counter=0;
            }
        }

        if(current_user->game_setting.game_level==0){
            if(counter==30){
                food--;
            }
        }
        else if(current_user->game_setting.game_level==1){
            if(counter==20){
                food--;
            }
        }
        else if(current_user->game_setting.game_level==2){
            if(counter==10){
                food--;
            }
        }

        if(health==0){
            current_user->new_golds=current_user->new_golds+total_black_gold+total_yellow_gold;
            current_user->total_gold=current_user->total_gold+ current_user->new_golds;
            return 0;
        }

        //door code
        int status=2;
        init_pair(12,COLOR_YELLOW,COLOR_BLACK);
        init_pair(13,COLOR_MAGENTA,COLOR_BLACK);
        init_pair(14,COLOR_RED,COLOR_BLACK);


        int dx = xd - new_x;
        int dy = yd - new_y;
        fx = new_x_f -  new_x;
        fy = new_y_f - new_y;
        gx = new_x_g -  new_x;
        gy = new_y_g - new_y;
        int sx = new_x_s -  new_x;
        int sy = new_y_s - new_y;
        if(c=='p' || c=='P') {
            if (in_use_weapon == 1) {
                if ((abs(dy) == 1 || abs(dy) == -1 || abs(dy) == 0) &&
                    (abs(dx) == 1 || abs(dx) == -1 || abs(dx) == 0)) {
                    deamon_health -= 5*k;
                    if (deamon_health <= 0) {
                        deamon_health = 0;
                    }
                    mvprintw(3, 3, "You hit Deamon!  health: %d/5                           ", deamon_health);

                }
                if ((abs(fy) == 1 || abs(fy) == -1 || abs(fy) == 0) &&
                    (abs(fx) == 1 || abs(fx) == -1 || abs(fx) == 0)) {
                    fire_health -= 5*k;
                    if (fire_health <= 0) {
                        fire_health = 0;
                    }
                    mvprintw(3, 3, "You hit Fire breathing monster!  health: %d/10                   ", fire_health);

                }
                if ((abs(gy) == 1 || abs(gy) == -1 || abs(gy) == 0) &&
                    (abs(gx) == 1 || abs(gx) == -1 || abs(gx) == 0)) {
                    giant_health -= 5*k;
                    if (giant_health <= 0) {
                        giant_health = 0;
                    }
                    mvprintw(3, 3, "You hit Giant!  health: %d/15                                    ", giant_health);

                }
                if ((abs(sy) == 1 || abs(sy) == -1 || abs(sy) == 0) &&
                    (abs(sx) == 1 || abs(sx) == -1 || abs(sx) == 0)) {
                    snake_health -= 5*k;
                    if (snake_health <= 0) {
                        snake_health = 0;
                    }
                    mvprintw(3, 3, "You hit Snake!  health: %d/20                                    ", snake_health);

                }
            }
            if(in_use_weapon==5){
                if ((abs(dy) == 1 || abs(dy) == -1 || abs(dy) == 0) &&
                    (abs(dx) == 1 || abs(dx) == -1 || abs(dx) == 0)) {
                    deamon_health -= 10*k;
                    if (deamon_health <= 0) {
                        deamon_health = 0;
                    }
                    mvprintw(3, 3, "You hit Deamon!  health: %d/5                           ", deamon_health);

                }
                if ((abs(fy) == 1 || abs(fy) == -1 || abs(fy) == 0) &&
                    (abs(fx) == 1 || abs(fx) == -1 || abs(fx) == 0)) {
                    fire_health -= 10*k;
                    if (fire_health <= 0) {
                        fire_health = 0;
                    }
                    mvprintw(3, 3, "You hit Fire breathing monster!  health: %d/10                   ", fire_health);

                }
                if ((abs(gy) == 1 || abs(gy) == -1 || abs(gy) == 0) &&
                    (abs(gx) == 1 || abs(gx) == -1 || abs(gx) == 0)) {
                    giant_health -= 10*k;
                    if (giant_health <= 0) {
                        giant_health = 0;
                    }
                    mvprintw(3, 3, "You hit Giant!  health: %d/15                                    ", giant_health);

                }



                if ((abs(sy) == 1 || abs(sy) == -1 || abs(sy) == 0) &&
                    (abs(sx) == 1 || abs(sx) == -1 || abs(sx) == 0)) {
                    snake_health -= 10*k;
                    if (snake_health <= 0) {
                        snake_health = 0;
                    }
                    mvprintw(3, 3, "You hit Snake!  health: %d/20                                    ", snake_health);

                }
            }
        }

        ///////////dagger
        if(in_use_weapon == 2 && previous_c == 'p') {
            start_dagger = 1;
            xfor2 = new_x;
            yfor2 = new_y;
            counterfor2 = 1;
            switch (c) {
                case 'a':
                    da++; break;
                case 'w':
                    dw++; break;
                case 's':
                    ds++; break;
                case 'd':
                    dd++; break;
            }

            current_user->weapons.Dagger_count--;
            if(current_user->weapons.Dagger_count < 0) {
                current_user->weapons.Dagger_count = 0;
            }
        }

        if(start_dagger == 1 && counterfor2 > 0) {

            if(xfor2 == new_x_f && yfor2 == new_y_f) {
                fire_health -= 10*k;
                if(fire_health <= 0) fire_health = 0;
                mvprintw(3, 3, "You hit Fire breathing monster!  health: %d/10                   ", fire_health);
                counterfor2=0;
                start_dagger=0;
            }
            if(xfor2 == new_x_g && yfor2 == new_y_g) {
                giant_health -= 10*k;
                if(giant_health <= 0) giant_health = 0;
                mvprintw(3, 3, "You hit Gaint!  health: %d/15                                    ", giant_health);
                counterfor2=0;
                start_dagger=0;
            }
            if(xfor2 == new_x_s && yfor2 == new_y_s) {
                snake_health -= 10*k;
                if(snake_health <= 0) snake_health = 0;
                mvprintw(3, 3, "You hit Snake!  health: %d/20                                    ", snake_health);
                counterfor2=0;
                start_dagger=0;
            }
            if(xfor2 == xd && yfor2 == yd) {
                deamon_health -= 10*k;
                if(deamon_health <= 0) deamon_health = 0;
                mvprintw(3, 3, "You hit Deamon!  health: %d/5                                    ", deamon_health);
                counterfor2=0;
                start_dagger=0;
            }

            if(da==1) {
                xfor2--;
                if(map[yfor2][xfor2]=='|' || map[yfor2][xfor2]=='_'){
                    counterfor2=0;
                    if(map[yfor2][xfor2+1]=='.')
                    {
                        map[yfor2][xfor2+1]='z';
                    }
                }
            }
            else if(ds==1) {
                yfor2++;
                if(map[yfor2][xfor2]=='|' || map[yfor2][xfor2]=='_'){
                    counterfor2=0;
                    if(map[yfor2-1][xfor2]=='.')
                    {
                        map[yfor2-1][xfor2]='z';
                    }
                }
            }
            else if(dd==1) {
                xfor2++;
                if(map[yfor2][xfor2]=='|' || map[yfor2][xfor2]=='_'){
                    counterfor2=0;
                    if(map[yfor2][xfor2-1]=='.')
                    {
                        map[yfor2][xfor2-1]='z';
                    }
                }
            }
            else if(dw==1) {
                yfor2--;
                if(map[yfor2][xfor2]=='|' || map[yfor2][xfor2]=='_'){
                    counterfor2=0;
                    if(map[yfor2+1][xfor2]=='.')
                    {
                        map[yfor2+1][xfor2]='z';
                    }
                }
            }

            counterfor2++;
            if(counterfor2 >= 5) {
                if(map[yfor2][xfor2]=='.'){
                    map[yfor2][xfor2]='z'; // z represents 1 dagger
                }
                start_dagger = 0;
                counterfor2 = 0;
                dd=0; da=0; dw=0; ds=0;
            }
            if(map[yfor2][xfor2]=='.'){
                mvaddch(yfor2, xfor2, '*');
            }
            mvprintw(3, 3, "                                                            ");
            refresh();
        }
        ////////////


        ///////////normal arrow
        if(in_use_weapon == 4 && previous_c == 'p') {
            start_normal_arrow = 1;
            xfor4 = new_x;
            yfor4 = new_y;
            counterfor4 = 1;
            switch (c) {
                case 'a':
                    na++; break;
                case 'w':
                    nw++; break;
                case 's':
                    ns++; break;
                case 'd':
                    nd++; break;
            }

            current_user->weapons.Normal_Arrow_count--;
            if(current_user->weapons.Normal_Arrow_count < 0) {
                current_user->weapons.Normal_Arrow_count = 0;
            }
        }

        if(start_normal_arrow == 1 && counterfor4 > 0) {

            if(xfor4 == new_x_f && yfor4 == new_y_f) {
                fire_health -= 10*k;
                if(fire_health <= 0) fire_health = 0;
                mvprintw(3, 3, "You hit Fire breathing monster!  health: %d/10                   ", fire_health);
                counterfor4=0;
                start_normal_arrow=0;
            }
            if(xfor4 == new_x_s && yfor2 == new_y_s) {
                snake_health -= 10*k;
                if(snake_health <= 0) snake_health = 0;
                mvprintw(3, 3, "You hit Snake!  health: %d/20                                    ", snake_health);
                counterfor4=0;
                start_normal_arrow=0;
            }

            if(xfor2 == new_x_g && yfor2 == new_y_g) {
                giant_health -= 10*k;
                if(giant_health <= 0) giant_health = 0;
                mvprintw(3, 3, "You hit Gaint!  health: %d/15                                    ", giant_health);
                counterfor4=0;
                start_normal_arrow=0;
            }

            if(xfor4 == xd && yfor4== yd) {
                deamon_health -= 10*k;
                if(deamon_health <= 0) deamon_health = 0;
                mvprintw(3, 3, "You hit Deamon!  health: %d/5                           ", deamon_health);
                counterfor4=0;
                start_normal_arrow=0;
            }

            if(na==1) {
                xfor4--;
                if(map[yfor4][xfor4]=='|' || map[yfor4][xfor4]=='_'){
                    counterfor4=0;
                    if(map[yfor4][xfor4+1]=='.')
                    {
                        map[yfor4][xfor4+1]='c';
                    }
                }
            }
            else if(ns==1) {
                yfor4++;
                if(map[yfor4][xfor4]=='|' || map[yfor4][xfor4]=='_'){
                    counterfor4=0;
                    if(map[yfor4-1][xfor4]=='.')
                    {
                        map[yfor4-1][xfor4]='c';
                    }
                }
            }
            else if(nd==1) {
                xfor4++;
                if(map[yfor4][xfor4]=='|' || map[yfor4][xfor4]=='_'){
                    counterfor4=0;
                    if(map[yfor4][xfor4-1]=='.')
                    {
                        map[yfor4][xfor4-1]='c';
                    }
                }
            }
            else if(nw==1) {
                yfor4--;
                if(map[yfor4][xfor4]=='|' || map[yfor4][xfor4]=='_'){
                    counterfor4=0;
                    if(map[yfor4+1][xfor4]=='.')
                    {
                        map[yfor4+1][xfor4]='c';
                    }
                }
            }

            counterfor4++;
            if(counterfor4 >= 5) {
                if(map[yfor4][xfor4]=='.'){
                    map[yfor4][xfor4]='c'; // c represents 1 normal arrow
                }
                start_normal_arrow = 0;
                counterfor4 = 0;
                nd=0; na=0; nw=0; ns=0;
            }
            if(map[yfor4][xfor4]=='.'){
                mvaddch(yfor4, xfor4, '-');
            }

            refresh();
        }
        ////////////

        ///////////Magic wand
        if(in_use_weapon == 3 && previous_c == 'p') {
            start_magic_wand = 1;
            xfor3 = new_x;
            yfor3 = new_y;
            counterfor3 = 1;
            switch (c) {
                case 'a':
                    ma++; break;
                case 'w':
                    mw++; break;
                case 's':
                    ms++; break;
                case 'd':
                    md++; break;
            }

            current_user->weapons.Magic_Wand_count--;
            if(current_user->weapons.Magic_Wand_count < 0) {
                current_user->weapons.Magic_Wand_count = 0;
            }
        }

        if(start_magic_wand == 1 && counterfor3 > 0) {

            if(xfor3 == new_x_f && yfor3 == new_y_f) {
                fire_health -= 15*k;
                if(fire_health <= 0) fire_health = 0;
                mvprintw(3, 3, "You hit Fire breathing monster!  health: %d/10                   ", fire_health);
                counterfor3=0;
                start_magic_wand=0;
            }
            if(xfor3 == new_x_s && yfor3 == new_y_s) {
                snake_health -= 15*k;
                if(snake_health <= 0) snake_health = 0;
                mvprintw(3, 3, "You hit Snake!  health: %d/20                                    ", snake_health);
                counterfor3=0;
                snake_chase=0;
                start_magic_wand=0;
            }
            if(xfor3 == xd && yfor3 == yd) {
                deamon_health -= 15*k;
                if(deamon_health <= 0) deamon_health = 0;
                mvprintw(3, 3, "You hit Deamon!  health: %d/5                                     ", deamon_health);
                counterfor3=0;
                start_magic_wand=0;
            }
            if(xfor2 == new_x_g && yfor2 == new_y_g) {
                giant_health -= 15*k;
                if(giant_health <= 0) giant_health = 0;
                mvprintw(3, 3, "You hit Gaint!  health: %d/15                                    ", giant_health);
                counterfor3=0;
                start_magic_wand=0;
            }

            if(ma==1) {
                xfor3--;
                if(map[yfor3][xfor3]=='|' || map[yfor3][xfor3]=='_'){
                    counterfor3=0;
                    if(map[yfor3][xfor3+1]=='.')
                    {
                        map[yfor3][xfor3+1]='x';
                    }
                }
            }
            else if(ms==1) {
                yfor3++;
                if(map[yfor3][xfor3]=='|' || map[yfor3][xfor3]=='_'){
                    counterfor3=0;
                    if(map[yfor3-1][xfor3+1]=='.')
                    {
                        map[yfor3-1][xfor3+1]='x';
                    }
                }
            }
            else if(md==1) {
                xfor3++;
                if(map[yfor3][xfor3]=='|' || map[yfor3][xfor3]=='_'){
                    counterfor3=0;
                    if(map[yfor3][xfor3-1]=='.')
                    {
                        map[yfor3][xfor3-1]='x';
                    }
                }
            }
            else if(mw==1) {
                yfor3--;
                if(map[yfor3][xfor3]=='|' || map[yfor3][xfor3]=='_'){
                    counterfor3=0;
                    if(map[yfor3+1][xfor3]=='.')
                    {
                        map[yfor3+1][xfor3]='x';
                    }
                }
            }

            counterfor3++;
            if(counterfor3 >= 5) {
                if(map[yfor3][xfor3]=='.'){
                    map[yfor3][xfor3]='x'; // x represents 1 magic wand
                }
                start_magic_wand = 0;
                counterfor3 = 0;
                md=0; ma=0; mw=0; ms=0;
            }
            if(map[yfor3][xfor3]=='.'){
                mvaddch(yfor3, xfor3, '+');
            }
            mvprintw(2, 3, "                                                            ");
            refresh();
        }
        ////////////


        if(locked[cordinate_locked[0]][cordinate_locked[1]]==1 && (new_y+1==cordinate_locked[0] && new_x==cordinate_locked[1] ||
                                                                   new_y-1==cordinate_locked[0] && new_x==cordinate_locked[1] ||
                                                                   new_y==cordinate_locked[0] && new_x+1==cordinate_locked[1] ||
                                                                   new_y==cordinate_locked[0] && new_x-1==cordinate_locked[1] )){
            mvprintw(4,3,"                                                               ",password);
            if (no_lock==0){
                if(password_counter>3){
                    attron(COLOR_PAIR(14));
                    mvprintw(3,3,"The door has been locked forever!!                   ");
                    attroff(COLOR_PAIR(14));
                }
                else {
                    mvprintw(3,3,"The door is locked. Press L to enter the pass !");
                }
                if(c=='l' && password_counter<=3){
                    status=code(password);password_counter++;
                }
                if(status==1 && password_counter<=3 ){
                    locked[cordinate_locked[0]][cordinate_locked[1]]=2;
                    mvprintw(3,3,"The door is unlocked !                                       ");

                }
                else if(status==0 && password_counter<=3){
                    if(password_counter==1){
                        attron(COLOR_PAIR(12));
                        mvprintw(3,3,"Wrong password!                                ");
                        attroff(COLOR_PAIR(12));
                    }
                    else if(password_counter==2){
                        attron(COLOR_PAIR(13));
                        mvprintw(3,3,"Wrong password!                                ");
                        attroff(COLOR_PAIR(13));
                    }
                    else if(password_counter==3){
                        attron(COLOR_PAIR(14));
                        mvprintw(3,3,"Wrong password! Door locked forever!!                          ");
                        attroff(COLOR_PAIR(14));
                    }
                }



            }
            else if(no_lock==1){
                locked[cordinate_locked[0]][cordinate_locked[1]]=2;
                mvprintw(3,3,"The door is unlocked !                                       ");
                mvprintw(3,3,"                                                            ");
            }


        }
        if(counter==40){
            strcpy(password,"0");
        }
        if(food>=10){
            if(food4health_counter>=4){
                if(current_user->spells.health_spell_counter>0){
                    health+=2;
                    current_user->spells.health_spell_counter-=1;
                    if(current_user->spells.health_spell_counter<0) current_user->spells.health_spell_counter=0;
                }
                else{
                    health+=1;
                }
                if(health>10) health=10;
                food4health_counter=0;
            }
        }

        mvprintw(max_y-2,60,"floor : 4");
        counter++;

        //health
        mvprintw(max_y-2,2,"health: ");
        refresh();
        for(int i =0;i<=health;i++){
            mvprintw(max_y-2,10+i,"♥");
            mvprintw(max_y-2,10+health," ");
            for(int j=0;j<10-i;j++){
                mvprintw(max_y-2,10+health+j," ");
            }
            mvprintw(max_y-2,10+12,"%d%c",health*10,'%');

        }

        //food
        mvprintw(max_y-2,32,"food: ");

        for(int i =0;i<=food;i++){
            mvprintw(max_y-2,38+i,"+");
            mvprintw(max_y-2,38+food," ");
            mvprintw(max_y-2,38 + 12,"     ");
            mvprintw(max_y-2,38 + 12,"%d%c",food*10,'%');
            refresh();
        }
        refresh();

        if(in_use_weapon==1){
            mvprintw(max_y-2,74,"weapon: Mace");
        }
        else if(in_use_weapon==2){
            mvprintw(max_y-2,74,"weapon: Dagger");
        }
        else if(in_use_weapon==3){
            mvprintw(max_y-2,74,"weapon: Magic Wand");
        }
        else if(in_use_weapon==4){
            mvprintw(max_y-2,74,"weapon: Normal Arrow");
        }
        else if(in_use_weapon==4){
            mvprintw(max_y-2,74,"weapon: Sword");
        }
        else {
            mvprintw(max_y-2,74,"weapon: no weapon in use!");
        }


        refresh();
        if( map[new_y][new_x]=='#'){
            int temp = cori_number[new_y][new_x];
            for(int j=-4;j<4;j++){
                for(int i=-4;i<4;i++){
                    if(cori_number[new_y+j][new_x+i]==temp && map[new_y+j][new_x+i]=='#' && visited[new_y+j][new_x+i]!=1 || map[new_y+j][new_x+i]=='+'){
                        visited[new_y+j][new_x+i]=1;
                    }
                }
            }
        }

        else if(map[new_y][new_x]=='+' ){
            int tempp=room_number[new_y][new_x];
            for(int j1=0;j1<max_y;j1++){
                for (int i1 = 0; i1 < max_x; i1++) {
                    if(visited[j1][i1]!=1 && room_number[j1][i1]==tempp){
                        visited[j1][i1]=1;
                    }
                }
            }
        }


        previous_x = new_x;
        previous_y = new_y;
        previous_c =c;
        food4health_counter++;

    } while ((c = getch()) != 27);

    endwin();
}

int treasure_room(struct user *current_user , int level){

    setlocale(LC_ALL, "");
    initscr();
    keypad(stdscr, TRUE);
    noecho();
    curs_set(0);
    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);
    char map[max_y][max_x];

    //--------------------------
    int visited[max_y][max_x];
    for(int j=0;j<max_y;j++){
        for(int i=0;i<max_x;i++){
            visited[j][i]=0;
        }
    }

    int room_number[max_y][max_x];
    for(int j=0;j<max_y;j++){
        for(int i=0;i<max_x;i++){
            room_number[j][i]=0;
        }
    }

    int cori_number[max_y][max_x];
    for(int j=0;j<max_y;j++){
        for(int i=0;i<max_x;i++){
            cori_number[j][i]=0;
        }
    }

    ///.........weapons

    int in_use_weapon= current_user->weapons.in_use_weapon;

    //.........................


    for(int i = 0; i < max_y; i++) {
        for(int j = 0; j < max_x; j++) {
            map[i][j] = ' ';
        }
    }

    srand(time(NULL));
    int number_of_rooms = 1;
    int num = 0;

    typedef struct {
        int center_x;
        int center_y;
        int room_x;
        int room_y;
        int room_x_size;
        int room_y_size;

    } RoomCenter;
    RoomCenter centers[number_of_rooms];

    //generating rooms
    while (num < number_of_rooms) {
        int ok = 0;
        int size_room_y, size_room_x, room_y, room_x;

        while (ok == 0) {


            size_room_y = 21;
            size_room_x = 21;


            room_y = max_y/2 -10;
            room_x = max_x/2 -7;

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
                    room_number[room_y + i][room_x + j]=num+1; //room number
                }
            }
        }

        num++;
    }


    //////////////////////

    //pillars
    int num_pillars= 3 + (rand() % 4);
    int np=0 ,py ,px;
    while(np<num_pillars){
        py = rand() % max_y  + 1;
        px = rand() % max_x  + 1;
        if(map[py][px]=='.' && map[py+1][px]!='+' && map[py][px-1]!='+' && map[py][px+1]!='+' && map[py-1][px]!='+'){
            map[py][px]='O';
            np++;
        }
    }
    //traps
    int num_traps;
    if(current_user->game_setting.game_level==0){
        num_traps= 10+ (rand() % 3);
    }
    else if(current_user->game_setting.game_level==1){
        num_traps= 12 + (rand() % 5);
    }
    else if(current_user->game_setting.game_level==2){
        num_traps= 14 + (rand() % 7);
    }
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
    int num_foods;
    if(current_user->game_setting.game_level==0){
        num_foods= 8 + (rand() % 3);
    }
    else if(current_user->game_setting.game_level==1){
        num_foods= 6 + (rand() % 3);
    }
    else if(current_user->game_setting.game_level==2){
        num_foods= 4 + (rand() % 2);
    }

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
    int num_ygolds= 12 + (rand() % 4);
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
    int num_bgolds= 10 + (rand() % 1);
    int nbg=0 ,by ,bx;
    while(nbg<num_bgolds){
        by = rand() % max_y  + 1;
        bx = rand() % max_x  + 1;
        if(map[by][bx]=='.'){
            map[by][bx]='@';
            nbg++;
        }
    }


    int x2 = 0, y2 = 0;
    int stairs = 0;
    while(!stairs) {
        y2 = rand() % max_y  + 1;
        x2 = rand() % max_x  + 1;
        if(map[y2][x2]=='.'){
            map[y2][x2]='<';
            stairs++;
        }
    }

    int y=y2;
    int x=x2;

    int room_num=room_number[y][x];

    for(int i=0;i<max_x;i++){
        for(int j=0;j<max_y;j++){
            if(room_number[j][i]==room_num){
                visited[j][i]=1;
            }
        }
    }

    //weapons
    int weapon_num= 2 + rand() % 4;
    int x3=0,y3=0;
    int weaponi =0 ;
    while(!weaponi){
        y3 = rand() % max_y ;
        x3 = rand() % max_x ;
        if(map[y3][x3]=='.'){
            if(weapon_num==1){
                map[y3][x3]='1';
                weaponi++;
            }
            else if(weapon_num==2){
                map[y3][x3]='2';
                weaponi++;
            }
            else if(weapon_num==3){
                map[y3][x3]='3';
                weaponi++;
            }

            else if(weapon_num==4){
                map[y3][x3]='4';
                weaponi++;
            }

            else if(weapon_num==5){
                map[y3][x3]='5';
                weaponi++;
            }
        }
    }

    weapon_num= 2 + rand() % 4;
    x3=0,y3=0;
    weaponi =0 ;
    while(!weaponi){
        y3 = rand() % max_y ;
        x3 = rand() % max_x ;
        if(map[y3][x3]=='.'){
            if(weapon_num==1){
                map[y3][x3]='1';
                weaponi++;
            }
            else if(weapon_num==2){
                map[y3][x3]='2';
                weaponi++;
            }
            else if(weapon_num==3){
                map[y3][x3]='3';
                weaponi++;
            }

            else if(weapon_num==4){
                map[y3][x3]='4';
                weaponi++;
            }

            else if(weapon_num==5){
                map[y3][x3]='5';
                weaponi++;
            }
        }
    }

    stairs = 0;
    while(!stairs) {
        y2 = rand() % max_y  + 1;
        x2 = rand() % max_x  + 1;
        if(map[y2][x2]=='.'){
            map[y2][x2]='<';
            stairs++;
        }
    }

    ///--->> deamon <<---///
    int xd=0, yd=0;
    int countd=0;
    while (countd==0){
        xd = rand() % max_x;
        yd = rand() % max_y;
        if(map[yd][xd]=='.'){
            countd++;
        }
    }
    ////////////////////////

    ///--->> fire breathing monster <<---///
    int xf=0, yf=0;
    int countf=0;
    while (countf==0){
        xf = rand() % max_x;
        yf = rand() % max_y;
        if(map[yf][xf]=='.'){
            countf++;
        }
    }
    ////////////////////////
    int xs=0, ys=0;
    ///--->> snake <<---///
    if(current_user->game_setting.snake_chasing==1){
        xs = x; ys=y;
    }
    else {
        int counts=0;
        while (counts==0){
            xs = rand() % max_x;
            ys = rand() % max_y;
            if(map[ys][xs]=='.'){
                counts++;
            }
        }
    }

    ////////////////////////

    ///--->> giant <<---///
    int xg=0, yg=0;
    int countg=0;
    while (countg==0){
        xg = rand() % max_x;
        yg = rand() % max_y;
        if(map[yg][xg]=='.'){
            countg++;
        }
    }
    ////////////////////////

    ///--->> undeed <<---///
    int xu=0, yu=0;
    int countu=0;
    while (countu==0){
        xu = rand() % max_x;
        yu = rand() % max_y;
        if(map[yu][xu]=='.'){
            countu++;
        }
    }
    //////////////////////


// speed spell
    int x_speed_spell=0, y_speed_spell=0;
    int countof= 1+  rand() % 2;
    while (countof!=0){
        x_speed_spell = rand() % max_x;
        y_speed_spell = rand() % max_y;
        if(map[y_speed_spell][x_speed_spell]=='.'){
            map[y_speed_spell][x_speed_spell]='n'; //n stands for speed spell
            countof--;
        }
    }
    // health spell
    int x_health_spell=0, y_health_spell=0;
    countof= 1 + rand() % 2;
    while (countof!=0){
        x_health_spell = rand() % max_x;
        y_health_spell = rand() % max_y;
        if(map[y_health_spell][x_health_spell]=='.'){
            map[y_health_spell][x_health_spell]='b'; //b stands for health spell
            countof--;
        }
    }

    //damage spell
    int x_damage_spell=0, y_damage_spell=0;
    countof= 1 + rand() % 2;
    while (countof!=0){
        x_damage_spell = rand() % max_x;
        y_damage_spell = rand() % max_y;
        if(map[y_damage_spell][x_damage_spell]=='.'){
            map[y_damage_spell][x_damage_spell]='m'; //m stands for health spell
            countof--;
        }
    }





    ////////////////

    clear();

    init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(6, COLOR_YELLOW, COLOR_BLACK);
    init_pair(7, COLOR_BLACK, COLOR_WHITE);
    init_pair(8, COLOR_YELLOW, COLOR_RED);
    init_pair(9, COLOR_CYAN, COLOR_BLACK);
    init_pair(10,COLOR_RED,COLOR_BLACK);
    init_pair(11,COLOR_GREEN,COLOR_BLACK);
    ////////////////////
    int total_yellow_gold=0;
    int total_black_gold=0;
    /////////////////////

    int food=current_user->food;
    int food1=current_user->food1;
    int health=current_user->health;


    ///////////////////////MAIN///////

    // printing map (player movement -- map)
    int c;
    int counter=0;

    char password[100]={0};
    int password_counter=0;
    int previous_x=0 , previous_y=0;
    int deamon_health=5;
    int fire_health = 10;
    int giant_health = 15;
    int snake_health = 20;
    int undeed_health = 30;
    int snake_chase=0;
    char previous_c;
    int start_normal_arrow=0;  int xfor4, yfor4, counterfor4;int nw=0,na=0,ns=0,nd=0;
    int start_magic_wand=0;  int xfor3, yfor3, counterfor3;int mw=0,ma=0,ms=0,md=0;
    int start_dagger=0;  int xfor2, yfor2, counterfor2; int dw=0,da=0,ds=0,dd=0;
    int is_sth_here[max_y][max_x];
    for(int j=0;j<max_y;j++){
        for(int i=0;i<max_x;i++){
            is_sth_here[j][i]=0;
        }
    }

    int food4health_counter=0;
    int k=1;
    init_color(27,1000,800,0);
    init_pair(40,30,COLOR_BLACK);


    do {
        //print map
        for(int i = 0; i < max_y; i++) {
            for(int j = 0; j < max_x; j++) {
                if(map[i][j] != ' ' && visited[i][j]==1) {
                    if(map[i][j]=='|'){
                        attron(COLOR_PAIR(40));
                        mvaddch(i, j, '|');
                        attroff(COLOR_PAIR(40));
                    }
                    else if(map[i][j]=='_'){
                        attron(COLOR_PAIR(40));
                        mvaddch(i, j, 'o');
                        attroff(COLOR_PAIR(40));
                    }
                    else if(map[i][j]=='O'){
                        attron(COLOR_PAIR(5));
                        mvaddch(i, j, map[i][j]);
                        attroff(COLOR_PAIR(5));
                    }
                    else if(map[i][j]=='$'){
                        attron(COLOR_PAIR(6));
                        mvprintw(i, j, "%lc", (wint_t)0x25C6);
                        attroff(COLOR_PAIR(6));
                    }
                    else if (map[i][j] == '@') {
                        init_color(21, 1000, 400, 1000);
                        init_pair(44,21,COLOR_BLACK);
                        attron(COLOR_PAIR(44));
                        mvprintw(i, j, "%lc", (wint_t) 0x25C6);
                        attroff(COLOR_PAIR(44));
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
                    else if(map[i][j]=='1') {
                        attron(COLOR_PAIR(9));
                        mvaddch(i, j, 'M');
                        attroff(COLOR_PAIR(9));
                        //mvprintw(i, j, "%lc", (wint_t)0x2692); // ⚒
                    }
                    else if(map[i][j]=='2' || map[i][j]=='z') {
                        mvprintw(i, j, "%lc", (wint_t)0x1F5E1); // 🗡 ok
                    }
                    else if(map[i][j]=='3'|| map[i][j]=='x') {
                        attron(COLOR_PAIR(9));
                        mvaddch(i, j, 'W');
                        attroff(COLOR_PAIR(9));
                        // mvprintw(i, j, "%lc", (wint_t)0x1FA84); // 🪄
                    }
                    else if(map[i][j]=='4'|| map[i][j]=='c') {
                        mvprintw(i, j, "%lc", (wint_t)0x27B3); // ➳ ok
                    }
                    else if(map[i][j]=='5') {
                        attron(COLOR_PAIR(9));
                        mvaddch(i, j, 'S');
                        attroff(COLOR_PAIR(9));
                        //mvprintw(i, j, "%lc", (wint_t)0x2694); // ⚔
                    }

                    else if (map[i][j] == '=') {
//                        mvprintw(i, j, "%lc", (wint_t) 0x23F9);
                        mvaddch(i, j, '&');
                    } else if (map[i][j] == '/') {
                        attron(COLOR_PAIR(6));
                        mvprintw(i, j, "%lc", (wint_t) 0x25B3);
                        attroff(COLOR_PAIR(6));
                    } else if (map[i][j] == 'b') { //health spell
                        attron(COLOR_PAIR(10));
                        mvprintw(i, j, "%lc", (wint_t)0x271A);
                        attroff(COLOR_PAIR(10));
                    } else if (map[i][j] == 'n') { //speed spell
                        attron(COLOR_PAIR(6));
                        mvprintw(i, j, "%lc", (wint_t) 0x27A4);
                        attroff(COLOR_PAIR(6));
                    } else if (map[i][j] == 'm') { //damage spell
                        init_color(24, 1000, 200, 0);
                        init_pair(45,24,COLOR_BLACK);
                        attron(COLOR_PAIR(45));
                        mvprintw(i, j, "%lc", (wint_t) 0x23FA);
                        attroff(COLOR_PAIR(45));
                    }

                    else if (map[i][j]!='1'){
                        mvaddch(i, j, map[i][j]);

                    }

                }
            }
        }

        int new_y = y;
        int new_x = x;

        if(c=='h'){
            help();
        }

        if(c=='i'){
            clear();
            in_use_weapon= weapon(current_user,in_use_weapon);

        }

        if(c ==101) { ///food window
            clear();
            int p= food_bar(&food1, &health, &food);
            if(p==3){
                continue;
            }
            c = getch();
        }
        mvprintw(2,max_x-30,"[h] to open help menu");

        ///movement

        if(current_user->spells.speed_spell_counter>0){
            if (c == KEY_UP && y > 0) new_y-=2;
            if (c == KEY_DOWN && y < max_y - 1) new_y+=2;
            if (c == KEY_RIGHT && x < max_x - 1) new_x+=2;
            if (c == KEY_LEFT && x > 0) new_x-=2;
            current_user->spells.speed_spell_counter-=1;
            if(current_user->spells.speed_spell_counter==0) current_user->spells.speed_spell_counter=0;
        }
        else{
            if (c == KEY_UP && y > 0) new_y--;
            if (c == KEY_DOWN && y < max_y - 1) new_y++;
            if (c == KEY_RIGHT && x < max_x - 1) new_x++;
            if (c == KEY_LEFT && x > 0) new_x--;

        }

        if(current_user->spells.damage_spell_counter>0){
            k=2;
            current_user->spells.damage_spell_counter-=1;
            if (current_user->spells.damage_spell_counter<0) current_user->spells.damage_spell_counter=0;
        } else {
            k=1;
        }



        if(  map[new_y][new_x] == '$'|| map[new_y][new_x] == '@' || map[new_y][new_x] == '.' ||
            map[new_y][new_x] == '#'  || map[new_y][new_x] == 'F' || map[new_y][new_x]=='T' || map[new_y][new_x]=='^' ||
            map[new_y][new_x] == '1'  || map[new_y][new_x] == '2' || map[new_y][new_x]=='3' || map[new_y][new_x]=='4' ||
            map[new_y][new_x] == '5'  || map[new_y][new_x]=='=' || map[new_y][new_x]=='/' || map[new_y][new_x]=='z'||
            map[new_y][new_x] == 'x'  || map[new_y][new_x] == 'c' || map[new_y][new_x] == 'b' || map[new_y][new_x] == 'n'||
            map[new_y][new_x] == 'm') {


            mvprintw(2,1,"  ");

            if(map[new_y][new_x]=='b'){
                mvprintw(2,3,"You claimed a Health potion              ");
                current_user->spells.health_spell++;
            }

            if(map[new_y][new_x]=='n'){
                mvprintw(2,3,"You claimed a Speed potion              ");
                current_user->spells.speed_spell++;

            }

            if(map[new_y][new_x]=='m'){
                mvprintw(2,3,"You claimed a Damage potion              ");
                current_user->spells.damage_spell++;
            }


            if(map[new_y][new_x]=='=' && password_counter<=3){
                char arrpass[]="0123456789";
                for(int i9=0;i9<4;i9++){
                    int temp=rand() % 9;
                    password[i9]=arrpass[temp];
                }
                mvprintw(2,3,"Password is %s                                           ",password);

            }

            if(map[new_y][new_x] == '$'){
                int temp = 2 + (rand() % 3 );
                mvprintw(2,3,"You claimed %d GOLDS !            ",temp);
                total_yellow_gold+= temp;
            }
            if(map[new_y][new_x] == '@'){
                int temp = 6 + (rand() % 4 );
                mvprintw(2,3,"You claimed %d GOLDS !            ",temp);
                total_black_gold+= temp;
            }
            if(map[new_y][new_x] == 'F'){
                int temp = 1;
                mvprintw(2,3,"You claimed %d FOOD !             ",temp);
                food1+= 1;
                if(food1>5){
                    food1=5;
                }
            }


            if(map[new_y][new_x] == 'T'){
                int temp = 1;
                mvprintw(2,3,"You stepped on a TRAP !           ",temp);
                if(current_user->game_setting.game_level==0){
                    health -= 1;
                } else{
                    health -= 2;
                }
                if(health<0){
                    health=0;
                }
                refresh();
                map[new_y][new_x]='^';
            }

            current_user->weapons.Mace=1;

            if(map[new_y][new_x] == '2'){
                current_user->weapons.Dagger=1;
                mvprintw(2,3,"You found a Dagger! +10                  ");
                current_user->weapons.Dagger_count+=10;
            }
            if(map[new_y][new_x] == 'z'){
                current_user->weapons.Dagger=1;
                mvprintw(2,3,"You found a Dagger! +1                  ");
                current_user->weapons.Dagger_count+=1;
            }


            if(map[new_y][new_x] == '3'){
                current_user->weapons.Magic_Wand=1;
                mvprintw(2,3,"You found a Magic Wand! +8             ");
                current_user->weapons.Magic_Wand_count+=8;
            }
            if(map[new_y][new_x] == 'x'){
                current_user->weapons.Magic_Wand=1;
                mvprintw(2,3,"You found a Magic Wand! +1             ");
                current_user->weapons.Magic_Wand_count+=1;
            }


            if(map[new_y][new_x] == '4'){
                current_user->weapons.Normal_Arrow=1;
                mvprintw(2,3,"You found a Normal Arrow! +20          ");
                current_user->weapons.Normal_Arrow_count+=20;
            }
            if(map[new_y][new_x] == 'c'){
                current_user->weapons.Normal_Arrow=1;
                mvprintw(2,3,"You found a Normal Arrow! +1          ");
                current_user->weapons.Normal_Arrow_count+=1;
            }


            if(map[new_y][new_x] == '5'){
                current_user->weapons.Sword=1;
                mvprintw(2,3,"You found a Sword!                   ");
            }
            y = new_y;
            x = new_x;
        }
        mvprintw(3,3,"                                                      ",password);

        if(map[y][x]!='+' && map[y][x]!='#'&&map[y][x]!='^' && map[y][x]!='='){
            map[y][x]='.';
        }

        if(c=='o'){
            potion(current_user);
        }

        mvprintw(max_y-2,max_x-10,"GOLD: %d",current_user->new_golds+total_black_gold+total_yellow_gold);



        //deamon ////////

        if(deamon_health>0){

            if(room_number[new_y][new_x]==room_number[yd][xd]){
                move_deamon(yd,xd);
            }
            if(deamon_health>=0 && xd==new_x && yd==new_y){
                if(current_user->game_setting.game_level==0){
                    health -= 1;
                } else{
                    health -= 2;
                }
                mvprintw(3,3,"Deamon hits you!                            ");
                if(health<0){
                    health=0;
                }
            }
            refresh();

        }

        ////////--------------------------


        //fire breathing monster//////////////
        int new_x_f , new_y_f;
        int fx = new_x - xf;
        int fy = new_y - yf;

        if(fire_health>0){

            if(room_number[new_y][new_x] == room_number[yf][xf]  ) {

                new_x_f = xf;
                new_y_f = yf;

                if((abs(fx)<=6 || abs(fy)<=6 )){
                    if (abs(fx) > abs(fy)) {
                        if (fx > 0) {
                            new_x_f += 1;
                        } else {
                            new_x_f -= 1;
                        }
                    } else {
                        if (fy > 0) {
                            new_y_f += 1;
                        } else {
                            new_y_f -= 1;
                        }
                    }

                }

                move_fire_breathing_monster(new_y_f, new_x_f);
            }
            refresh();

            if(fire_health>=0 && new_x_f==new_x && new_y_f==new_y){
                if(current_user->game_setting.game_level==0){
                    health -= 1;
                } else{
                    health -= 2;
                }
                mvprintw(3,3,"Fire breathing monster hits you!                                ");
                if(health<0){
                    health=0;
                }
            }


        }



        /////


        ///giant
        int new_x_g , new_y_g;
        int gx = new_x - xg;
        int gy = new_y - yg;



        if(giant_health>0){

            if(giant_health>0){
                if(room_number[new_y][new_x] == room_number[yf][xf]  ) {
                    new_x_g = xg;
                    new_y_g = yg;

                    if (abs(gx) > abs(gy)) {
                        if (gx > 0) {
                            new_x_g = new_x+1;
                        } else {
                            new_x_g = new_x-1;
                        }
                        new_y_g=new_y;
                    } else {
                        if (gy > 0) {
                            new_y_g = new_y+1;
                        } else {
                            new_y_g = new_y-1;
                        }
                        new_x_g=new_x;
                    }

                    move_giant(new_y_g, new_x_g);
                }
                refresh();

                if(giant_health>=0 && new_x_g==new_x && new_y_g==new_y){
                    if(current_user->game_setting.game_level==0){
                        health -= 1;
                    } else{
                        health -= 2;
                    }
                    mvprintw(3,3,"Giant hits you!                                     ");
                    if(health<0){
                        health=0;
                    }
                }


            }
        }

        ///undeed
        int new_x_u , new_y_u;
        int ux = new_x - xu;
        int uy = new_y - yu;

        if(undeed_health>0){

            if(abs(gx)<=7 || abs(gy)<=7) {

                new_x_u = xu;
                new_y_u = yu;

                if (abs(ux) > abs(uy)) {
                        if (ux > 0) {
                            new_x_u += 1;
                        } else {
                            new_x_u -= 1;
                        }
                    } else {
                        if (uy > 0) {
                            new_y_u += 1;
                        } else {
                            new_y_u -= 1;
                        }
                    }
                move_undeed(new_y_u, new_x_u);
            }
            refresh();

            if(undeed_health>=0 && new_x_u==new_x && new_y_u==new_y){
                if(current_user->game_setting.game_level==0){
                    health -= 1;
                } else{
                    health -= 2;
                }
                mvprintw(3,3,"Undeed hits you!                                ");
                if(health<0){
                    health=0;
                }
            }

        }


        ////////


        //////----------------------
        ////snake////////////////////////
        int new_y_s;
        int new_x_s;
        if(room_number[new_y][new_x]==room_number[ys][xs] && snake_health>0){
            snake_chase=1;

        }
        if(snake_chase==1 && snake_health>0){
            new_x_s = previous_x;
            new_y_s = previous_y;
            refresh();
            if(map[new_y_s][new_x_s]!=' '){
                move_snake(new_y_s,new_x_s );
            }
        }

        if(snake_health>0 && new_x_s==new_x && new_y_s==new_y){
            if(current_user->game_setting.game_level==0){
                health -= 1;
            } else{
                health -= 2;
            }
            mvprintw(3,3,"Snake hits you!                                 ");
            if(health<0){
                health=0;
            }
        }
        refresh();

        ////////////---------------------//

        draw_character(y, x, current_user->game_setting.player_color);

        if(current_user->game_setting.game_level==0){
            if(counter==40){
                health--;
                counter=0;
            }
        }
        else if(current_user->game_setting.game_level==1){
            if(counter==25){
                health--;
                counter=0;
            }
        }
        else if(current_user->game_setting.game_level==2){
            if(counter==15){
                health--;
                counter=0;
            }
        }

        if(current_user->game_setting.game_level==0){
            if(counter==30){
                food--;
            }
        }
        else if(current_user->game_setting.game_level==1){
            if(counter==20){
                food--;
            }
        }
        else if(current_user->game_setting.game_level==2){
            if(counter==10){
                food--;
            }
        }

        if(health==0){
            current_user->new_golds+=total_black_gold+total_yellow_gold;
            current_user->total_gold+=current_user->new_golds;
            return 0;
        }


        int dx = xd - new_x;
        int dy = yd - new_y;
        fx = new_x_f -  new_x;
        fy = new_y_f - new_y;
        int sx = new_x_s -  new_x;
        int sy = new_y_s - new_y;
        gx = new_x_g - new_x;
        gy = new_y_g - new_y;
        ux = new_x_u - new_x;
        uy = new_y_u - new_y;

        if(c=='p' || c=='P') {
            if (in_use_weapon == 1) {
                if ((abs(dy) == 1 || abs(dy) == -1 || abs(dy) == 0) &&
                    (abs(dx) == 1 || abs(dx) == -1 || abs(dx) == 0)) {
                    deamon_health -= 5*k;
                    if (deamon_health <= 0) {
                        deamon_health = 0;
                    }
                    mvprintw(3, 3, "You hit Deamon!  health: %d/5                           ", deamon_health);


                }
                else if ((abs(fy) == 1 || abs(fy) == -1 || abs(fy) == 0) &&
                    (abs(fx) == 1 || abs(fx) == -1 || abs(fx) == 0)) {
                    fire_health -= 5*k;
                    if (fire_health <= 0) {
                        fire_health = 0;
                    }
                    mvprintw(3, 3, "You hit Fire breathing monster!  health: %d/10                   ", fire_health);


                }
                else if ((abs(sy) == 1 || abs(sy) == -1 || abs(sy) == 0) &&
                    (abs(sx) == 1 || abs(sx) == -1 || abs(sx) == 0)) {
                    snake_health -= 5*k;
                    if (snake_health <= 0) {
                        snake_health = 0;
                    }
                    mvprintw(3, 3, "You hit Snake!  health: %d/20                                    ", snake_health);

                }
                else if ((abs(gy) == 1 || abs(gy) == -1 || abs(gy) == 0) &&
                    (abs(gx) == 1 || abs(gx) == -1 || abs(gx) == 0)) {
                    giant_health -= 5*k;
                    if (giant_health <= 0) {
                        giant_health = 0;
                    }
                    mvprintw(3, 3, "You hit Giant!  health: %d/15                                    ", giant_health);

                }
                else if ((abs(uy) == 1 || abs(uy) == -1 || abs(uy) == 0) &&
                    (abs(ux) == 1 || abs(ux) == -1 || abs(ux) == 0)) {
                    undeed_health -= 5*k;
                    if (undeed_health <= 0) {
                        undeed_health = 0;
                    }
                    mvprintw(3, 3, "You hit Undeed!  health: %d/30                                    ", undeed_health);

                }

            }
            if(in_use_weapon==5){
                if ((abs(dy) == 1 || abs(dy) == -1 || abs(dy) == 0) &&
                    (abs(dx) == 1 || abs(dx) == -1 || abs(dx) == 0)) {
                    deamon_health -= 10*k;
                    if (deamon_health <= 0) {
                        deamon_health = 0;
                    }
                    mvprintw(3, 3, "You hit Deamon!  health: %d/5                           ", deamon_health);

                }
                if ((abs(fy) == 1 || abs(fy) == -1 || abs(fy) == 0) &&
                    (abs(fx) == 1 || abs(fx) == -1 || abs(fx) == 0)) {
                    fire_health -= 10*k;
                    if (fire_health <= 0) {
                        fire_health = 0;
                    }
                    mvprintw(3, 3, "You hit Fire breathing monster!  health: %d/10                   ", fire_health);


                }
                if ((abs(sy) == 1 || abs(sy) == -1 || abs(sy) == 0) &&
                    (abs(sx) == 1 || abs(sx) == -1 || abs(sx) == 0)) {
                    snake_health -= 10*k;
                    if (snake_health <= 0) {
                        snake_health = 0;
                    }
                    mvprintw(3, 3, "You hit Snake!  health: %d/20                                    ", snake_health);

                }
                if ((abs(gy) == 1 || abs(gy) == -1 || abs(gy) == 0) &&
                    (abs(gx) == 1 || abs(gx) == -1 || abs(gx) == 0)) {
                    giant_health -= 10*k;
                    if (giant_health <= 0) {
                        giant_health = 0;
                    }
                    mvprintw(3, 3, "You hit Giant!  health: %d/15                                    ", giant_health);

                }

                if ((abs(uy) == 1 || abs(uy) == -1 || abs(uy) == 0) &&
                    (abs(ux) == 1 || abs(ux) == -1 || abs(ux) == 0)) {
                    undeed_health -= 10*k;
                    if (undeed_health <= 0) {
                        undeed_health = 0;
                    }
                    mvprintw(3, 3, "You hit Undeed!  health: %d/30                                    ", undeed_health);

                }

            }
        }

        ///////////dagger
        if(in_use_weapon == 2 && previous_c == 'p') {
            start_dagger = 1;
            xfor2 = new_x;
            yfor2 = new_y;
            counterfor2 = 1;
            switch (c) {
                case 'a':
                    da++; break;
                case 'w':
                    dw++; break;
                case 's':
                    ds++; break;
                case 'd':
                    dd++; break;
            }

            current_user->weapons.Dagger_count--;
            if(current_user->weapons.Dagger_count < 0) {
                current_user->weapons.Dagger_count = 0;
            }
        }

        if(start_dagger == 1 && counterfor2 > 0) {

            if(xfor2 == new_x_f && yfor2 == new_y_f) {
                fire_health -= 10*k;
                if(fire_health <= 0) fire_health = 0;
                mvprintw(3, 3, "You hit Fire breathing monster!  health: %d/10                   ", fire_health);
                counterfor2=0;
                start_dagger=0;
            }
            if(xfor2 == new_x_s && yfor2 == new_y_s) {
                snake_health -= 10*k;
                if(snake_health <= 0) snake_health = 0;
                mvprintw(3, 3, "You hit Snake!  health: %d/20                                    ", snake_health);
                counterfor2=0;
                start_dagger=0;
            }
            if(xfor2 == xd && yfor2 == yd) {
                deamon_health -= 10*k;
                if(deamon_health <= 0) deamon_health = 0;
                mvprintw(3, 3, "You hit Deamon!  health: %d/5                           ", deamon_health);
                counterfor2=0;
                start_dagger=0;
            }

            if(xfor2 == new_x_g && yfor2 == new_y_g) {
                giant_health -= 10*k;
                if(deamon_health <= 0) deamon_health = 0;
                mvprintw(3, 3, "You hit Giant!  health: %d/15                           ", giant_health);
                counterfor2=0;
                start_dagger=0;
            }

            if ((abs(uy) == 1 || abs(uy) == -1 || abs(uy) == 0) &&
                (abs(ux) == 1 || abs(ux) == -1 || abs(ux) == 0)) {
                undeed_health -= 10*k;
                if (undeed_health <= 0) {
                    undeed_health = 0;
                }
                mvprintw(3, 3, "You hit Undeed!  health: %d/30                           ", undeed_health);
                counterfor2=0;
                start_dagger=0;

            }

            if(da==1) {
                xfor2--;
                if(map[yfor2][xfor2]=='|' || map[yfor2][xfor2]=='_'){
                    counterfor2=0;
                    if(map[yfor2][xfor2+1]=='.')
                    {
                        map[yfor2][xfor2+1]='z';
                    }
                }
            }
            else if(ds==1) {
                yfor2++;
                if(map[yfor2][xfor2]=='|' || map[yfor2][xfor2]=='_'){
                    counterfor2=0;
                    if(map[yfor2-1][xfor2]=='.')
                    {
                        map[yfor2-1][xfor2]='z';
                    }
                }
            }
            else if(dd==1) {
                xfor2++;
                if(map[yfor2][xfor2]=='|' || map[yfor2][xfor2]=='_'){
                    counterfor2=0;
                    if(map[yfor2][xfor2-1]=='.')
                    {
                        map[yfor2][xfor2-1]='z';
                    }
                }
            }
            else if(dw==1) {
                yfor2--;
                if(map[yfor2][xfor2]=='|' || map[yfor2][xfor2]=='_'){
                    counterfor2=0;
                    if(map[yfor2+1][xfor2]=='.')
                    {
                        map[yfor2+1][xfor2]='z';
                    }
                }
            }

            counterfor2++;
            if(counterfor2 >= 5) {
                if(map[yfor2][xfor2]=='.'){
                    map[yfor2][xfor2]='z'; // z represents 1 dagger
                }
                start_dagger = 0;
                counterfor2 = 0;
                dd=0; da=0; dw=0; ds=0;
            }
            if(map[yfor2][xfor2]=='.'){
                mvaddch(yfor2, xfor2, '*');
            }
            mvprintw(3, 3, "                                                            ");
            refresh();
        }
        ////////////


        ///////////normal arrow
        if(in_use_weapon == 4 && previous_c == 'p') {
            start_normal_arrow = 1;
            xfor4 = new_x;
            yfor4 = new_y;
            counterfor4 = 1;
            switch (c) {
                case 'a':
                    na++; break;
                case 'w':
                    nw++; break;
                case 's':
                    ns++; break;
                case 'd':
                    nd++; break;
            }

            current_user->weapons.Normal_Arrow_count--;
            if(current_user->weapons.Normal_Arrow_count < 0) {
                current_user->weapons.Normal_Arrow_count = 0;
            }
        }

        if(start_normal_arrow == 1 && counterfor4 > 0) {

            if(xfor4 == new_x_f && yfor4 == new_y_f) {
                fire_health -= 10*k;
                if(fire_health <= 0) fire_health = 0;
                mvprintw(3, 3, "You hit Fire breathing monster!  health: %d/10                   ", fire_health);
                counterfor4=0;
                start_normal_arrow=0;
            }
            if(xfor4 == new_x_s && yfor2 == new_y_s) {
                snake_health -= 10*k;
                if(snake_health <= 0) snake_health = 0;
                mvprintw(3, 3, "You hit Snake!  health: %d/20                                    ", snake_health);
                counterfor4=0;
                start_normal_arrow=0;
            }
            if(xfor4 == xd && yfor4== yd) {
                deamon_health -= 10*k;
                if(deamon_health <= 0) deamon_health = 0;
                mvprintw(3, 3, "You hit Deamon!  health: %d/5                           ", deamon_health);
                counterfor4=0;
                start_normal_arrow=0;
            }

            if(xfor4 == new_x_g && yfor4 == new_y_g) {
                giant_health -= 10*k;
                if(giant_health <= 0) giant_health = 0;
                mvprintw(3, 3, "You hit Giant!  health: %d/15                                    ", giant_health);
                counterfor4=0;
                start_normal_arrow=0;
            }

            if(xfor4 == new_x_u && yfor4 == new_y_u) {
                undeed_health -= 10*k;
                if(undeed_health <= 0) undeed_health = 0;
                mvprintw(3, 3, "You hit Undeed!  health: %d/30                                     ", undeed_health);
                counterfor4=0;
                start_normal_arrow=0;
            }


            if(na==1) {
                xfor4--;
                if(map[yfor4][xfor4]=='|' || map[yfor4][xfor4]=='_'){
                    counterfor4=0;
                    if(map[yfor4][xfor4+1]=='.')
                    {
                        map[yfor4][xfor4+1]='c';
                    }
                }
            }
            else if(ns==1) {
                yfor4++;
                if(map[yfor4][xfor4]=='|' || map[yfor4][xfor4]=='_'){
                    counterfor4=0;
                    if(map[yfor4-1][xfor4]=='.')
                    {
                        map[yfor4-1][xfor4]='c';
                    }
                }
            }
            else if(nd==1) {
                xfor4++;
                if(map[yfor4][xfor4]=='|' || map[yfor4][xfor4]=='_'){
                    counterfor4=0;
                    if(map[yfor4][xfor4-1]=='.')
                    {
                        map[yfor4][xfor4-1]='c';
                    }
                }
            }
            else if(nw==1) {
                yfor4--;
                if(map[yfor4][xfor4]=='|' || map[yfor4][xfor4]=='_'){
                    counterfor4=0;
                    if(map[yfor4+1][xfor4]=='.')
                    {
                        map[yfor4+1][xfor4]='c';
                    }
                }
            }

            counterfor4++;
            if(counterfor4 >= 5) {
                if(map[yfor4][xfor4]=='.'){
                    map[yfor4][xfor4]='c'; // c represents 1 normal arrow
                }
                start_normal_arrow = 0;
                counterfor4 = 0;
                nd=0; na=0; nw=0; ns=0;
            }
            if(map[yfor4][xfor4]=='.'){
                mvaddch(yfor4, xfor4, '-');
            }

            refresh();
        }
        ////////////

        ///////////Magic wand
        if(in_use_weapon == 3 && previous_c == 'p') {
            start_magic_wand = 1;
            xfor3 = new_x;
            yfor3 = new_y;
            counterfor3 = 1;
            switch (c) {
                case 'a':
                    ma++; break;
                case 'w':
                    mw++; break;
                case 's':
                    ms++; break;
                case 'd':
                    md++; break;
            }

            current_user->weapons.Magic_Wand_count--;
            if(current_user->weapons.Magic_Wand_count < 0) {
                current_user->weapons.Magic_Wand_count = 0;
            }
        }

        if(start_magic_wand == 1 && counterfor3 > 0) {

            if(xfor3 == new_x_f && yfor3 == new_y_f) {
                fire_health -= 15*k;
                if(fire_health <= 0) fire_health = 0;
                mvprintw(3, 3, "You hit Fire breathing monster!  health: %d/10                   ", fire_health);
                counterfor3=0;
            }
            if(xfor3 == new_x_s && yfor3 == new_y_s) {
                snake_health -= 15*k;
                if(snake_health <= 0) snake_health = 0;
                mvprintw(3, 3, "You hit Snake!  health: %d/20                                    ", snake_health);
                counterfor3=0;
                snake_chase=0;
                start_magic_wand=0;
            }
            if(xfor3 == xd && yfor3 == yd) {
                deamon_health -= 15*k;
                if(deamon_health <= 0) deamon_health = 0;
                mvprintw(3, 3, "You hit Deamon!  health: %d/5                           ", deamon_health);
                counterfor3=0;
                start_magic_wand=0;
            }

            if(xfor3 == new_x_g && yfor3 == new_y_g) {
                giant_health -= 15*k;
                if(giant_health <= 0) giant_health = 0;
                mvprintw(3, 3, "You hit Giant!  health: %d/15                                    ", giant_health);
                counterfor3=0;
                start_magic_wand=0;
            }
            if(xfor4 == new_x_u && yfor2 == new_y_u) {
                undeed_health -= 15*k;
                if(undeed_health <= 0) undeed_health = 0;
                mvprintw(3, 3, "You hit Undeed!  health: %d/30                                     ", undeed_health);
                counterfor4=0;
                start_magic_wand=0;
            }

            if(ma==1) {
                xfor3--;
                if(map[yfor3][xfor3]=='|' || map[yfor3][xfor3]=='_'){
                    counterfor3=0;
                    if(map[yfor3][xfor3+1]=='.')
                    {
                        map[yfor3][xfor3+1]='x';
                    }
                }
            }
            else if(ms==1) {
                yfor3++;
                if(map[yfor3][xfor3]=='|' || map[yfor3][xfor3]=='_'){
                    counterfor3=0;
                    if(map[yfor3-1][xfor3+1]=='.')
                    {
                        map[yfor3-1][xfor3+1]='x';
                    }
                }
            }
            else if(md==1) {
                xfor3++;
                if(map[yfor3][xfor3]=='|' || map[yfor3][xfor3]=='_'){
                    counterfor3=0;
                    if(map[yfor3][xfor3-1]=='.')
                    {
                        map[yfor3][xfor3-1]='x';
                    }
                }
            }
            else if(mw==1) {
                yfor3--;
                if(map[yfor3][xfor3]=='|' || map[yfor3][xfor3]=='_'){
                    counterfor3=0;
                    if(map[yfor3+1][xfor3]=='.')
                    {
                        map[yfor3+1][xfor3]='x';
                    }
                }
            }

            counterfor3++;
            if(counterfor3 >= 5) {
                if(map[yfor3][xfor3]=='.'){
                    map[yfor3][xfor3]='x'; // x represents 1 magic wand
                }
                start_magic_wand = 0;
                counterfor3 = 0;
                md=0; ma=0; mw=0; ms=0;
            }
            if(map[yfor3][xfor3]=='.'){
                mvaddch(yfor3, xfor3, '+');
            }
            mvprintw(2, 3, "                                                            ");
            refresh();
        }
        ////////////


        //door code
        int status=2;
        init_pair(12,COLOR_YELLOW,COLOR_BLACK);
        init_pair(13,COLOR_MAGENTA,COLOR_BLACK);
        init_pair(14,COLOR_RED,COLOR_BLACK);



        if(food>=10){
            if(food4health_counter>=3){
                if(current_user->spells.health_spell_counter>0){
                    health+=2;
                    current_user->spells.health_spell_counter-=1;
                    if(current_user->spells.health_spell_counter<0) current_user->spells.health_spell_counter=0;
                }
                else{
                    health+=1;
                }
                if(health>10) health=10;
                food4health_counter=0;
            }
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
        mvprintw(max_y-2,60,"Treasure room");

        //health
        mvprintw(max_y-2,2,"health: ");
        refresh();
        for(int i =0;i<=health;i++){
            mvprintw(max_y-2,10+i,"♥");
            mvprintw(max_y-2,10+health," ");
            for(int j=0;j<10-i;j++){
                mvprintw(max_y-2,10+health+j," ");
            }
            mvprintw(max_y-2,10+12,"%d%c",health*10,'%');

        }

        //food
        mvprintw(max_y-2,32,"food: ");

        for(int i =0;i<=food;i++){
            mvprintw(max_y-2,38+i,"+");
            mvprintw(max_y-2,38+food," ");
            mvprintw(max_y-2,38 + 12,"     ");
            mvprintw(max_y-2,38 + 12,"%d%c",food*10,'%');
            refresh();
        }
        refresh();

        if(in_use_weapon==1){
            mvprintw(max_y-2,76,"weapon: Mace");
        }
        else if(in_use_weapon==2){
            mvprintw(max_y-2,76,"weapon: Dagger");
        }
        else if(in_use_weapon==3){
            mvprintw(max_y-2,76,"weapon: Magic Wand");
        }
        else if(in_use_weapon==4){
            mvprintw(max_y-2,76,"weapon: Normal Arrow");
        }
        else if(in_use_weapon==4){
            mvprintw(max_y-2,76,"weapon: Sword");
        }
        else {
            mvprintw(max_y-2,76,"weapon: no weapon in use!");
        }


        counter++;


        refresh();
        if( map[new_y][new_x]=='#'){
            int temp = cori_number[new_y][new_x];
            for(int j=-4;j<4;j++){
                for(int i=-4;i<4;i++){
                    if(cori_number[new_y+j][new_x+i]==temp && map[new_y+j][new_x+i]=='#' && visited[new_y+j][new_x+i]!=1 || map[new_y+j][new_x+i]=='+'){
                        visited[new_y+j][new_x+i]=1;
                    }
                }
            }
        }

        else if(map[new_y][new_x]=='+' &&(map[new_y+1][new_x]=='.' || map[new_y-1][new_x]=='.' || map[new_y][new_x+1]=='.' || map[new_y][new_x-1]=='.' )){
            int tempp=room_number[new_y][new_x];
            for(int j1=0;j1<max_y;j1++){
                for (int i1 = 0; i1 < max_x; i1++) {
                    if(visited[j1][i1]!=1 && room_number[j1][i1]==tempp){
                        visited[j1][i1]=1;
                    }
                }
            }
        }

        if(map[new_y][new_x]=='<' && deamon_health==0 && snake_health==0 && fire_health==0 && undeed_health==0 && giant_health==0){
            current_user->food=food;
            current_user->health=health;
            current_user->food1=food1;
            current_user->new_golds+=total_black_gold+total_yellow_gold;
            current_user->weapons.in_use_weapon=in_use_weapon;
            return 1;
        }
        previous_x = new_x;
        previous_y = new_y;
        previous_c =c;
        food4health_counter++;

    } while ((c = getch()) != 27);

    endwin();


}


int pre_leaderboard(struct user *current_user){
     FILE* fptr = fopen("leaderboard.txt", "r");
     FILE* fptrtemp = fopen("temp.txt", "w");

    char info[100][100][100];
    int info2[100][100];
    int rank;
    char username1[100];
    int total_score;
    int total_gold;
    int total_finished_games;
    char total_time[100];
    char tempi[100];
    int k =0;
    rewind(fptr);

    while (fgets(tempi, 100, fptr) != NULL) {
        sscanf(tempi, "%d %s %d %d %d %s", &rank, username1, &total_score, &total_gold, &total_finished_games, total_time);
        if (strcmp(username1, current_user->username) == 0) {
            strcpy(info[k][0],username1);
            info2[k][1]=current_user->total_score;
            info2[k][2]=current_user->total_gold;
            info2[k][3]=current_user->total_finished_games;
            strcpy(info[k][1],total_time);
        }
        else{
            strcpy(info[k][0],username1);
            info2[k][1]=total_score;
            info2[k][2]=total_gold;
            info2[k][3]=total_finished_games;
            strcpy(info[k][1],total_time);
        }

        k++;
    }


    for(int j = 0; j < k-1; j++) {
        for(int p = 0; p < k-1-j; p++) {
            if(info2[p][1] < info2[p+1][1]) {
                int tempscore = info2[p][1];
                int tempgold = info2[p][2];
                int tempfinished = info2[p][3];
                char tempusername[100];
                char temptime[100];

                strcpy(tempusername, info[p][0]);
                strcpy(temptime, info[p][1]);

                info2[p][1] = info2[p+1][1];
                info2[p][2] = info2[p+1][2];
                info2[p][3] = info2[p+1][3];

                strcpy(info[p][0], info[p+1][0]);
                strcpy(info[p][1], info[p+1][1]);

                info2[p+1][1] = tempscore;
                info2[p+1][2] = tempgold;
                info2[p+1][3] = tempfinished;
                strcpy(info[p+1][0], tempusername);
                strcpy(info[p+1][1], temptime);
            }
        }
    }

     for(int i = 0; i < k; i++) {
        fprintf(fptrtemp, "%d %s %d %d %d %s\n",
            i+1,
            info[i][0],
            info2[i][1],
            info2[i][2],
            info2[i][3],
            info[i][1]
        );
    }

    fclose(fptr);
    fclose(fptrtemp);

    remove("leaderboard.txt");

    rename("temp.txt", "leaderboard.txt");

    return 0;




}





int victory(struct user *current_user){
    initscr();
    keypad(stdscr, TRUE);
    curs_set(0);
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
    while(1) {
        clear();
        attron(COLOR_PAIR(1) | A_BOLD);
        mvprintw(center_y - 2, center_x-4, "══════════════════════════════");
        attron(COLOR_PAIR(1) | A_BOLD | A_BLINK);
        mvprintw(center_y, center_x+4, " V I C T O R Y ! ");
        attroff(COLOR_PAIR(1) | A_BOLD | A_BLINK);
        mvprintw(center_y + 2, center_x-4, "══════════════════════════════");
        attroff(COLOR_PAIR(1) | A_BOLD);
        mvprintw(center_y + 6, center_x-4, "Total received Golds: %d",current_user->new_golds);
        mvprintw(center_y + 8, center_x-4, "Total score: %d ", current_user->new_golds*(1 + current_user->game_setting.game_level)*10); ///total new gold * game level + new gold * 15
        current_user->total_score+=current_user->new_golds*(1 + current_user->game_setting.game_level)*10;
        mvprintw(center_y+20,center_x , selected == 0 ? "[ back to leaderboard ]" : "back to leaderboard");
        refresh();
        key = getch();
        current_user->total_finished_games+=1;
        pre_leaderboard(current_user);
        getch();
        return 1;
    }
    refresh();
}

int lost(struct user *current_user){
    initscr();
    keypad(stdscr, TRUE);
    curs_set(0);
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
    while(1) {
        clear();
        mvprintw(center_y + 10, center_x, "Total score: %d ", (current_user->new_golds* 1 + current_user->new_golds*current_user->game_setting.game_level)*5) ; ///total new gold * game level + new gold * 10
        current_user->total_score= current_user->total_score + (current_user->new_golds* 1 + current_user->new_golds*current_user->game_setting.game_level)*5 ;
        attron(COLOR_PAIR(1) | A_BOLD);
        mvprintw(center_y - 2, center_x-4, "══════════════════════════════");
        attron(COLOR_PAIR(1) | A_BOLD | A_BLINK);
        mvprintw(center_y, center_x, " G A M E  O V E R ! ");
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
                    pre_leaderboard(current_user);
                    return 1;
                }
                else if(selected == 1) {
                   pre_leaderboard(current_user);
                   return 0;
                }
                refresh();
                getch();
                break;
        }
    }

    refresh();




}
