#pragma once

#include "Entity.cpp"

class Characteristic : public Entity
{
public:
  Characteristic(const char*);
  Json::Value get_characteristic();
  bool set_characteristic(const std::string &);
  bool send_characteristic();
  bool delete_characteristic(const std::string &);
};

Characteristic::Characteristic(const char* link) : Entity::Entity((std::string(link) + "characteristics/").c_str()) {}

Json::Value Characteristic::get_characteristic()
{
  return this->get_entity();
}

bool Characteristic::set_characteristic(const std::string &characteristic_name)
{
  Json::Value entity;
  entity["name"] = characteristic_name;
  return this->set_entity(entity);
}

bool Characteristic::send_characteristic()
{
  return this->send_entity();
}

bool Characteristic::delete_characteristic(const std::string& characteristic_id)
{
  return this->delete_entity((this->link + characteristic_id).c_str());
}

class Characteristics : public Entity
{
private:
  Characteristic* characteristic;

public:
  Characteristics(const char*);
  bool import_characteristics();
  bool set_characteristic(const std::string &);
  Json::Value get_characteristics();
  bool send_characteristic();
  bool delete_characteristic(const std::string &);
};

Characteristics::Characteristics(const char* link) : Entity::Entity((std::string(link) + "characteristics/").c_str()) 
{
  this->characteristic = new Characteristic(link);
}

bool Characteristics::import_characteristics()
{
  return this->import_entity();
}

bool Characteristics::set_characteristic(const std::string &characteristic_name)
{
  return this->characteristic->set_characteristic(characteristic_name);
}

Json::Value Characteristics::get_characteristics()
{
  return this->get_entity();
}

bool Characteristics::send_characteristic()
{
  return this->characteristic->send_characteristic();
}

bool Characteristics::delete_characteristic(const std::string &characteristic_id)
{
  return this->characteristic->delete_characteristic(characteristic_id);
}