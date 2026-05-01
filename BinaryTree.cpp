#include <iostream>
#include <vector>

using namespace std;

class BinaryTree {
	struct  Node
	{
		int data{};
		Node* left{};
		Node* right{};

		Node(int data) :data(data) {}
	};
	
	void print(Node* current)
	{
		if (!current) return;

		print(current->left);
		cout << current->data << " ";
		print(current->right);

	}

	
public:
	Node* root;
	BinaryTree(int rootValue) :root(new Node(rootValue)) {}

	void print_inorder()
	{
		print(root);
	}
	//takes direction like LLR , RRL etc.
	void add(const vector<int>& values, const vector<char>& direction)
	{
		Node* current = root;
		//assert both vector has same size
		for (int i = 0; i < values.size(); i++)
		{
			if (direction[i] == 'L' || direction[i] == 'l')
			{
				if (!current->left)
				{
					current->left = new Node(values[i]);
			    }
				else
				{
					if (current->left->data != values[i])
					{
						current->left->data = values[i];
					}
				}
				current = current->left;
			}
			else
			{
				if (!current->right)
				{
					current->right = new Node(values[i]);
				}
				else
				{
					if (current->right->data != values[i])
					{
						current->right->data = values[i];
					}
				}
				current = current->right;
			}
		}


	}

	int GetMax(Node* root)
	{
		if (!root)
			return INT_MIN;

		int max = root->data;
		int lmax = GetMax(root->left);
		int rmax = GetMax(root->right);

		if (lmax > max) max = lmax;
		if (rmax > max) max = rmax;
		return max;
	}

	int GetHeight(Node* root)
	{

		int res = 0;

		if (root->left)
			res = GetHeight(root->left);
		if (root->right)
			res = max(res, GetHeight(root->right)) + 1;

		return res;
	}

	int total(Node* root)
	{
		if (!root)
		{
			return 0;
		}

		return total(root->left) + total(root->right) + 1;

	}

	int total_leaf(Node* root)
	{
		if (!root)
		{
			return 0;
		}
		if (!root->left && !root->right)
		{
			return 1;
		}

		return total_leaf(root->left) + total_leaf(root->right);
	}

	bool is_exist(int value, Node* root)
	{

		if (!root)
		{
			return false;
		}

		if (root->data == value) return true;

		return (is_exist(value, root->left) || is_exist(value, root->right));
	}

	bool isPerfect()
	{
		int height = GetHeight(root);
		int numNodes = total(root);

		if (pow(2, height + 1) - 1 == numNodes)
		{
			return true;
		}
		else
		{
			return false;
		}

	}
};






/*
void clear(Node* node)
{
	if (!node) return;
	clear(node->left);
	clear(node->right);
	delete node;
	node = nullptr;
}
*/
int main3()
{
	return 0;
	/*
	Node* root = new Node(1);
	Node* node2 = new Node(2);
	Node* node3 = new Node(3);
	Node* node4 = new Node(4);
	Node* node5 = new Node(5);
	Node* node6 = new Node(6);
	Node* node7 = new Node(7);
	Node* node8 = new Node(8);

	// Link them!
	root->left = node2;
	root->right = node3;

	node2->left = node4;
	node2->right = node5;

	node5->right = node7;

	node3->right = node6;
	node6->left = node8;

	print(root);
	*/

	BinaryTree tree(1);
	tree.add({ 2, 4, 7 }, { 'L', 'L', 'L' });
	tree.add({ 2, 4, 8 }, { 'L', 'L', 'R' });
	tree.add({ 2, 5, 9 }, { 'L', 'R', 'R' });
	tree.add({ 3, 6, 10 }, { 'R', 'R', 'L' });

	tree.print_inorder();
	cout << '\n'<< tree.GetMax(tree.root);
	cout << '\n' << tree.GetHeight(tree.root);
	cout << '\n' << tree.total(tree.root);
	cout << '\n' << tree.total_leaf(tree.root);
	cout << '\n' << tree.is_exist(9,tree.root);
	cout << '\n' << tree.isPerfect();
	//cout << '\n' << tree.total(tree.root);

	
}