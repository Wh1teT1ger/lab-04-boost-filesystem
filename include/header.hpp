// Copyright 2018 Your Name <your_email>

#ifndef INCLUDE_HEADER_HPP_
#define INCLUDE_HEADER_HPP_

#include <boost/filesystem.hpp>
#include <iostream>
#include <map>
#include <regex>
#include <set>
#include <string>

namespace fs = ::boost::filesystem;

class Account {
  unsigned int _account;
  size_t _numbers = 0;
  unsigned int _last_date;

 public:
  Account(const unsigned int& account, const unsigned int& date);

  [[nodiscard]] unsigned int last_date() const;

  [[nodiscard]] size_t number() const;
  [[nodiscard]] unsigned int id() const;

  void update_account(const unsigned int& date, const size_t& number);

  bool operator==(const Account& other) const;

  bool operator!=(const Account& other) const;

  bool operator<(const Account& other) const;
};

bool is_date(const std::string& date);

std::set<Account> brokers_accounts(const fs::path& p);

std::map<std::string, std::set<Account>> path_to_list(const fs::path& p);

#endif  // INCLUDE_HEADER_HPP_
