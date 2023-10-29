#include <iostream>
#include "GeneralTreeNode.h"
#include "Graph.h"

int main(int argc, char* argv[])
{
	// -------- Tree  --------- //

    GeneralTreeNode* MyTreeRoot = new GeneralTreeNode(23323);
    GeneralTreeNode* MyWorstChild = new GeneralTreeNode(2, MyTreeRoot);
    GeneralTreeNode* MyBestChild = new GeneralTreeNode(42145, MyWorstChild);
		
    MyWorstChild->AddChild(23)->AddChild(2545);
    MyWorstChild->AddChild(255)->AddChild(25636)->AddChild(24);
	
    MyTreeRoot->AddChild(9013);
    MyTreeRoot->AddChild(69420)->AddChild(2563);

    std::cout << "Max Depth: " << MyTreeRoot->GetMaxDepth() << std::endl;

    for (int i{}; i < 10; i++)
    {
        MyTreeRoot->AddChildAtRandom(i);
    }

    // Depth Traverse
    std::cout << "DepthTraverse:" << std::endl;
    MyTreeRoot->StartDepthTraverse();
    std::cout << "" << std::endl;
	
    std::cout << "BreadthTraverse:" << std::endl;
    MyTreeRoot->StartBreadthTraverse();
    std::cout << "" << std::endl;

	// --------       --------- //

	// -------- Graph --------- //
	
	Graph* MyGraph = new Graph();

	MyGraph->InsertNode("Stallgården", 5);
	MyGraph->InsertNode("Heim", 5);
	MyGraph->InsertNode("Siesta", 5);
	MyGraph->InsertNode("Matkvartalet", 5);
	MyGraph->InsertNode("Hygge", 5);
	MyGraph->InsertNode("Nellie", 5);
	MyGraph->InsertNode("Gullkorn", 5);
	MyGraph->InsertNode("Festiviteten", 5);

	MyGraph->InsertEdge("Stallgården","Heim", 2);
	MyGraph->InsertEdge("Stallgården","Hygge", 1);
    
	MyGraph->InsertEdge("Heim", "Siesta", 3);
	MyGraph->InsertEdge("Heim","Nellie", 3);
	MyGraph->InsertEdge("Heim","Gullkorn", 2);
    
	MyGraph->InsertEdge("Siesta","Matkvartalet", 3);
	MyGraph->InsertEdge("Siesta","Gullkorn", 3);
	MyGraph->InsertEdge("Siesta","Festiviteten", 8);
    
	MyGraph->InsertEdge("Hygge","Nellie", 2);
    
	MyGraph->InsertEdge("Gullkorn","Festiviteten", 5);
	MyGraph->InsertEdge("Gullkorn","Nellie", 4);
    
	MyGraph->InsertEdge("Matkvartalet","Festiviteten", 6);

	MyGraph->TraverseGraphStart("Stallgården");

	std::cout << MyGraph->GetEdgeBetween("Gullkorn", "Festiviteten")->Cost;

	// --------       --------- //

	delete MyGraph;
	delete MyTreeRoot;
	
    return 0;
}
