#include <stdio.h>

int main(void){
    int arr[6]={1,2,3,4,5,6};
    int * ptr1=arr;
    int k= sizeof(arr)/sizeof(int)-1;
    int * ptr2= arr+k;
    int * ch;

    while(1){
        ch=*ptr1;
        ptr1=ptr2;
        ptr2=ch;
        int i=1;
        ptr1=arr+i;
        ptr2=arr+k-i;
        i+=1;
        if(ptr1>=ptr2) break;



    }
    

}