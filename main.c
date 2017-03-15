#include <stdlib.h>
#include <unistd.h>

#include <signal.h>

#include "types.h"
#include "display.h"

char colors_list[][2] = {
    COLOR_RED,
    COLOR_GREEN,
    COLOR_YELLOW,
    COLOR_BLUE,
    COLOR_MAGENTA,
    COLOR_CYAN,
};

int blocs_types[][4][2] = {
    {
        {0,3}, //  ####
        {0,4},
        {0,5},
        {0,6},
    },
    {
        {0,3}, //  ##
        {0,4}, //   ##
        {1,4},
        {1,5},
    },
    {
        {0,4}, //   ##
        {0,5}, //  ##
        {1,3},
        {1,4},
    },
    {
        {0,4}, //   #
        {1,3}, //  ###
        {1,4},
        {1,5},
    },
    {
        {0,4}, //   ##
        {0,5}, //   ##
        {1,4},
        {1,5},
    },
};


Field field;

int isWork = 1;

void shutdown(int s) {
    resetTerminalSettings();
    isWork = 0;
}

void setCellColor(Cell *cell, Color color) {
    (*cell).color[0] = color[0];
    (*cell).color[1] = color[1];
}

void addCellToField(Field *f, Cell *cell, int y, int x) {
    cell->x = x;
    cell->y = y;

    (*f)[y][x] = cell;
}

Block createNewBlock() {

    Block block;
    block.isMovable = 1;

    int rand_type = rand() % 5;
    int rand_color = rand() % 6;

    for (int i = 0; i < 4; i++) {
        block.cells[i] = (Cell*)malloc(sizeof(Cell));
        setCellColor(block.cells[i], colors_list[rand_color]);
        addCellToField(&field, block.cells[i], blocs_types[rand_type][i][0], blocs_types[rand_type][i][1]);
    }

    return block;
}

void moveBlock(Block *block, int dx, int dy) {

    if (block->isMovable == 0) {
        return;
    }

    int x;
    int y;

    Cell *cp;

    for (int i = 0; i < 4; i++) {

        x = block->cells[i]->x;
        y = block->cells[i]->y;

        if (y+dy < 0 || y+dy >= HIGHT) {
            block->isMovable = 0;
            return;
        }

        if (x+dx < 0 || x+dx >= WIDTH) {
            return;
        }

        if (field[y+dy][x+dx] == NULL) {
            continue;
        }

        cp = field[y+dy][x+dx];

        int isForeign = 1;

        for (int j = 0; j < 4; j++) {
            if (block->cells[j] == cp) {
                isForeign = 0;
                break;
            }
        }

        if (isForeign) {
            block->isMovable = 0;
            return;
        }

    }

    for (int i = 0; i < 4; i++) {
        field[block->cells[i]->y][block->cells[i]->x] = NULL;
    }

    for (int i = 0; i < 4; i++) {
        block->cells[i]->x += dx;
        block->cells[i]->y += dy;
    }

    for (int i = 0; i < 4; i++) {
        field[block->cells[i]->y][block->cells[i]->x] = block->cells[i];
    }
}

void clearLinr() {
    for (int i = 0; i < HIGHT; i++) {

        int isFull = 1;

        for (int j = 0; j < HIGHT; j++) {
            if (field[i][j] == NULL) {
                isFull = 0;
                break;
            }
        }

        if (isFull) {
            for (int j = 0; j < HIGHT; j++) {
                free(field[i][j]);
                field[i][j] = NULL;
            }
        }
    }
}

Block block;

void teak(int s) {
    if (block.isMovable) {
        moveBlock(&block, 0, 1);
    }
    else {
        clearLinr();
        block = createNewBlock();
    }

    render(&field);

    alarm(1);
}

void controll(char key) {
    if (key == KEY_DOWN) {
        moveBlock(&block, 0, 1);
    }
    else if (key == KEY_RIGHT) {
        moveBlock(&block, 1, 0);
    }
    else if (key == KEY_LEFT) {
        moveBlock(&block, -1, 0);
    }
    else if (key == KEY_QUIT) {
        shutdown(0);
    }
    render(&field);
}

int main() {

    setTerminalSettings();

    signal(SIGINT, shutdown);

    block = createNewBlock();

    render(&field);

    alarm(1);
    signal(SIGALRM, teak);

    char key;

    while (isWork) {
        read(0, &key, 1);
        controll(key);
    }

    br();

    return 0;
}
