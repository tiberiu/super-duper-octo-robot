#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

#include "serializer/decoder/textdecoder.h"

vector<std::string> TextDecoder::Tokenize(std::string data) {
    vector<std::string> tokens;
    bool quote = false;
    bool escape = false;
    for (int i = 0; i < data.size(); i++) {
        if (data[i] == ' ' || data[i] == '\t') {
            continue;
        }

        string token = string(1, data[i]);
        if (data[i] == '"') {
            for (i++; i < data.size(); i++) {
                if (data[i] == '\\') {
                    escape = true;
                    continue;
                }

                token = token + data[i];
                if (data[i] == '"' && !escape) {
                    break;
                }
            }
        }

        tokens.push_back(token);
    }

    return tokens;
}

Decoder::Node* TextDecoder::Decode(std::string data) {
    vector<std::string> tokens = this->Tokenize(data);
    return TextDecoder::DecodeTokens(tokens);
}

Decoder::Node* TextDecoder::DecodeTokens(vector<string> tokens) {
    Decoder::Node* node = NULL;
    if (tokens[0] == "{") {
        node = new Decoder::Node();
        node->isObj = true;
        node->data = this->DecodeObject(tokens);
    } else if (tokens[0] == "[") {
        node = new Decoder::Node();
        node->isList = true;
        node->data = this->DecodeList(tokens);
    } else {
        node = new Decoder::Node();
        node->isValue = true;
        node->data = this->DecodeValue(tokens);
    }

    return node;
}

vector<string> TextDecoder::ParseNextObject(vector<string> tokens, int position) {
    int depth = 0;
    vector<string> objTokens;
    for (int i = position; i < tokens.size(); i++) {
        if (tokens[i] == "{" || tokens[i] == "[") {
            depth++;
        } else if (tokens[i] == "}" || tokens[i] == "]") {
            depth--;
        }

        objTokens.push_back(tokens[i]);

        if (depth == 0) {
            break;
        }
    }

    return objTokens;
}

void* TextDecoder::DecodeList(vector<std::string> tokens) {
    vector<Decoder::Node*>* nodes = new vector<Decoder::Node*>();
    for (int i = 1; i < tokens.size(); i++) {        
        if (tokens[i] == ",") {
            continue;
        }

        if (tokens[i] == "]") {
            break;
        }

        vector<string> objTokens = ParseNextObject(tokens, i);
        Decoder::Node* node = DecodeTokens(objTokens);
        i = i + objTokens.size();
        (*nodes).push_back(node);
    }
    return (void*) nodes;
}

void* TextDecoder::DecodeObject(vector<std::string> tokens) {
    map<string, Decoder::Node*>* objData = new map<std::string, Decoder::Node*>();
    for (int i = 1; i < tokens.size(); i++) {
        if (tokens[i] == ",") {
            continue;
        }

        string key = tokens[i].substr(1, tokens[i].size() - 2);
        i += 2;
        vector<string> objTokens = ParseNextObject(tokens, i);
        Decoder::Node* node = this->DecodeTokens(objTokens);
        (*objData)[key] = node;
        i = i + objTokens.size();
    }

    return (void*) objData;
}

void* TextDecoder::DecodeValue(vector<std::string> tokens) {
    return (void*) new std::string(tokens[0].substr(1, tokens[0].size() - 2));
}
