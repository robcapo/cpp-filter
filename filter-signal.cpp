#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <stdlib.h>
#include "filter.h"

using namespace std;

template<typename T>
ostream& operator<<(ostream& os, const vector<T>& vec);

string readString(ifstream &fp);
unsigned readUnsigned(ifstream &fp);
unsigned short readUnsignedShort(ifstream &fp);
double readDouble(ifstream &fp);
vector<double> loadFile(string fname);

int main()
{
    string fileName;
    cout << "Enter the file: ";
    cin >> fileName;

    vector<double> input = loadFile(fileName);


    cout << "Enter the b coefficients: ";

    vector<double> b;
    string bBuffer;

    while (getline(cin, bBuffer)) {

        istringstream ssin(bBuffer);
        double bi;
        while (ssin >> bi) {
            b.push_back(bi);
        }

        if (b.size()) {
            break;
        }
    }

    vector<double> a;
    cout << "Enter the a coefficients: ";

    string aBuffer;
    while (getline(cin, aBuffer)) {

        istringstream ssin(aBuffer);
        double ai;
        while (ssin >> ai) {
            a.push_back(ai);
        }

        if (a.size()) {
            break;
        }
    }

    cout << "Creating a filter with: " << endl
         << "b = " << b << endl << "a = " << a << endl;

    Filter filt = Filter(b, a);

    vector<double> output = filt.filter(input);

    string outfile;
    cout << "Enter the output file name: ";
    cin >> outfile;

    ofstream fpOut;
    fpOut.open(outfile);

    for (unsigned i = 0; i < output.size(); i++) {
        fpOut << output[i] << endl;
    }

    cout << "Done!";
}

template<typename T>
ostream& operator<<(ostream& os, const vector<T>& vec)
{
    os << '[';
    int n = vec.size();
    if (n != 0) {
        os << vec[0];
        for (int i = 1; i < n; i++) {
            os << ", " << vec[i];
        }
    }
    os << ']';
    return os;
}

// http://www.topherlee.com/software/pcm-tut-wavformat.html for wav spec
vector<double> loadFile(string fname)
{
    vector<double> samples;
    ifstream fh(fname, ios::in | ios::binary);

    if (fh.is_open()) {
        string riff, wave, fmt, dataStr; // RIFF
        unsigned fileSize, formatLength, dataSize, sampleRate, bytesPerSecond;
        unsigned short formatType, numChannels, blockAlign, bitsPerSample; //our 16 values 
        
        vector<double> data;

        riff = readString(fh);
        
        if (riff == "RIFF")   { //we had 'RIFF' let's continue 
            fileSize = readUnsigned(fh);
            wave = readString(fh);

            if (wave == "WAVE")  { //this is probably a wave file since it contained "WAVE" 
                fmt = readString(fh);
                
                formatLength   = readUnsigned(fh);
                formatType     = readUnsignedShort(fh);
                numChannels    = readUnsignedShort(fh);
                sampleRate     = readUnsigned(fh);
                bytesPerSecond = readUnsigned(fh);
                blockAlign     = readUnsignedShort(fh);
                bitsPerSample  = readUnsignedShort(fh);
                dataStr        = readString(fh);
                dataSize       = readUnsigned(fh);

                cout << "RIFF: " << riff << endl
                     << "File Size: " << fileSize << endl
                     << "WAVE: " << wave << endl
                     << "FMT: " << fmt << endl
                     << "Format Length: " << formatLength << endl
                     << "Format Type: " << formatType << endl
                     << "Num channels: " << numChannels << endl
                     << "Sample Rate: " << sampleRate << endl
                     << "Bytes per second: " << bytesPerSecond << endl
                     << "Block align: " << blockAlign << endl
                     << "Bits per sample: " << bitsPerSample << endl
                     << "Data string: " << dataStr << endl
                     << "Data size: " << dataSize << endl;

                while (!fh.eof()) {
                    samples.push_back(readDouble(fh));
                }

                cout << "Loaded " << samples.size() << " samples." << endl
                     << "First sample: " << samples[1] << endl;

            } else {
                cout << "Error: RIFF file but not a wave file" << endl;
            }
        } else {
            cout << "Error: not a RIFF file" << endl;
        }
    } else {
        cout << "Failed to open file" << endl;
    }

    return samples;
}

void writeFile(vector<double> samples, string fname)
{

}

string readString(ifstream &fp)
{
    char charString[5];
    fp.read(&charString[0], 4);
    charString[4] = 0;

    return string(&charString[0]);
}

unsigned readUnsigned(ifstream &fp)
{
    char charString[5];
    fp.read(&charString[0], 4);
    charString[4] = 0;

    return *((unsigned *) &charString[0]);
}

unsigned short readUnsignedShort(ifstream &fp)
{
    char charString[3];
    fp.read(&charString[0], 2);
    charString[2] = 0;

    return *((unsigned short*) &charString[0]);
}

double readDouble(ifstream &fp)
{
    char charString[5];
    fp.read(&charString[0], 4);
    charString[4] = 0;

    return *((float*) &charString[0]);
}
