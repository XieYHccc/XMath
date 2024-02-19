// Base Container to support 2D array-like object
#pragma once

#include <cassert>
#include <cstddef>

#include <array>
#include <iostream>

namespace xyh::XMath {

template<typename T, size_t NumRows, size_t NumCols>
class Array2D
{
public:
    // returns number of rows of the 2D Array
    static constexpr int num_rows() { return NumRows; }
    // returns number of columns of the 2D Array
    static constexpr int num_cols() { return NumCols; }
    // returns the size of the 2D Array as 1D array
    static constexpr int size() { return NumRows * NumCols; }

    Array2D() = default;

    //! constructor with a list of columns
    explicit Array2D(const std::initializer_list<std::initializer_list<T>>& columns) {
        assert(columns.size() == NumCols);
        size_t offset = 0;
        for (const auto& col : columns ) {
            assert(col.size() == NumRows);
            std::copy(col.begin(), col.end(), elements_.begin() + offset);
            offset += NumCols;
        }
    }

    void fill(T s) { elements_.fill(s); }

    // container access
	const T& operator[](size_t i) const {
		assert(i < NumRows * NumCols);
		return elements_[i];
	}
    const T& operator()(size_t row, size_t col) const {
        assert(row < NumRows&& col < NumCols);
        return elements_[get_index(row, col)];
    }
    T& operator[](size_t i) { return const_cast<T&>(static_cast<const Array2D<T, NumRows, NumCols>&>(*this)[i]); }
    T& operator()(size_t row, size_t col) { return const_cast<T&>(static_cast<const Array2D<T, NumRows, NumCols>&>(*this)(row, col)); }
    const T& at(size_t row, size_t col) const { return elements_.at(get_index(row, col)); }
    T& at(size_t row, size_t col) { return elements_.at(get_index(row, col)); }

    const T* data() const noexcept { return elements_.data(); }
    T* data() noexcept { return elements_.data();}

protected:
    // return the index in 1D array by row index and col index
    size_t get_index(size_t row, size_t col) const noexcept { return NumRows * col + row; }
protected:
    std::array<T, NumRows * NumCols> elements_;
};

//! output a 2D Array
template<typename T, size_t NumRows, size_t NumCols>
inline std::ostream& operator<<(std::ostream& os, const Array2D<T, NumRows, NumCols>& array) {
    for (size_t i = 0; i < NumRows; ++i) {
        for (size_t j = 0; j < NumCols; ++j) {
            os << array(i, j) << " ";
        }
        os << "\n";
    }
    return os;
}

}