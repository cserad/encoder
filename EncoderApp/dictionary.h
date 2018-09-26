#pragma once

#include <QString>
#include <QJsonDocument>

class Dictionary
{
public:
    Dictionary();
    Dictionary(const QString &path);
    ~Dictionary();

    QJsonDocument getDictionary() const;
    QJsonDocument getReverseDictionary() const;

    QString encode(const QString &input);
    QString decode(const QString &input);
    void encodeFile(const int &direction, const QString &in, const QString &out);

public:
    static bool dictCreated;

private:
    QJsonDocument dictionary;
    QJsonDocument reverseDictionary;
};
