#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>
#include <time.h>

#define MAX_X 80
#define MAX_Y 25

int initialization(int world[][MAX_X]); // initialization the world
void random_initialization(int world[][MAX_X]); // random one 
void output(int world[][MAX_X]); // print the world
void next_generation(int world[][MAX_X], int prev_world[][MAX_X]); // creating a new generation
void copy_world(int src[][MAX_X], int dst[][MAX_X]); // copy the world from src to dst
int compare_world(int world_1[][MAX_X], int world_2[][MAX_X]); // comparasion the current and previous worlds
int number_of_live(int world[][MAX_X]); // get the number of all live cells in the current world
int number_of_live_nb(int world[][MAX_X], int y, int x); // get the number of live neigbours
void pressed_key(int *n); // keypress handler

int initialization(int world[][MAX_X]) {
    int n = 0;
    for (int i = 0; i < MAX_Y; i++) {
        for (int j = 0; j < MAX_X; j++) {
            if (scanf("%d", &world[i][j]) !=1 || (world[i][j] != 0 && world[i][j] != 1)) {
                n = 1;
            }
        }
    }
    return n;
}

void random_initialization(int world[][MAX_X]) {	
    srand(time(NULL));
    for (int i = 0; i < MAX_Y; i++) {
        for (int j = 0; j < MAX_X; j++) {
		int n = rand();
            if (n % 2) {
		world[i][j] =1;
	    }
        }
    }
}

void output(int world[][MAX_X]) {
    for (int i = 0; i < MAX_Y; i++) {
        for (int j = 0; j < MAX_X; j++) {
            if (world[i][j] == 1) {
                printw("*");
            } else {
                printw(" ");
            }
            if (j == MAX_X - 1) {
                printw("\n");
            }
        }
    }
}

void next_generation(int world[][MAX_X], int prev_world[][MAX_X]) {
    int status_nb;
    int p;
    for (int i = 0; i < MAX_Y; i++) {
        for (int j = 0; j < MAX_X; j++) {
            p = prev_world[i][j];
            status_nb = number_of_live_nb(prev_world, i, j);
            if (p == 0) {
                if (status_nb == 3) {
                    world[i][j] = 1;
                }
            } else if (status_nb < 2 || status_nb > 3) {
                    world[i][j] = 0;
            }
        }
    }
}

void copy_world(int src[][MAX_X], int dst[][MAX_X]) {
    for (int i = 0; i < MAX_Y; i++) {
        for (int j = 0; j < MAX_X; j++) {
            dst[i][j] = src[i][j];
        }
    }
}

int compare_world(int world_1[][MAX_X], int world_2[][MAX_X]) {
    int flag = 0;
    for (int i = 0; i < MAX_Y; i++) {
        for (int j = 0; j < MAX_X; j++) {
            if (world_1[i][j] != world_2[i][j]) {
                flag = 1;
            }
        }
    }
    return flag;
}

int number_of_live(int world[][MAX_X]) {
    int count = 0;
    for (int i = 0; i < MAX_Y; i++) {
        for (int j = 0; j < MAX_X; j++) {
            if (world[i][j] == 1) {
                count++;
            }
        }
    }
    return count;
}

int number_of_live_nb(int world[][MAX_X], int y, int x) {
    int count = 0;
    for (int i = -1; i < 2; i++) {
        for (int j = -1; j < 2; j++) {
            int x_1 = (x + i + MAX_X) % MAX_X;
            int y_1 = (y + j + MAX_Y) % MAX_Y;
            count += world[y_1][x_1];
        }
    }
    count -= world[y][x];
    return count;
}

void pressed_key(int *n) {
    char c = getch();
    if (c == '+') {
        *n = *n/2;
    }
    if (*n == 0) {
        *n = 1;
    }
    if (c == '-') {
        *n = (*n) * 2;
    }
    if (c == 'q') {
	endwin();
	exit(1);
    }
}

int main(int argc, char *argv[]) {
    int world[MAX_Y][MAX_X] = {0};
    if (argc == 2 && *(char*)argv[1] == 'r') {
	random_initialization(world);
    } else if (initialization(world) == 1) {
		return 1;
    }
    int prev_world[MAX_Y][MAX_X] = {0};
    int live_cell = 0;
    int comp;
    int delay = 2000000;
    if (freopen("/dev/tty", "r", stdin) == NULL) {
         printf("stdin reopen error!");
    }
    initscr(); // ncurses initialization the screen 
    noecho();
    nodelay(stdscr, 1);
    curs_set(0);
    do {
       output(world);
       usleep(delay);
       pressed_key(&delay);
       copy_world(world, prev_world);
       next_generation(world, prev_world);
       comp = compare_world(world, prev_world);
       live_cell = number_of_live(world);
       refresh();
       clear();
    } while (live_cell > 0 && comp != 0);
    endwin();
    return 0;
}
