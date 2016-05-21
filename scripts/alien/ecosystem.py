from engine_component_description import EngineComponentDescription
from engine_object_description import EngineObjectDescription

class Ecosystem:    
    def __init__(self):
        self.ecosystem = {"objects": [], "components": []}

    def add_class_description(self, class_description):
        if not class_description:
            return

        if isinstance(class_description, EngineComponentDescription):
            self.ecosystem['components'].append(class_description)
        elif isinstance(class_description, EngineObjectDescription):
            self.ecosystem['objects'].append(class_description)

    def get_code_version(self):
        bashCommand = "git rev-parse HEAD"
        import subprocess
        process = subprocess.Popen(bashCommand.split(), stdout=subprocess.PIPE)
        output = process.communicate()[0][:-1]

        return output

    def serialize(self, indent=0):
        version = self.get_code_version() 
        data = " " * indent + '<ecosystem version="%s">\n' % version
        for obj in self.ecosystem["objects"] + self.ecosystem["components"]:
            data = data + obj.serialize(indent + 4)

        data = data + " " * indent + '</ecosystem>'
        return data


