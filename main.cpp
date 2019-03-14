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
    const std::vector<std::string> match_criteria_vec = {"x","z"};
    const auto fallback = x->tryFindSelectorFallbackPolicy(match_criteria_vec);
    x->printFallback(fallback);

    //x->printSubsetKeys();
    delete x;
    return 0;
}


