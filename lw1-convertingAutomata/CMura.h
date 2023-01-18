#pragma once
#include "CMiles.h"
#include "utils.h"
#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <vector>

class CMiles;

class CMura {
public:
    CMura() = default;
    void FromCSV(const std::string &csv);
    void FromData(const std::vector<std::string> &states,
                  const std::vector<std::string> &paths,
                  const std::vector<std::string> &output,
                  const std::vector<std::vector<std::string>> &transitions);
    std::string ConvertToCSV();
    void ToMiles(CMiles &miles);

private:
    void ReadOutputsCSV(const std::string &line);
    void ReadStatesCSV(const std::string &line);
    void ReadTransitionsCSV(const std::string &line);

    std::vector<std::string> m_states;
    std::vector<std::string> m_paths;
    std::vector<std::string> m_output;
    std::vector<std::vector<std::string>> m_transitions;
};
