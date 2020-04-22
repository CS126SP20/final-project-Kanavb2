// Copyright (c) 2020 Kanav Bhatnagar. All rights reserved.

#ifndef ISLAND_STATISTICS_H_
#define ISLAND_STATISTICS_H_

namespace island {
/** Manages the statistics of a character in the game. */
class Statistics {
public:
  Statistics(size_t hit_points, size_t attack, size_t defense, size_t speed) {
    hit_points_ = hit_points;
    attack_ = attack;
    defense_ = defense;
    speed_ = speed;
  }
  size_t hit_points_;
  size_t attack_;
  size_t defense_;
  size_t speed_;

  inline size_t GetHitPoints() {
    return hit_points_;
  }

  inline size_t GetAttack() {
    return attack_;
  }

  inline size_t GetDefense() {
    return defense_;
  }

  inline size_t GetSpeed() {
    return speed_;
  }

  inline void SetHitPoints(size_t hit_points) {
    hit_points_ = hit_points;
  }

  inline void SetAttack(size_t attack) {
    attack_ = attack;
  }

  inline void SetDefense(size_t defense) {
    defense_ = defense;
  }

  inline void SetSpeed(size_t speed) {
    speed_ = speed;
  }
};

}  // namespace island

#endif // ISLAND_STATISTICS_H_
