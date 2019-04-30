#include<bits/stdc++.h>
#include<fstream>
#include<string>
#include<stack>

using namespace std;

int main()
{
    ifstream ifile("Input.cpp") ;
    string line,functionSign[100],totalString;
    string stringOfFunction[10];
    char ch;
    int i=0,funcCounter=0;

	while(getline(ifile,line))
	{
		if(line.find("void") !=string::npos && line.find('(') !=string::npos && line.find(';') ==string::npos)
		{
            functionSign[i]=line;
            funcCounter++;
            i=i+1;
        }

        else if(line.find("int") !=string::npos && line.find('(') !=string::npos && line.find(';') ==string::npos)
		{
            functionSign[i]=line;
            funcCounter++;
            i=i+1;
        }

        else if(line.find("double") !=string::npos && line.find('(') !=string::npos && line.find(';') ==string::npos)
		{
            functionSign[i]=line;
            funcCounter++;
            i=i+1;
        }

        else if(line.find("bool") !=string::npos && line.find('(') !=string::npos && line.find(';') ==string::npos)
		{
            functionSign[i]=line;
            funcCounter++;
            i=i+1;
        }
	}

    ifile.close();

    fstream file;
    file.open( "Input.cpp", fstream::in | fstream::out | fstream::app );
    ofstream ofile("Output.cpp");

    while(!file.eof())
    {
        char ch = file.get();
        totalString.push_back(ch);
    }

	int funcNumber;

    for(funcNumber=0;funcNumber<i;funcNumber++)
    {
        int found1[10];
        found1[funcNumber]=totalString.find(functionSign[funcNumber]);

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
    	//cout << stringOfFunction[funcNumber] << endl;
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

    for(int i=0;i<funcCounter;i++)
    {
    	cout << functionSign[i] << endl;
    }

    string p=functionSign[0],funcPara[100];
    char stringForPara[100];
    int sfp=0,pc=0;
    cout << p.length() << endl;
    for(int i=0;i<p.length();i++)
    {
    	if((p[i]>=65 && p[i]<=90) || (p[i]>=97 && p[i]<=122))
        {
            stringForPara[sfp]=p[i];
            sfp++;
        }

        else if(p[i]==' ' || p[i]=='(' || p[i]==',' || p[i]==')')
        {
            for(int j=0;j<sfp;j++)
            {
                funcPara[pc].push_back(stringForPara[j]);
            }
            pc++;
            cout << sfp << endl;
            sfp=0;

        }
    }

    for(int i=0;i<pc;i++)
    {
        cout << funcPara[i] << endl;
    }
    
    string funcMaker=funcPara[1]+'(';
    for(int i=1;i<pc;i=i+2)
    {
          funcMaker=funcMaker+funcPara[i]+',';
    }
    
    funcMaker=funcMaker+");";
    
    cout << funcMaker << endl;

    char filename[100];
    cout << "Enter the file name to compile :  " << endl;;
    cin.getline(filename, 100);

    //char filename[]="1.cpp";
    string str = "g++ ";
    str = str + " -o a.out " + filename;

    const char *command = str.c_str();
    system(command);
    system("./a.out");

    return 0;
}


