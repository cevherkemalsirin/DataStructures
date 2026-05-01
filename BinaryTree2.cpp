#include <print>
#include <iostream>
#include <string>
#include <queue>
#include <stack>


struct BTnode {
	BTnode* _left{};
	BTnode* _right{};
	int _val;
	BTnode(int val) : _val(val) {}
	~BTnode()
	{
		if (_left) delete _left;
		if (_right) delete _right;
		_left = _right = nullptr;
	}
};


class BTree {

	void print(BTnode* root) const
	{
		if (root)
		{
			std::print("{} : ", root->_val);
			if (root->_left) std::print("{} : ", root->_left->_val);
			if (root->_right) std::print("{} : ", root->_right->_val);
			std::println();
			print(root->_left);
			print(root->_right);
	    }
	}

	unsigned int getNumberOfNodes(BTnode* root)const
	{
		if (root == nullptr)
			return 0;

		unsigned int total = 1;
		total += getNumberOfNodes(root->_left);
		total += getNumberOfNodes(root->_right);
		return total;
	}

	void printInOrder(BTnode* root) const
	{
		if (!root) return;
		printInOrder(root->_left);
		std::print("{},", root->_val);
		printInOrder(root->_right);
	}

	void printPreOrder(BTnode* root) const
	{
		if (!root) return;
		std::print("{},", root->_val);
		printPreOrder(root->_left);
		printPreOrder(root->_right);
	}

	void printPostOrder(BTnode* root) const
	{
		if (!root) return;
		printPostOrder(root->_left);
		printPostOrder(root->_right);
		std::print("{},", root->_val);
	}

	bool isSymmetricRec(BTnode* left, BTnode* right) const
	{
		if (left != nullptr && right == nullptr) return false;
		if (left == nullptr && right != nullptr) return false;
		if (left == right) return true;
		if (left->_val != right->_val) return false;

	
		
		return isSymmetricRec(left->_left, right->_right) && isSymmetricRec(left->_right, right->_left);

	}
	
	unsigned int heightRes(BTnode* root) const
	{
		if (!root) return -1;

		return std::max(heightRes(root->_left), heightRes(root->_right)) + 1;

	}

	BTnode* _root;
	
public:

	BTree(int val) : _root(new BTnode(val)) {

	}

	void Construct()
	{
		if (_root)
		{
			std::queue<BTnode*> q;
			q.push(_root);

			while (!q.empty())
			{
				BTnode* current = q.front();
				q.pop();
				std::println("Enter left child of {} ", current->_val);
				int lvalue;
				std::cin >> lvalue;
				if (lvalue != 0)
				{
					BTnode* left = new BTnode(lvalue);
					q.push(left);
					current->_left = left;
				}
				std::println("Enter right child of {} ", current->_val);
				int rvalue;
				std::cin >> rvalue;
				if (rvalue != 0)
				{
					BTnode* right = new BTnode(rvalue);
					q.push(right);
					current->_right = right;
				}

			}
		}
	}


	void LevelOrderPrint() const
	{

		if (_root)
		{
			std::queue<BTnode*> q;
			q.push(_root);
			while (!q.empty())
			{
				BTnode* cur = q.front();
				q.pop();
				std::print("{}: ",cur->_val);
				if (cur->_left)
				{
					std::print("{} ", cur->_left->_val);
					q.push(cur->_left);
				}

				if (cur->_right)
				{
					std::print("{} ", cur->_right->_val);
					q.push(cur->_right);
				}
				std::println();
			}
		}

	}

	unsigned int GetNumberOfNodes() const
	{
		return getNumberOfNodes(_root);
	}

	unsigned int GetNumberOfNodes2() const
	{
		unsigned int count = 0;
		std::stack<BTnode*> s;
		s.push(_root);
		while (!s.empty())
		{
			BTnode* cur = s.top(); s.pop();
			count++;
			if (cur->_left) s.push(cur->_left);
			if (cur->_right) s.push(cur->_right);

		}
		return count;
	}

	void Print()const
	{
		print(_root);
	}

	void PrintInOrder() const
	{
		printInOrder(_root);
	}

	void PrintPreOrder() const
	{
		printPreOrder(_root);
	}

	void PrintPostOrder() const
	{
		printPostOrder(_root);
	}

