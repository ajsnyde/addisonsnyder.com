// Wordplay.cpp : Defines the entry point for the console application.
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
	bool isword;
	bool kill;
	vector<string> edit;
/////////////////////////////////////////////////////
	cout << "Loading dictionary. . .\n";
	ifstream input;
	input.open("p5dict.txt");


	if(!input)
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

	cout << "Enter a string: ";
	getline (cin, pre);
	transform(pre.begin(), pre.end(), pre.begin(), ::tolower);
	for(i = 0; i < pre.size(); i++)
	{
		if(pre[i] >= 'a' && pre[i] <= 'z')
			in.push_back(pre[i]);
	}

	cin >> x;
	for(i = 0; i < x; i++)
		in.push_back('!');
	
/////////////////////////////////////////////////////


	sort(in.begin(), in.end());
	key.push_back(in);
	for(i = 0; next_permutation(in.begin(), in.end()); i++)                 
		key.push_back(in);
	std::cout << "Initial number of possibilities: " << i+1 << "\n";

	for(unsigned int i = 0; i < key.size(); i++)
	{
		kill = false;
		for(unsigned int q = 0; q < key[i].size(); q++)
		{
			if(q < key[i].size()-1)
				if(key[i][q] == '!' && key[i][q+1] == '!' )
					kill = true;
		}
		if(key[i][key[i].size()-1] != '!' && key[i][0] != '!' && !kill)
		{
			edit.push_back(key[i]);
		}

	}
	cout << "Killed " << (key.size()-edit.size()) << " combinations when checking for side-spaces and double-spaces.\n";
	key = edit;

	word.erase();

	for(i = 0; i < key.size(); i++)
	{
		isword = true;
		for(q = 0; q < key[i].size(); q++)
		{

			if(key[i][q] != '!')
				word.push_back(key[i][q]);
			else //CHECK WORD AGAINST DICT
			{

				if(dict.find(word) == dict.end())
				{
					isword = false;
					word.erase();
					break;	
				}
				word.erase();
			}
		}
		if(dict.find(word) != dict.end() && isword)
			fin.push_back(key[i]);
		word.erase();
	}



	vector<vector<string> > ending;
	ending.resize(fin.size());
	word.erase();

	for(i = 0; i < fin.size(); i++)
	{
		for(x = 0; x < fin[i].size(); x++)
		{
			if(fin[i][x] != '!')
				word.push_back(fin[i][x]);
			else
			{
				ending[i].push_back(word);
				word.erase();
			}
		}
		ending[i].push_back(word);
		word.erase();
		sort(ending[i].begin(),ending[i].end());
		for(q=0; q<ending[i].size(); q++)
			cout << ending[i][q] << "  ";
		cout << "\n";
	}



	for(i = 0; i < ending.size() - 1; i++)
	{
		for(x = i+1; x < ending.size(); x++)
		{
			if(ending[i] == ending[x])
				ending[x][0] = "-1";
		}
	}

	key.erase(key.begin(), key.end());

	for(i = 0; i < ending.size(); i++)
	{
		if(ending[i][0] != "-1")
			key.push_back(fin[i]);
	}

	cout << "END RESULTS:\n~~~~~~~~~\n";

	for (i=0; i < key.size(); i++)
	{
		for(q = 0; q < key[i].size(); q++)
			if(key[i][q] == '!')
				key[i][q] = ' ';		
		cout << key[i] << "\n";
	}
	return 0;
}

