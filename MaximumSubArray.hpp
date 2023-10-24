//
// Created by LiuShu on 2023/10/8.
// 输入一个数组, 找到和最大的子数组, 输出

#ifndef ALGORITHMDESIGN_MAXIMUMSUBARRAY_HPP
#define ALGORITHMDESIGN_MAXIMUMSUBARRAY_HPP

#include <iostream>
#include <vector>

using std::vector;

/**
 * 暴力求解
 * @tparam ElemType
 * @param input_array
 * @return maximum_subarray
 */
template<class ElemType>
vector<ElemType> naive(const vector<ElemType> &input_array)
{
    return input_array;
}


/**
 * 动态规划求解
 * @tparam ElemType
 * @param input_array
 * @return maximum_subarray
 */
template<class ElemType>
vector<ElemType> dynamic_programming(const vector<ElemType> &input_array)
{
    auto input_size = input_array.size();
    vector<ElemType> sum_array(input_array);
    vector<decltype(input_array.size())> terminal_index_array(input_size);

    for (auto index = input_size - 1; index >= 0; --index) {
        if (index ==  input_size - 1 or sum_array[index + 1] > 0) {
            sum_array[index] = input_array[index] + sum_array[index + 1];
            terminal_index_array[index] = terminal_index_array[index + 1];
        } else if (sum_array[index + 1] <= 0){
            sum_array[index] = input_array[index];
            terminal_index_array[index] = index;
        } else {
            std::cerr << "Undefined behavior in " << __func__ << std::endl;
        }
    }

    decltype(input_size) target_index = 0;
    for (auto i = 0; i < input_size; ++i) {
        if (sum_array[i] > sum_array[target_index])
            target_index = i;
    }

    return vector<ElemType> (
            input_array.cbegin() + target_index,
            input_array.cbegin() + terminal_index_array[target_index]);
}

template<class ElemType>
vector<ElemType> solve(const vector<ElemType> &input_array, const std::string &method)
{
    if (method == "naive")
        return naive(input_array);
    else
        return dynamic_programming(input_array);
}

#endif //ALGORITHMDESIGN_MAXIMUMSUBARRAY_HPP
