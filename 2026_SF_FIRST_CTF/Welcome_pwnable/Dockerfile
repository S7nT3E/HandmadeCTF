FROM python:3.11-slim

# 작업 디렉토리 설정
WORKDIR /app

# 파일 복사
COPY server.py .
COPY flag .

# 권한 설정
RUN chmod +x server.py && \
    chmod 444 flag

# 포트 노출
EXPOSE 20004

# 서버 실행
CMD ["python3", "server.py"]
