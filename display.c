#include "display.h"

void render(Field *field) {
    Cell cell;
    setCursor();
    printColorLine(' ', WIDTH + 2, COLOR_GRAY);
    br();
    for (int i = 0; i < HIGHT; i++) {
        printColorCell(' ', COLOR_GRAY);
        for (int j = 0; j < WIDTH; j++) {
            if ((*field)[i][j] != NULL) {
                cell = *(*field)[i][j];
                printColorCell(' ', cell.color);
            }
            else {
                printColorCell(' ', COLOR_RESET);
            }
        }
        printColorCell(' ', COLOR_GRAY);
        br();
    }
    printColorLine(' ', WIDTH + 2, COLOR_GRAY);
}
