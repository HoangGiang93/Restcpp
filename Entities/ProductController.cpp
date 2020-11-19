#pragma once

#include "EntityController.cpp"

class ProductController : public EntityController
{
public:
  ProductController(const char*);
  Json::Value get_products();
  bool post_products(const Json::Value &);

  Json::Value get_product(const std::string &);
  bool post_product(const Json::Value &, const std::string &);
  bool delete_product(const std::string &);
};

ProductController::ProductController(const char* link) : EntityController::EntityController((std::string(link) + "products/").c_str())
{
}

Json::Value ProductController::get_products()
{
  return this->get_entities();
}

bool ProductController::post_products(const Json::Value &products)
{
  if (!products["products"].isNull())
  {
    return this->post_entities(products, (std::string(this->entities->link) + "list").c_str());
  }
  else
  {
    std::cout << "Invalid products" << std::endl;
    return false;
  }
}

Json::Value ProductController::get_product(const std::string &product_id)
{
  return this->get_entity((this->entity->link + product_id).c_str());
}

bool ProductController::post_product(const Json::Value &products, const std::string &product_id)
{
  if (!products["products"].isNull())
  {
    return this->post_entities(products, (this->entities->link + product_id).c_str());
  }
  else
  {
    std::cout << "Invalid products" << std::endl;
    return false;
  }
}

bool ProductController::delete_product(const std::string &product_id)
{
  return this->delete_entity((this->entity->link + product_id).c_str());
}