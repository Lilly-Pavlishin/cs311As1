/*
 * Liliia Pavlishin
 * Summer 2020
 * CS 311
 *
 * This program mimics lexical analyzer
 * Spaces are chosen as delimeters
 *
 *
 */
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
using namespace std;

//int main(int argc, char* argv[]){
int main(){

	int i = 0;
	string stringTok;
	int SIZE = 45;
	int searchableSIZE = SIZE-3;
	const int keywordsBeg = 0;
	const int operatorsBeg = 8;
	const int specialTokBeg = 34;
	const int strAndCharBeg = 41;
	int keywordTOT, operatorTOT, specialTokTOT;
	keywordTOT = operatorTOT = specialTokTOT = 0;

	/*
	 * nameTable contents:
	 * 0-7 keywords
	 * 8-34 operators
	 * 35-41 special characters
	 * 42 strings
	 * 43 characters
	 * 44 identifiers
	 */
	string nameTable[SIZE] = {"if", "then", "else", "auto", "delete", "new", "NULL", "nullptr",
						      "=", "==", "!=", "<", "<=", ">", ">=", "+", "+=", "++", "-",  "-=", "--", "*", "*=",  "/", "/=", "%", "%=", ":", "::", "?", "!", "<<", ">>", "||", "&&", ";", "(", ")", "{", "}", "[", "]",
						      "SpaceHolderForStringLiterals", "SpaceHolderForCharacters", "SpaceHolderForIdentifiers"};

	// lexicalAnalyzerStringTable is initially initialized with zeros
	// it is mapped with nameTable
	// every time a word from nameTable is found in the file passed in,
	// the value at the corresponding index is incremented
	int lexicalStringTable[SIZE] = {0};

	ifstream fin;
	//fin.open(argv[1]);
	fin.open("../file_system.cpp");


	// TODO
	//  1. add identifiers as tokens here
	//  2. think about perfect hash table implementation
	//  3. Convert everything to lowercase before comparing



	string str, tok;

	while(getline(fin, str)){

		int strend = 0;
		i = 0;
		while(str[0] == '\"' && str[++i] != '\"'){

		}

		istringstream in(str);  // create a stringstream object
		in >> tok;

		while(in){

			i = 0;
			// look through nameTable trying to find a match
			while(i < searchableSIZE && tok.compare(nameTable[i]) != 0) {
				i++;
			}

			// of token matches the name, increment the lexical string table
			if(i != searchableSIZE && tok.compare(nameTable[i]) == 0) {
				lexicalStringTable[i]++;
			}
			// look for characters
			else if(tok.size() == 3 && tok[0] == '\'') {
				lexicalStringTable[42]++;
			}

			in >> tok;
		}

		// convert everything to lowercase
		
	}

	// REPORT:

	for(i=keywordsBeg; i<operatorsBeg; i++){
		cout << "Keyword: '" << nameTable[i] << "' was found " << lexicalStringTable[i] << " times\n";
		keywordTOT += lexicalStringTable[i];
	}
	for(i=operatorsBeg; i<specialTokBeg; i++){
		cout << "Operator: '" << nameTable[i] << "' was found " << lexicalStringTable[i] << " times\n";
		operatorTOT += lexicalStringTable[i];
	}
	for(i=specialTokBeg; i<strAndCharBeg; i++){
		cout << "Special: '" << nameTable[i] << "' was found " << lexicalStringTable[i] << " times\n";
		specialTokTOT += lexicalStringTable[i];
	}


	cout << "\nKeywords appeared " << keywordTOT << " times\n";
	cout << "Operators appeared " << operatorTOT << " times\n";
	cout << "Special characters appeared " << specialTokTOT << " times\n";
	cout << "Strings appeared " << lexicalStringTable[41] << " times\n";
	cout << "characters appeared " << lexicalStringTable[42] << " times\n";


	fin.close();

	return 0;
}
