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
    int process[100][3];
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
        }
    }
}

void FCFS(Feature details){
	int WT = 0, // Waiting Time
        TT = 0, // Turnaround Time
        ST = 0, // Start Time
        ET = 0, // End Time
        temp = 0;
    float AWT = 0.0; // Average Waiting Time
    
    for(int i=0; i<details.input[1]; i++){
        temp = i;
        for (int j=0; j<details.input[1]; j++){
            // check arrival time
            if(details.process[j][1] < details.process[temp][1]){
                temp = j;
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
        details.process[temp][1] = 999;
    }

    AWT = AWT / details.input[1];
    printf("\nAverage Waiting Time: %.2f", AWT);
    
};

void NSJF(Feature details){
	int WT = 0, // Waiting Time
        TT = 0, // Turnaround Time
        ST = 0, // Start Time
        ET = 0, // End Time
        temp = 0;
    float AWT = 0.0; // Average Waiting Time

    // Process 1 always run
    
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
        WT = ST - details.process[temp][1];
        TT = TT + details.process[temp][2];
        AWT = AWT + WT;
        printf("\nP[%d]", details.process[temp][0]);
        printf("\nStart Time: %d  End Time: %d ", ST, ET);
        printf("\nWaiting Time: %d", WT);
        printf("\nTurnaround Time: %d", TT);
        printf("\n************************************");
        details.process[temp][2] = 999;
    }

    AWT = AWT / details.input[1];
    printf("\nAverage Waiting Time: %.2f", AWT);
    
};

void PSJF(Feature details){
    /*
        1) Do process 1
        2) Check next arrival time (NAT)
        2) If NAT.BT < CurrentBT, change process
        3) If NAT.BT > CurrentBT, put in queue

        // input[1] = Arrival Time
        // input[2] = Burst Time
    */

	int WT = 0, // Waiting Time
        TT = 0, // Turnaround Time
        ST = 0, // Start Time
        ET = 0, // End Time
        temp = 0, temp2 = 0,
        NBT = 0,
        NAT = 0,
        nProcess = details.input[1];
    float AWT = 0.0; // Average Waiting Time

    int flag[details.input[1]], // if (flag == 1) preemp, if == 0 not preemp
        data[details.input[1]][2]; // contains the ST and ET of preemp

    for(int i=0; i<details.input[1]; i++){
        flag[i] = 0;
        for(int j=0; j<2; j++){
            data[i][j] = 0;
        }
    }

// Process 1 always run
    
    for(int i=0; i<nProcess; i++){
        temp = i;
        // check if last iteration of processes
        if(i == details.input[1]){
            // check if flag exists
            int isFlag = 0;
            for(int l=0; l<details.input[1]; l++){
                if(flag[l] == 1){
                    isFlag = 1;
                }
            }
            // if flag exists, get the skipped iteration
            if(isFlag == 1){
                for(int m=0; m<details.input[1]; m++){
                    // look only for < 999 value
                    if(details.process[m][2] < 999){
                        temp = m;
                    }
                }
            }
            
        }
        for (int j=0; j<details.input[1]; j++){
            // first process
            if(i == 0){

                // look for the first arrival time
                if(details.process[j][1] <= details.process[temp][1]){
                    temp = j;
                    temp2 = temp;

                    // check next burst time
                    for(int k=0; k<details.input[1]; k++){

                        // skip j or temp
                        if(k != temp){
                            // check next shortest burst time
                            if(details.process[k][2] < details.process[temp2][2]){

                                // store burst time
                                NBT = details.process[k][2];

                                // store arrival time
                                NAT = details.process[k][1];

                                // change temp2
                                temp2 = k;
                                flag[temp] = 1;
                            }
                        }
                    }
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

        

        if(flag[temp] == 1 && i == 0){
            ST = ET;
            ET = ET + details.process[temp][2] - (details.process[temp][2] - NAT);
            data[i][0] = 0;
            data[i][1] = details.process[temp][2] - (details.process[temp][2] - NAT);
            details.process[temp][2] = details.process[temp][2] - NAT;
            nProcess++;
        }
        else{
            ST = ET;
            ET = ET + details.process[temp][2];
            WT = ST - details.process[temp][1];
            TT = WT + details.process[temp][2];
            if(flag[temp] == 1){
                for(int i=0; i<details.input[1]; i++){
                    if(data[i][1] != 0){
                        AWT = AWT + ST - data[i][1];
                    }
                }
            }
            else{
                AWT = AWT + WT;
            }
            printf("\nP[%d]", details.process[temp][0]);
            if(flag[temp] == 1){
                for(int i=0; i<details.input[1]; i++){
                    if(data[i][1] != 0){
                        printf("\nStart Time: %d  End Time: %d ", data[i][0], data[i][1]);
                    }
                }
            }
            printf("\nStart Time: %d  End Time: %d ", ST, ET);
            if(flag[temp] == 1){
                for(int i=0; i<details.input[1]; i++){
                    if(data[i][1] != 0){
                        printf("\nWaiting Time: %d", ST - data[i][1]);
                    }
                }
            }
            else{
                printf("\nWaiting Time: %d", WT);
            }
            printf("\nTurnaround Time: %d", TT);
            printf("\n************************************");
            
            
            details.process[temp][2] = 999;
        }
        
    }

    AWT = AWT / details.input[1];
    printf("\nAverage Waiting Time: %.2f", AWT);
};

void RR(Feature details){
    /*
        1.) Iterate per process
        2.) Check Arrival Time
        3.) Check if cBT > QT
        4.) if cBT > QT, cBT - QT then next process. Flag cProcess
            Suggestion: cBT / QT = # of switches
                        put cPiD into array for queuing
        5.) if cBT <= QT, finish cProcess
    */

    int WT = 0, // Waiting Time
        TT = 0, // Turnaround Time
        ST = 0, // Start Time
        ET = 0, // End Time
        temp = 0, temp2 = 0,
        lET = 0, // Last Ending Time of finished process
        nProcess = details.input[1], // # of processes
        AT = 0, // Arrival Time
        QT = details.input[2]; // Quantum Time
    float AWT = 0.0; // Average Waiting Time
    int flag[details.input[1]][details.input[1]],
        data[50][4],
        BT[details.input[1]];

    for(int i=0; i<details.input[1]; i++){
        flag[i][0] = 0; // flag[i][0] = flag 
        flag[i][1] = details.process[i][1]; // flag[i][1] = AT
        BT[i] = details.process[i][2]; // burst time
    }
    for(int i=0; i<50; i++){
        for(int j=0; j<4; j++){
            data[i][j] = 0;
        }
    }

    for(int i=0; i<nProcess; i++){
        temp = i;
        for (int j=0; j<details.input[1]; j++){
            // check if temp >= nProcess
            if(temp >= nProcess-1){
                if(details.process[j][1] >= 0){
                    temp = j;
                }
            }
            

            // check arrival time
            if(details.process[j][1] < details.process[temp][1] && details.process[j][1] >= 0){
                temp = j;
            }
        }
        
        // check burst time with quantum time
        if(details.process[temp][2] > QT){
            temp2 = temp;
            flag[temp][0] = 1;
            nProcess++;
            int newTime = details.process[temp][2] - QT;
            ST = ET;
            ET = ET + QT;
            data[i][0] = details.process[temp][0];
            data[i][1] = ST;
            data[i][2] = ET;
            data[i][3] = QT;
            details.process[temp][2] = newTime;
            /*
                look for next arrival time
                check if within process time
            */
           int cAT = flag[temp][1];
           for(int p=0; p<nProcess; p++){
               if(details.process[p][1] > details.process[temp2][1]){
                   temp2 = p;
               }
           }
           for(int p=0; p<nProcess; p++){
               if(details.process[p][1] < details.process[temp2][1] && details.process[p][1] > cAT){ // check
                   temp2 = p;
               }
           }
           int newcAT = details.process[temp2][1] - 1;
           if(details.process[temp2][1] >= ST && details.process[temp2][1] <= ET && details.process[temp2][1] <= newcAT){
               printf("\nnice pID: %d", details.process[temp2][0]);
           }
           else{
               // look for highest arrival time
                for(int l=0; l<nProcess; l++){
                    if(details.process[l][1] >= details.process[temp2][1] && details.process[l][1] <= ET){
                        temp2 = l;
                    }
                }
           }
            

            // change arrival time for queue
            
            details.process[temp][1] = details.process[temp2][1] + 1;
        }
        else{
            if(flag[temp][0] == 1 && details.process[temp][2] <= QT && details.process[temp][2] > 0){
                nProcess++;
                int newTime = details.process[temp][2] - details.process[temp][2];
                ST = ET;
                ET = ET + details.process[temp][2];
                data[i][0] = details.process[temp][0];
                data[i][1] = ST;
                data[i][2] = ET;
                data[i][3] = details.process[temp][2];
                details.process[temp][2] = newTime;
            }
        }
        if(flag[temp][0] == 0 && details.process[temp][2] > 0){
            ST = ET;
            ET = ET + details.process[temp][2];
            
            lET = ET;
            TT = ET - details.process[temp][1];
            WT = TT - BT[temp]; 
            AWT = AWT + WT;
            printf("\nP[%d]", details.process[temp][0]);
            printf("\nStart Time: %d  End Time: %d ", ST, ET);
            printf("\nWaiting Time: %d", WT);
            printf("\nTurnaround Time: %d", TT);
            printf("\n************************************");
            details.process[temp][1] = -1;
        }
        else if (flag[temp][0] == 1 && details.process[temp][2] == 0){ 
            int cBT = 0;
            printf("\nP[%d]", details.process[temp][0]);
            for(int i=0; i<50; i++){
                if(data[i][2] != 0 && data[i][0] == details.process[temp][0]){
                    printf("\nStart Time: %d  End Time: %d ", data[i][1], data[i][2]);
                    cBT += data[i][3];
                    ST = data[i][1];
                    ET = data[i][2];

                }
            }
            ET = ET + details.process[temp][2];
            
            lET = ET;
            TT = ET - flag[temp][1];
            WT = TT - BT[temp];
            AWT = AWT + WT;
            printf("\nWaiting Time: %d", WT);
            printf("\nTurnaround Time: %d", TT);
            printf("\n************************************");
            details.process[temp][1] = -1;
        }
    }

    AWT = AWT / details.input[1];
    printf("\nAverage Waiting Time: %.2f", AWT);
}

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

    if(details.input[0] < 0 || details.input[0] > 3){
        printf("Input invalid");
        exit(1);
    }

    if(details.input[2] < 1 || details.input[2] > 100){
        printf("Input invalid");
        exit(1);
    }

    if(details.input[1] < 3 || details.input[1] > 100){
        printf("Input invalid");
        exit(1);
    }

    if(details.input[2] < 1 || details.input[2] > 100){
        printf("Input invalid");
        exit(1);
    }

    if(details.input[0] != 3){
        details.input[2] = 1;
    }

    switch(details.input[0]){
        // First Come First Serve (FCFS)
        case 0: 
            printf("First Come First Serve (FCFS) Scheduling");
            FCFS(details);
            break;
        // Non-preemptive Shortest-Job First (NSJF)
        case 1:
            printf("Non-preemptive Shortest-Job First (NSJF)");
            NSJF(details);
            break;
        // Preemptive Shortest-Job First (PSJF) 
        case 2:
            printf("Preemptive Shortest-Job First (PSJF)");
            PSJF(details);
            break;
        // Round-Robin (RR)
        case 3:
            printf("Round-Robin (RR)");
            RR(details);
            break;
    }
    return 0;
}