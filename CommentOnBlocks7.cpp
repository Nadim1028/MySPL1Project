#include<iostream>
#include<fstream>
#include<string.h>

using namespace std;


int main()
{
	ifstream ifile("Input.txt");
    string line = "",initial[100],condition[100],whileCondition[100],whileInitial[100],doInitial[100],doCondition[100];
    int m=0,n=0,o=0,p=0,q=0,r=0;
    int is=-1,vs=-1,ds=-1;
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


                int a=indexOfVariable[variable1-1];

                for(int j=a; j>=0; j--)
                {
                    if(line[j]==var[variable1-1])
                    {
                    	int f=j;


                        if((line[j-1]<'a' || line[j-1]>'z') && (line[j+1]<'a' || line[j+1]>'z') )
                        {

                            while(1)
                			{
                   				if((line[f]>='0' && line[f]<='9'))
                        		{
                            		ini[k] = line[f];
                            		k++;
                        		}

                    			if(line[f]==',' || line[f]==';')
                        			break;

                    			else
                        			f++;
                			}

                        }

                    }

                }

                for(int j=0; j<k; j++)
                {

                    whileInitial[p].push_back(ini[j]);
                }
                p++;
                k=0;


                cout << endl;

            }
        }

    }

    int doCounter=0,doIndexOfVariable[100],doVariable1=0,doVariable2=0;
    int doIndexOfVariable2[100],doIov;
    char doVar[10];


    for(int i=0; i<line.length(); i++)
    {
        if((i+1)<line.length())
        {
            if(line[i]=='d' && line[i+1]=='o'&& (line[i+2]<'a' || line[i+2]>'z'))
            {
                doCounter++;
                i = i+3;

                while(1)
                {
                    if(line[i]=='w' && line[i+1]=='h' && line[i+2]=='i' && line[i+3]=='l' && line[i+4]=='e')
                    {
                        i = i+5;
                        while(1)
                        {
                            if(line[i]==')')
                            {
                                doIov=i;
                                break;
                            }

                            i++;
                        }

                        break;
                    }
                    i++;

                }

                while(1)
                {
                    if((line[i]>='0' && line[i]<='9'))
                    {
                        con[k] = line[i];
                        k++;
                    }

                    if(line[i]=='(')
                    {
                        doIndexOfVariable[doVariable1]=i;
                        doVariable1++;
                        break;
                    }

                    else
                        i--;
                }


                while(1)
                {

                    if((line[doIov]>='a' && line[doIov]<='z'))
                    {
                        doVar[doVariable2] = line[doIov];

                        doVariable2++;
                    }

                    if(line[doIov]=='(')
                        break;


                    else
                        doIov--;
                }



                for(int j=k-1; j>=0; j--)
                {
                    //cout << con[j] << endl;
                    doCondition[q].push_back(con[j]);
                }
                q++;
                k=0;

                cout << endl;
                int a=doIndexOfVariable[doVariable1-1];

                for(int j=a; j>=0; j--)
                {
                    if(line[j]==doVar[doVariable1-1])
                    {
                    	int f=j;


                        if((line[j-1]<'a' || line[j-1]>'z') && (line[j+1]<'a' || line[j+1]>'z') )
                        {

                            while(1)
                			{
                   				if((line[f]>='0' && line[f]<='9'))
                        		{
                            		ini[k] = line[f];
                            		k++;
                        		}

                    			if(line[f]==',' || line[f]==';')
                        			break;

                    			else
                        			f++;
                			}
                        }
                    }
                }

                for(int j=0; j<k; j++)
                {
                    //cout << ini[j] << endl;
                    doInitial[r].push_back(ini[j]);
                }
                r++;
                k=0;
                cout << endl;

            }
        }
    }

    int func,ifunctionCounter=0,dfunctionCounter=0,vfunctionCounter=0;
    char ifuncName[100],dfuncName[100],vfuncName[100];
    string ifunctions[100],dfunctions[100],vfunctions[100];
    for(int i=0; i<line.length(); i++)
    {
        if((i+4)<line.length())
        {
            if(line[i]=='i' && line[i+1]=='n' && line[i+2]=='t')
            {

                i=i+2;
                while(1)
                {
                    if(line[i]=='(')
                    {
                        is++;
                        ifunctionCounter++;
                        func=i;

                        while(1)
                        {
                            if((line[i]>='a' && line[i]<='z') ||(line[i]>='A' && line[i]<='Z') )
                            {
                                ifuncName[k] = line[i];
                                k++;
                            }

                            if(line[i]==' ')
                                break;

                            else
                                i--;
                        }

                        break;
                    }

                    if(line[i]==';' || line[i]==')')
                        break;

                    i++;

                }

                for(int j=k-1; j>=0; j--)
                {
                    //cout << ifuncName[j];
                    ifunctions[is].push_back(ifuncName[j]);
                }


                k=0;
                cout << endl;
            }
        }
    }

    for(int i=0; i<line.length(); i++)
    {
        if((i+4)<line.length())
        {

            if(line[i]=='v' && line[i+1]=='o' && line[i+2]=='i' && line[i+3]=='d')
            {

                i=i+3;
                while(1)
                {
                    if(line[i]=='(')
                    {
                        vs++;
                        vfunctionCounter++;
                        func=i;

                        while(1)
                        {
                            if((line[i]>='a' && line[i]<='z') ||(line[i]>='A' && line[i]<='Z') )
                            {
                                vfuncName[k] = line[i];
                                k++;
                            }

                            if(line[i]==' ')
                                break;

                            else
                                i--;
                        }

                        break;
                    }

                    if(line[i]==';')
                        break;

                    i++;

                }

                for(int j=k-1; j>=0; j--)
                {
                    //cout << vfuncName[j];
                    vfunctions[vs].push_back(vfuncName[j]);
                }


                k=0;
                cout << endl;
            }
        }
    }

    for(int i=0; i<line.length(); i++)
    {
        if((i+4)<line.length())
        {
            if(line[i]=='d' && line[i+1]=='o' && line[i+2]=='u' && line[i+3]=='b' && line[i+4]=='l' && line[i+5]=='e')
            {

                i=i+4;
                while(1)
                {
                    if(line[i]=='(')
                    {
                        ds++;
                        dfunctionCounter++;
                        func=i;

                        while(1)
                        {
                            if((line[i]>='a' && line[i]<='z') ||(line[i]>='A' && line[i]<='Z') )
                            {
                                dfuncName[k] = line[i];
                                k++;
                            }

                            if(line[i]==' ')
                                break;

                            else
                                i--;
                        }

                        break;
                    }

                    if(line[i]==';')
                        break;

                    i++;

                }

                for(int j=k-1; j>=0; j--)
                {
                    //cout << dfuncName[j];
                    dfunctions[ds].push_back(dfuncName[j]);
                }

                k=0;
                cout << endl;
            }
        }
    }


    ifile.close();
    fstream file;

    file.open( "Input.txt", fstream::in | fstream::out | fstream::app );
    ofstream ofile("Output.txt");


    string c1="//This is a for loop which starts with ",d2=" and ends with ";
    string d1="//This is a while loop which starts with ";
	string c2=" and ends with ",comment[100],newline,comment2[100],comment3[100],comment4[100];
	string comment5[100],comment6[100];
	string c3=".The for loop is incremental.",c4=".The for loop is decremental.";
	string e1="//This is a do while loop which starts with ",e2=" and ends with ";
	string f1="//This is a function.The name of the function is **" ,f2="**.The retrun type of the function is integer";
    string f3="**.The retrun type of the function is void",f4="**.The retrun type of the function is double";
    for(int n=0;n<forcounter;n++)
    {
        comment[n]=c1+initial[n]+c2+condition[n];
    }

    for(int m=0;m<whilecounter;m++)
    {
        comment2[m]=d1+whileInitial[m]+d2+whileCondition[m];
    }

    for(int m=0;m<doCounter;m++)
    {
        comment3[m]=e1+doInitial[m]+e2+doCondition[m];
    }

    for(int n=0;n<ifunctionCounter;n++)
    {
        comment4[n]=f1+ifunctions[n]+f2;

    }


    for(int n=0;n<vfunctionCounter;n++)
    {
        comment5[n]=f1+vfunctions[n]+f3;
    }

    for(int n=0;n<dfunctionCounter;n++)
    {
        comment6[n]=f1+dfunctions[n]+f4;
    }

    int x=0,y=0,z=0;
    int iu=0,vu=0,du=0;
    int iv=0,vv=0,dv=0;

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

        if(newline.find("while") !=string::npos && newline.find(";") ==string::npos)
        {
            newline.append(comment2[y++]);
        }

        if(newline.find("do") !=string::npos && newline.find("u") ==string::npos && newline.find(";") ==string::npos && newline.find("(") ==string::npos)
        {
            newline.append(comment3[z++]);
        }

        if(newline.find(ifunctions[iu]) !=string::npos)
        {
            newline.append(comment4[iv++]);

            iu=iu+1;
        }

        if(newline.find(vfunctions[vu]) !=string::npos)
        {
            newline.append(comment5[vv++]);

            vu=vu+1;
        }

        if(newline.find(dfunctions[du]) !=string::npos)
        {
            newline.append(comment6[dv++]);

            du=du+1;
        }

        ofile << newline <<endl;
    }


	return 0;
}



