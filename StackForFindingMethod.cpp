#include<iostream>
#include<fstream>
#include<string>
#include<stack>

using namespace std;

int main()
{
    ifstream ifile("Input.txt");
    ofstream ofile("Output.txt");

    string line,method[100],totalString;
    char ch;
    int i=0;



	while(getline(ifile,line))
	{
		if(line.find("void") !=string::npos && line.find('(') !=string::npos && line.find(';') ==string::npos)
		{
            method[i]=line;

            ofile << method[i] <<endl;
            i=i+1;
        }

        else if(line.find("int") !=string::npos && line.find('(') !=string::npos && line.find(';') ==string::npos)
		{
            method[i]=line;

            ofile << method[i] <<endl;
            i=i+1;
        }

        else if(line.find("double") !=string::npos && line.find('(') !=string::npos && line.find(';') ==string::npos)
		{
            method[i]=line;

            ofile << method[i] <<endl;
            i=i+1;
        }

        else if(line.find("bool") !=string::npos && line.find('(') !=string::npos && line.find(';') ==string::npos)
		{
            method[i]=line;

            ofile << method[i] <<endl;
            i=i+1;
        }


	}

    ifile.close();

    fstream file;
    file.open( "Input.txt", fstream::in | fstream::out | fstream::app );

    while(!file.eof())
    {
        char ch = file.get();
        totalString.push_back(ch);
    }


    for(int l=0;l<i;l++)
    {
    //cout << method[l] << endl;

        int found1[10];
        found1[l]=totalString.find(method[l]);



        stack <char> stack1;
        int found2[10];

        for(int i=found1[l];i<totalString.length();i++)
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
                    found2[l]=i;
                    //cout << " Last index = " << found2[l] << endl;
                    break;
                }

            }

        }

        string st1[10];

        for(int i=found1[l];i<=found2[l];i++)
        {
            st1[l]=st1[l]+totalString[i];
        }


        cout << st1[l] << endl;
        cout <<"...................." << endl;
    }
    return 0;
}

/*
Client ID
48d128ef7769d21edb5905c71c6622b1
Client Secret
f98b4029ce7c1415f6d489f20ad843c868808be1f94eb0b45a7896535b78d6f6

*/
