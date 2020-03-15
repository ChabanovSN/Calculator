#include "parser.h"
#include<QDebug>
Parser::Parser()
{
 exeption = new ParserException("NULL");
}
double Parser::evaluate(QString expstr){
    double result;
    exp = expstr;
    expIdx = 0;

    getToken();
    if(token==EOE)
        handleErr(NOEXP); // Пустая строка

    // точка в хода
   result = evalExp2();

    if(token !=EOE) // Конец строки
        handleErr(SYNTAX);

    return result;
}

double Parser::evalExp2(){
    QChar op;
    double result;
    double partialResult;

    result = evalExp3();

    while(token  == "+" || token == "-") {
        op = token.at(0);

        getToken();
        partialResult = evalExp3();

        switch(op.toAscii()) {
        case '-':
            result = result - partialResult;
            break;
        case '+':
            result = result + partialResult;
            break;
        }
    }
    return result;


}

double Parser::evalExp3(){
    char op;
    double result;
    double partialResult;

    result = evalExp4();

    while( token == "*" || token == "/" || token == "%"){
        op = token.at(0).toAscii();
        getToken();
        partialResult = evalExp4();
        switch(op) {
        case '*':
            result = result * partialResult;
            break;
        case '/':
            if(partialResult == 0.0)
                handleErr(DIVBYZERO);
            result = result / partialResult;
            break;
        case '%':
            if(partialResult == 0.0)
                handleErr(DIVBYZERO);
            result = (int)result % (int)partialResult;
            break;
        }
    }
  //  qDebug()<<"evalExp3 " <<token<< " result "<<result;
    return result;
}

double Parser::evalExp4(){
    double result;
    double partialResult;
    double ex;
    int t;

    result = evalExp5();

    if(token=="^") {
        getToken();
        partialResult = evalExp4();
        ex = result;
        if(partialResult == 0.0) {
            result = 1.0;
        } else
            for(t=(int)partialResult-1; t > 0; t--)
                result = result * ex;
    }
  //  qDebug()<<"evalExp4 " <<token<< " result "<<result;
    return result;
}

double Parser::evalExp5(){
    double result;
       QString  op;

       op = "";
       if((tokType == DELIMITER) &&  (token=="+" || token== "-")) {
         op = token;
         getToken();

       }
       result = evalExp6();

       if(op== "-") result = -result;
//qDebug()<<"evalExp5 " <<token<< " result "<<result;
       return result;
}
double Parser::evalExp6(){
    double result;

       if(token=="(") {
         getToken();
         result = evalExp2();
         if(token !=")")
           handleErr(UNBALPARENS);
         getToken();
       }
       else result = atom();
//qDebug()<<"evalExp6 " <<token<< " result "<<result;
       return result;


}

double Parser::atom(){
    double result =0.0;

       switch(tokType) {
       case VARIABLE:
         handleErr(SYNTAX);
         break;
         case NUMBER:

           try {
          // qDebug()<< ":atom() "<<token.toDouble();
            result = token.toDouble();
           } catch (...) {
           handleErr(SYNTAX);
           }
           getToken();
           break;
         default:
          handleErr(SYNTAX);
           break;
       }

       return result;
}
void Parser::handleErr(int error){
    QString err[]= {
        QString::fromUtf8( "Синтаксическая ошибка"),
          QString::fromUtf8("Пропущена скобка"),
          QString::fromUtf8("Отсутствует выражение"),
          QString::fromUtf8("На ноль делить нельзя!")
       };
qDebug()<<err[error];
     exeption = new ParserException(err[error]);
}
void Parser::getToken(){
        tokType = NONE;
        token = "";

        // Check for end of expression.
        if(expIdx == exp.size()) {
          token = EOE;
          return;
        }

        // Skip over white space.
        while(expIdx < exp.size() && isspace(exp.at(expIdx).toAscii())){
         //   qDebug()<<"Skip over white space";
             ++expIdx;
        }
 //qDebug()<<"expIdx == exp.size" <<expIdx <<" =" <<exp.size();

        // Trailing whitespace ends expression.
        if(expIdx == exp.size()) {
        //    qDebug()<<"End String";
          token = EOE;
          return;
        }

        if(isDelim(exp.at(expIdx).toAscii())) { // is operator

          token += exp.at(expIdx);
         //   qDebug()<<"isDelim(exp.at(expIdx).toAscii()) " <<token;
          expIdx++;
          tokType = DELIMITER;
        }
        else if(isalpha(exp.at(expIdx).toAscii())) { // is variable
//          while(!isDelim(exp.at(expIdx).toAscii())) {
//            token += exp.at(expIdx);

//            expIdx++;
//            if(expIdx >= exp.size()) break;
//          }
           qDebug()<<"isalpha(exp.at(expIdx).toAscii()) ";
          tokType = VARIABLE;
        }
        else if(isdigit(exp.at(expIdx).toAscii())) { // is number
          while(!isDelim(exp.at(expIdx).toAscii())) {
            token += exp.at(expIdx);
         //    qDebug()<<"isdigit(exp.at(expIdx).toAscii()) " <<token;
            expIdx++;
            if(expIdx >= exp.size()) break;
          }
          tokType = NUMBER;
        }
        else { // unknown character terminates expression
          token = EOE;
          return;
        }
}
bool Parser::isDelim(char c){
    QString str = " +-/*%^=()";
    if((str.indexOf(c) != -1))
          return true;
        return false;
}
