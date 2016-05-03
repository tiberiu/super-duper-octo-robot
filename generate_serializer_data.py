import copy
import os
from os.path import isfile, isdir, join
import re
import sys

ENGINE_OBJECT_REGEX = re.compile("\s*//\s*EngineObject\((?P<objectName>\w*)\)")
ENGINE_COMPONENT_REGEX = re.compile("\s*//\s*EngineComponent\((?P<componentName>\w*)\)")
ENGINE_FIELD_REGEX = re.compile("\s*//\s*EngineField\((?P<fieldType>[\w<>]*)\s*,\s*(?P<fieldName>\w*)\)")
ARRAY_TYPE_REGEX = re.compile("\s*array\s*\<\s*(?P<type>\w*)\s*\>")

class FieldDescription:
    def __init__(self, name, fieldType, isArray):
        self.name = name
        self.fieldType = fieldType
        self.isArray = isArray

    def serialize(self, indent=0):
        isArray = str(self.isArray).lower()
        return " " * indent + '<field type="%s" name="%s" isArray="%s"/>\n' % (self.fieldType, 
                                                                               self.name,
                                                                               isArray) 

    def __repr__(self):
        return "[" + self.fieldType + ": " + self.name + "]" 

class EngineObjectDescription:
    def __init__(self, name, fields=[]):
        self.name = name
        self.fields = copy.copy(fields)

    def add_field(self, field):
        self.fields.append(field)

    def serialize(self, indent=0):
        data = " " * indent + '<object name="%s">\n' % self.name
        for field in self.fields:
            data = data + field.serialize(indent + 4)
        data = data + " " * indent + "</object>\n"
        return data

class EngineComponentDescription:
    def __init__(self, name, fields=[]):
        self.name = name
        self.fields = copy.copy(fields)

    def add_field(self, field):
        self.fields.append(field)

    def serialize(self, indent=0):
        data = " " * indent + '<component name="%s">\n' % self.name
        for field in self.fields:
            data = data + field.serialize(indent + 4)
        data = data + " " * indent + "</component>\n"
        return data

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

class CodeParser:
    def get_directory_files(self, path):
        entries = os.listdir(path)
        files = []
        for entry in entries:
            if isfile(join(path, entry)):
                files.append(join(path, entry))
            elif isdir(join(path, entry)):
                files.extend(self.get_directory_files(join(path, entry)))

        return files

    def get_class_files(self, code_directory):
        files = self.get_directory_files(code_directory)
        return filter(lambda path: path.endswith(".h"), files)

    def parse_class_file(self, input_lines):
        current_class = None
        current_type = ''
        for line in input_lines:
            matches = {
                'component': re.match(ENGINE_COMPONENT_REGEX, line),
                'object': re.match(ENGINE_OBJECT_REGEX, line),
                'field': re.match(ENGINE_FIELD_REGEX, line)
            }        

            if matches['component']:
                self.ecosystem.add_class_description(copy.copy(current_class))
                component_name = matches['component'].group('componentName')
                current_class = EngineComponentDescription(component_name)
            elif matches['object']:
                self.ecosystem.add_class_description(copy.copy(current_class))
                component_name = matches['object'].group('objectName')
                current_class = EngineObjectDescription(component_name)
            elif matches['field']:
                field_type = matches['field'].group('fieldType')
                field_name = matches['field'].group('fieldName')
                isArray = False

                arrayMatch = re.match(ARRAY_TYPE_REGEX, field_type)
                if arrayMatch:
                    isArray = True
                    field_type = arrayMatch.group("type")

                current_class.add_field(FieldDescription(field_name, field_type, isArray))

        self.ecosystem.add_class_description(copy.copy(current_class))

    def parse_files(self, files):
        for path in files:
            f = open(path, "r")
            lines = []
            for line in f:
                lines.append(line)

            self.parse_class_file(lines)
            f.close()

    def generate_data_structure(self, code_directory, output_file):
        files = self.get_class_files(code_directory)
        self.ecosystem = Ecosystem()
        self.parse_files(files)

        f = open(output_file, "w")
        f.write(self.ecosystem.serialize())
        f.close()

code_directory = "include/"
output_file = "data.conf"

codeParser = CodeParser()
codeParser.generate_data_structure(code_directory, output_file)
