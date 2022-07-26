#include <bits/stdc++.h>
using namespace std;

class segTree {
	private:
		vector<long long> psum;
		int tot_size,start_point;
		// tot_size stores total size of psum, start_point stores location of first data item
		void upd (int ind) {psum[ind]=comb(psum[2*ind],psum[2*ind+1]);};
		long long comb (long long, long long);

	public:
		segTree() {
			tot_size=0;
			start_point=0;
		}
		void init (vector<int> &);
		long long sum_rng (int,int);
		long long value (int a) {return psum[start_point+a];}
		void update (int ind, int value);
		// Deletes the tree
		void del_tree () {
			psum.clear();
			tot_size=0;
			start_point=0;
		}
};

// Initialises segment tree with a vector, identity to be chosen as per underlying operation
void segTree::init (vector<int> &a) {
	int n=a.size();
	tot_size=1;
	while (tot_size<n) tot_size*=2;
	start_point=tot_size;
	tot_size*=2;
	psum.resize(tot_size);
	for (int i=1; i<tot_size; i++) psum[i]=0ll;
	// Here 0 is the identity element as addition is the underlying operation
	// site 2
	for (int i=0; i<n; i++) psum[start_point+i]=(long long)a[i];
	for (int i=start_point-1; i>=1; i--) upd(i);
}

// Computes the sum over a range of indices in logarithmic time
long long segTree::sum_rng (int low, int high) {
	long long tot=0;
	// site
	int l=start_point+low;
	int h=start_point+high;
	// While loop controls the nodes to be combined
	while (l<=h) {
		if (l%2==1) {
			tot=comb(tot,psum[l]);
			l++;
		}
		if (h%2==0) {
			tot=comb(tot,psum[h]);
			h-=2;
		}
		l/=2;
		h/=2;
	}
	return tot;
}

// Updates data structure upon change in data item in logarithmic time
void segTree::update (int ind, int val) {
	int index=start_point+ind;
	int org=psum[index];
	psum[index]=(long long)val;
	index/=2;
	while (index>=1) {
		upd(index);
		index/=2;
	}
	return;
}

// Can be customized to reflect an underlying operation of your choice
long long segTree::comb (long long a, long long b) {
	return a+b;
	// site
}