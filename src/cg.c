#include "defs.h"
#include "data.h"
#include "decl.h"

//values of registers
#define unavailable  0
#define available  1

//generate preambule
void cgpreamble(){
  fprintf(Outfile, "@formatString = private constant [3 x i8] c\"%%d\\00\"\n");
  fprintf(Outfile, "@formatStringendl = private constant [5 x i8] c\"%%d \\0A\\00\" \n\n");
  // fprintf(Outfile, "define i32 @main() {\n");
  // fprintf(Outfile, "entry:\n");
}

//genrate postambule
void cgpostamble(){
  fprintf(Outfile, "declare i32 @printf(i8*, i32)");
}

//list all register
static int regList[10];
static int reg = 0;
// Set all registers as available
void freeall_registers(void)
{
  reg = 0;
}

void free_registers(int r){
  reg = r;
}

// Allocate a free register. Return the number of
// the register. Die if no available registers.
static int alloc_register(void)
{
  int r = reg;
  reg++;
  return r;
}


// Load an integer literal value into a register.
// Return the number of the register
int cgload(int value) {

  // Get a new register
  int r= alloc_register();
  // Print out the code to initialise it
  fprintf(Outfile, "%%%d = add i%d 0, %d\n", r, cgprimsize(type(value)), value);
  return(r);
}

// Load an boolean value into a register.
// Return the number of the register
int cgloadbool(int value) {

  // Get a new register
  int r= alloc_register();

  // Print out the code to initialise it
  fprintf(Outfile, "%%%d = add i1 0, %d\n", r, value);
  return(r);
}

// Load a value from a variable into a register.
// Return the number of the register
int cgloadglob(int id) {
  // Get a new register
  int r = alloc_register();
  int typesize = cgprimsize(Gsym[id].type);
  fprintf(Outfile, "%%%d = load i%d, i%d* @%s\n", r, typesize, typesize, Gsym[id].name);

  return (r);
}

//todo
// Store a register's value into a variable
int cgstorglob(int reg, int id) {

  int typesize = cgprimsize(Gsym[id].type);
  fprintf(Outfile, "store i%d %%%d, i%d* @%s\n",typesize, reg,typesize, Gsym[id].name);

  return (reg);
}

// Generate a global symbol
void cgglobsym(int id) {

  int typesize;
  // Get the size of the type
  typesize = cgprimsize(Gsym[id].type);

  fprintf(Header, "@%s = dso_local global i%d 0, align 4\n", Gsym[id].name, typesize);
}

// Widen the value in the register from the old
// to the new type, and return a register with
// this new value
int cgwiden(int r, int oldtype, int newtype) {
  int newreg = alloc_register();
  fprintf(Outfile, "%%%d = zext i%d %%%d to i%d\n", newreg, cgprimsize(oldtype), r, cgprimsize(newtype));
  return (newreg);
}

// Add two registers together and return
// the number of the register with the result
//the result is stored into r1
int cgadd(int r1, int r2, int type) {
  // Get a new register
  int r= alloc_register();
  fprintf(Outfile, "%%%d = add i%d %%%d, %%%d\n", r,cgprimsize(type),r1, r2);
  return(r);
}

// Subtract the second register from the first and
// return the number of the register with the result
int cgsub(int r1, int r2, int type) {
  // Get a new register
  int r= alloc_register();
  fprintf(Outfile, "%%%d = sub i%d %%%d, %%%d\n", r,cgprimsize(type) ,r1, r2);
  return(r);
}

// Multiply two registers together and return
// the number of the register with the result
int cgmul(int r1, int r2, int type) {
  // Get a new register
  int r= alloc_register();
  fprintf(Outfile, "%%%d = mul i%d %%%d, %%%d\n", r,cgprimsize(type) , r1, r2);
  return(r);
}

// Divide the first register by the second and
// return the number of the register with the result
int cgdiv(int r1, int r2, int type) {
  // Get a new register
  int r= alloc_register();
  fprintf(Outfile, "%%%d = udiv i% %%%d, %%%d\n", r,cgprimsize(type) ,r1, r2);
  return(r);
}

// Call printint() with the given register
void cgprintint(int r1) {
  int r = alloc_register();
  fprintf(Outfile, "%%%d = call i32 @printf(i8* getelementptr ([3 x i8], [3 x i8]* @formatString , i32 0, i32 0), i32 %%%d)\n",r, r1);
}

