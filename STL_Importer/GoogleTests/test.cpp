#include "pch.h"

TEST(Expected4When4, NumberTest1) {
	STL_Importer test;
	std::vector<STL_Importer::Face> test_vector;
	test.Import("TestTxtFiles/Expect4Test.txt", test_vector);
	int expected = 4;
	EXPECT_EQ(expected, test_vector.size());
}

TEST(ExpectedTrue, HasNormalTrueTest) {
	STL_Importer test;
	std::vector<STL_Importer::Face> test_vector;
	test.Import("TestTxtFiles/ExpectHasNormalTrueTest.txt", test_vector);
	bool expected = true;
	EXPECT_EQ(expected, test_vector[0].m_hasNormal);
}

TEST(ExpectedTrue, HasNormalFalseTest) {
	STL_Importer test;
	std::vector<STL_Importer::Face> test_vector;
	test.Import("TestTxtFiles/ExpectHasNormalFalseTest.txt", test_vector);
	bool expected = false;
	EXPECT_EQ(expected, test_vector[0].m_hasNormal);
}

TEST(ExpectedThrow, SolidFailTest) {
	STL_Importer test;
	std::vector<STL_Importer::Face> test_vector;
	EXPECT_ANY_THROW(test.Import("TestTxtFiles/ExpectSolidFailTest.txt", test_vector));
}

TEST(ExpectedThrow, FacetFailTest) {
	STL_Importer test;
	std::vector<STL_Importer::Face> test_vector;
	EXPECT_ANY_THROW(test.Import("TestTxtFiles/ExpectFacetFailTest.txt", test_vector));
}

TEST(ExpectedThrow, OuterLoopFailTest) {
	STL_Importer test;
	std::vector<STL_Importer::Face> test_vector;
	EXPECT_ANY_THROW(test.Import("TestTxtFiles/ExpectOuterLoopFailTest.txt", test_vector));
}

TEST(ExpectedThrow, VertexFailTest) {
	STL_Importer test;
	std::vector<STL_Importer::Face> test_vector;
	EXPECT_ANY_THROW(test.Import("TestTxtFiles/ExpectVertexFailTest.txt", test_vector));
}

TEST(ExpectedThrow, EndLoopFailTest) {
	STL_Importer test;
	std::vector<STL_Importer::Face> test_vector;
	EXPECT_ANY_THROW(test.Import("TestTxtFiles/ExpectEndLoopFailTest.txt", test_vector));
}

TEST(ExpectedThrow, EndFacetFailTest) {
	STL_Importer test;
	std::vector<STL_Importer::Face> test_vector;
	EXPECT_ANY_THROW(test.Import("TestTxtFiles/ExpectEndFacetFailTest.txt", test_vector));
}

TEST(ExpectedThrow, EndSolidFailTest) {
	STL_Importer test;
	std::vector<STL_Importer::Face> test_vector;
	EXPECT_ANY_THROW(test.Import("TestTxtFiles/ExpectEndSolidFailTest.txt", test_vector));
}

