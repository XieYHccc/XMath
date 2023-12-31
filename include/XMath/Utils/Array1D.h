// Base Container to support 1D array-like object


#pragma once

#include <cassert>

#include <array>

namespace xyh
{
// A wrapper of std::array to support some operators
// Regard this class just as a container without any abstract semantics
template <typename T, size_t N> 
class Array1D
{
public :
	//! returns the dimension of the Array
    static constexpr size_t size() { return N; }

	//! default constructor
	Array1D() = default;
    
    // init all elements to a specific value
    Array1D(T s) { elements_.fill(s); }

	//! constructor with initializer list
    explicit Array1D(const std::initializer_list<T>& elements)
    {
        assert(elements.size() == N);
		std::copy(elements.begin(), elements.end(), elements_.begin());
    }

    //! constructor for 2D array
    explicit Array1D(T x0, T x1)
    {
        static_assert(N == 2, "This constructor is only for 2D array" );
        elements_[0] = x0; elements_[1] = x1;
    }

    //! constructor for 3D array
    explicit Array1D(T x0, T x1, T x2)
    {
        static_assert(N == 3, "This constructor is only for 3D array" );
        elements_[0] = x0; elements_[1] = x1; elements_[2] = x2;
    }

    //! constructor for 4D array
    explicit Array1D(T x0, T x1, T x2, T x3)
    {
        static_assert(N == 4, "This constructor is only for 4D array" );
        elements_[0] = x0; elements_[1] = x1; elements_[2] = x2; elements_[3] = x3;
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

	//! Set all elements to a specified value.
	void fill(T s) { elements_.fill(s); }

    std::array<T, N>::iterator begin() noexcept { return elements_.begin(); }
    std::array<T, N>::const_iterator begin() const noexcept { return elements_.begin(); }
    std::array<T, N>::iterator end() noexcept { return elements_.end(); }
    std::array<T, N>::const_iterator end() const noexcept { return elements_.end(); }
    
    T* data() noexcept { return elements_.data(); }
    const T* data() const noexcept { return elements_.data(); }

protected:
	std::array<T, N> elements_;

};

// output an array by printing its space-separated compontens
template <typename Real, size_t N>
inline std::ostream& operator<<(std::ostream& os, const Array1D<Real, N>& array)
{
    for(size_t i = 0; i < N; ++i)
    {
        os << array[i] << " ";
    }
    return os;
}

}