#include <iostream>
#include <fstream>

#include "serializer/serializer.h"
#include "serializer/encoder.h"

using namespace std;

int main() {
    Serializer serializer;
    string data = serializer.LoadRawData("resources/test_data/sample_data.in");
    EncoderNode* node = serializer.LoadData(data);
    string output = node->Encode();

    cout << "\n\n" << output << endl;
}
