#include <stdio.h>

int vulc(){
	char buf[0x20];
	printf("[+] buffer address : %p\n", buf);
	printf("[+] Input : ");
	read(0, buf, 0x40);
}

int main(){
	setbuf(stdout, NULL);
	printf("Welcome to RTS CTF Challenge!\n");
	vulc();
	return 0;
}
