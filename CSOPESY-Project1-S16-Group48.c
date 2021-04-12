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
    int process[100][3]; // dapat yung # of rows = details.input[1]
}Feature;

void GetInputs(FILE *fp, Feature *details){
    for(int i=0; i<3; i++){
        fscanf(fp, "%d", &details->input[i]);
        // input[0] = X
        // input[1] = Y
        // input[2] = Z
    }

    for(int row=0; row<details->input[1]; row++){
        for(int col=0; col<3; col++){
            fscanf(fp, "%d", &details->process[row][col]);
            // printf("%d ", details->process[row][col]);
        }
        // printf("\n");
    }
}

void FCFS(Feature details){
	int WT = 0, // Waiting Time
        TT = 0, // Turnaround Time
        ST = 0, // Start Time
        ET = 0, // End Time
        AWT = 0; // Average Waiting Time
    float FAWT = 0.0; // Final Average Waiting Time
    
    for(int i=0; i<details.input[1]; i++){
        ST = ET;
        ET = ET + details.process[i][2];
        WT = ST;
        TT = TT + details.process[i][2];
        AWT = AWT + WT;
        printf("\nP[%d]", i);
        printf("\nStart Time: %d  End Time: %d ", ST, ET);
        printf("\nWaiting Time: %d", WT);
        printf("\nTurnaround Time: %d", TT);
        printf("\n************************************");
    }

    FAWT = AWT / details.input[1];
    printf("\nAverage Waiting Time: %.2f", FAWT);
    
};

void NSJF(Feature details){
	int WT = 0, // Waiting Time
        TT = 0, // Turnaround Time
        ST = 0, // Start Time
        ET = 0, // End Time
        AWT = 0, // Average Waiting Time
        temp = 0;
    float FAWT = 0.0; // Final Average Waiting Time
    int newArr[details.input[1]][3];

    // Process 1 always run
    // ST = ET;
    // ET = ET + details.process[0][2];
    // WT = ST;
    // TT = TT + details.process[0][2];
    // AWT = AWT + WT;
    // printf("\nP[0]");
    // printf("\nStart Time: %d  End Time: %d ", ST, ET);
    // printf("\nWaiting Time: %d", WT);
    // printf("\nTurnaround Time: %d", TT);
    // printf("\n************************************");
    
    for(int i=0; i<details.input[1]; i++){
        temp = i;
        for (int j=0; j<details.input[1]; j++){
            // first process
            if(i == 0){
                if(details.process[j][1] < details.process[temp][1]){
                    temp = j;
                }
            }
            // check burst time
            else if(details.process[j][2] < details.process[temp][2]){
                temp = j;
            }
            // check arrival time if burst time is equal
            else if(details.process[j][2] == details.process[temp][2]){
                if(details.process[j][1] < details.process[temp][1]){
                    temp = j;
                }
            }
        }
        
        ST = ET;
        ET = ET + details.process[temp][2];
        WT = ST;
        TT = TT + details.process[temp][2];
        AWT = AWT + WT;
        printf("\nP[%d]", details.process[temp][0]);
        printf("\nStart Time: %d  End Time: %d ", ST, ET);
        printf("\nWaiting Time: %d", WT);
        printf("\nTurnaround Time: %d", TT);
        printf("\n************************************");
        details.process[temp][2] = 999;
    }

    FAWT = AWT / details.input[1];
    printf("\nAverage Waiting Time: %.2f", FAWT);
    
};

void PSJF(Feature details){
    /*
        1) Do process 1
        2) Check next arrival time (NAT)
        2) If NAT.BT < CurrentBT, change process
        3) If NAT.BT > CurrentBT, put in queue
    */

	int WT = 0, // Waiting Time
        TT = 0, // Turnaround Time
        ST = 0, // Start Time
        ET = 0, // End Time
        AWT = 0; // Average Waiting Time
    float FAWT = 0.0; // Final Average Waiting Time

    for(int i=0; i<details.input[1]; i++){
        ST = ET;
        ET = ET + details.process[i][2];
        WT = ST;
        TT = TT + details.process[i][2];
        AWT = AWT + WT;
        printf("\nP[%d]", i);
        printf("\nStart Time: %d  End Time: %d ", ST, ET);
        printf("\nWaiting Time: %d", WT);
        printf("\nTurnaround Time: %d", TT);
        printf("\n************************************");
    }

    FAWT = AWT / details.input[1];
    printf("\nAverage Waiting Time: %.2f", FAWT);
    
};

int main(){
    FILE *fp;
    String20 filename;
    Feature details;

    //ask user for input file
    printf("Input filename: ");
    scanf("%s", filename);

    //open input file
    if((fp = fopen(filename,"r")) == NULL){
            printf("%s not found.", filename);
            exit(1);
        }
    //get inputs
    GetInputs(fp,&details);
    fclose(fp);

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
            // printf("\n%d %d %d", details.input[0], details.input[1], details.input[2]);
            FCFS(details);
            break;
        // Non-preemptive Shortest-Job First (NSJF)
        case 1:
            printf("Non-preemptive Shortest-Job First (NSJF)");
            // printf("\n%d %d %d", details.input[0], details.input[1], details.input[2]);
            NSJF(details);
            break;
        // Preemptive Shortest-Job First (PSJF) 
        case 2:
            printf("Preemptive Shortest-Job First (PSJF)");
            // printf("\n%d %d %d", details.input[0], details.input[1], details.input[2]);
            PSJF(details);
            break;
        // Round-Robin (RR)
        case 3:
            printf("Round-Robin (RR)");
            // printf("\n%d %d %d", details.input[0], details.input[1], details.input[2]);
            break;

        // default:
        //     printf("Invalid input, please try again: ");
        //     scanf("%d %d %d", &X, &Y, &Z);
        //     break;
    }
    return 0;
}