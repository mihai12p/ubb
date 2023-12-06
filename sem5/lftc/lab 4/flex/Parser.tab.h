
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton interface for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     INCLUDE = 258,
     LIBRARY = 259,
     MAIN = 260,
     RETURN = 261,
     CONST = 262,
     INT = 263,
     DOUBLE = 264,
     STRUCT = 265,
     TIPSPECIAL = 266,
     IF = 267,
     ELSE = 268,
     WHILE = 269,
     SWITCH = 270,
     CASE = 271,
     DEFAULT = 272,
     BREAK = 273,
     STD = 274,
     CIN = 275,
     COUT = 276,
     LBRACE = 277,
     RBRACE = 278,
     SEMICOLON = 279,
     COLON = 280,
     LPAREN = 281,
     RPAREN = 282,
     COMMA = 283,
     QUOTE = 284,
     PERCENT = 285,
     ADD = 286,
     SUB = 287,
     MUL = 288,
     DIV = 289,
     LT = 290,
     GT = 291,
     SHL = 292,
     SHR = 293,
     ASSIGN = 294,
     NEQ = 295,
     AND = 296,
     OR = 297,
     EQ = 298,
     LE = 299,
     GE = 300,
     NUMBER = 301,
     ID = 302,
     STRING_LITERAL = 303
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


