#pragma once

#include "Entity.cpp"

class Product : public Entity
{
public:
  Product(const char*);
  bool import_product(const std::string &);
  Json::Value get_product() const;
  bool set_product(const Json::Value &);
  bool send_product(const std::string &);
  bool delete_product(const std::string &);
};

Product::Product(const char* link) : Entity::Entity((std::string(link) + "products/").c_str())
{
}

bool Product::import_product(const std::string &product_id)
{
  if(product_id.empty())
  {
    std::cout << "Product id not found" << std::endl;
    return false;
  }
  else
  {
    return this->import_entity((this->link + product_id).c_str());
  }
}

Json::Value Product::get_product() const
{
  return this->get_entity();
}

bool Product::set_product(const Json::Value &product)
{
  if (product["depth"].isNumeric() &&
      product["description"].isString() &&
      product["gtin"].isString() &&
      product["height"].isNumeric() &&
      product["length"].isNumeric() &&
      product["name"].isString() &&
      product["weight"].isNumeric())
  {
    return this->set_entity(product);
  }
  else
  {
    std::cout << "Invalid product" << std::endl;
    return false;
  }
}

bool Product::send_product(const std::string &product_id)
{
  return this->send_entity((this->link + product_id).c_str());
}

bool Product::delete_product(const std::string& product_id)
{
  return this->delete_entity((this->link + product_id).c_str());
}

class Products : public Entity
{
private:
  Product* product;
public:
  Products(const char*);
  bool import_products();
  bool set_products(const Json::Value &);
  bool send_products();
  Json::Value get_products() const;

  bool import_product(const std::string &);
  Json::Value get_product() const;
  bool set_product(const Json::Value &);
  bool send_product(const std::string &);
  bool delete_product(const std::string &);
};

Products::Products(const char* link) : Entity::Entity((std::string(link) + "products/").c_str())
{
  this->product = new Product(link);
}

bool Products::import_products()
{
  return this->import_entity();
}

bool Products::set_products(const Json::Value &products)
{
  if (!this->entity["products"].isNull())
  {
    return this->set_entity(products);
  }
  else
  {
    std::cout << "Invalid products" << std::endl;
    return false;
  }
}

bool Products::send_products()
{
  return this->send_entity((this->link + "list").c_str());
}

Json::Value Products::get_products() const
{
  return this->get_entity();
}

bool Products::import_product(const std::string &product_id)
{
  return this->product->import_product(product_id);
}

Json::Value Products::get_product() const
{
  return this->product->get_product();
}

bool Products::set_product(const Json::Value &product)
{
  return this->product->set_product(product);
}

bool Products::send_product(const std::string &product_id)
{
  return this->product->send_product(product_id);
}

bool Products::delete_product(const std::string &product_id)
{
  return this->product->delete_product(product_id);
}
