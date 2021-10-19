#include "User.h"
#include "Db.h"
#include <string>
#include <vector>
#include "conversiontools.h"
#include "randomtools.h"

#include <cstdlib>

using namespace std;
using namespace myRandomTools;


User::User(int userId):
    m_id(userId)
{
    m_filename="users.rov";
    Db userDb(m_filename);

    if(m_id<=0)
    {
        m_id=1;
    }
    vector<string> userdatas=(userDb.getRowCols(m_id));

    for(int i(0),c(userdatas.size());i<c;i++)
    {
        m_datas.push_back(userdatas[i]);
    }
    //checking user dir
    //if(!this->hasDirectory())
   // {
     // this->setDirectory();
    //}
    checkId();
}

User::~User()
{

}
bool User::hasDirectory()
{

    return this->getAll("user_directory")=="true"?true:false;
}
void User::setDirectory()
{
string dirCommand("mkdir datas\\users\\"+toStr(m_id));
system(dirCommand.c_str());
this->updateAll("user_directory","true");
}
string User::getDirectory()
{

    return this->getAll("id");
}
string User::about()
{

    return m_datas[1];
}

void User::updateAll(std::string colName, string newdata)
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

int User::getUserCover()
{
    /*
    Db userProfileDb("datas/pictures.rov");

    vector<string> userfiles=userProfileDb.getRows();
    int id(0);
    for(int i(1),c(userfiles.size());i<c;i++)
    {
        UserFile *userFile=new UserFile(i);
        if(userFile->getAll("is_profile")=="true" && userFile->getAll("user_id")==this->getAll("id"))
        {
            id=i;
            break;
        }
    }
    return id;*/
    //this is faster
    User *user=new User(toInt(this->getAll("id")));
    return toInt(user->getAll("user_cover_id"));
}
void User::setCover(int fileId)
{
}

//profile
int User::getUserProfile()
{
    /*
    Db userProfileDb("datas/pictures.rov");

    vector<string> userfiles=userProfileDb.getRows();
    int id(0);
    for(int i(1),c(userfiles.size());i<c;i++)
    {
        UserFile *userFile=new UserFile(i);
        if(userFile->getAll("is_profile")=="true" && userFile->getAll("user_id")==this->getAll("id"))
        {
            id=i;
            break;
        }
    }
    return id;*/
    //this is faster
    User *user=new User(toInt(this->getAll("id")));
    return toInt(user->getAll("user_profile_id"));
}
void User::setProfile(int fileId)
{

}
std::string User::getAll(std::string colName)
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
        Db newRowDb("datas/users.cpp");
        newRowDb.update(0,currentRow);
        //creating new col
    }*/

    /*if(m_datas[colId].size()<=0)
    {
        this->update(colId, "tsy fantatra");
    }*/
    /*if(colName=="user_hp" && m_datas[colId]=="tsy fantatra")
    {
        this->update(colId, "0");
    }*/

    return result;
}
std::string User::getAll(int id)
{
    return m_datas[id];
}
string User::update(int col, std::string newdata){

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
void User::updateDatas()
{
    for(int i(0),c=m_datas.size();i<c;i++)
    {
        m_datas.pop_back();
    }
    //get all datas again
    Db userDb(m_filename);
    vector<string> userdatas=(userDb.getRowCols(m_id));

    for(int i(0),c(userdatas.size());i<c;i++)
    {
        m_datas.push_back(userdatas[i]);
    }
}


bool User::checkId()
{

    if(toInt(this->getAll("id")) >0)
    {
        return true;
    }else{
        updateAll("id", toStr(m_id));
        return false;
    }
}






