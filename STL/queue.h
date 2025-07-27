#pragma once
#include <stdexcept>
#include <memory>

template <class Type>

class queue
{
public:

    queue() = default;

    void push(const Type& value)
    {
        auto newNode = std::make_shared<Node>(value);
        if (!tail) {
            head = tail = newNode;
        }
        else {
            tail->next = newNode;
            tail = newNode;
        }
        queue_size++;
    }

    void pop()
    {
        if (!head) {
            throw std::runtime_error("Queue is empty!");
        }
        head = head->next;
        queue_size--;
        if (!head) {
            tail = nullptr;
        }
    }

    Type& front()
    {
        if (!head) {
            throw std::runtime_error("Queue is empty!");
        }
        return head->data;
    }

    Type& back()
    {
        if (!tail) {
            throw std::runtime_error("Queue is empty!");
        }
        return tail->data;
    }

    bool empty()
    {
        return !head;
    }

    size_t size()
    {
        return queue_size;
    }

    void swap(queue& other) noexcept
    {
        std::swap(*this, other);
    }

private:

    struct Node {
        Type data;
        std::shared_ptr<Node> next;

        Node(const Type& val) : data(val), next(nullptr) {};
    };

    size_t queue_size = 0;

    std::shared_ptr<Node> head = nullptr;
    std::shared_ptr<Node> tail = nullptr;
};
