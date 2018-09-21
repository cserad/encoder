#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <QtCore>

class Dictionary
{
private:
    QJsonDocument *dictionaryToEncode;
    QJsonDocument *dictionaryToDecode;
public:
    Dictionary(QString path);
    ~Dictionary();
    QJsonDocument *getDictionaryToEncode() const;
    QJsonDocument *getDictionaryToDecode() const;

};

#endif // DICTIONARY_H
