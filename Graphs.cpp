#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define fri(i, a, b) for(ll i = a; i < b; i++)
#define frd(i, a, b) for(ll i = a; i >= b; i--)
#define g(a,b) __gcd(a,b)
#define lcm(a,b) (a*b)/g(a,b)
#define lb(v,key) lower_bound(v.begin(), v.end(), key)
#define ub(v,key) upper_bound(v.begin(), v.end(), key)
#define srtvec(v) sort(v.begin(), v.end())
#define srt(arr,n) sort(arr, arr+n)
#define mem(arr,key) memset(arr, key, sizeof(arr))


const int N = 1000000;
bool isPrime[N];
set<int> s;


void preCalculatorPrime(){
    fill(isPrime+2, isPrime+N, true);
    for(int i = 2; i*i < N; i++){
        for(int j = i*i; j < N; j=j+i)
            isPrime[j] = false;
    }
    for(int i = 2; i < N; i++){
        if(isPrime[i])
            s.insert(i);
    }
}


const long long M = 1e9 + 7;
long long mod(long long x){
    return ((x%M + M)%M);
}


long long add(long long a, long long b){
    return mod(mod(a) + mod(b));
}


long long mul(long long a, long long b){
    return mod(mod(a) * mod(b));
}


int max3(int a, int b, int c){
    if(a > b)
        return (a > c) ? a : c;
    else
        return (b > c) ? b : c;
}


int min3(int a, int b, int c){
    if(a < b)
        return (a < c) ? a : c;
    else
        return (b < c) ? b : c;
}

class DSU{
    private:
        vector<int> parent, size, rank;
    
    public:
        DSU(int n){
            for(int i = 0; i <= n; i++){
                parent.push_back(i);
                size.push_back(1);
                rank.push_back(0);
            }
        }
    
    public:
        int findParent(int node){
            if(parent[node] == node)    return node;
            return parent[node] = findParent(parent[node]);
        }
    
    public:
        void unionSize(int u, int v){
            int pu = findParent(u);
            int pv = findParent(v);
            if(pu == pv)    return;
            if(size[pu] < size[pv]){
                size[pv] += size[pu];
                parent[pu] = pv;
            }
            else{
                size[pu] += size[pv];
                parent[pv] = pu;
            }
        }
        
        void unionRank(int u, int v){
            int pu = findParent(u);
            int pv = findParent(v);
            if(pu == pv)    return;
            if(rank[pu] < rank[pv]){
                parent[pu] = pv;
            }
            else if(rank[pv] < rank[pu]){
                parent[pv] = pu;
            }
            else{
                parent[pv] = pu;
                rank[pu]++;
            }
        }
};

void solve(){
    DSU dsu(int n);
}

void printff(int n, vector<int> adj[]){
    fri(i, 1, n+1){
        cout<<"("<<i<<")";
        for(auto a:adj[i]){
            cout<<" -> "<<a;
        }
        cout<<endl;
    }
}

void bfs(int node, vector<int> adj[], vector<int> &visited){
    queue<int> q;
    q.push(node);
    int temp;
    while(!q.empty()){
        temp = q.front();
        q.pop();
        cout<<temp<<" ";
        for(auto a : adj[temp]){
            if(!visited[a]) visited[a] = 1, q.push(a);
        }
    }
}

void dfs(vector<int> adj[], vector<int> &dfsans, vector<int> &visdfs, int node){
    visdfs[node]++;
    dfsans.push_back(node);
    for(auto a : adj[node]){
        if(!visdfs[a])  dfs(adj, dfsans, visdfs, a);
    }
}

bool checkForCycleDFS(int node, int parent, vector<int> &vis, vector<int> adj[]){
    vis[node]++;
    for(auto a : adj[node]){
        if(!vis[a]){
            if(checkForCycleDFS(a, node, vis, adj))    return true;
        }
        else if(a != parent)    return true;
    }
    return false;
}

bool checkForCycleBFS(int node, int parent, vector<int> &vis, vector<int> adj[]){
    vis[node]++;
    queue<pair<int, int>> q;
    q.push({node, parent});
    while(!q.empty()){
        auto temp = q.front();
        q.pop();
        for(auto a : adj[temp.first]){
            if(!vis[a]){
                q.push({a, temp.first});
                vis[a]++;
            }
            else if(a != temp.second)   return true;
        }
    }
    return false;
}

