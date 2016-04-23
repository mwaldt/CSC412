#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main(int argc, char *argv[]){
	int length;
	int fRange[2];

	printf("Welcome to FIFO Page Replacement Simulation Program!!\n\n");

	length = 12;
	int ref[] = {1, 2, 3, 4, 5, 6, 1, 2, 5, 3, 4, 6};

	int faults = getFaults(1, ref, length);
	printf("Page fault for %d frames(s): %d\n", 1, faults);
	faults = getFaults(6, ref, length);
	printf("Page fault for %d frames(s): %d\n", 6, faults);
}

// int i is the number of frames
int getFaults(int i, int refstr[], int l){
	int page[i];
	int j, k, f = 0;
	for(j = 0; j < i; j++){		//set up sentinal values
		page[i] = -1;
	}
	if(i == 1){
		return l;
	}else{
		for(j = 0; j < l; j++){
			for(k = 0; k < i; k++){
				if(page[k] == -1){				//empty space
					page[k] = refstr[j];
					k = i;
				}else if(page[k] == refstr[j]){	//elemnt found
					printf("Reorder at index %d\n", k);
					for(k; k > 0; k--){			//reorder
						page[k] = page[k-1];
					}
					page[0] = refstr[j];
					k = i;
				}else if(k == i-1){				//table full
					printf("Table full at index %d\n", k);
					for(k; k > 0; k--){			//reorder
						page[k] = page[k-1];
					}
					page[0] = refstr[j];
					k = i;
					f++;
				}
			}
		}
		return f;
	}//else	
}//end getFaults
