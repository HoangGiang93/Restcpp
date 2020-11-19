#pragma once

#include <curlpp/Options.hpp>
#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <jsoncpp/json/json.h>
#include <jsoncpp/json/reader.h>
#include <sstream>

class Entity
{
protected:
  std::string link;
  Json::Value entity;
  std::string name;
  curlpp::Easy request;

  virtual bool import_entity()
  {
    std::ostringstream os;
    os << this->request;

    // Convert the string to json
    Json::Reader reader;
    return reader.parse(os.str(), this->entity);
  }

  virtual Json::Value get_entity() const
  {
    return this->entity;
  }

  virtual bool set_entity(const Json::Value &entity)
  {
    this->entity = entity;
    return true;
  }

  virtual bool send_entity(const char* link = nullptr) 
  {
    try
    {
      if(link)
      {
        this->request.setOpt<curlpp::options::Url>(link);
      }
      else
      {
        this->request.setOpt<curlpp::options::Url>(this->link.c_str());
      }
      std::list<std::string> header;
      header.push_back("Content-Type: application/json");
      this->request.setOpt(new curlpp::options::HttpHeader(header));
      this->request.setOpt(new curlpp::options::PostFields(this->entity.toStyledString()));
      this->request.perform();
    }

    catch(curlpp::RuntimeError & e)
    {
      std::cout << e.what() << std::endl;
      std::cout << "Is host name correct?" << std::endl;
    }

    catch(curlpp::LogicError & e)
    {
      std::cout << e.what() << std::endl;
    }
  }

  virtual bool delete_entity(const char* link = nullptr) 
  {
    try
    {
      if(link)
      {
        this->request.setOpt<curlpp::options::Url>(link);
      }
      else
      {
        this->request.setOpt<curlpp::options::Url>(this->link.c_str());
      }
      this->request.setOpt(new curlpp::options::CustomRequest{"DELETE"});
      this->request.perform();
    }

    catch(curlpp::RuntimeError & e)
    {
      std::cout << e.what() << std::endl;
      std::cout << "Is host name correct?" << std::endl;
    }

    catch(curlpp::LogicError & e)
    {
      std::cout << e.what() << std::endl;
    }
  }

public:
  Entity(const char*);
  ~Entity();
};

Entity::Entity(const char* link = nullptr) : link(link)
{
  try
  {
    // That's all that is needed to do cleanup of used resources (RAII style).
    curlpp::Cleanup myCleanup;
    this->request.setOpt<curlpp::options::Url>(link);
    this->request.perform();
  }

  catch(curlpp::RuntimeError & e)
  {
    std::cout << e.what() << std::endl;
    std::cout << "Is host name correct?" << std::endl;
  }

  catch(curlpp::LogicError & e)
  {
    std::cout << e.what() << std::endl;
  }
}

Entity::~Entity()
{
}