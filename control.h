#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/shm.h>

#define SEM 24602
#define SHM 24603
#define SIZE 200
#define FILE "story"

int createSemaphore();
int removeSemaphore(int sd);
int createSharedMemory();
int removeSharedMemory(int smd);
int createFile(char * file);
int removeFile(char * file);
int readFile(char * file);
int writeLine();
