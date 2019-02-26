#include "subset_lb.h"
#include <iostream>


SubsetLoadBalancer::SubsetLoadBalancer() :
        subset_keys_top_({
                                 std::pair<std::set<std::string>, std::optional<Fallback>>({"version", "env"},
                                                                                           std::optional<Fallback>(
                                                                                                   Fallback::Default)),
                                 std::pair<std::set<std::string>, std::optional<Fallback>>({"app", "version"},
                                                                                           std::optional<Fallback>()),
                                 std::pair<std::set<std::string>, std::optional<Fallback>>({"x"},
                                                                                           std::optional<Fallback>(
                                                                                                   Fallback::None))
                         }) {
    initSubsetSelectorMap();
};

SubsetLoadBalancer::~SubsetLoadBalancer() {};


void SubsetLoadBalancer::initSubsetSelectorMap() {
    SubsetSelectorMap *selectors = &selectors_;
    for (const auto &selector_with_fallback : subset_keys_top_) {
        const auto &selector_keys = selector_with_fallback.first;
        int pos = 0;
        for (const auto &key : selector_keys) {
            const auto &selector_it = selectors->subset_keys.find(key);
            if (selector_it == selectors->subset_keys.end()) {
                //if this is last key for given selector, check if it has fallback specified
                if (++pos == selector_keys.size() && selector_with_fallback.second) {
                    selectors->fallback = selector_with_fallback.second;
                }
                selectors->subset_keys.emplace(std::make_pair(key, SubsetSelectorMap()));
                selectors = &selectors->subset_keys.find(key)->second;

            } else {
                selectors = &selector_it->second;
            };
        }
        selectors = &selectors_;
    }
}

void SubsetLoadBalancer::printSubsetKeys() {
//    for (auto i = subset_keys_top_.begin(); i != subset_keys_top_.end(); ++i) {
//        for (const auto key : *i) {
//            std::cout << key << ' ';
//        }
//        std::cout << std::endl;
//    }
}

void SubsetLoadBalancer::printSelectors() {

    SubsetSelectorMap *selectors = &selectors_;
    for (const auto &selector_with_fallback : subset_keys_top_) {
        const auto &selector_keys = selector_with_fallback.first;
        int pos = 0;
        for (const auto &key : selector_keys) {
            const auto &selector_it = selectors->subset_keys.find(key);
            std::cout << key << ' ';
            //if this is last key for given selector, check if it has fallback specified
            if (++pos == selector_keys.size() && selector_with_fallback.second) {
                std::cout << "<Fallback: " << (selector_with_fallback.second.value() == Fallback::Any ? "Any>" :
                                               selector_with_fallback.second.value() == Fallback::Default ? "Default>"
                                                                                                          : "None>");
            }
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