// Copyright (c) 2020 Kanav Bhatnagar. All rights reserved.

#include <island/location.h>

namespace island {

Location::Location(int row, int col) : row_(row), col_(col) {}

Location Location::operator+(const Location& rhs) const {
  return { row_ + rhs.row_, col_ + rhs.col_ };
}

int mod(int lhs_value, int rhs_value) {
  int result = lhs_value % rhs_value;

  if (result < 0) {
    return result + rhs_value;
  }
  return result;
}

Location Location::operator%(const Location& rhs) const {
  return {mod(row_, rhs.row_), mod(col_, rhs.col_)};
}

}  // namespace island
