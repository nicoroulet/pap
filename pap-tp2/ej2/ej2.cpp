#include <iostream>
#include <vector>

#define DBG(x) cerr << #x << " = " << (x) << endl

using namespace std;

int compAcc(vector<int> v1, vector<int> v2){
	if (v1[0] < v2[0]) {
	    /* code */
	}
}


int main(){
	int a, d;
	// a acciones, durante d días.
	cin >> a >> d;
	vector<vector<int> > acciones(a, vector<int>(d));

	// leo todo
	for (int i = 0; i < a; ++i) {
		for (int j = 0; j < d; ++j) {
			cin >> acciones[i][j];
		}
	}


	return 0;
}
