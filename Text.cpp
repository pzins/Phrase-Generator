#include "Text.h"


void Word::addSuccessor(const std::string& _str)
{
	if(successors.find(_str) == successors.end())
		successors[_str] = 0;
	else
		successors[_str]++;
}

void Word::print()
{
	std::cout << "=======  " << word << "   ============" << std::endl;
	for(auto& i : successors)
		std::cout << "=> " << i.first << std::endl;
	std::cout << "======================================" << std::endl;
}

int Word::size()
{
	return successors.size();
}

void Word::computeProba()
{
	int somme = 0;
	for(auto& i : successors)
		somme += i.second;
	for(auto& i : successors)
		i.second = i.second / somme;
}

const std::string Word::getBestSucc()
{
	std::string res = "";
	float max = 0;
	for(auto& i : successors)
	{
		if(i.second > max)
		{
			max = i.second;
			res = i.first;
		}
	}
	return res;
}


//====================================================================================================

void Text::addWords(std::string& _word, const std::string& _succ)
{
	if(words.find(_word) == words.end())
	{
		Word w(_word);
		w.addSuccessor(_succ);
		words[_word] = w;
	}
	else
	{
		words[_word].addSuccessor(_succ);
	}
}

void Text::print()
{
	for(auto& i : words)
	{
		std::cout << i.first << " => " << i.second.size() << std::endl;
	}
}

std::map<std::string, Word>& Text::getMap(){return words;}

void Text::computeProba()
{
	for(auto& i : words)
		i.second.computeProba();
}

std::string Text::getBestSucc(const std::string& _str)
{
	return words[_str].getBestSucc();
}