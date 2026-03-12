FROM ubuntu:22.04

ENV user poka
ENV port 7777

RUN apt-get update
RUN apt-get -y install socat adduser

RUN adduser -u 1234 $user
WORKDIR /home/$user

COPY ./flag .
COPY ./poka_playlist .

RUN chmod 755 ./poka_playlist
RUN chmod 444 ./flag

EXPOSE $chall_port
CMD socat TCP-LISTEN:$chall_port,reuseaddr,fork EXEC:./poka_playlist,stderr
