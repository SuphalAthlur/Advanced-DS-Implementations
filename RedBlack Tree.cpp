#include <iostream>
using namespace std;

//Modify element, creator and compare function definitions as per requirement
struct element {
	int a;
};

element creator (int inp) {
	element ret;
	ret.a=inp;
	return ret;
};

int cmp (element x, element y) {
	if (x.a<y.a) return 1;
	else if (x.a>y.a) return -1;
	else return 0;
};

struct node {
	element value;
	bool colour;
	node* parent;
	node* left;
	node* right;
};

class rbTree {
	private:
		//Level 0
		node* root;
		int counter;
		long long occ;

		//Level 1 of abstraction
		void iRec1 (node*);
		void iRec2 (node*);
		void dRec1 (node*);
		void dRec2 (node*);
		void dRec3 (node*);
		void dRec4 (node*);
		void dDecide (node*);
		void lRotate (node*);
		void rRotate (node*);

		//Level 2 of abstraction
		//displayTree, traverseTree and deleteTree use the same counter variable
		node* createNode (element);
		void insertNode (node*);
		bool deleteNode (node*);
		node* searchNode (element);
		void traverseTree (node*,int);
		void displayTree (node*);
		void deleteTree (node*);
		node* returnRoot ()
		{
			return root;
		};

	public:
		rbTree()
		{
			root=NULL;
			counter=0;
			occ=0;
		};

		//Level 3 of abstraction
		//Direct Use: Modify creator, element and compare (cmp) definitions as per need
		//Traversal utility function is not written yet
		//Presently supports insertion, search, node removal, tree deletion and size functions
		//MODIFY the signature of the below functions and the argument list to creator to suit the need
		void insert(int a) {
			insertNode(createNode(creator(a)));
			occ++;
			return;
		};
		void del(int a) {
			if(deleteNode(searchNode(creator(a)))==true) occ--;
			return;
		};
		bool search(int a) {
			if (searchNode(creator(a))==NULL) return false;
			return true;
		};
		void clear() {
			deleteTree(returnRoot());
			return;
		};
		long long size() {
			return occ;
		};
};

node* rbTree::createNode (element x) {
	node* born = new node;
	born->value = x;
	born->colour=true;
	born->parent=born->right=born->left=NULL;
	return born;
}

void rbTree::insertNode (node* x) {
	if (x==NULL) {
		printf ("\nInsufficient memory!\n");
		exit (4);
	}
	if (root==NULL) {
		x->colour=false;
		root=x;
		return;
	}
	node* temp=root;
	while (1) {
		if (cmp(x->value,temp->value)==1) {
			if (temp->left!=NULL) temp=temp->left;
			else {
				temp->left=x;
				x->parent=temp;
				temp=temp->left;
				break;
			}
		}
		else {
			if (temp->right!=NULL) temp=temp->right;
			else {
				temp->right=x;
				x->parent=temp;
				temp=temp->right;
				break;
			}
		}
	}
	if (x->parent->colour==false) return;
	if (x->parent->parent->left!=NULL && x->parent->parent->right!=NULL && 
		x->parent->parent->left->colour==x->parent->parent->right->colour) iRec1 (temp);
	else iRec2 (temp);
}

bool rbTree::deleteNode (node* g) {
	if (g==NULL) return false;
	element hold=g->value;
	node* temp=NULL;
	if (g->left==NULL || g->right==NULL) {
		temp=g;
		if (g==root && g->left==NULL && g->right==NULL) {
			root=NULL;
			delete g;
			return true;
		}
	}
	else {
		temp=g->right;
		while (temp->left!=NULL)
			temp=temp->left;
		g->value=temp->value;
	}
	if (temp->right!=NULL) {
		temp->value=temp->right->value;
		temp=temp->right;
	}
	else if (temp->left!=NULL) {
		temp->value=temp->left->value;
		temp=temp->left;
	}
	dDecide (temp);
	if (temp->parent->left==temp) temp->parent->left=NULL;
	else temp->parent->right=NULL;
	delete temp;
	return true;
}

node* rbTree::searchNode (element a) {
	node* temp=root;
	while (temp!=NULL) {
		if (cmp(a,temp->value)==0) break;
		else if (cmp(a,temp->value)==1) temp=temp->left;
		else temp=temp->right;
	}
	return temp;
}

//0 for preorder, 1 for inorder, 2 for postorder 
void rbTree::traverseTree (node* root, int select) {
	counter++;
	if (root==NULL) return;
	char c=(root->colour==false?'B':'R');
	switch (select) {
		case 0: 
			printf ("%d(%c)\t",root->value.a,c);
			traverseTree (root->left,select);
			counter--;
			traverseTree (root->right,select);
			counter--;
			break;
		case 1:
			traverseTree (root->left,select);
			counter--;
			printf ("%d(%c)\t",root->value.a,c);
			traverseTree (root->right,select);
			counter--;
			break;
		case 2:
			traverseTree (root->left,select);
			counter--;
			traverseTree (root->right,select);
			counter--;
			printf ("%d(%c)\t",root->value.a,c);
			break;
		default:
			printf ("Erraneous input!\n");
			exit(3);
			break;
	}
	if (counter==1) counter=0;
	return;
}

