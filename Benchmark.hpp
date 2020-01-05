#ifndef POWERSAVE_AI__BENCHMARK_HPP_
#define POWERSAVE_AI__BENCHMARK_HPP_
#include <string>

class Benchmark {
 public:
  static bool tensorflow(std::string args, std::string *output);
 private:
  static bool runCommmand(std::string command, std::string *output);
};

#endif //POWERSAVE_AI__BENCHMARK_HPP_
