#include "physical_vector.h"
#include <iostream>
#include <string>

using namespace pke;
int main() {
	physical_vector<3> v1{ 1,0,0 };
	physical_vector<3> v2{ 0,1,0 };
	physical_vector<3> v3{ 0,0,1 };

	v1.display(std::string("v1"));
	v2.display(std::string("v2"));
	v3.display(std::string("v3"));

	physical_vector<3> v4 = v1 * v2;

	v4.display("v4");

	float v1_v4 = v1.dot(v4);
	float v2_v4 = v2.dot(v4);
	float v4_v1 = v4.dot(v1);
	float v4_v2 = v4.dot(v2);

	// std::cout << "should all be zeros: " << v1_v4 << "," << v2_v4 << "," << v4_v1 << "," << v4_v2 << "," << std::end;
	std::cout << "should all be zeros: " << v1_v4 << "," << v2_v4 << "," << v4_v1 << "," << v4_v2 << std::endl;

	v3 = v4 * v1;

	v3.display("v3 = v4 * v1 ->");
	v3 *= 3;
	v3.display("v3 *= 3 ->");

	std::cout << "v3.get(3): " << v3.get(3) << std::endl;

	std::cout << "v3 == v2 * 3 -> " << (v3 == v2 * 3) << std::endl;
	float efi = 3.;
	physical_vector<3> xy = (efi * v2);
	xy.display("v3 == 3 * v2 -> ");


	system("pause");

	return 0;
}