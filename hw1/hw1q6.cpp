#include <iostream>
#include <sstream>
#include <fstream>
using namespace std;


// readFile function
void readFile(const char* fileName, string* &myArr, int &numWords){
	ifstream inFile(fileName);

	if(!inFile.fail()){
		if(inFile >> numWords){
			myArr = new string[numWords];
			string line;
			int index = 0;
			while (getline(inFile, line)){
				stringstream ss(line);
				if(!line.empty()){
					string word;
					while (ss >> word){
						myArr[index] = word;
						index ++; 
					}
				}
			}

		}
		else cerr << "The format of the file is wrong\n";
	}
	else cerr << "The file cannot be opened!\n";
	return; 
}

void printFile(string* myArr, int length){
	if(length != 0){
		for (int i = 0; i < length; i++){
			cout << myArr[length - i - 1] << endl;
		}
	}
	delete[] myArr;
}

int main(int argc, char* argv[]){
	string* myArr;
	int numWords = 0;
	readFile(argv[1], myArr, numWords);
	printFile(myArr, numWords);




	return 0;
}