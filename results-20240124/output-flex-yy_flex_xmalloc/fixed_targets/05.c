#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cstdlib>

#include "flex.h"

using namespace std;

extern "C" {
#include "scan.l"
}

int main() {
  ifstream in("input.txt");
  string line;
  while (getline(in, line)) {
    yyscan_t scanner;
    yylex_init(&scanner);
    YY_BUFFER_STATE state = yy_scan_string(line.c_str(), scanner);
    int token;
    while ((token = yylex(scanner)) != 0) {
      cout << yytext << " ";
    }
    yy_delete_buffer(state);
    yylex_destroy(scanner);
    cout << endl;
  }
  in.close();
  return 0;
}