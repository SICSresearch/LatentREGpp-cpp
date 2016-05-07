#include <bits/stdc++.h>
#define  pb             push_back
#define  mp             make_pair
#define  MAX            200015
#define  MAXM           1001
#define  INF            0x3fffffff
#define  MAXLOG         18
#define  MOD            1000000007LL

using namespace std;

typedef long long ll;
typedef vector<vector<int> > graph;
graph G;

void xd ( string s ) {
    freopen(s.c_str(), "r", stdin);
    while ( getline(cin, s) )
        cout << s << '\n';
}

int main ( ) {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int ITER = 2, ITEMS = 50;

    freopen("estimation.txt", "w", stdout);

    xd("estimation1-2.txt");
    xd("estimation3-4.txt");
}

