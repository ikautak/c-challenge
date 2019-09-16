#include <algorithm>
#include <iostream>
#include <locale>
#include <memory>
#include <string_view>
#include <vector>

class PasswordValidator {
 public:
  PasswordValidator() = default;
  virtual ~PasswordValidator() = default;

  virtual bool validate(std::string_view password) = 0;
};

class LengthValidator : public PasswordValidator {
 public:
  explicit LengthValidator(uint32_t len) : length_(len) {}

  bool validate(std::string_view password) override {
    return password.length() >= length_;
  }

 private:
  const uint32_t length_;
};

class DigitValidator : public PasswordValidator {
 public:
  DigitValidator() = default;
  virtual ~DigitValidator() = default;

  bool validate(std::string_view password) override {
    return std::any_of(std::begin(password), std::end(password), isdigit);
  }
};

class CaseValidator : public PasswordValidator {
 public:
  CaseValidator() = default;
  virtual ~CaseValidator() = default;

  bool validate(std::string_view password) override {
    const bool has_lower =
        std::any_of(std::cbegin(password), std::cend(password), islower);
    const bool has_upper =
        std::any_of(std::cbegin(password), std::cend(password), isupper);
    return has_lower && has_upper;
  }
};

class SymbolValidator : public PasswordValidator {
 public:
  SymbolValidator() = default;
  virtual ~SymbolValidator() = default;

  bool validate(std::string_view password) override {
    return password.find_first_of("!@#$%^&*(){}[]?<>") != std::string::npos;
  }
};

class AllValidator : public PasswordValidator {
 public:
  AllValidator() {
    validators_.push_back(std::make_unique<LengthValidator>(8));
    validators_.push_back(std::make_unique<DigitValidator>());
    validators_.push_back(std::make_unique<CaseValidator>());
    validators_.push_back(std::make_unique<SymbolValidator>());
  }

  bool validate(std::string_view password) override {
    for (auto&& v : validators_) {
      if (v->validate(password) == false) {
        return false;
      }
    }

    return true;
  }

 private:
  std::vector<std::unique_ptr<PasswordValidator>> validators_;
};

int main() {
  auto v = std::make_unique<AllValidator>();

  std::cout << v->validate("abc123!@#") << std::endl;
  std::cout << v->validate("abcdef!@#") << std::endl;
  std::cout << v->validate("ABC123!@#") << std::endl;
  std::cout << v->validate("Abc123!@#") << std::endl;

  return 0;
}
