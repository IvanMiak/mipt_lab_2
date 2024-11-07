#include <iostream>
#include <assert.h>

using namespace std;

template<typename T, size_t N>
class Grid {
public:
    using size_type = unsigned;
    ~Grid<T, N>()
    {
        for(size_t i = 0; i < size; i++) {
            delete data[i];
        }
        delete[] data;
    }
    template <typename... Args>
    Grid<T, N>(size_t const size_1, Args...sizes) :
        size(size_1),
        data(nullptr)
    {
        data = new Grid<T, N - 1> * [size];
        for(size_t i = 0; i < size; i++) {
            data[i] = new Grid<T, N - 1>(sizes...);
        }
    }

    Grid<T, N>(Grid<T, N> const&) = delete;
    Grid<T, N>(Grid<T, N>&&) = delete;
    //Grid<T, N>& operator =(Grid<T, N> const&) = delete;
    //Grid<T, N>& operator =(Grid<T, N>&&) = delete;

    Grid<T, N - 1> const& operator[](size_t index) const
    {
        return get_at(index);
    }

    Grid<T, N - 1>& operator[](size_t index)
    {
        return get_at(index);
    }
    template <typename... Args>
    T const& operator()(size_t const index1, Args... indexes) const
    {
        return get_at(index1).operator()(indexes...);
    }
    template <typename... Args>
    T& operator()(size_t const index1, Args... indexes)
    {
        return get_at(index1).operator()(indexes...);
    }

    Grid<T, N>& operator=(Grid<T, N>& g) {
        //size = g.size;
        size_t i = 0;
        for(auto it = data, end = data + size; it != end; ++it) {
            **it = (g[i]);
            i++;
        }
        return *this;
    }

    Grid<T, N>& operator=(Grid<T, N> const& g) {
        //size = g.size;
        size_t i = 0;
        for(auto it = data, end = data + size; it != end; ++it) {
            **it = (g[i]);
            i++;
        }
        return *this;
    }

    Grid<T, N>& operator =(Grid<T, N>&& g) {
        //size = std::move(g.size);
        size_t i = 0;
        for(auto it = data, end = data + size; it != end; ++it) {
            **it = std::move(g[i]);
            i++;
        }
        return *this;
    }

    size_t size;
    Grid<T, N - 1>** data;

    Grid<T, N - 1> const& get_at(size_t index) const
    {
        assert(0 <= index && index < size);
        return *data[index];
    }

    Grid<T, N - 1>& get_at(size_t index)
    {
        assert(0 <= index && index < size);
        return *data[index];
    }
    size_t get_y_size() {
        return size;
    }
    size_t get_x_size() {
        return (*data[0]).size;
    }

};

template<typename T>
class Grid<T, 1> {
public:
    using size_type = unsigned;
    ~Grid<T, 1>() { delete[] data; }

    Grid<T, 1>(size_t const size, T const& t) :
        size(size),
        data(nullptr)
    {
        data = new T[size];
        for(size_t i = 0; i < size; i++) {
            data[i] = t;
        }
    }

    Grid<T, 1>(Grid<T, 1> const&) = delete;
    Grid<T, 1>(Grid<T, 1>&&) = delete;
    //Grid<T, 1>& operator =(Grid<T, 1> const&) = delete;
    //Grid<T, 1>& operator =(Grid<T, 1>&&) = delete;



    Grid<T, 1>& operator=(Grid<T, 1>& g) {
        //size = g.size;
        size_t i = 0;
        for(auto it = data, end = data + size; it != end; ++it) {
            *it = (g[i]);
            i++;
        }
        return *this;
    }

    Grid<T, 1>& operator=(Grid<T, 1> const& g) {
        //size = g.size;
        size_t i = 0;
        for(auto it = data, end = data + size; it != end; ++it) {
            *it = (g[i]);
            i++;
        }
        return *this;
    }

    Grid<T, 1>& operator =(Grid<T, 1>&& g) {
        size = std::move(g.size);
        size_t i = 0;
        for(auto it = data, end = data + size; it != end; ++it) {
            *it = std::move(g[i]);
            i++;
        }
        return *this;
    }

    T const& operator[](size_t index) const
    {
        return get_at(index);
    }

    T& operator[](size_t index)
    {
        return get_at(index);
    }

    T const& operator()(size_t index) const
    {
        return get_at(index);
    }

    T& operator()(size_t index)
    {
        return get_at(index);
    }

    T const& operator()(size_t const* index) const
    {
        return get_at(index);
    }

    T& operator()(size_t const* index)
    {
        return get_at(index);
    }

    size_t size;
    T* data;

    T const& get_at(size_t index) const
    {
        assert(0 <= index && index < size);
        return data[index];
    }

    T& get_at(size_t index)
    {
        assert(0 <= index && index < size);
        return data[index];
    }
};