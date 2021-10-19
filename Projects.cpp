#include "Projects.h"
#include "Db.h"
#include <string>
#include <vector>
#include "conversiontools.h"
#include "randomtools.h"

#include <cstdlib>

using namespace std;
using namespace myRandomTools;


Projects::Projects(int ProjectsId):
    m_id(ProjectsId)
{
    m_filename="codes.rov";
    Db ProjectsDb(m_filename);

    if(m_id<=0)
    {
        m_id=1;
    }
    vector<string> Projectsdatas=(ProjectsDb.getRowCols(m_id));

    for(int i(0),c(Projectsdatas.size());i<c;i++)
    {
        m_datas.push_back(Projectsdatas[i]);
    }
    //checking Projects dir
    //if(!this->hasDirectory())
   // {
     // this->setDirectory();
    //}
    checkId();
}

Projects::~Projects()
{

}
bool Projects::hasDirectory()
{

    return this->getAll("Projects_directory")=="true"?true:false;
}
void Projects::setDirectory()
{
string dirCommand("mkdir datas\\Projectss\\"+toStr(m_id));
system(dirCommand.c_str());
this->updateAll("Projects_directory","true");
}
string Projects::getDirectory()
{

    return this->getAll("id");
}
string Projects::about()
{

    return m_datas[1];
}

void Projects::updateAll(std::string colName, string newdata)
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

int Projects::getProjectsCover()
{
    /*
    Db ProjectsProfileDb("datas/pictures.rov");

    vector<string> Projectsfiles=ProjectsProfileDb.getRows();
    int id(0);
    for(int i(1),c(Projectsfiles.size());i<c;i++)
    {
        ProjectsFile *ProjectsFile=new ProjectsFile(i);
        if(ProjectsFile->getAll("is_profile")=="true" && ProjectsFile->getAll("Projects_id")==this->getAll("id"))
        {
            id=i;
            break;
        }
    }
    return id;*/
    //this is faster
    Projects *projects=new Projects(toInt(this->getAll("id")));
    return toInt(projects->getAll("Projects_cover_id"));
}
void Projects::setCover(int fileId)
{
}

//profile
int Projects::getProjectsProfile()
{
    /*
    Db ProjectsProfileDb("datas/pictures.rov");

    vector<string> Projectsfiles=ProjectsProfileDb.getRows();
    int id(0);
    for(int i(1),c(Projectsfiles.size());i<c;i++)
    {
        ProjectsFile *ProjectsFile=new ProjectsFile(i);
        if(ProjectsFile->getAll("is_profile")=="true" && ProjectsFile->getAll("Projects_id")==this->getAll("id"))
        {
            id=i;
            break;
        }
    }
    return id;*/
    //this is faster
    Projects *projects=new Projects(toInt(this->getAll("id")));
    return toInt(projects->getAll("Projects_profile_id"));
}
void Projects::setProfile(int fileId)
{

}
std::string Projects::getAll(std::string colName)
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
        Db newRowDb("datas/Projectss.cpp");
        newRowDb.update(0,currentRow);
        //creating new col
    }*/

    /*if(m_datas[colId].size()<=0)
    {
        this->update(colId, "tsy fantatra");
    }*/
    /*if(colName=="Projects_hp" && m_datas[colId]=="tsy fantatra")
    {
        this->update(colId, "0");
    }*/

    return result;
}
std::string Projects::getAll(int id)
{
    return m_datas[id];
}
string Projects::update(int col, std::string newdata){

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
void Projects::updateDatas()
{
    for(int i(0),c=m_datas.size();i<c;i++)
    {
        m_datas.pop_back();
    }
    //get all datas again
    Db ProjectsDb(m_filename);
    vector<string> Projectsdatas=(ProjectsDb.getRowCols(m_id));

    for(int i(0),c(Projectsdatas.size());i<c;i++)
    {
        m_datas.push_back(Projectsdatas[i]);
    }
}


bool Projects::checkId()
{

    if(toInt(this->getAll("id")) >0)
    {
        return true;
    }else{
        updateAll("id", toStr(m_id));
        return false;
    }
}






