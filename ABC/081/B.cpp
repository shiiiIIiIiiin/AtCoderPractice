#include<stdio.h>
int main(void){
    int N;
    scanf("%d",&N);
    int a[N],i;
    for(i=0;i<N;i++){
        scanf("%d",&a[i]);
    }

    int count=0;

    for(i=0;i<N;i++){
        


        if(a[i]%2!=0){
            break;
        }

        if(i==N-1){
            for(int k=0;k<N;k++){
                a[k]/=2;
            }
            count++;
            i=0;
        }

    }

    printf("%d",count);
    return 0;
}