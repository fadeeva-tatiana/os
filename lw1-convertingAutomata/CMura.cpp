#include "CMura.h"

void CMura::FromCSV(const std::string &csv) {
    std::vector<std::string> lines;

    Split(csv, '\n', lines);
    for (int i = 0; i < lines.size(); ++i) {
        auto line = lines[i];
        if (i == 0) {
            ReadOutputsCSV(line);
        } else if (i == 1) {
            ReadStatesCSV(line);
        } else {
            ReadTransitionsCSV(line);
        }
    }
}

void CMura::FromData(
        const std::vector<std::string> &states,
        const std::vector<std::string> &paths,
        const std::vector<std::string> &output,
        const std::vector<std::vector<std::string>> &transitions) {
    m_states = states;
    m_paths = paths;
    m_output = output;
    m_transitions = transitions;
}

std::string CMura::ConvertToCSV() {
    std::string csv;
    for (const auto &out: m_output) {
        csv.append(";" + out);
    }
    csv.append("\n");
    for (const auto &st: m_states) {
        csv.append(";" + st);
    }
    csv.append("\n");
    for (int i = 0; i < m_paths.size(); ++i) {
        csv.append(m_paths[i]);
        for (auto &j: m_transitions[i]) {
            csv.append(";" + j);
        }
        csv.append("\n");
    }
    return csv;
}

void CMura::ToMiles(CMiles &miles) {
    std::vector<std::vector<SMilesItem>> transitions;
    for (const auto &row: m_transitions) {
        std::vector<SMilesItem> transitionLine;
        for (const auto &item: row) {
            if (auto it = std::find(m_states.begin(), m_states.end(), item); it != m_states.end()) {
                auto index = it - m_states.begin();
                transitionLine.push_back({item, m_output[index]});
            }
        }
        transitions.push_back(transitionLine);
    }
    miles.FromData(
            m_states,
            m_paths,
            transitions);
}

void CMura::ReadOutputsCSV(const std::string &line) {
    std::vector<std::string> outputs;
    Split(line, ';', outputs);
    for (const auto &output: outputs) {
        if (!output.empty()) {
            m_output.push_back(output);
        }
    }
}

void CMura::ReadStatesCSV(const std::string &line) {
    std::vector<std::string> states;
    Split(line, ';', states);
    for (const auto &state: states) {
        if (!state.empty()) {
            m_states.push_back(state);
        }
    }
}

void CMura::ReadTransitionsCSV(const std::string &line) {
    std::vector<std::string> transitions;
    Split(line, ';', transitions);
    auto path = transitions[0];
    m_paths.push_back(path);
    std::vector<std::string> transitionLine;
    for (int i = 1; i < transitions.size(); ++i) {
        transitionLine.push_back(transitions[i]);
    }
    m_transitions.push_back(transitionLine);
}
