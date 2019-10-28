#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QFileDialog>
#include<QInputDialog>
#include<QFile>
#include<QTextStream>
#include<QMessageBox>
#include<QPlainTextEdit>
#include<bits/stdc++.h>
using namespace std;
static string fileName = "";
//-----------------------------------------------AES-----------------------
static unsigned char allKey[4][44];
static unsigned char sBox[16][16];
static unsigned char invSBox[16][16];
static unsigned char key[4][4];
static int forwardArr[4][4] = {2,3,1,1,1,2,3,1,1,1,2,3,3,1,1,2};
static int backwordArr[4][4] = {14,11,13,9,9,14,11,13,13,9,14,11,11,13,9,14};
//------------------------------------SHA-----------------------------------------------------------------------------
#define SHR(x, n)    (x >> n)
#define ROTR(x, n)   ((x >> n) ^ (x << (64 - n)))
#define CH(x, y, z)  ((x & y) ^ (~x & z))
#define MAJ(x, y, z) ((x & y) ^ (x & z) ^ (y & z))
#define sum512_zero(x) (ROTR(x, 28) ^ ROTR(x, 34) ^ ROTR(x, 39))
#define sum512_one(x) (ROTR(x, 14) ^ ROTR(x, 18) ^ ROTR(x, 41))
#define sigma512_zero(x) (ROTR(x,  1) ^ ROTR(x,  8) ^ SHR(x,  7))
#define sigma512_one(x) (ROTR(x, 19) ^ ROTR(x, 61) ^ SHR(x,  6))
//---------------------SHA--------------------------------------------start-------------------------------------------
static uint64_t SHAkey[80],HASH[8];
void initializeHASH()
{
    ifstream ifile;
    ifile.open("C:\\Users\\bsse1\\Documents\\initialHASH.txt");
    if(!ifile)
    {
        cout<<"unable to open initialHASH.txt";
        exit(0);
    }
    for(int i=0;i<8;i++) ifile>>hex>>HASH[i];
    ifile.close();
}

void initializeSHAKey()
{
    ifstream ifile;
    ifile.open("C:\\Users\\bsse1\\Documents\\SHAkey.txt");
    if(!ifile)
    {
        cout<<"unable to open SHAkey.txt"<<endl;
        exit(1);
    }
    for(int i=0;i<80; i++) ifile>>hex>>SHAkey[i];
    ifile.close();
}

string printHASH()
{
    ofstream ofile;

    ofile.open("C:\\Users\\bsse1\\Documents\\temp.txt");
    ofile<<hex<<hex<<(uint64_t)HASH[0]<<(uint64_t)HASH[1]
        <<(uint64_t)HASH[2]<<(uint64_t)HASH[3]
        <<(uint64_t)HASH[4]<<(uint64_t)HASH[5]
        <<(uint64_t)HASH[6]<<(uint64_t)HASH[7];
    ofile.close();
    ifstream ifile;
    ifile.open("C:\\Users\\bsse1\\Documents\\temp.txt");
    string s;
    getline(ifile,s);
    while(getline(ifile,s)) s+="\n" +s;

    ifile.close();
    return s;

}


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


