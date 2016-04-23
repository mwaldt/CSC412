#include <stdio.h>

int main(int argc, char *argv[]){
	int length;
	int fRange[2];
	int i;

	printf("Welcome to FIFO Page Replacement Simulation Program!!\n\n");

	printf("Enter the length of the reference String: ");
	scanf("%d", &length);

	printf("Enter the reference String: ");
	int ref[length];
	while(i < length){
		scanf("%d", &ref[i++]);
	}


	printf("Enter the range for number of frames: ");
	i = 0;
	while(i < 2){
		scanf("%d", &fRange[i++]);
	}

	int faults;
	for(i = fRange[0]; i <= fRange[1]; i++){
		faults = getFaults(i, ref, length);
		printf("Page fault for %d frames(s): %d\n", i, faults);
	}
}

// int i is the number of frames
int getFaults(int i, int refstr[], int l){
	int page[i];
	int j, k, c = 0, f = 0;
	for(j = 0; j < i; j++){		//set up sentinal values
		page[j] = -1;
	}
	if(i == 1){
		for(j = 0; j < l; j++){
			if(page[0] != refstr[j])
				f++;
			page[0] = refstr[j];	
		}
		return f;
	}else{
		for(j = 0; j < l; j++){
			for(k = 0; k < i; k++){
				if(page[k] == -1){				//empty space
					page[k] = refstr[j];
					k = i;
					c++;
				}else if(page[k] == refstr[j]){	//elemnt found
					for(k; k > 0; k--){			//reorder
						page[k] = page[k-1];
					}
					page[0] = refstr[j];
					k = i;
				}else if(c == i && k == i-1){	//table full
					while(k > 0){			//reorder
						page[k] = page[k-1];
						k--;
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