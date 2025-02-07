#include <algorithm>
#include <list>
#include <deque>
#include <iterator>
#include <vector>
#include <iostream>

// Iterator used to handle groupings of elements
template<typename Iterator>
class group_iterator {
private:
    Iterator _it;
    std::size_t _size;

public:
    using iterator_category = std::random_access_iterator_tag;
    using iterator_type     = Iterator;
    using value_type        = typename std::iterator_traits<Iterator>::value_type;
    using difference_type   = typename std::iterator_traits<Iterator>::difference_type;
    using pointer           = typename std::iterator_traits<Iterator>::pointer;
    using reference         = typename std::iterator_traits<Iterator>::reference;

    group_iterator(Iterator it, std::size_t size) : _it(it), _size(size) {}

    group_iterator& operator++() {
        std::advance(_it, _size);
        return *this;
    }

    group_iterator operator++(int) {
        group_iterator tmp = *this;
        ++(*this);
        return tmp;
    }

    reference operator*() const { return *_it; }
    pointer operator->() { return &(*_it); }

    bool operator==(const group_iterator& other) const { return _it == other._it; }
    bool operator!=(const group_iterator& other) const { return !(*this == other); }

    // Access elements in groups
    Iterator group_end() const {
        Iterator tmp = _it;
        std::advance(tmp, _size);
        return tmp;
    }
};

