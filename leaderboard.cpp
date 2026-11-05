#pragma once
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <exception>
using namespace std;

class Leaderboard {
public:
    vector<string> names;
    vector<int> times;
    string entireString;

    // Converts "MM:SS" to seconds. Returns false if the text isn't a valid time.
    bool parseTime(const string& timeStr, int& totalSeconds) {
        size_t colonPos = timeStr.find(":");
        if (colonPos == string::npos) {
            return false;
        }
        try {
            int minutes = stoi(timeStr.substr(0, colonPos));
            int seconds = stoi(timeStr.substr(colonPos + 1));
            totalSeconds = minutes * 60 + seconds;
        } catch (const exception&) {
            return false;
        }
        return true;
    }

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
            int totalSeconds;
            if (getline(ss, time, ',') && getline(ss, name) && parseTime(time, totalSeconds)) {
                names.push_back(name);
                times.push_back(totalSeconds);
                count++;
            }
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
        // A missing file just means no scores yet; it gets created below.
        ifstream fileIn(filename);

        vector<pair<int, string>> scores;
        string line;
        while (getline(fileIn, line)) {
            istringstream ss(line);
            string timeStr, savedName;
            int totalSeconds;
            if (getline(ss, timeStr, ',') && getline(ss, savedName) && parseTime(timeStr, totalSeconds)) {
                scores.push_back({ totalSeconds, line });
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

        // Star the new score on screen only, so it isn't saved to the file.
        for (int i = 0; i < times.size(); i++) {
            if (times[i] == time && names[i] == name) {
                names[i] += "*";
                updateEntireString();
                break;
            }
        }
    }
};