// Copyright (c) 2020 Kanav Bhatnagar. All rights reserved.

#ifndef ISLAND_ITEM_H_
#define ISLAND_ITEM_H_

#include <string>
#include <utility>
#include <vector>

namespace island {

/** Represents each item in the inventory of the player. */
struct Item {
  /**
   * The default constructor for the Item.
   *
   * @param name the name of the item
   * @param description the description of the item
   */
  Item(const std::string& name, const std::string& description)
  : name_(name),
    description_(description) {}

  /** The name of the item. */
  const std::string& name_;

  /** The description of the item. */
  const std::string& description_;
};

}  // namespace island

#endif // ISLAND_ITEM_H_
