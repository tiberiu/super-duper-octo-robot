#include <map>
#include <vector>
#include <string>
#include "components/component.h"
#include "serializer/decoder/decoder.h"
#include "serializer/primitive_object_deserializers.h"
#include "geometry/mesh.h"
#include "geometry/vector3.h"
#include "components/renderercomponent.h"
#include "components/transformcomponent.h"
#include "serializer/object_deserializers.h"

Mesh* ObjectDeserializers::DeserializeMesh(Decoder::Node* objNode) {
    std::map<std::string, Decoder::Node*>* data = (std::map<std::string, Decoder::Node*>*) objNode->data;
    Mesh* obj = new Mesh();

	obj->vertices = DeserializeVector3List((Decoder::Node*) (*data)["vertices"]);
	obj->triangles = PrimitiveObjectDeserializers::DeserializeIntList((Decoder::Node*) (*data)["triangles"]);

    return obj;
}


std::vector<Mesh*> ObjectDeserializers::DeserializeMeshList(Decoder::Node* objNode) {
    std::vector<Decoder::Node*>* objData = (std::vector<Decoder::Node*>*) objNode->data;
    std::vector<Mesh*> v;
    for (int i = 0; i < objData->size(); i++) {
        v.push_back(DeserializeMesh((*objData)[i]));
    }

    return v;
}


Vector3* ObjectDeserializers::DeserializeVector3(Decoder::Node* objNode) {
    std::map<std::string, Decoder::Node*>* data = (std::map<std::string, Decoder::Node*>*) objNode->data;
    Vector3* obj = new Vector3();

	obj->x = PrimitiveObjectDeserializers::DeserializeFloat((Decoder::Node*) (*data)["x"]);
	obj->y = PrimitiveObjectDeserializers::DeserializeFloat((Decoder::Node*) (*data)["y"]);
	obj->z = PrimitiveObjectDeserializers::DeserializeFloat((Decoder::Node*) (*data)["z"]);

    return obj;
}


std::vector<Vector3*> ObjectDeserializers::DeserializeVector3List(Decoder::Node* objNode) {
    std::vector<Decoder::Node*>* objData = (std::vector<Decoder::Node*>*) objNode->data;
    std::vector<Vector3*> v;
    for (int i = 0; i < objData->size(); i++) {
        v.push_back(DeserializeVector3((*objData)[i]));
    }

    return v;
}


RendererComponent* ObjectDeserializers::DeserializeRendererComponent(Decoder::Node* objNode) {
    std::map<std::string, Decoder::Node*>* data = (std::map<std::string, Decoder::Node*>*) objNode->data;
    RendererComponent* obj = new RendererComponent();

	obj->mesh = DeserializeMesh((Decoder::Node*) (*data)["mesh"]);

    return obj;
}


std::vector<RendererComponent*> ObjectDeserializers::DeserializeRendererComponentList(Decoder::Node* objNode) {
    std::vector<Decoder::Node*>* objData = (std::vector<Decoder::Node*>*) objNode->data;
    std::vector<RendererComponent*> v;
    for (int i = 0; i < objData->size(); i++) {
        v.push_back(DeserializeRendererComponent((*objData)[i]));
    }

    return v;
}


TransformComponent* ObjectDeserializers::DeserializeTransformComponent(Decoder::Node* objNode) {
    std::map<std::string, Decoder::Node*>* data = (std::map<std::string, Decoder::Node*>*) objNode->data;
    TransformComponent* obj = new TransformComponent();

	obj->position = DeserializeVector3((Decoder::Node*) (*data)["position"]);
	obj->rotation = DeserializeVector3((Decoder::Node*) (*data)["rotation"]);
	obj->scale = DeserializeVector3((Decoder::Node*) (*data)["scale"]);

    return obj;
}


std::vector<TransformComponent*> ObjectDeserializers::DeserializeTransformComponentList(Decoder::Node* objNode) {
    std::vector<Decoder::Node*>* objData = (std::vector<Decoder::Node*>*) objNode->data;
    std::vector<TransformComponent*> v;
    for (int i = 0; i < objData->size(); i++) {
        v.push_back(DeserializeTransformComponent((*objData)[i]));
    }

    return v;
}


Component* ObjectDeserializers::DeserializeComponent(Decoder::Node* componentNode) {
    std::map<std::string, Decoder::Node*> *componentData = (std::map<std::string, Decoder::Node*>*) componentNode->data; 
    std::string obj_type = *(std::string*) ((*componentData)["__obj_type"]->data);

    Component* comp;
    if (obj_type == "RendererComponent") {
        comp = DeserializeRendererComponent(componentNode);
    } else if (obj_type == "TransformComponent") {
        comp = DeserializeTransformComponent(componentNode);
    }

    return comp;
}
