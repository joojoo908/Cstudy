#include <stdio.h>
int re(int num){
    if(num==2)
        return 2;
    return num*re(num-1);
}
int main(){
    printf("%d",re(4));
    return 0;
}