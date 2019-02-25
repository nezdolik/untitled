#include "subset_lb.h"
#include <iostream>


SubsetLoadBalancer::SubsetLoadBalancer() :
        subset_keys_top_({
                             {"version", "env"},
                             {"app",     "version"},
                             {"x"}
                         }) {
    initSubsetSelectorMap();
};

SubsetLoadBalancer::~SubsetLoadBalancer() {};


void SubsetLoadBalancer::initSubsetSelectorMap() {
    SubsetSelectorMap *selectors = &selectors_;
    for (const auto &selector_keys : subset_keys_top_) {
        for (const auto &key : selector_keys) {
            const auto &selector_it = selectors->subset_keys.find(key);
            if (selector_it == selectors->subset_keys.end()) {
                selectors->subset_keys.emplace(std::pair<std::string, SubsetSelectorMap>(key, SubsetSelectorMap()));
                selectors = &selectors->subset_keys.find(key)->second;
            } else {
                selectors = &selector_it->second;
            };
        }
        selectors = &selectors_;
    }
}

void SubsetLoadBalancer::printSubsetKeys() {
    for (auto i = subset_keys_top_.begin(); i != subset_keys_top_.end(); ++i) {
        for (const auto key : *i) {
            std::cout << key << ' ';
        }
        std::cout << std::endl;
    }
}

void SubsetLoadBalancer::printSelectors() {

    SubsetSelectorMap *selectors = &selectors_;
    for (const auto &selector_keys : subset_keys_top_) {
        for (const auto &key : selector_keys) {
            const auto &selector_it = selectors->subset_keys.find(key);
            std::cout << key << ' ';
            selectors = &selector_it->second;
        };
        std::cout << std::endl;
        selectors = &selectors_;
    }

}


void SubsetLoadBalancer::doPrint(const SubsetSelectorMap map, const std::string *key) {
    if (key == nullptr) {
        return;
    } else {
        std::cout << *key << ' ';
        const auto next = map.subset_keys.find(*key);
        if (next != map.subset_keys.end()) {
            auto *p = &next->first;
            doPrint(next->second, p);

        }

    }
}