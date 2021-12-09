#include "UserWidget.h"

std::string ws2s(const std::wstring &wstr) {
    using convert_typeX = std::codecvt_utf8<wchar_t>;
    std::wstring_convert<convert_typeX, wchar_t> converterX;

    return converterX.to_bytes(wstr);
}

UserWidget::UserWidget(Wt::WContainerWidget* mainPageRight, User& user, const Postgre_DB& db) : user(user) {
    createInfoPage(mainPageRight, db);
}

void UserWidget::createInfoPage(Wt::WContainerWidget* mainPageRight, Postgre_DB db) {
    mainPageRight->clear();

    auto setting = mainPageRight->addWidget(std::make_unique<Wt::WContainerWidget>());
    setting->setStyleClass("aboutMe");

    auto photos = setting->addWidget(std::make_unique<Wt::WContainerWidget>());
    photos->setStyleClass("userPhotos");

    myPhoto = photos->addWidget(std::make_unique<Wt::WImage>(Wt::WLink("../css/Me.jpg")));
    myPhoto->setStyleClass("userPhoto");

    auto buttons = setting->addWidget(std::make_unique<Wt::WContainerWidget>());

    addPhoto = buttons->addWidget(std::make_unique<Wt::WFileUpload>());
    addPhoto->setFileTextSize(512);
    addPhoto->setStyleClass("addPhoto");

    deletePhoto = buttons->addWidget(std::make_unique<Wt::WPushButton>("Удалить фото"));
    deletePhoto->setStyleClass("delete");
    deletePhoto->clicked().connect([=] {
        myPhoto->hide();
    });

    ageText = setting->addWidget(std::make_unique<Wt::WText>("Ваш возраст"));
    ageText->setStyleClass("textSetting");
    ageEdit = setting->addWidget(std::make_unique<Wt::WLineEdit>());
    ageEdit->setPlaceholderText("Можете поменять свой возраст");
    ageEdit->setValueText(std::to_string(user.age));
    ageEdit->setStyleClass("lineSetting");

    auto validatorAge = std::make_shared<Wt::WIntValidator>(18, 100);
    validatorAge->setMandatory(true);
    ageEdit->setValidator(validatorAge);

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

    passText = setting->addWidget(std::make_unique<Wt::WText>("Ваш пароль"));
    passText->setStyleClass("textSetting");
    passEdit = setting->addWidget(std::make_unique<Wt::WLineEdit>());
    passEdit->setEchoMode(Wt::EchoMode::Password);
    passEdit->setPlaceholderText("Можете поменять ваш пароль");
    passEdit->setValueText(user.password);
    passEdit->setStyleClass("lineSetting");

    passTwoText = setting->addWidget(std::make_unique<Wt::WText>("Повторите пароль"));
    passTwoText->setStyleClass("textSetting");
    passTwoEdit = setting->addWidget(std::make_unique<Wt::WLineEdit>());
    passTwoEdit->setEchoMode(Wt::EchoMode::Password);
    passTwoEdit->setStyleClass("lineSetting");

    auto validatorPassTwo = std::make_shared<Wt::WValidator>();
    validatorPassTwo->setMandatory(true);
    passTwoEdit->setValidator(validatorPassTwo);

    auto outAge = setting->addWidget(std::make_unique<Wt::WText>());
    outAge->hide();

    auto outPassTwo = setting->addWidget(std::make_unique<Wt::WText>());
    outPassTwo->hide();

    auto outAdd = setting->addWidget(std::make_unique<Wt::WText>());
    outAdd->hide();

    saveData = setting->addWidget(std::make_unique<Wt::WPushButton>("Сохранить изменения"));
    saveData->setStyleClass("info buttonSetting");

    bool checkAge = false;
    bool checkPass = false;
    addPhoto->fileTooLarge().connect([=] {
        outAdd->show();
        outAdd->setText("Файл слишком большой");
        outAdd->setStyleClass("invalid");
    });

    saveData->clicked().connect([&] {
        if (addPhoto->canUpload()) {
            addPhoto->upload();
            outAdd->hide();
        }
        if (ageEdit->validate() == Wt::ValidationState::Invalid) {
            outAge->show();
            outAge->setText("Только с 18 лет");
            outAge->setStyleClass("invalid");
        } else {
            outAge->hide();
            checkAge = true;
        }

        if (passTwoEdit->validate() == Wt::ValidationState::InvalidEmpty) {
            outPassTwo->show();
            outPassTwo->setText("Повторите пароль!");
            outPassTwo->setStyleClass("invalid");
        } else {
            if (passEdit->valueText() != passTwoEdit->valueText()) {
                outPassTwo->show();
                outPassTwo->setText("Пароли не совпадают");
                outPassTwo->setStyleClass("invalid");
            } else {
                outPassTwo->hide();
                checkPass = true;
            }
        }
        if (checkAge && checkPass) {
            user.age = std::stoi(ws2s(ageEdit->text()));
            user.description = ws2s(discEdit->text());
            user.faculty = ws2s(facEdit->text());
            user.course_number = std::stoi(ws2s(courseEdit->text()));
            user.telegram_link = ws2s(tgEdit->text());
            user.vk_link = ws2s(netEdit->text());
            int id = db.user_id(user.username);

            USERS_INFO usersInfo;
            usersInfo.age = user.age;
            usersInfo.faculty = user.faculty;
            usersInfo.course_number = user.course_number;
            usersInfo.vk_link = user.vk_link;
            usersInfo.telegram_link = user.telegram_link;
            usersInfo.description = user.description;
            //db.save_image();
            db.save_user(usersInfo);
            saveData->setLink(Wt::WLink(Wt::LinkType::InternalPath, "/start"));
        }
    });

    back = mainPageRight->addWidget(std::make_unique<Wt::WPushButton>("Вернуться к поиску"));
    back->setStyleClass("info");
    back->setLink(Wt::WLink(Wt::LinkType::InternalPath, "/start"));
}