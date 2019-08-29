#include "pch.h"


TEST(Expected4When4, NumberOfFacesTest) {
  STL_Importer test;
  test.Import("../../../src/Tests/STL_Importer_Tests/TestTxtFiles/Expect4Test.txt");
  int expected = 4;
  EXPECT_EQ(expected, test.GetFaces().size());
}

TEST(ExpectedArrayOfThreeFloatsInFirstFace, ThreeFloatsTest) {
  STL_Importer test;
  test.Import("../../../src/Tests/STL_Importer_Tests/TestTxtFiles/Expect4Test.txt");
  std::array<int, 3> expected = { 0, 1, 2 };
  EXPECT_EQ(expected, test.GetFaces()[0].m_triangle);
}


TEST(ExpectedTrue, HasNormalTrueTest) {
  STL_Importer test;
  test.Import("../../../src/Tests/STL_Importer_Tests/TestTxtFiles/ExpectHasNormalTrueTest.txt");
  bool expected = true;
  EXPECT_EQ(expected, test.GetFaces()[0].m_has_normal);
}

TEST(ExpectedFalse, HasNormalFalseTest) {
  STL_Importer test;
  test.Import("../../../src/Tests/STL_Importer_Tests/TestTxtFiles/ExpectHasNormalFalseTest.txt");
  bool expected = false;
  EXPECT_EQ(expected, test.GetFaces()[0].m_has_normal);
}

TEST(ExpectedThrow, SolidFailTest) {
  STL_Importer test;
  EXPECT_ANY_THROW(test.Import("../../../src/Tests/STL_Importer_Tests/TestTxtFiles/ExpectSolidFailTest.txt"));
}

TEST(ExpectedThrow, FacetFailTest) {
  STL_Importer test;
  EXPECT_ANY_THROW(test.Import("../../../src/Tests/STL_Importer_Tests/TestTxtFiles/ExpectFacetFailTest.txt"));
}

TEST(ExpectedThrow, OuterLoopFailTest) {
  STL_Importer test;
  EXPECT_ANY_THROW(test.Import("../../../src/Tests/STL_Importer_Tests/TestTxtFiles/ExpectOuterLoopFailTest.txt"));
}

TEST(ExpectedThrow, VertexFailTest) {
  STL_Importer test;
  EXPECT_ANY_THROW(test.Import("../STL_Importer_Tests/TestTxtFiles/ExpectVertexFailTest.txt"));
}

TEST(ExpectedThrow, EndLoopFailTest) {
  STL_Importer test;
  EXPECT_ANY_THROW(test.Import("../../../src/Tests/STL_Importer_Tests/TestTxtFiles/ExpectEndLoopFailTest.txt"));
}

TEST(ExpectedThrow, EndFacetFailTest) {
  STL_Importer test;
  EXPECT_ANY_THROW(test.Import("../STL_Importer_Tests/TestTxtFiles/ExpectEndFacetFailTest.txt"));
}

TEST(ExpectedThrow, EndSolidFailTest) {
  STL_Importer test;
  EXPECT_ANY_THROW(test.Import("../Tests/STL_Importer_Tests/TestTxtFiles/ExpectEndSolidFailTest.txt"));
}

