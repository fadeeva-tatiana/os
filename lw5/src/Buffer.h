#pragma once
#include <queue>
#include <string>
#include <utility>

struct Buffer {
    explicit Buffer(std::queue<std::string> queue) {
        m_queue = std::move(queue);
    }

    std::string GetItem() {
        if (m_queue.empty()) {
            throw std::invalid_argument("\nERROR: Unexpected ending of the file");
        }
        auto item = m_queue.front();
        transform(item.begin(), item.end(), item.begin(), ::toupper);
        return item;
    }

    std::string GetOriginalItem() {
        if (m_queue.empty()) {
            return "";
        }
        return m_queue.front();
    }

    void PopItem() {
        m_queue.pop();
    }

private:
    std::queue<std::string> m_queue;
};

void CompareItem(const std::string &item, Buffer &buffer) {
    if (buffer.GetItem() != item) {
        throw std::invalid_argument("\nERROR: \"" + item + "\" is expected, but \"" + buffer.GetOriginalItem() + "\" is received");
    }
    buffer.PopItem();
}

bool CheckItem(const std::string &item, Buffer &buffer) {
    auto currentItem = buffer.GetItem();
    if (currentItem == item) {
        buffer.PopItem();
        return true;
    }
    return false;
}
