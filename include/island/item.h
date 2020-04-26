// Copyright (c) 2020 Kanav Bhatnagar. All rights reserved.

#ifndef ISLAND_ITEM_H_
#define ISLAND_ITEM_H_

#include <string>
#include <utility>
#include <vector>

namespace island {

/** Represents the inventory of the player. */
class Item {
  Item(const std::string& name, const std::string& description)
  : name_(name),
    description_(description) {}

  const std::string& name_;
  const std::string& description_;
};

}  // namespace island

#endif // ISLAND_ITEM_H_
