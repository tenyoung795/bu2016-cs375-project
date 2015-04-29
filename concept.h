template <class Key>
struct set {
    using size_type = std::size_t;
    set(size_type bucket_count = /* default number of buckets */, float max_load_factor = 0.75);

    iterator begin();
    const_iterator begin() const;

    iterator end();
    const_iterator end() const;

    template <class.. Args>
    iterator emplace(Args &&...);

    iterator find(const Key &);
    const iterator find(const Key &) const;

    iterator erase(const_iterator);

    size_type size() const; 
    
    size_type bucket_count() const;
    
    float load_factor() const;

    float max_load_factor() const;
    void max_load_factor(float);
};
