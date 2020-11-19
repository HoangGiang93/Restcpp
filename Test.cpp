#include "Characteristic.cpp"
#include "Product.cpp"

int main(int, char**)
{
  Characteristics characteristics("http://ked.informatik.uni-bremen.de:8090/k4r-core/api/v0/characteristics/");
  characteristics.import_characteristics();
  std::cout << characteristics.get_characteristics() << std::endl;
  // characteristics.set_characteristic("a new char 123");
  // characteristics.send_characteristic();
  // characteristics.delete_characteristic("205");
  // std::cout << characteristics.get_characteristics() << std::endl;
  // characteristic.set_characteristic("new_char");
  // characteristic.send_characteristic();
  // characteristic.delete_characteristic("204");
  //characteristic.import_characteristic();
  //std::cout << characteristic.get_characteristic() << std::endl;
  return 0;
}