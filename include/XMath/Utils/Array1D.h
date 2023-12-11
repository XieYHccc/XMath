// base container class for point and vector


#pragma once

#include <cassert>

#include <array>

namespace xyh
{
// A wrapper of std::array to support some operators
// Regard this class just as a container without any abstract semantics
template <typename T, size_t N> 
class Array 
{
public :

	//! returns the dimension of the Array
    static constexpr size_t size() { return N; }

	//! default constructor
	Array() = default;
    
    // init all elements to a specific value
    Array(T s) { elements_.fill(s); }

	//! constructor with initializer list
    explicit Array(const std::initializer_list<T>& elements)
    {
        assert(elements.size() == N);
		std::copy(elements.begin(), elements.end(), elements_.begin());
    }

    //! constructor for 2D array
    explicit Array(T x0, T x1)
    {
        static_assert(N == 2, "This constructor is only for 2D array" );
        elements_[0] = x0; elements_[1] = x1;
    }

    //! constructor for 3D array
    explicit Array(T x0, T x1, T x2)
    {
        static_assert(N == 3, "This constructor is only for 3D array" );
        elements_[0] = x0; elements_[1] = x1; elements_[2] = x2;
    }

	// Container access
	T& operator[](size_t i) 
	{
		assert(i < N);
		return elements_[i];
	}

	const T& operator[](size_t i) const 
	{
		assert(i < N);
		return elements_[i];
	}

    T& at(size_t i)
    {
        assert(i < N);
        return elements_[i];
    }

    const T& at(size_t i) const
    {
        assert(i < N);
        return elements_[i];
    }

	//! Set all elements to the specified value.
	void fill(T s)
	{
		elements_.fill(s);
	}

    const T* data() const noexcept
    {
        return elements_.data();
    }

    T* data()
    {
        return elements_.data();
    }

private:
	std::array<T, N> elements_;

};

// output an array by printing its space-separated compontens
template <typename Real, size_t N>
inline std::ostream& operator<<(std::ostream& os, const Array<Real, N>& v)
{
    for(size_t i = 0; i < N; ++i)
    {
        os << v[i] << " ";
    }
    return os;
}

}