#include "source/serializer/serializer.h"
#include "source/gameobject.h"

EncoderNode* Serializer::LoadData(string raw_data) {
    raw_data = EncoderNode::RemoveIndentSpaces(raw_data);
    EncoderNode* node = new EncoderNode();
    node->Decode(raw_data);
    return node;
}

string Serializer::LoadRawData(string filePath) {
    ifstream f(filePath);
    string data;
    while (!f.eof()) {
        string temp;
        getline(f, temp);
        data = data + temp;
    }

    return data;
}

vector<Scene*> Serializer::LoadGameData(string raw_data) {
    EncoderNode* data = LoadData(raw_data);

    // TODO: assert data.isList
    vector<void*> *scenesData = (vector<void*>*) data->obj_data;
    vector<Scene*> scenes;
    for (int i = 0; i < scenesData->size(); i++) {
        EncoderNode* sceneNode = (EncoderNode*) (*scenesData)[i];
        map<string, void*> *sceneData = (map<string, void*>*) sceneNode->obj_data;
        string sceneName = DeserializeString((EncoderNode*) (*sceneData)["name"]);
        string sceneDataPath = DeserializeString((EncoderNode*) (*sceneData)["dataPath"]);
        Scene* scene = new Scene(sceneName, sceneDataPath);
        scenes.push_back(scene);
    }

    return scenes;
}

void Serializer::LoadScene(string raw_data, Scene& scene) {
    EncoderNode* data = LoadData(raw_data);

    cout << "DECODED DATA" << endl;
    // TODO: Assert data.isList
    vector<void*> *gameObjectsData = (vector<void*>*) data->obj_data;
    for (int i = 0; i < gameObjectsData->size(); i++) {
        cout << "ITERATING GAMEOBJECTS" << endl;
        // TODO: Assert gameObjectsData[i].isObj
        // TODO: Assert gameObjectsData[i]->__obj_type = GameObject
        EncoderNode* gameObjectNode = (EncoderNode*) (*gameObjectsData)[i];
        map<string, void*>* gameObjectData = (map<string, void*>*) gameObjectNode->obj_data; 
        string name = DeserializeString((EncoderNode*) (*gameObjectData)["name"]);
        GameObject* gameObject = new GameObject(name);

        // Deserialize Components
        if (!(*gameObjectData)["components"]) {
            // No components
            break;
        }

        EncoderNode* componentsNode = (EncoderNode*) (*gameObjectData)["components"];
        vector<void*> *componentsData = (vector<void*>*) componentsNode->obj_data;
        for (int j = 0; j < componentsData->size(); j++) {
            EncoderNode* componentNode = (EncoderNode*) (*componentsData)[j];
            Component* component = DeserializeComponent(componentNode);

            if (component) {
                gameObject->AddComponent(component);
            }
        }

        scene.AddGameObject(gameObject);
    }
}

Component* Serializer::DeserializeComponent(EncoderNode* componentNode) {
    // cout << "DESERIALIZE COMPONENT" << componentNode->Encode() << endl;
    // TODO: Assert componentNode.isObj
    map<string, EncoderNode*> *componentData = (map<string, EncoderNode*> *) componentNode->obj_data;
    string obj_type = *(string*) ((*componentData)["__obj_type"]->obj_data);

    cout << "DESERIALIZE TYPE " << obj_type << endl;

    // START_CODE_COMPONENT_NAME_INTROSPECTION
    Component* comp;
    if (obj_type == "TransformComponent") {
        comp = DeserializeTransform(componentNode);
        cout << "DESERIALIZED TRANSFORM" << endl;
    } else if (obj_type == "RendererComponent") {
        comp = DeserializeRenderer(componentNode);
        cout << "DESERIALIZED RENDERER" << endl;
    }
    // END_CODE_COMPONENT_NAME_INTROSPECTION

    return comp;
}

// Primitive Objects serializers
int Serializer::DeserializeInt(EncoderNode* objNode) {
    map<string, void*>* data = (map<string, void*>*) objNode->obj_data;
    EncoderNode* valNode = (EncoderNode*) (*data)["value"];
    string strValue = *(string*) (valNode->obj_data); 
    int val = atoi(strValue.c_str());
    return val;
}

vector<int> Serializer::DeserializeIntList(EncoderNode* objNode) {
    vector<EncoderNode*>* objData = (vector<EncoderNode*>*) objNode->obj_data;
    vector<int> v;
    for (int i = 0; i < objData->size(); i++) {
        v.push_back(DeserializeInt((*objData)[i]));
    }

    return v;
}

