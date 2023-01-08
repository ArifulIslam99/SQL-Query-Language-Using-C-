 #include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<vector>
#include <stack>
#include<iostream>
#include <fstream>
#include <typeinfo>
#include<sstream>
#include <bits/stdc++.h>
// Project Members
// MD ARIFUL ISALM        ID: 2019-1-60-140
// SYEDA TASFIA TASNIM    ID: 2019-1-60-137
//RAWNAK JAHAN TAIFA      ID: 2019-1-60-134


using namespace std ;
void printToken(vector<string> interToken)
{
    for(int i = 0 ; i < interToken.size() ; i++)
    {
        cout << interToken[i] << endl ;
    }
}

void printToken2(vector<string> interToken, vector<int> arr3)
{
    for(int j=0 ; j<arr3.size(); j++)
    {
        int attributeColumn = arr3[j];
        cout << interToken[attributeColumn] << "\t";

    }
    cout << "\n";
}

void createTable(vector<string> interToken)
{
    string temp = interToken[2] ;
    string temp2 = temp + ".config" ;
    const char* fileName = temp2.c_str() ;
    ofstream outfile;
    outfile.open(fileName);

    string temp3 = temp + ".data";
    const char* fileName2 = temp3.c_str();
    ofstream outfile2;
    outfile2.open(fileName2);


    string buffer = "" ;
    int flag = 0 ;
    for(int i = 3 ; i < interToken.size() ; i++)
    {
        buffer += interToken[i] ;
        int len = interToken[i].size() ;
        if(interToken[i][len-1] == ',')
        {
            buffer.erase(remove(buffer.begin(), buffer.end(), ','), buffer.end()) ;
            outfile << buffer << endl ;
            buffer = "" ;
            continue ;
        }
        buffer += " " ;
    }

    outfile << buffer << endl ;
    outfile.close() ;
}

int priority (string alpha)
{

    if(alpha == "|")
        return 1;

    if(alpha == "^")
        return 2;

    if(alpha == "!")
        return 3;

    if(alpha == "=" || alpha == ">" || alpha == "<" || alpha == "@" || alpha == "&" ) // @ --> >= and & --> <= and ~ --> !=
        return 4;

    return 0;
}

string convert2(vector<string> interToken, int position)
{
    stack <string>S;
    string postfix;

    for(int i = position+1 ; i < interToken.size(); i++)
    {
        const char * token = interToken[i].c_str();
        const char * great = ">";
        const char * orr = "|";
        const char * nott = "!";
        const char * equaa = "=";
        const char * andd = "^";
        const char * les = "<";

        if(strcmp(token, great) == 0 || strcmp(token, orr) == 0 ||
            strcmp(token, nott) == 0 || strcmp(token, equaa) == 0 || strcmp(token, andd) == 0 || strcmp(token, les) == 0)
        {
            while(!S.empty() && priority(token) <= priority(S.top()))
            {
                cout << priority(token);
                postfix += S.top() + " ";
                S.pop();
            }

            S.push(token);

        }
        else
        {
            postfix += interToken[i] + " ";
        }
    }


    while(!S.empty())
    {
        postfix += S.top();
        S.pop();

    }

    return postfix;
}


void insertData(vector<string> interToken)
{
    string temp = interToken[2] ;
    string temp3 = temp + ".data";
    const char* fileName2 = temp3.c_str();
    ofstream outfile2;
    outfile2.open(fileName2, std::ios_base::app);
    string buffer = "" ;
    int flag = 0 ;
    for(int i = 4 ; i < interToken.size() ; i++)
    {
        buffer += interToken[i] ;
        int len = interToken[i].size() ;
        if(interToken[i][len-1] == '#')
        {
            buffer.erase(remove(buffer.begin(), buffer.end(), '#'), buffer.end()) ;
            outfile2 << buffer + "#";
            cout << buffer << "\t";
            buffer = "" ;
            continue ;
        }
        buffer += " " ;
    }

    outfile2 << buffer << endl;
    cout << buffer << "are inserted";
    outfile2.close() ;
}

void showAll(vector<string> interToken)
{
    std::ifstream config_file(interToken[3] + ".config" );
    if(!config_file)
    {
        cout << "No such file has found!" <<endl;
    }

    std::vector<std::string> config;
    std::string tmp;
    while (std::getline(config_file, tmp))
    {
        config.push_back(tmp.substr(0, tmp.find_first_of(" ")));
    }
    config_file.close();

    for(int i=0; i<config.size()-1 ; i++)
    {
        cout << config[i] << "\t";

    }

    cout << "\n";
    cout << "---------------------------------------------------------------------";
    cout << "\n";
    //Read Data File
    std::ifstream file( interToken[3] + ".data" );
    if(!file)
    {
        cout << "No such file has found!" <<endl;
    }
    for( std::string line; getline( file, line ); )
    {
        std::replace( line.begin(), line.end(), '#', '\t');
        cout << line <<endl;
    }
}

