// Copyright (c) 2020 Kanav Bhatnagar. All rights reserved.

#ifndef ISLAND_LOCATION_H_
#define ISLAND_LOCATION_H_

namespace island {

/** Represents one location point on the map. */
class Location {
 public:
  /**
   * Constructor for the class.
   *
   * @param row the row index of the map
   * @param col the column index of the map
   */
  Location(int row, int col);

  /**
   * Overload for the + operator, adds two locations.
   *
   * @param rhs the other location to perform the operation on
   * @return the added location
   */
  Location operator+(const Location& rhs) const;

  /**
   * Overload for the % operator, gives the remainder of two locations.
   *
   * @param rhs the other location to perform the operation on
   * @return the remaindered location
   */
  Location operator%(const Location& rhs) const;


  /**
   * Accessor function for the row index in the location.
   *
   * @return the row index of the location
   */
  inline int GetRow() const {
    return row_;
  }

  /**
   * Accessor function for the column index in the location.
   *
   * @return the column index of the location
   */
  inline int GetCol() const {
    return col_;
  }

  /**
   * Sets the row index of the location to a new value.
   *
   * @param value the value to set the row to
   */
  inline void SetRow(int value) {
    row_ = value;
  }

  /**
   * Sets the column index of the location to a new value.
   *
   * @param value the value to set the column to
   */
  inline void SetCol(int value) {
    col_ = value;
  }

 private:
  /** The row index of the location. */
  int row_;

  /** The column index of the location. */
  int col_;
};

}  // namespace island

#endif // ISLAND_LOCATION_H_
