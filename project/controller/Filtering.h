#pragma once

#include "../repo/GameRepo.h"

enum class Comparison { LessThan, GreaterThan };

class Specification {
public:
  virtual bool isSatisfiedBy(const Game &game) const = 0;
  virtual ~Specification() = default;
};

class GenreSpecification : public Specification {
private:
  std::string genre;

public:
  GenreSpecification(const std::string &genre) : genre(genre) {}
  bool isSatisfiedBy(const Game &game) const override {
    const auto &genres = game.getGenres();
    return std::find(genres.begin(), genres.end(), genre) != genres.end();
  }
};

class YearSpecification : public Specification {
private:
  unsigned int year;
  Comparison comparison;

public:
  YearSpecification(unsigned int year, Comparison comparison)
      : year(year), comparison(comparison) {}
  bool isSatisfiedBy(const Game &game) const override {
    if (comparison == Comparison::LessThan) {
      return game.getReleaseYear() < year;
    } else {
      return game.getReleaseYear() > year;
    }
  }
};

class AndSpecification : public Specification {
private:
  const Specification &spec1;
  const Specification &spec2;

public:
  AndSpecification(const Specification &spec1, const Specification &spec2)
      : spec1(spec1), spec2(spec2) {}
  bool isSatisfiedBy(const Game &game) const override {
    return spec1.isSatisfiedBy(game) && spec2.isSatisfiedBy(game);
  }
};

class OrSpecification : public Specification {
private:
  const Specification &spec1;
  const Specification &spec2;

public:
  OrSpecification(const Specification &spec1, const Specification &spec2)
      : spec1(spec1), spec2(spec2) {}
  bool isSatisfiedBy(const Game &game) const override {
    return spec1.isSatisfiedBy(game) || spec2.isSatisfiedBy(game);
  }
};
