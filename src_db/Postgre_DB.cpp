#include "Postgre_DB.h"
using namespace std;
Postgre_DB::Postgre_DB(std::string host, std::string port, std::string db_name, std::string user, std::string password) {
    std::string request = "dbname=" + db_name + " user=" + user + " password=" + password + " host=" + host + " port=" + port;
    try
    {
        PG_conn = std::make_shared <connection>(request);
        if (!PG_conn->is_open()) {
            cerr << "Can't open database" << endl;
        }
    }
    catch (const std::exception &e)
    {
        cerr << e.what() << std::endl;
    }
    init_tables();
}

Postgre_DB::~Postgre_DB() {
    if (PG_conn->is_open()) {
        PG_conn->close();
    }
}

std::string Postgre_DB::remove_danger_characters(const std::string & row_column) {
    std::string prep_column = "";
    for (auto i : row_column) {
        if (i != '\'' and i != '\"') prep_column += i;
    }
    return prep_column;
}

result Postgre_DB::select(const std::string table, std::string where, std::vector <std::string> what) {
    std::string request = "SELECT ";
    if (what.size() > 0) {
        for (std::size_t i = 0; i < what.size(); ++i) {
            request += remove_danger_characters(what[i]) + ", ";
        }
        request = request.substr(0, request.size() - 2);
    }
    else {
        request += "*";
    }
    request += " FROM " + table;
    if (where != "") {
        request += " WHERE " + where;
    }
    request += ";";
    nontransaction N(*PG_conn);
    result res = N.exec(request);
    N.commit();
    return res;
}

int Postgre_DB::max_id(const std::string & table, std::string name_id) {
    result res = select(table);
    if (res.begin() == res.end()) {
        res.clear();
        return -1;
    }
    else {
        res.clear();
        std::vector <std::string> column;
        column.push_back("MAX(" + name_id + ")");
        result res = select(table, "", column);
        result::const_iterator c = res.begin();
        int m = c[0].as<int>();
        res.clear();
        return m;
    }
}

int Postgre_DB::insert(const std::string & table, std::vector <std::string> values) {
    work N(*PG_conn);
    std::string request;
    try {
        request = "INSERT INTO " + table + " VALUES('";
        for (size_t i = 0; i < values.size(); ++i) {
            request += remove_danger_characters(values[i]) + "', '";
        }
        request = request.substr(0, request.size() - 3);
        request += ");";
        N.exec(request);
        N.commit();
    }
    catch (const std::exception &e) {
        return 1;
    }
    return 0;
}

int Postgre_DB::update(const std::string & table, std::vector <std::string> values, std::string where) {
    work N(*PG_conn);
    std::string request;
    std::string lower_table = "";
    for (auto sym : table) {
        lower_table += tolower(sym);
    }
    std::vector <std::string> column;
    column.push_back("column_name");
    std::string wh = "TABLE_NAME = '" + lower_table + "'";
    result columns = select("INFORMATION_SCHEMA.COLUMNS", wh, column);
    try {
        request = "UPDATE " + table + " SET ";
        std::size_t i = 0;
        for (result::const_iterator c = columns.begin(); c != columns.end(); ++c) {
            request += c[0].as<std::string>() + " = '" + remove_danger_characters(values[i++]) + "', ";
        }
        if (i < values.size()) return 1;

        request = request.substr(0, request.size() - 2);
        if (where != "") {
            request += " WHERE " + where;
        }
        request += ";";
        N.exec(request);
        N.commit();
    }
    catch (const std::exception &e) {
        columns.clear();
        return 1;
    }
    columns.clear();
    return 0;
}

int Postgre_DB::save(const std::string & table, std::vector <std::string> values, std::string where) {
    std::vector <std::string> column;
    result check = select(table, where);
    try {
        if ((where != "") and (check.begin() != check.end())) {
            check.clear();
            return update(table, values, where);
        }
        else {
            check.clear();
            return insert(table, values);
        }
    }
    catch (const std::exception &e) {
        check.clear();
        return 1;
    }
}

int Postgre_DB::delete_(const std::string & table, std::string where) {
    work N(*PG_conn);
    std::string request;
    request = "DELETE FROM " + table;
    if (where != "") {
        request += " WHERE " + where;
    }
    request += ";";
    try {
        N.exec(request);
        N.commit();
    }
    catch (const std::exception &e) {
        return 1;
    }
    return 0;
}

