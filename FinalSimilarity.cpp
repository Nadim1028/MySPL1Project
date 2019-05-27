#include<iostream>
#include<fstream>

using namespace std;

int minimum(int p,int q,int r)
{
    int m;
    if(p<r && p<r)
        m=p;

    else if(q<p && q<r)
        m=q;

    else
        m=r;

	return m;
}

int editDistance(string str1,string str2,int len1,int len2)
{
	int dp[len1+1][len2+1];


	for (int i=0; i<=len1; i++)
	{
		for (int j=0; j<=len2; j++)
		{

			if (i==0)
				dp[i][j] = j;

			else if (j==0)
				dp[i][j] = i;


			else if (str1[i-1] == str2[j-1])
				dp[i][j] = dp[i-1][j-1];


			else
				dp[i][j] = 1 + minimum(dp[i][j-1],
								dp[i-1][j],
								dp[i-1][j-1]);
		}
	}

	return dp[len1][len2];
}

int stringLength(char *str)
{
	int i, length = 0;
	for (i = 0; str[i] != '\0'; i++)
	{

        length++;
	}

	return length;
}

int stringCompare(char s1[],char s2[])
{
	int i=0,flag=1;


	while( (s1[i] != '\0' || s2[i] != '\0'))
	{
		if(stringLength(s1)==stringLength(s2))
		{
			if(s1[i] == s2[i])
			{
			flag=0;
			}
		}

		else
			flag=1;

	  	i++;
	}
        return flag;
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
		if(stringCompare(keywords[i], buffer) == 0)
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
		if(stringCompare(keywords[i], buffer) == 0)
		{
			flag = 1;
			break;
		}
	}

	return flag;
}

int alphaNumeric(char c)
{
    if((c>=65 && c<=90) || (c>=97 && c<=122))
        return 0;

    else if(c>=48 && c<=57)
        return 0;

    else
        return 1;
}

string token(ifstream& ifile)
{
	char ch, temp[15], operators[] = "+-*/%=";
	string cat,cat2="K";
	int i,j=0,count=0,mount=0;

	if(!ifile.is_open())
	{
		cout<<"Finding error while opening the file" << endl;
    }

	while(!ifile.eof())
	{
   		ch = ifile.get();

   		if(alphaNumeric(ch)==0)
   		{
   			temp[j++] = ch;
   		}

   		else if((ch == ' ' || ch == '\n' || ch =='(' || '{' || ')' || '}' || ',' || '<' || '>' || ';' || '[' || ']' || '*' || '+') && (j != 0))
   		{
   				temp[j] = '\0';
   				j = 0;

   				if(isKeyword(temp) == 1)
   				{
   					cat = cat + cat2;
   					count++;

   				}

   				else if(isSpecialString(temp) == 0)
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

	int p= editDistance(str1, str2, str1.length(), str2.length());

	cout << editDistance(str1, str2, str1.length(), str2.length()) << endl;

	if(p==0)
		cout << "The codes are syntactically similar." << endl;

}


