/***************************************************************
Names:  Cuasi, Beaverly
        Tulabot, Victor
Group:   48
Section:  S16
***************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char String20[21];

typedef struct{
    int input[3];
    int process[3][100] // dapat yung # of rows = details.input[1]
}Feature;

void GetInputs(FILE *fp, Feature *details){
	int X,Y,Z;

    for(int i=0; i<3; i++){
        fscanf(fp, "%d", &details->input[i]);
    }

    for(int i=0; i<3; i++){
        for(int j=0; j<details.input[1]; j++){
            fscanf(fp, "%d", &details->process[j][i]);
        }
    }

    // for(i=0; i<10; i++){
    //     for(j=0; j<10; j++){
    //         fscanf(fp, "%d", &details->X);
    //     }
    // }

    fscanf(fp, "%d", &X);
    // printf("%d", X);

    fscanf(fp, "%d", &Y);
    // printf("%d", Y);
    
    fscanf(fp, "%d", &Z);
    // printf("%d", Z);

	// for(i=0;i<MAX_ANIMALS;i++){
	// 	for(j=0;j<MAX_BINARY;j++){
	// 		fscanf(fp,"%d",&details->AnimalFeatures[i][j]);
	// 	}

	// }

	// for(i=0;i<MAX_ANIMALS;i++){
	// 	fscanf(fp,"%s",details->ClassName[i]);
	// }

	// for(i=0;i<=MAX_ANIMALS;i++){
	// 	fgets(details->AnimalName[i-1],50,fp);
	// }

	// for(i=0;i<MAX_ANIMALS;i++){
	// 	details->AnimalNum[i] = 0;
	// }
}

void FCFS(Feature details){
    for(int i=0; i<details.input[1]; i++){
        printf("\nP[%d]", i);
        printf("\nStart Time: %d  End Time: %d ", i, i);
        printf("\nWaiting Time: %d", i);
        printf("\nTurnaround Time: %d", i);
        printf("\n************************************");
    }
    
};

int main(){
    FILE *fp;
    String20 filename;
    Feature details;

    //open input file
    if((fp = fopen("Sample1.txt","r")) == NULL){
            printf("ERROR");
            exit(1);
        }
    //get inputs
    GetInputs(fp,&details);
    // fscanf(fp,"%d",&rounds);
    fclose(fp);

    
    // printf("Input values X Y Z: ");
    // scanf("%d %d %d", &X, &Y, &Z);

    // while( (X != 0 || X != 1 || X != 2 || X != 3) && (Y <= 3 || Y >= 100) ){
    //     printf("Invalid input, please try again: ");
    //     printf("\nInput values X Y Z: ");
    //     scanf("%d %d %d", &X, &Y, &Z);
    // }

    if(details.input[0] != 3){
        details.input[2] = 1;
    }

    switch(details.input[0]){
        // First Come First Serve (FCFS)
        case 0: 
            printf("First Come First Serve (FCFS) Scheduling");
            printf("\n%d %d %d", details.input[0], details.input[1], details.input[2]);
            FCFS(details);
            break;
        // Non-preemptive Shortest-Job First (NSJF)
        case 1:
            printf("Non-preemptive Shortest-Job First (NSJF)");
            printf("\n%d %d %d", details.input[0], details.input[1], details.input[2]);
            break;
        // Preemptive Shortest-Job First (PSJF) 
        case 2:
            printf("Preemptive Shortest-Job First (PSJF)");
            printf("\n%d %d %d", details.input[0], details.input[1], details.input[2]);
            break;
        // Round-Robin (RR)
        case 3:
            printf("Round-Robin (RR)");
            printf("\n%d %d %d", details.input[0], details.input[1], details.input[2]);
            break;

        // default:
        //     printf("Invalid input, please try again: ");
        //     scanf("%d %d %d", &X, &Y, &Z);
        //     break;
    }
    return 0;
}