#pragma once

#include "Store.cpp"

class Shelf : public Entity
{
private:
  Stores* stores;
  std::string store_id;
public:
  Shelf(const char*);

  std::string get_store_id() const { return this->store_id; };
  bool set_store(const std::string&);

  bool import_shelf(const std::string&);
  Json::Value get_shelf() const;
  bool set_shelf(const Json::Value&);
  bool send_shelf(const std::string&);
  bool delete_shelf(const std::string&);
};

Shelf::Shelf(const char* link) : Entity::Entity(link)
{
  this->stores = new Stores(link);
}

bool Shelf::set_store(const std::string& store_id)
{
  if (this->stores->import_store(store_id))
  {
    this->store_id = this->stores->get_store()["id"].asString();
    return true;
  }
  return false;
}

bool Shelf::import_shelf(const std::string& shelf_id)
{
  if (shelf_id.empty())
  {
    std::cout << "Shelf id not found" << std::endl;
    return false;
  }
  else
  {
    return this->import_entity((this->link + "/shelves/" + shelf_id).c_str());
  }
}

Json::Value Shelf::get_shelf() const
{
  return this->get_entity();
}

bool Shelf::set_shelf(const Json::Value& shelf)
{
  if (shelf["cadPlanId"].isString() &&
      shelf["depth"].isNumeric() &&
      shelf["externalReferenceId"].isString() &&
      shelf["height"].isNumeric() &&
      shelf["orientationY"].isNumeric() &&
      shelf["orientationYaw"].isNumeric() &&
      shelf["orientationZ"].isNumeric() &&
      shelf["orientationx"].isNumeric() &&
      shelf["positionX"].isNumeric() &&
      shelf["positionY"].isNumeric() &&
      shelf["positionZ"].isNumeric() &&
      shelf["productGroupId"].isNumeric() &&
      shelf["storeId"].isNumeric() &&
      shelf["width"].isNumeric())
  {
    return this->set_entity(shelf);
  }
  else
  {
    std::cout << "Invalid Shelf" << std::endl;
    return false;
  }
}

bool Shelf::send_shelf(const std::string &store_id)
{
  return this->set_store(store_id) && this->send_entity((std::string(link) + "/stores/" + this->store_id + "/shelves").c_str());
}

bool Shelf::delete_shelf(const std::string& shelf_id)
{
  return this->delete_entity((this->link + "/shelves/" + shelf_id).c_str());
}

class Shelves : public Entity
{
private:
  Shelf* shelf;

public:
  Shelves(const char*);
  bool import_shelves(const std::string&);
  Json::Value get_shelves() const;

  bool set_store(const std::string&);
  bool import_shelf(const std::string&);
  Json::Value get_shelf() const;
  bool set_shelf(const Json::Value&);
  bool send_shelf(const std::string&);
  bool delete_shelf(const std::string&);
};

Shelves::Shelves(const char* link) : Entity::Entity(link)
{
  this->shelf = new Shelf(link);
}

bool Shelves::import_shelves(const std::string& store_id)
{
  return this->shelf->set_store(store_id) && this->import_entity((this->link + "/stores/" + this->shelf->get_store_id() + "/shelves").c_str());
}

Json::Value Shelves::get_shelves() const
{
  return this->get_entity();
}

bool Shelves::import_shelf(const std::string& shelf_id)
{
  return this->shelf->import_shelf(shelf_id);
}

Json::Value Shelves::get_shelf() const
{
  return this->shelf->get_shelf();
}

bool Shelves::set_shelf(const Json::Value& shelf)
{
  return this->shelf->set_shelf(shelf);
}

bool Shelves::send_shelf(const std::string& store_id)
{
  return this->shelf->send_shelf(store_id);
}

bool Shelves::delete_shelf(const std::string& shelf_id)
{
  return this->shelf->delete_shelf(shelf_id);
}