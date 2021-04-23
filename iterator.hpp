#ifndef ITERATOR_H
#define ITERATOR_H

namespace seg_tree{
    template<typename T>
    class Iterator
    {
        private:
        T* ptr_;

        public:
        Iterator(T* ptr):ptr_(ptr) 
        { }

        Iterator& operator++()
        {
            ++ptr_;
            return *this;
        }
        Iterator operator++(int)
        {
            Iterator temp(*this);
            ++(*this);
            return temp;
        }
        T operator*()
        {
            return *ptr_;
        }
        bool operator==(const Iterator &rhs)
        {
            return ptr_ == rhs.ptr_;
        }
        bool operator!=(const Iterator &rhs)
        {
            return !(*this == rhs);
        }

        int operator-(const Iterator &rhs)
        {
            return ptr_ - rhs.ptr_;
        }
    };
}


#endif