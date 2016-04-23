#include <iostream>
#include <fstream>

#include "source/serializer/serializer.h"
#include "source/serializer/encoder.h"

using namespace std;

int main() {
    Serializer serializer;
    string data = serializer.LoadRawData("tests/test_data/sample_data.in");
    EncoderNode* node = serializer.LoadData(data);
    string output = node->Encode();

    cout << "\n\n" << output << endl;
}
