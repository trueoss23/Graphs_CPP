#ifndef SRC_MISC_QUEUE_H_
#define SRC_MISC_QUEUE_H_

#include <memory>
#include <stdexcept>

class Queue {
 public:
  Queue() : head_(nullptr), tail_(nullptr) {}

  bool IsEmpty() const { return !head_; }

  void Push(const int &value) {
    auto new_element = std::make_unique<QueueNode>(value);
    if (IsEmpty()) {
      head_ = std::move(new_element);
      tail_ = head_.get();
    } else {
      tail_->next_ = std::move(new_element);
      tail_ = tail_->next_.get();
    }
  }

  int Pop() {
    if (IsEmpty()) {
      throw std::logic_error("The queue if empty!");
    }
    int value = std::move(head_->value_);
    head_ = std::move(head_->next_);
    if (IsEmpty()) {
      tail_ = nullptr;
    }
    return value;
  }

  const int &Front() {
    if (!head_) throw std::logic_error("The queue if empty!");
    return head_->value_;
  }

  const int &Back() {
    if (!tail_) throw std::logic_error("The queue if empty!");
    return tail_->value_;
  }

 private:
  class QueueNode {
   public:
    friend class Queue;

    explicit QueueNode(int value) : value_(value), next_(nullptr) {}

   private:
    int value_;
    std::unique_ptr<Queue::QueueNode> next_;
  };

  std::unique_ptr<Queue::QueueNode> head_;
  QueueNode *tail_;
};

#endif  // SRC_MISC_QUEUE_H_
