#include<iostream>
#include<fstream>>

using namespace std;

void quotation_comment(FILE *file1 ,FILE *file2)
{
	char m,n;
		while((m=fgetc(file1)) != EOF)
    	{

        	if(m == '<' || m == '"')
        	{
            	n=fgetc(file1);

            	if(n == '<' || n == ';')
                	return;
        	}
        }
}

void check_quotation(char c,FILE *file1 ,FILE *file2)
{
	char d,e;

    if(c == '<')
    {
    	if((d=fgetc(file1)) == '<')
    	{
    		while((e=fgetc(file1)) != EOF)
    		{
    			if(e == '"')
        		{

            		quotation_comment(file1,file2);
            		return;
            	}

				else
				{

					fputc(e,file2);
    			}
    		}
    	}

    	else if(d != '<')
    	{
    		fputc(c,file2);
    		fputc(d,file2);
    	}

    	else
    	{
    		fputc(c,file2);
    		fputc(d,file2);
    		fputc(e,file2);
    	}
    }
}


void single_comment(FILE *file1 ,FILE *file2)
{
	char d,e;

    while((d=fgetc(file1)) != EOF)
    {

        if(d == '\n')
            return;
	}
}

void block_comment(FILE *file1 ,FILE *file2)
{
	char d,e;

    while((d=fgetc(file1)) != EOF)
    {
        if(d == '*')
        {
            e=fgetc(file1);

            if(e == '/')
                return;
        }
   }
}

void check_comment(char c,FILE *file1 ,FILE *file2)
{
    char d,e;

	if( c == '/')
    {
        if((d=fgetc(file1)) == '*')
        	block_comment(file1,file2);

        else if( d == '/')
        {
        	single_comment(file1,file2);

        }

        else
        {

            fputc(c,file2);
            fputc(d,file2);
        }
    }

    else
        fputc(c,file2);
}

int main(void)
{
    FILE *file1 , *file2;

    char c,d;
    file1 = fopen ("Input.txt","r") ;
    file2 = fopen ("Output.txt","w") ;

    while((c=fgetc(file1)) != EOF)
    {
        check_comment(c,file1,file2);
            //check_quotation(c);
    }


    fclose(file1);
    fclose(file2);

    return 0;
}
