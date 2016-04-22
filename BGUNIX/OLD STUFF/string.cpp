// Wordplay.cpp ADDISON sNYDER	12/13/14!
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <fstream>
#include <set>

using namespace std;

int main()
{
	string in, pre;
	set<string> dict;
	unsigned int i, q, x;
	vector<string> key, fin;
	string word;
	bool isword, kill;
	vector<string> edit;


/////////////////////////////////////////////////////	Load dictionary

	cout << "Loading dictionary. . .\n";
	ifstream input;
	input.open("p5dict.txt");


	if(!input)	// In case file isn't found, program dies...
	{
		cout << "File not found!\n";
	}

		for(int i = 0; !input.eof(); i++)
	{
		input >> word;
		dict.insert(word);
	}
	cout << "File loaded!\n";
	input.close();

/////////////////////////////////////////////////////	Basic input and basic preprocessing


	cout << "Enter a string: ";	// Input
	getline (cin, pre);

	cout << "Transforming word to compatible chars. . .\n";

	transform(pre.begin(), pre.end(), pre.begin(), ::tolower);	//Forces lowercase
	for(i = 0; i < pre.size(); i++)
	{
		if(pre[i] >= 'a' && pre[i] <= 'z')	//Destroys punctuation
			in.push_back(pre[i]);
	}
	cout << "How many words? ";					//Get number of words
	cin >> x;
	cout << "Adding spaces for # words. . .\n";
	for(i = 0; i < in.size(); i++)					//Apply special symbol to sygnify 'spaces' in between substrings
		if(in[i] == 'a')
			in[i] = '!';


/////////////////////////////////////////////////////	Sorting, Permutation, and Cleansing (organization of data)


	cout << "Sorting letters. . .\n";
	sort(in.begin(), in.end());					//Sort chars before permutations and building predictable behavior
	cout << "Permutation phase. . .\n";			
	key.push_back(in);						//seed vector
	for(i = 0; next_permutation(in.begin(), in.end()); i++)         //Begin  filling vector with every possible combo       
		key.push_back(in);
	std::cout << "Initial number of possibilities: " << i+1 << "\n";
	cout << "Killing redundent combos. . .\n";
	for(unsigned int i = 0; i < key.size(); i++)			//Checks over each combo for double spaces and spaces against the sides of the string
	{
		kill = false;						//kill flag
		for(unsigned int q = 0; q < key[i].size(); q++)
		{
			if(q < key[i].size()-1)
				if(key[i][q] == '!' && key[i][q+1] == '!' )
					kill = true;
		}
		if(key[i][key[i].size()-1] != '!' && key[i][0] != '!' && !kill)		//cleansing
		{
			edit.push_back(key[i]);
		}

	}
	cout << "Killed " << (key.size()-edit.size()) << " combinations when checking for side-spaces and double-spaces.\n";	//status report
	key = edit;

	for (i = 0; i < edit.size(); i++)
		cout << edit[i] <<"\n";

/////////////////////////////////////////////////////	Searching/Flagging of good data

	word.erase();
	cout << "Comparing sub-groups to dictionary terms. . .\n";
	for(i = 0; i < key.size(); i++)				// check strings for substrings (using '!'s as guidelines)
	{
		isword = true;					//seeds internal loop
		for(q = 0; q < key[i].size(); q++)
		{

			if(key[i][q] != '!')
				word.push_back(key[i][q]);	//add chars to test string so when '!' is found, test string can be tested using dictionary
			else //CHECK WORD AGAINST DICT		//detects substrings
			{

				if(dict.find(word) == dict.end())	//using binary search on dictionary with ordered set
				{
					isword = false;
					word.erase();
					break;				//if one substring is bad, the entire string is garbage. Terminates loop for increased efficiency
				}
				word.erase();
			}
		}
		if(dict.find(word) != dict.end() && isword)
			fin.push_back(key[i]);				//adds the few meaningful strings to be further processed
		word.erase();
	}
	cout << fin.size() << "words left!\n";
/////////////////////////////////////////////////////	Prepping data for Final round of cleaning

	cout << "Preparing for duplicate detection. . .\n";

	vector<vector<string> > ending;
	ending.resize(fin.size());
	word.erase();

	for(i = 0; i < fin.size(); i++)					//breaks final strings up back into substrings (made after creating adequate results on base program)
	{
		for(x = 0; x < fin[i].size(); x++)			//inefficient, but better than not being there...
		{
			if(fin[i][x] != '!')
				word.push_back(fin[i][x]);		//uses vectors within vectors to hold an unknown amount of sub-strings for each string
			else
			{
				ending[i].push_back(word);
				word.erase();
			}
		}
		ending[i].push_back(word);
		word.erase();
		sort(ending[i].begin(),ending[i].end());		//sorts all of these substrings so they can be compared against one another
	}

	for(i = 0; i < ending.size(); i++)
	{
		for(x = 0; x < ending[i].size(); x++)
			cout << ending[i][x] << " ";
	cout << "\n";
	}
	

////////////////////////////////////////////////////	Flagging/Erasing Duplicates

	cout << "Flagging duplicates. . .\n";

	for(i = 0; i < ending.size() - 1; i++)
	{
		for(x = 0; x < ending.size(); x++)			// Big O of n^2 - fine for small numbers that make it this far (typically up to 30ish)
		{
			if(ending[i] == ending[x] && x != i)
			{						//if the strings are the same, one gets flagged with a '-1' as first substring
				ending[x][0] = "1";			//due to preprocessing, a naturally occurring -1 is impossible
			}
		}
	}

	cout << "Filtering Duplicates. . .\n";

	key.erase(key.begin(), key.end());				//reuses old variables to store new  and refined info

	for(i = 0; i < ending.size(); i++)				//filters using -1, as described previously
	{
		if(ending[i][0] != "1")
			key.push_back(fin[i]);
	}

/////////////////////////////////////////////////////	Presentation of data

	cout << "END RESULTS:\n~~~~~~~~~\n";				//shows end results

	for (i=0; i < key.size(); i++)
	{
		for(q = 0; q < key[i].size(); q++)
			if(key[i][q] == '!')
				key[i][q] = ' ';		
		cout << key[i] << "\n";					//DONE!
	}
	return 0;
}

