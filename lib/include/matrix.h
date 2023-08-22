#pragma once

#include <cstddef>
#include <concepts>
#include <unordered_map>
#include <tuple>

struct key
{
    std::size_t i, j;

    key(std::size_t i, std::size_t j)
        : i(i), j(j)
    {

    }

    bool operator == (const key& k) const
    {
        return i == k.i && j == k.j;
    }
};

struct hash
{
    /// Pairing function: https://en.wikipedia.org/wiki/Pairing_function
    std::size_t operator()(const key& k) const
    {
        return 0.5 * (k.i + k.j) * (k.i + k.j + 1) + k.j;
    }
};

template<std::integral T, T default_value>
class matrix
{
private:
    class map_wrapper
    {
    public:
        using matrix_iterator = typename std::unordered_map<key, T, hash>::iterator;

        map_wrapper() = default;

        ~map_wrapper() = default;

        T get(std::size_t row_index, std::size_t column_index)
        {
            auto it = map.find(key(row_index, column_index));
            return it == map.end() ? default_value : it->second;
        }

        void assign(std::size_t row_index, std::size_t column_index, T value)
        {
            if (value != default_value) {
                map[key(row_index, column_index)] = value;
            }
            else {
                map.erase(key(row_index, column_index));
            }
        }

        matrix_iterator begin()
        {
            return map.begin();
        }

        matrix_iterator end()
        {
            return map.end();
        }

        std::size_t size()
        {
            return map.size();
        }
    private:
        std::unordered_map<key, T, hash> map;
    };

    class column_proxy
    {
    public:
        column_proxy(std::size_t row_index, std::size_t column_index, map_wrapper& wrapper)
            : row_index(row_index), column_index(column_index), wrapper(wrapper)
        {

        }

        ~column_proxy() = default;

        column_proxy& operator=(T value)
        {
            wrapper.assign(row_index, column_index, value);
            return *this;
        }

        operator T()
        {
            return wrapper.get(row_index, column_index);
        }

        bool operator==(T value) const
        {
            return wrapper.get(row_index, column_index) == value;
        }

        bool operator!=(T value) const
        {
            return !operator==(value);
        }

    private:
        std::size_t row_index;
        std::size_t column_index;
        map_wrapper& wrapper;
    };

    class row_proxy
    {
    public:
        row_proxy(std::size_t row_index, map_wrapper& wrapper)
            : row_index(row_index), wrapper(wrapper)
        {

        }

        ~row_proxy() = default;

        column_proxy operator[](std::size_t column_index)
        {
            return column_proxy(row_index, column_index, wrapper);
        }

    private:
        std::size_t row_index;
        map_wrapper& wrapper;
    };

    class iterator
    {
    public:
        using value_type = std::tuple<std::size_t, std::size_t, T>;

        iterator(typename map_wrapper::matrix_iterator iter)
            : iter(iter)
        {

        }

        value_type operator*()
        {
            return std::make_tuple(iter->first.i, iter->first.j, iter->second);
        }

        iterator& operator++()
        {
            ++iter;
            return *this;
        }

        bool operator==(const iterator& other)
        {
            return (iter == other.iter);
        }

        bool operator!=(const iterator& other)
        {
            return !(*this == other);
        }

    private:
        typename map_wrapper::matrix_iterator iter;
    };

public:
    matrix() = default;
    ~matrix() = default;

    row_proxy operator[](std::size_t row_index)
    {
        return row_proxy(row_index, wrapper);
    }

    std::size_t size()
    {
        return wrapper.size();
    }

    iterator begin()
    {
        return iterator(wrapper.begin());
    }

    iterator end()
    {
        return iterator(wrapper.end());
    }

private:
    map_wrapper wrapper;
};
