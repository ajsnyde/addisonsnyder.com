// Decoder.cpp : Defines the entry point for the console application.
//

#include "cctype"
#include "iostream"
#include "string"
#include "fstream"

using namespace std;

int binary_search(string[],int, int, string);
void decoder(string&, string);
void load(string[]);

int main()
{
	string alphbet = "abcdefghijklmnopqrstuvwxyz";
	string ref1    = "bcdefghijklmnopqrstuvwxyza";
	string code1 = "Gdkkn Vnqkc!";

	string test_string = code1;

	char test = '0';
	int search = 0;

	cout << "Hello! Welcome to Dread's Decoder Utility!\n";

	cout << "Initial code:\n" << code1;
	
	if("hello" >= "abc")
		cout << "hello is greater than abc...\n";
	if("abc" >= "hello")
		cout << "abc is greater than hello\n";
	
	decoder(code1, ref1);
	cout << code1;

	string dict[25143];

	load(dict);

	for(int i = 0; i < 5; i++)
		cout << dict[i] << "\n";

	

	search = binary_search(dict, 1, 25142, "hello");

	if(search == -1)
		cout << "not found!\n";
	else
		cout << "found at " << search << "!\n";
	cin >> test;
	return 0;
}

void decoder(string &in, string key)
{
	char test = '0';
	bool capital;
	for(int i = 0; i < in.size(); i++)
	{
		test = in[i];
		if(tolower(in[i]) >= 'a' && tolower(in[i]) <= 'z')
		{
			if(in[i] >= 'A' && in[i] <= 'Z')
				capital = true;
			else
				capital = false;
			in[i] = key[(tolower(in[i]) - 97)];
			if(capital == true)
				in[i] -= 32;
		}
	}
	cout << "\nFinal code:\n" << in;
	return;
}

void load(string dictionary[])
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

int binary_search(string *array,int first,int last, string search_key)
{
	int index = 12;
	bool found = false;
	search_key = "AAA";
	

	for(int i = 0; search_key[i] != '\0'; i++)
	{
		search_key[i] = tolower(search_key[i]);
	}

	first = 0;
	last = 25142;
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
			{
				last = mid - 1;
				cout << array[mid] << " > " << search_key << "\n";
			}
			else
			{
				first = mid + 1;
				cout << array[mid] << " < " << search_key << "\n";
			}
		}
	}
	return -1;
}