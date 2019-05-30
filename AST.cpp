#include <bits/stdc++.h>

using namespace std;

struct node{
    string data;
    node* parent;
    vector <struct node*> children;
};

void PreOrder(node* treeNode);
void program();
void ListOfDeclaration();
bool declaration();
bool declarationOfVariable();
void data_type();
void function_declaration();
bool parameters();
bool Printing_Parameters();
bool param_list();
bool param_list_print();
bool param();
bool param_print();
bool listOfStatement();
bool PrintStatementList();
bool statement();
bool print_statement();
bool expressionStatement();
bool printExpressionStatement();
bool while_stmt();
bool while_stmt_print();
bool compound_stmt();
bool compound_stmt_print();
bool local_decls();
bool local_decls_print();
bool local_decl();
bool local_decl_print();
bool if_stmt();
bool if_stmt_print();
bool return_stmt();
bool return_stmt_print();
bool break_stmt();
bool break_stmt_print();
bool expression();
bool expr_print();
bool arglist();
bool args();

int success=0;
node* leaf = new node;
node* root = new node;
node* decl_list_leaf = new node;
node* function_decl_leaf = new node;

node* create_newNode(string data)
{
    node* temp = new node;
    temp->data = data;
    temp->parent = NULL;
    return temp;
}

int i=0;
ifstream ifile;
ofstream ofile;

string untokenedArray[500];
int filled_untokened_upto=0;

string tokenedArray[500];
int filled_tokened_upto=0;

int main()
{
    ifile.open("LexingOutput.txt");
    if(ifile.is_open())
    {
        cout << "The File has been opened" << endl;

        string untokened, tokened;

        while(!ifile.eof())
        {
            ifile >> untokened >> tokened;

            untokenedArray[filled_untokened_upto]=untokened;
            filled_untokened_upto++;

            tokenedArray[filled_tokened_upto]=tokened;
            filled_tokened_upto++;
        }

    }
    else
    {
        cout << "The file has not opened" << endl;
    }

    if(tokenedArray[i]=="header_file") program();

    if(success==1)
    {
        cout << endl << "Abstract Syntax Tree Traversal in Pre-Order:" << endl << endl;
        PreOrder(root);
    }

    return 0;
}

void PreOrder(node* treeNode)
{
    cout << treeNode->data << endl;

    int size = treeNode->children.size();

    if(size==0) return;
    int i=0;
    while(i < size)
    {
        PreOrder(treeNode->children[i]);
        i++;
    }

}

void program()
{
    leaf = root;
    leaf->data="Program_Starting";
    leaf->parent=NULL;

    i++;

    while(true)
    {
        if(tokenedArray[i]=="header_file")
        {
            i++;
        }
        else
        {
            ListOfDeclaration();
            break;
        }
    }
}

int decl_list_flag=0;
int z=0;
void ListOfDeclaration()
{
    if(decl_list_flag==0)
    {
        vector <node*> tempVec;
        node* temp = create_newNode("declaration_list");
        tempVec.push_back(temp);
        leaf->children=tempVec;
        temp->parent=leaf;

        decl_list_leaf = temp;
        decl_list_flag=1;
    }

    leaf = decl_list_leaf;

    if(declaration()==false)
    {
        decl_list_flag=0;
        return;
    }

    ListOfDeclaration();
}

bool declaration()
{
    if(tokenedArray[i]=="data_type" && tokenedArray[i+1]=="Identifier" && (tokenedArray[i+2]=="SEMICOLON"||tokenedArray[i+2]=="OpeningFirstBracket"))
    {
        if(tokenedArray[i+2]=="SEMICOLON")
        {
            leaf = decl_list_leaf;

            vector <node*> tempVec;
            node* temp = create_newNode("declaration");
            tempVec.push_back(temp);
            leaf->children.insert(leaf->children.end(),tempVec.begin(),tempVec.end());
            temp->parent=leaf;

            leaf = tempVec[0];
            declarationOfVariable();
            i++;
            return true;
        }
        else if(tokenedArray[i+2]=="OpeningFirstBracket")
        {
            vector <node*> tempVec;
            node* temp = create_newNode("declaration");
            tempVec.push_back(temp);
            leaf->children.insert(leaf->children.end(),tempVec.begin(),tempVec.end());
            temp->parent=leaf;

            leaf = tempVec[0];
            i=i+3;
            function_declaration();
            return true;
        }
    }
    else
    {
        return false;
    }
}

