#include "conversiontools.h"
#include <string>
#include <sstream>
using namespace std;
int toInt(std::string str)
{
    int result(0);
    stringstream  ss ;
    ss<<str;

    ss>>result;
    return result;  
}
std::string toStr(int number)
{

    stringstream  ss;

    ss<<number;
    return ss.str(); 
}