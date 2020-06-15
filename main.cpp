
/*
 * Liliia Pavlishin
 * Summer 2020
 * CS 311
 *
 * This program mimics lexical analyzer
 * Spaces are chosen as delimeters
 *
 */
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
using namespace std;

#define DICTIONARY_SIZE 97
#define KEYWORD_TABLE_SIZE 11
#define OPRATOR_TABLE_SIZE 29
#define SPECIAL_CHARACTER_TABLE_SIZE 7
#define DIGIT_TABLE_SIZE 10


// dictionary node
class NODE{
	string name;
	string className;
	int appearances;

	NODE(string n, string cn){
		appearances = 0;
		name = n;
		className = cn;
	}
};

vector<NODE> DICTIONARY[DICTIONARY_SIZE];

void buildDictionary(string keywordTable[], string operatorTable[], string specialCharTable[], string digitTable);
bool isInDictionary();
void addToDitionary();
int createKey(string str);
NODE nodeInit(string, string, int);



//int main(int argc, char* argv[]){
int main(){

	int i = 0;
	int found = 0;
	string stringTok;
	int SIZE = 45;
	const int keywordsBeg = 0;
	const int operatorsBeg = 8;
	const int specialTokBeg = 34;
	bool bfound;

	/*TODO
	 * 1. need a vector to keep track of classes
	 * but first need to find out what data type to use
	 */

	// sizes of tables
	int sctsize = 7;
	int dtsize = 10;

	// tables
	string keywordTable[11] = {"if", "then", "else", "auto", "delete", "new", "NULL", "nullptr", "using", "namespace", "std"};
	string operatorTable[29] = {"=", "==", "!=", "<", "<=", ">", ">=", "+", "+=", "++", "-",  "-=", "--", "*", "*=",  "/", "/=", "%", "%=", ":", "::", "?", "!", "<<", ">>", "|", "||", "&", "&&"};
	string specialCharTable[7] = {";", "(", ")", "{", "}", "[", "]"};
	string digitTable[10] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};

	cout << "\nBuilding hash table..." << endl;
	buildDictionary(keywordTable, operatorTable, specialCharTable, digitTable);
	cout << "\nBuild finished" << endl;


	// lexicalAnalyzerStringTable is initially initialized with zeros
	// it is mapped with nameTable
	// every time a word from nameTable is found in the file passed in,
	// the value at the corresponding index is incremented
	int lexicalStringTable[SIZE] = {0};

	ifstream fin;
	//fin.open(argv[1]);
	fin.open("../file_system.cpp");

	string str, tok;

	while(getline(fin, str)) {
		cout << "\nStr here is " << str << endl;
		i = 0;
		while(str[i] != '\n' && str != ""){
			cout << "str[i] is " << str[i] << endl;

			//****************************************************************** Omitting tokens that will not be evaluated **********************************************************

			// Omitting STRINGS
			if(str[i] == '\"'){
				do{
					// found should be never -1 since the code assumed to be syntactically correct
					found = str.find("\"", found);
				}while(str[found-1] == '\\');

				// move past string
				i = found+1;
				continue;
			}
			// Omitting spaces and tabs
			else if(str[i] == ' ' || str[i] == '\t'){
				i++;
				continue;
			}
			// Moving past multi-line comments
			else if(str[i] == '/' && str[i+1] == '*'){

				found = str.find("*/");

				while(found < 0){
					getline(fin, str);
					found = str.find("*/");
				}

				// moving pass the comment
				// get rid of the comment
				str.erase(0, found+2);
				continue;
			}
			// Omitting single line comments, include directives and macros
			else if((str[i] == '/' && str[i+1] == '/') || str[i] == '#'){
				// check if there is open tag for multi-line comment
				found = str.find("/*");
				if(found >=0){
					str.erase(i, found);
					continue;
				}
				break;
			}


			//*************************************************************************** get tokens*******************************************************************


			// RE DOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO
			if(isdigit(str[i])){
				string s(1, str[i]);
				digitMap[stoi(s)]++;
				i++;
				continue;
			}

			// operators
			// 1. one char operator
			// 2. two char operator
			/*
			 * a. if found an operator, check if there is one immidiately after
			 * 		- if there is an operator right after, your token is 2 chars
			 * b. assign token to tok
			 * c. erase token from str
			 * d. continue
			 *
			 */

			bfound = false;
			for(int j=0; j<29; j++){
				if(str[i] == operatorTable[j]){
					for(int k=0; k<29, k++){
						if(str[i])
					}
				}
			}








		}
		// here goes everything that skipsm
	}


	fin.close();

	return 0;
}

void buildDictionary(string keywordTable[], string operatorTable[], string specialCharTable[], string digitTable[]){
	int key;
	for(int i=0; i<KEYWORD_TABLE_SIZE; i++){
		NODE node = new NODE(keywordTable[i], "keyword");
		key = createKey(keywordTable[i]);
		DICTIONARY[key].push_back(node);
	}
	for(int i=0; i<OPRATOR_TABLE_SIZE; i++){
		NODE node = new NODE(keywordTable[i], "operator");
		key = createKey(keywordTable[i]);
		DICTIONARY[key].push_back(node);
	}
	for(int i=0; i<SPECIAL_CHARACTER_TABLE_SIZE; i++){
		NODE node = new NODE(keywordTable[i], "special character");
		key = createKey(keywordTable[i]);
		DICTIONARY[key].push_back(node);
	}
	for(int i=0; i<DIGIT_TABLE_SIZE; i++){
		NODE node = new NODE(keywordTable[i], "digit");
		key = createKey(keywordTable[i]);
		DICTIONARY[key].push_back(node);
	}
}
int createKey(string s){
	int i = atoi(s[0]);
	// the keys in askii that we're interested in start with 33
	i -=33;
	// precaution
	i %= DICTIONARY_SIZE;
	return i;
}


bool isInDictionary();
void addToDictionary();

