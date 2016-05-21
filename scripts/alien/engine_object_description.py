import copy

class EngineObjectDescription:
    def __init__(self, name, include_file, fields=[]):
        self.name = name
        self.include_file = '/'.join(include_file.split('/')[1:])
        self.fields = copy.copy(fields)

    def add_field(self, field):
        self.fields.append(field)

    def serialize(self, indent=0):
        data = " " * indent + '<object name="%s">\n' % self.name
        for field in self.fields:
            data = data + field.serialize(indent + 4)
        data = data + " " * indent + "</object>\n"
        return data


