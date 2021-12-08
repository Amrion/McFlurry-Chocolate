#include <gtest/gtest.h>
#include "Postgre_DB.h"

TEST(POSTGRE_DB, test_create_tables) {
  Postgre_DB pg("127.0.0.1", "5432", "test_db", "tester", "test_password");
  USERS_INFO user;
  user.user_id = pg.user_register("mail.ru", "mail123");
  user.name = "USER1";
  user.age = 18;
  user.gender = "M";
  pg.save_user(user);
  int new_user_id = pg.user_id("mail.ru");
  string user_login = pg.user_login(0);
  USERS_INFO user2 = pg.user_info("mail.ru");
  string name = user2.name;
  EXPECT_EQ(new_user_id, 0);
  EXPECT_EQ(user_login, "mail.ru");
  EXPECT_EQ(name, "USER1");
  EXPECT_EQ(pg.user_exist("mail.ru"), 1);
  EXPECT_EQ(pg.user_exist("mail.ru", "mail123"), 1);
  EXPECT_EQ(pg.user_exist("vk.ru"), 0);
}

TEST(POSTGRE_DB, test_set_mark) {
  Postgre_DB pg("127.0.0.1", "5432", "test_db", "tester", "test_password");
  USERS_INFO user;
  user.user_id = pg.user_register("vk.ru", "9054783478543");
  user.name = "USER2";
  user.age = 18;
  user.gender = "W";
  pg.save_user(user);
  pg.set_mark("mail.ru", "vk.ru", 1);
  pg.set_mark("vk.ru", "mail.ru", 1);
  int new_user_id = pg.user_id("vk.ru");
  EXPECT_EQ(new_user_id, 1);
  EXPECT_EQ(pg.is_pair(pg.user_id("vk.ru"), pg.user_id("mail.ru")), 1);
}

TEST(POSTGRE_DB, test_drop_tables) {
  Postgre_DB pg("127.0.0.1", "5432", "test_db", "tester", "test_password");
  pg.drop_tables();
  EXPECT_EQ(pg.user_exist("vk.ru"), 0);
  EXPECT_EQ(pg.user_exist("mail.ru"), 0);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
