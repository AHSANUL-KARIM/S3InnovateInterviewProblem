#include <iostream>
#include<cstdio>
#include <chrono>
#include <ctime>

using namespace std;
using namespace chrono;

int main() {
    string start_time_str;
    string end_time_str;
    cout << "Start time (YYYY-MM-DD HH:MM:SS AM/PM): ";
    getline(std::cin,start_time_str);
    cout << "End time (YYYY-MM-DD HH:MM:SS AM/PM): ";
    getline(std::cin,end_time_str);

    struct tm start_time = {};
    strptime(start_time_str.c_str(), "%Y-%m-%d %I:%M:%S %p", &start_time);
    time_t start_time_t = mktime(&start_time);
    auto start = system_clock::from_time_t(start_time_t);
    
    struct tm end_time = {};
    strptime(end_time_str.c_str(), "%Y-%m-%d %I:%M:%S %p", &end_time);
    time_t end_time_t = mktime(&end_time);
    auto end = system_clock::from_time_t(end_time_t);
    
    int pulse_rate = 0;
    float bill = 0;
    while (start < end) {
        auto start_hour = duration_cast<hours>(start.time_since_epoch()).count() % 24;
        auto start_hour_end = duration_cast<hours>(start.time_since_epoch() + 20s).count() % 24;;
        
        if (start_hour >= 9 && start_hour < 23) {
            pulse_rate = 30;
        }
        else if(start_hour < 9 && start_hour_end >= 9){
            pulse_rate = 30;
        }
        else if(start_hour >= 23 && start_hour_end >= 9)
        {
            pulse_rate = 30;
        }
        else if(start_hour >= 9 && start_hour_end >= 23){
             pulse_rate = 30;
        }
        else if(start_hour < 23 && start_hour_end >= 23){
             pulse_rate = 30;
        }
        else {
            pulse_rate = 20;
        }
        start += 20s;
        bill += pulse_rate;
    }
    
    cout << "Total bill: " << bill/100 << " taka" << endl;
    
    return 0;
}