// print int with \n
void cgprintlnint(int r1) {
  int r = alloc_register();
  fprintf(Outfile, "%%%d = call i32 @printf(i8* getelementptr ([5 x i8], [5 x i8]* @formatStringendl , i32 0, i32 0), i32 %%%d)\n",r, r1);
}

//cast the bool register to i32
int cgbooltoi32(int r1){
  int r = alloc_register();
  fprintf(Outfile, "%%%d = zext i1 %%%d to i32\n", r, r1);
  return r;
}

//cast the bool register to i32
int cgi32tobool(int r1){
  int r = alloc_register();
  fprintf(Outfile, "%%%d = trunc i32 %%%d to i1\n", r, r1);
  return r;
}

// List of comparison instructions,
// in AST order: A_EQ, A_NE, A_LT, A_GT, A_LE, A_GE
static char *cmplist[] =
  { "eq", "ne", "ult", "ugt", "ule", "uge" };

// Compare two registers and set if true.
int cgcompare_and_set(int ASTop, int r1, int r2) {
  // Check the range of the AST operation
  if (ASTop < A_EQ || ASTop > A_GE)
    fatal("Bad ASTop in cgcompare_and_set()");
  int r  = alloc_register();
  fprintf(Outfile, "%%%d = icmp %s i32 %%%d, %%%d \n",r ,cmplist[ASTop - A_EQ],r1 , r2);
  r = cgbooltoi32(r);
  return (r);
}


// Compare two registers and jump if false.
int cgcompare_and_jump(int ASTop, int r1, int r2, int label) {
  // Check the range of the AST operation
  if (ASTop < A_EQ || ASTop > A_GE)
    fatal("Bad ASTop in cgcompare_and_set()");

  int r = cgcompare_and_set(ASTop, r1, r2);
  r = cgi32tobool(r);
  // alloc_register();
  // br i1 %cond, label %IfEqual, label %IfUnequal
  fprintf(Outfile, "br i1 %%%d, label %%L-%d, label %%L%d\n",r, label, label);
  cglabel(label * -1);
  return (NOREG);
}

// Generate a label
void cglabel(int l) {
  fprintf(Outfile, "L%d:\n", l);
}

// Generate a jump to a label
void cgjump(int l) {
  fprintf(Outfile, "br label %%L%d\n", l);
}

// Array of type sizes in P_XXX order.
// 0 means no size. P_NONE, P_VOID,P_BOOL, P_CHAR, P_INT, P_LONG
static int psize[] = { 0, 0, 1, 8, 32, 64 };

// Given a P_XXX type value, return the
// size of a primitive type in bytes.
int cgprimsize(int type) {
  // Check the type is valid
  if (type < P_NONE || type > P_I64)
    fatal("Bad type in cgprimsize()");
  return (psize[type]);
}

// Print out a function preamble
void cgfuncpreamble(int id) {
  if (Gsym[id].type == P_VOID){
    fprintf(Outfile, "define void @%s() nounwind {\n", Gsym[id].name);
  }
  else {
  fprintf(Outfile, "define i%d @%s() nounwind {\n", cgprimsize(Gsym[id].type), Gsym[id].name);
  }
  if (!strcmp(Gsym[id].name, "main")){
    freeall_registers();
    fprintf(Outfile, "entry:\n");
  }
}

// Print out a function postamble
void cgfuncpostamble(int id) {
  if (Gsym[id].type == P_VOID){
    fprintf(Outfile, "ret void\n");
  }
  fprintf(Outfile, "} \n\n");
}

// Call a function with one argument from the given register
// Return the register with the result
int cgcall(int r, int id) {
  int fntype = cgprimsize(Gsym[id].type);
  char* fnname = Gsym[id].name;
  // Get a new register
  int outr = alloc_register();
  fprintf(Outfile, "%%%d = call i%d () @%s()\n",outr , fntype, fnname);
  return (outr);
}

// Generate code to return a value from a function
void cgreturn(int reg, int id) {
  // Generate code depending on the function's type
  int returntype = cgprimsize(Gsym[id].type);
  fprintf(Outfile, "ret i%d %%%d\n", returntype, reg);
}