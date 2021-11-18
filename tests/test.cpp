#include <gtest/gtest.h>
#include "DataBase.h"
#include "DIALOGS.h"
#include "MARKS.h"
#include "PHOTOS.h"
#include "USERS_INFO.h"
#include "USERS_REC.h"

TEST(DIALOGS_TEST, DIALOGS_set_get) {
  DIALOG dialog;
  dialog.setId(1);
  dialog.setFirstUserId(1);
  dialog.setSecondUserId(2);
  dialog.setDate("10.07.2021");
  EXPECT_EQ(dialog.getId, 1);
  EXPECT_EQ(dialog.getFirstUserId, 1);
  EXPECT_EQ(dialog.getSecondUserId, 2);
  ASSERT_STREQ(dialog.getDate, "10.07.2021")
}

TEST(DIALOGS_TABLE_TEST, DIALOGS_insert_save) {
  DIALOG dialog;
  dialog.setId(1);
  dialog.setFirstUserId(1);
  dialog.setSecondUserId(2);
  dialog.setDate("10.07.2021");
  dialog.save();
  dialog.setId(2);
  dialog.setFirstUserId(2);
  dialog.setSecondUserId(1);
  dialog.setDate("10.07.2021");
  dialog.save();
  dialog.setId(1);
  dialog.select_by_id();
  EXPECT_EQ(dialog.getSecondUserId, 2);
}

TEST(MESSAGES_TABLE_TEST, MESSAGE_select_save) {
  MESSAGES msg;
  msg.setMId(1);
  msg.setDialogId(2);
  msg.setSendinUserId(1);
  msg.setReceivingUserId(2);
  msg.setText("Hello");
  msg.setDate("10.07.2021");
  msg.save();
  msg.setDate("01.01.2020");
  msg.select_by_messageId(1);
  ASSERT_STREQ(msg.getDate, "10.07.2021");
}

TEST(USERS_INFO_TABLE_TEST, USERS_INFO_select_save) {
  USERS_INFO user;
  user.setId(1);
  user.setAge(18);
  user.save();
  user.setName("Vasya");
  user.select_by_id(1);
  ASSERT_STREQ(msg.getName(), "");
}

TEST(MARKS_TABLE_TEST, MARKS_select_save) {
    MARKS marks;
    marks.setMarkId(1);
    marks.setId(1);
    marks.setIdOther(2);
    marks.setMark(1);
    marks.setDate("20.12.2020");
    marks.save();
    marks.setMarkId(2);
    marks.setId(2);
    marks.setIdOther(1);
    marks.setMark(-1);
    marks.setDate("21.12.2020");
    marks.select_by_id(1);
    EXPECT_EQ(marks.getMark, 1);
}

TEST(MARKS_TABLE_TEST, MARKS_select_save) {
    MARKS marks;
    marks.setMarkId(1);
    marks.setId(1);
    marks.setIdOther(2);
    marks.setMark(1);
    marks.setDate("20.12.2020");
    marks.save();
    marks.setMarkId(2);
    marks.setId(2);
    marks.setIdOther(1);
    marks.setMark(-1);
    marks.setDate("21.12.2020");
    marks.select_by_id(1);
    EXPECT_EQ(marks.getMark, 1);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
