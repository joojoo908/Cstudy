#include<stdio.h>
int p1=0,p2=1,pn,n;
int f[100];
int pibo(int num){
    if(f[num]==-1){
        f[num]=pibo(num-1)+pibo(num-2);
        return f[num];
    }
    else 
        return f[num];
}


int main(){
    f[0]=p1;          
    f[1]=p2;
    for(int i=2;i<100;i++)
        f[i]=-1;
    pibo(10);
    printf("%d",f[7]);
    return 0;
}