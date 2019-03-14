
#pragma once

#include <unordered_map>
#include <set>
#include <vector>
#include <string>
#include  <optional>



enum class Fallback {
    None,
    Any,
    Default
};

struct SubsetSelectorMap {
    std::unordered_map<std::string, SubsetSelectorMap> subset_keys;
    std::optional<Fallback> fallback;
};

class SubsetLoadBalancer {
private:
    SubsetSelectorMap selectors_;
    const std::vector<std::pair<std::set<std::string>, std::optional<Fallback>>> subset_keys_top_;



    void doPrint(const SubsetSelectorMap& map, const std::string *key);



public:
    SubsetLoadBalancer();

    ~SubsetLoadBalancer();
    void initSubsetSelectorMap();
    void printSubsetKeys();
    void printSelectors();
    void printFallback(const std::optional<Fallback> &fallback);
    std::optional<Fallback> tryFindSelectorFallbackPolicy(const std::vector<std::string> &) const;
};

