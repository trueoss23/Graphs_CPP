#include <gtest/gtest.h>

#include <stack>
#include <vector>

#include "../misc/stack.h"

TEST(StackPush, StackPush1) {
  Stack my_stack;
  std::stack<int> std_stack;
  int n = 100;
  for (int i = 0; i < n; ++i) {
    my_stack.Push(i);
    std_stack.push(i);
  }
  for (int i = 0; i < n; ++i) {
    EXPECT_EQ(my_stack.Pop(), std_stack.top());
    std_stack.pop();
  }
}

TEST(StackTop, StackTop1) {
  Stack my_stack;
  std::stack<int> std_stack;
  int n = 100;
  for (int i = 0; i < n; ++i) {
    my_stack.Push(i);
    std_stack.push(i);
  }
  for (int i = 0; i < n; ++i) {
    EXPECT_EQ(my_stack.Top(), std_stack.top());
    std_stack.pop();
    my_stack.Pop();
  }
}

TEST(StackException, Exception1) {
  Stack my_stack;
  EXPECT_ANY_THROW(my_stack.Pop());
}

TEST(StackException, Exception2) {
  Stack my_stack;
  EXPECT_ANY_THROW(my_stack.Top());
}

TEST(StackTop, StackTop2) {
  Stack my_stack;
  std::stack<int> std_stack;
  int n = 100;
  for (int i = 0; i < n; ++i) {
    my_stack.Push(i);
    std_stack.push(i);
  }
  EXPECT_EQ(my_stack.Top(), std_stack.top());
}

TEST(StackTop, StackTop3) {
  Stack my_stack;
  std::stack<int> std_stack;
  int n = 100;
  for (int i = 0; i < n; ++i) {
    my_stack.Push(i);
    std_stack.push(i);
  }
  EXPECT_EQ(my_stack.Top(), std_stack.top());
}