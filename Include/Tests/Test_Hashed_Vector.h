#pragma once
#include <iostream>
#include <cassert>
#include <stdexcept>
#include <vector>
#include "Tools/HashedVector.hpp"

// Test function to check if the given condition is true
void test(bool condition, int testNumber)
{
	std::cout << "Test " << testNumber << ": " << (condition ? "Pass" : "Fail") << std::endl;
}

// Test function to check the functionality of HashedVector
void testHashedVector()
{
	HashedVector<int> hashedVector;

	// Test 1: Verify if push_back adds the item to the vector and returns a valid ID
	int id1 = hashedVector.push_back(10);
	test(id1 == 0, 1);

	// Test 2: Verify if the item can be accessed using the ID operator[]
	int& item1 = hashedVector[id1];
	test(item1 == 10, 2);

	// Test 3: Verify if try_get returns a valid pointer to the item
	auto pItem1 = hashedVector.try_get(id1);
	test(pItem1 != nullptr && *pItem1 == 10, 3);

	// Test 4: Verify if remove marks the item as deleted
	hashedVector.remove(id1);
	test(hashedVector.try_get(id1) == nullptr, 4);

	// Test 5: Verify if cullDeleted removes the deleted items from the vector
	//hashedVector.CullDeleted();
	test(hashedVector.size() == 0, 5);

	// Test 6: Verify if push_back adds new items after removal
	int id2 = hashedVector.push_back(20);
	test(id2 == 1, 6);

	// Test 7: Verify if the new item can be accessed correctly
	int& item2 = hashedVector[id2];
	test(item2 == 20, 7);

	// Test 8: Verify if the underlying vector is correct
	const std::vector<int>& vector = hashedVector.getVector();
	test(vector.size() == 1 && vector[0] == 20, 8);

	// Test 9: Verify if IDs and corresponding data are preserved after culling and rehashing
	//hashedVector.CullDeleted();
	int id3 = hashedVector.push_back(30);
	int id4 = hashedVector.push_back(40);
	hashedVector.remove(id3);
	hashedVector.remove(id4);
	//hashedVector.CullDeleted();
	test(hashedVector.size() == 1, 9);
	test(hashedVector.try_get(id2) != nullptr && *hashedVector.try_get(id2) == 20, 9);
	test(hashedVector.try_get(id3) == nullptr, 9);
	test(hashedVector.try_get(id4) == nullptr, 9);

	// Test 10: Verify if IDs and corresponding data are preserved after rehashing
	hashedVector.reserve(1000);
	test(hashedVector.try_get(id2) != nullptr && *hashedVector.try_get(id2) == 20, 10);
	test(hashedVector.try_get(id3) == nullptr, 10);
	test(hashedVector.try_get(id4) == nullptr, 10);

	// Test 12: Verify if emplace_back constructs new items with different arguments
	struct test_struct {
		int a;
		float b;
		std::string c;
	};
	HashedVector<test_struct> hv2;
	int id5 = hv2.emplace_back(50, 5.0, "five");
	int id6 = hv2.emplace_back(60, 6.0, "six");
	test_struct t{ 50,5.0,"five" };
	test(hv2.size() == 2, 12);
	test(hv2.try_get(id5) != nullptr && *(int*)hv2.try_get(id5) == 50, 12);
	test(hv2.try_get(id6) != nullptr && *(int*)hv2.try_get(id6) == 60, 13);

}

void testHashedVector2()
{
	HashedVector<int> hashedVector;

	// Test 1: Verify if push_back adds the item to the vector and returns a valid ID
	int id1 = hashedVector.push_back(10);
	test(id1 == 0, 1);

	// Test 2: Verify if the item can be accessed using the ID operator[]
	int& item1 = hashedVector[id1];
	test(item1 == 10, 2);

	// Test 3: Verify if try_get returns a valid pointer to the item
	auto pItem1 = hashedVector.try_get(id1);
	test(pItem1 != nullptr && *pItem1 == 10, 3);

	// Test 4: Verify if remove marks the item as deleted
	hashedVector.remove(id1);
	test(hashedVector.try_get(id1) == nullptr, 4);

	// Test 5: Verify if cullDeleted removes the deleted items from the vector
	//hashedVector.CullDeleted();
	test(hashedVector.size() == 0, 5);

	// Test 6: Verify if push_back adds new items after removal
	int id2 = hashedVector.push_back(20);
	test(id2 == 1, 6);

	// Test 7: Verify if the new item can be accessed correctly
	int& item2 = hashedVector[id2];
	test(item2 == 20, 7);

	// Test 8: Verify if the underlying vector is correct
	const std::vector<int>& vector = hashedVector.getVector();
	test(vector.size() == 1 && vector[0] == 20, 8);

	// Test 9: Verify if IDs and corresponding data are preserved after culling and rehashing
	//hashedVector.CullDeleted();
	int id3 = hashedVector.push_back(30);
	int id4 = hashedVector.push_back(40);
	hashedVector.remove(id3);
	hashedVector.remove(id4);
	//hashedVector.CullDeleted();
	test(hashedVector.size() == 1, 9);

	test(hashedVector.try_get(id2) != nullptr && *hashedVector.try_get(id2) == 20, 9);
	std::cout << *hashedVector.try_get(id2);

	test(hashedVector.try_get(id3) == nullptr, 9);
	test(hashedVector.try_get(id4) == nullptr, 9);

	// Test 10: Verify if IDs and corresponding data are preserved after rehashing
	hashedVector.reserve(1000);
	test(hashedVector.try_get(id2) != nullptr && *hashedVector.try_get(id2) == 20, 10);
	test(hashedVector.try_get(id3) == nullptr, 10);
	test(hashedVector.try_get(id4) == nullptr, 10);

	// Test 11: Verify constness of vector reference
	const std::vector<int>& constVector = hashedVector.getVector();
	test(constVector.size() == hashedVector.size(), 11);

	// Attempt to modify the underlying vector
	//constVector.push_back(30);  // This should result in a compilation error

	// Ensure the underlying vector is still unmodified
	test(hashedVector.size() == 1 && hashedVector.try_get(id2) != nullptr && *hashedVector.try_get(id2) == 20, 11);

	//Test 12: Try using emplace_back with parameters
	struct TestStruct
	{
		int a;
		float b;
		TestStruct(int a, float b) : a(a), b(b) {}
	};
	HashedVector<TestStruct> hashedVector2;
	int id5 = hashedVector2.emplace_back(10, 20.0f);
	test(id5 == 0, 12);
	TestStruct& item5 = hashedVector2[id5];
	test(item5.a == 10 && item5.b == 20.0f, 12);


}

