#pragma once

#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>
#include <curlpp/cURLpp.hpp>
#include <jsoncpp/json/json.h>
#include <jsoncpp/json/reader.h>
#include <sstream>

class Entity
{
public:
  std::string link;

  virtual Json::Value get_data(const char* link = nullptr)
  {
    curlpp::Easy request;
    if (link)
    {
      request.setOpt<curlpp::options::Url>(link);
    }
    else
    {
      request.setOpt<curlpp::options::Url>(this->link.c_str());
    }
    std::stringstream ss;
    ss << request;
    request.perform();

    // Convert the string to json
    Json::Reader reader;
    reader.parse(ss.str(), this->data);
    return this->data;
  }

  virtual bool post_data(const char* link = nullptr)
  {
    curlpp::Easy request;
    try
    {
      if (link)
      {
        request.setOpt<curlpp::options::Url>(link);
      }
      else
      {
        request.setOpt<curlpp::options::Url>(this->link.c_str());
      }
      std::list<std::string> header;
      header.push_back("Content-Type: application/json");
      request.setOpt(new curlpp::options::HttpHeader(header));
      request.setOpt(new curlpp::options::PostFields(this->data.toStyledString()));
      request.perform();
    }

    catch (curlpp::RuntimeError& e)
    {
      std::cout << e.what() << std::endl;
      std::cout << "Is host name correct?" << std::endl;
    }

    catch (curlpp::LogicError& e)
    {
      std::cout << e.what() << std::endl;
    }
  }

  virtual bool delete_data(const char* link = nullptr)
  {
    curlpp::Easy request;
    try
    {
      if (link)
      {
        request.setOpt<curlpp::options::Url>(link);
      }
      else
      {
        request.setOpt<curlpp::options::Url>(this->link.c_str());
      }
      request.setOpt(new curlpp::options::CustomRequest{"DELETE"});
      request.perform();
    }

    catch (curlpp::RuntimeError& e)
    {
      std::cout << e.what() << std::endl;
      std::cout << "Is host name correct?" << std::endl;
    }

    catch (curlpp::LogicError& e)
    {
      std::cout << e.what() << std::endl;
    }
  }

  Json::Value data;

  Entity(const char* link) : link(link) {}
  ~Entity() {}
};

class EntityController
{
protected:
  Entity* entity;
  Entity* entities;

protected:
  virtual Json::Value get_entity(const char* link = nullptr)
  {
    return entity->get_data(link);
  }

  virtual bool post_entity(const Json::Value& data, const char* link = nullptr)
  {
    this->entity->data = data;
    return this->entity->post_data(link);
  }

  virtual bool delete_entity(const char* link = nullptr)
  {
    return this->entity->delete_data(link);
  }

  virtual Json::Value get_entities(const char* link = nullptr)
  {
    return entities->get_data(link);
  }

  virtual bool post_entities(const Json::Value& data, const char* link = nullptr)
  {
    this->entities->data = data;
    return this->entities->post_data(link);
  }

  virtual bool delete_entities(const char* link = nullptr)
  {
    return this->entities->delete_data(link);
  }

  EntityController(const char* link) : entity(new Entity(link)), entities(new Entity(link)) {}
  ~EntityController() {}
};