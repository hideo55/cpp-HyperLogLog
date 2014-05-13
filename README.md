# HyperLoglog

C++ implementation of [HyperLogLog](http://algo.inria.fr/flajolet/Publications/FlFuGaMe07.pdf) algorithm.

## Usage

```C++

#include <vector>
#include <string>
#include <iostream>
#include "hyperloglog.hpp"

using namespace hll;

int main(){
    HyperLogLog hll(10);
    std::vector<string> somedata;

    //Load data to somedata

    std::vector<std::string>::iterator iter = somedata.begin();
    std::vector<std::string>::iterator iter_end = somedata.end();
    for(;iter != iter_end; ++iter){
        hll.add(iter->c_str(), iter->size());
    }

    double cardinality = hll.estimate();

    std::cout << "Cardinality:" << cardinality << std::endl;

    return 0;
}

```
## Document

http://hideo55.github.com/cpp-HyperLogLog/

## Author

Hideaki Ohno <hide.o.j55{at}gmail.com>

## License 

(The MIT License)

Copyright (c) 2013 Hideaki Ohno &lt;hide.o.j55{at}gmail.com&gt;

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
'Software'), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED 'AS IS', WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
