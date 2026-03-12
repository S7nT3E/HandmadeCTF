// gcc -fno-stack-protector -no-pie pheidole_noda.c -o pheidole_noda
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

int ant_colony(){
    int fd = open("flag", O_RDONLY);

    if (fd < 0) {
        write(STDERR_FILENO, "Error: Cannot open flag file\n", 30);
        return 1;
    }
    
    char buffer[1024];
    ssize_t bytes_read = read(fd, buffer, sizeof(buffer) - 1);
    
    if (bytes_read < 0) {
        write(STDERR_FILENO, "Error: Cannot read flag file\n", 30);
        close(fd);
        return 1;
    }
    
    buffer[bytes_read] = '\0';
    write(STDOUT_FILENO, buffer, bytes_read);
    
    close(fd);

    return 0;
}

int main(){
    setvbuf(stdout, 0, 2, 0);
    setvbuf(stdin, 0, 2, 0);
    
    char ants[100];
    
    printf("=============== AOF =============\n");
    printf("[>] Welcome to the ant colony!\n");
    printf("[>] You can relocate ants....\n");
    printf("[>] Pls ants relocate new colony!!\n");
    printf("> ");
    read(0, ants, (sizeof(ants) + 0x20));

    return 0;
}
