#include <stdio.h>
int aa3(int,int,int);
int cc3(int,int,int);
int main(){
    int a,b,c;
    a=3,b=4,c=8;
    printf("%d �� %d �� %d �߿� ���� ū ���� %d�̰� ���� ���� ���� %d �̴�.",a,b,c,aa3(a,b,c),cc3(a,b,c));
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