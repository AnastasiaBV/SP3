FROM ubuntu
COPY 2.cpp .
RUN apt-get update
RUN apt-get install -y gcc
RUN apt-get install -y g++
RUN g++ 2.cpp -o lab3 -static
CMD ./lab3
