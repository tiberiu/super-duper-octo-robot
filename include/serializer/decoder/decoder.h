#ifndef _DECODER_H
#define _DECODER_H

#include <string>

class Decoder {
public:
    struct Node {
        Node();
        ~Node();

        bool isList;
        bool isObj;
        bool isValue;
        void* data;
    };

    static Decoder* GetDecoder(std::string dataFormat);
    virtual Node* Decode(std::string data) = 0;
};

#endif
