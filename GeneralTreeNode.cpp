#include "GeneralTreeNode.h"
#include <iostream>
#include <list>
#include <vector>
#include <queue>

GeneralTreeNode::GeneralTreeNode(int inData)
{
	Parent = nullptr;
	Data = inData;
}

GeneralTreeNode::GeneralTreeNode(int inData, GeneralTreeNode* inParent)
{
	Parent = inParent;
	Data = inData;
	inParent->AddChild(this);
}

GeneralTreeNode::~GeneralTreeNode()
{
	DeleteChildren();
}

GeneralTreeNode* GeneralTreeNode::AddChild(GeneralTreeNode* inChild)
{
	Children.push_back(inChild);
	return inChild;
}

GeneralTreeNode* GeneralTreeNode::AddChild(int inData)
{
	GeneralTreeNode* NewChild = new GeneralTreeNode(inData,this);
	return NewChild;
}

GeneralTreeNode* GeneralTreeNode::AddChildAtRandom(int inData)
{
	srand(time(NULL));
	std::vector<GeneralTreeNode*> AllNodes = GetRoot()->GetAllNodesBelow();
	int randomIndex = rand() % AllNodes.size();
	std::cout << "Inserting at: " <<AllNodes[randomIndex]->GetData() << std::endl;
	return AllNodes[randomIndex]->AddChild(inData);
}

std::vector<GeneralTreeNode*> GeneralTreeNode::GetChildren()
{
	return Children;
}

std::vector<GeneralTreeNode*> GeneralTreeNode::GetSiblings()
{
	if (isRoot())
	{
		return std::vector<GeneralTreeNode*>();
	}
	return GetParent()->GetChildren();
}

std::vector<GeneralTreeNode*> GeneralTreeNode::GetAllNodesBelow()
{
	std::vector<GeneralTreeNode*> tempVector;
	tempVector.push_back(this);
	if (isLeaf())
	{
		return tempVector;
	}
	for (int i{}; i < GetChildren().size(); i++)
	{
		std::vector<GeneralTreeNode*> allchildren = GetChildren()[i]->GetAllNodesBelow();
		for (int y{}; y < allchildren.size(); y++)
		{
			tempVector.push_back(allchildren[y]);
		}
	}
	return tempVector;
}

GeneralTreeNode* GeneralTreeNode::GetParent()
{
	return Parent;
}

GeneralTreeNode* GeneralTreeNode::GetRoot()
{
	if (isRoot())
	{
		return this;
	}

	return GetParent()->GetRoot();
	
}

int GeneralTreeNode::GetData()
{
	return Data;
}

int GeneralTreeNode::GetSize()
{
	// int currentSizeCount = 0;
	// currentSizeCount += GetChildren().size();
	// for (size_t i{}; i < GetChildren().size(); i++)
	// {
	// 	currentSizeCount += GetChildren()[i]->GetSize();
	// }
	// 	
	// return currentSizeCount;
	return GetAllNodesBelow().size();
}

int GeneralTreeNode::GetDepth()
{
	int depth = 1;
	if (isRoot())
	{
		return 0;
	}
	depth += GetParent()->GetDepth();
	return depth;
}

int GeneralTreeNode::GetMaxDepth()
{
	std::vector<GeneralTreeNode*> AllNodes = GetAllNodesBelow();
	int MaxDepth = 0;
	for (int i{}; i < AllNodes.size(); i++)
	{
		if (AllNodes[i]->GetDepth() > MaxDepth)
		{
			MaxDepth = AllNodes[i]->GetDepth();
		}
	}
	return MaxDepth;
}

bool GeneralTreeNode::isEmpty()
{
	return false;
}

bool GeneralTreeNode::isRoot()
{
	return (Parent == nullptr) ? true : false;
}

bool GeneralTreeNode::isLeaf()
{
	return (Children.empty()) ? true : false;
}

void GeneralTreeNode::SetParent(GeneralTreeNode* newParent)
{
	Parent = newParent; 
}

void GeneralTreeNode::Delete()
{
	if (!isRoot())
	{
		std::vector<GeneralTreeNode*> ParentChildren = Parent->GetChildren();
		for (size_t i{}; i < ParentChildren.size(); i++)
		{
			if (ParentChildren[i] == this)
			{
				ParentChildren.erase(ParentChildren.begin() + i);
				break;
			}
		}
	}
	delete this;
}

void GeneralTreeNode::StartDepthTraverse()
{
	DepthTraverse(this);
}

void GeneralTreeNode::StartBreadthTraverse()
{
	BreadthTraverse(this);
}

void GeneralTreeNode::DepthTraverse(GeneralTreeNode* inNode)
{
	
	inNode->PrintNode();
	if (inNode->isLeaf())
	{
		return;
	}
	
	for (int i{}; i < inNode->GetChildren().size(); i++)
	{
		DepthTraverse(inNode->GetChildren()[i]);
	}
}

void GeneralTreeNode::BreadthTraverse(GeneralTreeNode* inNode)
{
	//std::cout << "BreadthTraverse Data: " << inNode->GetData() << std::endl;
	inNode->PrintNode();
	static std::queue<GeneralTreeNode*> BreadthQueue;

	for (int i{}; i < inNode->GetChildren().size(); i++)
	{
		BreadthQueue.push(inNode->GetChildren()[i]);	
	}
	while (!BreadthQueue.empty())
	{
		GeneralTreeNode* CurrentNode = BreadthQueue.front();
		BreadthQueue.pop();
		CurrentNode->PrintNode();
		if(!CurrentNode->isLeaf())
		{
			for(int i{}; i < CurrentNode->GetChildren().size(); i++)
			{
				BreadthQueue.push(CurrentNode->GetChildren()[i]);
			}
		}
	}
}

void GeneralTreeNode::DeleteChildren()
{
	if (Children.empty())
	{
		return;
	}
	const uint64_t AmountOfChildren = Children.size();
	for (uint64_t i{}; i < AmountOfChildren; i++)
	{
		Children[i]->Delete();
	}
	Children.clear();
}

void GeneralTreeNode::PrintNode()
{
	std::cout << "NodeDepth: " << GetDepth() << "   AmountOfChildren: " << GetChildren().size() << "   IsLeaf: " << isLeaf() << "   IsRoot: " << isRoot() << "   NodeData: " << Data << std::endl;
}