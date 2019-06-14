#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <iomanip>
#include <fstream>
using namespace std;

int main()
{
	ofstream myfile;
  	myfile.open ("urlshortner_output.txt");
	map<int, char> lookup;
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
	for(long long int input_no=0; input_no<10000; input_no++)
	{
		float t = clock(); 
		string shortURL = "";
		long long int key = input_no;
		while(key > 0)
		{
			int modulo = key%62;
			key /= 62;
			shortURL += lookup[modulo];
		}
		reverse(shortURL.begin(), shortURL.end());
		myfile << input_no << " " << std::fixed << std::setprecision(9) << (clock() - t) / CLOCKS_PER_SEC << endl;
	}
}