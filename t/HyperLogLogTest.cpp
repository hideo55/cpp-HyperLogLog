#include <igloo/igloo_alt.h>
#include "hyperloglog.h"
#include <map>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace igloo;
using namespace hll;

static const char alphanum[] = "0123456789"
        "!@#$%^&*"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";

static const int alphanumSize = sizeof(alphanum) - 1;

static void genRandomString(size_t len, std::string& str) {
    srand(time(0));
    for (size_t i = 0; i < len; ++i) {
        char c = alphanum[rand() % alphanumSize];
        str.append(&c, 1);
    }
}

static std::map<std::string, bool> GEN_STRINGS;
static void getUniqueString(std::string& str) {
    do {
        genRandomString(10, str);
    } while (GEN_STRINGS.find(str) != GEN_STRINGS.end());
    GEN_STRINGS.insert(std::make_pair(str, true));
}

Describe(hll_HyperLogLog) {
    It(create_instance) {
        HyperLogLog *hll = new HyperLogLog(10);
        Assert::That(hll != NULL);
        delete hll;
    }

    It(estimate) {
        for (int n = 0; n < 10; ++n) {
            HyperLogLog *hll = new HyperLogLog(16);
            size_t dataNum = 1000;
            for (int i = 1; i < dataNum; ++i) {
                std::string str;
                getUniqueString(str);
                hll->add(str.c_str(), str.size());
            }
            double cardinality = hll->estimate();
            double errorRatio = abs(dataNum - cardinality) / dataNum;
            Assert::That(errorRatio, IsLessThan(0.01));
        }
    }

    It(merge) {
            HyperLogLog *hll = new HyperLogLog(16);
            size_t dataNum = 1000;
            for (int i = 1; i < dataNum; ++i) {
                std::string str;
                getUniqueString(str);
                hll->add(str.c_str(), str.size());
            }

            HyperLogLog *hll2 = new HyperLogLog(16);
            size_t dataNum2 = 200;
            for (int i = 1; i < dataNum2; ++i) {
                std::string str;
                getUniqueString(str);
                hll2->add(str.c_str(), str.size());
            }

            hll->merge(*hll2);
            double cardinality = hll->estimate();
            double errorRatio = abs(dataNum + dataNum2 - cardinality) / (dataNum + dataNum2);
            Assert::That(errorRatio, IsLessThan(0.01));
    }
};

int main(int argc, const char* argv[]) {
    return TestRunner::RunAllTests(argc, argv);
}

