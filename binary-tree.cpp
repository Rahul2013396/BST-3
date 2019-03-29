#include <iostream>
using namespace std;

class Node
{
	public:
	int data;
	// Children
	Node *left;
	Node *right;
	Node *par;

	Node(int val)
	{
		data = val;
		left = NULL;
		right = NULL;
		par = NULL;
	}
};

class BiST
{
	public:
	Node *root;
	int count=0;

	BiST() { root = NULL; }

	void insert(int value)
	{
		 insertHelper(root, value);
		 count++;
	
	}

	void insertHelper(Node *curr, int value)
	{
		if (root == NULL)
		{
			root = new Node(value);
			count++;
		}
		// Else compare the curr data with value
		else if (value < curr->data)
		{
			// else move left and call insertH
			if (curr->left == NULL)
			{
				curr->left = new Node(value);
				curr->left->par = curr;
			}
			else
				insertHelper(curr->left, value);
		}
		else
		{
			// Else move right and call insertH
			if (curr->right == NULL)
			{
				curr->right = new Node(value);
				curr->right->par = curr;
			}
			else
				insertHelper(curr->right, value);
		}
  	}

  	void display()
	{displayHelper(root);}

  	void displayHelper(Node *curr)
	{
		// Base condition
		if (curr == NULL)
			return;
		// Display left.
		displayHelper(curr->left);
		// Display current
		cout << curr->data << ",";
		// Display right
		displayHelper(curr->right);
	}

	void displayFancy()
	{
		displayFancyHelper(root,0);
	}

	void displayFancyHelper(Node * cur,int s)
	{
		//when at the end of a trail return
		if(cur==NULL)
		{return;}
		//go left and increase the number of spaces
		displayFancyHelper(cur->left,s+1);
		//print the spaces
		for(int i=0;i<4*s;i++){cout<<" ";}
		//print the data
		cout<<cur->data<<endl;
		//go right and increase the number of spaces
		displayFancyHelper(cur->right,s+1);
  	}

	Node* search(Node * cur,int value)
	{
		if(cur==NULL)
		{return NULL;}
		if(cur->data==value)
		{return cur;}
		if(cur->data<value)
		{return search(cur->right,value);}
		else
		{return search(cur->left,value);}
	}
    Node * find_node(Node * cur)
    {
        while(cur->left != NULL)
        {
           cur = cur->left;
        }
         return cur;
    }
	
	void delet(Node * cur)
	{
		Node* temp=cur;
		if(cur->right!=NULL)
		{
			temp=temp->right;
			while(temp->left!=NULL)
			{
				temp=temp->left;
			}
			cur->data=temp->data;
			if(temp->right!=NULL)
			{delet(temp);
			count--;}
			else
			{
				temp->par->right=NULL;
				delete temp;
				count--;
			}
		}
		else
		{
			temp=temp->left;
			while(temp->right!=NULL)
			{
				temp=temp->right;
			}
			cur->data=temp->data;
			if(temp->left!=NULL)
			{delet(temp);
			count--;}
			else
			{
				temp->par->left=NULL;
				delete temp;
				count--;
			}
		}
	}
	int counti()
	{
		return count;
	}
	void printrangehelper(Node* curr,int low,int high)
	{
		if(curr == NULL){return;}
		printrangehelper(curr->left,low,high);
		if((curr->data)>=low && (curr->data)<=high){cout << curr->data << ",";}
		printrangehelper(curr->right,low,high);
	}
	void printrange(int low,int high)
	{	
		printrangehelper(root,low,high);
	}
	int rangecounthelper(Node* curr,int low,int high){
		if(!curr){return 0;}
		if(curr->data == high && curr->data == low){return 1;}
		if((curr->data)<=high && (curr->data)>=low)
			{return 1 + rangecounthelper(curr->left,low,high) + rangecounthelper(curr->right,low,high);}
		else if((curr->data)<low){return rangecounthelper(curr->right,low,high);}
		else{return rangecounthelper(curr->left,low,high);}
	}
	int rangecount(int low,int high)
	{	
		return rangecounthelper(root,low,high);
	}
    int height2(Node* curr){
		if(!curr){return 0;}
		int lh = height2(curr->left);
		int rh = height2(curr->right);
		if(lh>rh){return (lh+1);}
		else {return (rh+1);}
	}
};

int main()
{
	BiST lol;
	lol.insert(4);
	lol.insert(8);
	lol.insert(2);
	lol.insert(3);
	lol.insert(90);
	lol.insert(78);
	lol.insert(5);	
	lol.insert(67);
	lol.insert(6);
	lol.displayFancy();
	if ( lol.search ( lol.root , 2) == NULL)
	{
		cout << "Not Found"<<endl;
	}
	else
	{
		cout<<"Found"<<endl;
	}   
    cout <<  lol.find_node(lol.root)->data << endl;
	lol.delet(lol.root);
	lol.delet(lol.search(lol.root,78));
	lol.displayFancy();
	cout<< lol.counti();
	int x ,y ;
	cin >> x >>y;
	lol.printrange(x,y);
	cout << endl <<"Number of items in the range = " << lol.rangecount(x,y) <<endl;
	cout << "The height of tree = " << lol.height2(lol.root) << endl;
}