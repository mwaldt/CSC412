#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#include "sharevar.h"

/*Variables needed for shared memory segment*/
/*Set up as external variables for programming ease*/
int shmid;
syncvars *shmptr;

int main(int argc, char *argv[]){
	FILE *fp; int initial, final; int status;

	/*Check for command line arguments*/
	if(argc != 3){
		printf("usage: %s filename count\n", argv[0]);
		return -1;
	}

	/*Deterime initial value in the file before update*/
	fp = fopen(argv[1], "r");
	fscanf(fp, "%d", &initial);
	fclose(fp);

	/*Create a shared memory segmenmt for the given key*/
	/*provided one does not exist already*/
	shmid = shmget(SHMKEY, sizeof(syncvars), PERMS | IPC_CREAT);
	/*Attach the shared memory segment to this process.*/
	shmptr = (syncvars *) shmat(shmid, (void *) NULL, 0);

	/*Initialize the shared memory for Peterson's Algorithm*/
	shmptr->flag[0] = FALSE;
	shmptr->flag[1] = FALSE;
	shmptr->turn = 0;

	/*Launch the two processes*/
	if(fork() == 0){
		execlp("process0", "process0", argv[1], argv[2], (char *) NULL);
	}
	if(fork() == 0){
		execlp("process1", "process1", argv[1], argv[2], (char *) NULL);
	}
	/*Wait for the two processes to terminate*/
	wait(&status); wait(&status);

	/*Detatch the shared memory segment*/
	shmdt((void *) shmptr);
	/*Remove the shared memory segment*/
	shmctl(shmid, IPC_RMID, (struct shmid_ds *) NULL);

	/*Determine the file value in file after update*/
	fp = fopen(argv[1], "r");
	fscanf(fp, "%d", &final);
	fclose(fp);

	/*Print value in file before and after two-process update*/
	printf("\n\n****Initial value in file %d\n\n", initial);
	printf("****Final value in file %d\n\n", final);

	return 0;
}