#pragma once
#include "object.h"
#include <unordered_set>

namespace pke {
	template<int dimension>
	class containerObject : public object<dimension> {
	public:
		containedObjects(physical_vector<dimension>, physical_vector<dimension>)

		virtual float timeToIntersect(const object&) const;
		virtual physical_vector positionOfIntersect(const object&) const; // pos + mvmt * timeToIntersect(obj);
		virtual physical_vector normalOfIntersect(const object&) const;
		virtual void tick(const physical_vector& sumForce); // updates position and direction

		bool addObject(object obj) {
			return containedObjects.insert(std::move(obj)).second;
		}
	private:
		physical_vector<dimension> dimensions;
		std::unordered_set<object<dimension>> containedObjects;
	};
}