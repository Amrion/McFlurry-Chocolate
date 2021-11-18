#include <soci/soci.h>
#include <soci/connection-pool.h>
#include <iostream>
using namespace std;
int main() {
    soci::connection_pool* pool_;
    std::size_t pool_size_;
    pool_ = new soci::connection_pool((pool_size_ = 1));
    soci::session& sql = pool_->at(0);
    sql.open("service=orcl user=system password=awesome");
    return 0;
}