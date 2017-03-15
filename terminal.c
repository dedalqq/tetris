#include <unistd.h>
#include "terminal.h"

void setCursor() {
    write(1, "\033[0;0H", 6);
}

void printLine(char c, int len) {
    for (int i = 0; i < len * 2; i++) {
        write(1, &c, 1);
    }
}

void setColor(Color color) {
    write(1, "\e[", 2);
    write(1, color, 2);
    write(1, "m", 1);
}

void printColorLine(char c, int len, Color color) {
    setColor(color);
    printLine(c, len);
    setColor(COLOR_RESET);
}

void printColorCell(char c, Color color) {
    setColor(color);
    printLine(c, 1);
    setColor(COLOR_RESET);
}

// ========================

void setTerminalSettings() {
    struct termios new_settings;
    tcgetattr(0, &term_settings);
    new_settings = term_settings;

    new_settings.c_lflag &= (~ICANON);
    new_settings.c_lflag &= (~ECHO);
    new_settings.c_cc[VTIME] = 0;
    new_settings.c_cc[VMIN] = 1;
    tcsetattr(0, TCSANOW, &new_settings);
}

void resetTerminalSettings() {
    tcsetattr(0, TCSANOW, &term_settings);
}

// ========================

void br() {
    write(1, "\n", 1);
}
