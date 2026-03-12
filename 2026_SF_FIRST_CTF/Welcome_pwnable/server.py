#!/usr/bin/env python3
import socket
import sys

HOST = '0.0.0.0'
PORT = 9999

def handle_client(conn, addr):
    """클라이언트 연결 처리"""
    print(f"[*] Connection from {addr[0]}:{addr[1]}")

    try:
        # 환영 메시지
        conn.sendall(b"=" * 50 + b"\n")
        conn.sendall(b"  Welcome to CTF Warmup Challenge!\n")
        conn.sendall(b"=" * 50 + b"\n\n")

        # 플래그 읽기
        try:
            with open('flag', 'r') as f:
                flag = f.read().strip()
        except FileNotFoundError:
            flag = "FLAG{test_flag_replace_me}"

        # 플래그 전송
        conn.sendall(f"Here's your flag: {flag}\n\n".encode())
        conn.sendall(b"Congratulations! You've completed the warmup!\n")

        # 연결 즉시 종료
        conn.shutdown(socket.SHUT_RDWR)

    except Exception as e:
        print(f"[-] Error handling client: {e}")
    finally:
        conn.close()
        print(f"[*] Connection closed: {addr[0]}:{addr[1]}")

def main():
    """메인 서버 루프"""
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        s.bind((HOST, PORT))
        s.listen(5)

        print(f"[+] Server listening on {HOST}:{PORT}")
        print("[*] Waiting for connections...")

        try:
            while True:
                conn, addr = s.accept()
                handle_client(conn, addr)
        except KeyboardInterrupt:
            print("\n[*] Server shutting down...")
            sys.exit(0)

if __name__ == '__main__':
    main()
