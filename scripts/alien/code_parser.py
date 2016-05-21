import copy
import os
from os.path import isfile, isdir, join
import re

from ecosystem import Ecosystem
from engine_component_description import EngineComponentDescription
from engine_object_description import EngineObjectDescription
from field_description import FieldDescription

ENGINE_OBJECT_REGEX = re.compile("\s*//\s*EngineObject\((?P<objectName>\w*)\)")
ENGINE_COMPONENT_REGEX = re.compile("\s*//\s*EngineComponent\((?P<componentName>\w*)\)")
ENGINE_FIELD_REGEX = re.compile("\s*//\s*EngineField\((?P<fieldType>[\w<>]*)\s*,\s*(?P<fieldName>\w*)\)")
ARRAY_TYPE_REGEX = re.compile("\s*array\s*\<\s*(?P<type>\w*)\s*\>")

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

    def parse_class_file(self, input_lines, include_path):
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
                current_class = EngineComponentDescription(component_name, include_path)
            elif matches['object']:
                self.ecosystem.add_class_description(copy.copy(current_class))
                component_name = matches['object'].group('objectName')
                current_class = EngineObjectDescription(component_name, include_path)
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

            self.parse_class_file(lines, path)
            f.close()

    def generate_data_structure(self, code_directory, output_file):
        files = self.get_class_files(code_directory)
        self.ecosystem = Ecosystem()
        self.parse_files(files)

        f = open(output_file, "w")
        f.write(self.ecosystem.serialize())
        f.close()

        return self.ecosystem


