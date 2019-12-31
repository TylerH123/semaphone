#include "control.h"

int createSem() {
  int r, v;
  int sd = semget(SEM, 1, IPC_CREAT | IPC_EXCL | 0644);
  if(sd == -1) {
    sd = semget(SEM, 1, 0);
    r = semctl(sd, 0, GETVAL, 0);
  }
  else {
    union semun u;
    u.val = 1;
    v = semctl(sd, 0, SETVAL, u);
  }
  printf("semaphore created\n");
  return sd;
}

int removeSem(int sd) {
  semctl(sd, IPC_RMID, 0);
  printf("semaphore removed\n");
  return 0;
}

int createFile(char * file) {
  int fd;
  fd = open(file, O_CREAT | O_EXCL | O_TRUNC, 0644);
  if (fd < 0) {
    fd = open(file, O_TRUNC);
  }
  close(fd);
  printf("file created\n");
  return fd;
}

int removeFile(char * file) {
  if (remove(file) == 0) {
    printf("file removed\n");
  }
  else {
    printf("file not removed\n");
  }
  return 0;
}

int readFile(char * file) {
  int fd;
  fd = open(file, O_RDONLY);
  if(fd < 0) {
    printf("error %d: %s\n", errno, strerror(errno));
    return 1;
  }
  printf("The story so far:\n");
  char line[SIZE];
  while(read(fd, line, SIZE) > 0) {
    printf("%s\n", line);
  }
  close(fd);
}

int createSharedMemory() {
  int smd;
  smd = shmget(SHM, SIZE, IPC_CREAT | 0600);
  printf("shared memory created\n");
  return smd;
}

int removeSharedMemory(int smd) {
  shmctl(smd, IPC_RMID, 0);
  printf("shared memory removed\n");
  return 0;
}

int writeLine() {
  int smd;
  char * line;
  smd = shmget(SHM, SIZE, 0600);
  if(smd < 0) {
    printf("error %d: %s\n", errno, strerror(errno));
    return 1;
  }
  line = shmat(smd, 0, 0);
  printf("Last addition: %s\n", line);
  printf("Your addition: ");
  fgets(line, SIZE, stdin);
  *strchr(line, '\n') = 0;
  int fd = open(FILE, O_WRONLY | O_APPEND);
  write(fd, line, SIZE);
  close(fd);
  shmdt(line);
  return 0;
}