int Postgre_DB::init_tables() {
    std::string create_table = "CREATE TABLE ";
    std::string users_info = create_table + "USERS_INFO (user_id int, age int, course_number int, num_pairs int, name text, surname text, gender text, faculty text, vk_link text, telegram_link text, description text);";
    std::string login = create_table + "LOGIN (user_id int, login text, password text);";
    std::string  users_rec = create_table + "USERS_REC (user_id int, user_rec int[]);";
    std::string marks = create_table + "MARKS (mark_id int, id_marker int, id_marked int, mark int);";
    std::string images = create_table + "IMAGES (image_id int, user_id int, image_name text, image_path text);";
    work N(*PG_conn);
    try {
        N.exec(users_info);
    }
    catch (const std::exception &e) {
        cout << "TABLE USERS_INFO already exists" << endl;
    }
    N.commit();
    work N1(*PG_conn);
    try {
        N1.exec(login);
    }
    catch (const std::exception &e) {
        cout << "TABLE LOGIN already exist" << endl;
    }
    N1.commit();
    work N2(*PG_conn);
    try {
        N2.exec(users_rec);
    }
    catch (const std::exception &e) {
        cout << "TABLE USERS_REC already exist" << endl;
    }
    N2.commit();
    work N3(*PG_conn);
    try {
        N3.exec(marks);
    }
    catch (const std::exception &e) {
        cout << "TABLE MARKS already exist" << endl;
    }
    N3.commit();
    work N4(*PG_conn);
    try {
        N4.exec(images);
        N4.commit();
    }
    catch (const std::exception &e) {
        cout << "TABLE IMAGES already exist" << endl;
    }
    return 0;
}

int Postgre_DB::drop_tables() {
    std::string drop_table = "DROP TABLE ";
    std::string users_info = drop_table + "USERS_INFO;";
    std::string login = drop_table + "LOGIN;";
    std::string  users_rec = drop_table + "USERS_REC;";
    std::string marks = drop_table + "MARKS;";
    std::string images = drop_table + "IMAGES;";
    work N(*PG_conn);
    try {
        N.exec(users_info);
    }
    catch (const std::exception &e) {
        cout << "TABLE USERS_INFO does not exist" << endl;
    }
    N.commit();
    work N1(*PG_conn);
    try {
        N1.exec(login);
    }
    catch (const std::exception &e) {
        cout << "TABLE LOGIN does not exist" << endl;
    }
    N1.commit();
    work N2(*PG_conn);
    try {
        N2.exec(users_rec);
    }
    catch (const std::exception &e) {
        cout << "TABLE USERS_REC does not exist" << endl;
    }
    N2.commit();
    work N3(*PG_conn);
    try {
        N3.exec(marks);
    }
    catch (const std::exception &e) {
        cout << "TABLE MARKS does not exist" << endl;
    }
    N3.commit();
    work N4(*PG_conn);
    try {
        N4.exec(images);
        N4.commit();
    }
    catch (const std::exception &e) {
        cout << "TABLE IMAGES does not exist" << endl;
    }
    return 0;
}

int Postgre_DB::user_exist(std::string login, std::string password) {
    std::string where = "login = '" + remove_danger_characters(login) + "'";
    if (password != "") {
        where += " AND password = '" + password + "'";
    }
    try {
        result res = select("LOGIN", where);
        if (res.begin() != res.end()) {
            res.clear();
            return 1;
        }
    }
    catch (const std::exception &e) {
        return 0;
    }

    return 0;
}

USERS_INFO Postgre_DB::user_info(std::string login) {
    std::string where = "(SELECT user_id FROM LOGIN WHERE login = '" + login + "') = user_id"; 
    result res = select("USERS_INFO", where);
    USERS_INFO user;
    if (res.begin() != res.end()) {
        result::const_iterator c = res.begin();
        user.user_id = c[0].as<int>();
        user.age = c[1].as<int>();
        user.course_number = c[2].as<int>();
        user.num_pairs = c[3].as<int>();
        user.name = c[4].as<std::string>();
        user.surname = c[5].as<std::string>();
        user.gender = c[6].as<std::string>();
        user.faculty = c[7].as<std::string>();
        user.vk_link = c[8].as<std::string>();
        user.telegram_link = c[9].as<std::string>();
        user.description = c[10].as<std::string>();
    }
    res.clear();
    return user;
}

int Postgre_DB::user_register(std::string login, std::string password) {
    if (user_exist(login)) {
        return -1;
    }
    else {
        int id = max_id("LOGIN", "user_id") + 1;
        std::vector <string> user_vec(3);
        user_vec[0] = std::to_string(id);
        user_vec[1] = login;
        user_vec[2] = password;
        save("login", user_vec);
        return id;
    }
}

int Postgre_DB::save_user(USERS_INFO user_info) {
    std::vector <std::string> user;
    user.push_back(std::to_string(user_info.user_id));
    user.push_back(std::to_string(user_info.age));
    user.push_back(std::to_string(user_info.course_number));
    user.push_back(std::to_string(user_info.num_pairs));
    user.push_back(user_info.name);
    user.push_back(user_info.surname);
    user.push_back(user_info.gender);
    user.push_back(user_info.faculty);
    user.push_back(user_info.vk_link);
    user.push_back(user_info.telegram_link);
    user.push_back(user_info.description);
    std::string request = "user_id = " + user[0];
    try {
        std::string users_info = "USERS_INFO";
        save(users_info, user, request);
    }
    catch (const std::exception &e) {
        return 1;
    }
    return 0;
}

