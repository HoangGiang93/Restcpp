#pragma once

#include "Entity.cpp"

class Customer : public Entity
{
public:
  Customer(const char*);

  bool import_customer(const std::string&);
  Json::Value get_customer() const;
  bool set_customer(const std::string&);
  bool send_customer();
  bool delete_customer(const std::string&);
};

Customer::Customer(const char* link) : Entity::Entity((std::string(link) + "customers/").c_str()) {}

bool Customer::import_customer(const std::string& customer_id)
{
  return this->import_entity((this->link + customer_id).c_str());
}

Json::Value Customer::get_customer() const
{
  return this->get_entity();
}

bool Customer::set_customer(const std::string& customer_name)
{
  Json::Value entity;
  entity["anonymisedName"] = customer_name;
  return this->set_entity(entity);
}

bool Customer::send_customer()
{
  return this->send_entity();
}

bool Customer::delete_customer(const std::string& customer_id)
{
  return this->delete_entity((this->link + customer_id).c_str());
}

class Customers : public Entity
{
private:
  Customer* customer;

public:
  Customers(const char*);
  bool import_customers();
  Json::Value get_customer() const;
  bool import_customer(const std::string&);
  bool set_customer(const std::string&);
  Json::Value get_customers() const;
  bool send_customer();
  bool delete_customer(const std::string&);
};

Customers::Customers(const char* link) : Entity::Entity((std::string(link) + "customers/").c_str())
{
  this->customer = new Customer(link);
}

bool Customers::import_customer(const std::string& customer_id)
{
  return this->customer->import_customer(customer_id);
}

Json::Value Customers::get_customer() const
{
  return this->customer->get_customer();
}

bool Customers::import_customers()
{
  return this->import_entity();
}

Json::Value Customers::get_customers() const
{
  return this->get_entity();
}

bool Customers::set_customer(const std::string& customer_name)
{
  return this->customer->set_customer(customer_name);
}

bool Customers::send_customer()
{
  return this->customer->send_customer();
}

bool Customers::delete_customer(const std::string& customer_id)
{
  return this->customer->delete_customer(customer_id);
}