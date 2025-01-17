#include <fuzzer/FuzzedDataProvider.h>

#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include "cil/cil_db.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);
  struct cil_db* db = cil_db_new();
  if (db == nullptr) {
    return 0;
  }

  // Generate a random number of classes.
  int num_classes = provider.ConsumeIntegralInRange<int>(0, 100);
  for (int i = 0; i < num_classes; i++) {
    // Generate a random class name.
    size_t class_name_length = provider.ConsumeIntegralInRange<size_t>(0, 100);
    char* class_name = new char[class_name_length + 1];
    provider.ConsumeBytes(class_name, class_name_length);
    class_name[class_name_length] = '\0';

    // Generate a random number of fields.
    int num_fields = provider.ConsumeIntegralInRange<int>(0, 100);
    for (int j = 0; j < num_fields; j++) {
      // Generate a random field name.
      size_t field_name_length = provider.ConsumeIntegralInRange<size_t>(0, 100);
      char* field_name = new char[field_name_length + 1];
      provider.ConsumeBytes(field_name, field_name_length);
      field_name[field_name_length] = '\0';

      // Generate a random field type.
      size_t field_type_length = provider.ConsumeIntegralInRange<size_t>(0, 100);
      char* field_type = new char[field_type_length + 1];
      provider.ConsumeBytes(field_type, field_type_length);
      field_type[field_type_length] = '\0';

      // Add the field to the class.
      cil_db_add_field(db, class_name, field_name, field_type);

      // Free the memory allocated for the field name and type.
      delete[] field_name;
      delete[] field_type;
    }

    // Free the memory allocated for the class name.
    delete[] class_name;
  }

  // Generate a random number of functions.
  int num_functions = provider.ConsumeIntegralInRange<int>(0, 100);
  for (int i = 0; i < num_functions; i++) {
    // Generate a random function name.
    size_t function_name_length = provider.ConsumeIntegralInRange<size_t>(0, 100);
    char* function_name = new char[function_name_length + 1];
    provider.ConsumeBytes(function_name, function_name_length);
    function_name[function_name_length] = '\0';

    // Generate a random number of parameters.
    int num_parameters = provider.ConsumeIntegralInRange<int>(0, 100);
    for (int j = 0; j < num_parameters; j++) {
      // Generate a random parameter name.
      size_t parameter_name_length = provider.ConsumeIntegralInRange<size_t>(0, 100);
      char* parameter_name = new char[parameter_name_length + 1];
      provider.ConsumeBytes(parameter_name, parameter_name_length);
      parameter_name[parameter_name_length] = '\0';

      // Generate a random parameter type.
      size_t parameter_type_length = provider.ConsumeIntegralInRange<size_t>(0, 100);
      char* parameter_type = new char[parameter_type_length + 1];
      provider.ConsumeBytes(parameter_type, parameter_type_length);
      parameter_type[parameter_type_length] = '\0';

      // Add the parameter to the function.
      cil_db_add_parameter(db, function_name, parameter_name, parameter_type);

      // Free the memory allocated for the parameter name and type.
      delete[] parameter_name;
      delete[] parameter_type;
    }

    // Generate a random number of local variables.
    int num_local_variables = provider.ConsumeIntegralInRange<int>(0, 100);
    for (int j = 0; j < num_local_variables; j++) {
      // Generate a random local variable name.
      size_t local_variable_name_length = provider.ConsumeIntegralInRange<size_t>(0, 100);
      char* local_variable_name = new char[local_variable_name_length + 1];
      provider.ConsumeBytes(local_variable_name, local_variable_name_length);
      local_variable_name[local_variable_name_length] = '\0';

      // Generate a random local variable type.
      size_t local_variable_type_length = provider.ConsumeIntegralInRange<size_t>(0, 100);
      char* local_variable_type = new char[local_variable_type_length + 1];
      provider.ConsumeBytes(local_variable_type, local_variable_type_length);
      local_variable_type[local_variable_type_length] = '\0';

      // Add the local variable to the function.
      cil_db_add_local_variable(db, function_name, local_variable_name, local_variable_type);

      // Free the memory allocated for the local variable name and type.
      delete[] local_variable_name;
      delete[] local_variable_type;
    }

    // Free the memory allocated for the function name.
    delete[] function_name;
  }

  // Generate a random number of statements.
  int num_statements = provider.ConsumeIntegralInRange<int>(0, 100);
  for (int i = 0; i < num_statements; i++) {
    // Generate a random statement type.
    int statement_type = provider.ConsumeIntegralInRange<int>(0, 100);

    // Generate a random statement.
    switch (statement_type) {
      case 0: {
        // Assignment statement.
        // Generate a random variable name.
        size_t variable_name_length = provider.ConsumeIntegralInRange<size_t>(0, 100);
        char* variable_name = new char[variable_name_length + 1];
        provider.ConsumeBytes(variable_name, variable_name_length);
        variable_name[variable_name_length] = '\0';

        // Generate a random expression.
        size_t expression_length = provider.ConsumeIntegralInRange<size_t>(0, 100);
        char* expression = new char[expression_length + 1];
        provider.ConsumeBytes(expression, expression_length);
        expression[expression_length] = '\0';

        // Add the assignment statement to the database.
        cil_db_add_assignment(db, variable_name, expression);

        // Free the memory allocated for the variable name and expression.
        delete[] variable_name;
        delete[] expression;
        break;
      }
      case 1: {
        // If statement.
        // Generate a random condition.
        size_t condition_length = provider.ConsumeIntegralInRange<size_t>(0, 100);
        char* condition = new char[condition_length + 1];
        provider.ConsumeBytes(condition, condition_length);
        condition[condition_length] = '\0';

        // Generate a random number of statements in the if block.
        int num_if_statements = provider.ConsumeIntegralInRange<int>(0, 100);
        for (int j = 0; j < num_if_statements; j++) {
          // Generate a random statement.
          cil_db_add_if_statement(db, condition);
          cil_db_add_statement(db);
        }

        // Generate a random number of statements in the else block.
        int num_else_statements = provider.ConsumeIntegralInRange<int>(0, 100);
        for (int j = 0; j < num_else_statements; j++) {
          // Generate a random statement.
          cil_db_add_else_statement(db);
          cil_db_add_statement(db);
        }

        // Free the memory allocated for the condition.
        delete[] condition;
        break;
      }
      case 2: {