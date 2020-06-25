#include <iostream>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <random>

using namespace std;

typedef unsigned int uint;
typedef unsigned int data_t;

uint quicktop(data_t* __restrict__ in, uint n, uint k, data_t* __restrict__ large, data_t* __restrict__ small, data_t* __restrict__ result){
	static uint ridx = 0;
	static uint total_n = 0;
	total_n += n;

	uint lidx = 0;
	uint sidx = 0;
	const data_t pivot = in[rand() % n];
	for(uint i = 0; i < n; i++){
		if(in[i] > pivot){
			large[lidx++] = in[i];
		}
		else{
			small[sidx++] = in[i];
		}
	}
	if (lidx > k){
		//large bucket holds all the results
		quicktop(large, lidx, k, in, small, result);
	}
	else if (lidx < k){
		//large bucket hold lidx results, copy it
		memcpy(result + ridx, large, lidx * sizeof(data_t));
		ridx += lidx;

		//have to find rest in small bucket
		quicktop(small, sidx, k - lidx, large, in, result);
	}
	else{
		//large bucket holds exact results :)
		memcpy(result + ridx, large, lidx * sizeof(data_t));
		ridx += lidx;
	}
	return total_n;
}

int main(int argc, char** argv){
	if(argc < 3){
		cout << "usage: ./quicktop <n> <k>" << endl;
		return -1;
	}

	const uint n = atol(argv[1]);
	const uint k = atol(argv[2]);

	data_t *data = new data_t[n];
	data_t *large = new data_t[n];
	data_t *small = new data_t[n];
	data_t *result = new data_t[n];

	srand(23);

	for(uint i = 0; i < n; i++){
		data[i] = i;
	}

	shuffle(data, data + n, default_random_engine(42));

	uint total_n = quicktop(data, n, k, large, small, result);
	cout << "total_n: " << total_n << endl;
	//for(uint i = 0; i < k; i++){
	//	cout << result[i] << " ";
	//}
	//cout << endl;

	delete [] data;
	delete [] large;
	delete [] small;
	delete [] result;
	return 0;
}
