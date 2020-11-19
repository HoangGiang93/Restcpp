#include "Entity.cpp"

class Characteristic : public Entity
{
private:
  std::string characteristic_id;

public:
  Characteristic(const char*);
  void set_characteristic_id(const std::string &);
  Json::Value get_characteristic();
  bool set_characteristic(const std::string &);
  bool send_characteristic();
  bool delete_characteristic();
};

Characteristic::Characteristic(const char* link) : Entity::Entity(link) {}

void Characteristic::set_characteristic_id(const std::string &characteristic_id)
{
  this->characteristic_id = characteristic_id;
}

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

bool Characteristic::delete_characteristic()
{
  return this->delete_entity((std::string(this->link) + this->characteristic_id).c_str());
}

class Characteristics : public Entity
{
private:
  Characteristic characteristic;

public:
  Characteristics(const char*);
  bool import_characteristics();
  bool set_characteristic(const std::string &);
  Json::Value get_characteristics();
  bool send_characteristic();
  bool delete_characteristic(const std::string &);
};

Characteristics::Characteristics(const char* link) : Entity::Entity(link), characteristic(link) {}

bool Characteristics::import_characteristics()
{
  return this->import_entity();
}

bool Characteristics::set_characteristic(const std::string &characteristic_name)
{
  return this->characteristic.set_characteristic(characteristic_name);
}

Json::Value Characteristics::get_characteristics()
{
  return this->get_entity();
}

bool Characteristics::send_characteristic()
{
  return this->characteristic.send_characteristic();
}

bool Characteristics::delete_characteristic(const std::string &characteristic_id)
{
  this->characteristic.set_characteristic_id(characteristic_id);
  return this->characteristic.delete_characteristic();
}