#include "serializer/serializer.h"
#include "gameobject.h"

Decoder::Node* Serializer::LoadData(string raw_data) {
    Decoder* decoder = Decoder::GetDecoder(raw_data);
    Decoder::Node* node = decoder->Decode(raw_data);
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
    Decoder::Node* data = LoadData(raw_data);

    // TODO: assert data.isList
    vector<Decoder::Node*> *scenesData = (vector<Decoder::Node*>*) data->data;
    vector<Scene*> scenes;
    for (int i = 0; i < scenesData->size(); i++) {
        Decoder::Node* sceneNode = (*scenesData)[i];
        map<string, Decoder::Node*> *sceneData = (map<string, Decoder::Node*>*) sceneNode->data;
        string sceneName = DeserializeString((*sceneData)["name"]);
        string sceneDataPath = DeserializeString((*sceneData)["dataPath"]);
        Scene* scene = new Scene(sceneName, sceneDataPath);
        scenes.push_back(scene);
    }

    return scenes;
}

void Serializer::LoadScene(string raw_data, Scene& scene) {
    Decoder::Node* data = LoadData(raw_data);

    // TODO: Assert data.isList
    vector<Decoder::Node*> *gameObjectsData = (vector<Decoder::Node*>*) data->data;
    for (int i = 0; i < gameObjectsData->size(); i++) {
        // TODO: Assert gameObjectsData[i].isObj
        // TODO: Assert gameObjectsData[i]->__obj_type = GameObject
        Decoder::Node* gameObjectNode = (Decoder::Node*) (*gameObjectsData)[i];
        map<string, Decoder::Node*>* gameObjectData = (map<string, Decoder::Node*>*) gameObjectNode->data; 
        string name = DeserializeString((Decoder::Node*) (*gameObjectData)["name"]);
        GameObject* gameObject = new GameObject(name);

        // Deserialize Components
        if (!(*gameObjectData)["components"]) {
            // No components
            break;
        }

        Decoder::Node* componentsNode = (Decoder::Node*) (*gameObjectData)["components"];
        vector<Decoder::Node*> *componentsData = (vector<Decoder::Node*>*) componentsNode->data;
        for (int j = 0; j < componentsData->size(); j++) {
            Decoder::Node* componentNode = (Decoder::Node*) (*componentsData)[j];
            Component* component = DeserializeComponent(componentNode);

            if (component) {
                gameObject->AddComponent(component);
            }
        }

        scene.AddGameObject(gameObject);
    }
}

Component* Serializer::DeserializeComponent(Decoder::Node* componentNode) {
    // TODO: Assert componentNode.isObj
    map<string, Decoder::Node*> *componentData = (map<string, Decoder::Node*> *) componentNode->data;
    string obj_type = *(string*) ((*componentData)["__obj_type"]->data);

    // START_CODE_COMPONENT_NAME_INTROSPECTION
    Component* comp;
    if (obj_type == "TransformComponent") {
        comp = DeserializeTransform(componentNode);
    } else if (obj_type == "RendererComponent") {
        comp = DeserializeRenderer(componentNode);
    }
    // END_CODE_COMPONENT_NAME_INTROSPECTION

    return comp;
}

// Primitive Objects serializers
int Serializer::DeserializeInt(Decoder::Node* objNode) {
    string strValue = *(string*) (objNode->data); 
    int val = atoi(strValue.c_str());
    return val;
}

vector<int> Serializer::DeserializeIntList(Decoder::Node* objNode) {
    vector<Decoder::Node*>* objData = (vector<Decoder::Node*>*) objNode->data;
    vector<int> v;
    for (int i = 0; i < objData->size(); i++) {
        v.push_back(DeserializeInt((*objData)[i]));
    }

    return v;
}

string Serializer::DeserializeString(Decoder::Node* objNode) {
    string strValue = *(string*) (objNode->data);
    return strValue; 
}

