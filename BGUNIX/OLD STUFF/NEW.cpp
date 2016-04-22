#include "cctype"
#include "iostream"
#include "string"
#include "fstream"

using namespace std;

void decoder(string&, string);
void load(string[]);

int main()
{
	string alphbet = "abcdefghijklmnopqrstuvwxyz";
	string ref1    = "bcdefghijklmnopqrstuvwxyza";
	string code1 = "Gdkkn Vnqkc!";

	string test_string = code1;

	char test = '0';

	cout << "Hello! Welcome to Dread's Decoder Utility!\n";

	cout << "Initial code:\n" << code1;

	decoder(code1, ref1);
	cout << code1;

	string dict[26000];

	load(dict);

	for(int i = 0; i < 100; i++)
		cout << dict[i] << "\n";

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