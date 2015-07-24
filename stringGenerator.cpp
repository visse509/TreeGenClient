#include "stdafx.h"
#include "stringGenerator.h"


stringGenerator::stringGenerator(void){

	pRules['f'] = "f";
	//pRules['x'] = "[rfxf[lf[xf]]rf]f[lfx[rf]lf[xf]][xr][xr][xx]";
	//pRules['x'] = "[rf[x[x]]][lf[x[x]]]";
	pRules['x'] = "f[lf[xf]]f[rf[x]]f[lf[xf]]f[rf[xf]]f[lf[xf]]f[rf[x]]f[lf[xf]]f[rf[xf]]";
	pRules['l'] = "l";
	pRules['r'] = "r";
	pRules['['] = "[";
	pRules[']'] = "]";

	axiom.push_back('f');
	axiom.push_back('f');
	axiom.push_back('x');


	alphabet.push_back('f');
	alphabet.push_back('x');
	alphabet.push_back('y');
	alphabet.push_back('r');
	alphabet.push_back('l');
	alphabet.push_back('[');
	alphabet.push_back(']');
	alphabet.push_back('q');

	currentString = axiom;

	expandString();
	expandString();
	expandString();
	//expandString();
	//expandString();
	//expandString();
	//expandString();
}

void stringGenerator::expandString(){
	newString.clear();
	for(int i = 0; i < currentString.size(); i++){
		char tChar = currentString[i];
		std::vector<char> tVec = getProductionRule(tChar);
		newString.insert( newString.end(), tVec.begin(), tVec.end() );
	}
	currentString = newString;
}

std::vector<char> stringGenerator::getProductionRule(char inWord){
	std::vector<char> res;
	std::string tString = pRules.find(inWord)->second;
	for(int i = 0; i < tString.size();i++){
		res.push_back(tString[i]);
	}
	return res;
}

std::vector<char> stringGenerator::getString(){
	return newString;
}