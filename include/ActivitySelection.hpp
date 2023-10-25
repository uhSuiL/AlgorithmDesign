// [Greedy Algorithm]
//
// Activity Selection Problem:
//  Input:
//      - A set of activities: S = {a1, a2,..., an}
//      - The start time si and finish time fi of activity ai
//  Output:
//      - Subset of activities S', where for each ai and aj, si >= fj or fi <= fj
//      - Maximize |S'|


#ifndef ALGORITHMDESIGN_ACTIVITYSELECTION_HPP
#define ALGORITHMDESIGN_ACTIVITYSELECTION_HPP

#include <iostream>
#include <vector>
#include <random>
#include <algorithm>

using std::vector;


struct Activity
{
    int s;  // start time
    int f;  // finish time
    Activity(int s, int f): s(s), f(f) {};
    friend std::ostream& operator<<(std::ostream &os, const Activity &a) {
        os << "Activity["<<a.s<<"->"<<a.f<<"]";
        return os;
    }
};

vector<Activity> get_activities(int n)
{
    vector<Activity> activities;

    std::random_device rd;
    std::mt19937 mt = std::mt19937(rd());
    std::uniform_int_distribution<int> dist = std::uniform_int_distribution<int>(1, 24);

    for (int i = 0; i < n; ++i) {
        Activity a = Activity(dist(mt), dist(mt));
        activities.push_back(a);
    }

    return activities;
}


vector<Activity> first_finish_prior(vector<Activity> s) {
    std::sort(s.begin(), s.end(), [](Activity a1, Activity a2) {return a1.f < a2.f;});
    std::for_each(s.begin(), s.end(), [](Activity a) {std::cout << a << ", ";});

}

#endif //ALGORITHMDESIGN_ACTIVITYSELECTION_HPP
