// gcc -s sequence_rop.c -o sequence_rop -Wl,-z,relro,-z,now

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

int stage1_chk = 0;
int stage2_chk = 0;

void gift() {
	__asm__(
        "pop %rdi;"
        "ret;"
    );
}
void setup() {
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);
}

void check_sequence1(unsigned long val) {
    if (val == 0xdeadbeef) {
        printf("Stage 1 clear!\n");
	stage1_chk++;
    }
    else {
        exit(1);
    }
}

void check_sequence2(unsigned long val) {
    if (val == 0xcafebabe && stage1_chk == 1) {
        printf("Stage 2 clear!\n");
	stage2_chk++;
    }
    else {
        exit(1);
    }
}

void check_sequence3(unsigned long val) {
    if (val == 0x13371337 && stage2_chk == 1) {
        printf("Stage 3 clear!\n");
        execve("/bin/sh", NULL, NULL);
    }
    else {
        exit(1);
    }
}

void print_nearby() {
    unsigned long canary;
    asm("movq %%fs:0x28, %0" : "=r" (canary));
    printf("Value: %lx\n", canary);
}

void print_address() {
    printf("Address: %p\n", check_sequence1);
}

void get_input() {
    char buffer[128];
    printf("Enter input (max 256 bytes):\n");
    read(0, buffer, 256);
}

void print_menu(){
    printf("\n=== ROP Sequence Challenge ===\n");
    printf("[>] 1. Print nearby value\n");
    printf("[>] 2. Print function address\n");
    printf("[>] 3. Enter sequence\n");
    printf("[>] 4. Exit\n");
    printf("> ");
}

int main() {
    setup();
    int choice;

    while (1) {
        print_menu();
	scanf("%d", &choice);

        switch (choice) {
            case 1:
                print_nearby();
                break;
            case 2:
                print_address();
                break;
            case 3:
                get_input();
                break;
            case 4:
                printf("Goodbye!\n");
                return 0;
            default:
                printf("Invalid choice!\n");
        }
    }
    return 0;
}

