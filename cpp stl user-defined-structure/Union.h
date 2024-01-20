#include<vector>
#include<algorithm>
#include<numeric>
using namespace std;

// class UnionFind {
// public:
//     vector<int> parent;
//     vector<int> size;
//     int n;
//     // 当前连通分量数目
//     int setCount;
    
// public:
//     UnionFind(int _n): n(_n), setCount(_n), parent(_n), size(_n, 1) {
//         iota(parent.begin(), parent.end(), 0);
//     }
    
//     int findset(int x) {
//         return parent[x] == x ? x : parent[x] = findset(parent[x]);
//     }
    
//     bool unite(int x, int y) {
//         x = findset(x);
//         y = findset(y);
//         if (x == y) {
//             return false;
//         }
//         if (size[x] < size[y]) {
//             swap(x, y);
//         }
//         parent[y] = x;
//         size[x] += size[y];
//         --setCount;
//         return true;
//     }
    
//     bool connected(int x, int y) {
//         x = findset(x);
//         y = findset(y);
//         return x == y;
//     }
// };

class UnionFind {
public:
    UnionFind(vector<vector<char>>& grid) {
        count = 0;
        int m = grid.size();
        int n = grid[0].size();
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == '1') {
                    parent.push_back(i * n + j);
                    ++count;
                }
                else {
                    parent.push_back(-1);
                }
                rank.push_back(0);
            }
        }
    }

    int find(int i) {
        if (parent[i] != i) {
            parent[i] = find(parent[i]);
        }
        return parent[i];
    }

    void unite(int x, int y) {
        int rootx = find(x);
        int rooty = find(y);
        if (rootx != rooty) {
            if (rank[rootx] < rank[rooty]) {
                swap(rootx, rooty);
            }
            parent[rooty] = rootx;
            if (rank[rootx] == rank[rooty]) rank[rootx] += 1;
            --count;
        }
    }

    int getCount() const {
        return count;
    }

private:
    vector<int> parent;
    vector<int> rank;
    int count;
};
