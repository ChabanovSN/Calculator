#ifndef PARSEREXCEPTION_H
#define PARSEREXCEPTION_H
#include<QtCore>
class ParserException{
     QString errStr="";
public:
     ParserException(QString str ):errStr(str){};
     QString toString(){
         return errStr;
     }
};

#endif // PARSEREXCEPTION_H
