#ifndef SPARSE_ARRAY_H
#define SPARSE_ARRAY_H

#include <cstddef>

#include <algorithm>
#include <memory>
#include <utility>

namespace cs375 {

/**
 * A random-access continguous container
 * where some present may or may not have elements.
 * No method does bound checking; all indices are assumed
 * to fall within capacity.
 *
 * @tparam T the element type.
 */
template <class T>
class sparse_array {
    struct deleter {
        std::size_t capacity;
        void operator()(T *ptr) const {
            std::allocator<T>{}.deallocate(ptr, capacity);
        }
    };
    std::unique_ptr<T[], deleter> _data; 
    // Link all entries to make iteration efficient.
    std::unique_ptr<T *[]> _next;
    std::unique_ptr<T *[]> _prev;
    T *_head;
    std::size_t _size;

    template <class... Args>
    T &_do_emplace(std::size_t i, Args &&...args) {
        auto result = new(&_data[i]) T{std::forward<Args>(args)...};
        // The new node's next is the head.
        _next[i] = _head;
        // The head's previous is the new node.
        if (_head) _prev[_head - _data.get()] = result;
        _head = result;
        ++_size;

        return *result;
    }

    public:
    /**
     * Creates an empty sparse array of a given capacity.
     *
     * @param capacity the number of slots to support.
     */
    explicit sparse_array(std::size_t capacity):
        _data{std::allocator<T>{}.allocate(capacity), {capacity}},
        _next{new T *[capacity]{}},
        _prev{new T *[capacity]{}},
        _head{},
        _size{0} {
    }

    constexpr std::size_t capacity() const {
        return _data.get_deleter().capacity;
    }

    constexpr std::size_t size() const {
        return _size;
    }

    bool contains(std::size_t i) const {
        return _prev[i] || _head == &_data[i];
    }

    /**
     * Inserts an element at an index, if it is unoccupied.
     *
     * @param i the index.
     * @param args the element constructor arguments.
     * @tparam Args the element constructor argument types.
     * @return The pointer to the new element, or nullptr if the index is already occupied.
     */
    template <class... Args>
    T *emplace(std::size_t i, Args &&...args) {
        return contains(i) ? nullptr : &_do_emplace(i, std::forward<Args>(args)...);
    }

    /**
     * Inserts or assigns an element at an index.
     *
     * @param i the index.
     * @param arg the element assignment argument.
     * @tparam Arg the element assignment argument type.
     * @return The reference to the element.
     */
    template <class Arg>
    T &insert_or_assign(std::size_t i, Arg &&arg) {
        return contains(i)
            ? (_data[i] = std::forward<Arg>(arg))
            : *_do_emplace(i, std::forward<Arg>(arg));
    }

    const T *at(std::size_t i) const noexcept {
        return contains(i) ? &_data[i] : nullptr;
    }

    T *at(std::size_t i) noexcept {
        return contains(i) ? &_data[i] : nullptr;
    }

    bool erase(std::size_t i) noexcept {
        if (!contains(i)) return false;

        --_size;
        auto ptr = &_data[i];
        // The erased node's next's previous is now the erased node's previous.
        if (_next[i]) _prev[_next[i] - _data.get()] = _prev[i];
        // If erasing the head, we need to reset the head.
        if (_head == ptr) {
            // The head is now the erased head's next.
            _head = _next[i];
            // No need to reset _prev[i] since it must already be nullptr.
        } else {
            // The erased node's previous's next is now the erased node's next.
            _next[_prev[i] - _data.get()] = _next[i];
            _prev[i] = nullptr;
        }
        _next[i] = nullptr;
        ptr->~T();
        
        return true;
    }

    ~sparse_array() {
        for (auto ptr = _head; ptr; ptr = _next[ptr - _data.get()]) {
            ptr->~T();
        }
    }
};

}

#endif // SPARSE_ARRAY_H
