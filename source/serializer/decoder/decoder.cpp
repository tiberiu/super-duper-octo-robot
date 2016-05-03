#include "serializer/decoder/decoder.h"
#include "serializer/decoder/textdecoder.h"

Decoder* Decoder::GetDecoder(std::string dataFormat) {
    return new TextDecoder();
}

Decoder::Node::Node() {
    this->isList = false;
    this->isObj = false;
    this->isValue = false;
    this->data = NULL;
}

Decoder::Node::~Node() {
    // TODO: clean up
}
