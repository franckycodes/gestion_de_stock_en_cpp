#ifndef DB_H
#define DB_H
#include <string>
#include <vector>
#include <map>
class Db
{
    public:
        Db(std::string filename);
        Db(std::string filename, std::string lineseparator, std::string colseparator);
        ~Db();
        void read();
        void update();
        void update(int row, std::string newRow);
        void deleteRow(int row);
        
        std::string showCols();
        int totalSeparator(std::string str, std::string separator);
        std::vector<std::string> splitStr(std::string str, std::string separator);
        std::vector<int> getSeparators(std::string str, std::string separator);

        std::vector<int> getSeparatorsReverse(std::string str, std::string separator);
        std::string printArr(std::vector<int> arr);
        int getTotalRows();
        std::vector<std::string> getRows(); //no condition just getting all rows
        std::string showRows();
        std::string getRow(int row);
        //std::map<std::string, std::string> getRowKeys(int row);

        std::map<std::string, int> getRowKeys(int row);
        std::vector<std::string> getRowCols(int row);
        std::string getFilename() ;
        void encryptData();
        void unencryptData();
        bool addData(std::string newData);
        std::vector<std::string> getAllRows();

        std::vector<std::string> getAllRowsWhere(std::string col, std::string val);
        void removeData(); //empty file
        void setData(std::string datas);
    private:
        std::string m_filename;
        std::string m_lineseparator;
        std::string m_colseparator;
};
#endif // DB_H
