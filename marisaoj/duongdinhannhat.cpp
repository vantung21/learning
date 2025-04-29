#include<iostream>
#include<limits.h>
#include<vector>
#include<queue>

using namespace std;


const long long INF = LLONG_MAX;
long long L[1000000], P[1000000] = {0};
vector<pair<int, int>> adj[1000000];

void dijkstra(){
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq; // pair luu (khoang cach, dinh)
    for(int i=0; i<= sizeof(adj)/sizeof(adj[0]); i++){
        L[i] = INF;
    }
    L[1] = 0;
    pq.push({0, 1});
    while(!pq.empty()){
        int u = pq.top().second;
        int d = pq.top().first;
        pq.pop();
        if(d>L[u]) continue;

        for(auto t : adj[u]){
            int v = t.first;
            int w = t.second;
            if(L[v]> L[u] + w){
                L[v] = L[u] + w;
                P[v] = u;
                pq.push({L[v], v});
            }
        }
    }
}
int main(){
    int n,m;
    
    cin>> n>> m;
    int a[n], s = 0;
    for(int i=0; i<m; i++){
        int u,v,w;
        cin>> u>>v>>w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }
    dijkstra();
    if(L[n] == INF){
        cout << -1<< "\n";
        return 0;
    }
    else {
        cout<< L[n]<< endl;
        int p = n;
        while(p){
            a[s++] = p;
            p = P[p];
        }
        for(int i=s-1; i>=0; i--){
            cout<< a[i] << " ";
        }
    }
    return 0;
    
}