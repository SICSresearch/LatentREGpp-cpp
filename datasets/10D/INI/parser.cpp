#include <bits/stdc++.h>
#define  pb             push_back
#define  mp             make_pair
#define  INF            0x3fffffff

#include <sstream>

using namespace std;

typedef long long ll;
typedef double lf;
typedef vector<vector<int> > graph;

int ind[] = {1000, 2000, 5000};

int main ( ) {
//    ios_base::sync_with_stdio(false);
//    cin.tie(0);

    int D = 10;
    bool dicho = true;
    int items = 175;

    for ( int i = 0; i < 3; ++i ) {
        for ( int j = 1; j <= 10; ++j ) {
            stringstream ss1, ss2;
            ss1 << "INI-" << D << "D-" << (dicho ? "dicho" : "poly") << "-" << ind[i] << "x" << items << "-" << j << ".csv";
            ss2 << "INITIAL-" << D << "D-" << (dicho ? "dicho" : "poly") << "-" << ind[i] << "x" << items << "-" << j << ".csv";
            string filename1 = ss1.str();
            string filename2 = ss2.str();

            ifstream in(filename1.c_str());
            ofstream out(filename2.c_str());

            string s;
            in >> s;

            cout << filename1 << endl;
            cout << filename2 << endl;

            for ( int h = 0; h < items; ++h ) {

                in >> s;
                cout << s << endl;
                int unnecessary = 0;
                for ( ; s[unnecessary] != ','; ++unnecessary );

                s = s.substr(unnecessary + 1, s.size() - unnecessary);
                out << s << '\n';
            }

            in.close();
            out.close();
        }
    }


}
