#ifndef ITERATOR_H
#define ITERATOR_H
#include <iterator>

template<typename T, typename pred_t>
class segment_tree;

namespace seg_tree{
    template<typename T, typename pred_t>
    class iterator: public std::iterator<std::bidirectional_iterator_tag, T>
    {
        private:
        const segment_tree<T, pred_t> *tree_;
	    int index_;

        public:
        iterator(const segment_tree<T, pred_t> &tree_, int index):tree_(&tree_), index_(index)
        { }

		iterator(const iterator& rhs):tree_(rhs.tree_), index_(rhs.index_)
		{ }
		iterator& operator=(const iterator& rhs)
		{
			tree_ = rhs.tree_;
			index_ = rhs.index_;
			return *this;
		}
        iterator& operator++()
        {
            ++index_;
            return *this;
        }
        iterator operator++(int)
        {
            iterator temp(*this);
            ++(*this);
            return temp;
        }
		iterator& operator--()
        {
            --index_;
            return *this;
        }
        iterator operator--(int)
        {
            iterator temp(*this);
            --(*this);
            return temp;
        }
        T operator*()
        {
            return tree_->get(index_);
        }
        bool operator==(const iterator &rhs)
        {
            return index_ == rhs.index_;
        }
        bool operator!=(const iterator &rhs)
        {
            return !(*this == rhs);
        }
		int get_index()
		{
			return index_;
		}
        int operator-(const iterator &rhs)
        {
            return index_ - rhs.index_;
        }
        int operator+(const iterator &rhs)
        {
            return index_ + rhs.index_;
        }
    };
}

#endif