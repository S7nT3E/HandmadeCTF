FROM ubuntu:22.04

RUN apt-get -o Acquire::Check-Valid-Until=false -o Acquire::Check-Date=false update && apt-get install -y \
    qemu-user-static \
    libc6-armhf-cross \
    libgcc-s1-armhf-cross \
    socat \
    && rm -rf /var/lib/apt/lists/*

RUN useradd -m -s /bin/bash ctf

COPY retro_game_console /home/ctf/retro_game_console
COPY flag.txt      /flag.txt

RUN chmod 755 /home/ctf/retro_game_console \
 && chmod 444 /flag.txt \
 && chown root:root /flag.txt

WORKDIR /home/ctf
USER ctf

EXPOSE 20005

CMD ["socat", \
     "TCP-LISTEN:20005,reuseaddr,fork,keepalive", \
     "EXEC:'qemu-arm-static -L /usr/arm-linux-gnueabihf /home/ctf/retro_game_console',stderr,setsid,sigint,sighup"]
