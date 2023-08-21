#include <iostream>
#include <fstream>
#include <list>
#include <sstream>
#include <string.h>
#include "Actions.h"
#include "Actions.cpp"
#include <cstdio>
#include <string>
#include <cstdlib>
//#include "r_star_tree.hpp"
using namespace std;
/*
//Ένα πρόγραμμα C++ αρχίζει με τη main()
static std::string const INPUT_FILE_NAME ="BlockedMap.osm";
static std::string const COPY_FILE_NAME ="copyFile.osm";
static std::string const COULD_NOT_OPEN = "Could not open ";
*/
int main ()
{
    Actions x;
    x.delete_entry("3","4553128281");
    if(remove("BlockedMap.osm")==0){
        rename("copyFile.osm","BlockedMap.osm");
    }else{
        cout<<"OH NO"<<endl;
    }
   /*
    ifstream in("BlockedMap.osm");
    ofstream out("BlockedMap.osm",ios::app);
    string v1, v2, v3, v4;
    in >> v1 >> v2 >> v3 >> v4;
    cout<<v3<<endl;
    v3 = "Himalaka"; // <- Do whatever you need to here.
    out << v1 << " " << v2 << " " << v3 << " " << v4;
    out << in.rdbuf();
    out.close();
    in.close();
    */
    return 0;
    /*
    string copyString;
    ifstream oldFileR;
    oldFileR.open("BlockedMap.osm", ios::app);
    ofstream temp;
    temp.open("NewFile.osm",ios::app);
    string deleteline="</block>";
    string findBlock="<block id=\"5\"";
    cout<<findBlock<<endl;
    string id;
    bool flag=true;
    while (getline(oldFileR, copyString)) {
        //Βρίσκει το τελευταίο μπλοκ
        int pos = copyString.find('</block>');
        id = copyString.substr(0, pos+1);
        if (deleteline.compare(id)!=0 || flag) {
            temp << copyString +"\n";
            if(copyString.compare(findBlock)==0){
                flag=false;
            }
        }
        //copyString.replace(copyString.find(deleteline),deleteline.length(),"");
        //temp << copyString << endl;
    }
    */
}
/*
    ifstream inputFile;
    ofstream copyFile;
    string numOfBlocks;
    inputFile.open(INPUT_FILE_NAME);
    getline(inputFile,numOfBlocks);
    numOfBlocks=getSubstringBetween(numOfBlocks);
    //app so it doesn't overwrite the file
    copyFile.open(COPY_FILE_NAME,ios::app);
    if (!copyFile.is_open()){
        cout<< COULD_NOT_OPEN + COPY_FILE_NAME;
        return 1;
    }
    if (!inputFile.is_open()){
        cout<< COULD_NOT_OPEN + INPUT_FILE_NAME;
        return 1;
    }
    cout<<"hi"<<endl;
    string copyString;
    string findBlock="<block id=\"" + numOfBlocks + "\"";
    cout<<findBlock<<endl;
    while (getline(inputFile, copyString)) { 
        //Copying the data of a specific block
        if(copyString.compare(findBlock)==0){
            copyFile << copyString << "\n";
            while (getline(inputFile, copyString)){
                copyFile << copyString << "\n";
                if(copyString.compare("</block>")==0){
                    break;
                }
            }
            break;
        }
    }
    */
    /*
    else {
		char ch;

		while (!inputFile.eof()) {
			inputFile >> ch;
			outputFile << ch;
		}

	}
    */
   /*
    string copyString;
    ifstream copyFileRead;
    copyFileRead.open(COPY_FILE_NAME);
    while (getline(copyFileRead, copyString)) { 
        copyFile << copyString << "\n";
    }
	inputFile.close();
    copyFile.close();
    cout<<"\""<<endl;
    */







/*
string copyString;
    ifstream copyFileRead;
    copyFileRead.open(COPY_FILE_NAME);
    while (getline(inputFile, copyString)) { 
        //Copying the data of a specific block
        if(copyString.compare("<block id=\"3\"")==0){
            copyFile << copyString << "\n";
            while (getline(inputFile, copyString)){
                copyFile << copyString << "\n";
                if(copyString.compare("</block>")==0){
                    break;
                }
            }
            break;
        }
    }
	inputFile.close();
    copyFile.close();
    */
