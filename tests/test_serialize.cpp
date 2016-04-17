#include <iostream>
#include <fstream>

#include "source/serializer/serializer.h"
#include "source/serializer/encoder.h"

using namespace std;

int main() {
    ifstream f("tests/test_data/sample_data.in");
    string data;
    while (!f.eof()) {
        string temp;
        getline(f, temp);
        cout << data << flush << endl;
        data = data + temp;
    }


    Serializer serializer;
    EncoderNode* node = serializer.LoadData(data);
    string output = node->Encode();

    cout << "\n\n" << output << endl;
}
