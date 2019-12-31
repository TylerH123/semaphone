#include "control.h"

int main(int argc, char * argv[]) {
  if (argc > 1) {
    if(strcmp(argv[1], "-c") == 0) {
      createSem();
      createSharedMemory();
      createFile(FILE);
    }
    else if (strcmp(argv[1], "-r") == 0) {
      int sd = semget(SEM, 1, 0);
      struct sembuf s;
      s.sem_num = 0;
      s.sem_op = -1;
      printf("trying to get in\n");
      semop(sd, &s, 1);
      readFile(FILE);
      int smd = shmget(SHM, SIZE, 0600);
      printf("\n");
      removeSharedMemory(smd);
      removeFile(FILE);
      removeSem(sd);
    }
    else if (strcmp(argv[1],"-v") == 0 ) {
      readFile(FILE);
    }
  }
  else{
    printf("NO TAG FOUND!\n" );
  }
  return 0;
}
