#include <iostream>
#include <print>
#include <vector>
#include <queue>




template<class T>
class GenericTree {

	struct TreeNode {
		T _val;
		std::vector<TreeNode*> _children{};
		TreeNode(T val):_val(val)
		{
	    }
	};

	TreeNode* _root;

	void print(TreeNode* root) const
	{
		if (root)
		{
			std::print("{} : ", root->_val);
			for (int i = 0; i < root->_children.size(); i++)
			{
				if (i != 0)
					std::print(", ");
				std::print("{}", root->_children[i]->_val);
			}
			std::println();

			for (int i = 0; i < root->_children.size(); ++i)
			{
				print(root->_children[i]);
			}
	    }
	}

	unsigned int numberOfNodes(TreeNode* root) const
	{
		if (!root) return 0;

		int total = 1;
		for (int i = 0; i < root->_children.size(); i++)
		{
			total += numberOfNodes(root->_children[i]);
		}
		return total;
	}

	unsigned int getHeight(TreeNode* root) const
	{

		int max = -1;
		for (int i = 0; i < root->_children.size(); ++i)
		{
			int childHeight = getHeight(root->_children[i]);
			if (childHeight > max)
			{
				max = childHeight;
			}
		}

		return 1 + max;
	}

public:
	GenericTree(T rootValue){
		_root = new TreeNode(rootValue);
	}

	void ConstructTree()
	{
	   std::queue<TreeNode*> nodes;
	   nodes.push(_root);

	   while (!nodes.empty())
	   {
		   TreeNode* cur = nodes.front();
		   nodes.pop();
		   std::println("How many children for {} node?", cur->_val);
		   int numChildren;
		   std::cin >> numChildren;
		   for (int i = 0; i < numChildren; ++i)
		   {
			   T value;
			   std::println("Enter value for child number {} : ", i+1);
			   std::cin >> value;
			   TreeNode* childNode = new TreeNode{ value };
			   nodes.push(childNode);
			   cur->_children.push_back(childNode);
		   }

	   }

	}


	void Print() const
	{
		print(_root);
	}

	//level wise print
	void LevelOrderPrint()const
	{
		std::queue<TreeNode*> nodes;
		nodes.push(_root);

		while (!nodes.empty())
		{
			TreeNode* cur = nodes.front();
			nodes.pop();
			std::print("{}", cur->_val);
			std::print(" : ");
			for (int i = 0; i < cur->_children.size(); ++i)
			{
				std::print("{} ", cur->_children[i]->_val);
				nodes.push(cur->_children[i]);
			}
			std::cout << std::endl;
		}
	}


	unsigned int NumberOfNodes() const
	{
		return numberOfNodes(_root);

	}

	unsigned int GetHeight() const
	{
		return getHeight(_root);
	}
};




int Genericmain()
{
	return 0;
	GenericTree<int> tree(10);
	tree.ConstructTree();
	tree.Print();
	std::cout << std::endl << std::endl;
	std::cout << "-------------------------" << std::endl;
	tree.LevelOrderPrint();
	std::cout << "Number of nodes are : " << tree.NumberOfNodes() << std::endl;
	std::cout << "height is  : " << tree.GetHeight() << std::endl;
}