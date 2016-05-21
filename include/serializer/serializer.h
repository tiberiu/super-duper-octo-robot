#ifndef _SERIALIZER_H
#define _SERIALIZER_H

#include <string>
#include <map>
#include <cstdlib>
#include <iostream>
#include <fstream>

#include "components/component.h"
#include "scene.h"
#include "serializer/decoder/decoder.h"

using namespace std;

// START_CODE_INCLUDES
#include "components/transformcomponent.h"
#include "components/renderercomponent.h"
#include "geometry/vector3.h"
#include "geometry/mesh.h"
// END_CODE_INCLUDES

class Serializer {
public:
    Decoder::Node* LoadData(string raw_data);
    string LoadRawData(string filePath);
    vector<Scene*> LoadGameData(string raw_data); 
    void LoadScene(string raw_data, Scene& scene);
    Component* DeserializeComponent(Decoder::Node* componentNode);


    // Primitive object deserializers
    int DeserializeInt(Decoder::Node* objNode);
    vector<int> DeserializeIntList(Decoder::Node* objNode);
    string DeserializeString(Decoder::Node* objNode);
    vector<string> DeserializeStringList(Decoder::Node* objNode);
    float DeserializeFloat(Decoder::Node* objNode);
    vector<float> DeserializeFloatList(Decoder::Node* objNode);

    // START_CODE_COMPONENT_DESERIALIZERS_DECLARATION
    TransformComponent* DeserializeTransform(Decoder::Node* componentNode);
    RendererComponent* DeserializeRenderer(Decoder::Node* componentNode);
    // END_CODE_COMPONENT_DESERIALIZERS_DECLARATION

    // START_CODE_OBJECT_DESERIALIZERS_DECLARATION
    Vector3* DeserializeVector3(Decoder::Node* objNode);
    vector<Vector3*> DeserializeVector3List(Decoder::Node* objNode);
    Mesh* DeserializeMesh(Decoder::Node* objNode);
    vector<Mesh*> DeserializeMeshList(Decoder::Node* objNode);
    // END_CODE_OBJECT_DESERIALIZERS_DECLARATION
};
#endif
