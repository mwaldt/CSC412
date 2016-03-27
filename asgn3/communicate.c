#include <stdlib.h>
#include <stdio.h>

void runsrc(int pfd[], char **argv, int pid);
void rundest(int pfd[], char **argv, int pid);
int n;

int main(int argc, char **argv){
	int pid, status;
	int fd[2];

	if(argc != 2){
		printf("usage: %s n\n", argv[0]);
		exit(-1);
	}

	pipe(fd);

	printf("\n");

	runsrc(fd, argv, pid);
	rundest(fd, argv, pid);
	close(fd[0]); close(fd[1]);

	while((pid = wait(&status)) != -1){
		//fprintf(stderr, "process %d exits with %d\n", pid, WEXITSTATUS(&status));
	}
	printf("\n");
	exit(0);
}

void runsrc(int pfd[], char **argv, int pid){
	switch(pid = fork()){
		case 0:
			dup2(pfd[1], 1);
			close(pfd[0]);
			char *arg[] = {"writer", argv[1], NULL};
			printf("writer %s", argv[1]);
			execvp("writer", arg); //run cmd
			perror("writer"); //it failed
		default:
			break;
		case -1:
			perror("fork");
			exit(1);
	}
}

void rundest(int pfd[], char **argv, int pid){
	switch(pid = fork()){
		case 0:
			dup2(pfd[0], 0);
			close(pfd[1]);
			char *arg[] = {"reader", argv[1], NULL};
			execvp("reader", arg); //run cmd
			perror("reader"); //it failed
		default:
			break;
		case -1:
			perror("fork");
			exit(1);
	}
}