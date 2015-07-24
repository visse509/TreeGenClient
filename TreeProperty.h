
#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <fstream>
#include <vector>
class TreeProperty
{
public:
	static TreeProperty *instance;
	static TreeProperty* getInstance();
	int nLevels;
	std::vector<int> nBranchesList;
	std::vector<int> rotVals;
	std::vector<int> nSegments;
	std::vector<float> lengths;
	std::vector<int> nEdges;
	std::vector<float> girths;
	std::vector<float> nLeafs;
	
private:
	void initFromXml();
	TreeProperty(); 
	TreeProperty(TreeProperty const&);
    void operator=(TreeProperty const&); 
};

