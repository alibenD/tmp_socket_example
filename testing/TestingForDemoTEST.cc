/**-----------------------------------------------
  * @Copyright (C) All rights reserved.
  * @filename: Socket
  * @author: aliben.develop@gmail.com
  * @created_date: 2019-08-26 18:27:45
  * @last_modified_date: NO_LAST_MODIFIED_DATE
  * @description: TODO
  *-----------------------------------------------*/

//INCLUDE
#include <Socket/Test_Demo.hh>
#include <gtest/gtest.h>

//CODE

using namespace Demo;

TEST(DemoFuncTest, return10)
{
  EXPECT_EQ(10.0, func_return10());
};

TEST(DemoFuncTest, return20)
{
  EXPECT_EQ(20.0, func_return20());
};

int main(int argc, char** argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
