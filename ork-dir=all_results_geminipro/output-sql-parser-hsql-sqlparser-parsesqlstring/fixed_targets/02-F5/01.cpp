#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <iterator>
#include <stdexcept>
#include <cstring>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cassert>

#include "hsql_parser.h"

extern "C" {
#include "hsql_parser.h"
}

using namespace std;

static const string kUsage =
    "Usage: hsql_fuzzer [OPTIONS] <SQL_FILE>\n"
    "  -h, --help                        Display this help message.\n"
    "  -v, --verbose                     Display verbose output.\n"
    "  -n, --num_iterations <N>          Number of iterations to run.\n"
    "  -i, --input_file <FILE>           Input SQL file to fuzz.\n"
    "  -o, --output_file <FILE>          Output file to write fuzzed SQL to.\n";

static const char *kDefaultInputFile = "hsql_fuzzer_input.sql";
static const char *kDefaultOutputFile = "hsql_fuzzer_output.sql";

static void PrintUsageAndExit() {
  cerr << kUsage << endl;
  exit(1);
}

static void ParseCommandLineArguments(int argc, char **argv, string *input_file,
                                     string *output_file, int *num_iterations,
                                     bool *verbose) {
  for (int i = 1; i < argc; ++i) {
    string arg(argv[i]);
    if (arg == "-h" || arg == "--help") {
      PrintUsageAndExit();
    } else if (arg == "-v" || arg == "--verbose") {
      *verbose = true;
    } else if (arg == "-n" || arg == "--num_iterations") {
      if (++i >= argc) {
        cerr << "Error: missing argument for -n/--num_iterations." << endl;
        PrintUsageAndExit();
      }
      *num_iterations = atoi(argv[i]);
    } else if (arg == "-i" || arg == "--input_file") {
      if (++i >= argc) {
        cerr << "Error: missing argument for -i/--input_file." << endl;
        PrintUsageAndExit();
      }
      *input_file = argv[i];
    } else if (arg == "-o" || arg == "--output_file") {
      if (++i >= argc) {
        cerr << "Error: missing argument for -o/--output_file." << endl;
        PrintUsageAndExit();
      }
      *output_file = argv[i];
    } else {
      cerr << "Error: unrecognized argument: " << arg << endl;
      PrintUsageAndExit();
    }
  }
}

static string ReadFile(const string &filename) {
  ifstream file(filename);
  if (!file.is_open()) {
    cerr << "Error: could not open file: " << filename << endl;
    exit(1);
  }
  return string((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
}

static void WriteFile(const string &filename, const string &data) {
  ofstream file(filename);
  if (!file.is_open()) {
    cerr << "Error: could not open file: " << filename << endl;
    exit(1);
  }
  file << data;
}

static string FuzzSQLString(const string &sql, int num_iterations) {
  hsql::SQLParser parser;
  hsql::SQLParserResult result;
  string fuzzed_sql = sql;
  for (int i = 0; i < num_iterations; ++i) {
    // Randomly mutate the SQL string.
    int mutation_point = rand() % fuzzed_sql.size();
    int mutation_type = rand() % 3;
    switch (mutation_type) {
      case 0:
        // Insert a random character.
        fuzzed_sql.insert(mutation_point, 1, static_cast<char>(rand() % 256));
        break;
      case 1:
        // Delete a random character.
        if (mutation_point > 0) {
          fuzzed_sql.erase(mutation_point - 1, 1);
        }
        break;
      case 2:
        // Replace a random character with a different random character.
        fuzzed_sql[mutation_point] = static_cast<char>(rand() % 256);
        break;
    }

    // Parse the fuzzed SQL string.
    if (!parser.parseSQLString(&fuzzed_sql, &result)) {
      // If the fuzzed SQL string is invalid, try again.
      continue;
    }

    // If the fuzzed SQL string is valid, return it.
    return fuzzed_sql;
  }

  // If no valid fuzzed SQL string was found, return the original SQL string.
  return sql;
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  // Convert the input data to a string.
  string sql(reinterpret_cast<const char *>(data), size);

  // Fuzz the SQL string.
  string fuzzed_sql = FuzzSQLString(sql, 100);

  // Write the fuzzed SQL string to the output file.
  WriteFile(kDefaultOutputFile, fuzzed_sql);

  return 0;
}

int main(int argc, char **argv) {
  string input_file = kDefaultInputFile;
  string output_file = kDefaultOutputFile;
  int num_iterations = 100;
  bool verbose = false;

  ParseCommandLineArguments(argc, argv, &input_file, &output_file, &num_iterations,
                           &verbose);

  // Read the input SQL file.
  string sql = ReadFile(input_file);

  // Fuzz the SQL string.
  string fuzzed_sql = FuzzSQLString(sql, num_iterations);

  // Write the fuzzed SQL string to the output file.
  WriteFile(output_file, fuzzed_sql);

  return 0;
}