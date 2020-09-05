#include "defs.h"
#include "data.h"
#include "decl.h"

// Generic code generator

// Generate and return a new label number
int label(void) {
  static int id = 1;
  return (id++);
}

// Generate the code for an IF statement
// and an optional ELSE clause
static int genIFAST(struct ASTnode *n) {
  int Lfalse, Lend;

  // Generate two labels: one for the
  // false compound statement, and one
  // for the end of the overall IF statement.
  // When there is no ELSE clause, Lfalse _is_
  // the ending label!
  Lfalse = label();
  if (n->right)
    Lend = label();

  // Generate the condition code followed
  // by a zero jump to the false label.
  // We cheat by sending the Lfalse label as a register.
  genAST(n->left, Lfalse, n->op);

  // Generate the true compound statement
  genAST(n->mid, NOREG, n->op);

  // If there is an optional ELSE clause,
  // generate the jump to skip to the end
  if (n->right)
    cgjump(Lend);

  // Now the false label
  cglabel(Lfalse);

  // Optional ELSE clause: generate the
  // false compound statement and the
  // end label
  if (n->right) {
    genAST(n->right, NOREG, n->op);
    cgjump(Lend);
    cglabel(Lend);
  }

  return (NOREG);
}

static int genWHILEAST(struct ASTnode *n) {
  int Lend, LCMP;

  // Generate two labels: one for the
  // false compound statement, and one
  // for the end of the overall IF statement.
  // When there is no ELSE clause, Lfalse _is_
  // the ending label!
  LCMP = label();
  Lend = label();
  cgjump(LCMP);
  cglabel(LCMP);
  // Generate the condition code followed
  // by a zero jump to the false label.
  // We cheat by sending the Lfalse label as a register.
  genAST(n->left, Lend, n->op);

  // Generate the true compound statement
  genAST(n->mid, NOREG, n->op);


  
  cgjump(LCMP);
  cglabel(Lend);

  return (NOREG);
}

// Given an AST, the register (if any) that holds
// the previous rvalue, and the AST op of the parent,
// generate assembly code recursively.
// Return the register id with the tree's final value
int genAST(struct ASTnode *n, int reg, int parentASTop) {
  int leftreg, rightreg;

  // We now have specific AST node handling at the top
  switch (n->op) {
    case A_IF:
      return (genIFAST(n));
    case A_WHILE:
      return (genWHILEAST(n));
    case A_GLUE:
      // Do each child statement, and free the
      // registers after each child
      genAST(n->left, NOREG, n->op);
      // genfreeregs();
      genAST(n->right, NOREG, n->op);
      genfreeregs();
      return (NOREG);
    case A_FUNCTION:
      // Generate the function's preamble before the code
      free_registers(1);
      cgfuncpreamble(n->v.id);
      genAST(n->left, NOREG, n->op);
      cgfuncpostamble(n->v.id);
      return (NOREG);
  }

  // General AST node handling below

  // Get the left and right sub-tree values
  if (n->left)
    leftreg = genAST(n->left, NOREG, n->op);
  if (n->right)
    rightreg = genAST(n->right, leftreg, n->op);

  switch (n->op) {
    case A_ADD:
      return (cgadd(leftreg, rightreg, n->type));
    case A_SUBTRACT:
      return (cgsub(leftreg, rightreg, n->type));
    case A_MULTIPLY:
      return (cgmul(leftreg, rightreg, n->type));
    case A_DIVIDE:
      return (cgdiv(leftreg, rightreg, n->type));
    case A_EQ:
    case A_NE:
    case A_LT:
    case A_GT:
    case A_LE:
    case A_GE:
      // If the parent AST node is an A_IF or A_WHILE, generate
      // a compare followed by a jump. Otherwise, compare registers
      // and set one to 1 or 0 based on the comparison.
      if (parentASTop == A_IF || parentASTop == A_WHILE)
	return (cgcompare_and_jump(n->op, leftreg, rightreg, reg));
      else
	return (cgcompare_and_set(n->op, leftreg, rightreg));
    case A_INTLIT:
      return (cgload(n->v.intvalue));
    case A_BOOL:
      return (cgload(n->v.intvalue));
    case A_IDENT:
      return (cgloadglob(n->v.id));
    case A_LVIDENT:
      return (cgstorglob(reg, n->v.id));
    case A_ASSIGN:
      // The work has already been done, return the result
      return (rightreg);
    case A_PRINT:
      // Print the left-child's value
      // and return no register
      // printf("%d",n->type);
      if (n->type == P_BOOL){
        leftreg = cgbooltoi32(leftreg);
      }
      genprintint(leftreg);
      return (NOREG);
    case A_WIDEN:
    // Widen the child's type to the parent's type
      return (cgwiden(leftreg, n->left->type, n->type));
    case A_RETURN:
      cgreturn(leftreg, Functionid);
      return (NOREG);
    case A_FUNCCALL:
      return (cgcall(leftreg, n->v.id));
    default:
      fatald("Unknown AST operator", n->op);
  }
}

void genpreamble() { 
  cgpreamble();
}
void genpostamble() {
  cgpostamble();
}
void genfreeregs() {
  // freeall_registers();
}
void genprintint(int reg) {
  cgprintint(reg);
}

void genglobsym(int id) {
  cgglobsym(id);
}

int genprimsize(int type) {
  return (cgprimsize(type));
}