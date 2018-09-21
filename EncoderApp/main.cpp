#include <iostream>
#include <string>

#include "dictionary.h"
#include "encoder.h"
#include "decoder.h"

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
        std::cout<<"asd\n";
    } while(dict->getDictionaryToEncode()->isEmpty());


    return 0;
}