string  printSHA(string fileName)
{


        string s,temp;
        ifstream ifile;
        ifile.open(fileName);
        getline(ifile,s);
        while(getline(ifile,temp)) s+="\n" + temp;
        uint64_t numberOfBlock,mLength,pos = 0;
        mLength = s.length();
        if(mLength==0) exit(0);
        numberOfBlock = ceil((mLength+17+0.0)/128);
        initializeSHAKey();
        initializeHASH();
        unsigned char *totalCH = new unsigned char[numberOfBlock*128];
        for(uint64_t i=0; i<mLength; i++) totalCH[i] = s[i];
        totalCH[mLength] = 1<<7;
        for(uint64_t i=mLength+1; i<numberOfBlock*128; i++) totalCH[i] = 0;
        uint64_t totalBINs = mLength*8;
        for(uint64_t i=(numberOfBlock*128-1); i>(numberOfBlock*128-17); i--)
        {
            totalCH[i] = totalBINs;
            totalBINs = totalBINs>>8;
        }
        for(uint64_t k=1; k<=numberOfBlock; k++)
        {
            uint64_t W[80],t1,t2,a,b,c,d,e,f,g,h;
            for(int j=0;j<16;j++)
            {
                W[j] = totalCH[pos];
                for(int i=1; i<8; i++) W[j] = W[j]<<8 | totalCH[pos+i];
                pos+=8;
            }
            for(int j=16;j<80;j++) W[j] = (sigma512_one(W[j-2])+W[j-7]+sigma512_zero(W[j-15])+W[j-16]);

            a = HASH[0];   e = HASH[4];
            b = HASH[1];   f = HASH[5];
            c = HASH[2];   g = HASH[6];
            d = HASH[3];   h = HASH[7];

            for(int i=0;i<80;i++)
            {
                t1 = (h + CH(e,f,g) + sum512_one(e) + W[i] + SHAkey[i]);
                t2 = (sum512_zero(a) + MAJ(a,b,c));
                h = g;   g = f;
                f = e;   e = (d+ t1);
                d = c;   c = b;
                b = a;   a = (t1+ t2);
            }

           HASH[0] = (a+HASH[0]);
           HASH[1] = (b+HASH[1]);
           HASH[2] = (c+HASH[2]);
           HASH[3] = (d+HASH[3]);
           HASH[4] = (e+HASH[4]);
           HASH[5] = (f+HASH[5]);
           HASH[6] = (g+HASH[6]);
           HASH[7] = (h+HASH[7]);

        }
        return printHASH();


}

void MainWindow::on_pushButton_clicked()
{
    QString file_name= QFileDialog::getOpenFileName(this,"Open a file",QDir::homePath());
    ui->pushButton->setText(file_name);
    fileName = file_name.toStdString();

    string news = printSHA(fileName);
    ui->lineEdit->setText(QString::fromStdString(news));

    QFile file(file_name);
    if(!file.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this,"title","File is not opened");
    }
    QTextStream in(&file);
    QString text = in.readAll();

    ui->textEdit->setPlainText(text);

    file.close();
}
//----------------AES-------------------------------START--------------------------------------------------------
void initializeKey()
{
    ifstream ifile;
    int n;
    char ch;
    ifile.open("C:\\Users\\bsse1\\Documents\\key.txt");
    if(!ifile)
    {
        cout<<"unable to open key.txt:";
        exit(1);
    }
    for(int i=0; i<4; i++)
        for(int j=0; j<4; j++)
    {
        ifile.get(ch);
        key[j][i] = ch;
    }
    ifile.close();


}
void initSBox()
{
    int n;
    ifstream ifile;
    ifile.open("C:\\Users\\bsse1\\Documents\\s-box.txt");
    if(!ifile)
    {
        cout<<"unable to open s-box.txt:";
        exit(0);
    }
    for(int i=0; i<16; i++)
        for(int j=0; j<16; j++)
    {
        ifile>>hex>>n;
        sBox[i][j] = n;
    }
    ifile.close();
}
void initInvSBox()
{
    int n;
    ifstream ifile;
    ifile.open("C:\\Users\\bsse1\\Documents\\invS-box.txt");
    if(!ifile)
    {
        cout<<"unable to open invSBox.txt"<<endl;
        exit(0);
    }
    for(int i=0;i<16;i++)
        for(int j=0; j<16; j++)
        {
            ifile>>hex>>n;
            invSBox[i][j] = n;
        }
        ifile.close();
}
unsigned char *SubWord(unsigned char temp[])
{
    unsigned char ch,tempCH;
    for(int i=0; i<4; i++)
        {
            ch = temp[i];
            tempCH = ch<<4;
            temp[i] = sBox[int(ch>>4)][int(tempCH>>4)];
        }
    return temp;
}
unsigned char *RotWord(unsigned char temp[])
{
    unsigned char ch = temp[0];
    for(int i=0;i<3; i++) temp[i] = temp[i+1];
    temp[3] = ch;
    return temp;
}
unsigned char *Rcon(int round)
{
    unsigned char *temp = new unsigned char[4];
    if(round<9) temp[0] = pow(2,round-1);
    else if(round==9) temp[0] = 27;
    else temp[0] = 54;
    for(int i=1;i<4; i++) temp[i] = 0;
    return temp;
}
unsigned char *exor(unsigned char temp1[],unsigned char temp2[])
{
    for(int i=0; i<4; i++) temp1[i] = temp1[i]^temp2[i];
    return temp1;
}
void expansionKey()
{
    for(int word=0;word<4;word++)
        for(int byte=0;byte<4; byte++) allKey[byte][word] = key[byte][word];

    unsigned char *temp= new unsigned char[4];
    for(int word=4; word<44;word++)
    {
        for(int byte=0;byte<4; byte++) temp[byte] = allKey[byte][word-1];
        if(word%4==0) temp = exor(SubWord (RotWord (temp)),Rcon(word/4));
        for(int byte=0; byte<4; byte++) allKey[byte][word] = temp[byte]^allKey[byte][word-4];

    }
}
void addRound(unsigned char **state,int round)
{
    for(int i=0; i<4; i++)
        for(int j=0; j<4; j++)
    {
        state[j][i] = state[j][i]^allKey[j][(round*4)+i];
    }
}
void substitute(unsigned char **state)
{
    unsigned char ch,tempCH;
    for(int i=0; i<4; i++)
        for(int j=0; j<4; j++)
        {
            ch = state[i][j];
            tempCH = ch<<4;
            state[i][j] = sBox[int(ch>>4)][int(tempCH>>4)];
        }
}

