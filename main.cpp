#include <iostream>
#include "subset_lb.h"
//#include "foo.h"
#include <unordered_map>
#include <set>
#include <vector>
#include <string>

using namespace std;


int main() {
    SubsetLoadBalancer* x = new SubsetLoadBalancer();
    std::cout << "Hello, World!" << std::endl;
    x->printSelectors();
    delete x;
    return 0;
}


