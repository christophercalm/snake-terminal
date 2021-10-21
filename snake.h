#include "linked_list.c"

#define clrscr() printf("\e[1;1H\e[2J")
#define HEIGHT 25
#define WIDTH 25
#define BOARD_CHAR '.'
#define SNAKE_CHAR '8'
#define APPLE_CHAR '*'
#define SNAKE_SPEED 15 * 10000
#define SNAKE_INITIAL_LENGTH 4

typedef struct snake {
    node_t * snake_head;
    int snake_length;
    char direction;
    int dead;
}
Snake;

typedef struct game_board {
    Snake snake;
    int apple_position;
    char display[HEIGHT * WIDTH];   
} GameBoard;

void display_graphics();
void init_graphics();
void cleanup_graphics();
void update_graphics();
void get_input();
int get_random_apple_position();
int update_snake_position();
void init_board();
void game_loop();
void game_over();


