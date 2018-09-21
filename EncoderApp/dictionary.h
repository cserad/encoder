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
    QString encode(QString input);
    QString decode(QString input);
};

#endif // DICTIONARY_H
