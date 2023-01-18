#include "./CMiles.h"

void CMiles::FromCSV(const std::string &csv) {
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

void CMiles::FromData(
        const std::vector<std::string> &states,
        const std::vector<std::string> &paths,
        const std::vector<std::vector<SMilesItem>> &transitions) {
    m_states = states;
    m_paths = paths;
    m_transitions = transitions;
}

std::string CMiles::ConvertToCSV() {
    std::string csv;
    for (const auto &st: m_states) {
        csv.append(";" + st);
    }
    csv.append("\n");
    for (int i = 0; i < m_paths.size(); ++i) {
        csv.append(m_paths[i]);
        for (auto &j: m_transitions[i]) {
            csv.append(";" + j.to + "/" + j.out);
        }
        csv.append("\n");
    }
    return csv;
}

void CMiles::ToMura(CMura &mura) {
    std::vector<std::string> ids;
    std::vector<std::string> statesTransitions;
    std::vector<std::string> outs;
    for (const auto &lines: m_transitions) {
        for (const auto &transition: lines) {
            auto id = transition.to + transition.out;
            if (std::find(ids.begin(), ids.end(), id) == ids.end()) {
                ids.push_back(id);
                statesTransitions.push_back(transition.to);
                outs.push_back(transition.out);
            }
        }
    }

    std::vector<std::string> newStates;
    for (int i = 0; i < ids.size(); ++i) {
        newStates.push_back("S" + std::to_string(i));
    }

    std::vector<std::vector<std::string>> transitions;
    for (const auto &row: m_transitions) {
        std::vector<std::string> transitionsLine(statesTransitions.size());
        for (int i = 0; i < statesTransitions.size(); ++i) {
            if (auto it = std::find(m_states.begin(), m_states.end(), statesTransitions[i]); it != m_states.end()) {
                auto index = it - m_states.begin();
                auto oldState = row[index];
                if (auto it2 = std::find(ids.begin(), ids.end(), oldState.to + oldState.out); it2 != ids.end()) {
                    auto index2 = it2 - ids.begin();
                    transitionsLine[i] = newStates[index2];
                }
            }
        }
        transitions.push_back(transitionsLine);
    }

    mura.FromData(
            newStates,
            m_paths,
            outs,
            transitions);
}

void CMiles::ReadStatesCSV(const std::string &line) {
    std::vector<std::string> states;
    Split(line, ';', states);
    for (const auto &state: states) {
        if (!state.empty()) {
            m_states.push_back(state);
        }
    }
}

void CMiles::ReadTransitionsCSV(const std::string &line) {
    std::vector<std::string> transitions;
    Split(line, ';', transitions);
    auto path = transitions[0];
    m_paths.push_back(path);
    std::vector<SMilesItem> transitionLine;
    for (int i = 1; i < transitions.size(); ++i) {
        auto transition = transitions[i];
        std::vector<std::string> items;
        Split(transition, '/', items);
        transitionLine.push_back(SMilesItem{items[0], items[1]});
    }
    m_transitions.push_back(transitionLine);
}
