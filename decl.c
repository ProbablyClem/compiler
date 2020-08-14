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
//   match(T_INT, "int");
//   ident();
//   addglob(Text);
//   genglobsym(Text);
//   semi();
// }

// Parse the current token and
// return a primitive type enum value
int parse_type(int t) {
  if (t == T_CHAR) return (P_CHAR);
  if (t == T_INT)  return (P_INT);
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
  
  colon();
  int type = parse_type(Token.token);
  scan(&Token);
  semi();
  int id = addglob(Text, type, S_VARIABLE);
  genglobsym(id);
}

// Parse the declaration of a simplistic function
struct ASTnode *function_declaration(void) {
  struct ASTnode *tree;
  int nameslot;

  // Find the 'void', the identifier, and the '(' ')'.
  // For now, do nothing with them
  match(T_FN, "fn");
  ident();
  nameslot= addglob(Text, P_VOID, S_FUNCTION);
  lparen();
  rparen();

  // Get the AST tree for the compound statement
  tree= compound_statement();

  // Return an A_FUNCTION node which has the function's nameslot
  // and the compound statement sub-tree
  return(mkastunary(A_FUNCTION, P_VOID, tree, nameslot));
}