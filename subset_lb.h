
#pragma once
#include <unordered_map>
#include <set>
#include <vector>
#include <string>

struct SubsetSelectorMap {
    std::unordered_map<std::string, SubsetSelectorMap> subset_keys;
};

class SubsetLoadBalancer {
private:
    SubsetSelectorMap selectors_;
    const std::vector<std::set<std::string> > subset_keys_top_;
    void doPrint(const SubsetSelectorMap map,const std::string* key);
public:
    SubsetLoadBalancer();
    ~SubsetLoadBalancer();
    void initSubsetSelectorMap();
    void printSubsetKeys();
    void printSelectors();
};

