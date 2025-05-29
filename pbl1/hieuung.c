#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // cho hàm usleep

//color
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

// background color
#define BG_BLACK   "\x1B[40m"
#define BG_RED     "\x1B[41m"
#define BG_GREEN   "\x1B[42m"
#define BG_YELLOW  "\x1B[43m"
#define BG_BLUE    "\x1B[44m"
#define BG_MAGENTA "\x1B[45m"
#define BG_CYAN    "\x1B[46m"
#define BG_WHITE   "\x1B[47m"
#define BG_WHITE_B "\x1B[107m"

#define INVERT "\033[7m"
#define UNDERLINE "\033[4m"



const char* colors[] = { "\033[31m", "\033[33m", "\033[32m", "\033[36m", "\033[34m", "\033[35m" };

void rainbowText(const char* text) {
    for (int i = 0; text[i]; i++) {
        printf("%s%c", colors[i % 6], text[i]);
        fflush(stdout);
        usleep(20000); // 20ms
    }
    printf("\033[0m\n");
}


void printWithDelay(const char *line, int delayPerChar) {
    while (*line) {
        printf("%c", *line++);
        fflush(stdout); // In ra ngay
        usleep(delayPerChar); // Delay từng ký tự
    }
}

void printMainMenu() {
    int delayPerChar = 10000;
    system("clear"); // hoặc "cls" nếu chạy Windows


    printf(BOLD WHITE BG_BLUE " MAIN MENU " RESET "\n");
    printf(CYAN);
    printWithDelay("1. Select graph from file\n", delayPerChar);
    printWithDelay("2. Create new graph\n", delayPerChar);
    printWithDelay("3. Run algorithm \n", delayPerChar);
    printWithDelay("4. View result\n", delayPerChar);
    printf(BOLD);
    printWithDelay("0. EXIT\n", delayPerChar);
    printf(BOLD YELLOW "Your choice: \n" RESET);
}

void progressBar(int steps) {
    printf("[");
    for (int i = 0; i < steps; i++) {
        usleep(100000); // 100ms
        printf("#");
        fflush(stdout);
    }
    printf("] Done!\n");
}

void loadingSpinner(int durationSeconds) {
    const char* spin = "|/-\\";
    for (int i = 0; i < durationSeconds * 3; i++) {
        printf("\r%c Loading...", spin[i % 4]);
        fflush(stdout);
        usleep(100000); // 100ms
    }
    printf("\rDone!         \n");
}




int main(){
    printMainMenu();
    progressBar(10);
    loadingSpinner(5);
    rainbowText("HEllo cac ban abcdefghiklmn.");
    printf(INVERT BG_BLUE"Inverse text" RESET "\n");
    printf(UNDERLINE "Underlined text" RESET "\n");
    return 0;
}
