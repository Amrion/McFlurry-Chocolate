#ifndef MCFLURRY_CHOCOLATE_USER_H
#define MCFLURRY_CHOCOLATE_USER_H

#include <Wt/Dbo/Types.h>
#include <Wt/Dbo/WtSqlTraits.h>
#include <Wt/Auth/Dbo/AuthInfo.h>

#include <string>

using namespace Wt;

namespace dbo = Wt::Dbo;

class User;
typedef Auth::Dbo::AuthInfo<User> AuthInfo;
typedef dbo::collection< dbo::ptr<User> > Users;

class User
{
public:
    User();

    std::string name; /* a copy of auth info's user name */
    std::string surname;
    int age;
    std::string gender;
    std::string faculty;
    int course_number;
    std::string vk_link;
    std::string telegram_link;
    std::string description;
    dbo::collection<dbo::ptr<AuthInfo>> authInfos;

    template<class Action>
    void persist(Action& a)
    {
        dbo::field(a, name, "name");
        dbo::field(a, surname, "surname");
        dbo::field(a, age, "age");
        dbo::field(a, gender, "gender");
        dbo::field(a, faculty, "faculty");
        dbo::field(a, course_number, "course_number");
        dbo::field(a, vk_link, "vk_link");
        dbo::field(a, telegram_link, "telegram_link");
        dbo::field(a, description, "description");

        dbo::hasMany(a, authInfos, dbo::ManyToOne, "user");
    }
};

DBO_EXTERN_TEMPLATES(User);

#endif //MCFLURRY_CHOCOLATE_USER_H
