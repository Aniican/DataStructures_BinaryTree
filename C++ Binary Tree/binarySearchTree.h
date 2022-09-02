#ifndef SEARCH_H
#define SEARCH_H

#include "binaryTree.h"

template <class elemType>
class bSearchTreeType : public binaryTreeType<elemType>
{
public:
	bool search(const elemType& searchItem) const;
	void insert(const elemType& insertItem);
	void deleteNode(const elemType& deleteItem);
private:
	void deleteFromTree(nodeType<elemType>*& p);
	bool search(const elemType& searchItem, nodeType<elemType>* p, int numTraveled) const;
	void insert(nodeType<elemType>*& insertItem, nodeType<elemType>* &p);
};

template <class elemType>
bool bSearchTreeType<elemType>::search(const elemType& searchItem) const
{
	return search(searchItem, this->root, 0);
}

template <class elemType>
bool bSearchTreeType<elemType>::search(const elemType& searchItem, nodeType<elemType>* p, int numTraveled) const // Added a way for the nodes traversed to be displayed in function. This seemed like the easiest way.
{
	if (p == nullptr)
	{
		cout << "Your traversed " << numTraveled << " different nodes!" << endl;
		return false;
	}
	else if (p->info == searchItem)
	{
		cout << "Your traversed " << numTraveled << " different nodes!" << endl;
		return true;
	}
	else if (p->info > searchItem)
	{
		numTraveled++;
		return search(searchItem, p->lLink, numTraveled);
	}
	else
	{
		numTraveled++;
		return search(searchItem, p->rLink, numTraveled);
	}
}

template <class elemType>
void bSearchTreeType<elemType>::insert(const elemType& insertItem)
{
	nodeType<elemType>* newNode;
	newNode = new nodeType<elemType>;
	newNode->info = insertItem;
	newNode->lLink = nullptr;
	newNode->rLink = nullptr;
	insert(newNode, this->root);
}

template <class elemType>
void bSearchTreeType<elemType>::insert(nodeType<elemType>*& insertItem, nodeType<elemType>* &p)
{
	if (p == nullptr)
		p = insertItem;
	else if (p->info == insertItem->info)
	{
		cout << "The item to be inserted is already in the tree -- duplicates are not allowed." << endl;
		return;
	}
	else if (p->info == insertItem->info)
		insert(insertItem, p->lLink);
	else
		insert(insertItem, p->rLink);
}

template <class elemType>
void bSearchTreeType<elemType>::deleteFromTree(nodeType<elemType>*& p)
{
	nodeType<elemType>* current;
	nodeType<elemType>* trailCurrent;
	nodeType<elemType>* temp;

	if (p == nullptr)
		cout << "Error: The node to be deleted does not exist." << endl;
	else if (p->lLink == nullptr && p->rLink == nullptr)
	{
		temp = p;
		p = nullptr;
		delete temp;
	}
	else if (p->lLink == nullptr)
	{
		temp = p;
		p = temp->rLink;
		delete temp;
	}
	else if (p->rLink == nullptr)
	{
		temp = p;
		p = temp->lLink;
		delete temp;
	}
	else
	{
		current = p->lLink;
		trailCurrent = nullptr;
		while (current->rLink != nullptr)
		{
			trailCurrent = current;
			current = current->rLink;
		}
		p->info = current->info;
		if (trailCurrent == nullptr)
			p->lLink = current->lLink;
		else
			trailCurrent->rLink = current->lLink;

		delete current;
	}
}

template <class elemType>
void bSearchTreeType<elemType>::deleteNode(const elemType& deleteItem)
{
	nodeType<elemType>* current;
	nodeType<elemType>* trailCurrent;
	bool found = false;

	if (this->root == nullptr)
		cout << "cannot delete from an empty tree." << endl;
	else
	{
		current = this->root;
		trailCurrent = this->root;
		while (current != nullptr && !found)
		{
			if (current->info == deleteItem)
				found = true;
			else
			{
				trailCurrent = current;
				if (current->info > deleteItem)
					current = current->lLink;
				else
					current = current->rLink;
			}
		}

		if (current == nullptr)
			cout << "The item to be deleted is not in the tree." << endl;
		else if (found)
		{
			if (current == this->root)
				deleteFromTree(this->root);
			else if (trailCurrent->info > deleteItem)
				deleteFromTree(trailCurrent->lLink);
			else
				deleteFromTree(trailCurrent->rLink);
		}
		else
			cout << "The item to be deleted is not in the tree." << endl;
	}
}

#endif