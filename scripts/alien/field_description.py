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
