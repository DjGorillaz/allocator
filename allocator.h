#pragma once

#include <memory>
#include <vector>

template<typename T>
class Allocator
{
public:
    using value_type = T;

    template <class U>
    struct rebind {
        typedef Allocator<U> other;
    };

    Allocator(std::size_t sz);
    Allocator(const Allocator& al);
    ~Allocator() = default;

    template<typename U>
    Allocator<T>(const Allocator<U>& al);

    T* allocate(std::size_t n);
    void deallocate(T* p, std::size_t n);

    template<typename U, typename ... Args>
    void construct(U* p, Args&& ... args);

    template<typename U>
    void destroy(U* p);

    std::size_t getBlockSize() const;

private:
    std::size_t blockSize;
    std::size_t offset;
    std::vector<std::unique_ptr<char[]>> blocks;
};

template<typename T>
Allocator<T>::Allocator(std::size_t sz): blockSize(sz)
{
    if (sz <= 0) throw std::invalid_argument("Block size must be greater than zero");
}

template<typename T>
Allocator<T>::Allocator(const Allocator& al): blockSize(al.blockSize)
{  }

template<typename T>
template <typename U>
Allocator<T>::Allocator(const Allocator<U>& al)
{
    blockSize = al.getBlockSize();
}

template<typename T>
T* Allocator<T>::allocate(std::size_t n)
{
    if (offset >= blockSize || blocks.empty())
    {
        blocks.emplace_back(std::make_unique<char[]>(blockSize * sizeof(T)));
        offset = 0;
    }
    offset += n;
    return (reinterpret_cast<T*>(blocks.back().get() + (offset-n)*sizeof(T)));
}

template <typename T>
void Allocator<T>::deallocate(T* /* p */, std::size_t /* n */)
{  }

template<typename T>
template <typename U, typename ... Args>
void Allocator<T>::construct(U* p, Args&& ... args)
{
    new(p) U(std::forward<Args>(args)...);
}

template <typename T>
template<typename U>
void Allocator<T>::destroy(U* p)
{
    p->~U();
}

template <typename T>
std::size_t Allocator<T>::getBlockSize() const
{
    return blockSize;
}
