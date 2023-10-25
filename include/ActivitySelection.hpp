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
        os << "Activity["<<a.s<<"->"<<a.f<<"]" << std::endl;
        return os;
    }
};

/**
 * 获取n个Activity组成的集合(deque)
 * @param n 活动数量
 * @return
 */
deque<Activity> get_activities(int n)
{
    deque<Activity> activities;

    std::random_device rd;
    std::mt19937 mt = std::mt19937(rd());
    std::uniform_int_distribution<int> dist = std::uniform_int_distribution<int>(1, 24);

    for (int i = 0; i < n; ++i) {
        auto s = dist(mt), f = dist(mt);
        if (s > f)
            std::swap(s, f);
        else if (s == f) {
            auto tmp_dist = std::uniform_int_distribution<int>(1, s);
            s -= tmp_dist(mt);
        }

        Activity a = Activity(s, f);
        activities.push_back(a);
    }

    return activities;
}

/**
 * 删除s中与a冲突的元素
 * @param a
 * @param s
 */
void drop_conflict(const Activity &a, deque<Activity> &s) {
    auto it = s.cbegin();
    while (it != s.cend()) {
        if (it->s <= a.f)  // TODO: 条件判断bug
            it = s.erase(it);
        else
            ++it;
    }
}

/**
 * [loop]取s的第一个元素, 然后删除s中与之冲突的元素, 直到s为空
 * @param s
 * @return
 */
deque<Activity> drop_conflict(deque<Activity> &s) {
    deque<Activity> output;
    while (!s.empty()) {
        auto a = s[0];
        output.push_back(a);
        s.pop_front();
        drop_conflict(a, s);
    }
    return output;
}

size_t count_conflict(const Activity &a, const deque<Activity> &s) {
    size_t num_conflict = 0;
    for (auto it = s.begin(); it < s.end(); ++it) {
        if (a.s < it->f or a.f > it->s)  // TODO: 条件判断bug
            ++num_conflict;
    }
    return num_conflict;
}

// ========================== Algorithms ==========================

/**
 * 最早结束活动优先
 *  先对所有活动按照结束时间从早到晚排序
 *  [loop]拿到一个活动, 排除剩下活动中与之时间冲突的活动, 直到没有剩余活动
 * @param s 候选活动集
 * @return 最终活动集
 */
deque<Activity> first_finish_prior(deque<Activity> s) {
    std::cout << "==== "<< __FUNCTION__ << " ====" <<std::endl;

    std::sort(s.begin(), s.end(), [](Activity a1, Activity a2) {return a1.f < a2.f;});

    std::cout << "sorted s: " << std::endl;;
    std::for_each(s.begin(), s.end(), [](Activity a) {std::cout << "\t"<<a;});
    std::cout << std::endl;

    deque<Activity> output = drop_conflict(s);
    return output;
}

deque<Activity> last_start_prior(deque<Activity> s) {
    std::cout << "==== "<< __FUNCTION__ << " ====" <<std::endl;
    std::sort(s.begin(), s.end(), [](Activity a1, Activity a2) {return a1.s > a2.s;});

    std::cout << "sorted s: " << std::endl;;
    std::for_each(s.begin(), s.end(), [](Activity a) {std::cout << "\t"<<a;});
    std::cout << std::endl;

    deque<Activity> output = drop_conflict(s);
    return output;
}

deque<Activity> shortest_prior(deque<Activity> s) {
    std::cout << "==== "<< __FUNCTION__ << " ====" <<std::endl;

    std::sort(s.begin(), s.end(),
              [](Activity a1, Activity a2) {return (a1.f - a1.s) < (a2.s - a2.f);});

    std::cout << "sorted s: " << std::endl;;
    std::for_each(s.begin(), s.end(), [](Activity a) {std::cout << "\t"<<a;});
    std::cout << std::endl;

    deque<Activity> output = drop_conflict(s);
    return output;
}

deque<Activity> first_start_prior(deque<Activity> s) {
    std::cout << "==== "<< __FUNCTION__ << " ====" <<std::endl;

    std::sort(s.begin(), s.end(), [](Activity a1, Activity a2) {return a1.s < a2.s;});

    std::cout << "sorted s: " << std::endl;;
    std::for_each(s.begin(), s.end(), [](Activity a) {std::cout << "\t"<<a;});
    std::cout << std::endl;

    deque<Activity> output = drop_conflict(s);
    return output;
}

deque<Activity> least_conflict_prior(deque<Activity> s) {
    std::cout << "==== "<< __FUNCTION__ << " ====" <<std::endl;

    deque<Activity> output;
    while (!s.empty()) {
        std::sort(s.begin(), s.end(),
                  [s](Activity a1, Activity a2) {return count_conflict(a1, s) < count_conflict(a2, s);});
        auto a = s[0];
        output.push_back(a);
        s.pop_front();
        drop_conflict(a, s);
    }
    return output;
}

#endif //ALGORITHMDESIGN_ACTIVITYSELECTION_HPP
