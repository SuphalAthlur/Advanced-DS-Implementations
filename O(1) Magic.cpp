#include <bits/stdc++.h>
using namespace std;

class ads {
private:
	// Maintains frequencies of all elements
	vector<int> freq;
	// Maintains inverse of required array
	vector<int> pos;
	// Maintains index of first element of a certain frequency
	vector<int> spoint;
	// Actual array
	vector<int> ord;
	void resize(int n, int m) {
		freq.resize(m+1);
		pos.resize(n+1);
		spoint.resize(m+2);
		ord.resize(n+1);
	}
	void swap (int i1, int i2, vector<int> &v) {
		int temp=v[i1];
		v[i1]=v[i2];
		v[i2]=temp;
	}
public:
	void init (int, int);
	void increment (int);
	void decrement (int);
	int ret (int position) {return ord[position];}
	int fq (int position) {return freq[position];}
	int start (int frequency) {return spoint[frequency];}
	int loc (int ele) {return pos[ele];}
};

void ads::init (int numele, int rng) {
	resize(numele,rng);
	fill (freq.begin(),freq.end(),0);
	for (int i=1; i<=numele; i++) {
		ord[i]=i;
		pos[i]=i;
	}
	spoint[0]=1;
	for (int i=1; i<=rng+1; i++) spoint[i]=numele+1;
	return;
}

// Decrements in O(1) time with swaps and other updates
void ads::decrement (int k) {
	if (freq[k]>0) {
		swap(pos[k],spoint[freq[k]],ord);
		swap(k,ord[spoint[freq[k]]],pos);
		spoint[freq[k]-1]++;
		freq[k]--;
		return;
	}
	else {
		printf ("Error! Frequency dipped below 0\n");
		exit(1);
	}
}

// Increments in O(1) time with swaps and other updates
void ads::increment (int k) {
	if (freq[k]<freq.size()-2) {
		swap(pos[k],spoint[freq[k]+1]-1,ord);
		swap(k,ord[spoint[freq[k]+1]-1],pos);
		spoint[freq[k]+1]--;
		freq[k]++;
		return;
	}
	else {
		printf ("Error! Frequency exceeded maximum\n");
		exit(2);
	}
}

int main ()
{
	
	return 0;
}