void sssp_dfs(vector<int> adj[], vector<int> &visited, vector<int> &distance, int node, int dist){
    visited[node]++;
    distance[node] = dist;
    for(auto a : adj[node]){
        if(!visited[a]){
            sssp_dfs(adj, visited, distance, a, dist+1);
        }
    }
}

void sssp_bfs(vector<int> adj[], vector<int> &visited, vector<int> &distance, int node, int dist){
    visited[node]++;
    distance[node] = dist;
    queue<int> q;
    q.push(node);
    int curr;
    while(!q.empty()){
        curr = q.front();
        q.pop();
        for(auto a : adj[curr]){
            if(!visited[a]){
                visited[a]++;
                distance[a] = distance[curr] + 1;
                q.push(a);
            }
        }
    }
}

bool bipartite(vector<int> adj[], vector<int> &visited, vector<int> &color, int node, int col){
    visited[node]++;
    color[node] = col;
    for(auto a : adj[node]){
        if(!visited[a]){
            if(color[a] == -1)  return bipartite(adj, visited, color, a, col^1);
        }
        else if(color[a] == col)    return false;
    }
    return true;
}

void in_out(vector<int> adj[], vector<int> &visited, vector<int> &in, vector<int> &out, int &timer, int node){
    visited[node]++;
    in[node] = timer++;
    for(auto a : adj[node]){
        if(!visited[a]) in_out(adj, visited, in, out, timer, a);
    }
    out[node] = timer++;
}

void max_dist_node(vector<int> adj[], vector<int> &visited, int node, int &mx_node, int &mx, int count){
    visited[node]++;
    if(count > mx){
        mx = count;
        mx_node = node;
    }
    for(auto a : adj[node]){
        if(!visited[a]) max_dist_node(adj, visited, a, mx_node, mx, count+1);
    }
}

void diameter_graph(vector<int> adj[], vector<int> &visi, int node, int &mx, int count){
    visi[node]++;
    mx = max(count, mx);
    for(auto a : adj[node]){
        if(!visi[a])    diameter_graph(adj, visi, a, mx, count+1);
    }
}

bool directed_cycle_dfs(vector<int> adj[], vector<int> &visited, vector<bool> &stk, int node){
    visited[node]++;
    stk[node] = true;
    for(auto a : adj[node]){
        if(!visited[a] && directed_cycle_dfs(adj, visited, stk, a)) return true;
        else if(stk[a]) return true;
    }
    stk[node] = false;
    return false;
}

