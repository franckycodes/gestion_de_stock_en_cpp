#include "strtools.h"
#include <string>
#include <string.h>
#include "conversiontools.h"
using namespace std;

std::string  getStr(std::string mainStr, int minIndex, int maxIndex)
{
	std::string result("");

	for(int i(minIndex),c(maxIndex);i<c;i++)
	{
		result += mainStr[i];
	}
	return result;
}

int getTotalWords(std::string books)
{
    int totalFound(0);

    for(int i(0),c(books.size());i<c;i++)
    {
        //basic condition
        
        //conditions  || books[i]=="." || books[i]=="," || books[i]==""
        if(books[i]==' ' || books[i]=='\n')
        {
            totalFound++;
        }
    }
    return totalFound;
}

//for a symbol only
std::string replaceStr(std::string mainStr, std::string toReplace, std::string replacement, bool escapeSymbol)
{
    std::string result("");

    for(int i(0),c(mainStr.length());i<c;i++)
    {
        if(escapeSymbol){
            if(mainStr[i]!=toReplace[0])
            {
                result+=mainStr[i];
            }
        }else{
            if(mainStr[i]==toReplace[0])
            {
                mainStr[i]=replacement[0];
            }
        }
    }
    return escapeSymbol?result:mainStr;
}



std::string toUpperCase(std::string str)
{
    /*for(int i(0),c(str.size());i<c;i++)
    {
        str[i]=strupr(str[i])
    }*/
    return "";
}
std::string toLowerCase(std::string str)
{
    /*
    for(int i(0),c(str.size());i<c;i++)
    {
         str[i]=strlwr(str[i])
    }*/
    return "";
}

//_rov_hello  world_rov_
std::string replaceText(std::string mainStr, std::string toReplace, std::string replacement)
{ 
    const int mainPos(mainStr.find(toReplace));
    const int toReplaceSize(toReplace.size());
    std::string result("");
    for(int i(0),c(mainStr.size());i<c;i++)
    {
        if(i!=mainPos && i>=toReplaceSize)
        { 
            result+=mainStr[i]; 
        }
    }

    // for(int i(mainPos),c(mainPos+toReplace.size());i<c;i++)
    // {
    //     result+=mainStr[i];
    // }
    return result; 
}
