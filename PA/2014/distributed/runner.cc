#include <cassert>
#include <cstdlib>
#include <cstring>
#include <string>
#include <unistd.h>
#include <sys/resource.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <cstdio>


using namespace std;
int main(int argc, char ** argv) {
  string input_file_path = string(argv[1]);
  string binary_path = string(argv[2]);
  assert(freopen(input_file_path.c_str(), "r", stdin) != NULL);
  char *argvv[] = {nullptr};
  return execv(binary_path.c_str(), argvv);
}
