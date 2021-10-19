#include "randomtools.h"
#include <cstdlib>
#include <ctime>


using namespace std;
using namespace myRandomTools;


int myRandomTools::getRandomNumber(int min, int max)
{
    return rand()%(max-min);
}
