#pragma once
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class Leaderboard {
public:
    vector<string> names;
    vector<int> times;
    string entireString;

    void readFile() {
        names.clear();
        times.clear();
        string filename = "files/leaderboard.txt";
        ifstream file(filename);
        if (!file.is_open()) {
            cout << "Failed to open file " << filename << endl;
            return;
        }

        string line;
        int count = 0;
        while (getline(file, line) && count < 5) {
            istringstream ss(line);
            string time;
            string name;
            if (getline(ss, time, ',') && getline(ss, name)) {
                names.push_back(name);
                int colonPos = time.find(":");
                if (colonPos != string::npos) {
                    int minutes = stoi(time.substr(0, colonPos));
                    int seconds = stoi(time.substr(colonPos + 1));
                    int totalSeconds = minutes * 60 + seconds;
                    times.push_back(totalSeconds);
                }
            }
            count++;
        }
        file.close();

        updateEntireString();
    }

    void updateEntireString() {
        ostringstream ss;
        for (int i = 0, j = 1; i < times.size(); i++, j++) {
            ss << j << ".\t";
            ss << setfill('0') << setw(2) << times[i] / 60 << ":";
            ss << setfill('0') << setw(2) << times[i] % 60 << "\t";
            ss << names[i] << "\n\n";
        }
        entireString = ss.str();
    }

    void writeToFile(string name, int time) {
        string filename = "files/leaderboard.txt";
        ifstream fileIn(filename);
        if (!fileIn.is_open()) {
            cout << "Failed to open file " << filename << endl;
            return;
        }

        vector<pair<int, string>> scores;
        string line;
        while (getline(fileIn, line)) {
            istringstream ss(line);
            string timeStr, name;
            if (getline(ss, timeStr, ',') && getline(ss, name)) {
                int colonPos = timeStr.find(":");
                if (colonPos != string::npos) {
                    int minutes = stoi(timeStr.substr(0, colonPos));
                    int seconds = stoi(timeStr.substr(colonPos + 1));
                    int totalSeconds = minutes * 60 + seconds;
                    scores.push_back({ totalSeconds, line });
                }
            }
        }
        fileIn.close();

        int minutes = time / 60;
        int seconds = time % 60;
        string timeStr = to_string(minutes / 10) + to_string(minutes % 10) + ":" +
                         to_string(seconds / 10) + to_string(seconds % 10);

        scores.push_back({ time, timeStr + "," + name });
        sort(scores.begin(), scores.end());

        ofstream fileOut(filename);
        if (!fileOut.is_open()) {
            cout << "Failed to open file " << filename << endl;
            return;
        }

        int numScores = min((int)scores.size(), 5);
        for (int i = 0; i < numScores; i++) {
            fileOut << scores[i].second << endl;
        }

        for (int i = 5; i < scores.size(); i++) {
            fileOut << scores[i].second << endl;
        }

        fileOut.close();
        readFile();
    }
};