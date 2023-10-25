#include <iostream>
#include <algorithm>
#include "../include/MaximumSubArray.hpp"
#include "../include/ActivitySelection.hpp"

void test_activity_selection(int n = 10) {
    std::cout << __FUNCTION__  << std::endl;
    auto activities = get_activities(10);
    auto output = first_finish_prior(activities);
    std::for_each(output.begin(), output.end(), [](Activity a) {std::cout << a << ", ";});
}

int main(int argc, char* argv[]) {
    test_activity_selection();
    return 0;
}
