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
    std::istringstream data("5:hello");

    auto res = std::shared_ptr<tItem>(decode(data));

    auto str_value = res->as<tString>();
    ASSERT_NE(str_value, nullptr);
    ASSERT_EQ(str_value->str, "hello");

    auto int_value = res->as<tInt>();
    ASSERT_EQ(int_value, nullptr);


}

TEST(MetadataTest, decodeEmptyList)
{
    std::istringstream data("le");

    auto res = std::shared_ptr<tItem>(decode(data));
    auto list_value = res->as<tList>();
    ASSERT_NE(list_value, nullptr);
    ASSERT_EQ(list_value->data.size(), 0);
}

TEST(MetadataTest, decodeStringList)
{
    std::istringstream data("l3:key5:value4:key26:value2e");

    auto res = std::shared_ptr<tItem>(decode(data));

    auto list_value = res->as<tList>();
    ASSERT_NE(list_value, nullptr);

    ASSERT_EQ(list_value->data.size(), 4);

    ASSERT_EQ(list_value->data[0]->as<tString>()->str,"key");
    ASSERT_EQ(list_value->data[3]->as<tString>()->str,"value2");
}

TEST(MetadataTest, decodeNumberList)
{
    std::istringstream data("li32ei45ei11ee");

    auto res = std::shared_ptr<tItem>(decode(data));

    auto list_value = res->as<tList>();
    ASSERT_NE(list_value, nullptr);

    ASSERT_EQ(list_value->data.size(), 3);

    ASSERT_EQ(list_value->data[0]->as<tInt>()->value, 32);
    ASSERT_EQ(list_value->data[2]->as<tInt>()->value, 11);
}

TEST(MetadataTest, decodeNumberANDStringList)
{
    std::istringstream data("li32e5:helloi11ee");

    auto res = std::shared_ptr<tItem>(decode(data));

    auto list_value = res->as<tList>();
    ASSERT_NE(list_value, nullptr);

    ASSERT_EQ(list_value->data.size(), 3);

    ASSERT_EQ(list_value->data[0]->as<tInt>()->value, 32);
    ASSERT_EQ(list_value->data[1]->as<tString>()->str, "hello");
    ASSERT_EQ(list_value->data[2]->as<tInt>()->value, 11);
}

TEST(MetadataTest, decodeEmptyDict)
{
    std::istringstream data("de");

    auto res = std::shared_ptr<tItem>(decode(data));

    auto dict_value = res->as<tDict>();
    ASSERT_NE(dict_value, nullptr);

    ASSERT_EQ(dict_value->data.size(), 0);
}

TEST(MetadataTest, decodeStringDict)
{
    std::istringstream data("d3:key5:value4:key26:value2e");

    auto res = std::shared_ptr<tItem>(decode(data));

    auto dict_value = res->as<tDict>();
    ASSERT_NE(dict_value, nullptr);

    ASSERT_EQ(dict_value->data.size(), 2);
    ASSERT_EQ(dict_value->data["key"]->as<tString>()->str, "value");
    ASSERT_EQ(dict_value->data["key2"]->as<tString>()->str, "value2");
}


TEST(MetadataTest, decodeHybridDict)
{
    std::istringstream data("d3:keyi45e4:key26:value2e");

    auto res = std::shared_ptr<tItem>(decode(data));

    auto dict_value = res->as<tDict>();
    ASSERT_NE(dict_value, nullptr);

    ASSERT_EQ(dict_value->data.size(), 2);
    ASSERT_EQ(dict_value->data["key"]->as<tInt>()->value, 45);
    ASSERT_EQ(dict_value->data["key2"]->as<tString>()->str, "value2");
}
int main(int argc, char **argv)
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
