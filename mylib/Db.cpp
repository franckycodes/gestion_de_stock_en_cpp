#include "Db.h"
#include <fstream>
#include <string>
#include <vector>
#include "conversiontools.h"
#include "strtools.h"
#include <map>
#include <cstdlib>
using namespace std;

Db::Db(string filename) : m_filename(filename)
{
    m_lineseparator = "_line_";
    m_colseparator = "_rov_";
}

Db::Db(string filename, string lineseparator, std::string colseparator) : m_filename(filename),
                                                                          m_lineseparator(lineseparator),
                                                                          m_colseparator(colseparator)
{
}
Db::~Db()
{
}
//getting a specific row cols
vector<string> Db::getRowCols(int row)
{
    string mydatas(this->getRow(row)); //get selected row
    vector<string> rows(50, "");
    string separator(this->m_colseparator);
    vector<int> separators = this->getSeparators(mydatas, separator);
    //rows.push_back(toStr(separators.size()));
    int counter(0);
    string line("");

    //initializing array through data cols
    /*string colsData=this->getRow(0);
    vector<int> separateCols=this->getSeparators(colsData,separator);
*/
    //minimum 30 columns
    /*for(int i(0), c=30;i<c;i++)
    {
        rows[i]="unknown values";
    }*/

    for (int i(0), c = separators.size(); i < c; i++)
    {
        line = getStr(mydatas, counter, separators[i]);
        /*if(line.size()<=0)
            line="unknown";*/
        rows[i] = line;
        //rows.push_back("datas ( "+toStr(counter)+"  ,  "+toStr(separators[i])+") ");
        counter = separators[i] + separator.size();
        //counter=separators[i];
    }
    separators.clear();

    return rows;
}
//getting row keys
/*
std::map<std::string, std::string> Db::getRowKeys(int row)
{
    string cols(this->getRow(0));
    vector<string> colsArr=this->getRowCols(0);
    map<string, int> keysStored;
    //mapping each cols to rows data
    vector<string> selectedRow; //=this->getRowCols(row);
    vector<string> tempSelectedRow=this->getRowCols(row);
    //initialize rows
    for(int i(0),c=colsArr.size();i<c;i++)
    {
        selectedRow[i]="unknown values";
    }
    //update row values
    for(int i(0),c=tempSelectedRow.size();i<c;i++)
    {
        selectedRow[i]=tempSelectedRow[i];
    }

    //mapping keys
    for(int i(0),c=colsArr.size();i<c;i++)
    {
        keysStored[colsArr[i]]=selectedRow[i];
    }
    return keysStored;
}
*/
//getting a specific row
string Db::getRow(int row)
{
    //row+=1;
    vector<string> rows = this->getRows();
    string result("");
    for (int i(0), c(rows.size()); i < c; i++)
    {
        if (i == row)
        {
            result = rows[i];
            break;
        }
    }
    rows.clear();
    return result;
}
//delete row
void Db::deleteRow(int row)
{
    vector<string> rows = this->getRows();
    std::string newRow("");

    ifstream readDb(m_filename.c_str());
    ofstream writeDb(m_filename.c_str());

    string previousData("");
    string currentData("");
    string nextData("");

    //int counter(0);
    //string datas("");
    if (readDb)
    {
        //getting all datas

        //debug only
        //system(("notepad "+toStr(rows.size())+".txt").c_str());
        for (int i(0), c(rows.size()); i < c; i++)
        {
            if (i < row)
            {
                previousData += rows[i] + "_line_";
            }
            else if (i == row)
            {
                currentData = rows[i];
            }
            else if (i > row)
            {
                nextData += rows[i] + "_line_";
            }
        }

        newRow += "_line_";
        //updating
    }
    readDb.close();
    if (writeDb)
    {
        writeDb << previousData;
        //writeDb << newRow  ;
        writeDb << nextData;
    }
    writeDb.close();
}
//update row
void Db::update(int row, string newRow)
{
    vector<string> rows = this->getRows();

    ifstream readDb(m_filename.c_str());
    ofstream writeDb(m_filename.c_str());

    string previousData("");
    string currentData("");
    string nextData("");

    //int counter(0);
    //string datas("");
    if (readDb)
    {
        //getting all datas

        //debug only
        //system(("notepad "+toStr(rows.size())+".txt").c_str());
        for (int i(0), c(rows.size()); i < c; i++)
        {
            if (i < row)
            {
                previousData += rows[i] + "_line_";
            }
            else if (i == row)
            {
                currentData = rows[i];
            }
            else if (i > row)
            {
                nextData += rows[i] + "_line_";
            }
        }

        newRow += "_line_";
        //updating
    }
    readDb.close();
    if (writeDb)
    {
        writeDb << previousData;
        writeDb << newRow;
        writeDb << nextData;
    }
    writeDb.close();
    rows.clear();
}
//return all rows into string
string Db::showRows()
{
    vector<string> photos = this->getRows();
    string allPhotos("");
    for (int i(0), c(photos.size()); i < c; i++)
    {
        allPhotos += photos[i] + "\n";
    }

    photos.clear();
    return allPhotos;
}
bool Db::addData(string newData)
{
    bool added(false);
    ofstream writeDb(m_filename.c_str(), ios::app);

    if (writeDb)
    {
        newData += "_line_";
        writeDb << ("\n" + newData);
        added = true;
    }
    else
    {
        system("pause");
    }
    writeDb.close();
    return added;
}
void Db::update()
{
}