void invSubstitute(unsigned char **state)
{
    unsigned char ch,tempCh;
    for(int i=0; i<4; i++)
        for(int j=0; j<4;j++)
    {
        ch = state[i][j];
        tempCh = ch<<4;
        state[i][j] = invSBox[int(ch>>4)][int(tempCh>>4)];
    }
}
void shiftRow(unsigned char **state,int startinRow)
{
    if(startinRow==4) return;
    unsigned char ch[3];
    for(int i=0;i<startinRow; i++) ch[i] = state[startinRow][i];
    for(int i=0; i<4; i++)
    {
        int clm = (i+startinRow)%4;
        if(clm>=i) state[startinRow][i] = state[startinRow][clm];
        else state[startinRow][i] = ch[clm];
    }
    shiftRow(state,++startinRow);
}

void invShiftRows(unsigned char **state,int startinRow)
{
    if(startinRow==4) return;
    unsigned char ch[3];
    for(int i=0;i<startinRow; i++) ch[i] = state[startinRow][3-i];
    for(int i=0; i<4; i++)
    {
        int clm = (i+startinRow)%4;
        if(clm>=i) state[startinRow][3-i] = state[startinRow][3-clm];
        else state[startinRow][3-i] = ch[clm];
    }
    invShiftRows(state,++startinRow);
}
char productByTwo(unsigned char ch)
{
        if(int(ch>>7)) return (ch<<1)^(27);
        return ch<<1;
}
unsigned char productByPowerTwoNumber(int n,unsigned char ch)
{
    if(n==1) return ch;
    if(n==2) return productByTwo(ch);
    else return productByPowerTwoNumber(2,productByPowerTwoNumber(n/2,ch));
}
unsigned char product(int n,unsigned char ch)
{
    unsigned char tempCh = 0;
    int power;
    do
    {
        power = log2(n);
        tempCh^=productByPowerTwoNumber(pow(2,power),ch);
        n = n%(int)(pow(2,power));
    }while(n!=0);
    return tempCh;
}

