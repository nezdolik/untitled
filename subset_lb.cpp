#include "subset_lb.h"
#include <iostream>


SubsetLoadBalancer::SubsetLoadBalancer() :
        subset_keys_top_({
                                 std::pair<std::set<std::string>, std::experimental::optional<Fallback>>({"version", "env"},
                                                                                           std::experimental::optional<Fallback>(
                                                                                                   Fallback::None)),
                                 std::pair<std::set<std::string>, std::experimental::optional<Fallback>>({"app", "version"},
                                                                                           std::experimental::nullopt),
                                 std::pair<std::set<std::string>, std::experimental::optional<Fallback>>({"x"},
                                                                                           std::experimental::optional<Fallback>(
                                                                                                   Fallback::Any)),
                                 std::pair<std::set<std::string>, std::experimental::optional<Fallback>>({"z", "x"},
                                                                                           std::experimental::optional<Fallback>(
                                                                                                   Fallback::Default)),
                         }) {
    initSubsetSelectorMap();
};

SubsetLoadBalancer::~SubsetLoadBalancer() {};


void SubsetLoadBalancer::initSubsetSelectorMap() {
    selectors_ = std::make_shared<SubsetSelectorMap>();
    SubsetSelectorMapPtr selectors = selectors_;
    for (const auto &selector_with_fallback : subset_keys_top_) {
        const auto &selector_keys = selector_with_fallback.first;
        int pos = 0;
        for (const auto &key : selector_keys) {
            const auto &selector_it = selectors->subset_keys.find(key);
            pos++;
            if (selector_it == selectors->subset_keys.end()) {
                //if this is last key for given selector, check if it has fallback specified
                if (pos == selector_keys.size() && selector_with_fallback.second) {
                    selectors->fallback = selector_with_fallback.second;
                }
                selectors->subset_keys.emplace(std::make_pair(key, std::make_shared<SubsetSelectorMap>()));
                selectors = selectors->subset_keys.find(key)->second;

            } else {
                selectors = selector_it->second;
            };
        }
        selectors = selectors_;
    }
}

std::experimental::optional<Fallback>
SubsetLoadBalancer::tryFindSelectorFallbackPolicy(const std::vector<std::string>& match_criteria_vec) const {
    SubsetSelectorMapPtr selectors = selectors_;
    for (uint32_t i = 0; i < match_criteria_vec.size(); i++) {
        const std::string &match_criterion = match_criteria_vec[i];
        const auto &subset_it = selectors->subset_keys.find(match_criterion);
        if (subset_it == selectors->subset_keys.end()) {
            // No subsets with this key (at this level in the hierarchy).
            break;
        }

        if (i + 1 == match_criteria_vec.size()) {
            // We've reached the end of the criteria, and they all matched.
            return selectors->fallback;
        }

        selectors = subset_it->second;
    }
    return std::experimental::nullopt;
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

    SubsetSelectorMapPtr selectors = selectors_;
    for (const auto &selector_with_fallback : subset_keys_top_) {
        const auto &selector_keys = selector_with_fallback.first;
        int pos = 0;
        for (const auto &key : selector_keys) {
            const auto &selector_it = selectors->subset_keys.find(key);
            std::cout << key << ' ';
            //if this is last key for given selector, check if it has fallback specified
            if (++pos == selector_keys.size() && selector_with_fallback.second) {
                printFallback(selector_with_fallback.second.value_or(Fallback::NotDefined));
            }
            selectors = selector_it->second;
        };
        std::cout << std::endl;
        selectors = selectors_;
    }

}

void SubsetLoadBalancer::printFallback(const std::experimental::optional<Fallback> &fallback) {
    if (fallback) {
        std::cout << "<Fallback: " << (fallback == Fallback::Any ? "Any>" :
                                       fallback == Fallback::Default ? "Default>"
                                                                     : "None>");
    } else {

        std::cout << "nullopt";
    }
}


void SubsetLoadBalancer::doPrint(const SubsetSelectorMapPtr map, const std::string *key) {
    if (key == nullptr) {
        return;
    } else {
        std::cout << *key << ' ';
        const auto next = map->subset_keys.find(*key);
        if (next != map->subset_keys.end()) {
            auto *p = &next->first;
            doPrint(next->second, p);

        }

    }
}

void SubsetLoadBalancer::printSelectorsCorrect(const SubsetSelectorMapPtr selectorMap) {
    const auto entries = selectorMap->subset_keys;
    for (const auto &selector_with_fallback : entries) {

        printFallback(selectorMap->fallback);
        const auto &key = selector_with_fallback.first;
        std::cerr << key << ' ';
        printSelectorsCorrect(selector_with_fallback.second);
    }
    std::cerr << " "<< std::endl;

}