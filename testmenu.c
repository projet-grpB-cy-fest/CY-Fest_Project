#include <stdio.h>
#include <stdlib.h>

int main(){
    int val,rep;
    do{
        printf("1 ou 2: ");
        val=1;
        if(val==1){
            printf("\n1,2 ou 3: ");
            scanf("%d",rep);
            if(rep==1){
                printf("1");
            }
            else if(rep==2){
                printf("2");
            }
        }
    }while(rep!=3);
    return 0;
}