#include "Entity.cpp"

class Product : public Entity
{
private:
  std::string product_id;

public:
  Product(const char*);
  bool import_product(const std::string &);
  void set_product_id(const std::string &);
  Json::Value get_product();
  bool set_product(const Json::Value &);
  bool send_product();
  bool delete_product();
};

Product::Product(const char* link) : Entity::Entity(link)
{
  this->entity["depth"] = 0;
  this->entity["description"] = "string";
  this->entity["gtin"] = "string";
  this->entity["height"] = 0;
  this->entity["length"] = 0;
  this->entity["name"] = "string";
  this->entity["weight"] = 0;
}

bool Product::import_product(const std::string &product_id)
{
  this->set_product_id(product_id);
  return this->import_entity();
}

void Product::set_product_id(const std::string &product_id)
{
  this->product_id = product_id;
}

Json::Value Product::get_product()
{
  return this->get_entity();
}

bool Product::set_product(const Json::Value &product)
{
  if(this->entity["depth"].empty() ||
  this->entity["description"].empty() ||
  this->entity["gtin"].empty() ||
  this->entity["height"].empty() ||
  this->entity["length"].empty() ||
  this->entity["name"].empty() ||
  this->entity["weight"].empty())
  {
    return this->set_entity(product);
  }
  else
  {
    return false;
  }
}

bool Product::send_product()
{
  return this->send_entity((std::string(this->link) + this->product_id).c_str());
}

bool Product::delete_product()
{
  return this->delete_entity((std::string(this->link) + this->product_id).c_str());
}

// class Products : public Entity
// {
// public:
//   Products(const char*);
//   bool set_products(const Json::Value &);
//   bool delete_product(const std::string &);
// };

// Products::Products(const char* link) : Entity::Entity(link)
// {
//   this->entity["depth"] = 0;
//   this->entity["description"] = "string";
//   this->entity["gtin"] = "string";
//   this->entity["height"] = 0;
//   this->entity["id"] = "string";
//   this->entity["length"] = 0;
//   this->entity["name"] = "string";
//   this->entity["weight"] = 0;
// }

// bool Product::set_product(const Json::Value &product)
// {
//   return this->set_entity(product);
// }

// bool Product::delete_product(const std::string &product_id)
// {
//   return this->delete_entity((this->link + product_id).c_str());
// }