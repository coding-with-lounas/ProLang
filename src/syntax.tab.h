/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_SYNTAX_TAB_H_INCLUDED
# define YY_YY_SYNTAX_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    BEGIN_PROJECT = 258,           /* BEGIN_PROJECT  */
    END_PROJECT = 259,             /* END_PROJECT  */
    SETUP = 260,                   /* SETUP  */
    RUN = 261,                     /* RUN  */
    DEFINE = 262,                  /* DEFINE  */
    CONST = 263,                   /* CONST  */
    INTEGER = 264,                 /* INTEGER  */
    FLOAT = 265,                   /* FLOAT  */
    IF = 266,                      /* IF  */
    THEN = 267,                    /* THEN  */
    ELSE = 268,                    /* ELSE  */
    ENDIF = 269,                   /* ENDIF  */
    LOOP = 270,                    /* LOOP  */
    WHILE = 271,                   /* WHILE  */
    ENDLOOP = 272,                 /* ENDLOOP  */
    FOR = 273,                     /* FOR  */
    IN = 274,                      /* IN  */
    TO = 275,                      /* TO  */
    ENDFOR = 276,                  /* ENDFOR  */
    OUT = 277,                     /* OUT  */
    AND = 278,                     /* AND  */
    OR = 279,                      /* OR  */
    NON = 280,                     /* NON  */
    AFFECT = 281,                  /* AFFECT  */
    COMP_GE = 282,                 /* COMP_GE  */
    EXPECT = 283,                  /* EXPECT  */
    COMP_LE = 284,                 /* COMP_LE  */
    COMP_EQ = 285,                 /* COMP_EQ  */
    COMP_NEQ = 286,                /* COMP_NEQ  */
    COMP_GT = 287,                 /* COMP_GT  */
    COMP_LT = 288,                 /* COMP_LT  */
    COMP_AFFECT = 289,             /* COMP_AFFECT  */
    PLUS = 290,                    /* PLUS  */
    MINUS = 291,                   /* MINUS  */
    MULT = 292,                    /* MULT  */
    DIV = 293,                     /* DIV  */
    SEMI = 294,                    /* SEMI  */
    COLON = 295,                   /* COLON  */
    COMMA = 296,                   /* COMMA  */
    PIPE = 297,                    /* PIPE  */
    LPAREN = 298,                  /* LPAREN  */
    RPAREN = 299,                  /* RPAREN  */
    LBRACE = 300,                  /* LBRACE  */
    RBRACE = 301,                  /* RBRACE  */
    LBRACKET = 302,                /* LBRACKET  */
    RBRACKET = 303,                /* RBRACKET  */
    T_ENTIER = 304,                /* T_ENTIER  */
    T_FLOAT = 305,                 /* T_FLOAT  */
    T_IDF = 306,                   /* T_IDF  */
    T_CHAINE = 307                 /* T_CHAINE  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 19 "syntax.y"

    int entier;
    float reel;
    char* str;

#line 122 "syntax.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_SYNTAX_TAB_H_INCLUDED  */
