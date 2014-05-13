#include <igloo/igloo_alt.h>
#include "hyperloglog.h"
#include <map>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace igloo;
using namespace hll;


static const char alphanum[] =
"0123456789"
"!@#$%^&*"
"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
"abcdefghijklmnopqrstuvwxyz";

static const int alphanumSize = sizeof(alphanum) - 1;

static void genRandomString(size_t len, std::string& str) {
    srand(time(0));
    for(size_t i = 0; i < len; ++i){
        char c = alphanum[rand() % alphanumSize];
        str.append(&c, 1);
    }
}

Describe(normal_pattern) 
{
    It(create_instance) 
    {
        HyperLogLog *hll = new HyperLogLog(10);
        Assert::That(hll != NULL);
        delete hll;
    }

    It(estimate)
    {
        HyperLogLog *hll = new HyperLogLog(16);
        std::map <std::string, bool> unique;
        size_t dataNum = 1000;
        for(size_t i = 1; i < dataNum; ++i){
            std::string str;
            do {
                genRandomString(10, str);
            } while(unique.find(str) != unique.end());
            unique.insert(std::make_pair(str, true));
            hll->add(str.c_str(), str.size());
        }
        double cardinality = hll->estimate();
        double errorRatio = abs(dataNum - cardinality)/dataNum;
        Assert::That(errorRatio < 0.01);
    }
};

int
main(int argc, const char* argv[])
{
    return TestRunner::RunAllTests(argc, argv);
}