void showSelectedByWhere(std::vector< string > operand, string operato, vector<string> interToken, int wp)
{
    string variable =  operand[0];
    string value = operand[1];
    const char * great = ">";
    const char * orr = "|";
    const char * nott = "!";
    const char * equaa = "=";
    const char * andd = "^";
    const char * les = "<";
    const char * operatorToken =  operato.c_str();

    int numOfAttr = interToken.size() - (( interToken.size()-wp)+3);
    std::vector< string > arr;

    for(int i=0; i<numOfAttr; i++)
    {
        string attrName = interToken[i+1];
        arr.push_back(attrName);
    }

    std::ifstream config_file(interToken[wp-1] + ".config" );
    if(!config_file)
    {
        cout << "No such file has found!" <<endl;
    }

    std::vector<std::string> config;
    std::vector<std::string> type;
    std::string tmp;
    int attrIdx = -1;
    string str_piece;

    while (std::getline(config_file, tmp))
    {
        config.push_back(tmp.substr(0, tmp.find_first_of(" ")));
        stringstream obj_ss(tmp);
        std::vector<std::string> chk_tp;
        while (getline(obj_ss, str_piece, ' '))
        {
            chk_tp.push_back(str_piece);
        }

        type.push_back(chk_tp[1]);
    }
    config_file.close();

    for(int i=0; i<config.size(); i++)
    {
        const char * s1 = config[i].c_str();
        const char * s2 = variable.c_str();
        if(strcmp(s1, s2)==0)
        {
            attrIdx = i;
        }
    }

    std::vector<std::string> arr2;
    std::vector< int > arr3;
    for(int i=0; i<config.size()-1 ; i++)
    {
        for(int j=0; j<arr.size() ; j++)
        {
            const char * s1 = config[i].c_str();
            const char * s2 = arr[j].c_str();

            if(strcmp(s1, s2) == 0 )
            {
                arr2.push_back(s1);
                arr3.push_back(i);
            }
        }

    }

    for(int i =0; i<arr2.size(); i++)
    {
        cout << arr2[i] + "\t";
    }

    cout << "\n";
    cout << "---------------------------------------------------------------------";
    cout << "\n";

    int valueINT = -1;
    if(attrIdx >= 0 )
    {
        string chk_type = type[attrIdx];
        if(chk_type == "INT")
        {
            valueINT = std::stoi(value);
        }


        //Read Data File
        std::ifstream file( interToken[wp-1] + ".data" );
        if(!file)
        {
            cout << "No such file has found!" <<endl;
        }
        for( std::string line; getline( file, line ); )
        {
            std::replace( line.begin(), line.end(), '#', '\t');
            stringstream obj_ss(line);
            std::vector<std::string> arr4;
            while (getline(obj_ss, str_piece, '\t'))
            {
                arr4.push_back(str_piece);
            }

            if( valueINT >= 0)
            {
                if( operato == "=" && std::stoi(arr4[attrIdx]) == valueINT)
                {
                    printToken2(arr4, arr3);
                }
                else if(  operato == ">" && std::stoi(arr4[attrIdx]) > valueINT )
                {
                     printToken2(arr4, arr3);
                }
                else if(operato == "<" && std::stoi(arr4[attrIdx]) < valueINT)
                {
                     printToken2(arr4, arr3);
                }
                else if(operato == "!" && std::stoi(arr4[attrIdx]) != valueINT)
                {
                     printToken2(arr4, arr3);
                }

            }
            else
            {
                if( operato == "=" && arr4[attrIdx] == value)
                {
                    printToken2(arr4, arr3);
                }
                else if(operato == "!" && arr4[attrIdx] != value)
                {
                    printToken2(arr4, arr3);
                }
            }
        }

    }
    else
    {
        cout << "Attribute Not Found";
    }
}
void showAllByWhere(std::vector< string > operand, string operato, vector<string> interToken, int wp)
{
    string variable =  operand[0];
    string value = operand[1];
    const char * great = ">";
    const char * orr = "|";
    const char * nott = "!";
    const char * equaa = "=";
    const char * andd = "^";
    const char * les = "<";
    const char * operatorToken =  operato.c_str();
    std::ifstream config_file(interToken[wp-1] + ".config" );
    if(!config_file)
    {
        cout << "No such file has found!" <<endl;
    }
    std::vector<std::string> config;
    std::vector<std::string> type;
    std::string tmp;
    int attrIdx = -1;
    string str_piece;
    while (std::getline(config_file, tmp))
    {
        config.push_back(tmp.substr(0, tmp.find_first_of(" ")));
        stringstream obj_ss(tmp);
        std::vector<std::string> arr2;
        while (getline(obj_ss, str_piece, ' '))
        {
            arr2.push_back(str_piece);
        }
        type.push_back(arr2[1]);
    }
    config_file.close();
    for(int i=0; i<config.size(); i++)
    {
        const char * s1 = config[i].c_str();
        const char * s2 = variable.c_str();
        if(strcmp(s1, s2)==0)
        {
            attrIdx = i;
        }
    }

    int valueINT = -1;
    if(attrIdx >= 0 )
    {
        string chk_type = type[attrIdx];
        if(chk_type == "INT")
        {
            valueINT = std::stoi(value);
        }
        for(int i=0; i<config.size()-1 ; i++)
        {
            cout << config[i] << "\t";
        }
        cout << "\n";
        cout << "---------------------------------------------------------------------";
        cout << "\n";
        std::ifstream file( interToken[wp-1] + ".data" );
        if(!file)
        {
            cout << "No such file has found!" <<endl;
        }
        for( std::string line; getline( file, line ); )
        {
            std::replace( line.begin(), line.end(), '#', '\t');
            stringstream obj_ss(line);
            std::vector<std::string> arr3;
            while (getline(obj_ss, str_piece, '\t'))
            {
                arr3.push_back(str_piece);
            }

            if( valueINT >= 0)
            {
                if( operato == "=" && std::stoi(arr3[attrIdx]) == valueINT)
                {
                    cout << line << endl;
                }
                else if(  operato == ">" && std::stoi(arr3[attrIdx]) > valueINT )
                {
                    cout << line << endl;
                }
                else if(operato == "<" && std::stoi(arr3[attrIdx]) < valueINT)
                {
                    cout << line << endl;
                }
                else if(operato == "!" && std::stoi(arr3[attrIdx]) != valueINT)
                {
                    cout << line << endl;
                }

            }
            else
            {
                if( operato == "=" && arr3[attrIdx] == value)
                {
                    cout << line << endl;
                }
                else if(operato == "!" && arr3[attrIdx] != value)
                {
                    cout << line << endl;
                }
            }
        }

    }
    else
    {
        cout << "Attribute Not Found";
    }
}



