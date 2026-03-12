FROM ubuntu:22.04

ENV user msg
ENV port 7777

RUN apt-get update
RUN apt-get -y install socat adduser

RUN adduser -u 1234 $user
WORKDIR /home/$user

COPY ./flag .
COPY ./wish_list .

RUN chmod 755 ./wish_list
RUN chmod 444 ./flag

EXPOSE $port
CMD socat TCP-LISTEN:$port,reuseaddr,fork EXEC:./wish_list,stderr
