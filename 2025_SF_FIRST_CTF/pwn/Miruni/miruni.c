#define _CRT_SECURE_NO_WARNNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void print_flag() {
    int fd = open("flag", O_RDONLY);
    if (fd == -1) {
        return;
    }
    char flag[0x40] = { '\0' };
    if (!read(fd, flag, 0x3f)) {
        close(fd);
        return;
    }
    flag[strlen(flag)] = '\n';
    write(1, flag, strlen(flag));
    close(fd);
}

void setup_environment() {
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);
}

int main() {
    setup_environment();

    uint8_t num1 = 0;
    int8_t num2 = 0;
    int16_t result = 0;
    char calc = 0;

    printf("[>] Welcome to the Security First!!\n");
    printf("[>] You can use only +, -\n");
    printf("[>] You can use integers 100 or less\n");

    printf("[>] PLS Input num op num (ex. 10 + 10)\n");
    printf("> ");
    scanf("%hhd %c %hhd", &num1, &calc, &num2);

    if (num1 > 100 || num2 > 100) {
        printf("[!] I can't calculate these nums..!!\n");
        return 1;
    }

    switch (calc) 
    {
        case '+': 
            result = num1 + num2; 
            break;
        case '-': 
            result = num1 - num2; 
            break;
        default: 
            printf("[!] Please enter the correct calculation method..!!!!\n"); 
            return 1;
    }
    printf("[>] %hhd %c %hhd = %hd\n", num1, calc, num2, result);

    if (result > 200) {
        print_flag();
    }

    return 0;
}
