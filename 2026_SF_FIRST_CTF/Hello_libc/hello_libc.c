//gcc -no-pie -fno-stack-protector -Wl,-z,relro,-z,now hello_libc.c -o hello_libc
#include <stdio.h>

long library_pointer[10];

void library_plus(){
   int idx = 0;

   printf("Hello Libc!\n");
   scanf("%d", &idx);

   printf("hi : %p\n", library_pointer[idx]);

   return 0;
}

void func(char* ptr){
   printf("Now it's time for us to part ways. See you later....\n");
   printf("> ");
   read(0, ptr, 88);

   return 0;
}

int main(){
   setvbuf(stdin, NULL, _IONBF, 0);
   setvbuf(stdout, NULL, _IONBF, 0);

   char buf[48];

   library_plus();
   func(buf);

   printf("Bye Bye\n");

   return 0;
}
