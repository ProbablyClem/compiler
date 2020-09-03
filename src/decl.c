#include "defs.h"
#include "data.h"
#include "decl.h"

// Parsing of declarations
// Copyright (c) 2019 Warren Toomey, GPL3


// // Parse the declaration of a variable
// void var_declaration(void) {

//   // Ensure we have an 'int' token followed by an identifier
//   // and a semicolon. Text now has the identifier's name.
//   // Add it as a known identifier
//   match(T_I32, "int");
//   ident();
//   addglob(Text);
//   genglobsym(Text);
//   semi();
// }

// Parse the current token and
// return a primitive type enum value
int parse_type(int t) {
  if (t == T_CHAR) return (P_CHAR);
  if (t == T_I32)  return (P_I32);
  if (t == T_I64)  return (P_I64);
  if (t == T_VOID) return (P_VOID);
  if (t == T_BOOL) return (P_BOOL);
  fatald("Illegal type, token", t);
}

// Parse the declaration of a global variable
void global_declaration(void) {
  // Ensure we have an 'global' token followed by an identifier
  // and a semicolon. Text now has the identifier's name.
  // Add it as a known identifier
  match(T_GLOBAL, "global");

  ident();
  char globname[sizeof(Text)];
  strcpy(globname, Text);

  colon();
  int type = parse_type(Token.token);
  scan(&Token);
  semi();
  int id = addglob(globname, type, S_VARIABLE);
  genglobsym(id);
}

// Parse the declaration of a simplistic function
struct ASTnode *function_declaration(void) {
  struct ASTnode *tree, *finalstmt;
  int nameslot, type;
  

  match(T_FN, "fn");

  ident();
  char funcname[sizeof(Text)];
  strcpy(funcname, Text);
  
  lparen();
  rparen();
  arrow();
  type = parse_type(Token.token);
  scan(&Token);

  // Get a label-id for the end label, add the function
  // to the symbol table, and set the Functionid global
  // to the function's symbol-id
  // endlabel = genlabel();
  nameslot = addglob(funcname, type, S_FUNCTION);
  Functionid = nameslot;

    // Get the AST tree for the compound statement
  tree = compound_statement();

  // If the function type isn't P_VOID, check that
  // the last AST operation in the compound statement
  // was a return statement
  if (type != P_VOID) {
    finalstmt = (tree->op == A_GLUE) ? tree->right : tree;
    if (finalstmt == NULL || finalstmt->op != A_RETURN)
      fatal("No return for function with non-void type");
  }
  // Return an A_FUNCTION node which has the function's nameslot
  // and the compound statement sub-tree
  return (mkastunary(A_FUNCTION, type, tree, nameslot));
}