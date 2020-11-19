#pragma once

#include "Entity.cpp"

class Store : public Entity
{
public:
  Store(const char*);
  bool import_store(const std::string&);
  Json::Value get_store() const;
  bool set_store(const Json::Value&);
  bool send_store();
  bool delete_store(const std::string&);
};

Store::Store(const char* link) : Entity::Entity((std::string(link) + "stores/").c_str())
{
}

bool Store::import_store(const std::string& store_id)
{
  if (store_id.empty())
  {
    std::cout << "Store id not found" << std::endl;
    return false;
  }
  else
  {
    return this->import_entity((this->link + store_id).c_str());
  }
}

Json::Value Store::get_store() const
{
  return this->get_entity();
}

bool Store::set_store(const Json::Value& store)
{
  if (store["addressAdditional"].isString() &&
      store["addressCity"].isString() &&
      store["addressCountry"].isString() &&
      store["addressPostcode"].isString() &&
      store["addressState"].isString() &&
      store["addressStreet"].isString() &&
      store["addressStreetNumber"].isString() &&
      store["cadPlanId"].isString() &&
      store["latitude"].isNumeric() &&
      store["longitude"].isNumeric() &&
      store["storeName"].isString() &&
      store["storeNumber"].isString())
  {
    return this->set_entity(store);
  }
  else
  {
    std::cout << "Invalid Store" << std::endl;
    return false;
  }
}

bool Store::send_store()
{
  return this->send_entity();
}

bool Store::delete_store(const std::string& store_id)
{
  return this->delete_entity((this->link + store_id).c_str());
}

class Stores : public Entity
{
private:
  Store* store;

public:
  Stores(const char*);
  bool import_stores();
  Json::Value get_stores() const;

  bool import_store(const std::string&);
  Json::Value get_store() const;
  bool set_store(const Json::Value&);
  bool send_store();
  bool delete_store(const std::string&);
};

Stores::Stores(const char* link) : Entity::Entity((std::string(link) + "stores/").c_str())
{
  this->store = new Store(link);
}

bool Stores::import_stores()
{
  return this->import_entity();
}

Json::Value Stores::get_stores() const
{
  return this->get_entity();
}

bool Stores::import_store(const std::string& store_id)
{
  return this->store->import_store(store_id);
}

Json::Value Stores::get_store() const
{
  if (this->store)
  {
    return this->store->get_store();
  }
  else
  {
    return Json::Value();
  }
}

bool Stores::set_store(const Json::Value& store)
{
  return this->store->set_store(store);
}

bool Stores::send_store()
{
  return this->store->send_store();
}

bool Stores::delete_store(const std::string& store_id)
{
  return this->store->delete_store(store_id);
}
