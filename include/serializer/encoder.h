#ifndef _ENCODER_H
#define _ENCODER_H

#include <string>

class EncoderNode {
public:
    bool isList;
    bool isObj;
    bool isValue;
    std::string type;
    void* obj_data;

    void Decode(std::string raw_data);
    void DecodeList(std::string raw_data);
    void DecodeObj(std::string raw_data);
    void DecodeValue(std::string raw_data);
    std::string ParseToken(std::string raw_data, int pos);
    static std::string RemoveIndentSpaces(std::string raw_obj_data);
    std::string Encode(int indent=0);
};

#endif
