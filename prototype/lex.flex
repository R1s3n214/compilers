%option noyywrap

%{
  enum {
  LT, LE, EQ, NE, GT, GE,
  IF, THEN, ELSE, ID, NUMBER, RELOP, WHILE,
  };
%}

delim	[ \t\n]
ws	{delim}+
letter	[A-Za-z]
digit	[0-9]
id	({letter}|_)({letter}|{digit}|_)*
number	{digit}+(\.{digit}+)?(E[+-]?{digit}+)?

%%

{ws}	{ /* no action */ }
if	{ return IF; }
then	{ return THEN; }
else	{ return ELSE; }
while	{ return WHILE; }
{id}	{ yylval = (int) installID(); return ID; }
{number}	{ yylval = (int) installNum(); return NUMBER; }
"<"	{ yylval = LT; return RELOP; }
"<="	{ yylval = LE; return RELOP; }
"="	{ yylval = EQ; return RELOP; }
"<>"	{ yylval = NE; return RELOP; }
">"	{ yylval = GT; return RELOP; }
">="	{ yylval = GE; return RELOP; }

%%

int installID() {

}

int installNum() {

}

