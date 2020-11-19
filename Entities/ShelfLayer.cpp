#pragma once

#include "Shelf.cpp"

class ShelfLayer : public Entity
{
private:
  Shelves* shelves;
  std::string shelf_id;

public:
  ShelfLayer(const char*);

  std::string get_shelf_id() const { return this->shelf_id; };
  bool set_shelf(const std::string&);

  bool import_shelf_layer(const std::string&);
  Json::Value get_shelf_layer() const;
  bool set_shelf_layer(const Json::Value&);
  bool send_shelf_layer(const std::string&);
  bool delete_shelf_layer(const std::string&);
};

ShelfLayer::ShelfLayer(const char* link) : Entity::Entity(link)
{
  this->shelves = new Shelves(link);
}

bool ShelfLayer::set_shelf(const std::string& shelf_id)
{
  if (this->shelves->import_shelf(shelf_id))
  {
    this->shelf_id = this->shelves->get_shelf()["id"].asString();
    return true;
  }
  return false;
}

bool ShelfLayer::import_shelf_layer(const std::string& shelf_layer_id)
{
  if (shelf_layer_id.empty())
  {
    std::cout << "Shelf layer id not found" << std::endl;
    return false;
  }
  else
  {
    return this->import_entity((this->link + "/shelflayers/" + shelf_layer_id).c_str());
  }
}

Json::Value ShelfLayer::get_shelf_layer() const
{
  return this->get_entity();
}

bool ShelfLayer::set_shelf_layer(const Json::Value& shelf_layer)
{
  if (shelf_layer["depth"].isNumeric() &&
      shelf_layer["externalReferenceId"].isString() &&
      shelf_layer["height"].isNumeric() &&
      shelf_layer["positionZ"].isNumeric() &&
      shelf_layer["shelfId"].isNumeric() &&
      shelf_layer["type"].isString() &&
      shelf_layer["width"].isNumeric())
  {
    return this->set_entity(shelf_layer);
  }
  else
  {
    std::cout << "Invalid shelf layer" << std::endl;
    return false;
  }
}

bool ShelfLayer::send_shelf_layer(const std::string& shelf_id)
{
  return this->set_shelf(shelf_id) && this->send_entity((std::string(link) + "/shelves/" + this->shelf_id + "/shelflayers").c_str());
}

bool ShelfLayer::delete_shelf_layer(const std::string& shelf_layer_id)
{
  return this->delete_entity((this->link + "shelflayers/" + shelf_layer_id).c_str());
}

class ShelfLayers : public Entity
{
private:
  ShelfLayer* shelf_layer;

public:
  ShelfLayers(const char*);
  bool import_shelf_layers(const std::string&);
  Json::Value get_shelf_layers() const;

  bool set_shelf(const std::string&);
  bool import_shelf_layer(const std::string&);
  Json::Value get_shelf_layer() const;
  bool set_shelf_layer(const Json::Value&);
  bool send_shelf_layer(const std::string&);
  bool delete_shelf_layer(const std::string&);
};

ShelfLayers::ShelfLayers(const char* link) : Entity::Entity(link)
{
  this->shelf_layer = new ShelfLayer(link);
}

bool ShelfLayers::import_shelf_layers(const std::string& shelf_id)
{
  return this->shelf_layer->set_shelf(shelf_id) && this->import_entity((this->link + "/shelves/" + this->shelf_layer->get_shelf_id() + "/shelflayers").c_str());
}

Json::Value ShelfLayers::get_shelf_layers() const
{
  return this->get_entity();
}

bool ShelfLayers::import_shelf_layer(const std::string& shelf_layer_id)
{
  return this->shelf_layer->import_shelf_layer(shelf_layer_id);
}

Json::Value ShelfLayers::get_shelf_layer() const
{
  return this->shelf_layer->get_shelf_layer();
}

bool ShelfLayers::set_shelf_layer(const Json::Value& shelf_layer)
{
  return this->shelf_layer->set_shelf_layer(shelf_layer);
}

bool ShelfLayers::send_shelf_layer(const std::string& shelf_id)
{
  return this->shelf_layer->send_shelf_layer(shelf_id);
}

bool ShelfLayers::delete_shelf_layer(const std::string& shelf_layer_id)
{
  return this->shelf_layer->delete_shelf_layer(shelf_layer_id);
}