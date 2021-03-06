//  Copyright [2013] Kyle Galloway (kyle.s.galloway@gmail.com)
//                   Pravish Sood (pravish.sood@gmail.com)
//                   Dylan Kelemen (dckelemen@gmail.com)

//  Licensed under the Apache License, Version 2.0 (the "License");
//  you may not use this file except in compliance with the License.
//  You may obtain a copy of the License at

//      http://www.apache.org/licenses/LICENSE-2.0

//  Unless required by applicable law or agreed to in writing, software
//  distributed under the License is distributed on an "AS IS" BASIS,
//  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//  See the License for the specific language governing permissions and
//  limitations under the License.

#include "sql_select_statement.h"

#include <gtest/gtest.h>

#include <iostream>
#include <string>

TEST(SQLSelectStatement, Breathing)
{
    mongoodbc::SQLSelectStatementParser<std::string::const_iterator> parser;
    mongoodbc::SQLSelectStatement stmt;
    std::string query("SELECT * FROM db.table");
    std::string::const_iterator iter = query.begin();
    std::string::const_iterator end = query.end();
    try
    {
        boost::spirit::qi::phrase_parse(iter, end, parser, boost::spirit::ascii::space, stmt);
        std::cout << "SELECT Stmt: " << stmt << std::endl;
    }
    catch (const boost::spirit::qi::expectation_failure<std::string::const_iterator>& ex)
    {
        std::string fragment(ex.first, ex.last);
        std::cerr << ex.what() << "'" << fragment << "'" << std::endl;
    }
}

TEST(SQLSelectStatement, SelectStar)
{
    mongoodbc::SQLSelectStatementParser<std::string::const_iterator> parser;
    mongoodbc::SQLSelectStatement stmt;
    std::string query("SELECT * FROM db.table");
    std::string::const_iterator iter = query.begin();
    std::string::const_iterator end = query.end();
    try
    {
        EXPECT_TRUE(
            boost::spirit::qi::phrase_parse(iter, end, parser, boost::spirit::ascii::space, stmt));
        EXPECT_FALSE(stmt._all);
        EXPECT_FALSE(stmt._distinct);
        EXPECT_EQ(0, stmt._selectList.size());
        std::cout << "SELECT Stmt: " << stmt << std::endl;
    }
    catch (const boost::spirit::qi::expectation_failure<std::string::const_iterator>& ex)
    {
        std::string fragment(ex.first, ex.last);
        std::cerr << ex.what() << "'" << fragment << "'" << std::endl;
    }
}

TEST(SQLSelectStatement, SelectStarDb)
{
    mongoodbc::SQLSelectStatementParser<std::string::const_iterator> parser;
    mongoodbc::SQLSelectStatement stmt;
    std::string query("SELECT * FROM db.table");
    std::string::const_iterator iter = query.begin();
    std::string::const_iterator end = query.end();
    try
    {
        EXPECT_TRUE(
            boost::spirit::qi::phrase_parse(iter, end, parser, boost::spirit::ascii::space, stmt));
        EXPECT_FALSE(stmt._all);
        EXPECT_FALSE(stmt._distinct);
        EXPECT_EQ(0, stmt._selectList.size());
        std::cout << "SELECT Stmt: " << stmt << std::endl;
    }
    catch (const boost::spirit::qi::expectation_failure<std::string::const_iterator>& ex)
    {
        std::string fragment(ex.first, ex.last);
        std::cerr << ex.what() << "'" << fragment << "'" << std::endl;
    }
}

TEST(SQLSelectStatement, SelectAllStar)
{
    mongoodbc::SQLSelectStatementParser<std::string::const_iterator> parser;
    mongoodbc::SQLSelectStatement stmt;
    std::string query("SELECT ALL * FROM db.table");
    std::string::const_iterator iter = query.begin();
    std::string::const_iterator end = query.end();
    try
    {
        EXPECT_TRUE(
            boost::spirit::qi::phrase_parse(iter, end, parser, boost::spirit::ascii::space, stmt));
        EXPECT_TRUE(stmt._all);
        EXPECT_FALSE(stmt._distinct);
        EXPECT_EQ(0, stmt._selectList.size());
        std::cout << "SELECT Stmt: " << stmt << std::endl;
    }
    catch (const boost::spirit::qi::expectation_failure<std::string::const_iterator>& ex)
    {
        std::string fragment(ex.first, ex.last);
        std::cerr << ex.what() << "'" << fragment << "'" << std::endl;
    }
}

