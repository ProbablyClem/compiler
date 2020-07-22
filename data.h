#ifndef extern_
 #define extern_ extern
#endif

// Global variables
// Copyright (c) 2019 Warren Toomey, GPL3

extern_ int     	Line;
extern_ int		Putback;
extern_ FILE		*Infile;
extern_ FILE		*Outfile;
extern_ FILE        *Header;
extern_ struct token	Token;
extern_ char Text[TEXTLEN + 1];		
extern_ struct symtable Gsym[NSYMBOLS]; // Global symbol table               // Position of next free global symbol slot// Last identifier scanned