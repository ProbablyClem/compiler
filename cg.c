#include "defs.h"
#include "data.h"
#include "decl.h"

//values of registers
#define unavailable  0
#define available  1

//generate preambule
void cgpreamble(){
  fprintf(Outfile, "@formatString = private constant [2 x i8] c\"%%d\" \n\n");
  fprintf(Outfile, "define i32 @main() {\n");
  fprintf(Outfile, "entry:\n");
}

//genrate postambule
void cgpostamble(){
  fprintf(Outfile, "\tret i32 1\n");
  fprintf(Outfile, "}\n\n");
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
  fprintf(Outfile, "%%%d = add i32 0, %d\n", r, value);
  return(r);
}

// Add two registers together and return
// the number of the register with the result
//the result is stored into r1
int cgadd(int r1, int r2) {
  // Get a new register
  int r= alloc_register();

  fprintf(Outfile, "%%%d = add i32 %%%d, %%%d\n", r,r1, r2);
  return(r);
}

// Subtract the second register from the first and
// return the number of the register with the result
int cgsub(int r1, int r2) {
  // Get a new register
  int r= alloc_register();
  fprintf(Outfile, "%%%d = sub i32 %%%d, %%%d\n", r,r1, r2);
  return(r);
}

// Multiply two registers together and return
// the number of the register with the result
int cgmul(int r1, int r2) {
  // Get a new register
  int r= alloc_register();
  fprintf(Outfile, "%%%d = mul i32 %%%d, %%%d\n", r, r1, r2);
  return(r);
}

// Divide the first register by the second and
// return the number of the register with the result
int cgdiv(int r1, int r2) {
  // Get a new register
  int r= alloc_register();
  fprintf(Outfile, "%%%d = udiv i32 %%%d, %%%d\n", r,r1, r2);
  return(r);
}

// Call printint() with the given register
void cgprintint(int r) {
  fprintf(Outfile, "call i32 @printf(i8* getelementptr ([2 x i8], [2 x i8]* @formatString , i32 0, i32 0), i32 %%%d)\n", r);
}
