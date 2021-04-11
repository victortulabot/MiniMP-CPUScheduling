/***************************************************************
Names:  Cuasi, Beaverly
        Tulabot, Victor
Group:   48
Section:  S16
***************************************************************/

#include <stdio.h>

int main(){
    int X, Y, Z;
    printf("Input values X Y Z: ");
    scanf("%d %d %d", &X, &Y, &Z);

    while( (X != 0 || X != 1 || X != 2 || X != 3) && (Y <= 3 || Y >= 100) ){
        printf("Invalid input, please try again: ");
        printf("\nInput values X Y Z: ");
        scanf("%d %d %d", &X, &Y, &Z);
    }

    if(X != 3){
        Z = 1;
    }

    switch(X){
        // First Come First Serve (FCFS)
        case 0: 
            printf("First Come First Serve (FCFS) Scheduling");
            printf("\n%d %d %d", X, Y, Z);
            break;
        // Non-preemptive Shortest-Job First (NSJF)
        case 1:
            printf("Non-preemptive Shortest-Job First (NSJF)");
            printf("\n%d %d %d", X, Y, Z);
            break;
        // Preemptive Shortest-Job First (PSJF) 
        case 2:
            printf("Preemptive Shortest-Job First (PSJF)");
            printf("\n%d %d %d", X, Y, Z);
            break;
        // Round-Robin (RR)
        case 3:
            printf("Round-Robin (RR)");
            printf("\n%d %d %d", X, Y, Z);
            break;

        // default:
        //     printf("Invalid input, please try again: ");
        //     scanf("%d %d %d", &X, &Y, &Z);
        //     break;
    }
    return 0;
}