string Serializer::DeserializeString(EncoderNode* objNode) {
    map<string, void*>* data = (map<string, void*>*) objNode->obj_data;
    EncoderNode* valNode = (EncoderNode*) (*data)["value"];
    string strValue = *(string*) (valNode->obj_data);
    return strValue; 
}

vector<string> Serializer::DeserializeStringList(EncoderNode* objNode) {
    vector<EncoderNode*>* objData = (vector<EncoderNode*>*) objNode->obj_data;
    vector<string> v;
    for (int i = 0; i < objData->size(); i++) {
        v.push_back(DeserializeString((*objData)[i]));
    }

    return v; 
}

float Serializer::DeserializeFloat(EncoderNode* objNode) {
    map<string, void*>* data = (map<string, void*>*) objNode->obj_data;
    EncoderNode* valNode = (EncoderNode*) (*data)["value"];
    string strValue = *(string*) (valNode->obj_data);
    cout << "StrValue " << strValue << endl;
    float val = atof(strValue.c_str());
    cout << "Final Value " << val << endl;

    return val; 
}

vector<float> Serializer::DeserializeFloatList(EncoderNode* objNode) {
    vector<EncoderNode*>* objData = (vector<EncoderNode*>*) objNode->obj_data;
    vector<float> v;
    for (int i = 0; i < objData->size(); i++) {
        v.push_back(DeserializeFloat((*objData)[i]));
    }

    return v; 
}

// START_CODE_COMPONENT_DESERIALIZERS_DEFINITION
TransformComponent* Serializer::DeserializeTransform(EncoderNode* componentNode) {
    if (!componentNode) {
        return NULL;
    }

    map<string, void*>* componentData = (map<string, void*>*) componentNode->obj_data;

    TransformComponent* transformComponent = new TransformComponent();
    transformComponent->position = DeserializeVector3((EncoderNode*) (*componentData)["position"]);
    transformComponent->rotation = DeserializeVector3((EncoderNode*) (*componentData)["rotation"]);
    transformComponent->scale = DeserializeVector3((EncoderNode*) (*componentData)["scale"]);

    return transformComponent;
}

RendererComponent* Serializer::DeserializeRenderer(EncoderNode* componentNode) {
    if (!componentNode) {
        return NULL;
    }

    map<string, void*>* componentData = (map<string, void*>*) componentNode->obj_data;

    RendererComponent* rendererComponent = new RendererComponent();
    rendererComponent->mesh = DeserializeMesh((EncoderNode*) (*componentData)["mesh"]);

    return rendererComponent;
}
// END_CODE_COMPONENT_DESERIALIZERS_DEFINITION

// START_CODE_OBJECT_DESERIALIZERS_DEFINITION
Vector3* Serializer::DeserializeVector3(EncoderNode* objNode) {
    map<string, void*>* data = (map<string, void*>*) objNode->obj_data;
    Vector3* obj = new Vector3();

    obj->x = DeserializeFloat((EncoderNode*) (*data)["x"]);
    obj->y = DeserializeFloat((EncoderNode*) (*data)["y"]);
    obj->z = DeserializeFloat((EncoderNode*) (*data)["z"]);

    return obj;
}

vector<Vector3*> Serializer::DeserializeVector3List(EncoderNode* objNode) {
    vector<EncoderNode*>* objData = (vector<EncoderNode*>*) objNode->obj_data;
    vector<Vector3*> v;
    for (int i = 0; i < objData->size(); i++) {
        v.push_back(DeserializeVector3((*objData)[i]));
    }

    return v;
}

Mesh* Serializer::DeserializeMesh(EncoderNode* objNode) {
    map<string, void*>* data = (map<string, void*>*) objNode->obj_data;
    Mesh* mesh = new Mesh();

    mesh->vertices = DeserializeVector3List((EncoderNode*) (*data)["vertices"]);      
    mesh->triangles = DeserializeIntList((EncoderNode*) (*data)["triangles"]);

    return mesh;
}

vector<Mesh*> Serializer::DeserializeMeshList(EncoderNode* objNode) {
    vector<EncoderNode*>* objData = (vector<EncoderNode*>*) objNode->obj_data;
    vector<Mesh*> v;
    for (int i = 0; i < objData->size(); i++) {
        v.push_back(DeserializeMesh((*objData)[i]));
    }

    return v; 
}
// END_CODE_OBJECT_DESERIALIZERS_DEFINITION
