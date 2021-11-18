#include <gtest/gtest.h>
#include "DataBase.h"
#include "DIALOGS.h"
#include "MARKS.h"
#include "PHOTOS.h"
#include "USERS_INFO.h"
#include "USERS_REC.h"

TEST(DIALOGS_TEST, DIALOGS_set_get) {
  DIALOGS dialog;
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
  DIALOGS dialog;
  dialog.connect("", "", "");
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
  dialog.select_by_dialogId();
  EXPECT_EQ(dialog.getSecondUserId, 2);
  dialog.close_connection();
}

TEST(MESSAGES_TABLE_TEST, MESSAGE_select_save) {
  MESSAGES msg;
  msg.connect("", "", "");
  msg.setMId(1);
  msg.setDialogId(2);
  msg.setSendinUserId(1);
  msg.setReceivingUserId(2);
  msg.setText("Hello");
  msg.setDate("10.07.2021");
  msg.save();
  msg.setDate("01.01.2020");
  msg.setMId(1);
  msg.select_by_messageId();
  ASSERT_STREQ(msg.getDate, "10.07.2021");
  msg.close_connection();
}

TEST(USERS_INFO_TABLE_TEST, USERS_INFO_select_save) {
  USERS_INFO user;
  user.close_connection("", "", "");
  user.setId(1);
  user.setAge(18);
  user.save();
  user.setName("Vasya");
  user.setId(1);
  user.select_by_id();
  ASSERT_STREQ(msg.getName(), "");
  user.close_connection();
}

TEST(MARKS_TABLE_TEST, MARKS_select_save) {
    MARKS marks;
    marks.connect("", "", "");
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
    marks.setMarkId(1);
    marks.select_by_id();
    EXPECT_EQ(marks.getMark, 1);
    marks.close_connection();
}

TEST(PHOTOS_TABLE_TEST, PHOTOS_select_save) {
    PHOTOS photos;
    photos.connect("", "", "");
    photos.setPhotoId(1);
    photos.setUserId(1);
    photos.setDate("10.10.2020");
    photos.save();
    photos.setPhotoId(2);
    photos.setUserId(2);
    photos.setDate("11.10.2020");
    photos.save();
    photos.setPhotoId(1);
    photos.select_by_photoId();
    EXPECT_EQ(photos.getUserId, 1);
    photos.close_connection();
}

TEST(USERS_INFO_TABLE_TEST, USERS_INFO_delete) {
  USERS_INFO user;
  user.close_connection("", "", "");
  user.setId(1);
  user.setAge(18);
  user.save();
  user.delete_by_id();
  user.select_by_id();
  ASSERT_STREQ(msg.getId(), 0);
  user.close_connection();
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
