#include <Wt/WApplication.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WEnvironment.h>
#include <Wt/WInPlaceEdit.h>
#include <Wt/WHBoxLayout.h>
#include <Wt/WVBoxLayout.h>
#include <Wt/WLabel.h>
#include <Wt/WLineEdit.h>
#include <Wt/WTemplate.h>
#include <Wt/WText.h>
#include <Wt/WTextArea.h>
#include <Wt/WPushButton.h>
#include <Wt/WRadioButton.h>
#include <Wt/WFileUpload.h>
#include <Wt/WIntValidator.h>

#include <chrono>
#include <codecvt>

#include "TinderWidget.hpp"
#include "MainPageWidget.h"


std::string ws2s(const std::wstring &wstr) {
    using convert_typeX = std::codecvt_utf8<wchar_t>;
    std::wstring_convert<convert_typeX, wchar_t> converterX;

    return converterX.to_bytes(wstr);
}

TinderWidget::TinderWidget(TinderServer &server, TinderApplication* app)
        : WContainerWidget(),
          app(app),
          server_(server),
          loggedIn_(false),
          user_(User())
           {

    letLogin();
}

void TinderWidget::letSignUp() {
    clear();

    auto vLayout = setLayout(std::make_unique<Wt::WVBoxLayout>());


    auto hLayout = std::make_unique<Wt::WHBoxLayout>();


    auto container = hLayout->addWidget(std::make_unique<Wt::WContainerWidget>(), 1);

    avatar_ = container->addNew<Wt::WFileUpload>();
    avatar_->setFileTextSize(150); // Set the maximum file size to 50 kB.
    avatar_->setMargin(10, Wt::Side::Right);

    avatar_->changed().connect([this] {
        isImageEmpty = false;
        isChanged = true;
    });

    vLayout->addLayout(std::move(hLayout), 0, Wt::AlignmentFlag::Center);

    hLayout = std::make_unique<Wt::WHBoxLayout>();

    hLayout->addWidget(std::make_unique<Wt::WLabel>("Имя:"), 1);

    nameEdit_ = hLayout->addWidget(std::make_unique<Wt::WLineEdit>(), 1);
    nameEdit_->setPlaceholderText("Иван");
    nameEdit_->setFocus();

    vLayout->addLayout(std::move(hLayout), 0, Wt::AlignmentFlag::Center);

    hLayout = std::make_unique<Wt::WHBoxLayout>();

    hLayout->addWidget(std::make_unique<Wt::WLabel>("Фамилия:"), 1);

    surnameEdit_ = hLayout->addWidget(std::make_unique<Wt::WLineEdit>(), 1);
    surnameEdit_->setPlaceholderText("Иванов");
    surnameEdit_->setFocus();

    vLayout->addLayout(std::move(hLayout), 0, Wt::AlignmentFlag::Center);

    hLayout = std::make_unique<Wt::WHBoxLayout>();
    hLayout->addWidget(std::make_unique<Wt::WLabel>("Пол:"), 1);

    container = hLayout->addWidget(std::make_unique<Wt::WContainerWidget>(), 1);
    auto group = std::make_shared<Wt::WButtonGroup>();
    Wt::WRadioButton *rb;

    rb = container->addNew<Wt::WRadioButton>("Мужской");
    rb->setInline(false);
    group->addButton(rb, 1);

    rb = container->addNew<Wt::WRadioButton>("Женский");
    rb->setInline(false);
    group->addButton(rb, 2);

    group->setSelectedButtonIndex(0);

    genderBtn_ = group->checkedButton();

    vLayout->addLayout(std::move(hLayout), 0, Wt::AlignmentFlag::Center);
    
    group->checkedChanged().connect([this] (Wt::WRadioButton *selection) {
        genderBtn_ = selection;
    });

    hLayout = std::make_unique<Wt::WHBoxLayout>();

    hLayout->addWidget(std::make_unique<Wt::WLabel>("Возраст:"), 1);

    ageEdit_ = hLayout->addWidget(std::make_unique<Wt::WLineEdit>(), 1);
    ageEdit_->setPlaceholderText("20");
    ageEdit_->setFocus();

    vLayout->addLayout(std::move(hLayout), 0, Wt::AlignmentFlag::Center);

    hLayout = std::make_unique<Wt::WHBoxLayout>();

    hLayout->addWidget(std::make_unique<Wt::WLabel>("Факультет:"), 1);

    facultyEdit_ = hLayout->addWidget(std::make_unique<Wt::WLineEdit>(), 1);
    facultyEdit_->setPlaceholderText("ИУ5");
    facultyEdit_->setFocus();

    vLayout->addLayout(std::move(hLayout), 0, Wt::AlignmentFlag::Center);

    hLayout = std::make_unique<Wt::WHBoxLayout>();

    hLayout->addWidget(std::make_unique<Wt::WLabel>("Курс:"), 1);

    courseNumberEdit_ = hLayout->addWidget(std::make_unique<Wt::WLineEdit>(), 1);
    courseNumberEdit_->setPlaceholderText("2");
    courseNumberEdit_->setFocus();

    vLayout->addLayout(std::move(hLayout), 0, Wt::AlignmentFlag::Center);

    hLayout = std::make_unique<Wt::WHBoxLayout>();

    hLayout->addWidget(std::make_unique<Wt::WLabel>("VK:"), 1);

    vkLinkEdit_ = hLayout->addWidget(std::make_unique<Wt::WLineEdit>(), 1);
    vkLinkEdit_->setPlaceholderText("VK");
    vkLinkEdit_->setFocus();

    vLayout->addLayout(std::move(hLayout), 0, Wt::AlignmentFlag::Center);

    hLayout = std::make_unique<Wt::WHBoxLayout>();

    hLayout->addWidget(std::make_unique<Wt::WLabel>("Telegram:"), 1);

    telegramEdit_ = hLayout->addWidget(std::make_unique<Wt::WLineEdit>(), 1);
    telegramEdit_->setPlaceholderText("Telegram");
    telegramEdit_->setFocus();

    vLayout->addLayout(std::move(hLayout), 0, Wt::AlignmentFlag::Center);

    hLayout = std::make_unique<Wt::WHBoxLayout>();

    hLayout->addWidget(std::make_unique<Wt::WLabel>("Расскажи о себе:"), 1);

    descriptionEdit_ = hLayout->addWidget(std::make_unique<Wt::WTextArea>(), 1);
    descriptionEdit_->setPlaceholderText("Не стесняйся, напиши что-нибудь!");
    descriptionEdit_->setColumns(40);
    descriptionEdit_->setRows(5);
    descriptionEdit_->setFocus();

    vLayout->addLayout(std::move(hLayout), 0, Wt::AlignmentFlag::Center);

    hLayout = std::make_unique<Wt::WHBoxLayout>();

    hLayout->addWidget(std::make_unique<Wt::WLabel>("Логин:"), 1);

    userLoginEdit_ = hLayout->addWidget(std::make_unique<Wt::WLineEdit>(), 1);
    userLoginEdit_->setPlaceholderText("Логин");
    userLoginEdit_->setFocus();

    vLayout->addLayout(std::move(hLayout), 0, Wt::AlignmentFlag::Center);


    hLayout = std::make_unique<Wt::WHBoxLayout>();

    hLayout->addWidget(std::make_unique<Wt::WLabel>("Пароль:"), 1);

    passwordEdit_ = hLayout->addWidget(std::make_unique<Wt::WLineEdit>(), 1);
    passwordEdit_->setPlaceholderText("Пароль");
    passwordEdit_->setAttributeValue("type", "password");

    vLayout->addLayout(std::move(hLayout), 0, Wt::AlignmentFlag::Center);


    hLayout = std::make_unique<Wt::WHBoxLayout>();

    hLayout->addWidget(std::make_unique<Wt::WLabel>("Повторите пароль:"), 1);

    confirmPasswordEdit_ = hLayout->addWidget(std::make_unique<Wt::WLineEdit>(), 1);
    confirmPasswordEdit_->setPlaceholderText("Повторите пароль");
    confirmPasswordEdit_->setAttributeValue("type", "password");

    vLayout->addLayout(std::move(hLayout), 0, Wt::AlignmentFlag::Center);


    auto signUp = vLayout->addWidget(std::make_unique<Wt::WPushButton>("Зарегистрироваться"), 0, Wt::AlignmentFlag::Center);

    signUp->clicked().connect(this, &TinderWidget::signUp);

    userLoginEdit_->enterPressed().connect(this, [&] {
        passwordEdit_->setFocus();
    });
    passwordEdit_->enterPressed().connect(this, [&] {
        confirmPasswordEdit_->setFocus();
    });
    confirmPasswordEdit_->enterPressed().connect(this, &TinderWidget::signUp);


    auto logIn = vLayout->addWidget(std::make_unique<Wt::WText>("Войти"), 0, Wt::AlignmentFlag::Center);
    logIn->setStyleClass("text-link");
    logIn->clicked().connect(this, &TinderWidget::letLogin);

    statusMsg_ = vLayout->addWidget(std::make_unique<Wt::WText>(), 1, Wt::AlignmentFlag::Center);
    statusMsg_->setTextFormat(Wt::TextFormat::Plain);
}