bool declarationOfVariable()
{
    node* temp = create_newNode("variable_declaration");
    vector <node*> tempVec;
    tempVec.push_back(temp);
    leaf->children.insert(leaf->children.end(),tempVec.begin(),tempVec.end());
    temp->parent=leaf;

    leaf = tempVec[0];

    data_type();

    return true;
}

void data_type()
{
    vector <node*> tempVec;
    string s1,s2,s3,s4;
    s1 = "data_type (";
    s2 = untokenedArray[i];
    s3 = ")";
    s4=s1+s2+s3;
    i++;

    node* temp1 = create_newNode(s4);
    tempVec.push_back(temp1);
    temp1->parent=leaf;
    leaf->children.insert(leaf->children.end(),tempVec.begin(),tempVec.end());

    s1 = "Identifier (";
    s2 = untokenedArray[i];
    s3 = ")";
    s4=s1+s2+s3;
    i++;

    node* temp2 = create_newNode(s4);
    tempVec.push_back(temp2);
    temp2->parent=leaf;
    leaf->children.insert(leaf->children.end(),tempVec.begin(),tempVec.end());

    leaf->children=tempVec;


    return;
}

void function_declaration()
{
    int marker=i;

    if(parameters()==true && compound_stmt()==true)
    {
        node* temp = create_newNode("function_declaration");
        vector <node*> tempVec;
        tempVec.push_back(temp);
        leaf->children=tempVec;
        temp->parent=leaf;

        leaf = tempVec[0];
        function_decl_leaf = leaf;

        i=marker;
        Printing_Parameters();
        compound_stmt_print();

        success=1;

        return;
    }
    else
    {
        cout << "Context Free Grammar is not followed by the code." << endl;
        return;
    }

}

bool parameters()
{
    if(tokenedArray[i]=="VOID" && tokenedArray[i+1]=="ClosingFirstBracket")
    {
        i=i+2;
        return true;
    }
    else if(param_list()==false)
    {
        return false;
    }
}

bool Printing_Parameters()
{
    if(tokenedArray[i]=="VOID" && tokenedArray[i+1]=="ClosingFirstBracket")
    {
        node* temp = create_newNode("parameters (VOID)");
        vector <node*> tempVec;
        tempVec.push_back(temp);
        leaf->children=tempVec;
        temp->parent=leaf;

        leaf = tempVec[0];
        i=i+2;
        return true;
    }
    else if(param_list_print()==false)
    {
        return false;
    }
}

bool param_list()
{
    if(param()==true)
    {
        if(tokenedArray[i]=="COMA")
        {
            i++;
            param_list();
        }
        else
        {
            return true;
        }
    }
    else return false;
}

int param_list_flag=0;
bool param_list_print()
{
    if(param_list_flag==0)
    {
        node* temp = create_newNode("parameter_list");
        vector <node*> tempVec;
        tempVec.push_back(temp);
        leaf->children=tempVec;
        temp->parent=leaf;

        leaf = tempVec[0];
        param_list_flag=1;
    }

    if(param_print()==true)
    {
        if(tokenedArray[i]=="COMA")
        {
            i++;
            param_list_print();
        }
        else
        {
            param_list_flag=0;
            return true;
        }
    }
    else return false;
}

bool param()
{
    if(tokenedArray[i]=="data_type" && tokenedArray[i+1]=="Identifier")
    {
        i=i+2;
        return true;
    }
    else
    {
        return false;
    }
}

bool param_print()
{
    if(tokenedArray[i]=="data_type" && tokenedArray[i+1]=="Identifier")
    {
        node* temp = create_newNode("parameter");
        vector <node*> tempVec;
        tempVec.push_back(temp);
        leaf->children=tempVec;
        temp->parent=leaf;

        leaf = tempVec[0];
        data_type();
        return true;
    }
    else
    {
        return false;
    }
}

bool listOfStatement()
{
    if(statement()==true)
    {
        listOfStatement();
    }
    else
    {
        return true;
    }

}


