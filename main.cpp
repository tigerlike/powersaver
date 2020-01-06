#include <string>
#include <iostream>
#include <cuda_runtime.h>

int testMain();

int main() {

  int dv = 0;
  if (cudaSuccess == cudaDriverGetVersion(&dv))
    std::cout << std::to_string(dv) << std::endl;

  testMain();
//  std::string command = "python /home/b/powersaver/test.py";
//  std::string output;
//  char buffer[128];
//  FILE *file_p;
////  command = command + " 2>&1"; // 2>/dev/null  This hides sterr from the pipe
//  file_p = popen(command.c_str(), "r");
//  if (file_p == nullptr)
//    return 0;
//
//  while (fgets(buffer, 128, file_p)) // TODO  handle timeout issue here
//    output += buffer;
//
//  if (feof(file_p))
//    pclose(file_p);
//
//  std::cout << output << std::endl;
//
//  return 0;

//  return true;

}