//showing db columns
string Db::showCols()
{

    ifstream myDb(m_filename);
    string line("");
    string datas("");
    int i(0);
    if (myDb)
    {
        while (getline(myDb, line))
        {
            datas += line;
            if (i > 0)
            {
                break;
            }
            i++;
        }
    }
    else
    {
        datas += "error file not found";
    }
    myDb.close();
    return datas;
}
//getting filename
string Db::getFilename()
{
    return m_filename;
}
//get all rows where
std::vector<std::string> Db::getAllRowsWhere(std::string col, std::string val)
{
    std::vector<std::string> result;
    ifstream db(this->m_filename.c_str());
    string line("");
    if (db)
    {
        std::string allCols("");
        int i(0);
        while (getline(db, line))
        {
            //add line with data only
            if (line.size() > 0 && i > 0)
            {
                if (allCols.find(col) && line.find(val))
                {
                    result.push_back(line);
                }
            }

            if (i == 0)
            {
                allCols = line;
            }
            i++;
        }
    }
    else
    {
        Db errorDb("error.log");
        errorDb.removeData();
        errorDb.setData("file not found error : " + this->m_filename + ", " + this->m_filename + "\n\n");
        /*ofstream errStream("error.log");
        if(errStream)
        {
            errStream << "file not found error: "<< this->m_filename <<" not found\n";
        }*/
    }
    db.close();
    return result;
}
//get all rows
std::vector<std::string> Db::getAllRows()
{

    std::vector<std::string> result;
    ifstream db(this->m_filename.c_str());
    string line("");
    if (db)
    {

        while (getline(db, line))
        {
            //add line with data only
            if (line.size() > 0)
                result.push_back(line);
        }
    }
    else
    {
        Db errorDb("error.log");
        errorDb.removeData();
        errorDb.setData("file not found error : " + this->m_filename + ", " + this->m_filename + "\n\n");
        /*ofstream errStream("error.log");
        if(errStream)
        {
            errStream << "file not found error: "<< this->m_filename <<" not found\n";
        }*/
    }
    db.close();
    return result;
}
//getting rows without conditions
vector<string> Db::getRows()
{

    vector<string> rows;
    //rows.push_back("shit");

    ifstream db(this->m_filename.c_str());
    string datas("");
    string line("");
    if (db)
    {

        while (getline(db, line))
        {
            datas += line + "\n";
        }
        string separator(this->m_lineseparator);
        vector<int> separators = this->getSeparators(datas, separator);

        //rows.push_back(toStr(separators.size()));
        int counter(0);
        for (int i(0), c = separators.size(); i < c; i++)
        {
            rows.push_back(getStr(datas, counter, separators[i]));
            //rows.push_back("datas ( "+toStr(counter)+"  ,  "+toStr(separators[i])+") ");
            counter = separators[i] + separator.size();
            //counter=separators[i];
        }
    }
    else
    {
        rows.push_back("file not found");
    }
    db.close();
    return rows;
}

