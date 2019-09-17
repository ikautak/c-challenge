#include <cassert>
#include <iostream>
#include <string>
#include <vector>

struct DiscountType {
  virtual double discount_percent(double const price,
                                  double const quantity) const noexcept = 0;
  virtual ~DiscountType() = default;
};

struct FixedDiscount final : public DiscountType {
  explicit FixedDiscount(double const discount) noexcept
      : discount_(discount) {}
  virtual double discount_percent(double const, double const) const noexcept {
    return discount_;
  }

 private:
  double const discount_;
};

struct VolumeDiscount final : public DiscountType {
  VolumeDiscount(double const quantity, double const discount) noexcept
      : discount_(discount), min_quantity_(quantity) {}

  virtual double discount_percent(double const, double const quantity) const
      noexcept {
    return quantity >= min_quantity_ ? discount_ : 0.0;
  }

 private:
  double const discount_;
  double const min_quantity_;
};

struct PriceDiscount : public DiscountType {
  PriceDiscount(double const price, double const discount) noexcept
      : discount_(discount), min_total_price_(price) {}
  virtual double discount_percent(double const price,
                                  double const quantity) const noexcept {
    return price * quantity >= min_total_price_ ? discount_ : 0.0;
  }

 private:
  double const discount_;
  double const min_total_price_;
};

struct AmountDiscount : public DiscountType {
  AmountDiscount(double const price, double const discount) noexcept
      : discount_(discount), min_total_price_(price) {}
  virtual double discount_percent(double const price, double cosnt) const
      noexcept {
    return price >= min_total_price_ ? discount_ : 0.0;
  }

 private:
  double const discount_;
  double const min_total_price_;
};

struct Customer {
  std::string name;
  DiscountType* discount;
};

enum class ArticleUnit { piece, kg, meter, sqmeter, cmeter, liter };

struct Article {
  int id;
  std::string name;
  double price;
  ArticleUnit unit;
  DiscountType* discount;
};

struct OrderLine {
  Article product;
  int quantity;
  DiscountType* discount;
};

struct Order {
  int id;
  Customer* buyer;
  std::vector<OrderLine> lines;
  DiscountType* discount;
};

struct PriceCalculator {
  virtual double calculate_price(Order const& o) = 0;
  virtual ~PriceCalculator() = default;
};

struct CumulativePriceCalculator : public PriceCalculator {
  virtual double calculate_price(Order const& o) override {
    double price = 0.0;

    for (auto ol : o.lines) {
      double line_price = ol.product.price * ol.quantity;

      if (ol.product.discount != nullptr) {
        line_price *= (1.0 - ol.product.discount->discount_percent(
                                 ol.product.price, ol.quantity));
      }

      if (ol.discount != nullptr) {
        line_price *= (1.0 - ol.discount->discount_percent(ol.product.price,
                                                           ol.quantity));
      }

      if (o.buyer != nullptr && o.buyer->discount != nullptr) {
        line_price *= (1.0 - o.buyer->discount->discount_percent(
                                 ol.product.price, ol.quantity));
      }

      price += line_price;
    }

    if (o.discount != nullptr) {
      price *= (1.0 - o.discount->discount_percent(price, 0.0));
    }

    return price;
  }
};

inline bool are_equal(double const d1, double const d2,
                      double const diff = 0.001) {
  return std::abs(d1 - d1) <= diff;
}

int main() {
  FixedDiscount d1(0.1);
  VolumeDiscount d2(10, 0.15);
  PriceDiscount d3(100, 0.05);
  AmountDiscount d4(100, 0.05);

  Customer c1{"default", nullptr};
  Customer c2{"john", &d1};
  Customer c3{"joane", &d3};

  Article a1{1, "pen", 5, ArticleUnit::piece, nullptr};
  Article a2{2, "expensive pen", 15, ArticleUnit::piece, &d1};
  Article a3{3, "scissors", 10, ArticleUnit::piece, &d2};

  CumulativePriceCalculator calc;

  Order o1{101, &c1, {{a1, 1, nullptr}}, nullptr};
  assert(are_equal(calc.calculate_price(o1), 5.0));

  Order o3{103, &c1, {{a2, 1, nullptr}}, nullptr};
  assert(are_equal(calc.calculate_price(o3), 13.5));

  Order o6{106, &c1, {{a3, 15, nullptr}}, nullptr};
  assert(are_equal(calc.calculate_price(o6), 127.5));

  Order o9{109, &c3, {{a2, 20, &d1}}, &d4};
  assert(are_equal(calc.calculate_price(o9), 219.3075));

  return 0;
}
