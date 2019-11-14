#include <stdio.h>
int aa3(int,int,int);
int cc3(int,int,int);
int main(){
    int a,b,c;
    a=3,b=4,c=8;
    printf("%d 와 %d 와 %d 중에 가장 큰 수는 %d이고 가장 작은 수는 %d 이다.",a,b,c,aa3(a,b,c),cc3(a,b,c));
}
int aa3(int a,int b,int c){
    int d;
    if(a>b)
        d=a;
    else
    {
        d=b;
    }
    if(d>c)
        return d;
    else
    {
        return c;
    }
    

}
int cc3(int a,int b,int c){
    int d;
    if(a<b)
        d=a;
    else
        d=b;
    if(d<c)
        return d;
    else
        return c;
    
}