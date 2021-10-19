#include "translateplugins.h"
#include <iostream>
#include "Db.h"
#include "conversiontools.h"
#include "strtools.h"
#include <vector>
#include <string>
 
using namespace std;
 
std::string getTranslate(std::string str, std::string language)
{

    Db translationDb("translations.rov");
    if(translationDb.getTotalRows()>0)
    {
        //faut ajouter un test ici
        vector<string> checkExists(translationDb.getAllRows());
        bool alreadyExists(false);
        int test;
        string firstRow;
        vector<string> datas={"", "", "", "", "", "", "", "", "", ""};
        for(int i(0),c(checkExists.size());i<c;i++)
        {
            
            datas=(translationDb.splitStr(checkExists[i], "_rov_"));
            //test=datas.size();
           
            //firstRow=toStr(datas.size());
            try{
            //firstRow+=replaceStr(datas[0], "_rov_", "", true)+", ";
            }catch(std::exception e){

            }
            try{
           
                firstRow = replaceText(datas[1], "_rov_", "")  ;

                // firstRow+= "\n";
                if(firstRow==str)
                {
                    alreadyExists=true;
                    break;
                }
            }catch(std::exception e)
            {

            }
            try{
            //firstRow+= datas[2]+", ";
            }catch(std::exception e)
            {

            }
            //firstRow+="\n";
            //if(checkExists[1]==str)
            //{
              //  alreadyExists=true;
            //}
        }
        //translationDb.addData(firstRow);
        if(!alreadyExists && str.size()>0){ 
            int id(translationDb.getTotalRows()+1);
            string mainText(str);
            string newTuple(toStr(id)+"_rov_"+mainText+"_rov_"+language+"_rov_");
            translationDb.addData(newTuple);
        }
    }else{
        string cols("id_rov_main text_rov_main language_rov_"); 
        translationDb.addData(cols);
    }

    //some language translation algorithm
    return str;
}
