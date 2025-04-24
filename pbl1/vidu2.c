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
#define BG_RED     "\x1B[107m"
#define BG_GREEN   "\x1B[42m"
#define BG_YELLOW  "\x1B[43m"
#define BG_BLUE    "\x1B[44m"
#define BG_MAGENTA "\x1B[45m"
#define BG_CYAN    "\x1B[46m"
#define BG_WHITE   "\x1B[47m"

int main() {
	printf( BG_RED YELLOW "%c", 201);
	for (int i = 1; i < 21; i++){
		printf("%c", 205);
	}
	printf("%c\n",187);
	
    printf(YELLOW "%c" BLUE "   D                " YELLOW "%c\n", 186, 186);
    printf("%c" RED " B A C H K H O A    " YELLOW "%c\n", 186, 186);
    printf("%c" BLUE "   N @@@@@@" YELLOW "@@" BLUE "@@@@@@ " YELLOW "%c\n", 186, 186);
    printf("%c" BLUE "   A @@@@@@@@" YELLOW "@@" BLUE "@@@@ "YELLOW "%c\n", 186, 186);
    printf("%c" BLUE "   N @@@@@@@@*"YELLOW "@@@" BLUE"@@ "YELLOW "%c\n", 186, 186);
    printf("%c" BLUE "   G @@@@@@@@"YELLOW "@@@@" BLUE "@@ "YELLOW "%c\n", 186, 186);
    printf("%c"BLUE "     @@@@@@@#"YELLOW "@@@@@" BLUE "@ "YELLOW "%c\n",186, 186);
    printf("%c" BLUE "     @@@@@" YELLOW "@@@@@@@" BLUE "#@ " YELLOW "%c\n", 186, 186);
    printf("%c" BLUE "     @@" YELLOW "@@@@@@@@@@" BLUE "@@ " YELLOW "%c\n", 186, 186);
   // printf("                         \n");
    printf("%c", 200);
	for (int i = 1; i < 21; i++){
			printf("%c", 205);
	}
	printf("%c\n" RESET, 188);
    return 0;
}