int stmt_list_flag=0;
bool PrintStatementList()
{
    if(stmt_list_flag==0)
    {
        node* temp = create_newNode("statement_list");
        vector <node*> tempVec;
        tempVec.push_back(temp);
        leaf->children.insert(leaf->children.end(),tempVec.begin(),tempVec.end());
        temp->parent=leaf;

        leaf = tempVec[0];

        stmt_list_flag=1;
    }

    if(print_statement()==false)
    {
        stmt_list_flag=0;
        return true;
    }

    PrintStatementList();

}

bool statement()
{
    if(return_stmt()==true)
    {
        return true;
    }
    else if(expressionStatement()==true)
    {
        return true;
    }

    else if(if_stmt()==true)
    {
        return true;
    }
    else if(while_stmt()==true)
    {
        return true;
    }
    else if(break_stmt()==true)
    {
        return true;
    }
    else
    {
        return false;
    }
}


bool print_statement()
{
    if(return_stmt_print()==true)
    {
        return true;
    }
    else if(break_stmt_print()==true)
    {
        return true;
    }
    else if(printExpressionStatement()==true)
    {
        return true;
    }

    else if(while_stmt_print()==true)
    {
        return true;
    }
    else if(if_stmt_print()==true)
    {
        return true;
    }
    else
    {
        return false;
    }
}


bool expressionStatement()
{
    if(tokenedArray[i+1]=="SEMICOLON")
    {
        i++;
        return true;
    }
    else if((tokenedArray[i+6]=="SEMICOLON"||tokenedArray[i+4]=="SEMICOLON") && expression()==true)
    {
        i++;
        return true;
    }
    else
    {
        return false;
    }
}


bool printExpressionStatement()
{
    if(tokenedArray[i+1]=="SEMICOLON")
    {
        node* temp = create_newNode("statement");
        vector <node*> tempVec;
        tempVec.push_back(temp);
        leaf->children.insert(leaf->children.end(),tempVec.begin(),tempVec.end());
        temp->parent=leaf;

        leaf = tempVec[0];

        node* temp1 = create_newNode("expression_statement (;)");
        vector <node*> tempVec1;
        tempVec1.push_back(temp1);
        leaf->children.insert(leaf->children.end(),tempVec1.begin(),tempVec1.end());
        temp1->parent=leaf;

        leaf = tempVec1[0];

        i++;
        return true;
    }
    if((tokenedArray[i+6]=="SEMICOLON"||tokenedArray[i+4]=="SEMICOLON") && expr_print()==true)
    {
        i++;
        return true;
    }
    else
    {
        return false;
    }
}


bool while_stmt()
{
    if(tokenedArray[i+1]=="WHILE"&&tokenedArray[i+2]=="OpeningFirstBracket")
    {
        i=i+2;
        if(expression()==true)
        {

            if(tokenedArray[i+1]=="ClosingFirstBracket")
            {

                i++;
                if(statement()==true)
                {
                    return true;
                }
            }
        }
    }
    else
    {
        return false;
    }
}

bool while_stmt_print()
{
    if(tokenedArray[i+1]=="WHILE"&&tokenedArray[i+2]=="OpeningFirstBracket")
    {
        node* temp = create_newNode("statement");
        vector <node*> tempVec;
        tempVec.push_back(temp);
        leaf->children.insert(leaf->children.end(),tempVec.begin(),tempVec.end());
        temp->parent=leaf;

        leaf = tempVec[0];

        node* temp1 = create_newNode("while_statement");
        vector <node*> tempVec1;
        tempVec1.push_back(temp1);
        leaf->children.insert(leaf->children.end(),tempVec1.begin(),tempVec1.end());
        temp1->parent=leaf;

        leaf = tempVec1[0];

        i=i+2;

        if(expr_print()==true)
        {
            if(tokenedArray[i+1]=="ClosingFirstBracket")
            {
                i++;
                if(print_statement()==true)
                {
                    return true;
                }
            }
        }
    }
    else
    {
        return false;
    }
}

