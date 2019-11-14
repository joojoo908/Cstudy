#include <stdio.h>

int main(){
    int kk1[2][4];
    int kk2[4][2];

    for(int i=0;i<2;i++){
        for(int j=0;j<4;j++){
            kk1[i][j]=2*i+j+1;
            printf("%d ",kk1[i][j]);
        }
        printf("\n");
    }
    for(int i=0;i<4;i++){
        for(int j=0;j<2;j++){
            kk2[i][j]=kk1[j][i];
            printf("%d ",kk2[i][j]);
        }
        printf("\n");
    }
    
}