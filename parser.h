#ifndef PARSER_H
#define PARSER_H
#include<QtCore>
#include"ParserException.h"
class Parser
{
    // These are the token types.
   static const int NONE = 0;
    const int  DELIMITER = 1;
   static const int VARIABLE = 2;
    static  const int  NUMBER = 3;

    // These are the types of syntax errors.
    const int SYNTAX = 0;
    const int UNBALPARENS = 1;
    const int NOEXP = 2;
    const int DIVBYZERO = 3;

    // This token indicates end-of-expression.
    QString EOE = "\0";

    QString exp;   // refers to expression string
    int expIdx;   // current index into the expression
    QString token; // holds current token
    int tokType;  // holds token's type

    // Array for variables.
    double vars[26];
public:
    Parser();
    ParserException * exeption;
    double evaluate(QString expstr);
private:
    void getToken();

    double evalExp2();
    double evalExp3();
    double evalExp4();
    double evalExp5();
    double evalExp6();
    double atom();
    void handleErr(int error);
    bool isDelim(char c);

};

#endif // PARSER_H
