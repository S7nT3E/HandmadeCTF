// gcc -fno-stack-protector -no-pie -z execstack snack_shell.c -o snack_shell

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>
#include <sys/mman.h>

void init() {
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);
}

void snack() {
    char buffer[0x100];
    printf("Enter your snacks set : ");
    read(0, buffer, 0x110);
}

int main() {
    init();

    register volatile uint64_t rsp asm("rsp");
    printf("[+] Snack shop location : 0x%016lx\n", rsp);

    snack();
    return 0;
}
