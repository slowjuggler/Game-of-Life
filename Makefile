all: game_of_life.c
	gcc -o life -Wall -Werror -Wextra game_of_life.c -lncurses
	
