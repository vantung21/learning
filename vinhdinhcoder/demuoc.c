#include<stdio.h>
#include<math.h>
int main(){
    long long n,a[1000000],b[1000000];
    
    FILE *inputFile = fopen("demuoc.inp","r");
    FILE *outputFile = fopen("demuoc.out","w");
    if (inputFile == NULL || outputFile == NULL) {
        printf("Khong the mo tep.\n");
        return 1;
    }
    fscanf(inputFile,"%lld",&n);
    int cnt=0;
    for(long long i=2; i<=sqrt(n); i++){
        if(n%i==0){
            a[cnt]=i;
            b[cnt]=n/i;
            cnt++;
        }
    }
    fprintf(outputFile,"%lld co %d uoc. Danh sach uoc:\n1\n",n,cnt*2+2);
    for(int i=0; i<cnt; i++){
        fprintf(outputFile,"%lld\n",a[i]);
    }
    for(int i=cnt-1; i>=0; i--){
        fprintf(outputFile,"%lld\n",b[i]);
    }
    fprintf(outputFile,"%lld",n);
    fclose(inputFile);
    fclose(outputFile);

}