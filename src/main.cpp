#include <iostream>
#include <algorithm>
#include "../include/MaximumSubArray.hpp"
#include "../include/ActivitySelection.hpp"


void test_activity_selection(int n = 10) {
    std::cout << "====== "<<  __FUNCTION__ << " ======" << std::endl;
    auto activities = get_activities(10);
    std::cout << "Input:" << std::endl;
    std::for_each(activities.begin(), activities.end(), [](Activity a) {std::cout << "\t"<<a;});
    std::cout << "------" << std::endl;

    auto output = first_finish_prior(activities);
    std::cout << "Output:" << std::endl;
    std::for_each(output.begin(), output.end(), [](Activity a) {std::cout << "\t"<<a;});
    std::cout << "------" << std::endl;

    output = last_start_prior(activities);
    std::cout << "Output:" << std::endl;
    std::for_each(output.begin(), output.end(), [](Activity a) {std::cout << "\t"<<a;});
    std::cout << "------" << std::endl;

    output = shortest_prior(activities);
    std::cout << "Output:" << std::endl;
    std::for_each(output.begin(), output.end(), [](Activity a) {std::cout << "\t"<<a;});
    std::cout << "------" << std::endl;

    output = first_start_prior(activities);
    std::cout << "Output:" << std::endl;
    std::for_each(output.begin(), output.end(), [](Activity a) {std::cout << "\t"<<a;});
    std::cout << "------" << std::endl;

    output = least_conflict_prior(activities);
    std::cout << "Output:" << std::endl;
    std::for_each(output.begin(), output.end(), [](Activity a) {std::cout << "\t"<<a;});
    std::cout << "------" << std::endl;
}

int main(int argc, char* argv[]) {
    test_activity_selection();
    return 0;
}
