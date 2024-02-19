#include <vector>
#include <iostream>

template <typename T, std::size_t N>
class StaticAllocator {
public:
    using value_type = T;

    // 预分配的内存块
    static inline T* memoryBlock = nullptr;
    static inline bool isAllocated = false;

    StaticAllocator() {
        // 在第一次使用时分配内存
        if (!isAllocated) {
            memoryBlock = static_cast<T*>(std::malloc(N * sizeof(T)));
            if (memoryBlock == nullptr) {
                throw std::bad_alloc();
            }
            isAllocated = true;
        }
    }

    ~StaticAllocator() {
        // 析构函数中不释放内存，以便重用
    }

    template <class U>
    constexpr StaticAllocator(const StaticAllocator<U, N>&) noexcept {}

    [[nodiscard]] T* allocate(std::size_t n) {
        if (n > N) {
            throw std::bad_alloc(); // 请求的大小超出预分配内存的容量
        }
        return memoryBlock; // 返回预分配的内存块
    }

    void deallocate(T* p, std::size_t n) noexcept {
        // 不实际释放内存，以便下次重用
    }
};

template <typename T, std::size_t N>
using StaticVector = std::vector<T, StaticAllocator<T, N>>;

int main() {
    // 使用StaticVector，它配置了StaticAllocator
    for (int i = 0; i < 100000; ++i) {
        StaticVector<int, 100> vec(100);
        // 使用vec...
        // 注意：vec在每次迭代时不会分配新内存，而是重用相同的内存块
    }

    // 程序结束前释放内存
    std::free(StaticAllocator<int, 100>::memoryBlock);
    return 0;
}