void rbTree::deleteTree (node* temp) {
	counter++;
	if (temp==NULL) return;
	deleteTree (temp->left);
	counter--;
	deleteTree (temp->right);
	counter--;
	delete temp;
	if (counter==1) {
		root=NULL;
		counter=0;
	}
	return;
}

//Flexible framework
void rbTree::displayTree (node* temp) {
	counter++;
	if (counter==1) {
		printf ("\n------->>\n");
		if (temp==NULL) {
			printf ("<<-------\n");
			return;
		}
	}
	if (temp==NULL) return;
	char c=(temp->colour==false?'B':'R');
	for (int i=0; i<counter-1; i++) printf ("\t");
	printf ("%d(%c)\n",temp->value.a,c);
	displayTree (temp->left);
	counter--;
	displayTree (temp->right);
	counter--;
	if (counter==1) {
		counter=0;
		printf ("<<-------\n");
	}
	return;
}

void rbTree::lRotate (node* g) {
	node* temp=g->right;
	if (temp==NULL) {
		printf ("\nError! No right child\n");
		exit (2);
	}
	if (g==root) root=temp;
	else {
		if (g->parent->left==g) g->parent->left=temp;
		else g->parent->right=temp;
	}
	temp->parent=g->parent;
	g->right=temp->left;
	if (temp->left!=NULL) {
		temp->left->parent=g;
	}
	g->parent=temp;
	temp->left=g;
}

void rbTree::rRotate (node* g) {
	node* temp=g->left;
	if (temp==NULL) {
		printf ("\nError! No left child\n");
		exit (1);
	}
	if (g==root) root=temp;
	else {
		if (g->parent->left==g) g->parent->left=temp;
		else g->parent->right=temp;
	}
	temp->parent=g->parent;
	g->left=temp->right;
	if (temp->right!=NULL) {
		temp->right->parent=g;
	}
	temp->right=g;
	g->parent=temp;
}

void rbTree::iRec1 (node* g) {
	g->parent->parent->left->colour=false;
	g->parent->parent->right->colour=false;
	g->parent->parent->colour=true;
	g=g->parent->parent;
	if (g->parent==NULL) {
		g->colour=false;
		return;
	}
	if (g->parent->colour==false) return;
	if (g->parent->parent->left!=NULL && g->parent->parent->right!=NULL && 
		g->parent->parent->left->colour==g->parent->parent->right->colour) iRec1 (g);
	else iRec2 (g);
	return;
}

void rbTree::iRec2 (node* g) {
	if (g->parent->right==g && g->parent->parent->left==g->parent) {
		lRotate (g->parent);
		g=g->left;
	}
	else if (g->parent->left==g && g->parent->parent->right==g->parent) {
		rRotate (g->parent);
		g=g->right;
	}
	if (g->parent->left==g) rRotate (g->parent->parent);
	else lRotate (g->parent->parent);
	g->parent->colour=false;
	g->parent->left->colour=g->parent->right->colour=true;
	return;
}

void rbTree::dRec1 (node* g) {
	if (g->parent->left==g) lRotate (g->parent);
	else rRotate (g->parent);
	g->parent->colour=true;
	g->parent->parent->colour=false;
	dDecide (g);
	return;
}

void rbTree::dRec2 (node* g) {
	if (g->parent->left==g) g->parent->right->colour=true;
	else g->parent->left->colour=true;
	if (g->parent==root) {
		if (g->parent->colour==true) g->parent->colour=false;
		return;
	}
	if (g->parent->colour==false) dDecide (g->parent);
	else g->parent->colour=false;
	return;
}

void rbTree::dRec3 (node* g) {
	if (g->parent->left==g) {
		rRotate (g->parent->right);
		g->parent->right->colour=false;
		g->parent->right->right->colour=true;
	}
	else {
		lRotate (g->parent->left);
		g->parent->left->colour=false;
		g->parent->left->left->colour=true;		
	}
	dRec4(g);
	return;
}

void rbTree::dRec4 (node* g) {
	if (g->parent->left==g) {
		lRotate (g->parent);
		g->parent->parent->colour=g->parent->colour;
		g->parent->colour=false;
		g->parent->parent->right->colour=false;
	}
	else {
		rRotate (g->parent);
		g->parent->parent->colour=g->parent->colour;
		g->parent->colour=false;
		g->parent->parent->left->colour=false;
	}
	return;
}

void rbTree::dDecide (node* temp) {
	if (temp->colour==false) {
		if ((temp->parent->left==temp && temp->parent->right->colour==true) ||
			(temp->parent->right==temp && temp->parent->left->colour==true))
		dRec1 (temp);
		else if (temp->parent->left->colour==false && temp->parent->right->colour==false) {
			if ((temp->parent->left==temp &&
				(temp->parent->right->left==NULL || temp->parent->right->left->colour==false) &&
				(temp->parent->right->right==NULL || temp->parent->right->right->colour==false)) || 
				(temp->parent->right==temp &&
				(temp->parent->left->left==NULL || temp->parent->left->left->colour==false) &&
				(temp->parent->left->right==NULL || temp->parent->left->right->colour==false)))
			dRec2(temp);
			else if ((temp->parent->left==temp &&
				(temp->parent->right->right==NULL || temp->parent->right->right->colour==false)) ||
				(temp->parent->right==temp &&
				(temp->parent->left->left==NULL || temp->parent->left->left->colour==false)))
			dRec3(temp);
			else dRec4(temp);
		}
	}
	return;
}