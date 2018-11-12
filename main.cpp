#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <queue>
#include <iterator>
#include "Passenger.h"
#include "Simulator.h"

using namespace std;

template <class Container>
void split1(const string& str, Container& cont)
{
    istringstream iss(str);
    copy(istream_iterator<string>(iss),
         istream_iterator<string>(),
         back_inserter(cont));
}

void scenerios(queue<Passenger> passengers, string output, int numLugCount, int numSecCount){
    ofstream myfile;
    myfile.open (output);
    Simulator s1(passengers, false, false, false, numLugCount, numSecCount);
    myfile<< s1.avgWaitingTime << " " << s1.numMissedFlights << endl;
    Simulator s2(passengers, true, false, false, numLugCount, numSecCount);
    myfile<< s2.avgWaitingTime << " " << s2.numMissedFlights << endl;
    Simulator s3(passengers, false, true, false, numLugCount, numSecCount);
    myfile<< s3.avgWaitingTime << " " << s3.numMissedFlights << endl;
    Simulator s4(passengers, true, true, false, numLugCount, numSecCount);
    myfile<< s4.avgWaitingTime << " " << s4.numMissedFlights << endl;
    Simulator s5(passengers, false, false, true, numLugCount, numSecCount);
    myfile<< s5.avgWaitingTime << " " << s5.numMissedFlights << endl;
    Simulator s6(passengers, true, false, true, numLugCount, numSecCount);
    myfile<< s6.avgWaitingTime << " " << s6.numMissedFlights << endl;
    Simulator s7(passengers, false, true, true, numLugCount, numSecCount);
    myfile<< s7.avgWaitingTime << " " << s7.numMissedFlights << endl;
    Simulator s8(passengers, true, true, true, numLugCount, numSecCount);
    myfile<< s8.avgWaitingTime << " " << s8.numMissedFlights << endl;
    myfile.close();
}


int main(int argc, char* argv[]) {
    // below reads the input file
    // in your next projects, you will implement that part as well
    if (argc != 3) {
        cout << "Run the code with the following command: ./project2 [input_file] [output_file]" << endl;
        return 1;
    }

    cout << "input file: " << argv[1] << endl;
    cout << "output file: " << argv[2] << endl;


    // here, perform the input operation. in other words,
    // read the file named <argv[1]>
    ifstream infile(argv[1]);
    string line;
    vector<string> input;
    // process first line
    getline(infile, line);
    split1(line, input);
    if(!input.empty()) {
        int N = stoi(input[0]);
        int numLugCount = stoi(input[1]);
        int numSecCount = stoi(input[2]);
        cout << "number of input lines: " << N << endl;
        queue<Passenger> passengers;

        for (int i = 0; i < N; i++) {
            getline(infile, line);
            cout << "line: " << line << endl;

            vector<string> words;
            split1(line, words);
            Passenger p(stoi(words[0]), stoi(words[1]), stoi(words[2]), stoi(words[3]), words[4].c_str()[0],
                        words[5].c_str()[0]);
            passengers.push(p);
        }

        cout << "input file has been read" << endl;

        // here, perform the output operation. in other words,
        // print your results into the file named <argv[2]>
        scenerios(passengers, argv[2], numLugCount, numSecCount);
    }

    return 0;
}
