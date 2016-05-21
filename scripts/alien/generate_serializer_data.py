from code_parser import CodeParser
from code_generator import CodeGenerator

code_directory = "include/"
output_file = "data.conf"

codeParser = CodeParser()
ecosystem = codeParser.generate_data_structure(code_directory, output_file)

codeGenerator = CodeGenerator()
codeGenerator.generate_deserializers(ecosystem)
