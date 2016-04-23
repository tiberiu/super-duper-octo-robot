#include <string>
#include <vector>
#include <map>
#include <iostream>

#include "source/serializer/encoder.h"

void EncoderNode::Decode(std::string raw_data) {
    if (raw_data[0] == '[') {
        isList = true;
        DecodeList(raw_data); 
    } else if (raw_data[0] == '{') {
        isObj = true;
        DecodeObj(raw_data); 
    } else if (raw_data[0] == '"') {
        isValue = true;
        DecodeValue(raw_data);
    }
}

void EncoderNode::DecodeList(std::string raw_data) {
    std::vector<EncoderNode*> *nodes = new std::vector<EncoderNode*>();
    for (int i = 1; i < raw_data.size() - 1; i++) {
        // Decode curent object
        int dpth = 0;
        bool quote = false;
        bool escape = false;
        int j;
        for (j = i; j < raw_data.size() - 1; j++) { 
            if ((raw_data[j] == '{' || raw_data[j] == '[') && !quote) {
                dpth++;
            }

            if ((raw_data[j] == '}' || raw_data[j] == ']') && !quote) {
                dpth--;
            }

            if (raw_data[j] == '"' && !escape) {
                quote = !quote;
            }

            if (raw_data[j] == '\\' && !escape) {
                escape = true;
            } else {
                escape = false;
            }

            if (dpth == 0 && !quote) {
                break;
            }
        }

        std::string obj_data = raw_data.substr(i, j - i + 1);            
        EncoderNode* node = new EncoderNode();
        node->Decode(obj_data);
        nodes->push_back(node);
        i = j + 1;
    }

    this->obj_data = (void*) nodes;
}

void EncoderNode::DecodeObj(std::string raw_data) {
    std::map<std::string, EncoderNode*> *nodes = new std::map<std::string, EncoderNode*>();
    for (int i = 1; i < raw_data.size(); i++) {
        // Parse name
        bool quote = false;
        bool escaped = false;
        std::string name = ParseToken(raw_data, i);
        i = i + name.size() + 1;
        // Parse object now
        std::string obj_data = "";
        if (raw_data[i] == '"') {
            obj_data = ParseToken(raw_data, i);
        } else {
            // list or object
            int dpth = 0;
            bool quote = false;
            bool escape = false;
            int j;
            for (j = i; j < raw_data.size() - 1; j++) { 
                if ((raw_data[j] == '{' || raw_data[j] == '[') && !quote) {
                    dpth++;
                }

                if ((raw_data[j] == '}' || raw_data[j] == ']') && !quote) {
                    dpth--;
                }

                if (raw_data[j] == '"' && !escape) {
                    quote = !quote;
                }

                if (raw_data[j] == '\\' && !escape) {
                    escape = true;
                } else {
                    escape = false;
                }

                if (dpth == 0) {
                    break;
                }
            }

            obj_data = raw_data.substr(i, (j - i + 1));
        }

        i = i + obj_data.size();
        EncoderNode* node = new EncoderNode();
        node->Decode(obj_data);
        (*nodes)[name.substr(1, name.size() - 2)] = node;            
    }

    this->obj_data = (void*) nodes;
}

void EncoderNode::DecodeValue(std::string raw_data) {
    std::string *value = new std::string(raw_data.substr(1, raw_data.size() - 2));
    this->obj_data = (void*) value;
}

std::string EncoderNode::ParseToken(std::string raw_data, int pos) {
    bool quote = false;
    bool escaped = false;
    std::string token = "";
    for (int j = pos; j < raw_data.size(); j++) {
        token = token + raw_data[j];

        if (raw_data[j] == '"' && !escaped) {
            quote = !quote;
        }

        if (raw_data[j] == '\\' && !escaped) {
            escaped = true;
        } else {
            escaped = false;
        }

        if (!quote) {
            break;
        }
    }

    return token;
}

std::string EncoderNode::RemoveIndentSpaces(std::string raw_obj_data) {
    std::string data = "";
    bool quote;
    bool escape = false;
    for (int i = 0; i < raw_obj_data.size(); i++) {
        if (raw_obj_data[i] == '"' && !escape) {
            quote = !quote;
        }

        if (raw_obj_data[i] == '\\' && !escape) {
            escape = true;
        } else {
            escape = false;
        }

        if (!quote && raw_obj_data[i] == ' ') {
            continue;
        } else {
            data = data + raw_obj_data[i];
        }
    }

    return data;
}

std::string EncoderNode::Encode(int indent) {
    std::string indent_string = "";
    for (int i = 0; i < indent; i++) {
        indent_string += " ";
    }

    std::string data = "";
    if (isValue) {
        data = indent_string + *((std::string*) this->obj_data) + "\n";
    } else if (isList) {
        data = indent_string + "[\n";
        std::vector<EncoderNode*> *nodes = (std::vector<EncoderNode*>*) this->obj_data;
        for (int i = 0; i < nodes->size(); i++) {
            data = data + (*nodes)[i]->Encode(indent + 4);
        }
        data = data + indent_string + "]\n"; 
    } else if (isObj) {
        data = indent_string + "{\n";
        std::map<std::string, EncoderNode*> *nodes = (std::map<std::string, EncoderNode*>*) this->obj_data;
        for (std::map<std::string, EncoderNode*>::iterator it = nodes->begin(); it != nodes->end(); it++) {
            std::string key = it->first;
            data = data + indent_string + key + ":\n" + (*nodes)[key]->Encode(indent + 4);
        }
        data = data + indent_string + "}\n"; 
    }

    return data;
}

