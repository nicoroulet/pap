#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <functional>

using namespace std;

int main() {
	int n;
	cin >> n;
	vector<int> v(n);
	int i;
	for (i = 0; i < n; ++i) {
		cin >> v[i];
	}
	sort(v.begin(), v.end(), greater<int>());
	vector<int> reps;
	i = 0;
	int last = -1;
	int j = 0;
	while (i < n) {
		last = v[i];
		reps.push_back(1);
		i++;
		while(i < n && v[i] == last){
			reps[j]++;
			i++;
		}
		j++;
	}
	int size = reps.size();
	vector<double> expected(size);
	int mayores = reps[0];	// acumulo la cant de mayores.
	expected[0] = 1; // solo los elementos más grandes, todos iguales. Tiempo esperado = 1
	for (int i = 1; i < size; ++i) {
		int r = reps[i];
		expected[i] = expected[i-1] - r;
		for (int j = 1; j <= r; ++j) {
			expected[i] += (mayores+j)/(double)(j);
		}
		mayores += r;
	}

	printf("%.6f\n", expected[size-1]);

	//cout << "expected = " << expected[size-1] << endl;
	/*for (std::vector<int>::iterator it = reps.begin(); it != reps.end(); ++it) {
		cout << *it << " ";
	}
	cout << endl;
	*/
	return 0;
}