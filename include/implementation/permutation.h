/* MIT License

Copyright (c) 2022 Asger Gitz-Johansen

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
#ifndef YAPERMUTATION_PERMUTATION_H
#define YAPERMUTATION_PERMUTATION_H
#include <numeric>
#include <vector>
#include <optional>

namespace ya {
    struct _n_digit_num_t {
        std::vector<size_t> max_digits;
        std::vector<size_t> number;
        _n_digit_num_t(std::vector<size_t>&& m, std::vector<size_t>&& n) : max_digits{std::move(m)}, number{std::move(n)} {}
        void operator++() {
            for(size_t i = number.size()-1; i >= 0; i--) {
                if(number[i] < max_digits[i]) {
                    number[i]++;
                    break;
                }
                number[i] = 0;
            }
        }
    };

    template<typename T>
    using combiner_iterator_t = typename std::vector<T>::const_iterator;
    template<typename T>
    using combiner_iterator_list_t = std::vector<combiner_iterator_t<T>>;
    template<typename R, typename T>
    using combiner_funct_t = std::function<std::optional<R>(const combiner_iterator_list_t<T>&)>;

    template<typename T, typename R>
    auto generate_permutations(const std::vector<std::vector<T>>& input, combiner_funct_t<R,T> combiner) {
        std::vector<size_t> m{}; m.reserve(input.size());
        std::vector<size_t> n{}; n.reserve(input.size());
        for(auto& v : input) {
            n.push_back(0);
            if(v.empty()) {
                m.push_back(0);
                continue;
            }
            m.push_back(v.size()-1);
        }
        auto plus_one_mult = [](const size_t& a, const size_t& b){ return a * (b+1); };
        auto max_num = std::accumulate(m.begin(), m.end(), 1, plus_one_mult);
        _n_digit_num_t tt{std::move(m),std::move(n)};
        std::vector<R> result{}; result.reserve(max_num);
        std::vector<typename std::vector<T>::const_iterator> c{}; c.reserve(tt.number.size());
        for(int i = 0; i < max_num; i++) {
            c.clear();
            for(size_t j = 0; j < tt.number.size(); j++)
                c.push_back(input[j].begin() + tt.number[j]);
            auto x = combiner(c);
            if(x)
                result.push_back(*x);
            ++tt;
        }
        return result;
    }
}

#endif //YAPERMUTATION_PERMUTATION_H
