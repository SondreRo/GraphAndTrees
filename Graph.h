#pragma once
#include <string>
#include <vector>


class Node
{
	
public:

	
	Node(std::string inName, float inData)
	{
		Name = inName;
		Data = inData;
	}
	std::string Name;
	float Data;
	std::vector<Node*> ListOfAdjacentNodes;
	//std::vector<Node*> GetAdjacentNodes();
	
	std::vector<class Edge*> ListOfConnectedEdges;

	bool isVisited = false;
	
	void Destroy()
	{
		ListOfConnectedEdges.clear();
		delete this;
	}
};


class Edge
{
public:
	Edge(float inCost, Node* inNode1, Node* inNode2)
	{
		Cost = inCost;
		Node1 = inNode1;
		Node2 = inNode2;
	}

	Node* Node1;
	Node* Node2;
	float Cost;

	void Destroy()
	{
		for (int i{}; i < Node1->ListOfConnectedEdges.size(); i++)
		{
			if (Node1->ListOfConnectedEdges[i] == this)
			{
				//DeleteYourself from this list
				Node1->ListOfConnectedEdges.erase(Node1->ListOfConnectedEdges.begin()+i);
				return;
			}
		}

		for (int i{}; i < Node1->ListOfAdjacentNodes.size(); i++)
		{
			if (Node1->ListOfAdjacentNodes[i] == Node2)
			{
				//Delete Node from AdjacentNodes
				Node1->ListOfAdjacentNodes.erase(Node1->ListOfAdjacentNodes.begin()+i);
				return;
			}
		}
		
		for (int y{}; y < Node2->ListOfConnectedEdges.size(); y++)
		{
			if (Node2->ListOfConnectedEdges[y] == this)
			{
				//DeleteYourself from this list
				Node1->ListOfConnectedEdges.erase(Node2->ListOfConnectedEdges.begin()+y);
				return;
			}
		}

		for (int i{}; i < Node2->ListOfAdjacentNodes.size(); i++)
		{
			if (Node1->ListOfAdjacentNodes[i] == Node1)
			{
				//Delete Node from AdjacentNodes
				Node2->ListOfAdjacentNodes.erase(Node2->ListOfAdjacentNodes.begin()+i);
				return;
			}
		}
		delete this;
	}
	
};


class Graph
{
public:
	Graph();
	~Graph();
	
	std::vector<Node*> ListOfNodes;
	
	Node* InsertNode(std::string inName, float inData);
	Edge* InsertEdge(Node* inNode1, Node* inNode2, float inCost);
	Edge* InsertEdge(std::string inNode1, std::string inNode2, float inCost);
	Edge* GetEdgeBetween(Node* inNode1, Node* inNode2);
	Edge* GetEdgeBetween(std::string inNode1s, std::string inNode2s);
	int GetDegree(Node* inNode);
	int GetDegree(std::string inNodeS);
	std::vector<Node*> GetAdjacent(Node* inNode);
	Node** EndNodes(Edge* inEdge);
	Node* Opposite(Node* inNode, Edge* inEdge);
	bool AreAdjacent(Node* inNode1, Node* inNode2);
	void ReplaceNode(Node* inNode, float inData);
	void ReplaceEdge(Edge* inEdge, float inCost);
	void DeleteNode(Node* inNode);
	void DeleteEdge(Edge* inEdge);
	std::vector<Edge*> IncidentEdges(Node* inNode);
	std::vector<Node*> Nodes();
	std::vector<Edge*> Edges();
	
	Node* FindNodeFromName(std::string inName);
	
	void TraverseGraph(Node* StartNode);
	
	void TraverseGraphStart(Node* StartNode);
	void TraverseGraphStart(std::string StartNodeS);

	Node* InsertRandomNode(std::string inName, float inData, int maxCost);
};
