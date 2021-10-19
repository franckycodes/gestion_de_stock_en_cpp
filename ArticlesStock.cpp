#include "ArticlesStock.h"
#include "Db.h"
#include <string>
#include <vector>
#include "conversiontools.h"
#include "randomtools.h"

#include <cstdlib>

using namespace std;
using namespace myRandomTools;


ArticlesStock::ArticlesStock(int ArticlesStockId):
    m_id(ArticlesStockId)
{
    m_filename="articles.rov";
    Db ArticlesStockDb(m_filename);

    if(m_id<=0)
    {
        m_id=1;
    }
    vector<string> ArticlesStockdatas=(ArticlesStockDb.getRowCols(m_id));

    for(int i(0),c(ArticlesStockdatas.size());i<c;i++)
    {
        m_datas.push_back(ArticlesStockdatas[i]);
    }
    //checking ArticlesStock dir
    //if(!this->hasDirectory())
   // {
     // this->setDirectory();
    //}
    checkId();
}

ArticlesStock::~ArticlesStock()
{

}
bool ArticlesStock::hasDirectory()
{

    return this->getAll("ArticlesStock_directory")=="true"?true:false;
}
void ArticlesStock::setDirectory()
{
string dirCommand("mkdir datas\\ArticlesStocks\\"+toStr(m_id));
system(dirCommand.c_str());
this->updateAll("ArticlesStock_directory","true");
}
string ArticlesStock::getDirectory()
{

    return this->getAll("id");
}
string ArticlesStock::about()
{

    return m_datas[1];
}

void ArticlesStock::updateAll(std::string colName, string newdata)
{
    Db colDb(m_filename);
    vector<string> colsdata=colDb.getRowCols(0);
    int colId(0);
    //getting cols id
    for(int i(0),c(colsdata.size());i<c;i++)
    {

        if(colsdata[i]==colName)
        {
            colId=i;
            break;
        }
    }
    this->update(colId,newdata);
}
//cover

int ArticlesStock::getArticlesStockCover()
{
    /*
    Db ArticlesStockProfileDb("datas/pictures.rov");

    vector<string> ArticlesStockfiles=ArticlesStockProfileDb.getRows();
    int id(0);
    for(int i(1),c(ArticlesStockfiles.size());i<c;i++)
    {
        ArticlesStockFile *someArticleFile=new ArticlesStockFile(i);
        if(ArticlesStockFile->getAll("is_profile")=="true" && ArticlesStockFile->getAll("ArticlesStock_id")==this->getAll("id"))
        {
            id=i;
            break;
        }
    }
    return id;*/
    //this is faster
    ArticlesStock *someArticle=new ArticlesStock(toInt(this->getAll("id")));
    return toInt(someArticle->getAll("ArticlesStock_cover_id"));
}
void ArticlesStock::setCover(int fileId)
{
}

//profile
int ArticlesStock::getArticlesStockProfile()
{
    /*
    Db ArticlesStockProfileDb("datas/pictures.rov");

    vector<string> ArticlesStockfiles=ArticlesStockProfileDb.getRows();
    int id(0);
    for(int i(1),c(ArticlesStockfiles.size());i<c;i++)
    {
        ArticlesStockFile *someArticleFile=new ArticlesStockFile(i);
        if(ArticlesStockFile->getAll("is_profile")=="true" && ArticlesStockFile->getAll("ArticlesStock_id")==this->getAll("id"))
        {
            id=i;
            break;
        }
    }
    return id;*/
    //this is faster
    ArticlesStock *someArticle=new ArticlesStock(toInt(this->getAll("id")));
    return toInt(someArticle->getAll("ArticlesStock_profile_id"));
}
void ArticlesStock::setProfile(int fileId)
{

}
std::string ArticlesStock::getAll(std::string colName)
{
    Db colDb(m_filename);
    vector<string> colsdata=colDb.getRowCols(0);
    string result("");
    int colId(0);
    //getting cols id
    bool colExist(false);
    for(int i(0),c(colsdata.size());i<c;i++)
    {

        if(colsdata[i]==colName)
        {
            colId=i;
            colExist=true;
            break;
        }
    }
    if(!colExist)
    {
        result="0";
    }else{
        result=m_datas[colId];
    }
    colsdata.clear();

    /*if(!colExist)
    {
        string currentRow("");
        for(int i(0),c(colsdata.size()-1);i<c;i++)
        {
            if(colsdata[i].size()>1){
                currentRow+=colsdata[i]+"_rov_";
            }else{
                break;
            }
        }
        currentRow+=colName+"_rov_";
        Db newRowDb("datas/ArticlesStocks.cpp");
        newRowDb.update(0,currentRow);
        //creating new col
    }*/

    /*if(m_datas[colId].size()<=0)
    {
        this->update(colId, "tsy fantatra");
    }*/
    /*if(colName=="ArticlesStock_hp" && m_datas[colId]=="tsy fantatra")
    {
        this->update(colId, "0");
    }*/

    return result;
}
std::string ArticlesStock::getAll(int id)
{
    return m_datas[id];
}
string ArticlesStock::update(int col, std::string newdata){

    string newLine("");
    this->updateDatas();
    for(int i(0),c(m_datas.size());i<c;i++)
    {
        if(i==col)
        {
            newLine+=newdata+"_rov_";
        }else{
            newLine+=m_datas[i]+"_rov_";
        }
    }

    Db *updateDb= new Db(m_filename);

    updateDb->update(m_id,newLine);
    delete updateDb;
    updateDb=nullptr;
    return newLine;
}
void ArticlesStock::updateDatas()
{
    for(int i(0),c=m_datas.size();i<c;i++)
    {
        m_datas.pop_back();
    }
    //get all datas again
    Db ArticlesStockDb(m_filename);
    vector<string> ArticlesStockdatas=(ArticlesStockDb.getRowCols(m_id));

    for(int i(0),c(ArticlesStockdatas.size());i<c;i++)
    {
        m_datas.push_back(ArticlesStockdatas[i]);
    }
}


bool ArticlesStock::checkId()
{

    if(toInt(this->getAll("id")) >0)
    {
        return true;
    }else{
        updateAll("id", toStr(m_id));
        return false;
    }
}






