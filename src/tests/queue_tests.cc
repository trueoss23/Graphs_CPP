#include <gtest/gtest.h>

#include <queue>

#include "../misc/queue.h"

void fill_queue(std::queue<int>& std_queue, Queue& my_queue, const int& n) {
  for (int i = 0; i < n; ++i) {
    std_queue.push(i);
    my_queue.Push(i);
  }
}

TEST(Queue, PushQueue1) {
  Queue my_queue;
  std::queue<int> std_queue;
  int n = 100;
  fill_queue(std_queue, my_queue, n);
  for (int i = 0; i < n; ++i) {
    EXPECT_EQ(my_queue.Pop(), std_queue.front());
    std_queue.pop();
  }
}

TEST(Queue, QueueBack1) {
  Queue my_queue;
  std::queue<int> std_queue;
  int n = 100;
  fill_queue(std_queue, my_queue, n);
  EXPECT_EQ(my_queue.Back(), std_queue.back());
}

TEST(Queue, QueueBack2) {
  Queue my_queue;
  std::queue<int> std_queue;
  int n = 100;
  fill_queue(std_queue, my_queue, n);
  EXPECT_EQ(my_queue.Back(), std_queue.back());
}

TEST(Queue, QueueFront1) {
  Queue my_queue;
  std::queue<int> std_queue;
  int n = 100;
  fill_queue(std_queue, my_queue, n);
  for (int i = 0; i < n; ++i) {
    EXPECT_EQ(my_queue.Front(), std_queue.front());
    my_queue.Pop();
    std_queue.pop();
  }
}

TEST(Queue, QueueFront2) {
  Queue my_queue;
  std::queue<int> std_queue;
  int n = 100;
  fill_queue(std_queue, my_queue, n);
  EXPECT_EQ(my_queue.Front(), std_queue.front());
}

TEST(Queue, Exception1) {
  Queue my_queue;
  EXPECT_ANY_THROW(my_queue.Pop());
}

TEST(Queue, Exception2) {
  Queue my_queue;
  EXPECT_ANY_THROW(my_queue.Back());
}

TEST(Queue, Exception3) {
  Queue my_queue;
  EXPECT_ANY_THROW(my_queue.Front());
}

TEST(Queue, Exception4) {
  Queue my_queue;
  my_queue.Push(3);
  my_queue.Pop();
  EXPECT_ANY_THROW(my_queue.Front());
}