bool compound_stmt()
{
    bool step1 = (tokenedArray[i]=="OpeningSecondBracket");
    bool step2 = local_decls();
    bool step3 = listOfStatement();
    bool step4 = (tokenedArray[i+1]=="ClosingSecondBracket");

    if(step1 && (step2 || step3) && step4)
    {
        return true;
    }
    else
    {
        return false;
    }
}


bool compound_stmt_print()
{
    int k=i;

    bool step1 = (tokenedArray[i]=="OpeningSecondBracket");
    bool step2 = local_decls();
    bool step3 = listOfStatement();
    bool step4 = (tokenedArray[i+1]=="ClosingSecondBracket");

    if(step1 && (step2 || step3) && step4)
    {
        i=k;
        if(step2==true)
        {
            local_decls_print();
        }
        if(step3==true)
        {
            PrintStatementList();
        }

        return true;
    }
    else
    {
        return false;
    }
}

int local_decls_flag1=0;
bool local_decls()
{
    if(local_decl()==true)
    {
        local_decls();
        local_decls_flag1=1;
    }
    else
    {
        if(local_decls_flag1==1)
        {
            return true;
            local_decls_flag1=0;
        }
        else
        {
            return false;
        }
    }
}

int local_decls_flag2=0;
bool local_decls_print()
{
    if(local_decls_flag2==0)
    {
        leaf=function_decl_leaf;

        node* temp = create_newNode("local_declarations");
        vector <node*> tempVec;
        tempVec.push_back(temp);
        leaf->children.insert(leaf->children.end(),tempVec.begin(),tempVec.end());
        temp->parent=leaf;

        leaf = tempVec[0];
        local_decls_flag2=1;
    }

    if(local_decl_print()==false)
    {
        local_decls_flag2=0;
        return true;
    }

    local_decls_print();
}


bool local_decl()
{
    if(tokenedArray[i+1]=="data_type" && tokenedArray[i+2]=="Identifier" && tokenedArray[i+3]=="SEMICOLON")
    {
        i=i+3;
        return true;
    }
    else
    {
        return false;
    }
}


bool local_decl_print()
{
    if(tokenedArray[i+1]=="data_type" && tokenedArray[i+2]=="Identifier" && tokenedArray[i+3]=="SEMICOLON")
    {
        node* temp = create_newNode("local_declare");
        vector <node*> tempVec;
        tempVec.push_back(temp);
        leaf->children.insert(leaf->children.end(),tempVec.begin(),tempVec.end());
        temp->parent=leaf;

        leaf = tempVec[0];
        i=i+1;
        data_type();
        return true;
    }
    else
    {
        return false;
    }
}


