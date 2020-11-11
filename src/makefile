#
# makefile for mlb sorting utilities
# and demonstrations
#
CC = gcc -std=gnu99 -Wall -Wextra

mlbDriver: mlbDriver.c team.o
	$(CC) -o mlbDriver team.o mlbDriver.c

team.o: team.h team.c
	$(CC) -c -o team.o team.c
