#include "Actions.h"
#include <iostream>
#include <fstream>
#include <list>
#include <sstream>
#include <string.h>
#include <cstdio>
#include <sstream>
#include <string>
using namespace std;
static std::string const COPY_FILE_NAME ="copyFile.osm";
std::string getSubstringBetween(std::string input){
    std::string startStr="blocks=\"";
    std::string endStr="\"";
    std::size_t startPos=input.find(startStr);
    startPos+=startStr.length();
    std::size_t endPos=input.find(endStr,startPos);
    return input.substr(startPos,endPos-startPos);
}
Actions::Actions(){}
void Actions::add_entry(string existingFile, string newFile){
    ifstream oldFileR,newFileR;
    ofstream copyFile,oldFileW;
    oldFileR.open(existingFile);
    oldFileW.open(existingFile,ios::app);
    //app so it doesn't overwrite the file
    copyFile.open(COPY_FILE_NAME,ios::app);
    newFileR.open(newFile);
    if (!oldFileR.is_open()){
        cout<< existingFile;
        return ;
    }
    if (!copyFile.is_open()){
        cout<<"copyFile.osm";
        return ;
    }
        if (!newFileR.is_open()){
        cout<<newFile;
        return ;
    }
    string numOfBlocks;
    getline(oldFileR,numOfBlocks);
    numOfBlocks=getSubstringBetween(numOfBlocks);
    string copyString;
    ifstream copyFileRead;
    string findBlock="<block id=\"" + numOfBlocks + "\"";
    while (getline(oldFileR, copyString)) { 
        //Copying the data of a specific block
        if(copyString.compare(findBlock)==0){
            copyFile << copyString << "\n";
            while (getline(oldFileR, copyString)){
                copyFile << copyString << "\n";
                if(copyString.compare("</block>")==0){
                    break;
                }
            }
            break;
        }
    }
    while (getline(newFileR, copyString)) { 
        copyFile << copyString << "\n";
    }
    ifstream in_file(COPY_FILE_NAME, ios::binary);
    in_file.seekg(0, ios::end);
    int file_size = in_file.tellg();
    cout<<"Size of the file is"<<" "<< file_size<<" "<<"bytes";
    copyFile.close();
    newFileR.close();
    newFileR.open(newFile);
    oldFileR.close();
    oldFileR.open(existingFile);
    oldFileW.close();
    oldFileW.open(existingFile,ios::app);
    if(file_size<32000){
        cout<<"OH YES"<<endl;
        
    }else{
        string newblock="</block>";
        stringstream ss,ss2;
        int numB;
        ss<< numOfBlocks;
        ss>>numB;
        numB++;
        string str;
        ss2<<numB;
        ss2>>numOfBlocks;
        while (getline(oldFileR, copyString)) { 
            //Βρίσκει το τελευταίο μπλοκ
            if(copyString.compare(findBlock)==0){
                while (getline(oldFileR, copyString)){
                    //Βρίσκει το τέλος του block και δημιουργεί το νέο block
                    if(copyString.compare("</block>")==0){
                        oldFileW<<"\n";
                        oldFileW<<"<block id=\"" + numOfBlocks+"\""<<"\n";
                        while(getline(newFileR,copyString)){
                            oldFileW<<copyString << "\n";
                        }
                        break;
                    }
                }
                oldFileW<<"</block>";
                break;
            }
        }
    }
}