//getting total rows or total entries in the database
int Db::getTotalRows()
{
    ifstream myDb(m_filename);
    string line("");
    string datas("");
    int i(0);
    if (myDb)
    {
        while (getline(myDb, line))
        {
            if (line.size() > 0)
            {
                datas += line;
                i++;
            }
        }
    }
    else
    {
        datas += "error file not found";
    }
    myDb.close();
    return i - 1; //because our db start with line columns
    //return this->getSeparators(datas,this->m_lineseparator).size();
}
//miteste raha misy mot noeritreretina ao anaty variable std::string
int Db::totalSeparator(std::string str, std::string separator)
{
    bool result(true);
    int totalFound = 0;
    int counter = 0;
    for (int i(0), c(str.size()); i < c; i++)
    {
        if (str[i] == separator[counter])
        {
            result = true; //reinitialize test variable
            for (int j(i), k(i + separator.size()); j < k; j++)
            {
                if (str[j] == separator[counter++])
                {
                    result &= true;
                }
            }
            if (result)
            {

                i = i + separator.size() - 1; //move i to right index
                totalFound += 1;
                counter = 0; //reinitialize separator counter
            }
        }
    }
    return totalFound;
}

vector<int> Db::getSeparators(std::string str, std::string separator)
{
    bool result(true);
    int totalFound = 0;
    int counter = 0;
    vector<int> separatorsIndex;

    for (int i(0), c(str.size()); i < c; i++)
    {
        if (str[i] == separator[counter])
        {
            result = true; //reinitialize test variable
            for (int j(i), k(i + separator.size()); j < k; j++)
            {
                if (str[j] == separator[counter++])
                {
                    result &= true;
                }
                else
                {
                    result &= false;
                    break;
                }
            }
            if (result)
            {
                separatorsIndex.push_back(i);
                i = i + separator.size() - 1; //move i to right index

                totalFound += 1;
            }
            counter = 0; //reinitialize separator counter no matter the result
        }
    }
    return separatorsIndex;
}
//split
std::vector<std::string> Db::splitStr(std::string str, std::string separator)
{
    std::vector<std::string> allWords;
    str += separator;
    std::vector<int> separators(this->getSeparators(str, separator));
    int temp = 0;

    for (int i(0), c(separators.size()); i < c; i++)
    {
        allWords.push_back(getStr(str, temp, separators[i]));
        temp = separators[i];
    }
    separators.clear();
    return allWords;
}
//reverse separators
vector<int> Db::getSeparatorsReverse(std::string str, std::string separator)
{
    bool result(true);
    int totalFound = 0;
    int counter = 0;
    vector<int> separatorsIndex;

    for (int i(str.size()); i >= 0; i--)
    {
        if (str[i] == separator[counter])
        {
            result = true; //reinitialize test variable
            for (int j(i), k(i - separator.size()); j >= k; j--)
            {
                if (str[j] == separator[counter++])
                {
                    result &= true;
                }
                else
                {
                    result &= false;
                    break;
                }
            }
            if (result)
            {

                separatorsIndex.push_back(i);
                i = i - separator.size() - 1; //move i to right index

                totalFound += 1;
                counter = 0; //reinitialize separator counter
            }
        }
    }
    return separatorsIndex;
}

string Db::printArr(vector<int> arr)
{

    string indexes("");
    for (int i(0), c(arr.size()); i < c; i++)
    {
        indexes += toStr(arr[i]) + ", ";
    }

    return indexes;
}

//remove data, empty file
void Db::removeData()
{
    ofstream mystream(this->m_filename.c_str());

    if (mystream)
    {

        mystream << "";
    }
}

//add data to file
void Db::setData(std::string datas)
{
    ofstream mystream(this->m_filename.c_str());

    if (mystream)
    {

        mystream << datas;
    }
}
