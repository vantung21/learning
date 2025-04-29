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

int main(){
    printf("\t" BG_WHITE_B YELLOW "%c", 201);
	for (int i = 1; i < 21; i++){
		printf("%c", 205);
	}
	printf("%c" RESET "\t\t\t\t\t\t\t\t\t",187);
    printf(BG_WHITE_B BLACK "     \\" BLUE "#############" BLACK "/    " RESET "\n");
    printf("\t" BG_WHITE_B YELLOW "%c" BLUE "   D                " YELLOW "%c" RESET "\t\t\t\t\t\t\t\t\t", 186, 186);
    printf(BG_WHITE_B BLACK "      \\" BLUE "###########" BLACK "/     " RESET "\n");
    printf("\t" BG_WHITE_B YELLOW "%c" RED " B A C H K H O A    " YELLOW "%c" RESET "\t\t\t\t\t\t\t\t\t", 186, 186);
    printf(BG_WHITE_B BLACK "       \\" BLUE"#########" BLACK "/      " RESET"\n");
    printf("\t" BG_WHITE_B YELLOW "%c" BLUE "   N @@@@@@" YELLOW "@@" BLUE "@@@@@@ " YELLOW "%c" RESET "\t", 186, 186);
    printf(BG_BLUE "      " RESET "%c " BG_BLUE "  " RESET "%c   " BG_BLUE "  " RESET "%c" BG_BLUE "        " RESET"%c              " BG_BLUE "  " RESET"%c" BG_BLUE "        " RESET"%c" BG_BLUE "       " RESET "%c\t", 187, 187, 187, 187, 187, 187, 187);
    printf(BG_WHITE_B BLUE "     _=======%c%c=====    " RESET "\n", 240, 240);
    printf("\t" BG_WHITE_B YELLOW "%c" BLUE "   A @@@@@@@@" YELLOW "@@" BLUE "@@@@ " YELLOW "%c" RESET "\t", 186, 186);
    printf(BG_BLUE "  " RESET "%c%c%c" BG_BLUE "  " RESET "%c" BG_BLUE "  " RESET "%c   " BG_BLUE "  " RESET "%c%c%c%c" BG_BLUE "  " RESET "%c%c%c%c              " BG_BLUE "  " RESET "%c%c%c%c" BG_BLUE "  " RESET "%c%c%c%c" BG_BLUE "  " RESET "%c%c%c%c%c%c\t", 201, 205, 205, 187, 186, 186, 200, 205, 205, 201, 205, 205, 188, 186, 200, 205, 205, 201, 205, 205, 188, 201, 205, 205, 205, 205, 188);
    printf(BG_WHITE_B BLUE "    //    " BLACK "\\" BLUE "#####" BLACK "/   " BLUE "=>  " RESET "\n");
    printf("\t" BG_WHITE_B YELLOW "%c  " BLUE " N @@@@@@@@*" YELLOW "@@@" BLUE "@@ " YELLOW "%c" RESET "\t", 186, 186);
    printf(BG_BLUE "  " RESET "%c  " BG_BLUE "  " RESET "%c" BG_BLUE "  " RESET "%c   " BG_BLUE "  " RESET "%c   " BG_BLUE "  " RESET"%c       " BG_BLUE "     " RESET "%c    " BG_BLUE "  " RESET"%c   " BG_BLUE"  " RESET"%c   " BG_BLUE "     " RESET "%c\t", 186, 186, 186, 186, 186, 187, 186, 186, 187);
    printf(BG_WHITE_B BLUE "  <=      " BLACK"/" BLUE "####" BLACK"/  " BLUE"//    " RESET "\n");
    printf("\t" BG_WHITE_B YELLOW "%c" BLUE "   G @@@@@@@@" YELLOW "@@@@" BLUE "@@ " YELLOW "%c" RESET "\t", 186, 186);
    printf(BG_BLUE "  " RESET "%c  " BG_BLUE "  " RESET "%c" BG_BLUE "  " RESET "%c   " BG_BLUE "  " RESET "%c   " BG_BLUE "  " RESET"%c       %c%c%c%c%c%c    " BG_BLUE "  " RESET "%c   " BG_BLUE"  " RESET "%c   " BG_BLUE "  " RESET "%c%c%c%c\t", 186, 186, 186, 186, 186, 200, 205, 205, 205, 205, 188, 186, 186, 201, 205, 205, 188);
    printf(BG_WHITE_B BLUE "    ========%c%c=====%c    " RESET"\n", 240, 240, 196);
    printf("\t" BG_WHITE_B YELLOW "%c" BLUE "     @@@@@@@#" YELLOW "@@@@@" BLUE "@ " YELLOW "%c" RESET "\t",186, 186);
    printf(BG_BLUE "      " RESET "%c%c%c" BG_BLUE "      " RESET "%c%c   " BG_BLUE "  " RESET "%c                 " BG_BLUE"  " RESET "%c   " BG_BLUE"  " RESET "%c   " BG_BLUE"  " RESET "%c\t\t", 201, 188, 200, 201, 188, 186, 186, 186, 186);
    printf(BG_WHITE_B BLACK "        /" BLUE "#####" BLACK"/         " RESET "\n");
    printf("\t" BG_WHITE_B YELLOW "%c" BLUE "     @@@@@" YELLOW "@@@@@@@" BLUE "#@ " YELLOW "%c" RESET "\t", 186, 186);
    printf("%c%c%c%c%c%c%c  %c%c%c%c%c%c%c    %c%c%c                 %c%c%c   %c%c%c   %c%c%c\t\t", 200, 205, 205, 205, 205, 205, 188, 200, 205, 205, 205, 205, 205, 188, 200, 205, 188, 200, 205, 188, 200, 205, 188, 200, 205, 188);
    printf(BG_WHITE_B BLACK "       /" BLUE "#####" BLACK "/          " RESET "\n");
    printf("\t" BG_WHITE_B YELLOW "%c" BLUE "     @@" YELLOW "@@@@@@@@@@" BLUE "@@ " YELLOW "%c" RESET "\t\t\t\t\t\t\t\t\t", 186, 186);
    printf(BG_WHITE_B BLACK " ______________________ " RESET "\n");
    printf("\t" BG_WHITE_B YELLOW "%c", 200);
	for (int i = 1; i < 21; i++){
			printf("%c", 205);
	}
	printf("%c" RESET "\t\t\t\t\t\t\t\t\t", 188);
    printf(BG_WHITE_B BLACK"   I T  F A C U L T Y   " RESET "\n");
    return 0;
}