vector<string> Serializer::DeserializeStringList(Decoder::Node* objNode) {
    vector<Decoder::Node*>* objData = (vector<Decoder::Node*>*) objNode->data;
    vector<string> v;
    for (int i = 0; i < objData->size(); i++) {
        v.push_back(DeserializeString((*objData)[i]));
    }

    return v; 
}

float Serializer::DeserializeFloat(Decoder::Node* objNode) {
    string strValue = *(string*) (objNode->data);
    float val = atof(strValue.c_str());

    return val; 
}

vector<float> Serializer::DeserializeFloatList(Decoder::Node* objNode) {
    vector<Decoder::Node*>* objData = (vector<Decoder::Node*>*) objNode->data;
    vector<float> v;
    for (int i = 0; i < objData->size(); i++) {
        v.push_back(DeserializeFloat((*objData)[i]));
    }

    return v; 
}

// START_CODE_COMPONENT_DESERIALIZERS_DEFINITION
TransformComponent* Serializer::DeserializeTransform(Decoder::Node* componentNode) {
    if (!componentNode) {
        return NULL;
    }

    map<string, Decoder::Node*>* componentData = (map<string, Decoder::Node*>*) componentNode->data;

    TransformComponent* transformComponent = new TransformComponent();
    transformComponent->position = DeserializeVector3((Decoder::Node*) (*componentData)["position"]);
    transformComponent->rotation = DeserializeVector3((Decoder::Node*) (*componentData)["rotation"]);
    transformComponent->scale = DeserializeVector3((Decoder::Node*) (*componentData)["scale"]);

    return transformComponent;
}

RendererComponent* Serializer::DeserializeRenderer(Decoder::Node* componentNode) {
    if (!componentNode) {
        return NULL;
    }

    map<string, Decoder::Node*>* componentData = (map<string, Decoder::Node*>*) componentNode->data;

    RendererComponent* rendererComponent = new RendererComponent();
    rendererComponent->mesh = DeserializeMesh((Decoder::Node*) (*componentData)["mesh"]);

    return rendererComponent;
}
// END_CODE_COMPONENT_DESERIALIZERS_DEFINITION

// START_CODE_OBJECT_DESERIALIZERS_DEFINITION
Vector3* Serializer::DeserializeVector3(Decoder::Node* objNode) {
    map<string, Decoder::Node*>* data = (map<string, Decoder::Node*>*) objNode->data;
    Vector3* obj = new Vector3();

    obj->x = DeserializeFloat((Decoder::Node*) (*data)["x"]);
    obj->y = DeserializeFloat((Decoder::Node*) (*data)["y"]);
    obj->z = DeserializeFloat((Decoder::Node*) (*data)["z"]);

    return obj;
}

vector<Vector3*> Serializer::DeserializeVector3List(Decoder::Node* objNode) {
    vector<Decoder::Node*>* objData = (vector<Decoder::Node*>*) objNode->data;
    vector<Vector3*> v;
    for (int i = 0; i < objData->size(); i++) {
        v.push_back(DeserializeVector3((*objData)[i]));
    }

    return v;
}

Mesh* Serializer::DeserializeMesh(Decoder::Node* objNode) {
    map<string, Decoder::Node*>* data = (map<string, Decoder::Node*>*) objNode->data;
    Mesh* mesh = new Mesh();

    mesh->vertices = DeserializeVector3List((Decoder::Node*) (*data)["vertices"]);      
    mesh->triangles = DeserializeIntList((Decoder::Node*) (*data)["triangles"]);

    return mesh;
}

vector<Mesh*> Serializer::DeserializeMeshList(Decoder::Node* objNode) {
    vector<Decoder::Node*>* objData = (vector<Decoder::Node*>*) objNode->data;
    vector<Mesh*> v;
    for (int i = 0; i < objData->size(); i++) {
        v.push_back(DeserializeMesh((*objData)[i]));
    }

    return v; 
}
// END_CODE_OBJECT_DESERIALIZERS_DEFINITION
