#include<iostream>
#include<fstream>

using namespace std;

int main()
{
	ifstream ifile("one.txt");
	ofstream ofile("3.txt");
	string line;
	
	while(getline(ifile,line))
	{
		if(line.find("for") !=string::npos && line.find("++") !=string::npos)
		{
			 line.append("  //this is a for loop and the variable  is increasing");
		}
		
		else if(line.find("for") !=string::npos && line.find("--") !=string::npos)
		{
			 line.append("  //this is a for loop and the variable is decreasing");
		}
		
		ofile << line <<endl;
	
	}
	
	
	return 0;
}
