#include "stdafx.h"
#include "TreeProperty.h"
#include "rapidxml.hpp"
#include "FileReader.h"
#pragma unmanaged
using namespace rapidxml;
TreeProperty* TreeProperty::instance = NULL;  
TreeProperty::TreeProperty()
{
	initFromXml();
}

TreeProperty* TreeProperty::getInstance()
{
	if (TreeProperty::instance == NULL) {
		instance = new TreeProperty();
	}
	return instance;
}

void TreeProperty::initFromXml()
{
	FileReader *file = new FileReader("treeProp.xml");
	char * text = const_cast<char*>(file->getChars());

	//Parse xmlfile
	xml_document<> doc;
	doc.parse<0>(text);

	//nbranches
	xml_node<> *root = doc.first_node()->first_node();
	xml_node<> *node = root->next_sibling();
	for (xml_node<> *child = node->first_node(); child; child = child->next_sibling())
	{
		char *nBranchesVal = child->first_node()->value();
		char *rotVal = child->first_node()->next_sibling()->value();
		char *segVal = child->first_node()->next_sibling()->next_sibling()->value();
		char *lengthVal = child->first_node()->next_sibling()->next_sibling()->next_sibling()->value();
		char *edgeVal = child->first_node()->next_sibling()->next_sibling()->next_sibling()->next_sibling()->value();
		char *girth = child->first_node()->next_sibling()->next_sibling()->next_sibling()->next_sibling()->next_sibling()->value();
		char *leaf = child->first_node()->next_sibling()->next_sibling()->next_sibling()->next_sibling()->next_sibling()->next_sibling()->value();

		nBranchesList.push_back(atoi(nBranchesVal));
		rotVals.push_back(atoi(rotVal));
		nSegments.push_back(atoi(segVal));
		lengths.push_back(static_cast<float>(atof(lengthVal)));
		nEdges.push_back(atoi(edgeVal));
		girths.push_back(static_cast<float>(atof(girth)));
		nLeafs.push_back(static_cast<float>(atof(leaf)));

	}
}
