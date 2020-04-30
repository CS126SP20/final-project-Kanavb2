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
  Item(std::string&& name, std::string&& description, std::string&& file_path)
  : name_(std::move(name)),
    description_(std::move(description)),
    file_path_(std::move(file_path)) {}

  /** The name of the item. */
  std::string name_;

  /** The description of the item. */
  std::string description_;

  /** The file path storing the image of the item. */
  std::string file_path_;
};

}  // namespace island

#endif // ISLAND_ITEM_H_
