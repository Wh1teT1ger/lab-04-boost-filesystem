// Copyright 2020 Burylov Denis <burylov01@mail.ru>

#include <gtest/gtest.h>
#include <header.hpp>

std::string current_dir() {
  std::string dir = __FILE__;
  return dir.substr(0, dir.find("test.cpp"));
}

TEST(Brokers, Summary) {
  std::map<std::string, std::set<Account>> broker1 =
      brokers_summary(current_dir());
  std::map<std::string, std::set<Account>> broker2{
      {"test broker",
       {Account{00000001, 20201103, 2}, Account{00000002, 20201201, 3}}}};
  EXPECT_EQ(broker1, broker2);
  std::cout << current_dir() << std::endl;
}

TEST(Brokers, List) {
  std::ostringstream broker1, broker2;
  brokers_info(current_dir(), broker1);
  broker2 << "test broker balance_00000001_20201101.txt" << std::endl;
  broker2 << "test broker balance_00000001_20201103.txt" << std::endl;
  broker2 << "test broker balance_00000002_20201105.txt" << std::endl;
  broker2 << "test broker balance_00000002_20201108.txt" << std::endl;
  broker2 << "test broker balance_00000002_20201201.txt" << std::endl;
  EXPECT_EQ(broker2.str(), broker1.str());
}
