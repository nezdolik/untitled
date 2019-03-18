#include <iostream>
#include "subset_lb.h"
#include <unordered_map>
#include <set>
#include <vector>
#include <string>

using namespace std;


int main() {
    SubsetLoadBalancer* x = new SubsetLoadBalancer();
    x->printSelectors();
    std::vector<std::string> match_criteria_vec{"x", "z"};

    auto fallback = x->tryFindSelectorFallbackPolicy(match_criteria_vec);
    x->printFallback(fallback);

    std::vector<std::string> match_criteria_vec1{"x"};

    fallback = x->tryFindSelectorFallbackPolicy(match_criteria_vec1);
    x->printFallback(fallback);

    std::vector<std::string> match_criteria_vec2{"pp"};

    fallback = x->tryFindSelectorFallbackPolicy(match_criteria_vec2);
    x->printFallback(fallback);

    std::vector<std::string> match_criteria_vec3{"env","version"};

    fallback = x->tryFindSelectorFallbackPolicy(match_criteria_vec3);
    x->printFallback(fallback);

    std::vector<std::string> match_criteria_vec4{"app","version"};

    fallback = x->tryFindSelectorFallbackPolicy(match_criteria_vec4);
    x->printFallback(fallback);

    delete x;
    return 0;
}


