#include "Postgre_DB.h"
using namespace std;
Postgre_DB::Postgre_DB(string host, string port, string db_name, string user, string password) {
    string request = "dbname=" + db_name + " user=" + user + " password=" + password + " host=" + host + " port=" + port;
    try
    {
        PG_conn = new connection(request);
        if (!PG_conn->is_open()) {
            cout << "Can't open database" << endl;
        }
    }
    catch (const std::exception &e)
    {
        cerr << e.what() << std::endl;
    }
}

Postgre_DB::~Postgre_DB() {
    delete PG_conn;
}

// result Postgre_DB::select(string request) {
//     nontransaction N(*PG_conn);
//     result res(N.exec(request));
//     return res;
// }


int Postgre_DB::max_id(string table, string name_id) {
    nontransaction N(*PG_conn);
    string check = "SELECT * FROM " + table;
    result res(N.exec(check));
    if (res.begin() == res.end()) {
        return -1;
    }
    else {
        string sql = "SELECT MAX(" + name_id + ") FROM " + table;
        result res(N.exec(sql));
        result::const_iterator c = res.begin();
        return c[0].as<int>();
    }
}

int Postgre_DB::insert(string table, std::vector <string> values) {
    work N(*PG_conn);
    string request;
    try {
        request = "INSERT INTO " + table + " VALUES('";
        for (size_t i = 0; i < values.size(); ++i) {
            request += values[i] + "', '";
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

int Postgre_DB::update(string table, std::vector <string> values, string where) {
    work N(*PG_conn);
    string request;
    string lower_table = "";
    for (auto sym : table) {
        lower_table += tolower(sym);
    }
    request = "SELECT column_name FROM INFORMATION_SCHEMA.COLUMNS WHERE TABLE_NAME = '" + lower_table + "';";
    result columns(N.exec(request));
    try {
        request = "UPDATE " + table + " SET ";
        std::size_t i = 0;
        for (result::const_iterator c = columns.begin(); c != columns.end(); ++c) {
            request += c[0].as<string>() + " = '" + values[i++] + "', ";
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
        return 1;
    }
    return 0;
}

int Postgre_DB::save(string table, std::vector <string> values, string where) {
    work N(*PG_conn);
    string request;
    request = "SELECT * FROM " + table;
    if (where != "") {
        request += " WHERE " + where;
    } 
    request += ";";
    try {
        result check(N.exec(request));
        N.commit();
        if (where != "" and check.begin() != check.end()) {
            return update(table, values, where);
        } 
        else {
            return insert(table, values);
        }
    }
    catch (const std::exception &e) {
        return 1;
    }
}

int Postgre_DB::delete_(string table, string where) {
    work N(*PG_conn);
    string request;
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
    string create_table = "CREATE TABLE ";
    string users_info = create_table + "USERS_INFO (user_id int, age int, course_number int, num_pairs int, name text, surname text, gender text, faculty text, vk_link text, telegram_link text, description text, soul_mate_gender text);";
    string login = create_table + "LOGIN (user_id int, login text, password float);";
    string  users_rec = create_table + "USERS_REC (user_id int, user_rec int[]);";
    string marks = create_table + "MARKS (mark_id int, id_marker int, id_marked int, mark int);";
    string images = create_table + "IMAGES (image_id int, user_id int, image_name text, image bytea);";
    work N(*PG_conn);
    try {
        N.exec(users_info);
    }
    catch (const std::exception &e) {
        cout << "TABLE USERS_INFO is already exists" << endl;
    }
    N.commit();
    work N1(*PG_conn);
    try {
        N1.exec(login);
    }
    catch (const std::exception &e) {
        cout << "TABLE LOGIN is already exists" << endl;
    }
    N1.commit();
    work N2(*PG_conn);
    try {
        N2.exec(users_rec);
    }
    catch (const std::exception &e) {
        cout << "TABLE USERS_REC is already exists" << endl;
    }
    N2.commit();
    work N3(*PG_conn);
    try {
        N3.exec(marks);
    }
    catch (const std::exception &e) {
        cout << "TABLE MARKS is already exists" << endl;
    }
    N3.commit();
    work N4(*PG_conn);
    try {
        N4.exec(images);
        N4.commit();
    }
    catch (const std::exception &e) {
        cout << "TABLE IMAGES is already exists" << endl;
    }
    return 0;
}

int Postgre_DB::drop_tables() {
    string drop_table = "DROP TABLE ";
    string users_info = drop_table + "USERS_INFO;";
    string login = drop_table + "LOGIN;";
    string  users_rec = drop_table + "USERS_REC;";
    string marks = drop_table + "MARKS;";
    string images = drop_table + "IMAGES;";
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
        cout << "TABLE LOGIN does not exist" << endl;;
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

int Postgre_DB::user_exist(string login, float password) {
    nontransaction N(*PG_conn);
    string request = "SELECT * FROM LOGIN WHERE login = '" + login + "'"; 
    if (password != -1) {
        request += " password = '" + to_string(password) + "'";
    }
    request += ";";
    try {
        result res(N.exec(request));
        if (res.begin() != res.end()) {
            return 1;
        }
    }
    catch (const std::exception &e) {
        return 0;
    }
    
    return 0;
}

USERS_INFO Postgre_DB::user_info(string login) {
    nontransaction N(*PG_conn);
    string request = "SELECT * FROM USERS_INFO WHERE (SELECT user_id FROM LOGIN WHERE login = '" + login + "') = user_id;"; 
    result res(N.exec(request));
    USERS_INFO user;
    if (res.begin() != res.end()) {
        result::const_iterator c = res.begin();
        user.user_id = c[0].as<int>();
        user.age = c[1].as<int>();
        user.course_number = c[2].as<int>();
        user.num_pairs = c[3].as<int>();
        user.name = c[4].as<string>();
        user.surname = c[5].as<string>();
        user.gender = c[6].as<string>();
        user.faculty = c[7].as<string>();
        user.vk_link = c[8].as<string>();
        user.telegram_link = c[9].as<string>();
        user.description = c[10].as<string>();
        user.soul_mate_gender = c[11].as<string>();
    }
    return user;
}

int Postgre_DB::user_register(string login, float password) {
    if (user_exist(login)) {
        return -1;
    }
    else {
        int id = max_id("LOGIN", "user_id") + 1;
        std::vector <string> user_vec(3);
        user_vec[0] = to_string(id);
        user_vec[1] = to_string(login);
        user_vec[2] = to_string(password);
        save("login", user_vec);
        return id;
    }
}

int Postgre_DB::save_user(USERS_INFO user_info) {
    std::vector <string> user;
    user.push_back(to_string(user_info.user_id));
    user.push_back(to_string(user_info.age));
    user.push_back(to_string(user_info.course_number));
    user.push_back(to_string(user_info.num_pairs));
    user.push_back(user_info.name);
    user.push_back(user_info.surname);
    user.push_back(user_info.gender);
    user.push_back(user_info.faculty);
    user.push_back(user_info.vk_link);
    user.push_back(user_info.telegram_link);
    user.push_back(user_info.description);
    user.push_back(user_info.soul_mate_gender);
    string request = "user_id = " + user[0];
    try {
        save("USERS_INFO", user, request);
    }
    catch (const std::exception &e) {
        return 1;
    }
    return 0;
}

int Postgre_DB::user_id(string login) {
    nontransaction N(*PG_conn);
    string request = "SELECT user_id FROM LOGIN WHERE login = '" + login + "';"; 
    result res(N.exec(request));
    if (res.begin() == res.end()) {
        return -1;
    }
    else {
         result::const_iterator c = res.begin();
         return c[0].as<int>();
    }
}

string Postgre_DB::user_login(int id) {
    nontransaction N(*PG_conn);
    string request = "SELECT login FROM LOGIN WHERE user_id = '" + to_string(id) + "';"; 
    result res(N.exec(request));
    if (res.begin() == res.end()) {
        return "";
    }
    else {
        result::const_iterator c = res.begin();
        return c[0].as<string>();
    }
}

int Postgre_DB::set_mark(string login_marker, string login_marked, int mark) {
    int id_marker = user_id(login_marker);
    int id_marked = user_id(login_marked);
    int mark_id = max_id("MARKS", "mark_id") + 1;
    std::vector <string> mark_vec(4);
    mark_vec[0] = to_string(mark_id);
    mark_vec[1] = to_string(id_marker);
    mark_vec[2] = to_string(id_marked);
    mark_vec[3] = to_string(mark);
    string request = "id_marker = '" + mark_vec[1] + "' and id_marked = '" + mark_vec[2] + "'";
    try {
        save("MARKS", mark_vec, request);
    }
    catch (const std::exception &e) {
        return 1;
    }
    return 0;
}

std::vector <string> Postgre_DB::pairs_login(string login) {
    int id = user_id(login);
    std::vector <string> pairs;
    nontransaction N(*PG_conn);
    string request = "(SELECT id_marked FROM MARKS WHERE id_marker = " + to_string(id) + " and mark = 1) INTERSECT (SELECT id_marker FROM MARKS WHERE id_marked = " + to_string(id) + " and mark = 1);";
    result res(N.exec(request));
    N.commit();
    if (res.begin() != res.end()) {
        for (result::const_iterator c = res.begin(); c != res.end(); ++c) {
            pairs.push_back(user_login(c[0].as<int>()));
        }
    }
    return pairs;
}

std::vector <std::vector <int>> Postgre_DB::marks_matrix() {
    int id_size = max_id("LOGIN", "user_id") + 1;
    std::vector <std::vector <int>> marks;
    for(int i = 0; i < id_size; ++i) {
        std::vector<int> temp;
        for(int j = 0; j < id_size; ++j)
            temp.push_back(0);
        marks.push_back(temp);
    }
    nontransaction N(*PG_conn);
    string request = "SELECT id_marker, id_marked, mark FROM MARKS;";
    result res(N.exec(request));
    for (result::const_iterator c = res.begin(); c != res.end(); ++c) {
        marks[c[0].as<int>()][c[1].as<int>()] = c[2].as<int>();
    }
    
    return marks;
}

int Postgre_DB::gender_is_different(int id1, int id2) {
    nontransaction N(*PG_conn);
    string request = "SELECT gender FROM USERS_INFO WHERE user_id = " + to_string(id1) + ";";
    result res(N.exec(request));
    result::const_iterator c = res.begin();
    string gender1 = c[0].as<string>();
    N.commit();
    nontransaction N1(*PG_conn);
    request = "SELECT gender FROM USERS_INFO WHERE user_id = " + to_string(id2) + ";";
    result res1(N1.exec(request));
    result::const_iterator c1 = res1.begin();
    string gender2 = c1[0].as<string>();
    N1.commit();
    return (gender1 != gender2);
}

int Postgre_DB::seen(int id1, int id2) {
    nontransaction N(*PG_conn);
    string request = "SELECT * FROM MARKS WHERE id_marker = " + to_string(id1) + "AND id_marked = " + to_string(id2) + ";";
    result res(N.exec(request));
    if (res.begin() != res.end()) {
        return 1;
    }
    return 0;
}

int Postgre_DB::is_pair(int id1, int id2) {
    std::vector <string> pairs = pairs_login(user_login(id1));
    for (int i = 0; i < (int) pairs.size(); ++i) {
        if (user_id(pairs[i]) == id2) return 1;
    }
    return 0;
}

int Postgre_DB::make_recommendations() {
    std::vector <std::vector <int>> marks;
    std::vector <string> user_rec;
    string rec;
    string request;
    std::vector <int> zeros(0);
    RecSys recsys;
    marks = marks_matrix();
    std::shared_ptr<std::map<int, std::vector<int>>> REC = recsys.create_recommendations(marks, zeros);
    for (auto& kv : *REC) {
        std::vector <int> vec_rec = kv.second;
        for (int i = (int) vec_rec.size() - 1; i >= 0; --i) {
            if (!(gender_is_different(kv.first, vec_rec[i])) or seen(kv.first, vec_rec[i])) {
                vec_rec[i] = vec_rec[vec_rec.size() - 1];
                vec_rec.pop_back();
            }
        }
        user_rec.push_back(to_string(kv.first));
        rec = "{ ";
        for (size_t i = 0; i < vec_rec.size(); ++i) rec += to_string(vec_rec[i]) + ",";
        rec = rec.substr(0, rec.size() - 1);
        rec += "}";
        user_rec.push_back(rec);
        request = "user_id = " + to_string(kv.first);
        save("USERS_REC", user_rec, request);
        user_rec.clear();
    }
    
    return 0;
}

int Postgre_DB::save_image(string path_to_file, int user_id, string name) {
    int image_id; 
    image_id = max_id("IMAGES", "image_id") + 1;
    string request = "INSERT INTO IMAGES VALUES (" + to_string(image_id) + ", " + to_string(user_id) + ", '" + name + "', " + "pg_read_binary_file('" + path_to_file + "')::bytea);";
    try {
        work N(*PG_conn);
        N.exec(request);
        N.commit();
    }
    catch (const std::exception &e) {
        return 1;
    }
    return 0;
}


// #include <boost/archive/iterators/base64_from_binary.hpp>
// #include <boost/archive/iterators/binary_from_base64.hpp>
// #include <boost/archive/iterators/transform_width.hpp>

// bool Base64Decode( const string & input, string * output )
// {
// 	typedef transform_width<binary_from_base64<string::const_iterator>, 8, 6> Base64DecodeIterator;
// 	stringstream result;
// 	try {
// 		copy( Base64DecodeIterator( input.begin() ), Base64DecodeIterator( input.end() ), ostream_iterator<char>( result ) );
// 	} catch ( ... ) {
// 		return false;
// 	}
// 	*output = result.str();
// 	return output->empty() == false;
// }

std::vector <string> Postgre_DB::user_image(string dirname, int user_id, string image_name) {
    std::vector <string> files;
    string request = "SELECT user_id, image_name, encode(image, 'base64') FROM IMAGES WHERE user_id = " + to_string(user_id);
    if (image_name != "") {
        request += ", image_name = " + image_name;
    }
    request += ";";
    nontransaction N(*PG_conn);
    result res(N.exec(request));
    for (result::const_iterator c = res.begin(); c != res.end(); ++c) {
        ofstream fout;
        fout.open(dirname + "/" + to_string(c[0].as<int>()) + c[1].as<string>() + ".jpg", ios::binary|ios::out);
        string str = c[2].as<string>();
        fout << str;
        fout.close(); 
        files.push_back(dirname + "/" + to_string(c[0].as<int>()) + "_" + c[1].as<string>() + ".jpg");
    }
        
    return files;
}

