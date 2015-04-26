template <class Key, class T>
struct map {
    using size_type = std::size_t;
    map(size_type bucket_count = /* some default */);

    using value_type = std::pair<const Key, T>;

    iterator begin();
    const_iterator begin() const;

    iterator end();
    const_iterator end() const;

    // Args are arguments to constructing a value_type
    template <class... Args>
    iterator emplace(Args &&...args);

    iterator find(const Key &);
    const iterator find(const Key &) const;

    iterator erase(const_iterator);

    size_type size() const; 
    
    size_type bucket_count() const;
    
    float load_factor() const;

    float max_load_factor() const;
    void max_load_factor(float);
};
