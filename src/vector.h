#pragma once

#include <initializer_list>
#include <iostream>

namespace ng {
    /*
    * @class vector
    * Похожий аналог std::vector
    */
    template <class T, class Allocator = std::allocator<T>>
    class vector {
    public:
        using value_type = T;
        using reference = T&;
        using const_reference = const T&;
        using size_type = std::size_t;
        using iterator = T*;
        using const_iterator = const T*;
        using pointer = T*;
        using const_pointer = const T*;
        using allocator_type = Allocator;
        using traits = std::allocator_traits<Allocator>;

    private:
        T* data_;
        size_type size_;
        size_type capacity_;
        Allocator allocator_;

    public:
        /*=========================================================*/
        /*                                                         */
        /*                 VECTOR MEMBER FUNCTIONS                 */
        /*                                                         */
        /*=========================================================*/

        vector() : size_(0u), capacity_(0u), data_(nullptr), allocator_(Allocator()) {}
        vector(std::initializer_list<value_type> const& items, const Allocator & = Allocator());
        explicit vector(const Allocator& a) : size_(0u), capacity_(0u), data_(nullptr), allocator_(a) {}
        explicit vector(size_type size, const T & = T(), const Allocator & = Allocator());
        vector(const vector& other);
        vector(vector&& other) noexcept;
        ~vector();

        vector& operator=(const vector& other);
        vector& operator=(vector&& other) noexcept;

        /*=========================================================*/
        /*                                                         */
        /*                  VECTOR ELEMENT ACCESS                  */
        /*                                                         */
        /*=========================================================*/

        reference at(size_type pos);
        const_reference at(size_type pos) const;
        reference operator[](size_type pos) { return data_[pos]; }
        const_reference operator[](size_type pos) const { return data_[pos]; }
        reference front() { return data_[0]; }
        const_reference front() const { return data_[0]; }
        reference back() { return size() == 0 ? data_[0] : data_[size_ - 1]; }
        const_reference back() const { return size() == 0 ? data_[0] : data_[size_ - 1]; }
        pointer data() { return data_; }
        const_pointer data() const { return data_; }

        /*=========================================================*/
        /*                                                         */
        /*                     VECTOR ITERATORS                    */
        /*                                                         */
        /*=========================================================*/

        iterator begin() const { return data_; }
        const_iterator cbegin() const { return data_; }
        iterator end() const { return data_ + size_; }
        const_iterator cend() const { return data_ + size_; }

        /*=========================================================*/
        /*                                                         */
        /*                     VECTOR CAPACITY                     */
        /*                                                         */
        /*=========================================================*/

        bool empty() const { return cbegin() == cend(); }
        size_type size() const { return size_; }
        size_type capacity() const { return capacity_; }
        size_type max_size() const { return traits::max_size(allocator_); }
        void reserve(size_type size);
        void shrink_to_fit();

        /*=========================================================*/
        /*                                                         */
        /*                     VECTOR MODIFIERS                    */
        /*                                                         */
        /*=========================================================*/

        void clear() noexcept;
        void push_back(const_reference value);
        void push_back(value_type&& value);
        iterator insert(iterator pos, const_reference value);
        void erase(iterator pos);
        void pop_back();
        void swap(vector& other);
        void resize(size_type count);
        void resize(size_type count, const_reference value);

        template <class... Args>
        iterator insert_many(const_iterator pos, Args &&...args);

        template <class... Args>
        reference insert_many_back(Args &&...args);

    private:
        pointer allocate_memory(size_type size, size_type capacity, const T& value,
            Allocator& allocator);
        pointer allocate_memory(size_type size, size_type capacity, const_pointer arr,
            Allocator& allocator);
        void deallocate_memory(size_type size, size_type capacity, pointer arr,
            Allocator& allocator);
        void swap_(vector& to, vector& from);
    };

}  //!namespace ng

#include "vector_realization.h"
