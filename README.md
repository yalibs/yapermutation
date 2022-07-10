# YA-PERMUTATION
yet another C/C++ permutation algorithm implementation. Header only C/C++ permutation algorithm

## Usage Notes
Keep note that the complexity of this algorithm increases exponentially: The more choices you provide, the more time it will take.

This library is _not_ the same as [`std::next_permutation`](https://en.cppreference.com/w/cpp/algorithm/next_permutation)

## Help Wanted
If you have a suggestion on how to decrease the complexity, please submit an issue or pull-request

## Example Usage
```c++
#include <permutation> // include the library

// define a function that combines the permutations into some type
// in this case, we combine a list of ints to a std::string
auto combiner_function(const ya::combiner_iterator_list_t<int>& iterator_list) -> std::string {
    std::stringstream ss{};
    for(auto& it : iterator_list)
        ss << *it;
    return ss.str();
}

int main(int argc, char** argv) {
    // construct the different choices
    std::vector<std::vector<int>> choices = {{0,1},{0,1},{1,2,3}};
    // call the library
    auto permutations = ya::generate_permutations(choices, combiner_function);
    // go through the generated permutations
    for(auto& perm : permutations)
        std::cout << perm << std::endl;
    return 0;
}
// RESULT:
// 001
// 002
// 003
// 011
// 012
// 013
// 101
// 102
// 103
// 111
// 112
// 113
```

