#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
 
using namespace std;
 
int isKeyword(char buffer[])
{
	char keywords[32][10] = {"auto","break","case","char","const","continue","default",
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
	char keywords[9][10] = {"include","iostream","using","namespace","std","main","cin","cout","return"};
	int i, flag = 0;
	
	for(i = 0; i < 9; ++i)
	{
		if(strcmp(keywords[i], buffer) == 0)
		{
			flag = 1;
			break;
		}
	}
	
	return flag;
}

int isDigit(char buffer[])
{
	char keywords[9][5] = {"1","2","3","4","5","6","7","8","9"};
	int i, flag = 0;
	
	for(i = 0; i < 9; ++i)
	{
		if(strcmp(keywords[i], buffer) == 0)
		{
			flag = 1;
			break;
		}
	}
	
	return flag;
}
 
int main()
{
	char ch, buffer[15], operators[] = "+-*/%=";
	string cat,cat2="Key";
	
	ifstream fin("Input.txt");
	int i,j=0,count=0;
	
	if(!fin.is_open())
	{
		cout<<"error while opening the file\n";
		exit(0);
	}
	
	while(!fin.eof())
	{
   		ch = fin.get();
   		
		for(i = 0; i < 6; ++i)
		{
   			if(ch == operators[i])
   			cat = cat + ch;
   			//cout << ch << " is operator\n";
   		}
   			
   		
   		
   		if(isalnum(ch))
   		{
   			buffer[j++] = ch;
   		}
   		
   		else if((ch == ' ' || ch == '\n' || ch =='(' || '{' || ')' || '}' || ',' || '<' || '>' || ';' || '[' || ']' || '*' || '"') && (j != 0))
   		{
   				buffer[j] = '\0';
   				j = 0;
   				   				
   				if(isKeyword(buffer) == 1)
   				{
   					cat = cat + cat2;
   					count++;
   					//cout<< buffer <<" is A keyword\n";
   				}
   				
   				else if(isSpecialString(buffer) == 0)
   				{
   					if(isDigit(buffer)==1)
   					{
   						cat = cat + buffer;
   					}
   					
   					else
   						cat = cat + "id";
   				}
   					//cout << buffer <<" is identifier\n";
   		}
   		
	}
	
	cout << cat << endl;
	cout << count << endl;
	
	fin.close();
	
	return 0;
}
