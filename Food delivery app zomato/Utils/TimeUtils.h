#ifndef TIME_UTILS_H
#define TIME_UTILS_H

#include <ctime>
#include <string>
using namespace std;

class TimeUtils {
public:
    static string get_current_time() {
        time_t now = time(0);
        char* dt = ctime(&now);
        string s(dt);
        if(!s.empty() && s.back() == '\n') {
            s.pop_back(); // Remove the newline character
        }
        return s;
    }
};

#endif