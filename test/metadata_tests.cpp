#include "metadata.h"
#include <gtest/gtest.h>
#include <sstream>

using namespace Metadata;

TEST(MetadataTest, decodeInts)
{
    std::istringstream data("i45e");

    auto res = std::shared_ptr<tItem>(decode(data));

    auto str_value = res->as<tString>();
    ASSERT_EQ(str_value, nullptr);

    auto int_value = res->as<tInt>();
    ASSERT_NE(int_value, nullptr);

    ASSERT_EQ(int_value->value, 45);

}

TEST(MetadataTest, decodeStrings)
{
    //TODO Something!
}

int main(int argc, char **argv)
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
