#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>

#include "sharevar.h"

#define MAXSIZE 80

void fileaccess(int fd, int count);

int shmid;
syncvars *shmptr;

int main(int argc, char *argv[])
{
   int fd, count;
   if(argc != 3){
      printf("usage: process0 filename count\n");
      return -1;
   }
   count = atoi(argv[2]);

   fd = open(argv[1], O_RDWR, 0);
   fileaccess(fd, count);

   return 0;
}

void fileaccess(int fd, int count){
   void lockfile (void);
   void unlockfile (void);

   int i, k, value; pid_t pid;
   char buff[MAXSIZE];
   
   shmid = shmget(SHMKEY, sizeof(syncvars), PERMS | IPC_CREAT);
   shmptr = (syncvars *) shmat(shmid, (void *) NULL, 0);
   pid = getpid();

   for(i = 0; i < count; i++){
      lockfile();
      while(shmptr->turn == 1 && shmptr->flag[1] == TRUE );
      
      //critical stuff
      lseek(fd, 0L, 0);
      k = read(fd, buff, MAXSIZE); buff[k] = '\0';
      sscanf(buff, "%d\n", &value);
      value++;

      sprintf(buff, "%10d\n", value);
      lseek(fd, 0l, 0);
      k = strlen(buff); write(fd, buff, k);
      printf("pid = %d, new value = %d\n", pid, value);
      unlockfile();   }
}

void lockfile (void){
   shmptr->flag[0] = TRUE;
   shmptr->turn = 1;
}

void unlockfile (void){
   shmptr->flag[0] = FALSE;
}