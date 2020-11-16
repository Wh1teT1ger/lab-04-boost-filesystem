#include <header.hpp>

int main(int argc, char* argv[]) {
  fs::path path_to_ftp;
  if (argc >= 2) {
    path_to_ftp = argv[1];
  } else {
    path_to_ftp = fs::current_path();
  }
  std::map<std::string, std::set<Account>> brokers =
      brokers_summary(path_to_ftp);
  brokers_info(path_to_ftp, std::cout);
  std::cout << std::endl;
  for (auto& broker : brokers) {
    for (auto& account : broker.second) {
      std::cout << "broker:" << broker.first << " account:";
      std::cout.fill('0');
      std::cout.width(8);
      std::cout << account.id();
      std::cout << " files:" << account.number()
                << " lastdate:" << account.last_date() << std::endl;
    }
  }

  return 0;
}
