FROM ubuntu:22.04
ENV DEBIAN_FRONTEND=noninteractive\
    LC_CTYPE=C.UTF-8

# 포트 설정
EXPOSE 30777

# 레포지토리 변경
RUN sed -i "s/archive.ubuntu/mirror.kakao/g" /etc/apt/sources.list

# 업데이트
RUN apt update && apt upgrade -y
RUN apt install -y xinetd ssh
RUN apt install -y --no-install-recommends tzdata

# 타임존 설정
RUN echo "Asia/Seoul" > /etc/timezone
RUN rm -f /etc/localtime
RUN dpkg-reconfigure --frontend noninteractive tzdata

# 서비스 설정
RUN touch /var/log/seq_rop.log
RUN touch /etc/xinetd.d/seq_rop
RUN echo "service seq_rop                         " >> /etc/xinetd.d/seq_rop
RUN echo "{                                       " >> /etc/xinetd.d/seq_rop
RUN echo "    flags = REUSE                       " >> /etc/xinetd.d/seq_rop
RUN echo "    disable = no                        " >> /etc/xinetd.d/seq_rop
RUN echo "    socket_type = stream                " >> /etc/xinetd.d/seq_rop
RUN echo "    wait = no                           " >> /etc/xinetd.d/seq_rop
RUN echo "    user = secu                         " >> /etc/xinetd.d/seq_rop
RUN echo "    server = /home/secu/seq_rop         " >> /etc/xinetd.d/seq_rop
RUN echo "    port = 30777                        " >> /etc/xinetd.d/seq_rop
RUN echo "    protocol = tcp                      " >> /etc/xinetd.d/seq_rop
RUN echo "    log_type = FILE /var/log/seq_rop.log" >> /etc/xinetd.d/seq_rop
RUN echo "    log_on_success = HOST DURATION EXIT " >> /etc/xinetd.d/seq_rop
RUN echo "}                                       " >> /etc/xinetd.d/seq_rop
RUN echo "seq_rop 30777/tcp" >> /etc/services


# 계정 설정
RUN useradd secu -m -s /bin/bash
RUN echo "secu:p4ass@#!!a9dfa" | chpasswd
RUN echo "root:pa14098#@!9102afda!" | chpasswd

# ASLR 설정
RUN touch /etc/sysctl.d/01-disable-aslr.conf
RUN echo "kernel.randomize_va_space = 2" >> /etc/sysctl.d/01-disable-aslr.conf

# 기본 권한 설정
RUN chmod -R 700 /bin
RUN chmod -R 700 /sbin
RUN chmod -R 700 /usr/bin
RUN chmod -R 700 /usr/sbin
RUN chmod 755 /bin
RUN chmod 755 /sbin
RUN chmod 755 /usr/bin
RUN chmod 755 /usr/sbin
RUN chmod 755 /bin/ls
RUN chmod 755 /bin/cat
RUN chmod 755 /bin/sh
RUN chmod 755 /bin/dash
RUN chmod 755 /bin/bash
RUN chmod 600 /etc/passwd
RUN chmod 600 /etc/passwd-
RUN chmod 600 /etc/group
RUN chmod 600 /etc/group-
RUN chmod 600 /etc/shadow
RUN chmod 600 /etc/shadow-
RUN chmod -R 700 /var/log
RUN chmod -R 700 /var/tmp
RUN chmod 700 /var
RUN chmod 700 /tmp
RUN chmod 600 /dev/shm

# 바이너리 복사
COPY flag.txt /home/secu/flag
COPY seq_rop /home/secu/seq_rop
RUN ln -s /home/secu/flag /flag

# 홈 디렉토리 설정
RUN rm -rf /home/secu/.bash_history
RUN rm -rf /home/secu/.bash_logout
RUN rm -rf /home/secu/.bashrc
RUN rm -rf /home/secu/.profile
RUN rm -rf /home/secu/.cache
RUN ln -s /dev/null /home/secu/.bash_history
RUN ln -s /dev/null /home/secu/.bash_logout
RUN ln -s /dev/null /home/secu/.bashrc
RUN ln -s /dev/null /home/secu/.profile
RUN ln -s /dev/null /home/secu/.cache
RUN chown secu.secu /home/secu/.bash_history
RUN chown secu.secu /home/secu/.bash_logout
RUN chown secu.secu /home/secu/.bashrc
RUN chown secu.secu /home/secu/.profile
RUN chown secu.secu /home/secu/.cache
RUN chown secu.secu /home/secu
RUN chown secu.secu /home/secu/flag
RUN chown secu.secu /home/secu/seq_rop
RUN chmod 500 /home/secu
RUN chmod 400 /home/secu/flag
RUN chmod 500 /home/secu/seq_rop

CMD ["/usr/sbin/xinetd","-dontfork"]
