#include "test.h"
#include <SDL.h>
#include <iostream>
#include <string>

int main(int argc, char const *argv[]) {
   int sum = add(1, 3);

   std::string msg = "Sum: ";

   std::cout << msg << std::to_string(sum) << std::endl;
   return 0;
}
