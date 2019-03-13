#include <bits/stdc++.h>
//#include<stdlib.h>

using namespace std;

FILE *fp , *fp2;


void quotation_comment()
{
	char m,n;
		while((m=fgetc(fp)) != EOF)
    	{

        	if(m == '<' || m == '"')
        	{
            	n=fgetc(fp);

            	if(n == '<' || n == ';')
                	return;
        	}
        }
}

void check_quotation(char c)
{
	char d,e;

    if(c == '<')
    {
    	if((d=fgetc(fp)) == '<')
    	{
    		while((e=fgetc(fp)) != EOF)
    		{
    			if(e == '"')
        		{

            		quotation_comment();
            		return;
            	}

				else
				{

					fputc(e,fp2);
    			}
    		}
    	}

    	else if(d != '<')
    	{
    		fputc(c,fp2);
    		fputc(d,fp2);
    	}

    	else
    	{
    		fputc(c,fp2);
    		fputc(d,fp2);
    		fputc(e,fp2);
    	}
    }
}

void single_comment()
{
	char d,e;

    while((d=fgetc(fp)) != EOF)
    {

        if(d == '\n')
            return;
	}
}

void block_comment()
{
	char d,e;

    while((d=fgetc(fp)) != EOF)
    {
        if(d == '*')
        {
            e=fgetc(fp);

            if(e == '/')
                return;
        }
   }
}

void check_comment(char c)
{
    char d,e;

	if( c == '/')
    {
        if((d=fgetc(fp)) == '*')
        	block_comment();

        else if( d == '/')
        {
        	single_comment();

        }

        else
        {

            fputc(c,fp2);
            fputc(d,fp2);
        }
    }

    else
        fputc(c,fp2);
}

int main(void)
{
    char c,d;
    fp = fopen ("Input.txt","r") ;
    fp2 = fopen ("freshCode.txt","w") ;

    while((c=fgetc(fp)) != EOF)
    {
        check_comment(c);
            check_quotation(c);



    }


    fclose(fp);
    fclose(fp2);

    return 0;
}






