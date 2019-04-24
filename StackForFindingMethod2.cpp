#include<iostream>
#include<fstream>
#include<string>
#include<stack>

using namespace std;

int main()
{
    ifstream ifile("1.cpp");
    ofstream ofile("2.cpp");

    string line,method[100],totalString;
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
    file.open( "1.cpp", fstream::in | fstream::out | fstream::app );

    while(!file.eof())
    {
        char ch = file.get();
        totalString.push_back(ch);
    }


    for(int l=0;l<i;l++)
    {
  
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
                    
                    break;
                }

            }

        }

        string st1[10];

        for(int i=found1[l];i<=found2[l];i++)
        {
            st1[l]=st1[l]+totalString[i];
        }


        //cout << st1[l] << endl;
        cout <<"...................." << endl;
        
        string formation;
        formation="#include<iostream>\nusing namespace std;\n";
        
        st1[0]=formation+st1[0];
        ofile<<st1[0]<<endl;
    }
    
    char filename[100]; 
    cout << "Enter the file name to compile :  " << endl;; 
    cin.getline(filename, 100); 
  
    
    string str = "g++ "; 
    str = str + " -o a.out " + filename; 
  
    
    const char *command = str.c_str(); 
  
    system(command); 
  
    system("./a.out"); 
    

    return 0;
}


