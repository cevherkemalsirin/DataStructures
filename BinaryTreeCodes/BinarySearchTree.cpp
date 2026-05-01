#include <iostream>

using namespace std;

struct treenode {
	treenode* leftchild;
	int val;
	treenode* rightchild;

	treenode(int val):val(val),leftchild(nullptr),rightchild(nullptr){}
};


class BinarySearchTree {
	treenode* root;

	void Print_Inorder(treenode* node)
	{
		if (!node) return;

		Print_Inorder(node->leftchild);
		cout << node->val << " ";
	    Print_Inorder(node->rightchild);
	}

public:
	BinarySearchTree(int rootValue) : root(new treenode(rootValue)){}

	void Insert(int key)
	{

		if (!root)
		{
			root = new treenode(key);
			return;
		}
		treenode* p = root;
		treenode* insert = nullptr;
		treenode* parentPtr = nullptr;
		
		while (p)
		{
			parentPtr = p;
			if (p->val == key)
			{
				return;
			}
			else if (p->val > key)
			{
				p = p->leftchild;
			}
			else
			{
				p = p->rightchild;
			}
			
		}
		insert = new treenode(key);
		if (parentPtr->val < key)
		{
			parentPtr->rightchild = insert;
		}
		else
		{
			parentPtr->leftchild = insert;
		}
		
	}

	treenode* Search(int key)
	{

		treenode* p = root;

		while (p)
		{
			if (key == p->val) return p;
			else if (key > p->val) 
			{
				p = p->rightchild;
			}
			else
			{
				p = p->leftchild;
			}
		}

		return nullptr;

	}

	static treenode* Presuccessor(treenode* node)
	{
		node = node->leftchild;
		while (node && node->rightchild)
		{
			node = node->rightchild;
		}
		return node;
	}

	static treenode* Successor(treenode* node)
	{
		node = node->rightchild;
		while (node && node->leftchild)
		{
			node = node->leftchild;
		}
		return node;
	}

	void Print_InOrder()
	{
		Print_Inorder(root);
	}

};








int main5()
{
	return 0;
	BinarySearchTree bst(30);

	bst.Insert(2);
	bst.Insert(3);
	bst.Insert(50);
	bst.Insert(40);
	bst.Insert(60);
	bst.Insert(43);
	//bst.Insert(15);

	bst.Print_InOrder();
	cout << endl;
	cout << endl;
	cout << bst.Search(43)->val  << endl;
	//f cout << BinarySearchTree::Presuccessor(bst.Search(10))->val <<" "<< BinarySearchTree::Successor(bst.Search(10))->val<<endl;
}