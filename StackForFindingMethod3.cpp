#include<iostream>
#include<fstream>
#include<string>
#include<stack>

using namespace std;

int main()
{
    ifstream ifile("BubbleSort.cpp") ;

    string line,method[100],totalString;
    string stringOfFunction[10];
    char ch;
    int i=0;



	while(getline(ifile,line))
	{
		if(line.find("void") !=string::npos && line.find('(') !=string::npos && line.find(';') ==string::npos)
		{
            method[i]=line;

            i=i+1;
        }

        else if(line.find("int") !=string::npos && line.find('(') !=string::npos && line.find(';') ==string::npos)
		{
            method[i]=line;

            i=i+1;
        }

        else if(line.find("double") !=string::npos && line.find('(') !=string::npos && line.find(';') ==string::npos)
		{
            method[i]=line;

            i=i+1;
        }

        else if(line.find("bool") !=string::npos && line.find('(') !=string::npos && line.find(';') ==string::npos)
		{
            method[i]=line;

            i=i+1;
        }


	}

    ifile.close();

    fstream file;
    file.open( "BubbleSort.cpp", fstream::in | fstream::out | fstream::app );
    ofstream ofile("1.cpp");

    while(!file.eof())
    {
        char ch = file.get();
        totalString.push_back(ch);
    }

	int funcNumber;

    for(funcNumber=0;funcNumber<i;funcNumber++)
    {

        int found1[10];
        found1[funcNumber]=totalString.find(method[funcNumber]);

        stack <char> stack1;
        int found2[10];

        for(int i=found1[funcNumber];i<totalString.length();i++)
        {
            if(totalString[i]=='{')
            {
                  stack1.push(totalString[i]);
            }

            if(totalString[i]=='}')
            {
                stack1.pop();
                if(stack1.empty()==true)
                {
                    found2[funcNumber]=i;

                    break;
                }

            }

        }


        for(int i=found1[funcNumber];i<=found2[funcNumber];i++)
        {
            stringOfFunction[funcNumber]=stringOfFunction[funcNumber]+totalString[i];
        }

		cout << funcNumber+1 << "th founded function in the code." << endl <<endl;
    	cout << stringOfFunction[funcNumber] << endl;
        cout <<"...................." << endl;


    }

    string formation;
    formation="#include<bits/stdc++.h>\nusing namespace std;\n";

    stringOfFunction[0]=formation+stringOfFunction[0];
    for(int i=1;i<=funcNumber;i++)
    {
    	stringOfFunction[0]=stringOfFunction[0]+"\n"+stringOfFunction[i];
    }
    ofile<<stringOfFunction[0]<<endl;

    char filename[100];
    cout << "Enter the file name to compile :  " << endl;;
    cin.getline(filename, 100);

    //char filename[]="1.cpp";
    string str = "g++ ";
    str = str + " -o a " + filename;


    const char *command = str.c_str();

    system(command);

    system("./a");


    return 0;
}


