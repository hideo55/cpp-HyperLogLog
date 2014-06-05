#include <igloo/igloo_alt.h>
#include <igloo/TapTestListener.h>
#include "hyperloglog.hpp"
#include <map>
#include <string>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <iomanip>
using namespace igloo;
using namespace hll;

namespace {
// Test utilities

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
}

Describe(hll_HyperLogLog) {
    Describe(create_instance) {
        It(pass_minimum_arugment_in_range) {
            HyperLogLog *hll = new HyperLogLog(4);
            Assert::That(hll != NULL);
            delete hll;
        }

        It(pass_maximum_argument_in_range) {
            HyperLogLog *hll = new HyperLogLog(16);
            Assert::That(hll != NULL);
            delete hll;
        }

        It(pass_out_of_range_argument_min) {
            AssertThrows(std::invalid_argument, HyperLogLog(3));
            Assert::That(LastException<std::invalid_argument>().what(),
                    Is().Containing("bit width must be in the range [4,16]"));
        }

        It(pass_out_of_range_argument_max) {
            AssertThrows(std::invalid_argument, HyperLogLog(17));
            Assert::That(LastException<std::invalid_argument>().what(),
                    Is().Containing("bit width must be in the range [4,16]"));
        }
    };

    It(get_register_size) {
        HyperLogLog *hll = new HyperLogLog(10);
        Assert::That(hll->registerSize(), Equals(pow(2, 10)));
        delete hll;

        hll = new HyperLogLog(16);
        Assert::That(hll->registerSize(), Equals(pow(2, 16)));
        delete hll;
    }

    It(estimate_cardinality) {
        for (int n = 0; n < 10; ++n) {
            HyperLogLog hll(16);
            size_t dataNum = 500;
            for (int i = 1; i < dataNum; ++i) {
                std::string str;
                getUniqueString(str);
                hll.add(str.c_str(), str.size());
            }
            double cardinality = hll.estimate();
            double errorRatio = fabs(dataNum - cardinality) / dataNum;
            Assert::That(errorRatio, IsLessThan(0.01));
        }
    }

    Describe(merge) {
        It(merge_registers) {
            HyperLogLog hll(16);
            size_t dataNum = 100;
            for (int i = 1; i < dataNum; ++i) {
                std::string str;
                getUniqueString(str);
                hll.add(str.c_str(), str.size());
            }

            HyperLogLog hll2(16);
            size_t dataNum2 = 200;
            for (int i = 1; i < dataNum2; ++i) {
                std::string str;
                getUniqueString(str);
                hll2.add(str.c_str(), str.size());
            }

            hll.merge(hll2);
            double cardinality = hll.estimate();
            double errorRatio = abs(dataNum + dataNum2 - cardinality) / (dataNum + dataNum2);
            Assert::That(errorRatio, IsLessThan(0.01));
        }

        It(merge_size_unmatched_registers) {
            HyperLogLog hll(16);
            HyperLogLog hll2(10);
            AssertThrows(std::invalid_argument, hll.merge(hll2));
            Assert::That(LastException<std::invalid_argument>().what(),
                    Is().Containing("number of registers doesn't match:"));
        }
    };

    It(clear_register) {
        HyperLogLog hll(16);
        size_t dataNum = 100;
        for (int i = 1; i < dataNum; ++i) {
            std::string str;
            getUniqueString(str);
            hll.add(str.c_str(), str.size());
        }
        Assert::That(hll.estimate(), !Equals(0.0f));
        hll.clear();
        Assert::That(hll.estimate(), Equals(0.0f));
    }
};

int main() {
    DefaultTestResultsOutput output;
    TestRunner runner(output);

    TapTestListener listener;
    runner.AddListener(&listener);

    runner.Run();
}

