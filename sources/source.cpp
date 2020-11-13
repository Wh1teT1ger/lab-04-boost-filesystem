// Copyright 2018 Your Name <your_email>

#include <header.hpp>

Account::Account(const unsigned int& account, const unsigned int& date)
    : _account(account), _numbers(1), _last_date(date) {}

unsigned int Account::last_date() const { return _last_date; }

size_t Account::number() const { return _numbers; }

unsigned int Account::id() const { return _account; }

void Account::update_account(const unsigned int& date, const size_t& number) {
  if (date > _last_date) _last_date = date;
  if (number > _numbers) _numbers = number;
  _numbers++;
}

bool Account::operator==(const Account& other) const {
  return _account == other._account;
}

bool Account::operator!=(const Account& other) const {
  return _account != other._account;
}

bool Account::operator<(const Account& other) const {
  return _account < other._account;
}

bool is_date(const std::string& date) {
  unsigned int mount = std::stoi(date.substr(4, 2));
  unsigned int day = std::stoi(date.substr(6, 2));
  return (mount <= 12 && day <= 31);
}

std::set<Account> brokers_accounts(const fs::path& p) {
  const std::regex filename_template("^balance_(\\d{8})_(\\d{8}).txt$");
  std::set<Account> accounts;
  for (const auto& file_entry : fs::directory_iterator(p)) {
    fs::path entry_path;
    if (fs::is_regular_file(file_entry))
      entry_path = file_entry.path();
    else if (fs::is_symlink(file_entry))
      entry_path = fs::read_symlink(file_entry.path());
    std::string filename = entry_path.filename().string();
    if (!std::regex_match(filename, filename_template)) continue;
    std::smatch match;
    std::regex_search(filename, match, filename_template);

    if (!is_date(match[2])) continue;

    Account account(std::stoi(match[1]), std::stoi(match[2]));
    auto iter_account = accounts.find(account);
    if (iter_account == accounts.end()) {
      accounts.insert(account);
    } else {
      auto& element = *iter_account;
      account.update_account(element.last_date(), element.number());
      accounts.erase(iter_account);
      accounts.insert(account);
    }
    std::cout << p.filename().string() << " " << entry_path.filename().string()
              << std::endl;
  }
  return accounts;
}

std::map<std::string, std::set<Account>> path_to_list(const fs::path& p) {
  std::map<std::string, std::set<Account>> brokers_info;
  std::set<std::string> brokers{"ib", "otkritie", "bcs"};
  for (const auto& directory_entry : fs::directory_iterator(p)) {
    if (!fs::is_directory(directory_entry)) continue;
    const auto& entry_path = directory_entry.path();
    auto entry_name = entry_path.filename().string();
    if (brokers.find(entry_name) == brokers.end()) continue;
    brokers_info.insert(
        std::make_pair(entry_name, brokers_accounts(entry_path)));
  }
  return brokers_info;
}