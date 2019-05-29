
#pragma once

#include <unordered_map>
#include <set>
#include <vector>
#include <string>
#include  <experimental/optional>



enum class Fallback {
    NotDefined,
    None,
    Any,
    Default
};

struct SubsetSelectorMap;
typedef std::shared_ptr<SubsetSelectorMap> SubsetSelectorMapPtr;

struct SubsetSelectorMap {
    std::unordered_map<std::string, SubsetSelectorMapPtr> subset_keys;
    std::experimental::optional<Fallback> fallback;
};

class SubsetLoadBalancer {
private:
    SubsetSelectorMapPtr selectors_;
    const std::vector<std::pair<std::set<std::string>, std::experimental::optional<Fallback>>> subset_keys_top_;



    void doPrint(const SubsetSelectorMapPtr map, const std::string *key);



public:
    SubsetLoadBalancer();

    ~SubsetLoadBalancer();
    void initSubsetSelectorMap();
    void printSubsetKeys();
    void printSelectors();
    void printFallback(const std::experimental::optional<Fallback> &fallback);
    std::experimental::optional<Fallback> tryFindSelectorFallbackPolicy(const std::vector<std::string>&match_criteria_vec) const;
    void printSelectorsCorrect(const SubsetSelectorMapPtr selectorMap);
};

