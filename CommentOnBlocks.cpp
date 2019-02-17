#include<iostream>
#include<fstream>

using namespace std;

int main()
{
	ifstream ifile("Input.txt");
	ofstream ofile("OutputFile.txt");
	string line;
	
	while(getline(ifile,line))
	{
		if(line.find("for") !=string::npos && line.find("++") !=string::npos)
		{
			 line.append("  //This is a for loop and the loop  is increamental");
		}
		
		else if(line.find("for") !=string::npos && line.find("--") !=string::npos)
		{
			 line.append("  //This is a for loop and the loop is decreamental");
		}
		
		
		else if(line.find("else") !=string::npos && line.find("if") !=string::npos)
		{
			line.append("//This is a ELSE IF condition");
		}
		
		else if(line.find("if") !=string::npos)
		{
			line.append("//This is a IF condition");
		}
		
		else if(line.find("else") !=string::npos)
		{
			line.append("//This is a ELSE condition");
		}
		
		else if(line.find("while") !=string::npos)
		{
			line.append("//This is a while loop");
		}
		
		
		
		
		ofile << line <<endl;
	
	}
	
	
	return 0;
}
