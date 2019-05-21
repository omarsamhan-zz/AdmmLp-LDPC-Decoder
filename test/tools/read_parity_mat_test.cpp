#include "gtest/gtest.h"
#include "../../tools/read_parity_mat.h"

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(example, sum_zero) {
    static string code_filename = "../../../code_files/96.3.963";
    auto cr = read_alist(code_filename);
    ASSERT_EQ(0, 0);
}
