#include "initapp.h"
#include "Db.h"

#include <vector>
#include <string>



using namespace std;

//creating all tables for the app
void createTables()
{
    //init translations
    Db *translationsDb=new Db("translations.rov");

    if(translationsDb->getTotalRows()<=0) {
        string cols("id_rov_main text_rov_main language_rov_"); 
        translationsDb->addData(cols);
    }
    //users 
    Db *usersDb=new Db("users.rov");

    if(usersDb->getTotalRows()<=0)
    {
        string cols("id_rov_user name_rov_user email_rov_pwd_rov_user points_rov_user intelligence_rov_");
        usersDb->addData(cols); 
    }
    //courses
    Db *courseDb=new Db("cours.rov");

    if(courseDb->getTotalRows()<=0)
    {
        string cols("id_rov_course name_rov_course description_rov_date creation_rov_author id_rov_");
        courseDb->addData(cols); 
    }
    //qcm questions
    Db *qcmQuestionsDb=new Db("qcmquestions.rov");

    if(qcmQuestionsDb->getTotalRows()<=0)
    {
        string cols("id_rov_question title_rov_answer id_rov_classroom id_rov_");
        qcmQuestionsDb->addData(cols); 
    }
    //qcm answers  
    Db *qcmAnswersDb=new Db("qcmanswers.rov"); 
    if(qcmAnswersDb->getTotalRows()<=0)
    {
        string cols("id_rov_qcm answer_rov_question id_rov_");
        qcmAnswersDb->addData(cols); 
    }

}