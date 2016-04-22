//All code by Addison Snyder
//Lab #3 - reading from files
//File from wired.com

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main()
{
	string word;
	string first;
	char backspace = 8;//used to get rid of period when displaying last "word"
	int sentance_count = 0;
	int word_count = 0;
	ifstream input;

	input.open("wired.txt");//attempt to open file
	if(!input)//check if file is successfully opened
	{
		cout << "File not found! Terminating program!\n";
		return 1;//if not, kill the program
	}
	input >> first;//seed loop
	cout << "\n" << first << " ";
	word_count++;
	while(!input.eof())
	{
		input >> word;
		word_count++;
		if(!input.eof())
			cout << word;
		cout << " ";
		if(word[(word.length() - 1)] == '.')//detects periods at the END of each word
			sentance_count++;//counts them as sentances.
	}
	cout << "\n-------------------------------------------------------------------------------\n";//display stats
	cout << "First: " << first << "     Last: " << word << backspace << "     Wordcount: " << word_count << "     # of sentances: " << sentance_count << "\n";
	return 0;//end
}