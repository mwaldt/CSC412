/*Constant and type definitions needed for creating the*/
/*shared memory segment to implement Peterson's Algorithm*/
#define PERMS 0666 /*Acess rights*/
#define SHMKEY ((key_t) 800650198)
#define FALSE 0
#define TRUE 1
typedef struct {
	int flag[2];
	int turn;
} syncvars;
