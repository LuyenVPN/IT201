#include <stdio.h>

int main(){
    int a[]={1,4,3,2,3,3};
    int n= sizeof(a)/sizeof(a[0]);
    int temp=0;
    for (int i=0; i<n;i++) {
        for (int j=i+1; j<n; j++) {
            if (a[i]==a[j]) {
                temp++;
            }
        }
    }
    if (temp==0) {
        printf("khong co so trung lap");
        return 0;
    }
    printf("co so trung lap");
    return 0;
}
// do phuc tap la o(n)