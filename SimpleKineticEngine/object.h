#pragma once
#include "physical_vector.h"

namespace pke {
	template<int dimension>
	class object {
	public:
		object(physical_vector<dimension> position, physical_vector<dimension> mvmtVector, float mass) 
			: position(std::move(position)), mvmtVctr(std::move(mvmtVector)), mass(mass)
		{}
		~object();

		virtual float timeToIntersect(const object&) const;
		virtual physical_vector positionOfIntersect(const object&) const; // pos + mvmt * timeToIntersect(obj);
		virtual physical_vector normalOfIntersect(const object&) const;

		//hit(const physical_vector&) : position, normal, angle, 
		virtual void tick(const physical_vector& sumForce); // updates position and direction
	private:
		physical_vector<dimension> position;
		physical_vector<dimension> mvmtVctr;
		// angular velocity?
		// axis of rotation
		float mass;
	};
}