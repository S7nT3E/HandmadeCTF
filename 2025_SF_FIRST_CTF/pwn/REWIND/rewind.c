// gcc -fno-stack-protector -no-pie -z execstack  rewind.c -o rewind

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>
#include <sys/mman.h>

void setup_environment() {
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);
}

void vulnerable_function() {
    char buffer[0x100];
    printf("Enter your shellcode: ");
    read(0, buffer, 0x200);
}

int main() {
    setup_environment();

    register volatile uint64_t rsp asm("rsp");
    printf("[+] rsp : 0x%016lx\n", rsp);

    vulnerable_function();
    return 0;
}