void TinderWidget::letLogin() {
    auto cookie = app->environment().getCookie("userToken");
    if (cookie == 0 || !cookie || cookie->empty()) {
        clear();

        auto vLayout = setLayout(std::make_unique<Wt::WVBoxLayout>());


        auto hLayout = std::make_unique<Wt::WHBoxLayout>();

        hLayout->addWidget(std::make_unique<Wt::WLabel>("Логин:"), 1);

        userLoginEdit_ = hLayout->addWidget(std::make_unique<Wt::WLineEdit>(), 1);
        userLoginEdit_->setPlaceholderText("Логин");

        vLayout->addLayout(std::move(hLayout), 0, Wt::AlignmentFlag::Center);


        hLayout = std::make_unique<Wt::WHBoxLayout>();

        hLayout->addWidget(std::make_unique<Wt::WLabel>("Пароль:"), 1);

        passwordEdit_ = hLayout->addWidget(std::make_unique<Wt::WLineEdit>(), 1);
        passwordEdit_->setPlaceholderText("Пароль");
        passwordEdit_->setAttributeValue("type", "password");

        vLayout->addLayout(std::move(hLayout), 0, Wt::AlignmentFlag::Center);


        auto logIn = vLayout->addWidget(std::make_unique<Wt::WPushButton>("Войти"), 0, Wt::AlignmentFlag::Center);

        logIn->clicked().connect(this, &TinderWidget::login);
        userLoginEdit_->enterPressed().connect(this, [&] {
            passwordEdit_->setFocus();
        });
        passwordEdit_->enterPressed().connect(this, &TinderWidget::login);


        auto signUp = vLayout->addWidget(std::make_unique<Wt::WText>("Зарегистрироваться"), 0, Wt::AlignmentFlag::Center);
        signUp->setStyleClass("text-link");
        signUp->clicked().connect(this, &TinderWidget::letSignUp);

        statusMsg_ = vLayout->addWidget(std::make_unique<Wt::WText>(), 1, Wt::AlignmentFlag::Center);
        statusMsg_->setTextFormat(Wt::TextFormat::Plain);
    } else {
        app->setInternalPath("/", true);

        loggedIn_ = true;

        USERS_INFO usersInfo;
        usersInfo = server_.db_.user_info(*cookie);

        user_ = User();
        user_.username = *cookie;
        user_.name = usersInfo.name;
        user_.surname = usersInfo.surname;
        user_.age = usersInfo.age;
        user_.gender = usersInfo.gender;
        user_.faculty = usersInfo.faculty;
        user_.course_number = usersInfo.course_number;
        user_.num_pairs = usersInfo.num_pairs;
        user_.vk_link = usersInfo.vk_link;
        user_.telegram_link = usersInfo.telegram_link;
        user_.description = usersInfo.description;
        user_.rec_users = server_.db_.user_rec(*cookie);
        user_.user_image = server_.db_.user_image(server_.db_.user_id(*cookie));
        addWidget(std::make_unique<MainPageWidget>(user_,server_, app, this));
    }
}

