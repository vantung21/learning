#include <stdio.h>
#include <stdlib.h>

// make color
#define BLACK   "\x1B[30m"
#define RED     "\x1B[31m"
#define GREEN   "\x1B[32m"
#define YELLOW  "\x1B[33m"
#define BLUE    "\x1B[34m"
#define MAGENTA "\x1B[35m"
#define CYAN    "\x1B[36m"
#define WHITE   "\x1B[37m"
#define RESET   "\x1B[0m"
#define BOLD    "\x1B[1m"
//mau nen
#define BG_BLACK   "\x1B[40m"
#define BG_RED     "\x1B[41m"
#define BG_GREEN   "\x1B[42m"
#define BG_YELLOW  "\x1B[43m"
#define BG_BLUE    "\x1B[44m"
#define BG_MAGENTA "\x1B[45m"
#define BG_CYAN    "\x1B[46m"
#define BG_WHITE   "\x1B[47m"
#define BG_WHITE_B   "\x1B[107m"

int main() {
    printf("       @:::::::::::@      \n");
    printf("        @:::::::::@      \n");
    printf("         @:::::::@       \n");
    printf("     _=======%c%c=======   \n",240,240);
    printf("    /     @::::::@   =%c   \n",41);
    printf("  %c=      @:::::@   /   \n",40);
    printf("    ========%c%c=====-     \n",240,240);
    printf("        @::::::@         \n");
    printf("       @::::::@         \n");
    printf(" _______________________ \n");
    printf("   I T   F A C U L T Y   \n");

    return 0;
}
