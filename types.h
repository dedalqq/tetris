#include <stddef.h>

#ifndef TYPES
#define TYPES


#define WIDTH 10
#define HIGHT 20

//#define NULL ((void*)0)

// colors
typedef char Color[2];

#define COLOR_RED "41"
#define COLOR_GREEN "42"
#define COLOR_YELLOW "43"
#define COLOR_BLUE "44"
#define COLOR_MAGENTA "45"
#define COLOR_CYAN "46"
#define COLOR_GRAY "47"
#define COLOR_RESET "00"

#define KEY_UP 65
#define KEY_DOWN 66
#define KEY_RIGHT 67
#define KEY_LEFT 68

#define KEY_QUIT 113

typedef struct _Cell {
    Color color;
    int x;
    int y;
} Cell;

// Cell *field[HIGHT][WIDTH];

typedef Cell *Field[HIGHT][WIDTH];

typedef struct _Block {
    short int isMovable;
    Cell *cells[4];
} Block;

//typedef Cell *Block[4];

#endif
