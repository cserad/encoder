#include <iostream>
#include <string>

#include "dictionary.h"

int main()
{
    Dictionary *dict = nullptr;

    do {
        std::string path;
        std::cout<<"Give path to dictionary:";
        std::cin>>path;
        try {
            dict = new Dictionary(QString::fromStdString(path));
        } catch (QException &exception) {
            qDebug() << exception.what();
        }
    } while(dict->getDictionaryToEncode()->isEmpty());
    QString tmp;
    tmp = dict->encode("acf");
    std::cout<<tmp.toStdString()<<std::endl;
    tmp = dict->decode(tmp);
    std::cout<<tmp.toStdString()<<std::endl;
    return 0;
}
