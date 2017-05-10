#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "interpreter.hpp"
#include "environment.hpp"
#include "interpreter_semantic_error.hpp"

using namespace std;


int main(int argc, char* argv[]) {
   Interpreter inter;
   ifstream expression;
   if (argc <=	1) {
       while (argc) {
           string arguments_from_command_line;
           cout << "vtscript> ";
           while (!(getline(cin, arguments_from_command_line))) {}
           istringstream stream(arguments_from_command_line);
           inter.parse(stream);
           try {
               inter.eval();
           }
           catch(exception& e) {
               cout << e.what() << endl;
           }
       }
   } else {
       string argument_string(argv[1]);
       if (argv[1] && !argv[2]) {
           expression.open(argv[1]);
           if (!expression.is_open()) {
               return EXIT_FAILURE;
           }
           else {
               inter.parse(expression);
           }
//            return EXIT_SUCCESS;
//			inter.parse(expression);
       } else if (argument_string == "-e"){
           istringstream stream(argv[2]);
           inter.parse(stream);
       }
       else {
           return EXIT_FAILURE;
       }
   }
   try {
       inter.eval();
   }
   catch(exception& e) {
       cout << e.what() << endl;
       return EXIT_FAILURE;
   }
   return EXIT_SUCCESS;
}
