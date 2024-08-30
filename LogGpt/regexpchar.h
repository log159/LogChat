#ifndef REGEXPCHAR_H
#define REGEXPCHAR_H
#include <QRegExp>

class RegExpChar{
public:
    /*中文字符*/
    static QString CHINESE_CHAR;
    /*英文字符*/
    static QString ENGLISH_CHAR;
    /*英文字母*/
    static QString ENGLISH_LETTER;
    /*阿拉伯数字*/
    static QString NUMBER;
    /*转义字符*/
    static QString SPECIAL_CHAR;
};

#endif // REGEXPCHAR_H
