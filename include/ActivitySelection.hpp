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
#include <deque>
#include <random>
#include <algorithm>

using std::deque;


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

deque<Activity> get_activities(int n)
{
    deque<Activity> activities;

    std::random_device rd;
    std::mt19937 mt = std::mt19937(rd());
    std::uniform_int_distribution<int> dist = std::uniform_int_distribution<int>(1, 24);

    for (int i = 0; i < n; ++i) {
        Activity a = Activity(dist(mt), dist(mt));
        activities.push_back(a);
    }

    return activities;
}

/**
 * 最早结束活动优先
 *  先对所有活动按照结束时间从早到晚排序
 *  [loop]拿到一个活动, 排除剩下活动中与之时间冲突的活动, 直到没有剩余活动
 * @param s 候选活动集
 * @return 最终活动集
 */
deque<Activity> first_finish_prior(deque<Activity> s) {
    std::sort(s.begin(), s.end(), [](Activity a1, Activity a2) {return a1.f < a2.f;});
    std::for_each(s.begin(), s.end(), [](Activity a) {std::cout << a << ", ";});
    std::cout << std::endl;

    deque<Activity> output;
    while (!s.empty()) {
        auto a = s[0];
        output.push_back(a);
        s.pop_front();

        auto it = s.cbegin();
        while (it != s.cend()) {
            if (it->s <= a.f)
                it = s.erase(it);
            else
                ++it;
        }
    }

    return output;
}

#endif //ALGORITHMDESIGN_ACTIVITYSELECTION_HPP
