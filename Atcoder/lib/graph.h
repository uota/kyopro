class Vertex{
public:
    ll value;
    ll parent;
    bool visited;
    Vertex() : visited(false), parent(-1) {};
};

template<class T>
class Edge{
public:
    T dest;
    Edge(const T &dest){this->dest = dest;}
};

template<class T>
class Graph{
public:
    map<T, Vertex> vertices;
    map<T, vector<Edge<T>>> edges;

    void add_edge(const T &vsrc, const T &vdest){
        edges[vsrc].emplace_back(Edge<T>(vdest));
    }

    void add_bidir_edge(const T &v1, const T &v2){
        edges[v1].emplace_back(Edge<T>(v2));
        edges[v2].emplace_back(Edge<T>(v1));
    }
};

template<class T>
void dfs(Graph<T> &G, T start){
    for(pair<T,Vertex> v:G.vertices){
        v.second.visited=false;
    }
    stack<T> stack;
    stack.push(start);
    while(!stack.empty()){
        T top=stack.top(); stack.pop();
        G.vertices[top].visited=true;

        // code here
        // std::cout << top << std::endl;

        for(Edge<T> v:G.edges[top]){
            if(!G.vertices[v.dest].visited){
                stack.push(v.dest);
            }
        }
    }
}

template<class T>
void bfs(Graph<T> &G, T start){
    for(pair<T,Vertex> v:G.vertices){
        v.second.visited=false;
    }
    queue<T> queue;
    queue.push(start);
    while(!queue.empty()){
        T top=queue.front(); queue.pop();
        G.vertices[top].visited=true;

        // code here
         std::cout << top << std::endl;

        for(Edge<T> v:G.edges[top]){
            if(!G.vertices[v.dest].visited){
                queue.push(v.dest);
            }
        }
    }
}

//namespace UnionFind {
//    // Constructor
//    UnionFind(ll sz_): par(sz_), siz(sz_, 1LL) {
//        for (ll i = 0; i < sz_; ++i) par[i] = i; // 初期では親は自分自身
//    }
//    void init(ll sz_) {
//        par.resize(sz_);
//        siz.assign(sz_, 1LL);  // resize だとなぜか初期化されなかった
//        for (ll i = 0; i < sz_; ++i) par[i] = i; // 初期では親は自分自身
//    }
//
//    // Member Function
//    // Find
//    ll root(ll x) { // 根の検索
//        while (par[x] != x) {
//            x = par[x] = par[par[x]]; // x の親の親を x の親とする
//        }
//        return x;
//    }
//
//    // Union(Unite, Merge)
//    bool merge(ll x, ll y) {
//        x = root(x);
//        y = root(y);
//        if (x == y) return false;
//        // merge technique（データ構造をマージするテク．小を大にくっつける）
//        if (siz[x] < siz[y]) swap(x, y);
//        siz[x] += siz[y];
//        par[y] = x;
//        return true;
//    }
//
//    bool issame(ll x, ll y) { // 連結判定
//        return root(x) == root(y);
//    }
//
//    ll size(ll x) { // 素集合のサイズ
//        return siz[root(x)];
//    }
//};
//
int main(){
    Graph<ll> graph;

// 0 ->1 ->2 
//   \>3 ->4
//       \>5
    graph.add_edge(0,1);
    graph.add_edge(1,2);
    graph.add_edge(0,3);
    graph.add_edge(3,4);
    graph.add_edge(3,5);

// 6<->7<->8
//   \>9<->10
//       \>11
    graph.add_bidir_edge(6,7);
    graph.add_bidir_edge(7,8);
    graph.add_bidir_edge(6,9);
    graph.add_bidir_edge(9,10);
    graph.add_bidir_edge(9,11);

//    dfs<ll>(graph, 0);
//    dfs<ll>(graph, 6);
    bfs<ll>(graph, 0);
    bfs<ll>(graph, 6);

}

