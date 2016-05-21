#include <vector>
#include <string>
#include <cstdlib>

#include "serializer/decoder/decoder.h"
#include "serializer/primitive_object_deserializers.h"

using namespace std;

int PrimitiveObjectDeserializers::DeserializeInt(Decoder::Node* objNode) {
    string strValue = *(string*) (objNode->data); 
    int val = atoi(strValue.c_str());
    return val;
}

vector<int> PrimitiveObjectDeserializers::DeserializeIntList(Decoder::Node* objNode) {
    vector<Decoder::Node*>* objData = (vector<Decoder::Node*>*) objNode->data;
    vector<int> v;
    for (int i = 0; i < objData->size(); i++) {
        v.push_back(PrimitiveObjectDeserializers::DeserializeInt((*objData)[i]));
    }

    return v;
}

string PrimitiveObjectDeserializers::DeserializeString(Decoder::Node* objNode) {
    string strValue = *(string*) (objNode->data);
    return strValue; 
}

vector<string> PrimitiveObjectDeserializers::DeserializeStringList(Decoder::Node* objNode) {
    vector<Decoder::Node*>* objData = (vector<Decoder::Node*>*) objNode->data;
    vector<string> v;
    for (int i = 0; i < objData->size(); i++) {
        v.push_back(PrimitiveObjectDeserializers::DeserializeString((*objData)[i]));
    }

    return v; 
}

float PrimitiveObjectDeserializers::DeserializeFloat(Decoder::Node* objNode) {
    string strValue = *(string*) (objNode->data);
    float val = atof(strValue.c_str());

    return val; 
}

vector<float> PrimitiveObjectDeserializers::DeserializeFloatList(Decoder::Node* objNode) {
    vector<Decoder::Node*>* objData = (vector<Decoder::Node*>*) objNode->data;
    vector<float> v;
    for (int i = 0; i < objData->size(); i++) {
        v.push_back(PrimitiveObjectDeserializers::DeserializeFloat((*objData)[i]));
    }

    return v; 
}