void mixCLM(unsigned char **state,int forward)
{

    for(int i=0; i<4; i++)
    {
        unsigned char tempArr[4];
        for(int k=0; k<4; k++)
        {
            tempArr[k] = state[k][i];
            state[k][i] = 0;
        }
        if(forward) for(int j=0; j<4; j++) for(int k = 0; k<4; k++) state[j][i]^=product(forwardArr[j][k],tempArr[k]);
        else for(int j=0; j<4; j++) for(int k = 0; k<4; k++) state[j][i]^=product(backwordArr[j][k],tempArr[k]);
    }
}
void printState(unsigned char **state)
{
        for(int i=0; i<4;i++)
        for(int j=0; j<4; j++) cout<<state[j][i];
}
void saveFile(string s,bool asciii)
{
    ofstream ofile;
    unsigned int n,cnt=0;
    ofile.open(fileName);
    if(!ofile) return;
    if (!asciii)
        for(int i=0; i<s.length(); i++)
        {
            if(s[i]<0) n = s[i] + 256;
            else n =s[i];
            ofile<<hex<<n;
            if(cnt==30)
            {
                ofile<<endl;
                cnt = -1;
            }
            else ofile<<" ";
            cnt++;
        }
    else ofile<<s;
    ofile.close();
}

void encrypt(unsigned char **state)
{
        addRound(state,0);
        for(int i=1; i<11; i++)
        {
            substitute(state);
            shiftRow(state,1);
            if(i<10) mixCLM(state,1);
            addRound(state,i);
        }
}
void xorState(unsigned char **returnState,unsigned char **secondState)
{
    for(int i=0; i<4; i++)
        for(int j=0; j<4; j++)
            returnState[i][j] ^= secondState[i][j];
}

void initializeTempState(unsigned char **temp)
{
    for(int i=0; i<4; i++)
        for(int j=0; j<4; j++)
            temp[i][j] = 0;
}
void increaseTempByOne(unsigned char **temp,int row,int col)
{
    if(row==0 && col==0)
    {
        temp[0][0] += 1;
        return;
    }
    else if(temp[row][col]<255)
    {
        temp[row][col] +=1;
        return;
    }
    if(row==0) increaseTempByOne(temp,3,col-1);
    else increaseTempByOne(temp,row-1,col);
    temp[row][col] +=1;
}
int ECBencryption(int mood)
{
    string s;
    ifstream ifile;
    unsigned char **IV = new unsigned char *[4];
    for(int i=0; i<4; i++) IV[i] = new unsigned char[4];
    initializeTempState(IV);
    unsigned char **counter = new unsigned char *[4];
    for(int i=0; i<4; i++) counter[i] = new unsigned char[4];
    initializeTempState(counter);
    unsigned char **temp = new unsigned char *[4];
    for(int i=0; i<4; i++) temp[i] = new unsigned char[4];
    initializeTempState(temp);
    if(fileName=="") return 0;
    ifile.open(fileName);
    if(!ifile) return 0;
    unsigned char **state = new unsigned char *[4];
    for(int i=0; i<4; i++) state[i] = new unsigned char[4];
    char ch;

    while(ifile.get(ch))
    {
        int word=0;
        int byte=1;
        state[0][0] = ch;
        for(; word<4;word++)
        {
            for(; byte<4;)
            {
                if(ifile.get(ch)) state[byte][word] = ch;
                else break;
                byte=(byte+1)%4;
                if(byte==0) break;
            }
            if(ifile.eof()) break;
        }
        for(;word<4;word++)
            for(;byte<4;)
                {
                    state[byte][word] = 0;
                    byte=(byte+1)%4;
                    if(byte==0) break;
                }
        if(mood==1)
            encrypt(state);

        else if(mood==2) //CBC
        {
            xorState(IV,state);
            encrypt(IV);
            for(int i=0; i<4;i++)
                for(int j=0; j<4; j++)
                {
                    state[i][j] = IV[i][j];
                }

        }
        else //CTR
        {
            for(int i=0; i<4;i++)
                for(int j=0; j<4; j++)
                    counter[i][j] = temp[i][j];
            encrypt(counter);
            xorState(state,counter);
            increaseTempByOne(temp,3,3);

        }

        for(int i=0; i<4;i++)
                for(int j=0; j<4; j++)
                        s += state[j][i];
    }
    ifile.close();
    saveFile(s,0);
}

