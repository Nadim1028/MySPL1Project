#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

using namespace std;

int min(int x, int y, int z)
{
	return min(min(x, y), z);
}

int editDistDP(string str1, string str2, int m, int n)
{

	int dp[m+1][n+1];


	for (int i=0; i<=m; i++)
	{
		for (int j=0; j<=n; j++)
		{

			if (i==0)
				dp[i][j] = j;

			else if (j==0)
				dp[i][j] = i;


			else if (str1[i-1] == str2[j-1])
				dp[i][j] = dp[i-1][j-1];


			else
				dp[i][j] = 1 + min(dp[i][j-1], // Insert
								dp[i-1][j], // Remove
								dp[i-1][j-1]); // Replace
		}
	}

	return dp[m][n];
}


int isKeyword(char buffer[])
{
	char keywords[32][9] = {"auto","break","case","char","const","continue","default",
							"do","double","else","enum","else if","float","for","goto",
							"if","int","long","register","return","short","signed",
							"sizeof","static","struct","switch","typedef","union",
							"unsigned","void","volatile","while"};
	int i, flag = 0;

	for(i = 0; i < 32; ++i)
	{
		if(strcmp(keywords[i], buffer) == 0)
		{
			flag = 1;
			break;
		}
	}

	return flag;
}

int isSpecialString(char buffer[])
{
	char keywords[9][10] = {"include","iostream","using","namespace","std","main","return"};
	int i, flag = 0;

	for(i = 0; i < 7; ++i)
	{
		if(strcmp(keywords[i], buffer) == 0)
		{
			flag = 1;
			break;
		}
	}

	return flag;
}

string token(ifstream& ifile)
{
	char ch, buffer[15], operators[] = "+-*/%=";
	string cat,cat2="K";
	int i,j=0,count=0,mount=0;



	if(!ifile.is_open())
	{
		cout<<"error while opening the file\n";
		exit(0);
	}

	while(!ifile.eof())
	{
   		ch = ifile.get();

   		if(isalnum(ch))
   		{
   			buffer[j++] = ch;
   		}

   		else if((ch == ' ' || ch == '\n' || ch =='(' || '{' || ')' || '}' || ',' || '<' || '>' || ';' || '[' || ']' || '*' || '+') && (j != 0))
   		{
   				buffer[j] = '\0';
   				j = 0;

   				if(isKeyword(buffer) == 1)
   				{
   					cat = cat + cat2;
   					count++;

   				}

   				else if(isSpecialString(buffer) == 0)
   				{


   						cat = cat + "I";

   						mount++;
   				}

   		}

   		for(i = 0; i < 6; ++i)
		{
   			if(ch == operators[i])
   			cat = cat + ch;

   		}


	}

		ifile.close();

	return cat;

}

int main()
{



	ifstream ifile("input3.cpp");
	ifstream ifile2("input2.cpp");

	string str1= token(ifile);
	string str2 = token(ifile2);
	cout << str1 << endl << str2 << endl;
	int p= editDistDP(str1, str2, str1.length(), str2.length()) ;
	cout << editDistDP(str1, str2, str1.length(), str2.length()) << endl;

	if(p==0)
		cout << "The codes are syntactically similar." << endl;
}

