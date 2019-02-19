#include "subset_lb.h"
#include <iostream>


SubsetLoadBalancer::SubsetLoadBalancer() :
        subset_keys_({{"version", "env"},
                      {"app",     "version"},
                      {"x"}}) {
    initSubsetSelectorMap();
};

SubsetLoadBalancer::~SubsetLoadBalancer() {};


void SubsetLoadBalancer::initSubsetSelectorMap() {
    SubsetSelectorMap *selectors = &selectors_;
    const auto subset_keys(subset_keys_);
    for (const auto &selector_keys : subset_keys) {
        for (auto &key : selector_keys) {
            const auto &selector_it = selectors->subset_keys.find(key);
            if (selector_it == selectors->subset_keys.end()) {
                auto* next = new SubsetSelectorMap();
                selectors->subset_keys.emplace(std::pair<std::string, SubsetSelectorMap>(key, *next));
                selectors = next;
            } else {
                selectors = &selector_it->second;
            };
        }
        selectors = &selectors_;
    }
}

void SubsetLoadBalancer::printSubsetKeys() {
    for (auto i = subset_keys_.begin(); i != subset_keys_.end(); ++i) {
        for (const auto key : *i) {
            std::cout << key << ' ';
        }
        std::cout << std::endl;
    }
}

void SubsetLoadBalancer::printSelectors() {

    for (auto &keys: selectors_.subset_keys) {
        auto *p = &keys.first;
        doPrint(selectors_, p);
        std::cout << std::endl;
    }
}

void SubsetLoadBalancer::doPrint(const SubsetSelectorMap map, const std::string *key) {
    if (key == nullptr) {
        return;
    } else {
        std::cout << *key << ' ';
        const auto next = map.subset_keys.find(*key);
        if (next != map.subset_keys.end()){
            auto *p = &next->first;
            doPrint(next->second, p);

        }

    }
}