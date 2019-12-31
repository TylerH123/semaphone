#include "control.h"

int main() {
  int sd = semget(SEM, 1, 0);
  struct sembuf s;
  s.sem_num = 0;
  s.sem_op = -1;
  printf("trying to get in\n");
  semop(sd, &s, 1);
  writeLine();
  s.sem_op = 1;
  semop(sd, &s, 1);
  return 0;
}
