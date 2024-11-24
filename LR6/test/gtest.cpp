#include <gtest/gtest.h>

#include "tools.h"

TEST(Task1, test1)
{
    int max_word_serial;
    int max_word_index;
    String string("");
    string.get_max_word(max_word_serial, max_word_index);
    ASSERT_EQ(0, max_word_serial);
    ASSERT_EQ(0, max_word_index);
}

TEST(Task1, test2)
{
    int max_word_serial, max_word_index;
    String string("a");
    string.get_max_word(max_word_serial, max_word_index);
    ASSERT_EQ(1, max_word_serial);
    ASSERT_EQ(0, max_word_index);
}

TEST(Task1, test3)
{
    int max_word_serial, max_word_index;
    String string("a aa aaa aaaa aaaaa");
    string.get_max_word(max_word_serial, max_word_index);
    ASSERT_EQ(5, max_word_serial);
    ASSERT_EQ(14, max_word_index);
}

TEST(Task1, test4)
{
    int max_word_serial, max_word_index;
    String string("aaaaa aaaa aaa aa a");
    string.get_max_word(max_word_serial, max_word_index);
    ASSERT_EQ(1, max_word_serial);
    ASSERT_EQ(0, max_word_index);
}

TEST(Task1, test5)
{
    int max_word_serial, max_word_index;
    String string("a aaa aaaaa aaa a");
    string.get_max_word(max_word_serial, max_word_index);
    ASSERT_EQ(3, max_word_serial);
    ASSERT_EQ(6, max_word_index);
}

TEST(Task1, test6)
{
    int max_word_serial, max_word_index;
    String string("a a a a a");
    string.get_max_word(max_word_serial, max_word_index);
    ASSERT_EQ(1, max_word_serial);
    ASSERT_EQ(0, max_word_index);
}

TEST(Task1, test7)
{
    int max_word_serial, max_word_index;
    String string("aboba aliexpress abib icpc");
    string.get_max_word(max_word_serial, max_word_index);
    ASSERT_EQ(2, max_word_serial);
    ASSERT_EQ(6, max_word_index);
}

TEST(Task1, test8)
{
    int max_word_serial, max_word_index;
    String string("a aa aaa aaaa aaaaa aaaa aaa aa a");
    string.get_max_word(max_word_serial, max_word_index);
    ASSERT_EQ(5, max_word_serial);
    ASSERT_EQ(14, max_word_index);
}

TEST(Task1, test9)
{
    int max_word_serial, max_word_index;
    String string("      a aaa    aaaaa  aaaa     aaa    ");
    string.get_max_word(max_word_serial, max_word_index);
    ASSERT_EQ(3, max_word_serial);
    ASSERT_EQ(15, max_word_index);
}

TEST(Task1, test10)
{
    int max_word_serial, max_word_index;
    String string("Lorem ipsum dolor sit amet, consectetur adipiscing elit");
    string.get_max_word(max_word_serial, max_word_index);
    ASSERT_EQ(6, max_word_serial);
    ASSERT_EQ(28, max_word_index);
}

TEST(Task2, test1)
{
    String string("");
    String result;
    string.get_sorted_line(result);
    ASSERT_STREQ("", result.c_str());
}

TEST(Task2, test2)
{
    String string("a");
    String result;
    string.get_sorted_line(result);
    ASSERT_STREQ("a", result.c_str());
}

TEST(Task2, test3)
{
    String string("aboba aboba");
    String result;
    string.get_sorted_line(result);
    ASSERT_STREQ("aboba aboba", result.c_str());
}

TEST(Task2, test4)
{
    String string("ab bc cd de ef");
    String result;
    string.get_sorted_line(result);
    ASSERT_STREQ("ab bc cd de ef", result.c_str());
}

TEST(Task2, test5)
{
    String string("ef de cd bc ab");
    String result;
    string.get_sorted_line(result);
    ASSERT_STREQ("ab bc cd de ef", result.c_str());
}

TEST(Task2, test6)
{
    String string("FE ED DC CB BA");
    String result;
    string.get_sorted_line(result);
    ASSERT_STREQ("FE ED DC CB BA", result.c_str());
}

TEST(Task2, test7)
{
    String string("SUs AMOGUs");
    String result;
    string.get_sorted_line(result);
    ASSERT_STREQ("AMOGUs SUs", result.c_str());
}

TEST(Task2, test8)
{
    String string("qw ww we ee rt tt yu uu io oo pa aa sd dd fg gg hj jj kl ll zx xx cv vv bn nn mn");
    String result;
    string.get_sorted_line(result);
    ASSERT_STREQ("qw ww we ee", result.c_str());
}

TEST(Task2, test9)
{
    String string("abc def cda fge efa");
    String result;
    string.get_sorted_line(result);
    ASSERT_STREQ("def fge efa abc cda", result.c_str());
}

TEST(Task2, test10)
{
    String string("Lorem ipsum dolor sit amet, consectetur adipiscing elit");
    String result;
    string.get_sorted_line(result);
    ASSERT_STREQ("Lorem", result.c_str());
}

TEST(Task3, test1)
{
    String string(""), chars;
    string.get_chars(chars);
    ASSERT_STREQ("", chars.c_str());
}

TEST(Task3, test2)
{
    String string("a"), chars;
    string.get_chars(chars);
    ASSERT_STREQ("a", chars.c_str());
}

TEST(Task3, test3)
{
    String string("           "), chars;
    string.get_chars(chars);
    ASSERT_STREQ(" ", chars.c_str());
}

TEST(Task3, test4)
{
    String string("AMOGUS");
    String chars;
    string.get_chars(chars);
    ASSERT_STREQ("AMOGUS", chars.c_str());
}

TEST(Task3, test5)
{
    String string("88005553535"), chars;
    string.get_chars(chars);
    ASSERT_STREQ("8053", chars.c_str());
}

TEST(Task3, test6)
{
    String string("!@#$%^&*())(*&^%$#@!)"), chars;
    string.get_chars(chars);
    ASSERT_STREQ("!@#$%^&*()", chars.c_str());
}

TEST(Task3, test7)
{
    String string("aboba"), chars;
    string.get_chars(chars);
    ASSERT_STREQ("abo", chars.c_str());
}

TEST(Task3, test8)
{
    String string("84.n#$^v&^sef%84##%^sfds,7,.y3bv,"), chars;
    string.get_chars(chars);
    ASSERT_STREQ("84.n#$^v&sef%d,7y3b", chars.c_str());
}

TEST(Task3, test9)
{
    String string("qw ww we ee rt tt yu uu io oo pa aa sd dd fg gg hj jj kl ll zx xx cv vv bn nn mn"), chars;
    string.get_chars(chars);
    ASSERT_STREQ("qw ertyuiopasdfghjklzxcvbnm", chars.c_str());
}

TEST(Task3, test10)
{
    String string("Lorem ipsum dolor sit amet, consectetur adipiscing elit");
    String chars;
    string.get_chars(chars);
    ASSERT_STREQ("Lorem ipsudlta,cng", chars.c_str());
}