int Postgre_DB::user_id(std::string login) {
    std::string where = "login = '" + login + "'"; 
    result res = select("LOGIN", where);
    if (res.begin() == res.end()) {
        res.clear();
        return -1;
    }
    else {
        result::const_iterator c = res.begin();
        int m = c[0].as<int>();
        res.clear();
        return m;
    }
}

std::string Postgre_DB::user_login(int id) {
    std::string where = "user_id = '" + std::to_string(id) + "'"; 
    result res = select("LOGIN", where);
    if (res.begin() == res.end()) {
        res.clear();
        return "";
    }
    else {
        result::const_iterator c = res.begin();
        std::string s = c[1].as<std::string>();
        res.clear();
        return s;
    }
}

int Postgre_DB::set_mark(std::string login_marker, std::string login_marked, int mark) {
    int id_marker = user_id(login_marker);
    int id_marked = user_id(login_marked);
    int mark_id = max_id("MARKS", "mark_id") + 1;
    std::vector <std::string> mark_vec(4);
    mark_vec[0] = std::to_string(mark_id);
    mark_vec[1] = std::to_string(id_marker);
    mark_vec[2] = std::to_string(id_marked);
    mark_vec[3] = std::to_string(mark);
    std::string request = "id_marker = '" + mark_vec[1] + "' and id_marked = '" + mark_vec[2] + "'";
    try {
        std::string marks = "MARKS";
        save(marks, mark_vec, request);
    }
    catch (const std::exception &e) {
        return 1;
    }
    return 0;
}

std::vector <std::string> Postgre_DB::pairs_login(std::string login) {
    int id = user_id(login);
    std::vector <std::string> pairs;
    nontransaction N(*PG_conn);
    std::string request = "(SELECT id_marked FROM MARKS WHERE id_marker = " + std::to_string(id) + " and mark = 1) INTERSECT (SELECT id_marker FROM MARKS WHERE id_marked = " + std::to_string(id) + " and mark = 1);";
    result res = N.exec(request);
    N.commit();
    if (res.begin() != res.end()) {
        for (result::const_iterator c = res.begin(); c != res.end(); ++c) {
            pairs.push_back(user_login(c[0].as<int>()));
        }
    }
    res.clear();
    return pairs;
}

std::vector <std::vector <int>> Postgre_DB::marks_matrix() {
    std::string login = "LOGIN";
    int id_size = max_id(login, "user_id") + 1;
    std::vector <std::vector <int>> marks;
    for(int i = 0; i < id_size; ++i) {
        std::vector<int> temp;
        for(int j = 0; j < id_size; ++j)
            temp.push_back(0);
        marks.push_back(temp);
    }
    result res = select("MARKS");
    for (result::const_iterator c = res.begin(); c != res.end(); ++c) {
        marks[c[1].as<int>()][c[2].as<int>()] = c[3].as<int>();
    }
    res.clear();
    return marks;
}

int Postgre_DB::gender_is_different(int id1, int id2) {
    std::string where = "user_id = " + to_string(id1);
    std::vector <std::string> column;
    column.push_back("gender");
    result res = select("USERS_INFO", where, column);
    std::string gender1 = "";
    if (res.begin() != res.end()) {
        result::const_iterator c = res.begin();
        gender1 = c[0].as<string>();
    }
    res.clear();
    where = "user_id = " + to_string(id2);
    result res1 = select("USERS_INFO", where, column);
    std::string gender2 = "";
    if (res1.begin() != res1.end()) {
        result::const_iterator c1 = res1.begin();
        gender2 = c1[0].as<string>();
    }
    res1.clear();
    return (gender1 != gender2);
}

int Postgre_DB::seen(int id1, int id2) {
    std::string where = "id_marker = " + std::to_string(id1) + "AND id_marked = " + std::to_string(id2);
    result res = select("MARKS", where);
    if (res.begin() != res.end()) {
        res.clear();
        return 1;
    }
    res.clear();
    return 0;
}

int Postgre_DB::is_pair(int id1, int id2) {
    std::vector <std::string> pairs = pairs_login(user_login(id1));
    for (int i = 0; i < (int) pairs.size(); ++i) {
        if (user_id(pairs[i]) == id2) return 1;
    }
    return 0;
}

