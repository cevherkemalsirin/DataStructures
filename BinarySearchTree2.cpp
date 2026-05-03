#include <iostream>
#include <stack>
#include <queue>


using namespace std;

struct BSnode {
	BSnode* _left;
	int val;
	BSnode* _right;

	BSnode(int val) :val(val), _left(nullptr), _right(nullptr) {}
	~BSnode()
	{
		if (_left) delete _left;
		if (_right) delete _right;
		_left = _right = nullptr;
	}
};


class BSTree {

	void printInOrder(BSnode* root)const
	{
		if (!root) return;

		printInOrder(root->_left);
		cout << root->val << " ";
		printInOrder(root->_right);
	}

	bool isLeafNode(BSnode* node) const
	{
		return !node->_left && !node->_right;
	}

	int height(BSnode* node) const
	{
		if (!node) return -1;

		return max(height(node->_left), height(node->_right)) + 1;
	}

	BSnode* _root{};
public:
	BSTree() = default;
	BSTree(int val): _root(new BSnode(val)){}

	inline  const BSnode const * GetRoot() const { return _root; }

	void Insert(int val)
	{
		BSnode* newNode = new BSnode(val);
		if (!_root)
		{
			_root = newNode;
		}
		else
		{
			BSnode* cur = _root;
			BSnode* prevParent = nullptr;
			while (cur)
			{
				if (cur->val == newNode->val) return;

				if (newNode->val > cur->val)
				{
					prevParent = cur;
					cur = cur->_right;
				}
				else
				{
					prevParent = cur;
					cur = cur->_left;
				}
			}
			if (prevParent->val < newNode->val) prevParent->_right = newNode;
			else prevParent->_left = newNode;
		}
	}

	BSnode* SearchTree(int val) const
	{
		if (!_root) return nullptr;

		BSnode* cur = _root;
		while (cur)
		{
			if (val == cur->val) return cur;

			else if (val < cur->val)
			{
				cur = cur->_left;
			}
			else
			{
				cur = cur->_right;
			}
		}

		return nullptr;

	}

	int MinValue()const
	{
		if (!_root) return INT_MAX;

		BSnode* cur = _root;
		while (cur->_left)
		{
			cur = cur->_left;
		}
		return cur->val;
	}
	int MaxValue()const
	{
		if (!_root) return INT_MIN;

		BSnode* cur = _root;
		while (cur->_right)
		{
			cur = cur->_right;
		}
		return cur->val;
	}

	void PrintInOrder()const
	{
		printInOrder(_root);
		cout << endl;
	}

	int RangeSum(int rmin, int rmax)
	{
		if (!_root) return 0;
		
		stack<BSnode*> s;

		s.push(_root);
		int total = 0;

		while (!s.empty())
		{
			BSnode* cur = s.top(); s.pop();
			while (cur)
			{
				if (cur->val > rmax)
				{
					cur = cur->_left;
				}
				else if (cur->val < rmin)
				{
					cur = cur->_right;
				}
				else
				{
					total += cur->val;
					s.push(cur->_left);
					s.push(cur->_right);
					break;
				}

		    }

		}
		return total;

	}

	BSnode* PreSuccessor(BSnode* root) const
	{
		if (!root) return nullptr;

		BSnode* cur = root->_left;
	    
		while (cur && cur->_right)
		{
			cur = cur->_right;
		}

		return cur;
	}

	BSnode* Successor(BSnode* root) const
	{
		if (!root) return nullptr;

		BSnode* cur = root->_right;
		while (cur && cur->_left)
		{
			cur = cur->_left;
		}
		return cur;

	}

	int Height()const
	{
		if (!_root) return -1;
	    
		queue<BSnode*> q;
		q.push(_root);
		int height = 0;
		while (!q.empty())
		{
			int size = q.size();

			for (int i = 0; i < size; ++i)
			{
				BSnode* cur = q.front(); q.pop();
				if (cur->_left) q.push(cur->_left);
				if (cur->_right) q.push(cur->_right);

			}
			if(!q.empty())
				height++;
		}

		return height;
		
	}

	BSnode* GetParent(int val) const
	{
		if (!_root) return nullptr;

		BSnode* cur = _root;
		BSnode* parent = cur;
		while (cur)
		{
			if (cur->val < val)
			{
				parent = cur;
				cur = cur->_right;
			}
			else if(cur->val > val)
			{
				parent = cur;
				cur = cur->_left;
			}
			else
			{
				return parent;
			}
		}
		return nullptr;

	}

	void Delete(int val)
	{
		BSnode* node = this->SearchTree(val);

		if (!node) return;
		if (this->isLeafNode(node))
		{
			BSnode* parent = GetParent(val);
			delete node;
			if (parent->val > val)
			{
				parent->_left = nullptr;
			}
			else
			{
				parent->_right = nullptr;
			}
		}
		else
		{
			while (!isLeafNode(node))
			{
				BSnode* prev = node;
				if (this->height(node->_left) > this->height(node->_right))
				{
					node = this->PreSuccessor(node);
					prev->val = node->val;
				}
				else
				{
					node = this->Successor(node);
					prev->val = node->val;
				}
			}
			BSnode* parent = GetParent(node->val);
			delete node;
			if (parent->val > val)
			{
				parent->_left = nullptr;
			}
			else
			{
				parent->_right = nullptr;
			}
		}

	}

	~BSTree()
	{
		if (_root) delete _root;
		_root = nullptr;
	}

};




int main111()
{
	return 0;
	BSTree tree;
	tree.Insert(10);
	tree.Insert(8);
	tree.Insert(14);
	tree.Insert(4);
	tree.Insert(9);
	tree.Insert(13);
	tree.Insert(15);
	tree.Insert(12);
	tree.Insert(2);
	tree.Insert(5);


	cout << "current tree has: " << endl;;
	cout << "height is " << tree.Height() << endl;
	cout << "succesor is " << tree.Successor(tree.SearchTree(10))->val << endl;
	cout << "presuccesor is " << tree.PreSuccessor(tree.SearchTree(10))->val << endl;
	cout << endl;

	while (true)
	{

		cout << "1) Enter 1 to insert, \n2) Enter 2 to print \n3) Enter 3 to search \n4) Enter 4 to range sum\n5) Enter 5 to Delete \n6) anything else to exit" << endl;
		int choice;
		cin >> choice;
		switch (choice)
		{
		case 1:
		{
			cout << "Enter  Number: " << endl;
			int num; cin >> num;
			tree.Insert(num);
		}break;
		case 2:
		{
			tree.PrintInOrder();
			cout << "Max value is " << tree.MaxValue() << " , Min value is " << tree.MinValue() << endl;
		}break;
		case 3:
		{
			cout << "Enter  Number to search : " << endl;
			int num; cin >> num;
			if (!tree.SearchTree(num)) std::cout << "Not in it " << endl;
			else
			std::cout << tree.SearchTree(num)->val << endl;
		}break;

		case 4:	
		{
			cout << "Enter  min Range and Max Range: " << endl;
			int minr; int maxr;
			cin >> minr >> maxr;
			cout << "total is " << tree.RangeSum(minr,maxr) << endl;
		}
		break;
		case 5: {
			cout << "Enter  Number to delete : " << endl;
			int num; cin >> num;
			tree.Delete(num);
		}
		 break;
		default:
			break;
		}
	}
}