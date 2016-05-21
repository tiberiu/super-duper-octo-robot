DESERIALIZER_DECLARATION = "[TYPE]* Deserialize[TYPE](Decoder::Node* objNode);"
LIST_DESERIALIZER_DECLARATION = "std::vector<[TYPE]*> Deserialize[TYPE]List(Decoder::Node* objNode);"

FIELD_DESERIALIZE = "obj->[FIELDNAME] = Deserialize[FIELDTYPE]((Decoder::Node*) (*data)[\"[FIELDNAME]\"]);"
FIELD_DESERIALIZE_ARRAY = "obj->[FIELDNAME] = Deserialize[FIELDTYPE]List((Decoder::Node*) (*data)[\"[FIELDNAME]\"]);"

PRIMITIVE_FIELD_DESERIALIZE = "obj->[FIELDNAME] = PrimitiveObjectDeserializers::Deserialize[FIELDTYPE]((Decoder::Node*) (*data)[\"[FIELDNAME]\"]);"
PRIMITIVE_FIELD_DESERIALIZE_ARRAY = "obj->[FIELDNAME] = PrimitiveObjectDeserializers::Deserialize[FIELDTYPE]List((Decoder::Node*) (*data)[\"[FIELDNAME]\"]);"

DESERIALIZER_STRUCTURE = \
"""
[TYPE]* ObjectDeserializers::Deserialize[TYPE](Decoder::Node* objNode) {
    std::map<std::string, Decoder::Node*>* data = (std::map<std::string, Decoder::Node*>*) objNode->data;
    [TYPE]* obj = new [TYPE]();

[FIELD-DESERIALIZERS]

    return obj;
}
"""

# TODO: This unfortunately means we can't do vector<vector<type>>
LIST_DESERIALIZER_STRUCTURE = \
"""
std::vector<[TYPE]*> ObjectDeserializers::Deserialize[TYPE]List(Decoder::Node* objNode) {
    std::vector<Decoder::Node*>* objData = (std::vector<Decoder::Node*>*) objNode->data;
    std::vector<[TYPE]*> v;
    for (int i = 0; i < objData->size(); i++) {
        v.push_back(Deserialize[TYPE]((*objData)[i]));
    }

    return v;
}
"""

COMPONENT_DESERIALIZER_DECLARATION = "Component* DeserializeComponent(Decoder::Node* componentNode);"

COMPONENT_DESERIALIZER_STRUCTURE = \
"""
Component* ObjectDeserializers::DeserializeComponent(Decoder::Node* componentNode) {
    std::map<std::string, Decoder::Node*> *componentData = (std::map<std::string, Decoder::Node*>*) componentNode->data; 
    std::string obj_type = *(std::string*) ((*componentData)["__obj_type"]->data);

    Component* comp;
    [DESERIALIZER-TESTS]

    return comp;
}
"""

COMPONENT_DESERIALIZER_TEST = \
"""if (obj_type == "[TYPE]") {
        comp = Deserialize[TYPE](componentNode);
    }"""

WRAPPER_CLASS_STRUCTURE = \
"""
class ObjectDeserializers {
public:
[DESERIALIZERS-SIGNATURES]
};
"""

INCLUDE_LINE = "#include \"[PATH]\""

PRIMITIVE_FIELD_TYPES = ["int", "float", "string"]

class CodeGenerator:
    def generate_object_deserializers(self, obj):
        field_deserializers = []
        for field in obj.fields:
            if field.fieldType.lower() not in PRIMITIVE_FIELD_TYPES:
                field_deserializer = FIELD_DESERIALIZE
                if field.isArray:
                    field_deserializer = FIELD_DESERIALIZE_ARRAY
            else:
                field_deserializer = PRIMITIVE_FIELD_DESERIALIZE
                if field.isArray:
                    field_deserializer = PRIMITIVE_FIELD_DESERIALIZE_ARRAY

            field_deserializer = field_deserializer.replace("[FIELDNAME]", field.name)
            field_deserializer = field_deserializer.replace("[FIELDTYPE]", field.fieldType.capitalize()) 
            field_deserializers.append(field_deserializer)

        declaration = DESERIALIZER_DECLARATION
        declaration = declaration.replace("[TYPE]", obj.name)

        definition = DESERIALIZER_STRUCTURE
        definition = definition.replace("[TYPE]", obj.name)

        definition = definition.replace("[FIELD-DESERIALIZERS]", "\n".join(("\t" + field for field in field_deserializers)))

        list_declaration = LIST_DESERIALIZER_DECLARATION
        list_declaration = list_declaration.replace("[TYPE]", obj.name)

        list_definition = LIST_DESERIALIZER_STRUCTURE
        list_definition = list_definition.replace("[TYPE]", obj.name)

        return [(declaration, definition), (list_declaration, list_definition)]

    def generate_component_deserializer(self, ecosystem):
        tests = []
        for comp in ecosystem.ecosystem["components"]:
            test = COMPONENT_DESERIALIZER_TEST.replace("[TYPE]", comp.name)
            tests.append(test)

        comp_deserializer = COMPONENT_DESERIALIZER_STRUCTURE
        comp_deserializer = comp_deserializer.replace("[DESERIALIZER-TESTS]",
                                  ' else '.join(tests))

        comp_deserializer_declaration = COMPONENT_DESERIALIZER_DECLARATION
        return (comp_deserializer_declaration, comp_deserializer)

    def generate_deserializers(self, ecosystem):
        h_file = open("include/serializer/object_deserializers.h", "w")
        cpp_file = open("source/serializer/object_deserializers.cpp", "w")

        include_lines = [
            "#include <map>",
            "#include <vector>",
            "#include <string>",
            "#include \"components/component.h\"",
            "#include \"serializer/decoder/decoder.h\"",
            "#include \"serializer/primitive_object_deserializers.h\""
        ]
        objects = ecosystem.ecosystem["objects"]
        deserializers = []
        for obj in objects:
            include_line = INCLUDE_LINE.replace("[PATH]", obj.include_file)
            include_lines.append(include_line)
            deserializers.extend(self.generate_object_deserializers(obj))

        components = ecosystem.ecosystem["components"]
        for comp in components:
            include_line = INCLUDE_LINE.replace("[PATH]", comp.include_file)
            include_lines.append(include_line) 
            deserializers.extend(self.generate_object_deserializers(comp))

        deserializers.append(self.generate_component_deserializer(ecosystem))

        class_structure = WRAPPER_CLASS_STRUCTURE
        class_structure = class_structure.replace("[DESERIALIZERS-SIGNATURES]", '\n'.join('\t' + deserializer[0] for deserializer in deserializers)) 

        h_file.write('\n'.join(include_lines))
        h_file.write('\n')
        h_file.write(class_structure)

        include_lines.append("#include \"serializer/object_deserializers.h\"")
        cpp_file.write('\n'.join(include_lines))
        cpp_file.write('\n')
        cpp_file.write('\n'.join(deserializer[1] for deserializer in deserializers))


