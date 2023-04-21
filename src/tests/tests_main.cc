#include <gtest/gtest.h>

#include "graph_algorithms_tests.cc"
#include "graph_tests.cc"
#include "queue_tests.cc"
#include "stack_tests.cc"

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