	bool IsSymmetric() const
	{

		if (_root)
		{
			std::queue<BTnode*> q;
			q.push(_root->_left);
			q.push(_root->_right);

			while (!q.empty())
			{
				BTnode* left = q.front(); q.pop();
				BTnode* right = q.front(); q.pop();

				if (!left && !right) continue;
				if (!left || !right) return false;
				if (left->_val != right->_val) return false;

				q.push(left->_left); q.push(right->_right);
				q.push(left->_right); q.push(right->_left);
		    }
			return true;

		}
		else
		{
			return true;
		}
	}

	bool IsSymmetricRec() const
	{
		if (_root)
		{
			return isSymmetricRec(_root->_left,_root->_right);
		}
		return true;
		
	}

	unsigned int Height()const
	{
		if (_root)
		{
			int height = 0;
			std::queue<BTnode*> q;
			q.push(_root); q.push(nullptr);
			while (!q.empty())
			{
				BTnode* cur = q.front(); q.pop();
				if (cur == nullptr)
				{
					if (q.empty())break;
					else
					{
						q.push(nullptr);
						height++;
					}
				}
				else
				{
					if(cur->_left)q.push(cur->_left);
					if (cur->_right)q.push(cur->_right);
				}
			}
			
			return height;
		}
		return 0;
	}

	unsigned int HeightRes()const
	{
		return heightRes(_root);
	}

	bool Find(int val)const 
	{
		if (_root)
		{
			std::queue<BTnode*> q;
			q.push(_root);
			while (!q.empty())
			{
				BTnode* cur = q.front(); q.pop();

				if (cur->_val == val) return true;
				else
				{
					if (cur->_left)q.push(cur->_left);
					if (cur->_right)q.push(cur->_right);
				}
			}
			return false;
		}
		else
		{
			return false;
		}
		
	}

	int Min()const
	{
		int min = INT_MAX;
		if (_root)
		{
			std::queue<BTnode*> q;
			q.push(_root);
			while (!q.empty())
			{
				BTnode* cur = q.front(); q.pop();

				if (cur->_val < min) min = cur->_val;
				if (cur->_left)q.push(cur->_left);
				if (cur->_right)q.push(cur->_right);

			}
			
		}
		return min;
	}

	int Max()const
	{
		int max = INT_MIN;

		if (!_root) return max;
	    
		std::queue<BTnode*> q;
		q.push(_root);
		while (!q.empty())
		{
			BTnode* cur = q.front(); q.pop();
			
			if (cur->_val > max) max = cur->_val;
			if (cur->_left)q.push(cur->_left);
			if (cur->_right)q.push(cur->_right);
		}
		return max;
	}

	int NumberOfLeaveNodes()const
	{
		if (_root)
		{
			int count = 0;
			std::queue<BTnode*> q;
			q.push(_root);
			while (!q.empty())
			{
				BTnode* cur = q.front(); q.pop();
				if (!cur->_left && !cur->_right) {
					++count;
				} 
				else 
				{
					if (cur->_left)q.push(cur->_left);
					if (cur->_right)q.push(cur->_right);
				}

			}
			return count;
		}
		else
		{
			return -1;
		}
	}
	~BTree()
	{
		if (_root)
		{
			delete _root;
			_root = nullptr;
		}
	}
	

};



int BinaryTreemain()
{
	return 0;
	BTree tree(10);
	tree.Construct();
	tree.Print();
	std::cout << std::endl << std::endl;
	tree.LevelOrderPrint();
	std::println();
	std::cout<<"Number of Nodes: " << tree.GetNumberOfNodes()<<std::endl;
	std::cout << "Number of Nodes no recursive way : " << tree.GetNumberOfNodes2()<<std::endl;
	tree.PrintInOrder();
	std::cout << std::endl;
	tree.PrintPreOrder();
	std::cout << std::endl;
	tree.PrintPostOrder();
	std::cout << std::endl;
	//std::cout << "Tree is symmatric recursion : " << tree.IsSymmetricRec() << std::endl;
	std::cout << "Tree is symmatric queue solution : " << tree.IsSymmetric() << std::endl;
	std::cout << "Tree height recursion is : " << tree.HeightRes() << std::endl;
	std::cout << "Tree height is : " << tree.Height() << std::endl;
	std::cout << "Tree min value is : " << tree.Min() << std::endl;
	std::cout << "Tree max value is : " << tree.Max() << std::endl;
	std::cout << "Tree leaf nodes number is : " << tree.NumberOfLeaveNodes() << std::endl;
}