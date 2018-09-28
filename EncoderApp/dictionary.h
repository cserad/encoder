#pragma once

#include <QString>
#include <QVariantMap>

class Dictionary
{
public:
    Dictionary();
    Dictionary(const QString &path);
    ~Dictionary();

    QString encode(const QString &input);
    QString decode(const QString &input);
    void encodeFile(const int &direction, const QString &in, const QString &out);

public:
    static bool dictCreated;

private:
    QVariantMap dictionary;
    QVariantMap reverseDictionary;
};
