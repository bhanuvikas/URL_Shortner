#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <iomanip>
using namespace std;

class URLShortner
{
private:
	map<int, string> database;
	map<int, char> lookup;
	long long int entries_count;
	long long int base;

public:
	string Encode(string);
	string Decode(string);
	int GetEntryCount() {return entries_count;}
	URLShortner();
	~URLShortner();
	void ToString();
};

URLShortner::URLShortner()
{
	base = 1000000;
	entries_count = base;
	for(int i=0;i<=25;i++)
	{
		lookup[i] = i+97;
	}
	for(int i=26;i<=51;i++)
	{
		lookup[i] = i-26+65;
	}
	for(int i=52;i<=61;i++)
	{
		lookup[i] = i-52+48;
	}
}

URLShortner::~URLShortner()
{
	lookup.clear();
	database.clear();
}

string URLShortner::Encode(string longURL)
{
	entries_count++;
	long long int key = entries_count;
	database[key] = longURL;

	float t = clock();
	string shortURL = "";
	while(key > 0)
	{
		int modulo = key%62;
		key /= 62;
		shortURL += lookup[modulo];
	}
	reverse(shortURL.begin(), shortURL.end());
	cout << "URLShortner: " << std::fixed << std::setprecision(9) << (clock() - t) / CLOCKS_PER_SEC << " seconds" << endl;
	return shortURL;
}

string URLShortner::Decode(string shortURL)
{
	long long int key=0;
	long long int multiplier = 1;
	for(int i=shortURL.length()-1;i>=0;i--)
	{
		int lookupIndex;
		char lookupValue = shortURL[i];
		if(lookupValue>=97 && lookupValue<=122)
		{
			lookupIndex = lookupValue-97;
		}
		else if(lookupValue>=65 && lookupValue<=90)
		{
			lookupIndex = lookupValue-65;
			lookupIndex += 26;
		}
		else if(lookupValue>=48 && lookupValue<=57)
		{
			lookupIndex = lookupIndex-48;
			lookupIndex += 52;
		}
		key += multiplier*lookupIndex;
		multiplier *= 62;
	}
	if(key <= GetEntryCount() && key >= base)
	{
		string longURL;
		longURL = database[key];
		return longURL;		
	}
	else
	{
		string temp = "";
		return temp;
	}
	
}


int main()
{
	URLShortner urlShortner;
	cout << "*****************************WELCOME TO URLShortner*****************************\n" << endl;
	cout << "Set Of Operations Those Can Be Requested:" << endl;
	cout << "1. Compression Of URL" << "\t\t--> Enter 'compress' without quotes\n";
	cout << "2. De-Compression Of URL" << "\t--> Enter 'decompress' without quotes\n";
	cout << "3. Exit" << "\t\t\t\t--> Enter 'exit' without quotes\n\n\n";
	string command;
	string input;
	string output;
	const string compress = "compress";
	const string decompress = "decompress";
	const string exit = "exit";
	const string prefix = "www.urlShortner.com/";
	while(true)
	{
		cout << "Enter the operation you want to perform:\n> ";
		cin >> command;
		if(command.compare(compress)==0)
		{
			cout << "Enter the URL you want to compress:\n> ";
			cin >> input;
			output = urlShortner.Encode(input);
			cout << "Your compressed URL is: \"www.urlShortner.com/" << output << "\"" << endl;
		}
		else if(command.compare(decompress)==0)
		{
			cout << "Enter the compressed URL which you want to decompress:\n> ";
			cin >> input;
			if(input.length() <= 20)
			{
				cout << "The prefix of the URL should be \"www.urlShortner.com/\"\n\n\n";
				continue;
			}
			string temp = "";
			for(int i=0;i<20;i++)
			{
				temp += input[i];
			}
			if(temp.compare(prefix)==0)
			{
				string input_suffix = "";
				for(int i=20;i<input.length();i++)
				{
					input_suffix += input[i];
				}
				output = urlShortner.Decode(input_suffix);
				string forcheck = "";
				if(output.compare(forcheck)==0)
				{
					cout << "This URL has not been compressed previously\n\n\n";
					continue;
				}
				cout << "Your Original URL is: \"" << output << "\"" << endl;
			}
			else
			{
				cout << "The prefix of the URL should be \"www.urlShortner.com/\"\n\n\n";	
				continue;	
			}
			
		}
		else if(command.compare(exit)==0)
		{
			cout << "**************************Thanks For Using URLShortner**************************\n";
			return 0;
		}
		else
		{
			cout << "Un-Recognisable Command\n";
		}
		cout << "\n\n";
	}
}