void topological_sort(vector<int> adj[], vector<int> &visited, vector<int> &indegree, int n){
    queue<int> q;
    int node;
    fri(i, 1, n+1){
        if(!indegree[i])    visited[i]++,   q.push(i);
    }
    while(!q.empty()){
        node = q.front();
        q.pop();
        for(auto a : adj[node]){
            indegree[a]--;
            if(!indegree[a]){
                visited[a]++;
                q.push(a);
            }
        }
        cout<<node<<" ";
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m, a, b;
    cin>>n>>m;
    vector<int> indegree(n+1, 0);
    vector<int> visited(n+1, 0);
    vector<int> adj[n+1];
    fri(i, 0, m){
        cin>>a>>b;
        adj[a].push_back(b);
        //  Next line will be removed for directed graphs
        //adj[b].push_back(a);
        // Next line is for marking indegress of nodes in a directed graph
        indegree[b]++;
    }
    //cout<<"The adjacency list of given graph is: "<<endl;
    //printff(n, adj);
    
    //          BFS TRAVERSAL
    // cout<<"The breadth first search traversal is: "<<endl;
    // fri(i, 1, n+1){
    //     if(!visited[i]){
    //         parent[i] = -1;
    //         visited[i] = 1;
    //         bfs(i, adj, visited);
    //     }
    // }
    
    //          DFS TRAVERSAL
    // cout<<"The depth first search Traversal technique is: "<<endl;
    // vector<int> visdfs(n+1, 0);
    // vector<int> dfsans;
    // fri(i, 1, n+1){
    //     if(!visdfs[i])  dfs(adj, dfsans, visdfs, i);
    // }
    // for(auto a : dfsans)    cout<<a<<" ";
    // cout<<endl;

    //          CYCLE CHECK BY DFS
    // cout<<"Checking for cycle in the graph USING DFS =>"<<endl;
    // vector<int> vis(n+1, 0);
    // bool cycle = false;
    // fri(i, 1, n+1){
    //     if(!vis[i]){
    //         if(checkForCycleDFS(i, -1, vis, adj)){
    //             cycle = true;
    //             cout<<"Cycle is present in the graph."<<endl;
    //         }
    //     }
    // }
    // if(!cycle)  cout<<"No cycle is present in the graph."<<endl;

    //         CYCLE CHECK BY BFS
    // cout<<"Checking for cycle in the graph USING BFS =>"<<endl;
    // vector<int> vis(n+1, 0);
    // bool cycle = false;
    // fri(i, 1, n+1){
    //     if(!vis[i]){
    //         if(checkForCycleBFS(i, -1, vis, adj)){
    //             cycle = true;
    //             cout<<"Cycle is present in the graph."<<endl;
    //         }
    //     }
    // }
    // if(!cycle)  cout<<"No cycle is present in the graph."<<endl;

    //          SINGLE SOURCE SHORTEST PATH (SSSP)
    // ---> DFS method
    // vector<int> distance(n+1, 0);
    // fri(i, 1, n+1){
    //     if(!visited[i]){
    //         sssp_dfs(adj, visited, distance, i, 0);
    //     }
    // }
    // fri(i, 1, n+1){
    //     cout<<"The distance of "<<i<<" from the root is "<<distance[i]<<endl;
    // }
    // ---> BFS method
    // vector<int> distance(n+1, 0);
    // sssp_bfs(adj, visited, distance, 1, 0);
    // fri(i, 1, n+1)  cout<<"The distance of "<<i<<" from the root is "<<distance[i]<<endl;


    //              BIPARTITE GRAPH
    // vector<int> color(n+1, -1);
    // if(bipartite(adj, visited, color, 1, 0))    cout<<"Bipartite graph"<<endl;
    // else    cout<<"Not a bipartite graph"<<endl;
    
    //              IN-OUT TIME OF NODES OF GRAPH
    // Q. Given two nodes, check whether one node lies in the sub-tree of another node or not?
    // int x, y;
    // cin>>x>>y;
    // int timer = 1;
    // vector<int> in(n+1, 0);
    // vector<int> out(n+1, 0);
    // fri(i, 1, n+1){
    //     if(!visited[i]){
    //         in_out(adj, visited, in, out, timer, i);
    //     }
    // }
    // if((in[x]<in[y] && out[x]>out[y]) || (in[y]<in[x] && out[y]>out[x]))    cout<<"YES"<<endl;
    // else    cout<<"NO"<<endl;

    //              DIAMETER OF A TREE
    // --> First dfs to go to the max distant node from any element
    // int mx = 0, max_node = -1;
    // max_dist_node(adj, visited, 1, max_node, mx, 1);
    // --> Second dfs for finding max dist from max_node node
    // vector<int> visi(n+1, 0);
    // diameter_graph(adj, visi, max_node, mx, 1);
    // cout<<"Diameter of the given graph is: "<<mx-1<<endl;

    //              CYCLE CHECK IN DIRECTED GRAPH(DFS method)
    // vector<bool> stk(n+1, false);
    // bool cycle = false;
    // fri(i, 1, n+1){
    //     if(!visited[i] && directed_cycle_dfs(adj, visited, stk, i)) cycle = true;
    // }
    // if(cycle)   cout<<"Cycle Detected"<<endl;
    // else    cout<<"No cycle detected"<<endl;

    //              TOPOLOGICAL SORT (BFS method)   ----    Kahn's Algorithm
    // topological_sort(adj, visited, indegree, n);
    //----> Cycle detection can be done using topological sort as it in a cyclic graph, there might be some point where there is no node of indegree 0
    // for this we can use a count variable for everytime we pop from q, and at last check if count == v
    // if yes, no cycle else cycle is present in the graph.
    return 0;
}