void whereAll(vector<string> interToken, int wherePosition)
{
    stack <string>S;
    stack <string>S2;
    int size = interToken.size();
    for(int i = 1 ; i < size ; i++)
    {
        if(interToken[i] == "and")
        {
            interToken[i] = "^";
        }
        else if(interToken[i] == "or")
        {
            interToken[i] = "|" ;
        }
        else if(interToken[i] == ">=")
        {
            interToken[i] = "@";
        }
        else if(interToken[i] == "<=")
        {
            interToken[i] = "&";
        }
        else if(interToken[i] == "not")
        {
            interToken[i] = "!";
        }
    }
    std::ifstream config_file(interToken[wherePosition - 1] + ".config" );
    if(!config_file)
    {
        cout << "No such file has found!" <<endl;
    }

    string condition = "";
    for(int i = (wherePosition + 1) ; i < size ; i++)
    {
        const char * s1 = interToken[i].c_str();
        condition =  condition + s1;
    }

    std::vector< string > operand;
    string str_piece;
    string postfix;
    postfix = convert2(interToken, wherePosition);
    const char * great = ">";
    const char * orr = "|";
    const char * nott = "!";
    const char * equaa = "=";
    const char * andd = "^";
    const char * les = "<";
    stringstream obj_ss(postfix);
    string operato = "";
    while (getline(obj_ss, str_piece, ' '))
    {
        S.push(str_piece);
    }
    while(!S.empty())
    {
        string v = S.top();
        S2.push(v);
        S.pop();
    }
    while(!S2.empty())
    {
        string v = S2.top();
        const char * token = v.c_str();
        if(strcmp(token, great) == 0 || strcmp(token, orr) == 0 || strcmp(token, nott) == 0 || strcmp(token, equaa) == 0 ||
                strcmp(token, andd) == 0 || strcmp(token, les) == 0)
        {
            S2.pop();
            operato = token;
        }
        else
        {
            S2.pop();
            operand.push_back(token);
        }
        if(!operato.empty() && operand.size() == 2)
        {
            if(wherePosition == 4)
            {
                showAllByWhere(operand, operato, interToken, wherePosition);
            }
            else
            {
                showSelectedByWhere(operand, operato, interToken, wherePosition);
            }
        }
    }
}

