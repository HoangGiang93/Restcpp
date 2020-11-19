#include "Entities/Customer.cpp"
#include "Entities/Characteristic.cpp"
#include "Entities/Product.cpp"
#include "Entities/Property.cpp"
#include "Entities/Shelf.cpp"
#include "Entities/ShelfLayer.cpp"
#include "Entities/Store.cpp"

#define A1_1
#define A1_2
#define A1_3
#define A1_4

int main(int, char**)
{
  // Example 1: Customer
  // 0. Make customers 
  Customers customers("http://ked.informatik.uni-bremen.de:8090/k4r-core/api/v0/"); // customers is ready, but it has nothing in it
  std::cout << "\nEmpty customers: " << customers.get_customers() << std::endl;

#ifdef A1_1
  // 1. Get all customers (in Json, string and const char*)
  std::cout << "------------------------------" << std::endl;
  customers.import_customers(); // Import all Customers
  std::cout << "\nCustomers in json:" << std::endl;
  std::cout << customers.get_customers() << std::endl;                                    // Return all customers in json

  std::cout << "\nCustomers in string:" << std::endl;
  std::cout << customers.get_customers().toStyledString() << std::endl;                   // Return all customers in string

  std::cout << "\nCustomers in const char*:" << std::endl;
  std::string customers_string = customers.get_customers().toStyledString();
  std::cout << customers_string.c_str() << std::endl;                                     // Return customers in const char* (for Predicate variable)
#endif

#ifdef A1_2
  // 2. Send a customer (name Giang for example)
  std::cout << "------------------------------" << std::endl;
  customers.set_customer("Giang");
  customers.send_customer();                              // Customer Giang is sent
  customers.import_customers();                           // Import all Customers again to see that
  std::cout << customers.get_customers() << std::endl;    // You see?
#endif

#ifdef A1_3
  // 3. Get a customer with the id
  std::cout << "------------------------------" << std::endl;
  // First we search for my id
  std::string giang_id;
  for (const auto customer : customers.get_customers())
  {
    if (customer["anonymisedName"].asString() == "Giang")
    {
      giang_id = customer["id"].asString();
      std::cout << "\nFound giang id: " << giang_id << std::endl;
      break; // In case we find more...
    }
  }
  // Then we can query for this id to check
  customers.import_customer(giang_id);  // Import first, otherwise we dont have that information
  std::cout << "\nCustomer Giang in json:" << std::endl;
  std::cout << customers.get_customer() << std::endl;
#endif

#ifdef A1_4
  // 4. Delete a customer with id
  std::cout << "------------------------------" << std::endl;
  customers.delete_customer(giang_id);  // Delete customer with giang_id
  customers.import_customers();         // Import again
  std::cout << "\nCustomers without giang" << std::endl;
  std::cout << customers.get_customers() << std::endl;
#endif
}