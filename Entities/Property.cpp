#pragma once

#include "Store.cpp"
#include "Product.cpp"
#include "Characteristic.cpp"

class Property : public Entity
{
private:
  Stores* stores;
  Products* products;
  Characteristics* characteristics;

  std::string store_id;
  std::string product_id;
  std::string characteristic_id;

public:
  Property(const char*);

  std::string get_store_id() const { return this->store_id; };
  std::string get_product_id() const { return this->product_id; };
  std::string get_characteristic_id() const { return this->characteristic_id; };
  bool set_store(const std::string&);
  bool set_product(const std::string&);
  bool set_characteristic(const std::string&);

  Json::Value get_property() const;
  bool set_property(const std::string&, const std::string&, const std::string&, const std::string&);
  bool set_property(const std::string&);
  bool send_property();
  bool delete_property(const std::string&);
};

Property::Property(const char* link) : Entity::Entity(link)
{
  this->stores = new Stores(link);
  this->products = new Products(link);
  this->characteristics = new Characteristics(link);
}

Json::Value Property::get_property() const
{
  if(!store_id.empty())
  {
    std::cout << "Store id is empty" << std::endl;
  }
  else if (!product_id.empty())
  {
    std::cout << "Product id is empty" << std::endl;
  }
  else if (!characteristic_id.empty())
  {
    std::cout << "Characteristic id is empty" << std::endl;
  }
  return this->get_entity();
}

bool Property::set_store(const std::string& store_id)
{
  if (this->stores->import_store(store_id))
  {
    this->store_id = this->stores->get_store()["id"].asString();
    return true;
  }
  else
  {
    std::cout << "Store id not found" << std::endl;
    return false;
  }
}

bool Property::set_product(const std::string& product_id)
{
  if (this->products->import_product(product_id))
  {
    this->product_id = this->products->get_product()["id"].asString();
    return true;
  }
  else
  {
    std::cout << "Product id not found" << std::endl;
    return false;
  }
}

bool Property::set_characteristic(const std::string& characteristic_id)
{
  if (this->characteristics->import_characteristics())
  {
    for(const Json::Value& characteristic : this->characteristics->get_characteristics())
    {
      if (characteristic["id"].asString() == characteristic_id)
      {
        this->characteristic_id = characteristic["id"].asString();
        return true;
      }
    }
    std::cout << "Characteristic id not found" << std::endl;
    return false;
  }
  else
  {
    std::cout << "Characteristics not found" << std::endl;
    return false;
  }
}

bool Property::set_property(const std::string& value)
{
  this->entity.empty();
  this->entity["characteristicId"] = this->characteristic_id;
  this->entity["productId"] = this->product_id;
  this->entity["storeId"] = this->store_id;
  this->entity["value"] = value;
  return true;
}

bool Property::set_property(const std::string& characteristic_id, const std::string& product_id, const std::string& store_id, const std::string& value)
{
  return this->set_store(store_id) && 
  this->set_product(product_id) && 
  this->set_characteristic(characteristic_id) && 
  this->set_property(value);
}

bool Property::send_property()
{
  return this->send_entity((this->link + "stores/" + this->store_id + "/products/" + this->product_id + "/properties/" + this->characteristic_id).c_str());
}

bool Property::delete_property(const std::string& characteristic_id="")
{
  if (characteristic_id.empty())
  {
    return this->delete_entity((this->link + "stores/" + this->store_id + "/products/" + this->product_id + "/properties/" + this->characteristic_id).c_str());
  }
  else
  {
    return this->delete_entity((this->link + "stores/" + this->store_id + "/products/" + this->product_id + "/properties/" + characteristic_id).c_str());
  }
  
}

class Properties : public Entity
{
private:
  Property* property;

public:
  Properties(const char*);
  bool import_properties();
  Json::Value get_properties() const;

  Json::Value get_property() const;
  bool set_store(const std::string&);
  bool set_product(const std::string&);
  bool set_characteristic(const std::string&);
  bool set_property(const std::string&, const std::string&, const std::string&, const std::string&);
  bool set_property(const std::string&);
  bool send_property();
  bool delete_property(const std::string&);
};

Properties::Properties(const char* link) : Entity::Entity(link)
{
  this->property = new Property(this->link.c_str());
}

bool Properties::import_properties()
{
  std::string link = this->link + 
  "stores/" + this->property->get_store_id() + 
  "/products/" + this->property->get_product_id() + 
  "/properties/";
  this->import_entity(link.c_str());
}

Json::Value Properties::get_properties() const
{
  return this->get_entity();
}

Json::Value Properties::get_property() const
{
  return this->property->get_property();
}

bool Properties::set_store(const std::string& store_id)
{
  return this->property->set_store(store_id);
}

bool Properties::set_product(const std::string& product_id)
{
  return this->property->set_product(product_id);
}

bool Properties::set_characteristic(const std::string& characteristic_id)
{
  return this->property->set_characteristic(characteristic_id);
}

bool Properties::set_property(const std::string& value)
{
  return this->property->set_property(value);
}

bool Properties::set_property(const std::string& characteristic_id, const std::string& product_id, const std::string& store_id, const std::string& value)
{
  return this->property->set_property(characteristic_id, product_id, store_id, value);
}

bool Properties::send_property()
{
  return this->property->send_property();
}

bool Properties::delete_property(const std::string& characteristic_id)
{
  return this->property->delete_property(characteristic_id);
}