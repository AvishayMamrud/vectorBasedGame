#include "pch.h"
#include "physical_vector.h"

TEST(createAndGet, vector) {
  pke::physical_vector<3> v1{ 1,2,3 };
  float* vals = v1.get();
  EXPECT_EQ(vals[0], 1);
  EXPECT_EQ(vals[1], 2);
  EXPECT_EQ(vals[2], 3);
  EXPECT_EQ(v1.get(0), 1);
  EXPECT_EQ(v1.get(1), 2);
  EXPECT_EQ(v1.get(2), 3);
  EXPECT_ANY_THROW(v1.get(3));
}


TEST(eq_noq_op, vector) {
	pke::physical_vector<3> v1{ 1,2,3 };
	pke::physical_vector<3> v2{ 1,2,3 };
	pke::physical_vector<3> v3{ 0,2,3 };
	EXPECT_EQ(v1[0], 1);
	EXPECT_EQ(v1[1], 2);
	EXPECT_EQ(v1[2], 3);

	EXPECT_EQ(v1, v2);
	//EXPECT_NE(v3, v2);
	EXPECT_TRUE(v1 == v2);
	EXPECT_FALSE(v1 == v3);
	EXPECT_FALSE(v1 != v2);
	EXPECT_TRUE(v1 != v3);
}

TEST(copyAndMove, vector) {
	pke::physical_vector<3> v1{ 1,2,3 };
	pke::physical_vector<3> v2(v1);
	// v2 is {1,2,3}
	EXPECT_EQ(v2, v1);

	pke::physical_vector<3> v3{ 4,5,6 };
	v3 = v1;
	// v3 is {1,2,3}
	EXPECT_EQ(v3, v1);

	pke::physical_vector<3> v5(pke::physical_vector<3>{7,8,9});
	// v5 is {7,8,9}
	EXPECT_EQ(v5[0], 7);
	EXPECT_EQ(v5[1], 8);
	EXPECT_EQ(v5[2], 9);

	v1 = std::move(v5);
	// v5 empty
	EXPECT_EQ(v5[0], 0);
	EXPECT_EQ(v5[1], 0);
	EXPECT_EQ(v5[2], 0);

	// v1 is {7,8,9}
	EXPECT_EQ(v1[0], 7);
	EXPECT_EQ(v1[1], 8);
	EXPECT_EQ(v1[2], 9);

	// v3 is still {1,2,3}
	EXPECT_EQ(v3[0], 1);
	EXPECT_EQ(v3[1], 2);
	EXPECT_EQ(v3[2], 3);
}

TEST(plusAndMinus, vector) {
	pke::physical_vector<3> v1{ 1,2,3 };
	pke::physical_vector<3> v2{ 4,-5,6 };
	pke::physical_vector<3> v3{ 0,2,-3 };

	pke::physical_vector<3> v4_a{ 5,-3,9 };
	auto v4_b = v1 + v2;
	EXPECT_EQ(v4_a, v4_b);

	v2 = v1 += v2;
	EXPECT_EQ(v1, v4_a);
	EXPECT_EQ(v2, v4_a);

	pke::physical_vector<3> v5_a = {5,-5,12};
	auto v5_b = v1 - v3;
	EXPECT_EQ(v5_a, v5_b);

	v3 = v1 -= v3;
	EXPECT_EQ(v1, v5_a);
	EXPECT_EQ(v3, v5_a);
}

TEST(multiplyAndMagnitudeAndNormalize, vector) {
	pke::physical_vector<3> v1{ 2,8,-3 };
	pke::physical_vector<3> v2 = v1;
	pke::physical_vector<3> v3{ 5,20,-7.5f };
	EXPECT_EQ(v1 * 2.5f, v3);

	float magnitude = v1.magnitude();

	EXPECT_EQ(v1.normalize().magnitude(), 1);
	v1 *= magnitude;
	EXPECT_TRUE(v1 == v2);
}

TEST(dotAndCrossProduct, vector) {
	pke::physical_vector<3> v1{ 1,0,0 };
	pke::physical_vector<3> v2{ 0,1,0 };
	pke::physical_vector<3> v3{ 0,0,1 };

	EXPECT_EQ(v1.dot(v2), 0);
	EXPECT_EQ(v2.dot(v1), 0);
	EXPECT_NE(v1.dot(v1), 0);

	pke::physical_vector<3> v4 = v1 * v2;

	v4.display("v4");

	v4.normalize();

	v4.display("v4 normalized");

	EXPECT_EQ(v4, v3);
}