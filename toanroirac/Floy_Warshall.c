#include<stdio.h>
#include<limits.h>

#define maxn 101

void Floyd(int graph[][maxn], int n, int begin, int end){
    int D[maxn][maxn], P[maxn][maxn];

    //khoi tao 
    for(int i=1; i<=n; i++){
        for(int j=1; j<=n; j++){
            if(graph[i][j]==0){
                D[i][j] = 9999;
                P[i][j] = 0;
            }
            else{
                D[i][j] = graph[i][j];
                P[i][j] = j;
            }
        }
    }

    for(int k=1; k<=n; k++){
        for(int i=1; i<=n; i++){
            for(int j=1; j<=n; j++){
                if(D[i][j] > D[i][k] + D[k][j]){
                    D[i][j] = D[i][k] + D[k][j];
                    P[i][j] = P[i][k];
                }
            }
        }
    }
    printf(" duong di ngan nhat tu (%d) den (%d) la: %d\n",begin, end, D[begin][end]);
    printf("duong di: ");
    int t = begin;
    while(t != end){
        printf("%d -> ",t);
        t = P[t][end];
    }
    printf("%d\n",end);
}

void nhap(int graph[][maxn], int n){
    for(int i=1; i<=n; i++){
        for(int j=1; j<=n; j++){
            scanf("%d",&graph[i][j]);
        }
    }
}

int main(){
    int graph[maxn][maxn], n, a,b;
    scanf("%d", &n);
    nhap(graph, n);
    scanf("%d%d",&a,&b);
    Floyd(graph, n,a,b);

    

}