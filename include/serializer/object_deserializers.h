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

class ObjectDeserializers {
public:
	Mesh* DeserializeMesh(Decoder::Node* objNode);
	std::vector<Mesh*> DeserializeMeshList(Decoder::Node* objNode);
	Vector3* DeserializeVector3(Decoder::Node* objNode);
	std::vector<Vector3*> DeserializeVector3List(Decoder::Node* objNode);
	RendererComponent* DeserializeRendererComponent(Decoder::Node* objNode);
	std::vector<RendererComponent*> DeserializeRendererComponentList(Decoder::Node* objNode);
	TransformComponent* DeserializeTransformComponent(Decoder::Node* objNode);
	std::vector<TransformComponent*> DeserializeTransformComponentList(Decoder::Node* objNode);
	Component* DeserializeComponent(Decoder::Node* componentNode);
};
