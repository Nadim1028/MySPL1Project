#include<iostream>
#include<fstream>
#include<string.h>

using namespace std;
int main()
{


    ifstream ifile("Input.txt");
    string line = "",initial[100],condition[100],whileCondition[100],whileInitial[100];
    int m=0,n=0,o=0,p=0;

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

    int whilecounter = 0,indexOfVariable[100],variable1=0,variable2=0;
    int indexOfVariable2[100];
    char var[10];

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
                int iov=i;

                while(1)
                {
                    if((line[i]>='0' && line[i]<='9'))
                    {
                        con[k] = line[i];
                        k++;
                    }


                    if(line[i]=='(')
                    {
                        indexOfVariable[variable1]=i;
                        cout << indexOfVariable[variable1] << endl;
                        variable1++;
                         break;
                    }

                    else
                        i--;
                }


                while(1)
                {

                    if((line[iov]>='a' && line[iov]<='z'))
                    {
                        var[variable2] = line[iov];
                        cout << var[variable2] << endl;
                        variable2++;
                    }

                    if(line[iov]=='(')
                    break;


                    else
                        iov--;
                }



                for(int j=k-1; j>=0; j--)
                {
                    whileCondition[o].push_back(con[j]);
                }
                o++;
                k=0;

                //cout << variable1 << " " << variable2 << endl;
                int a=indexOfVariable[variable1-1];

                for(int j=a; j>=0; j--)
                {
                    if(line[j]==var[variable1-1])
                    {
                        if(j<indexOfVariable2[variable1-1])
                            indexOfVariable2[variable1-1]=j;

                    }

                }
                cout << endl;

            }
        }

    }

    ifile.close();
    fstream file;

    file.open( "Input.txt", fstream::in | fstream::out | fstream::app );
    ofstream ofile("Output.txt");


    string c1= "//This is a for loop which starts with ",d2="//This is a while loop which ends with ";
	string c2=" and ends with ",comment[100],newline,comment2[100];
	string c3=".The for loop is incremental.",c4=".The for loop is decremental.";

    for(int n=0;n<forcounter;n++)
    {
        comment[n]=c1+initial[n]+c2+condition[n];
    }

    for(int m=0;m<whilecounter;m++)
    {
        comment2[m]=d2+whileCondition[m];
    }

    int x=0,y=0;

    while(getline(file,newline))
    {
        if(newline.find("for") !=string::npos && newline.find("++") !=string::npos)
        {
            newline.append(comment[x++]);
            newline.append(c3);
        }

        if(newline.find("for") !=string::npos && newline.find("--") !=string::npos)
        {
            newline.append(comment[x++]);
            newline.append(c4);
        }

        if(newline.find("while") !=string::npos)
        {
            newline.append(comment2[y++]);
        }

        ofile << newline <<endl;
    }



    return 0;
}


