#include "functions.hpp"

int main(int argc, char *argv[])
{
  if (argc > 1) {
    try {
      if (*argv[1] == '1') {
        doTask1();
        return 0;
      } else if (*argv[1] == '2') {
        doTask2();
        return 0;
      }
    } catch (const std::exception &ex) {
      std::cout << ex.what();
      return 1;
    }
  }
  return 1;
}
