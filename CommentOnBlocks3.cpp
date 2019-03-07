#include<iostream>
#include<fstream>
#include<string.h>

using namespace std;
int main()
{


    ifstream ifile("Input.txt");
    string line = "",initial[100],condition[100];
    int m=0,n=0;

    while(!ifile.eof())
        {
            char ch = ifile.get();
            line.push_back(ch);
        }

    char ini[10];
    char con[10];
    int k=0;

    int forcounter = 0;

    for(int i=0; i<line.length(); i++)
    {
        if((i+2)<line.length())
        {
            if(line[i]=='f' && line[i+1]=='o' && line[i+2]=='r')
            {
                forcounter++;
                i = i+3;
                int sem;

                while(1)
                {
                    if(line[i]==';')
                    {
                        sem = i;
                        break;
                    }

                    i++;
                }


                while(1)
                {
                    if((line[i]>='0' && line[i]<='9'))
                        {
                            ini[k] = line[i];
                            k++;
                        }

                    if(line[i]=='(')
                        break;

                    else
                        i--;
                }


                for(int j=k-1; j>=0; j--)
                {


                        initial[m].push_back(ini[j]);

                }
                m++;

                k=0;
                i = sem+1;

                while(1)
                {
                    if(line[i]==';')
                    {
                        sem = i;
                        break;
                    }

                    i++;
                }

                i--;


                while(1)
                {
                    if((line[i]>='0' && line[i]<='9'))
                        {
                            con[k] = line[i];
                            k++;
                        }

                    if(line[i]==';')
                        break;

                    else
                        i--;
                }


                for(int j=k-1; j>=0; j--)
                {
                    condition[n].push_back(con[j]);
                }
                n++;


                cout << endl;

                k=0;

            }
        }
    }

    int whilecounter = 0;

    for(int i=0; i<line.length(); i++)
    {
        if((i+4)<line.length())
        {
            if(line[i]=='w' && line[i+1]=='h' && line[i+2]=='i' && line[i+3]=='l' && line[i+4]=='e')
            {
                whilecounter++;
                i = i+5;

                while(1)
                {
                    if(line[i]==')')
                        break;

                    i++;

                }


                while(1)
                {
                    if((line[i]>='0' && line[i]<='9'))
                        {
                            ini[k] = line[i];
                            k++;
                        }

                    if(line[i]=='(')
                        break;

                    else
                        i--;
                }

                cout << "Ini for WHILELoop " << whilecounter << " = ";
                for(int j=k-1; j>=0; j--)
                    cout << ini[j];

                k = 0;

                cout << endl;

            }
        }
    }

    ifile.close();
    fstream file;

    file.open( "Input.txt", fstream::in | fstream::out | fstream::app );
    ofstream ofile("Output.txt");


    string c1= "//This is a for loop which starts with ";
	string c2=" and end with ",comment[4],newline;

    for(int n=0;n<forcounter;n++)
    {
        comment[n]=c1+initial[n]+c2+condition[n];
    }


        int x=0;

        while(getline(file,newline))
        {
            if(newline.find("for") !=string::npos)
            {
                newline.append(comment[x++]);
            }

            ofile << newline <<endl;
        }


    return 0;
}

