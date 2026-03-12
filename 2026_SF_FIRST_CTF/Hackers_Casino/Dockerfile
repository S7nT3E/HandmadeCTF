FROM ubuntu:22.04

ENV user secu
ENV port 20000

RUN apt-get update
RUN apt-get -y install socat adduser

RUN adduser -u 1234 $user
WORKDIR /home/$user

COPY ./flag .
COPY ./prob .

RUN chmod 755 ./prob
RUN chmod 444 ./flag

EXPOSE $port
CMD socat TCP-LISTEN:$port,reuseaddr,fork EXEC:./prob,stderr
