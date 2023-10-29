#include "Graph.h"
#include "iostream"

Graph::Graph()
{
}

Graph::~Graph()
{
	for (int i{}; i < ListOfNodes.size(); i++)
	{
		ListOfNodes[i]->Destroy();
	}
}

Node* Graph::InsertNode(std::string inName, float inData)
{
	Node *NewNode = new Node(inName, inData);
	ListOfNodes.push_back(NewNode);
	return NewNode;
}

Edge* Graph::InsertEdge(Node* inNode1, Node* inNode2, float inCost)
{
	Edge *NewEdge = new Edge(inCost, inNode1, inNode2);

	inNode1->ListOfConnectedEdges.push_back(NewEdge);
	inNode1->ListOfAdjacentNodes.push_back(inNode2);

	inNode2->ListOfConnectedEdges.push_back(NewEdge);
	inNode2->ListOfAdjacentNodes.push_back(inNode1);
	
	return NewEdge;
}

Edge* Graph::InsertEdge(std::string inNodeS1, std::string inNodeS2, float inCost)
{
	Node* inNode1 = FindNodeFromName(inNodeS1); 
	Node* inNode2 = FindNodeFromName(inNodeS2);
	
	Edge *NewEdge = new Edge(inCost, inNode1, inNode2);


	inNode1->ListOfConnectedEdges.push_back(NewEdge);
	inNode1->ListOfAdjacentNodes.push_back(inNode2);

	inNode2->ListOfConnectedEdges.push_back(NewEdge);
	inNode2->ListOfAdjacentNodes.push_back(inNode1);
	
	return NewEdge;
}

Edge* Graph::GetEdgeBetween(Node* inNode1, Node* inNode2)
{
	std::vector<Edge*> ConnectedEdges1 = inNode1->ListOfConnectedEdges;
	for (int i{}; i < ConnectedEdges1.size(); i++)
	{
		if (Opposite(inNode1, ConnectedEdges1[i]) == inNode2)
		{
			return ConnectedEdges1[i];
		}
	}
	std::cout << "No edge found between" << std::endl;
	return nullptr;
}

Edge* Graph::GetEdgeBetween(std::string inNode1s, std::string inNode2s)
{
	Node* inNode1 = FindNodeFromName(inNode1s);
	Node* inNode2 = FindNodeFromName(inNode2s);
	return GetEdgeBetween(inNode1, inNode2);
}

int Graph::GetDegree(Node* inNode)
{
	return inNode->ListOfConnectedEdges.size();
}

int Graph::GetDegree(std::string inNodeS)
{
	return GetDegree(FindNodeFromName(inNodeS));
}

std::vector<Node*> Graph::GetAdjacent(Node* inNode)
{
	return inNode->ListOfAdjacentNodes;
}

Node** Graph::EndNodes(Edge* inEdge)
{
	Node* ListOfEndNodes[2]; 
	ListOfEndNodes[0] = inEdge->Node1;
	ListOfEndNodes[1] = inEdge->Node2;
	return ListOfEndNodes;
}

Node* Graph::Opposite(Node* inNode, Edge* inEdge)
{
	if(inEdge->Node1 == inNode)
	{
		return inEdge->Node2;
	}
	else if(inEdge->Node2 == inNode)
	{
		return inEdge->Node1;
	}
	return nullptr;
}

bool Graph::AreAdjacent(Node* inNode1, Node* inNode2)
{
	std::vector<Edge*> Node1Edges = inNode1->ListOfConnectedEdges;
	std::vector<Edge*> Node2Edges = inNode2->ListOfConnectedEdges;
	bool isConnected = false;
	for (int i{}; i < Node1Edges.size(); i++)
	{
		if (Opposite(inNode1, Node1Edges[i]) == inNode2)
		{
			isConnected = true;
		}	
	}
	for (int y{}; y < Node2Edges.size(); y++)
	{
		if (Opposite(inNode2, Node2Edges[y]) == inNode1)
		{
			isConnected = true;
		}	
	}

	return isConnected;
}

void Graph::ReplaceNode(Node* inNode, float inData)
{
	inNode->Data = inData;
}

void Graph::ReplaceEdge(Edge* inEdge, float inCost)
{
	inEdge->Cost = inCost;
}

void Graph::DeleteNode(Node* inNode)
{
	inNode->Destroy();
}

void Graph::DeleteEdge(Edge* inEdge)
{
	inEdge->Destroy();
}

std::vector<Edge*> Graph::IncidentEdges(Node* inNode)
{
	return inNode->ListOfConnectedEdges;
}

std::vector<Node*> Graph::Nodes()
{
	return ListOfNodes;
}

std::vector<Edge*> Graph::Edges()
{
	std::vector<Edge*> AllEdges;
	for (int i{}; i < Nodes().size(); i++)
	{
		std::vector<Edge*> tempListOfEdges = Nodes()[i]->ListOfConnectedEdges;
		
		for (int y{}; y < tempListOfEdges.size(); y++)
		{
			bool isInList = false;
			for (int z{}; z < AllEdges.size(); z++)
			{
				if (tempListOfEdges[y] == AllEdges[z])
				{
					isInList = true;
				}
			}
			if(!isInList)
			{
				AllEdges.push_back(tempListOfEdges[y]);
			}
			
		}
		
	}
	return AllEdges;
}

Node* Graph::FindNodeFromName(std::string inName)
{
	for (int i{}; i < Nodes().size(); i++)
	{
		if (Nodes()[i]->Name == inName)
		{
			return Nodes()[i];
		}
	}
	std::cout <<"'" <<  inName << "' not found" << std::endl;
	return nullptr;
}


void Graph::TraverseGraph(Node* StartNode)
{
	StartNode->isVisited = true;
	std::cout << StartNode->Name << std::endl;

	std::vector<Node*> AdjacentNodes = StartNode->ListOfAdjacentNodes;
	
	for (int i{}; i < AdjacentNodes.size(); i++)
	{
		if (AdjacentNodes[i]->isVisited)
		{
			
		}
		else
		{
			TraverseGraph(AdjacentNodes[i]);
			//StartNode->isVisited = false;
		}
	}
}

void Graph::TraverseGraphStart(Node* StartNode)
{
	std::vector<Node*> AllNodes = Nodes();
	for (int i{}; i < AllNodes.size(); i++)
	{
		AllNodes[i]->isVisited = false;
	}
	TraverseGraph(StartNode);

	for (int i{}; i < AllNodes.size(); i++)
	{
		AllNodes[i]->isVisited = false;
	}
}

void Graph::TraverseGraphStart(std::string StartNodeS)
{
	return TraverseGraphStart(FindNodeFromName(StartNodeS));
}

Node* Graph::InsertRandomNode(std::string inName, float inData, int maxCost)
{
	srand(time(nullptr));

	int RandInt = rand() % Nodes().size();
	int RandCost = rand() % maxCost;
	Node* RandNode = InsertNode(inName, inData);
	InsertEdge(RandNode, Nodes()[RandInt], RandCost);
	
	return RandNode;
}


