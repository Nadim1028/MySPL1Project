#include <iostream>
#include <fstream>

using namespace std;


bool identifierChecker(string s)
{
    bool flag=false;

    if((s[0]>='0' && s[0]<='9'))
    {
        return false;
    }

    for(int i=0; i<s.size(); i++)
    {
        if(((s[i]>='A' && s[i]<='Z')||(s[i]>='a' && s[i]<='z')||s[i]=='_'||(s[i]>='0' && s[i]<='9')))
        {
            flag = true;
        }
        else
        {
            flag = false;
            break;
        }
    }

    if(flag==true)
        return true;
    else
        return false;

}

bool returnFinder(string s)
{
    if(s=="return")
        return true;
}

bool floatChecker(string s)
{
    int flag1=0, flag2=0;

    for(int i=0; i<s.size(); i++)
    {
        if((s[i]>='0' && s[i]<='9') || s[i]=='.')
            flag1=1;
        else
        {
            flag1=0;
            break;
        }
        if(s[i]=='.')
            flag2++;
    }

    if(flag1==1 && flag2==1)
        return true;
}

bool intChecker(string s)
{
    bool flag=false;

    for(int i=0; i<s.size(); i++)
    {
        if(s[i]>='0' && s[i]<='9')
            flag=true;
        else
        {
            flag=false;
            break;
        }
    }

    if(flag==true)
        return true;
    else
        return false;

}

bool boolChecker(string s)
{
    if(s=="true" || s=="false")
        return true;

    else
        return false;
}

int if_elseFinder(string s)
{
    if(s=="if")
        return 0;

    else if(s=="else")
        return 1;
}

bool breakFinder(string s)
{
    if(s=="break")
        return true;
}

bool dataTypeFinder(string s)
{
    if(s=="void" || s=="bool" || s=="int" || s=="float" || s=="double")
        return true;
}

