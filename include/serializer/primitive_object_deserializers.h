#ifndef _PRIMITIVE_OBJECT_DESERIALIZERS
#define _PRIMITIVE_OBJECT_DESERIALIZERS

#include <vector>
#include <string>

using namespace std;

class PrimitiveObjectDeserializers {
public:
    static int DeserializeInt(Decoder::Node* objNode);
    static vector<int> DeserializeIntList(Decoder::Node* objNode);
    static string DeserializeString(Decoder::Node* objNode);
    static vector<string> DeserializeStringList(Decoder::Node* objNode);
    static float DeserializeFloat(Decoder::Node* objNode);
    static vector<float> DeserializeFloatList(Decoder::Node* objNode);
};

#endif
