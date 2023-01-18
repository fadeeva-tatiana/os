#include "utils.h"
#include <iostream>
#include <map>
#include <string>
#include <vector>

struct SMilesItem {
    std::string to;
    std::string out;
};

struct SMilesState {
    std::map<std::string, SMilesItem> transitions;
};

class CMiles {
public:
    CMiles() = default;

    void FromCSV(const std::string &csv) {
        std::vector<std::string> lines;

        Split(csv, '\n', lines);
        for (int i = 0; i < lines.size(); ++i) {
            auto line = lines[i];
            if (i == 0) {
                ReadStatesCSV(line);
            } else {
                ReadTransitionsCSV(line);
            }
        }
    }

private:
    void ReadStatesCSV(const std::string &line) {
        std::vector<std::string> states;
        Split(line, ';', states);
        for (const auto &state: states) {
            if (!state.empty()) {
                m_state.insert(std::make_pair(state, SMilesState{}));
                m_states.push_back(state);
            }
        }
    }

    void ReadTransitionsCSV(const std::string &line) {
        std::vector<std::string> transitions;
        Split(line, ';', transitions);
        auto path = transitions[0];
        m_paths.push_back(path);
        for (int i = 1; i < transitions.size(); ++i) {
            auto transition = transitions[i];
            std::vector<std::string> items;
            Split(transition, '/', items);
            auto st = m_state.find(m_states[i - 1]);
            st->second.transitions.insert(std::make_pair(path, SMilesItem{items[0], items[1]}));
        }
    }

    std::map<std::string, SMilesState> m_state;
    std::vector<std::string> m_states;
    std::vector<std::string> m_paths;
};
