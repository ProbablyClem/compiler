#include "defs.h"
#define extern_
#include "data.h"
#undef extern_
#include "decl.h"
#include <errno.h>

// Compiler setup and top-level execution
// Copyright (c) 2019 Warren Toomey, GPL3

// Initialise global variables
static void init() {
  Line = 1;
  Putback = '\n';
}

// Print out a usage if started incorrectly
static void usage(char *prog) {
  fprintf(stderr, "Usage: %s infile\n", prog);
  exit(1);
}

// Main program: check arguments and print a usage
// if we don't have an argument. Open up the input
// file and call scanfile() to scan the tokens in it.
void main(int argc, char *argv[]) {

  if (argc != 2)
    usage(argv[0]);

  init();

  // Open up the input file
  if ((Infile = fopen(argv[1], "r")) == NULL) {
    fprintf(stderr, "Unable to open %s: %s\n", argv[1], strerror(errno));
    exit(1);
  }
  // Create the output file
  if ((Outfile = fopen("out.ll", "w")) == NULL) {
    fprintf(stderr, "Unable to create out.ll: %s\n", strerror(errno));
    exit(1);
  }

  // Create the header file (temporary file containing everyhting in the header)
  if ((Header = fopen("header.ll", "w")) == NULL) {
    fprintf(stderr, "Unable to create header.ll: %s\n", strerror(errno));
    exit(1);
  }
  scan(&Token);			// Get the first token from the input
  genpreamble();		// Output the preamble
  statements();			// Parse the statements in the input
  genpostamble();		// Output the postamble
  fclose(Outfile);		// Close the output file and exit
  fclose(Header);

  // append the content of Outfile into the header

  if ((Outfile = fopen("out.ll", "r")) == NULL) {
    fprintf(stderr, "Unable to read out.ll: %s\n", strerror(errno));
    exit(1);
  }

  // Create the header file (temporary file containing everyhting in the header)
  if ((Header = fopen("header.ll", "a")) == NULL) {
    fprintf(stderr, "Unable to appen to header.ll: %s\n", strerror(errno));
    exit(1);
  }

  char c = fgetc(Outfile);

  while (c != EOF)
  {
        fputc(c,Header);
        c = fgetc(Outfile);
  }
  fclose(Outfile);		// Close the output file and exit
  fclose(Header);

  remove("out.ll"); //delete the body file
  rename("header.ll", "out.ll"); //rename the header into the final file
  exit(0);
}