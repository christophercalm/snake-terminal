#include <stdio.h>

#include <stdlib.h>

#include <assert.h>

#include <string.h>

#include <time.h>

#include "snake.h"

#include "kbhit.c"

GameBoard board;

void display_graphics() {
    clrscr();
    printf("\n\n\nSCORE: %d\n\n", board.snake.snake_length - SNAKE_INITIAL_LENGTH);
    //top border
    for (int i = 0; i < (WIDTH + 2); i++) {
        printf("#");
    }
    printf("\n");
    for (int i = 0; i < WIDTH * HEIGHT; i++) {
        if (i == 0) {
            printf("#"); //first border element
        }
        if (i != 0 && i % WIDTH == 0) {
            printf("#\n#"); //border and newline
        }
        printf("%c", board.display[i]);
        if (i == WIDTH * HEIGHT - 1) {
            printf("#\n"); //last border element
        }
    }
    for (int i = 0; i < (WIDTH + 2); i++) {
        printf("#");
    }
    puts("\n");
}

void init_graphics() {
    //flush input
    tcflush(0, TCIFLUSH);
    fflush(stdin);
    //hide cursor
    printf("\e[?25l");
    //seed random variable for apple
    srand(time(0));
    memset(board.display, BOARD_CHAR, sizeof(board.display));
}
void cleanup_graphics() {
    //show cursor again
    printf("\e[?25h");
    free(board.snake.snake_head);
}
void update_graphics() {
    memset(board.display, BOARD_CHAR, sizeof(board.display));
    //update snake
    node_t * current_snake_node = board.snake.snake_head;
    for (int i = 0; i < board.snake.snake_length; i++) {
        board.display[current_snake_node -> value] = SNAKE_CHAR;
        current_snake_node = current_snake_node -> next;
    }
    //update apple
    board.display[board.apple_position] = APPLE_CHAR;
}

void get_input() {
    enable_raw_mode();
    if (kbhit()) {
        char c = getch();
        switch (c) {
        case 'w':
            board.snake.direction = 'N';
            break;
        case 'a':
            board.snake.direction = 'W';
            break;
        case 's':
            board.snake.direction = 'S';
            break;
        case 'd':
            board.snake.direction = 'E';
            break;
        default:
            break;
        }
    }
    disable_raw_mode();
    tcflush(0, TCIFLUSH);
    fflush(stdin);
}

int get_random_apple_position() {
    return rand() % (WIDTH * HEIGHT);
}

int update_snake_position() {
    int new_index = 0;
    int end_snake_value = get_value_from_linked_list(board.snake.snake_head, board.snake.snake_length - 1);
    switch (board.snake.direction) {
    case 'N':
        new_index = end_snake_value - WIDTH;
        break;
    case 'S':
        new_index = end_snake_value + WIDTH;
        break;
    case 'E':
        new_index = end_snake_value + 1;
        break;
    case 'W':
        new_index = end_snake_value - 1;
        break;
    }
    //collision with snake, too far north, too far south
    for (int i = 0; i < board.snake.snake_length; i++) {
        if (get_value_from_linked_list(board.snake.snake_head, i) == new_index) {
            return 1;
        }
    }
    if (new_index < 0 || new_index > WIDTH * HEIGHT) {
        return 1;

        //we are already on the east most square
    } else if (board.snake.direction == 'E' && (end_snake_value + 1) % WIDTH == 0) {
        return 1;

        //we are already on the west most square
    } else if (board.snake.direction == 'W' && end_snake_value % WIDTH == 0) {
        return 1;

    } else if (new_index != board.apple_position) {
        board.snake.snake_head = delete_from_position(board.snake.snake_head, 0);
        add_to_end_linked_list(board.snake.snake_head, new_index);
        return 0;

    } else {
        board.apple_position = get_random_apple_position();
        add_to_end_linked_list(board.snake.snake_head, new_index);
        board.snake.snake_length += 1;
        return 0;
    }
}

void init_board() {
    init_graphics();
    board.snake.direction = 'E';
    board.apple_position = get_random_apple_position();
    board.snake.snake_head = (node_t * ) malloc(sizeof(node_t));
    board.snake.snake_head -> value = 3;
    board.snake.snake_head -> next = NULL;
    board.snake.snake_head = add_to_beginning_linked_list(board.snake.snake_head, 2);
    board.snake.snake_head = add_to_beginning_linked_list(board.snake.snake_head, 1);
    board.snake.snake_head = add_to_beginning_linked_list(board.snake.snake_head, 0);
    board.snake.snake_length = SNAKE_INITIAL_LENGTH;
    board.snake.dead = 0;
}

void game_loop() {
    while (!board.snake.dead) {
        board.snake.dead = update_snake_position();
        update_graphics();
        display_graphics();
        get_input();
        usleep(SNAKE_SPEED);
    }
    cleanup_graphics();
    game_over();
}

void game_over() {
    printf("\nGAME OVER\nPress q to quit, any other key to play again: ");
    char c = getchar();
    if (c == 'q') {
        exit(0);
    } else {
        init_board();
        game_loop();
    }
}

int main() {
    init_board();
    game_loop();
}