std::vector <std::vector<float>> Postgre_DB::users_params() {
    std::vector <std::vector<float>> users_params;
    std::vector <std::string> columns;
    columns.push_back("age");
    columns.push_back("course_number");
    columns.push_back("num_pairs");
    result res = select("USERS_INFO", "", columns);

    for (result::const_iterator c = res.begin(); c != res.end(); ++c) {
        std::vector <float> temp;
        temp.push_back(c[0].as<float>());
        temp.push_back(c[1].as<float>());
        temp.push_back(c[2].as<float>());
        users_params.push_back(temp);
    }
    res.clear();
    return users_params;
}  


int Postgre_DB::make_recommendations() {
    std::vector <std::vector <int>> marks = marks_matrix();;
    std::vector <std::vector <float>> u_params = users_params();;
    std::vector <std::string> user_rec;
    std::string rec;
    std::string request;
    std::vector <int> zeros(0);
    RecSys recsys;

    if (u_params.size() <= 1) return 0;
    recsys.fit(marks, &u_params);

    for (int i = 0; i < (int) u_params.size(); ++i) {
        std::vector<int> recs_for_user = recsys.predict(i);
        for (int j = (int) recs_for_user.size() - 1; j >= 0; --j) {
            if (!(gender_is_different(i, recs_for_user[j])) or seen(i, recs_for_user[j])) {
                recs_for_user[j] = recs_for_user[recs_for_user.size() - 1];
                recs_for_user.pop_back();
            }
        }
        user_rec.push_back(std::to_string(i));
        rec = "{ ";
        for (size_t i = 0; i < recs_for_user.size(); ++i) rec += std::to_string(recs_for_user[i]) + ",";
        rec = rec.substr(0, rec.size() - 1);
        rec += "}";
        user_rec.push_back(rec);
        request = "user_id = " + std::to_string(i);
        std::string users_rec = "USERS_REC";
        save(users_rec, user_rec, request);
        user_rec.clear();
    }

    return 0;
}

std::vector <std::string> Postgre_DB::user_rec(std::string login) {
    std::vector <std::string> rec;
    std::vector<int> rec_id;
    int us_id = user_id(login);
    std::string where = "user_id = " + std::to_string(us_id);
    result res = select("USERS_REC", where);
    if (res.begin() != res.end()) {
        result::const_iterator c = res.begin();
        std::string row = c[1].as<std::string>();
        res.clear();
        int kol = 0;
        if (row != "{}") {
            for (int i = 0; i < (int) row.size(); ++i) {
                if ((row[i] != '{') and (row[i] != ' ') and (row[i] != ',') and (row[i] != '}')) {
                    kol = kol * 10 + (row[i] - '0');
                }
                else {
                    if (i != 0) {
                        rec_id.push_back(kol);
                        kol = 0;
                    }
                }
            }
        }
    }

    else {
        res.clear();
        std::vector <std::vector <int>> marks = marks_matrix();
        std::vector <std::vector <float>> u_params = users_params();
        RecSys recsys;
        if (u_params.size() <= 1) return rec;
        recsys.fit(marks, &u_params);
        rec_id = recsys.predict(us_id);
        for (int i = (int) rec_id.size() - 1; i >= 0; --i) {
            if (!gender_is_different(us_id, rec_id[i])) {
                rec_id[i] = rec_id[rec_id.size() - 1];
                rec_id.pop_back();
            }
        }

    }

    for (auto i : rec_id) {
        if (!seen(us_id, i)) {
            rec.push_back(user_login(i));
        }
    }
    return rec;
}

int Postgre_DB::save_image(std::string path_to_file, int user_id, std::string name) {
    int image_id;
    std::string images = "IMAGES";
    std::string where = "";
    if (name != "") {
        where = "image_name = " + name;
    }
    image_id = max_id(images, "image_id") + 1;
    std::vector <std::string> values;
    values.push_back(std::to_string(image_id));
    values.push_back(std::to_string(user_id));
    values.push_back(name);
    values.push_back(path_to_file);
    try {
        save(images, values);
    }
    catch (const std::exception &e) {
        return 1;
    }
    return 0;
}

std::vector <std::string> Postgre_DB::user_image(int user_id, std::string image_name) {
    std::vector <std::string> paths;
    std::string where = "user_id = " + std::to_string(user_id);
    if (image_name != "") {
        where += " AND image_name = '" + image_name + "'";
    }
    where += " ORDER BY image_id";
    result res = select("IMAGES", where);
    for (result::const_iterator c = res.begin(); c != res.end(); ++c) {
        paths.push_back(c[3].as<std::string>());
    }
    res.clear();
    return paths;
}

int Postgre_DB::delete_image(int user_id, std::string image_name) {
    std::string img_req = "user_id = " + std::to_string(user_id) + " AND ";
    std::string table = "IMAGES";
    if (image_name != "") {
        img_req += "image_name = '" + image_name + "'";
    }
    else {
        img_req += "image_id = (SELECT MAX(image_id) FROM IMAGES WHERE user_id = " + std::to_string(user_id) + ")";
    }
    return delete_(table, img_req);
}