void decrypt(unsigned char **state)
{
        addRound(state,10);
        for(int i=9;i>=0;i--)
        {
            invShiftRows(state,1);
            invSubstitute(state);
            addRound(state,i);
            if(i>0) mixCLM(state,0);
        }
}

int ECBdecryption(int mood)
{

    string s;
    ifstream ifile;
    unsigned char **IV = new unsigned char *[4];
    for(int i=0; i<4; i++) IV[i] = new unsigned char[4];
    initializeTempState(IV);
    unsigned char **counter = new unsigned char *[4];
    for(int i=0; i<4; i++) counter[i] = new unsigned char[4];
    initializeTempState(counter);
    unsigned char **temp = new unsigned char *[4];
    for(int i=0; i<4; i++) temp[i] = new unsigned char[4];
    initializeTempState(temp);
    unsigned char **temp1 = new unsigned char *[4];
    for(int i=0; i<4; i++) temp1[i] = new unsigned char[4];
    initializeTempState(temp1);
    unsigned char **temp2 = new unsigned char *[4];
    for(int i=0; i<4; i++) temp2[i] = new unsigned char[4];
    initializeTempState(temp2);
    int time = 1;
    if(fileName=="") return 0;
    ifile.open(fileName);
    if(!ifile) return 0;
    unsigned char **state = new unsigned char *[4];
    for(int i=0; i<4; i++) state[i] = new unsigned char[4];
    char ch;
    unsigned int n;


    while(ifile>>hex>>n)
    {
        ch = n;
        int word=0;
        int byte=1;
        state[0][0] = ch;
        for(; word<4;word++)
        {
            for(; byte<4;)
            {
                if(ifile>>hex>>n) state[byte][word] = n;
                else break;
                byte=(byte+1)%4;
                if(byte==0) break;
            }
            if(ifile.eof()) break;
        }
        for(;word<4;word++)
            for(;byte<4;)
                {
                    state[byte][word] = 0;
                    byte=(byte+1)%4;
                    if(byte==0) break;
                }

        if(mood==1) //ECB
            decrypt(state);

        else if(mood==2) //CBC
        {
            for(int i=0; i<4; i++)
                for(int j=0; j<4; j++)
                    temp1 [i][j] = state[i][j];

            decrypt(state);
            if (time==1) xorState(state,IV);
            else xorState(state,temp2);
            for(int i=0; i<4; i++)
                for(int j=0; j<4; j++)
                    temp2[i][j] = temp1[i][j];

            time=2;
        }
        else //CTR
        {
            for(int i=0; i<4;i++)
                for(int j=0; j<4; j++)
                    counter[i][j] = temp[i][j];
            encrypt(counter);
            xorState(state,counter);
            increaseTempByOne(temp,3,3);
        }
        for(int i=0; i<4;i++)
                for(int j=0; j<4; j++)
                    if ((int) state[j][i])
                        s += state[j][i];
    }
    ifile.close();

    saveFile(s,1);
}
//------------------------------------------------------------AES-------------------end-------------------------
void MainWindow::on_checkBox_clicked()
{

}

void MainWindow::on_checkBox_2_clicked()
{

}

void MainWindow::on_radioButton_clicked()
{

}

void MainWindow::on_radioButton_2_clicked()
{

}

void MainWindow::on_radioButton_3_clicked()
{

}



