#include <iostream>
#include <map>

#include "allocator.h"
#include "linkedlist.h"

using namespace std;

constexpr std::size_t factorial(const int& n)
{
    std::size_t res = 1, i = 1;
    for(; i <= n; ++i)
        res *= i;
    return res;
}

int main()
{
    try
    {
        std::map<int, int> m1;
        for (std::size_t i = 0; i < 10; ++i)
            m1.insert(std::make_pair(i, factorial(i)));

        Allocator<std::pair<const int, int>> alMap{10};
        std::map<int, int, std::less<int>, Allocator<std::pair<const int, int>> > m2{alMap};
        for (std::size_t i = 0; i < 10; ++i)
            m2.insert(std::make_pair(i, factorial(i)));

        for (auto const& p: m2)
        {
            std::cout << p.first << " " << p.second << std::endl;
        }

        List<int> l1;
        for (int i = 0; i < 10; ++i)
            l1.pushBack(i);

        Allocator<int> alList{10};
        List<int, Allocator<int>> l2{alList};
        for (int i = 0; i < 10; ++i)
            l2.pushBack(i);

        l2.print();
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