TEST(SQLSelectStatement, SelectDistinctStar)
{
    mongoodbc::SQLSelectStatementParser<std::string::const_iterator> parser;
    mongoodbc::SQLSelectStatement stmt;
    std::string query("SELECT DISTINCT * FROM db.table");
    std::string::const_iterator iter = query.begin();
    std::string::const_iterator end = query.end();
    try
    {
        EXPECT_TRUE(
            boost::spirit::qi::phrase_parse(iter, end, parser, boost::spirit::ascii::space, stmt));
        EXPECT_FALSE(stmt._all);
        EXPECT_TRUE(stmt._distinct);
        EXPECT_EQ(0, stmt._selectList.size());
        std::cout << "SELECT Stmt: " << stmt << std::endl;
    }
    catch (const boost::spirit::qi::expectation_failure<std::string::const_iterator>& ex)
    {
        std::string fragment(ex.first, ex.last);
        std::cerr << ex.what() << "'" << fragment << "'" << std::endl;
    }
}

TEST(SQLSelectStatement, SelectColumn)
{
    mongoodbc::SQLSelectStatementParser<std::string::const_iterator> parser;
    mongoodbc::SQLSelectStatement stmt;
    std::string query("SELECT columnName FROM db.table");
    std::string::const_iterator iter = query.begin();
    std::string::const_iterator end = query.end();
    try
    {
        EXPECT_TRUE(
            boost::spirit::qi::phrase_parse(iter, end, parser, boost::spirit::ascii::space, stmt));
        EXPECT_FALSE(stmt._all);
        EXPECT_FALSE(stmt._distinct);
        EXPECT_EQ(1, stmt._selectList.size());
        std::cout << "SELECT Stmt: " << stmt << std::endl;
    }
    catch (const boost::spirit::qi::expectation_failure<std::string::const_iterator>& ex)
    {
        std::string fragment(ex.first, ex.last);
        std::cerr << ex.what() << "'" << fragment << "'" << std::endl;
    }
}

TEST(SQLSelectStatement, SelectTableColumn)
{
    mongoodbc::SQLSelectStatementParser<std::string::const_iterator> parser;
    mongoodbc::SQLSelectStatement stmt;
    std::string query("SELECT tableName.columnName FROM db.table");
    std::string::const_iterator iter = query.begin();
    std::string::const_iterator end = query.end();
    try
    {
        EXPECT_TRUE(
            boost::spirit::qi::phrase_parse(iter, end, parser, boost::spirit::ascii::space, stmt));
        EXPECT_FALSE(stmt._all);
        EXPECT_FALSE(stmt._distinct);
        EXPECT_EQ(1, stmt._selectList.size());
        std::cout << "SELECT Stmt: " << stmt << std::endl;
    }
    catch (const boost::spirit::qi::expectation_failure<std::string::const_iterator>& ex)
    {
        std::string fragment(ex.first, ex.last);
        std::cerr << ex.what() << "'" << fragment << "'" << std::endl;
    }
}

TEST(SQLSelectStatement, SelectStarWhere)
{
    mongoodbc::SQLSelectStatementParser<std::string::const_iterator> parser;
    mongoodbc::SQLSelectStatement stmt;
    std::string query("SELECT * FROM db.table WHERE age > 5");
    std::string::const_iterator iter = query.begin();
    std::string::const_iterator end = query.end();
    try
    {
        EXPECT_TRUE(
            boost::spirit::qi::phrase_parse(iter, end, parser, boost::spirit::ascii::space, stmt));
        EXPECT_FALSE(stmt._all);
        EXPECT_FALSE(stmt._distinct);
        EXPECT_EQ(0, stmt._selectList.size());
        std::cout << "SELECT Stmt: " << stmt << std::endl;
    }
    catch (const boost::spirit::qi::expectation_failure<std::string::const_iterator>& ex)
    {
        std::string fragment(ex.first, ex.last);
        std::cerr << ex.what() << "'" << fragment << "'" << std::endl;
    }
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

