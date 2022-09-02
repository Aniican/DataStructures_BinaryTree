#ifndef TREE_H
#define TREE_H

using namespace std;

template <class elemType>
struct nodeType
{
	elemType info;
	nodeType<elemType>* lLink;
	nodeType<elemType>* rLink;
};

template <class elemType>
class binaryTreeType
{
public:
	const binaryTreeType<elemType>& operator=(const binaryTreeType<elemType>& otherTree);
	bool isEmpty() const;
	void inorderTraversal() const;
	void preorderTraversal() const;
	void postorderTraversal() const;
	int treeHeight() const;
	int treeNodeCount() const;
	int treeLeavesCount() const;
	void destroyTree();
	virtual bool search(const elemType& searchItem) const = 0;
	virtual void insert(const elemType& insertItem) = 0;
	virtual void deleteNode(const elemType& deleteItem) = 0;
	binaryTreeType(const binaryTreeType<elemType>& otherTree);
	binaryTreeType();
	~binaryTreeType();
protected:
	nodeType<elemType>* root;
private:
	void copyTree(nodeType<elemType>*& copiedTreeRoot, nodeType<elemType>* otherTreeRoot);
	void destroy(nodeType<elemType>*& p);
	void inorder(nodeType<elemType>* p) const;
	void preorder(nodeType<elemType>* p) const;
	void postorder(nodeType<elemType>* p) const;
	int height(nodeType<elemType>* p) const;
	int max(int x, int y) const;
	int nodeCount(nodeType<elemType>* p) const;
	int leavesCount(nodeType<elemType>* p) const;

};

template <class elemType>
bool binaryTreeType<elemType>::isEmpty() const
{
	return (root == nullptr);
}

template <class elemType>
binaryTreeType<elemType>::binaryTreeType()
{
	root = nullptr;
}

template <class elemType>
void binaryTreeType<elemType>::inorderTraversal() const
{
	inorder(root);
}

template <class elemType>
void binaryTreeType<elemType>::preorderTraversal() const
{
	preorder(root);
}

template <class elemType>
void binaryTreeType<elemType>::postorderTraversal() const
{
	postorder(root);
}

template <class elemType>
int binaryTreeType<elemType>::treeHeight() const
{
	return height(root);
}

template <class elemType>
int binaryTreeType<elemType>::treeNodeCount() const
{
	return nodeCount(root);
}

template <class elemType>
int binaryTreeType<elemType>::treeLeavesCount() const
{
	return leavesCount(root);
}

template <class elemType>
void binaryTreeType<elemType>::inorder(nodeType<elemType> *p) const
{
	if (p != nullptr)
	{
		inorder(p->lLink);
		cout << p->info << " - ";
		inorder(p->rLink);
	}
}

template <class elemType>
void binaryTreeType<elemType>::preorder(nodeType<elemType>* p) const
{
	if (p != nullptr)
	{
		cout << p->info << " - ";
		preorder(p->lLink);
		preorder(p->rLink);
	}
}

template <class elemType>
void binaryTreeType<elemType>::postorder(nodeType<elemType>* p) const
{
	if (p != nullptr)
	{
		preorder(p->lLink);
		preorder(p->rLink);
		cout << p->info << " - ";	
	}
}

template <class elemType>
int binaryTreeType<elemType>::height(nodeType<elemType>* p) const
{
	if (p == nullptr)
		return 0;
	else
		return 1 + max(height(p->lLink), height(p->rLink));
}

template <class elemType>
int binaryTreeType<elemType>::max(int x, int y) const
{
	if (x >= y)
		return x;
	else
		return y;
}

template<class elemType>
int binaryTreeType<elemType>::leavesCount(nodeType<elemType>* p) const
{
	if (p == nullptr)
		return 0;

	if (p->lLink == nullptr && p->rLink == nullptr)
		return 1;

	else
		return leavesCount(p->lLink) + leavesCount(p->rLink);
}

template<class elemType>
int binaryTreeType<elemType>::nodeCount(nodeType<elemType>* p) const
{
	if (p == nullptr)
		return 0;

	else
		return 1 + nodeCount(p->lLink) + nodeCount(p->rLink);
}

template<class elemType>
void binaryTreeType<elemType>::copyTree(nodeType<elemType>*& copiedTreeRoot, nodeType<elemType>* otherTreeRoot)
{
	if (otherTreeRoot == nullptr)
		copiedTreeRoot = nullptr;
	else
	{
		copiedTreeRoot = new nodeType<elemType>;
		copiedTreeRoot->info = otherTreeRoot->info;
		copyTree(copiedTreeRoot->lLink, otherTreeRoot->lLink);
		copyTree(copiedTreeRoot->rLink, otherTreeRoot->rLink);
	}
}

template<class elemType>
void binaryTreeType<elemType>::destroy(nodeType<elemType>*& p)
{
	if (p != nullptr)
	{
		destroy(p->lLink);
		destroy(p->rLink);
		delete p;
		p = nullptr;
	}
}

template<class elemType>
void binaryTreeType<elemType>::destroyTree()
{
	destroy(root);
}

template<class elemType>
binaryTreeType<elemType>::~binaryTreeType()
{
	destroy(root);
}

template<class elemType>
binaryTreeType<elemType>::binaryTreeType(const binaryTreeType<elemType>& otherTree)
{
	if (otherTree == nullptr)
		root = nullptr;
	else
		copyTree(root, otherTree.root);
}

template<class elemType>
const binaryTreeType<elemType>& binaryTreeType<elemType>::operator=(const binaryTreeType<elemType>& otherTree)
{
	if (this != &otherTree)
	{
		if (root != nullptr)
			destroy(root);
		if (otherTree.root == nullptr)
			root = nullptr;
		else
			copyTree(root, otherTree.root);
	}

	return *this;
}
#endif 