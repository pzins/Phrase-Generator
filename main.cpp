#include "Text.h"

#define LEARNING_LENGTH 100000
#define SENTENCE_PHRASE 5
//input : 
//_text : the whole learning text
//t : the Text object
void learn(const std::string& _text, Text& t)
{
	std::string word;
	std::string succ;
	int pointer = 0;
	int stop = 0;
	do
	{
		++stop;
		//end of the first word
		std::size_t found = _text.find_first_not_of("abcdefghijklmnopqrstuvwxyzéèâîêàABCDEFGHIJKLMNOPQRSTUVWXYZ", pointer);
		//1st word
		word = _text.substr(pointer, found-pointer);
		//beginning second word
		pointer = _text.find_first_of("abcdefghijklmnopqrstuvwxyzéèâîêàABCDEFGHIJKLMNOPQRSTUVWXYZ", found);
		//end of second word
		found = _text.find_first_not_of("abcdefghijklmnopqrstuvwxyzéèâîêàABCDEFGHIJKLMNOPQRSTUVWXYZ", pointer);
		//second word
		succ = _text.substr(pointer, found-pointer);
		//add word to t
		t.addWords(word, succ);
	}while(stop < LEARNING_LENGTH); 
	t.computeProba();
}



//input : 
//_startWord : first word of the sentence
//_text : the text
//print a generated sentence
void generateSentence(const std::string& _startWord, Text& _text)
{
	std::string sentence = _startWord;
	std::string tmp = _startWord;
	for(int i = 0; i < SENTENCE_PHRASE; ++i)
	{
		sentence += " ";
		std::string res = _text.getBestSucc(tmp);
		tmp = res;
		sentence += res;
	}
	std::cout << "Starting word : " << _startWord << " => " << sentence << std::endl;
}



int main()
{
	//learning text : rouge.txt => Le Rouge et le Noir
	std::ifstream in("rouge.txt");
	
	//reserve place is not necessary
	//in.seekg(0, std::ios::end);
	//str.reserve(in.tellg());
	
	//copy the learning text in one big string
	std::string str;
	in.seekg(0);
	str.assign((std::istreambuf_iterator<char>(in)),
		std::istreambuf_iterator<char>());
	
	Text t;
	learn(str,t);

	generateSentence("Une", t);
	generateSentence("La", t);
	generateSentence("à", t);
	generateSentence("Un", t);
	generateSentence("Elle", t);
	generateSentence("Il", t);
	return 0;
}