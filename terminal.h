#include "types.h"

#include <termios.h>

static struct termios term_settings;

void setCursor();

void printLine(char c, int len);

void printColorLine(char c, int len, Color color);

void printColorCell(char c, Color color);

void setTerminalSettings();

void resetTerminalSettings();

void br();