void TinderWidget::logout() {
    if (loggedIn()) {
        app->removeCookie("userToken");
        loggedIn_ = false;
        isImageEmpty = true;

        server_.logout(user_);

        letLogin();
    }
}

bool TinderWidget::loggedIn() const {
    return loggedIn_;
}

void TinderWidget::signUp() {
    if (loggedIn()) {
        return;
    }

//    std::string avatar;

    std::string username = ws2s(userLoginEdit_->text());
    std::string password = ws2s(passwordEdit_->text());
    std::string confirmPassword = ws2s(confirmPasswordEdit_->text());
    std::string name = ws2s(nameEdit_->text());
    std::string surname = ws2s(surnameEdit_->text());
    std::string faculty = ws2s(facultyEdit_->text());
    std::string courseNumber = ws2s(courseNumberEdit_->text());
    std::string vkLink = ws2s(vkLinkEdit_->text());
    std::string telegram = ws2s(telegramEdit_->text());
    std::string description = ws2s(descriptionEdit_->text());
    std::string gender = ws2s(genderBtn_->text());
    std::string  age = ws2s(ageEdit_->text());

    if (password.empty() || username.empty() || name.empty() || surname.empty() || faculty.empty() ||
        courseNumber.empty() || vkLink.empty() || telegram.empty() || description.empty() || isImageEmpty) {
        statusMsg_->setText("Все поля должны быть заполнены");
        return;
    }


    avatar_->fileTooLarge().connect([=] {
        statusMsg_->setText("Фото слишком большое");
        return;
    });


    if (std::stoi(age) < 18) {
        statusMsg_->setText("Возраст должен быть больше 18");
        return;
    }
    if (password != confirmPassword) {
        statusMsg_->setText("Пароли не совпадают");
        return;
    }

    if (!isImageEmpty) {
        avatar_->upload();
    }
//    user_ = User();

    user_.description = description;
    user_.faculty = faculty;
    user_.surname = surname;
    user_.name = name;
    user_.gender = gender;
    user_.age = std::stoi(age);
    user_.course_number = std::stoi(courseNumber);
    user_.vk_link = vkLink;
    user_.telegram_link = telegram;
    user_.username = username;
    user_.password = password;

    avatar_->uploaded().connect([this] {
        if (isChanged) {
            user_.user_image.push_back(avatar_->spoolFileName());
            isChanged = false;
        }

        if (server_.signUp(user_)) {
            login();
        } else {
            statusMsg_->setText("Это имя уже используется");
        }
    });
}

void TinderWidget::login() {
    if (loggedIn()) {
        return;
    }

    std::string username = ws2s(userLoginEdit_->text());
    std::string password = ws2s(passwordEdit_->text());

//    user_ = User();
    user_.username = username;
    user_.password = password;

    if (server_.login(user_)) {
        app->setCookie("userToken", user_.username, 604800);
        loggedIn_ = true;
        clear();
        addWidget(std::make_unique<MainPageWidget>(user_,server_, app, this));
    } else {
        statusMsg_->setText("Неверный логин или пароль");
    }
}

