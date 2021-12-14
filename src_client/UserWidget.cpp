#include "UserWidget.h"
#include <string>
#include "Wt/WProgressBar.h"

std::string ws2str(const std::wstring &wstr) {
    using convert_typeX = std::codecvt_utf8<wchar_t>;
    std::wstring_convert<convert_typeX, wchar_t> converterX;

    return converterX.to_bytes(wstr);
}

UserWidget::UserWidget(Wt::WContainerWidget* mainPageRight, User& user, TinderServer& server) : user(user), server(server), checkAdd(false) {
    createInfoPage(mainPageRight);
}

void UserWidget::createInfoPage(Wt::WContainerWidget* mainPageRight) {
    mainPageRight->clear();
    user.user_image = server.db_.user_image(server.db_.user_id(user.username));

    auto setting = mainPageRight->addWidget(std::make_unique<Wt::WContainerWidget>());
    setting->setStyleClass("aboutMe");

    auto photos = setting->addWidget(std::make_unique<Wt::WContainerWidget>());
    photos->setStyleClass("userPhotos");

    myPhoto = new Wt::WImage*[user.user_image.size()];
    for (size_t i = 0; i < user.user_image.size(); ++i) {
        myPhoto[i] = photos->addWidget(std::make_unique<Wt::WImage>(Wt::WLink(user.user_image[i])));
        myPhoto[i]->setStyleClass("userPhoto");
    }

    auto buttons = setting->addWidget(std::make_unique<Wt::WContainerWidget>());

    addPhoto = buttons->addWidget(std::make_unique<Wt::WFileUpload>());
    addPhoto->setFileTextSize(2048);
    addPhoto->setStyleClass("addPhoto");

    deletePhoto = buttons->addWidget(std::make_unique<Wt::WPushButton>("Удалить фото"));
    deletePhoto->setStyleClass("delete");

    auto deletedPhoto = setting->addWidget(std::make_unique<Wt::WText>());
    deletedPhoto->hide();

    deletePhoto->clicked().connect([=] {
        myPhoto[user.user_image.size() - 1]->hide();
        int id = server.db_.user_id(user.username);
        server.db_.delete_image(id, "");
        std::string rename = "mv ../users_images/profilePhoto" + std::to_string(id) + std::to_string(user.user_image.size() - 1) + " ../users_images/deleted";
        system(rename.c_str());
        std::string deleteP = "rm ../users_images/deleted";
        system(deleteP.c_str());
        user.user_image.pop_back();
        deletedPhoto->setText("Нажмите на сохранить внизу для удалении фотографии");
        deletedPhoto->setStyleClass("valid");
        deletedPhoto->show();
    });

    savePhoto = setting->addWidget(std::make_unique<Wt::WPushButton>("Начать загрузку фото"));
    savePhoto->setStyleClass("save");

    if (user.user_image.size() == 4) {
        addPhoto->hide();
        savePhoto->hide();
    }

    auto outPhoto = setting->addWidget(std::make_unique<Wt::WText>());
    outPhoto->hide();

    savePhoto->clicked().connect([=] {
        checkAdd = true;
        addPhoto->upload();
        outPhoto->setText("Загрузка фото успешно началась. Чтобы добавить фото, нажмите Сохранить внизу");
        outPhoto->show();
        outPhoto->setStyleClass("valid");
    });

    nameText = setting->addWidget(std::make_unique<Wt::WText>("Ваше имя"));
    nameText->setStyleClass("textSetting");
    nameEdit = setting->addWidget(std::make_unique<Wt::WLineEdit>());
    nameEdit->setPlaceholderText("Можете поменять свое имя");
    nameEdit->setValueText(user.name);
    nameEdit->setStyleClass("lineSetting");

    ageText = setting->addWidget(std::make_unique<Wt::WText>("Ваш возраст"));
    ageText->setStyleClass("textSetting");
    ageEdit = setting->addWidget(std::make_unique<Wt::WLineEdit>());
    ageEdit->setPlaceholderText("Можете поменять свой возраст");
    ageEdit->setValueText(std::to_string(user.age));
    ageEdit->setStyleClass("lineSetting");

    auto validatorAge = std::make_shared<Wt::WIntValidator>(18, 100);
    validatorAge->setMandatory(true);
    ageEdit->setValidator(validatorAge);

    genderText = setting->addWidget(std::make_unique<Wt::WText>("Ваш пол"));
    genderText->setStyleClass("textSetting");
    genderEdit = setting->addWidget(std::make_unique<Wt::WLineEdit>());
    genderEdit->setPlaceholderText("Можете поменять свой пол, только ЗАЧЕМ!");
    genderEdit->setValueText(user.gender);
    genderEdit->setStyleClass("lineSetting");

    discText = setting->addWidget(std::make_unique<Wt::WText>("Расскажите о себе"));
    discText->setStyleClass("textSetting");
    discEdit = setting->addWidget(std::make_unique<Wt::WTextArea>());
    discEdit->setPlaceholderText("Не стесняйся, напиши что-нибудь!");
    discEdit->setValueText(user.description);
    discEdit->setColumns(40);
    discEdit->setRows(5);
    discEdit->setStyleClass("discSetting");

    facText = setting->addWidget(std::make_unique<Wt::WText>("Ваш факультет"));
    facText->setStyleClass("textSetting");
    facEdit = setting->addWidget(std::make_unique<Wt::WLineEdit>());
    facEdit->setPlaceholderText("Можете поменять свой факультет");
    facEdit->setValueText(user.faculty);
    facEdit->setStyleClass("lineSetting");

    courseText = setting->addWidget(std::make_unique<Wt::WText>("Ваш курс"));
    courseText->setStyleClass("textSetting");
    courseEdit = setting->addWidget(std::make_unique<Wt::WLineEdit>());
    courseEdit->setPlaceholderText("Можете поменять свой курс");
    courseEdit->setValueText(std::to_string(user.course_number));
    courseEdit->setStyleClass("lineSetting");

    netText = setting->addWidget(std::make_unique<Wt::WText>("Ваша ссылка на ВК"));
    netText->setStyleClass("textSetting");
    netEdit = setting->addWidget(std::make_unique<Wt::WLineEdit>());
    netEdit->setPlaceholderText("Можете поменять ссылку на ВК");
    netEdit->setValueText(user.vk_link);
    netEdit->setStyleClass("lineSetting");

    tgText = setting->addWidget(std::make_unique<Wt::WText>("Ваша ссылка на Телеграмм"));
    tgText->setStyleClass("textSetting");
    tgEdit = setting->addWidget(std::make_unique<Wt::WLineEdit>());
    tgEdit->setPlaceholderText("Можете поменять ссылку на Телеграмм");
    tgEdit->setValueText(user.telegram_link);
    tgEdit->setStyleClass("lineSetting");

    auto outAge = setting->addWidget(std::make_unique<Wt::WText>());
    outAge->hide();

    auto outAdd = setting->addWidget(std::make_unique<Wt::WText>());
    outAdd->hide();

    auto success = setting->addWidget(std::make_unique<Wt::WText>());
    success->hide();

    saveData = setting->addWidget(std::make_unique<Wt::WPushButton>("Сохранить изменения"));
    saveData->setStyleClass("info buttonSetting");

    bool checkAge = false;
    addPhoto->fileTooLarge().connect([=] {
        outAdd->show();
        outAdd->setText("Файл слишком большой");
        outAdd->setStyleClass("invalid");
    });

    saveData->clicked().connect([=, &checkAge] {
        addPhoto->upload();
        std::string mFilename = addPhoto->spoolFileName();
        user.user_image.push_back(mFilename);

        if (ageEdit->validate() == Wt::ValidationState::Invalid) {
            outAge->show();
            outAge->setText("Только с 18 лет");
            outAge->setStyleClass("invalid");
        } else {
            checkAge = true;
        }

        if (checkAge) {
            user.name = ws2str(nameEdit->text());
            user.age = std::stoi(ws2str(ageEdit->text()));
            user.gender = ws2str(genderEdit->text());
            user.description = ws2str(discEdit->text());
            user.faculty = ws2str(facEdit->text());
            user.course_number = std::stoi(ws2str(courseEdit->text()));
            user.telegram_link = ws2str(tgEdit->text());
            user.vk_link = ws2str(netEdit->text());
            int id = server.db_.user_id(user.username);

            USERS_INFO usersInfo;
            usersInfo.user_id = id;
            usersInfo.age = user.age;
            usersInfo.name = user.name;
            usersInfo.faculty = user.faculty;
            usersInfo.course_number = user.course_number;
            usersInfo.vk_link = user.vk_link;
            usersInfo.telegram_link = user.telegram_link;
            usersInfo.description = user.description;
            usersInfo.gender = user.gender;
            if (checkAdd) {
                std::string command = "mkdir -p ../users_images";
                system(command.c_str());
                command = "mv " + user.user_image[user.user_image.size() - 1] + " ../users_images";
                system(command.c_str());
                std::filesystem::path p(user.user_image[user.user_image.size() - 1]);
                command = "mv ../users_images/" + string(p.stem()) + " ../users_images/profilePhoto" +
                          std::to_string(usersInfo.user_id) + std::to_string(user.user_image.size() - 1);
                system(command.c_str());
                server.db_.save_image("../users_images/profilePhoto" +
                                      std::to_string(usersInfo.user_id) + std::to_string(user.user_image.size() - 1), usersInfo.user_id, "profilePhoto" +
                                                                                                                                         std::to_string(usersInfo.user_id) + std::to_string(user.user_image.size() - 1));
            }
            server.db_.save_user(usersInfo);
            outAdd->show();
            outAdd->setText("Настройки успешно изменены");
            outAdd->setStyleClass("valid");
            checkAdd = false;
        }
        delete [] myPhoto;
        createInfoPage(mainPageRight);
    });

    back = mainPageRight->addWidget(std::make_unique<Wt::WPushButton>("Вернуться к поиску"));
    back->setStyleClass("info");
    back->setLink(Wt::WLink(Wt::LinkType::InternalPath, "/start"));
}