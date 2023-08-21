#include "Actions.h"
#include <iostream>
#include <fstream>
#include <list>
#include <sstream>
#include <string.h>
#include <cstdio>
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
    ofstream copyFile;
    oldFileR.open(existingFile);
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
    //cout<<"Size of the file is"<<" "<< file_size<<" "<<"bytes";
    copyFile.close();
    copyFile.open(COPY_FILE_NAME);
    newFileR.close();
    newFileR.open(newFile);
    oldFileR.close();
    oldFileR.open(existingFile, ios::app);
    //checking if the new block will be over 32kb
    if(file_size<32000){
        string id;
        bool flag=true;
        string deleteline="</block>";
        int pos;
        while (getline(oldFileR, copyString)) {
            //Βρίσκει το τελευταίο μπλοκ
            /*
            if(pos!=-1){
               id = copyString.substr(0,pos+1);
            }
            */
            pos = copyString.find('</block>');
            id = copyString.substr(0,pos+1);
            //Δεν αντιγράφει το </block> που είναι στο τελευταίο block που θα μπει η εγγραφή
            if (deleteline.compare(id)!=0 || flag) {
                copyFile << copyString +"\n";
                if(copyString.compare(findBlock)==0){
                    flag=false;
                }
            }
        }
        while(getline(newFileR,copyString)){
            copyFile<<copyString << "\n";
        }
        copyFile<<"</block>";
    }else{
        stringstream ss,ss2;
        int numB;
        ss<< numOfBlocks;
        ss>>numB;
        numB++;
        ss2<<numB;
        ss2>>numOfBlocks;
        //Δημιουργεί ένα νέο αρχείο με το νέο μπλοκ και αυξάνει τον αριθμό των blocks
        copyFile<<"block id=\"0\" blocks=\"" + numOfBlocks + "</block>\n";
        getline(oldFileR,copyString);
        while(getline(oldFileR,copyString)){
            copyFile<<copyString<<"\n";
        }
        copyFile<<"<block id=\"" + numOfBlocks+"\""<<"\n";
        copyFile<<"\n";
        while(getline(newFileR,copyString)){
            copyFile<<copyString << "\n";
        }
        copyFile<<"</block>";
    }
    copyFile.close();
}
void Actions::delete_entry(string block, string id){
    ifstream oldFileR;
    ofstream copyFile;
    oldFileR.open("BlockedMap.osm");
    //app so it doesn't overwrite the file
    copyFile.open(COPY_FILE_NAME,ios::app);
    string copyString;
    bool flagBlock=true,flagNode=true;
    string deleteBlock="<block id=\"" + block + "\"";
    int pos;
    size_t found;
    int i=0;
    string node;
    int length=11+id.length();
    id=" <node id=\""+id;
    while (getline(oldFileR, copyString)) {
        i++;
            //Βρίσκει το τελευταίο μπλοκ
            /*
            if(pos!=-1){
               id = copyString.substr(0,pos+1);
            }
            */
            pos = copyString.find(id);
            node = copyString.substr(0,length);
            //Βρίσκει το block στο οποίο βρίσκεται η εγγραφή
            found = copyString.find(id);
            if(copyString.compare(deleteBlock)==0){
                flagBlock=false;
            }
            //Αν είναι στο σωστό block βρίσκει το id της εγγραφής
            if(!flagBlock && id.compare(node)==0){
                flagNode=false;
            }
            //Μόλις τελείωσει η εγγραφή συνεχίζει ακυρώνει τα flag για να αντιγράψει τα υπόλοιπα δεδομένα
            if(copyString.compare(" </node>")==0 && !flagBlock && !flagNode){
                cout<<i<<endl;
                flagNode=true;
                flagBlock=true;
            }
            if (flagBlock || flagNode) {
                copyFile << copyString +"\n";
            }
    }
}