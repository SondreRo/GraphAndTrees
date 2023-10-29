#pragma once
#include <vector>
class GeneralTreeNode
{
public:
	GeneralTreeNode(int inData);
	GeneralTreeNode(int inData, GeneralTreeNode* inParent);
	~GeneralTreeNode();

private:
	int Data;
	GeneralTreeNode* Parent;
	std::vector<GeneralTreeNode*> Children;

public:
	GeneralTreeNode* AddChild(GeneralTreeNode* inChild);
	GeneralTreeNode* AddChild(int inData);
	GeneralTreeNode* AddChildAtRandom(int inData);
	void DeleteChildren();

	GeneralTreeNode* GetParent();
	GeneralTreeNode* GetRoot();
	std::vector<GeneralTreeNode*> GetChildren();
	std::vector<GeneralTreeNode*> GetSiblings();
	std::vector<GeneralTreeNode*> GetAllNodesBelow();
	
	int GetData();
	int GetSize();
	int GetDepth();
	int GetMaxDepth();
	bool isEmpty();
	bool isRoot();
	bool isLeaf();

	void SetParent(GeneralTreeNode* newParent);
	void Delete();

	void StartDepthTraverse();
	void StartBreadthTraverse();
	
	void DepthTraverse(GeneralTreeNode* inNode);
	void BreadthTraverse(GeneralTreeNode* inNode);
	
	void PrintNode();
};
