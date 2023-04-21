#ifndef SRC_MISC_STACK_H_
#define SRC_MISC_STACK_H_

#include <memory>
#include <stdexcept>

class Stack {
 public:
  Stack() : head_(nullptr) {}

  void Push(const int &value) {
    auto new_element = std::make_shared<Stack::StackNode>();
    new_element->next_ = head_;
    new_element->value_ = value;
    head_ = new_element;
  }

  int Pop() {
    if (IsEmpty()) throw std::logic_error("The stack is empty!");
    int value = head_->value_;
    head_ = head_->next_;
    return value;
  }

  const int &Top() {
    if (IsEmpty()) throw std::logic_error("The stack is empty!");
    return head_->value_;
  }

  bool IsEmpty() { return !head_; }

 private:
  class StackNode {
   public:
    friend class Stack;

    StackNode() : value_(), next_(nullptr) {}

   private:
    int value_;
    std::shared_ptr<StackNode> next_;
  };

  std::shared_ptr<StackNode> head_;
};

#endif  // SRC_MISC_STACK_H_
