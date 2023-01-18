#pragma once
#include "CMura.h"
#include "utils.h"
#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <vector>

class CMura;

struct SMilesItem {
    std::string to;
    std::string out;
};

class CMiles {
public:
    CMiles() = default;
    void FromCSV(const std::string &csv);
    void FromData(const std::vector<std::string> &states,
                  const std::vector<std::string> &paths,
                  const std::vector<std::vector<SMilesItem>> &transitions);
    std::string ConvertToCSV();
    void ToMura(CMura &mura);

private:
    void ReadStatesCSV(const std::string &line);
    void ReadTransitionsCSV(const std::string &line);

    std::vector<std::string> m_states;
    std::vector<std::string> m_paths;
    std::vector<std::vector<SMilesItem>> m_transitions;
};
