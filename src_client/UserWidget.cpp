#include "UserWidget.h"

UserWidget::UserWidget(Wt::WContainerWidget* mainPageRight) {
    createInfoPage(mainPageRight);
}

void UserWidget::createInfoPage(Wt::WContainerWidget* mainPageRight) {
    mainPageRight->clear();

    auto setting = mainPageRight->addWidget(std::make_unique<Wt::WContainerWidget>());
    setting->setStyleClass("aboutMe");

    auto photos = setting->addWidget(std::make_unique<Wt::WContainerWidget>());
    photos->setStyleClass("userPhotos");

    myPhoto = photos->addWidget(std::make_unique<Wt::WImage>(Wt::WLink("../css/Me.jpg")));
    myPhoto->setStyleClass("userPhoto");
    auto emptyPhoto = photos->addWidget(std::make_unique<Wt::WContainerWidget>());
    emptyPhoto->setStyleClass("empty");
    emptyPhoto = photos->addWidget(std::make_unique<Wt::WContainerWidget>());
    emptyPhoto->setStyleClass("empty");
    emptyPhoto = photos->addWidget(std::make_unique<Wt::WContainerWidget>());
    emptyPhoto->setStyleClass("empty");

    addPhoto = setting->addWidget(std::make_unique<Wt::WFileUpload>());
    addPhoto->setFileTextSize(500);
    addPhoto->setStyleClass("addPhoto");

    ageText = setting->addWidget(std::make_unique<Wt::WText>("Ваш возраст"));
    ageText->setStyleClass("textSetting");
    ageEdit = setting->addWidget(std::make_unique<Wt::WLineEdit>());
    ageEdit->setPlaceholderText("Можете поменять свой возраст");
    ageEdit->setValueText("19");
    ageEdit->setStyleClass("lineSetting");

    auto validatorAge = std::make_shared<Wt::WIntValidator>(18, 100);
    validatorAge->setMandatory(true);
    ageEdit->setValidator(validatorAge);

    discText = setting->addWidget(std::make_unique<Wt::WText>("Расскажите о себе"));
    discText->setStyleClass("textSetting");
    discEdit = setting->addWidget(std::make_unique<Wt::WTextArea>());
    discEdit->setPlaceholderText("Не стесняйся, напиши что-нибудь!");
    discEdit->setValueText("Я Даня, учусь в Бомонке, вот и все");
    discEdit->setColumns(40);
    discEdit->setRows(5);
    discEdit->setStyleClass("discSetting");

    netText = setting->addWidget(std::make_unique<Wt::WText>("Ваша социальная сеть"));
    netText->setStyleClass("textSetting");
    netEdit = setting->addWidget(std::make_unique<Wt::WLineEdit>());
    netEdit->setPlaceholderText("Можете поменять соц. сеть");
    netEdit->setValueText("Мой вк - https://vk.com/dtarnovsky");
    netEdit->setStyleClass("lineSetting");

    passText = setting->addWidget(std::make_unique<Wt::WText>("Ваш пароль"));
    passText->setStyleClass("textSetting");
    passEdit = setting->addWidget(std::make_unique<Wt::WLineEdit>());
    passEdit->setEchoMode(Wt::EchoMode::Password);
    passEdit->setPlaceholderText("Можете поменять ваш пароль");
    passEdit->setValueText("1qaz2wsx3edc");
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

    saveData = setting->addWidget(std::make_unique<Wt::WPushButton>("Сохранить изменения"));
    saveData->setStyleClass("info buttonSetting");

    saveData->clicked().connect([=] {
        if (ageEdit->validate() == Wt::ValidationState::Invalid) {
            outAge->show();
            outAge->setInline(true);
            outAge->setText("Только с 18 лет");
            outAge->setStyleClass("invalid");
        } else {
            outAge->hide();
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
            }
        }
    });

    back = mainPageRight->addWidget(std::make_unique<Wt::WPushButton>("Вернуться к поиску"));
    back->setStyleClass("info");
    back->setLink(Wt::WLink(Wt::LinkType::InternalPath, "/start"));
}