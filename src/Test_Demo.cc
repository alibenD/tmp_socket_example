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
#include <iostream>

//CODE
namespace Demo
{
  int Obj::func_return1(){ return 1; }
  int Obj::func_return2(){ return 2; }
  int Obj::getValue() const { return value_; }
  void Obj::setValue(int value) { value_ = value; }

  double func_return10() { return 10.0; }
  double func_return20() { return 20.0; }
}
