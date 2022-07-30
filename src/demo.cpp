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
#include <iostream>
#include <sstream>
#include <permutation>

auto combiner_function(const ya::combiner_iterator_list_t<int>& iterator_list) -> std::optional<std::string> {
    std::stringstream ss{};
    for(auto& it : iterator_list)
        ss << *it;
    return ss.str();
}

int main(int argc, char** argv) {
    std::vector<std::vector<int>> binary_choices = {{0,1},{0,1},{0,1}};
    ya::combiner_funct_t<std::string, int> x = combiner_function;
    auto permutations = ya::generate_permutations(binary_choices, x);
    for(auto& perm : permutations)
        std::cout << perm << std::endl;
    return 0;
}
