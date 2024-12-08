#pragma once
#include <memory>
#include <algorithm>
#include <cassert>
#include <string>
#include <iostream>

namespace pke {
	template <int dimension>
	class physical_vector {
		using value_type = physical_vector<dimension>;
		using reference = physical_vector<dimension>&;
		using const_reference = const physical_vector<dimension>&;

	public:
		void display(std::string beforeStr) const {
			std::cout << beforeStr <<  " Vector: (";
			for (size_t i = 0; i < dimension; ++i) {
				std::cout << vals[i];
				if (i < dimension - 1) std::cout << ", ";
			}
			std::cout << ")" << std::endl;
		}

		physical_vector()
			: vals(std::make_unique<float[]>(dimension))
		{}

		physical_vector(std::initializer_list<float> list)
			: vals(std::make_unique<float[]>(dimension))
		{
			auto it = list.begin();
			for (size_t i = 0; i < dimension && it != list.end(); ++i, ++it) {
				vals[i] = *it;
			}
		}

		~physical_vector() {
			vals.reset();
		}
		
		physical_vector(const_reference other)
			: vals(std::make_unique<float[]>(dimension))
		{
			std::copy(other.vals.get(), other.vals.get() + dimension, vals.get());
		}

		reference operator=(const_reference other) {
			value_type tmp(other);
			std::swap(tmp, *this);
			return *this;
		}

		physical_vector(physical_vector<dimension>&& other)
			: vals(other.vals.release())
		{
			other.vals = std::make_unique<float[]>(dimension);
		}

		reference operator=(physical_vector<dimension>&& other) noexcept {
			vals.reset(other.vals.release());
			other.vals = std::make_unique<float[]>(dimension);
			return *this;
		}

		bool operator==(const_reference other) const {
			float epsilon = 0.000001;
			return std::equal(vals.get(), vals.get() + dimension, other.vals.get(), 
				[epsilon](float e1, float e2) {
					return std::abs(e1 - e2) < epsilon;
				});
		}

		bool operator!=(const_reference other) const {
			return !(*this == other);
		}

		value_type operator+(const_reference obj) const {
			value_type new_vec{};
			std::transform(
				vals.get(), vals.get() + dimension,
				obj.vals.get(), new_vec.get(),
				std::plus<float>());
			return new_vec;
		}

		reference operator+=(const_reference obj) {
			std::transform(
				vals.get(), vals.get() + dimension,
				obj.vals.get(), vals.get(),
				std::plus<float>());
			return *this;
		}

		value_type operator-(const_reference obj) const {
			value_type new_vec{};
			std::transform(
				vals.get(), vals.get() + dimension,
				obj.vals.get(), new_vec.get(),
				std::minus<float>());
			return new_vec;
		}

		reference operator-=(const_reference obj) {
			std::transform(
				vals.get(), vals.get() + dimension,
				obj.vals.get(), vals.get(),
				std::minus<float>());
			return *this;
		}

		value_type operator*(float scalar) const {
			value_type new_vec{};
			std::transform(
				vals.get(), vals.get() + dimension,
				new_vec.vals.get(),
				[scalar](float elem) {
					return elem * scalar;
				});
			return new_vec;
		}

		reference operator*=(float scalar) {
			std::transform(
				vals.get(), vals.get() + dimension,
				vals.get(),
				[scalar](float elem) {
					return elem * scalar;
				});
			return *this;
		}
		
		/*
		* cross product. for dot-product try the signature:
		* float dot(const physical_vector&) const
		*/
		value_type operator*(const_reference other) const {
			static_assert(dimension == 3, "the dimension must be 3 to use this operator.");
			if (dimension == 3) {
				float i = vals[1] * other.vals[2] - vals[2] * other.vals[1];
				float j = -(vals[0] * other.vals[2] - vals[2] * other.vals[0]);
				float k = vals[0] * other.vals[1] - vals[1] * other.vals[0];
				return value_type{i, j, k};
			}
			else {
				throw new std::exception("operator*(const_reference other) is not defined for dimensions other then 3 at the moment.");
			}
		}

		/*
		* cross product. for dot-product try the signature:
		* float dot(const physical_vector&) const
		*/
		/*reference operator*=(reference) {

		}*/

		float operator[](size_t index) const {
			if (!vals) throw new std::exception("nullptr exection in subscript opertor");
			return vals[index];
		}

		float* get() const {
			return vals.get();
		}

		float get(int index) const {
			if(index >= dimension) throw new std::exception("index out of range");
			return vals[index];
		}

		reference operator->() {
			return *this;
		}

		const_reference operator->() const {
			return *this;
		}

		float dot(const_reference other) const {
			static_assert(dimension == 3, "the dimension must be 3 to use dot-product.");
			
			return vals[0] * other.vals[0] +
				vals[1] * other.vals[1] +
				vals[2] * other.vals[2];
		}

		/* 
		* calls operator*
		*/
		value_type cross(const_reference other) const {
			static_assert(dimension == 3, "the dimension must be 3 to use cross-product.");
			return *this * other;
		}

		float magnitude() {
			return std::sqrt(dot(*this));
		}

		reference normalize() {
			return (*this *= (1 / magnitude()));
		}

		template<int x>
		friend physical_vector<x> operator*(float scalar, const physical_vector<x>& obj);

	private:
		std::unique_ptr<float[]> vals;
	};

	template<int x>
	physical_vector<x> operator*(float scalar, const physical_vector<x>& vec) {
		return vec * scalar;
	}

}
