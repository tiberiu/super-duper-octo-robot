#ifndef _TEXT_DECODER
#define _TEXT_DECODER

#include <vector>

#include "serializer/decoder/decoder.h"

class TextDecoder : public Decoder {
private:
    void* DecodeList(std::vector<std::string> tokens);
    void* DecodeObject(std::vector<std::string> tokens);
    void* DecodeValue(std::vector<std::string> tokens);
    Node* DecodeTokens(std::vector<std::string> tokens);
    std::vector<std::string> ParseNextObject(std::vector<std::string> tokens, int position);

public:
    virtual Node* Decode(std::string data);
    std::vector<std::string> Tokenize(std::string data);    
};

#endif
