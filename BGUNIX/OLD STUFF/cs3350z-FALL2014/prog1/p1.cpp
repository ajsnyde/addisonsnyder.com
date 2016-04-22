// File: p1.cpp
// Author: Addison Snyder
// Course: CS 3350

#include "cctype"
#include "iostream"
#include "string"
#include "fstream"

using namespace std;

int binary_search(string[], string);	//searches dictionary for a word
string decoder(string&, string);	//decodes message using key
void load(string[]);	     // loads dictionary
void word(string[], string); // recognizes words using dictionary

int main()
{
	string key;

	string dict[25143];
	load(dict);	
	string test_string;
	int test;
	string code2 = "vshx su wgcy wx mcix sy, cvwclu gcu rxxe, cvwclu wsvv rx.";		// standard code you gave us. I don't understand why it won't work with the keys. I've tried by hand and using the program...
	string code1 = "Ifmmp! Uijt jt b UfTu";							// Demonstrates code with compatibility with first key
	string code;
	cout << "Hello! Welcome to Dread's Decoder Utility!\n";
	cout << "Opening codetable.txt . . .\n";
	
	//Open Table of keys

	ifstream input;
	input.open("codetable.txt");

	if(!input)
	{
		cout << "File not found!\n";
		return 0;// Kills program
	}



	cout << "Initial code:\n" << code1 << "\n\n";	

	for(int i = 0; !input.eof(); i++) // Until the end of the table, try all keys against string
	{
		code = code1;
		input >> key;
		test_string = decoder(code, key);
		word(dict, test_string);
	}

	return 0;
}

string decoder(string &in, string key)
{
	char test = '0';
	bool capital;
	string alphabet = "abcdefghijklmnopqrstuvwxyz"; // used to make comparisons

	cout << "Processing code using the following key:\n";
	cout << key << "\n";

	for(int i = 0; i < in.size(); i++)
	{
		test = in[i];
		if(tolower(in[i]) >= 'a' && tolower(in[i]) <= 'z')
		{
			if(in[i] >= 'A' && in[i] <= 'Z')
				capital = true;
			else
				capital = false;

			for(int p = 0; p < 25; p++)
			{
				if(tolower(in[i]) == key[p])
					in[i] = alphabet[p];
			}
				if(capital == true)// Allows for capitals to appear
					in[i] = toupper(in[i]);
		}
	}

	cout << "\nFinal code:\n" << in << "\n\n";

	return in;
}

void load(string dictionary[]) // Loads dictionary into giant array
{
	ifstream input;
	input.open("/usr/dict/words");

	if(!input)
	{
		cout << "File not found!\n";
		return;
	}

		for(int i = 0; !input.eof(); i++)
	{
		input >> dictionary[i];
	}
	return;
}

void word(string *dict, string code) // breaks string up by words, sends individual words to be searched through dictionary
{
	int num_words = 0;
	int words_recognized = 0;
	int first = 0;			//first & last number of char of a marked 'word'
	int last = 0;
	char test;
	bool start = false;		// essentially marks when the program looks for the end of a stream of letters

	for(int i = 0; code[i] != '\0'; i++)
	{
		if(!start && ((code[i] >= 65 && code[i] <= 132) || (code[i] >= 141 && code[i] <= 172)))//is letter?
		{
			first = i;
			start = true;
		}

		if(start && (code[i] <= 65 || code[i] >= 132) && (code[i] <= 141 || code[i] >= 172))//is non-letter?
		{
			last = i - 1;
			start = false;
			num_words++;

			cout << "Possible word detected between chars " << first << " and " << last;

			if(binary_search(dict, code.substr(first, (last-first) +1)) != -1) // search using binary search function
			{
				words_recognized++;
				cout << " - It's a word!\n";
			}
			else cout << " - No dice!\n";
		}
	}
	cout << "Total words detected: " << num_words << "\nTotal words recognized: " << words_recognized << "\n";
	return;
}

int binary_search(string *array, string search_key) // standard binary search with added compatibility for MIXED capitalization
{
	for(int i = 0; search_key[i] != '\0'; i++)
	{
		search_key[i] = tolower(search_key[i]);
	}

	int first = 0;
	int last = 25142;  // my lucky number
	string compare;

	while(first <= last)
	{
		int mid = (first + last)/2;
		
		compare = array[mid];

		for(int i = 0; compare[i] != '\0'; i++)
		{
			compare[i] = tolower(compare[i]);
		}

		if (compare == search_key)
			return mid;
		else
		{
			if (compare > search_key)
				last = mid - 1;
			else
				first = mid + 1;
		}
	}
	return -1;
}