int main()
{
    char ch;
    int tokentCounter=0;
    string s="";
    ifstream ifile;
    ofstream ofile;
    ifile.open("1.txt");
    ofile.open("Lexing.txt");

    if(ifile.is_open())
    {
        cout << "The Lexical Analysis file has been opened" << endl;

        int string_flag=-1;
        char previousChar='?';
        ifile.get(ch);

        while(true)
        {
            if(ch=='\n'||ch=='\t'||ch==' ')
            {
                if(dataTypeFinder(s)==true)
                {
                    ofile << s << " dataType" << endl;
                    ifile.get(ch);
                    tokentCounter++;
                    s = "";
                    break;
                }

                if(s[0]=='#' && s[s.size()-1]=='>')
                {
                    ofile << s << " header_file" << endl;
                    tokentCounter++;
                }

                s="";
            }

            else
            {
                if(ch=='#')
                    s=s+(char)35;

                else
                    s=s+ch;
            }

            ifile.get(ch);
        }

        while(!ifile.eof())
        {
            if(ch==',' || ch==';' || ch==' ' || ch=='=' || ch=='\n' || ch=='\t' || ch=='('|| ch==')' || ch=='{'|| ch=='}'|| ch=='"'|| ch==']'|| ch=='['|| ch=='+'|| ch=='-'|| ch=='*'|| ch=='/'|| ch=='%'|| ch=='<'|| ch=='>'||ch=='!')
            {
                if(dataTypeFinder(s)==true)
                {
                    ofile << s << " dataType" << endl;
                    s = "";
                    tokentCounter++;
                }
                else if(breakFinder(s)==true)
                {
                    ofile << s << " BREAK" << endl;
                    s = "";
                    tokentCounter++;
                }
                else if(if_elseFinder(s)==0)
                {
                    ofile << s << " IF" << endl;
                    s = "";
                    tokentCounter++;
                }
                else if(if_elseFinder(s)==1)
                {
                    ofile << s << " ELSE" << endl;
                    s = "";
                    tokentCounter++;
                }
                else if(boolChecker(s)==true)
                {
                    ofile << s << " BOOL_LIT" << endl;
                    s = "";
                    tokentCounter++;
                }
                else if(floatChecker(s)==true)
                {
                    ofile << s << " FLOAT_LIT" << endl;
                    s = "";
                    tokentCounter++;
                }
                else if(intChecker(s)==true)
                {
                    ofile << s << " INT_LIT" << endl;
                    s = "";
                    tokentCounter++;
                }
                else if(returnFinder(s)==true)
                {
                    ofile << s << " RETURN" << endl;
                    s = "";
                    tokentCounter++;
                }
                else if(identifierChecker(s)==true)
                {
                    ofile << s << " IDENT" << endl;
                    s = "";
                    tokentCounter++;
                }
                if(ch=='"')
                {
                    s=s+'"';
                    previousChar = ch;
                    ifile.get(ch);

                    while(ch!='"')
                    {
                        s = s+ch;
                        previousChar = ch;
                        ifile.get(ch);
                    }

                    ofile << s << ch << " STRING_LITERAL" << endl;
                }
                if(ch==';')
                {
                    tokentCounter++;
                    ofile << ch << " SEMICOLON" << endl;
                    s = "";
                }
                if(ch==',')
                {
                    tokentCounter++;
                    ofile << ch << " COMA" << endl;
                    s = "";
                }
                if(ch=='(')
                {
                    tokentCounter++;
                    ofile << ch << " FIRST_BRACKET_OPEN" << endl;
                    s = "";
                }
                if(ch==')')
                {
                    tokentCounter++;
                    ofile << ch << " FIRST_BRACKET_CLOSE" << endl;
                    s = "";
                }
                if(ch=='{')
                {
                    tokentCounter++;
                    ofile << ch << " SECOND_BRACKET_OPEN" << endl;
                    s = "";
                }
                if(ch=='}')
                {
                    tokentCounter++;
                    ofile << ch << " SECOND_BRACKET_CLOSE" << endl;
                    s = "";
                }
                if(ch=='[')
                {
                    tokentCounter++;
                    ofile << ch << " THIRD_BRACKET_OPEN" << endl;
                    s = "";
                }
                if(ch==']')
                {
                    tokentCounter++;
                    ofile << ch << " THIRD_BRACKET_CLOSE" << endl;
                    s = "";
                }
                if(ch=='+')
                {
                    tokentCounter++;
                    ofile << ch << " ADD" << endl;
                    s = "";
                }
                if(ch=='-')
                {
                    tokentCounter++;
                    ofile << ch << " SUBTRACT" << endl;
                    s = "";
                }
                if(ch=='*')
                {
                    tokentCounter++;
                    ofile << ch << " MULTIPLICATION" << endl;
                    s = "";
                }
                if(ch=='/')
                {
                    tokentCounter++;
                    ofile << ch << " DIVISION" << endl;
                    s = "";
                }
                if(ch=='%')
                {
                    tokentCounter++;
                    ofile << ch << " MODULUS" << endl;
                    s = "";
                }
                if(ch=='<')
                {
                    tokentCounter++;
                    ofile << ch << " LESSER" << endl;
                    s = "";
                }
                if(ch=='>')
                {
                    tokentCounter++;
                    ofile << ch << " GREATER" << endl;
                    s = "";
                }
                if(ch=='!')
                {
                    tokentCounter++;
                    ofile << ch << " NOT" << endl;
                    s = "";
                }
            }

            else
                s = s + ch;

            previousChar = ch;
            ifile.get(ch);

            if(ch=='=' && previousChar=='=')
            {
                tokentCounter++;
                ofile << previousChar << ch << " " << "EQ" << endl;
                s = "";
            }
            else if(ch=='='&&previousChar=='!')
            {
                tokentCounter++;
                ofile << previousChar << ch << " " << "NE" << endl;
                s = "";
            }
            else if(ch=='='&&previousChar=='>')
            {
                tokentCounter++;
                ofile << previousChar << ch << " " << "GE" << endl;
                s = "";
            }
            else if(ch=='='&&previousChar=='<')
            {
                tokentCounter++;
                ofile << previousChar << ch << " " << "LE" << endl;
                s = "";
            }
            else if(ch!='='&&previousChar=='=')
            {
                tokentCounter++;
                ofile << "= " << "ASSIGNMENT" << endl;
                s = "";
            }

        }

    }
    else cout << "File did not open" << endl;

    cout << tokentCounter << endl;

    ifile.close();
    ofile.close();

    return 0;
}