void showSelected(vector<string> interToken)
{
    std::ifstream config_file(interToken[interToken.size() - 1] + ".config" );
    if(!config_file)
    {
        cout << "No such file has found!" <<endl;
    }
    int numOfAttr = interToken.size() - 3;
    std::vector< string > arr;
    for(int i=0; i<numOfAttr; i++)
    {
        string attrName = interToken[i+1];
        arr.push_back(attrName);
    }
    std::vector<std::string> config;
    std::string tmp;
    while (std::getline(config_file, tmp))
    {
        config.push_back(tmp.substr(0, tmp.find_first_of(" ")));
    }
    config_file.close();
    std::vector<std::string> arr2;
    std::vector< int > arr3;
    for(int i=0; i<config.size()-1 ; i++)
    {
        for(int j=0; j<arr.size() ; j++)
        {
            const char * s1 = config[i].c_str();
            const char * s2 = arr[j].c_str();
            if(strcmp(s1, s2) == 0 )
            {
                arr2.push_back(s1);
                arr3.push_back(i);
            }
        }
    }

    for(int i =0; i<arr2.size(); i++)
    {
        cout << arr2[i] + "\t";
    }
    cout << "\n";
    cout << "---------------------------------------------------------------------";
    cout << "\n";

    std::ifstream file( interToken[interToken.size() - 1] + ".data" );
    if(!file)
    {
        cout << "No such file has found!" <<endl;
    }

    for( std::string line; getline( file, line ); )
    {
        vector<string> interToken2 ;
        string intermediate ;
        stringstream check(line);
        char token = '#';
        while(getline(check, intermediate, token))
        {
            intermediate.erase(remove(intermediate.begin(), intermediate.end(), '#'), intermediate.end());
            if(intermediate.length()>0)
            {
                interToken2.push_back(intermediate) ;
            }
        }
        printToken2(interToken2, arr3);

    }

}



void parsing(string inputBuffer)
{
    string intermediate ;
    stringstream check(inputBuffer);
    char token = ' ' ;
    vector<string> interToken ;

    while(getline(check, intermediate, token))
    {
        intermediate.erase(remove(intermediate.begin(), intermediate.end(), '('), intermediate.end()) ;
        intermediate.erase(remove(intermediate.begin(), intermediate.end(), ')'), intermediate.end()) ;
        //intermediate.erase(remove(intermediate.begin(), intermediate.end(), '"'), intermediate.end()) ;
        intermediate.erase(remove(intermediate.begin(), intermediate.end(), ';'), intermediate.end()) ;
        if(intermediate.length()>0)
        {
            interToken.push_back(intermediate) ;
        }
    }
    //printToken(interToken) ;
    if(interToken[0] == "create")
    {
        if(interToken[1] == "table")
        {
            createTable(interToken) ;
        }
        else
        {
            cout << "Syntax error" << endl ;
        }
    }
    else if(interToken[0] == "insert")
    {
        if(interToken[1] == "into")
        {
            insertData(interToken);
        }
        else
        {
            cout << "Syntax error" << endl ;
        }
    }
    else if(interToken[0] == "select")
    {
        if( interToken[1] == "*")
        {
            if(interToken.size() > 4 && interToken[4] == "where")
            {
                whereAll(interToken, 4);
            }
            else
            {
                showAll(interToken);
            }
        }
        else
        {
            int wherePosition = -1;
            for(int i=0; i<interToken.size(); i++)
            {
                if(interToken[i] == "where")
                {
                    wherePosition = i;
                }
            }
            if(wherePosition > 0)
            {
                whereAll(interToken, wherePosition);
            }
            else
            {
                showSelected(interToken);
            }
        }
    }

    else
    {
        cout << "Syntax error" << endl ;
    }

}
int main()
{
    string inputBuffer = "";


    while(true)
    {
        string c ;
        getline(cin, c) ;
        inputBuffer += c ;
        int len = c.length() ;
        if(c[len-1] == ';') break ;
    }
    parsing(inputBuffer) ;




    return 0 ;
}