void MainWindow::on_pushButton_2_clicked() //nextButton
{

        initSBox();
        initializeKey();
        initInvSBox();
        expansionKey();

    if( ui->checkBox->isChecked() && ui->checkBox_2->isChecked())
    {
        QMessageBox::information(this,"Result","please select either ENCODE or DECODE");
    }

    else if( !ui->checkBox_2->isChecked() && !ui->checkBox->isChecked())
    {

        QMessageBox::information(this,"Result","please select either ENCODE or DECODE");
    }

    if(ui->checkBox->isChecked())              //-----------------------encode-----------------------------------
    {
        if(ui->radioButton->isChecked() && !ui->radioButton_2->isChecked() && !ui->radioButton_3->isChecked())
        {
            //ECB

            ECBencryption(1);
            QString file_name = QString::fromStdString(fileName);
            QFile file(file_name);
            if(!file.open(QFile::ReadOnly | QFile::Text))
            {
                QMessageBox::warning(this,"title","File is not opened");
            }
            QTextStream in(&file);
            QString text = in.readAll();
            ui->textEdit->setPlainText(text);
            string news = printSHA(fileName);
            ui->lineEdit->setText(QString::fromStdString(news));
            file.close();

        }
        else if(!ui->radioButton->isChecked() && ui->radioButton_2->isChecked() && !ui->radioButton_3->isChecked())
        {
           //CBC
            ECBencryption(2);
            QString file_name = QString::fromStdString(fileName);
            QFile file(file_name);
            if(!file.open(QFile::ReadOnly | QFile::Text))
            {
                QMessageBox::warning(this,"title","File is not opened");
            }
            QTextStream in(&file);
            QString text = in.readAll();
            ui->textEdit->setPlainText(text);
            string news = printSHA(fileName);
            ui->lineEdit->setText(QString::fromStdString(news));
            file.close();

        }
        else if(!ui->radioButton->isChecked() && !ui->radioButton_2->isChecked() && ui->radioButton_3->isChecked())
        {
            //CTR
            ECBencryption(3);
            QString file_name = QString::fromStdString(fileName);
            QFile file(file_name);
            if(!file.open(QFile::ReadOnly | QFile::Text))
            {
                QMessageBox::warning(this,"title","File is not opened");
            }
            QTextStream in(&file);
            QString text = in.readAll();
            ui->textEdit->setPlainText(text);
            string news = printSHA(fileName);
            ui->lineEdit->setText(QString::fromStdString(news));
            file.close();

        }
        else QMessageBox::information(this,"Result","please select either CBC,CTR,EBC");

    }
    else                                      //------------------------decode-------------------------------------------
    {

        if(ui->radioButton->isChecked() && !ui->radioButton_2->isChecked() && !ui->radioButton_3->isChecked())
        {
            //ECB
            ECBdecryption(1);
            QString file_name = QString::fromStdString(fileName);
            QFile file(file_name);
            if(!file.open(QFile::ReadOnly | QFile::Text))
            {
                QMessageBox::warning(this,"title","File is not opened");
            }
            QTextStream in(&file);
            QString text = in.readAll();
            ui->textEdit->setPlainText(text);
            string news = printSHA(fileName);
            ui->lineEdit->setText(QString::fromStdString(news));
            file.close();

        }
        else if(!ui->radioButton->isChecked() && ui->radioButton_2->isChecked() && !ui->radioButton_3->isChecked())
        {
           //CBC
            ECBdecryption(2);
            QString file_name = QString::fromStdString(fileName);
            QFile file(file_name);
            if(!file.open(QFile::ReadOnly | QFile::Text))
            {
                QMessageBox::warning(this,"title","File is not opened");
            }
            QTextStream in(&file);
            QString text = in.readAll();
            ui->textEdit->setPlainText(text);
            string news = printSHA(fileName);
            ui->lineEdit->setText(QString::fromStdString(news));
            file.close();

        }
        else if(!ui->radioButton->isChecked() && !ui->radioButton_2->isChecked() && ui->radioButton_3->isChecked())
        {
            //CTR
            ECBdecryption(3);
            QString file_name = QString::fromStdString(fileName);
            QFile file(file_name);
            if(!file.open(QFile::ReadOnly | QFile::Text))
            {
                QMessageBox::warning(this,"title","File is not opened");
            }
            QTextStream in(&file);
            QString text = in.readAll();
            ui->textEdit->setPlainText(text);
            string news = printSHA(fileName);
            ui->lineEdit->setText(QString::fromStdString(news));
            file.close();

        }
        else QMessageBox::information(this,"Result","please select either CBC,CTR,EBC");
    }
}

void MainWindow::on_pushButton_3_clicked()
{

}

void MainWindow::on_pushButton_4_clicked()
{

}