bool if_stmt()
{
    if(tokenedArray[i+1]=="IF" && tokenedArray[i+2]=="OpeningFirstBracket")
    {
        i=i+2;

        if(expression()==true)
        {
            if(tokenedArray[i+1]=="ClosingFirstBracket")
            {
                i++;

                if(statement()==true)
                {
                    if(tokenedArray[i+1]=="ELSE")
                    {
                        i++;

                        if(statement()==true)
                        {
                            return true;
                        }
                        else
                        {
                            return false;
                        }
                    }

                    return true;
                }
                else
                {
                    return false;
                }
            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }

        return true;
    }
    else
    {
        return false;
    }
}


bool if_stmt_print()
{
    if(tokenedArray[i+1]=="IF" && tokenedArray[i+2]=="OpeningFirstBracket")
    {
        node* temp = create_newNode("statement");
        vector <node*> tempVec;
        tempVec.push_back(temp);
        leaf->children.insert(leaf->children.end(),tempVec.begin(),tempVec.end());
        temp->parent=leaf;

        leaf = tempVec[0];

        node* temp1 = create_newNode("if_statement");
        vector <node*> tempVec1;
        tempVec1.push_back(temp1);
        leaf->children.insert(leaf->children.end(),tempVec1.begin(),tempVec1.end());
        temp1->parent=leaf;

        leaf = tempVec1[0];

        i=i+2;

        if(expr_print()==true)
        {
            if(tokenedArray[i+1]=="ClosingFirstBracket")
            {
                i++;

                if(print_statement()==true)
                {
                    if(tokenedArray[i+1]=="ELSE")
                    {
                        node* temp2 = create_newNode("else_statement");
                        vector <node*> tempVec2;
                        tempVec2.push_back(temp2);
                        leaf->children.insert(leaf->children.end(),tempVec2.begin(),tempVec2.end());
                        temp2->parent=leaf;

                        leaf = tempVec2[0];
                        i++;

                        if(print_statement()==true)
                        {
                            return true;
                        }
                        else
                        {
                            return false;
                        }
                    }

                    return true;
                }
                else
                {
                    return false;
                }

                return true;
            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }

        return true;
    }
    else
    {
        return false;
    }
}

bool return_stmt()
{
    if(tokenedArray[i+1]=="RETURN"&&tokenedArray[i+2]=="SEMICOLON")
    {
        i=i+2;
        return true;
    }
    else if(tokenedArray[i+1]=="RETURN")
    {
        i=i+1;
        if(expression()==true)
        {
            if(tokenedArray[i+1]=="SEMICOLON")
            {
                i=i++;
                return true;
            }
        }
    }
    else
    {
        return false;
    }
}

bool return_stmt_print()
{
    if(tokenedArray[i+1]=="RETURN"&&tokenedArray[i+2]=="SEMICOLON")
    {
        node* temp = create_newNode("statement");
        vector <node*> tempVec;
        tempVec.push_back(temp);
        leaf->children.insert(leaf->children.end(),tempVec.begin(),tempVec.end());
        temp->parent=leaf;

        leaf = tempVec[0];

        node* temp1 = create_newNode("return_statement");
        vector <node*> tempVec1;
        tempVec1.push_back(temp1);
        leaf->children.insert(leaf->children.end(),tempVec1.begin(),tempVec1.end());
        temp1->parent=leaf;

        leaf = tempVec1[0];
        i=i+2;
        return true;
    }
    else if(tokenedArray[i+1]=="RETURN")
    {
        i=i+1;
        if(expression()==true)
        {
            if(tokenedArray[i+1]=="SEMICOLON")
            {
                node* temp = create_newNode("statement");
                vector <node*> tempVec;
                tempVec.push_back(temp);
                leaf->children.insert(leaf->children.end(),tempVec.begin(),tempVec.end());
                temp->parent=leaf;

                leaf = tempVec[0];

                node* temp1 = create_newNode("return_statement");
                vector <node*> tempVec1;
                tempVec1.push_back(temp1);
                leaf->children.insert(leaf->children.end(),tempVec1.begin(),tempVec1.end());
                temp1->parent=leaf;

                leaf = tempVec1[0];
                i=i+2;
                return true;
            }
        }
    }
    else
    {
        return false;
    }
}

bool break_stmt()
{
    if(tokenedArray[i+1]=="BREAK" && tokenedArray[i+2]=="SEMICOLON")
    {
        i=i+2;
        return true;
    }
    else
    {
        return false;
    }
}

bool break_stmt_print()
{
    if(tokenedArray[i+1]=="BREAK" && tokenedArray[i+2]=="SEMICOLON")
    {
        node* temp = create_newNode("statement");
        vector <node*> tempVec;
        tempVec.push_back(temp);
        leaf->children.insert(leaf->children.end(),tempVec.begin(),tempVec.end());
        temp->parent=leaf;

        leaf = tempVec[0];

        node* temp1 = create_newNode("break_statement");
        vector <node*> tempVec1;
        tempVec1.push_back(temp1);
        leaf->children.insert(leaf->children.end(),tempVec1.begin(),tempVec1.end());
        temp1->parent=leaf;

        leaf = tempVec1[0];
        i=i+2;
        return true;
    }
    else
    {
        return false;
    }
}

bool expr_print()
{
    if(tokenedArray[i+1]=="Identifier"&&tokenedArray[i+2]=="ASSIGNMENT"&&tokenedArray[i+3]=="Identifier"&&(tokenedArray[i+4]=="ADD"||tokenedArray[i+4]=="SUBTRACT"||tokenedArray[i+4]=="MULTIPLICATION"||tokenedArray[i+4]=="DIVISION")&&tokenedArray[i+5]=="IDENT")
    {
        node* temp = create_newNode("statement");
        vector <node*> tempVec;
        tempVec.push_back(temp);
        leaf->children.insert(leaf->children.end(),tempVec.begin(),tempVec.end());
        temp->parent=leaf;

        leaf = tempVec[0];

        node* temp1 = create_newNode("expression_statement");
        vector <node*> tempVec1;
        tempVec1.push_back(temp1);
        leaf->children.insert(leaf->children.end(),tempVec1.begin(),tempVec1.end());
        temp1->parent=leaf;

        leaf = tempVec1[0];

        string s1,s2,s3,s4;
        s1="Identifier (";
        s2=untokenedArray[i+1];
        s3=")";
        s4=s1+s2+s3;

        node* temp2 = create_newNode(s4);
        vector <node*> tempVec2;
        tempVec2.push_back(temp2);
        leaf->children.insert(leaf->children.end(),tempVec2.begin(),tempVec2.end());
        temp2->parent=leaf;

        node* temp3 = create_newNode("ASSIGNMENT (=)");
        vector <node*> tempVec3;
        tempVec3.push_back(temp3);
        leaf->children.insert(leaf->children.end(),tempVec3.begin(),tempVec3.end());
        temp3->parent=leaf;

        s1="Identifier (";
        s2=untokenedArray[i+3];
        s3=")";
        s4=s1+s2+s3;

        node* temp4 = create_newNode(s4);
        vector <node*> tempVec4;
        tempVec4.push_back(temp4);
        leaf->children.insert(leaf->children.end(),tempVec4.begin(),tempVec4.end());
        temp1->parent=leaf;

        if(tokenedArray[i+4]=="ADD")
        {
            node* temp5 = create_newNode("ADD (+)");
            vector <node*> tempVec5;
            tempVec5.push_back(temp5);
            leaf->children.insert(leaf->children.end(),tempVec5.begin(),tempVec5.end());
            temp5->parent=leaf;
        }
        if(tokenedArray[i+4]=="SUBTRACT")
        {
            node* temp5 = create_newNode("SUBTRACT (-)");
            vector <node*> tempVec5;
            tempVec5.push_back(temp5);
            leaf->children.insert(leaf->children.end(),tempVec5.begin(),tempVec5.end());
            temp5->parent=leaf;
        }
        if(tokenedArray[i+4]=="MULTIPLICATION")
        {
            node* temp5 = create_newNode("MULTIPLICATION (*)");
            vector <node*> tempVec5;
            tempVec5.push_back(temp5);
            leaf->children.insert(leaf->children.end(),tempVec5.begin(),tempVec5.end());
            temp5->parent=leaf;
        }

        if(tokenedArray[i+4]=="DIVISION")
        {
            node* temp5 = create_newNode("DIVISION (/)");
            vector <node*> tempVec5;
            tempVec5.push_back(temp5);
            leaf->children.insert(leaf->children.end(),tempVec5.begin(),tempVec5.end());
            temp5->parent=leaf;
        }

        s1="Identifier (";
        s2=untokenedArray[i+5];
        s3=")";
        s4=s1+s2+s3;

        node* temp6 = create_newNode(s4);
        vector <node*> tempVec6;
        tempVec6.push_back(temp6);
        leaf->children.insert(leaf->children.end(),tempVec6.begin(),tempVec6.end());
        temp6->parent=leaf;

        i=i+5;
        return true;

    }
    else if(tokenedArray[i+1]=="Identifier"&&tokenedArray[i+2]=="ASSIGNMENT"&&tokenedArray[i+3]=="Identifier")
    {
        node* temp = create_newNode("statement");
        vector <node*> tempVec;
        tempVec.push_back(temp);
        leaf->children.insert(leaf->children.end(),tempVec.begin(),tempVec.end());
        temp->parent=leaf;

        leaf = tempVec[0];

        node* temp1 = create_newNode("expression_statement");
        vector <node*> tempVec1;
        tempVec1.push_back(temp1);
        leaf->children.insert(leaf->children.end(),tempVec1.begin(),tempVec1.end());
        temp1->parent=leaf;

        leaf = tempVec1[0];
        string s1,s2,s3,s4;
        s1="Identifier (";
        s2=untokenedArray[i+1];
        s3=")";
        s4=s1+s2+s3;

        node* temp2 = create_newNode(s4);
        vector <node*> tempVec2;
        tempVec2.push_back(temp2);
        leaf->children.insert(leaf->children.end(),tempVec2.begin(),tempVec2.end());
        temp2->parent=leaf;

        node* temp3 = create_newNode("ASSIGNMENT (=)");
        vector <node*> tempVec3;
        tempVec3.push_back(temp3);
        leaf->children.insert(leaf->children.end(),tempVec3.begin(),tempVec3.end());
        temp3->parent=leaf;
        s1="Identifier (";
        s2=untokenedArray[i+3];
        s3=")";
        s4=s1+s2+s3;

        node* temp4 = create_newNode(s4);
        vector <node*> tempVec4;
        tempVec4.push_back(temp4);
        leaf->children.insert(leaf->children.end(),tempVec4.begin(),tempVec4.end());
        temp1->parent=leaf;

        i=i+3;
        return true;
    }

    else if(tokenedArray[i+1]=="Identifier"&&(tokenedArray[i+2]=="Equation"||tokenedArray[i+2]=="NotEqual"||tokenedArray[i+2]=="LESSER"||tokenedArray[i+2]=="GREATER")&&tokenedArray[i+3]=="Identifier")
    {
        node* temp = create_newNode("statement");
        vector <node*> tempVec;
        tempVec.push_back(temp);
        leaf->children.insert(leaf->children.end(),tempVec.begin(),tempVec.end());
        temp->parent=leaf;

        leaf = tempVec[0];

        node* temp1 = create_newNode("expr_stmt");
        vector <node*> tempVec1;
        tempVec1.push_back(temp1);
        leaf->children.insert(leaf->children.end(),tempVec1.begin(),tempVec1.end());
        temp1->parent=leaf;

        leaf = tempVec1[0];
        string s1,s2,s3,s4;
        s1="Identifier (";
        s2=untokenedArray[i+1];
        s3=")";
        s4=s1+s2+s3;

        node* temp2 = create_newNode(s4);
        vector <node*> tempVec2;
        tempVec2.push_back(temp2);
        leaf->children.insert(leaf->children.end(),tempVec2.begin(),tempVec2.end());
        temp2->parent=leaf;

        if(tokenedArray[i+2]=="Equation")
        {
            node* temp3 = create_newNode("Equation (==)");
            vector <node*> tempVec3;
            tempVec3.push_back(temp3);
            leaf->children.insert(leaf->children.end(),tempVec3.begin(),tempVec3.end());
            temp3->parent=leaf;
        }
        else if(tokenedArray[i+2]=="NotEqual")
        {
            node* temp3 = create_newNode("NotEqual (!=)");
            vector <node*> tempVec3;
            tempVec3.push_back(temp3);
            leaf->children.insert(leaf->children.end(),tempVec3.begin(),tempVec3.end());
            temp3->parent=leaf;
        }
        if(tokenedArray[i+2]=="LESSER")
        {
            node* temp3 = create_newNode("LESSER (<)");
            vector <node*> tempVec3;
            tempVec3.push_back(temp3);
            leaf->children.insert(leaf->children.end(),tempVec3.begin(),tempVec3.end());
            temp3->parent=leaf;
        }
        if(tokenedArray[i+2]=="GREATER")
        {
            node* temp3 = create_newNode("GREATER (>)");
            vector <node*> tempVec3;
            tempVec3.push_back(temp3);
            leaf->children.insert(leaf->children.end(),tempVec3.begin(),tempVec3.end());
            temp3->parent=leaf;
        }

        s1="Identifier (";
        s2=untokenedArray[i+3];
        s3=")";
        s4=s1+s2+s3;

        node* temp4 = create_newNode(s4);
        vector <node*> tempVec4;
        tempVec4.push_back(temp4);
        leaf->children.insert(leaf->children.end(),tempVec4.begin(),tempVec4.end());
        temp1->parent=leaf;
        i=i+3;
        return true;
    }
    else if(tokenedArray[i+1]=="Bool"||tokenedArray[i+1]=="Float"||tokenedArray[i+1]=="Integer"||tokenedArray[i+1]=="Identifier")
    {
        node* temp = create_newNode("statement");
        vector <node*> tempVec;
        tempVec.push_back(temp);
        leaf->children.insert(leaf->children.end(),tempVec.begin(),tempVec.end());
        temp->parent=leaf;

        leaf = tempVec[0];

        node* temp1 = create_newNode("expr_stmt");
        vector <node*> tempVec1;
        tempVec1.push_back(temp1);
        leaf->children.insert(leaf->children.end(),tempVec1.begin(),tempVec1.end());
        temp1->parent=leaf;
        leaf = tempVec1[0];

        if(tokenedArray[i+1]=="Bool")
        {
            string s1,s2,s3,s4;
            s1="Bool (";
            s2=untokenedArray[i+1];
            s3=")";
            s4=s1+s2+s3;

            node* temp2 = create_newNode(s4);
            vector <node*> tempVec2;
            tempVec2.push_back(temp2);
            leaf->children.insert(leaf->children.end(),tempVec2.begin(),tempVec2.end());
            temp2->parent=leaf;
        }

        else if(tokenedArray[i+1]=="Float")
        {
            string s1,s2,s3,s4;
            s1="Float (";
            s2=untokenedArray[i+1];
            s3=")";
            s4=s1+s2+s3;

            node* temp2 = create_newNode(s4);
            vector <node*> tempVec2;
            tempVec2.push_back(temp2);
            leaf->children.insert(leaf->children.end(),tempVec2.begin(),tempVec2.end());
            temp2->parent=leaf;
        }

        if(tokenedArray[i+1]=="Integer")
        {
            string s1,s2,s3,s4;
            s1="Integer (";
            s2=untokenedArray[i+1];
            s3=")";
            s4=s1+s2+s3;

            node* temp2 = create_newNode(s4);
            vector <node*> tempVec2;
            tempVec2.push_back(temp2);
            leaf->children.insert(leaf->children.end(),tempVec2.begin(),tempVec2.end());
            temp2->parent=leaf;
        }

        if(tokenedArray[i+1]=="Identifier")
        {
            string s1,s2,s3,s4;
            s1="Identifier (";
            s2=untokenedArray[i+1];
            s3=")";
            s4=s1+s2+s3;

            node* temp2 = create_newNode(s4);
            vector <node*> tempVec2;
            tempVec2.push_back(temp2);
            leaf->children.insert(leaf->children.end(),tempVec2.begin(),tempVec2.end());
            temp2->parent=leaf;
        }

        i=i+1;
        return true;
    }
    else
    {
        return false;
    }
}

bool expression()
{
    if(tokenedArray[i+1]=="Identifier"&&tokenedArray[i+2]=="ASSIGNMENT"&&tokenedArray[i+3]=="Identifier"&&(tokenedArray[i+4]=="ADD"||tokenedArray[i+4]=="SUBTRACT"||tokenedArray[i+4]=="MULTIPLICATION"||tokenedArray[i+4]=="DIVISION")&&tokenedArray[i+5]=="Identifier")
    {
        i=i+5;
        return true;
    }
    else if(tokenedArray[i+1]=="Identifier"&&tokenedArray[i+2]=="ASSIGNMENT"&&tokenedArray[i+3]=="Identifier")
    {
        i=i+3;
        return true;
    }
    else if(tokenedArray[i+1]=="Identifier"&&(tokenedArray[i+2]=="Equation"||tokenedArray[i+2]=="NotEqual"||tokenedArray[i+2]=="LESSER"||tokenedArray[i+2]=="GREATER")&&tokenedArray[i+3]=="Identifier")
    {
        i=i+3;
        return true;
    }
    else if(tokenedArray[i+1]=="Bool"||tokenedArray[i+1]=="Float"||tokenedArray[i+1]=="Integer"||tokenedArray[i+1]=="Identifier")
    {
        i=i+1;
        return true;
    }
    else
    {
        return false;
    }

}

bool arg_list()
{
    if(expression()==true)
    {
        return true;
    }
    else if(arg_list()==true&&tokenedArray[i]=="COMA"&&expression()==true)
    {
        i++;
        return true;
    }
    else
    {
        return false;
    }
}


bool args()
{
    arg_list();
    return true;
}
