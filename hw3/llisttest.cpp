#include "lliststring.h"
#include <iostream>
#include "gtest/gtest.h"

using namespace std;



TEST(LListString, CopyConstructor){
	LListString* list = new LListString();
	list->insert(0, "first");
	list->insert(1, "second");

    LListString copy (*list);
    // check values in copy
    EXPECT_EQ("first", copy[0]);
    EXPECT_EQ("second", copy[1]);
    // modify list, see if copy changes
    list->clear();
    EXPECT_EQ(2, copy.size());
    
    // check if works on empty list
    LListString more_copy (*list);
    EXPECT_EQ(0, more_copy.size());
    
    delete list;
}

TEST(LListString, AssignmentOperator){
	LListString* list = new LListString();
	list->insert(0, "first");
	list->insert(1, "second");

    LListString copy;
    copy = *list;
    
    // check values in copy
    EXPECT_EQ("first", copy[0]);
    EXPECT_EQ("second", copy[1]);
    
    // modify list, see if copy changes
    list->clear();
    EXPECT_EQ(2, copy.size());
    
    // check if works on empty list
    LListString more_copy;
    more_copy = *list;
    EXPECT_EQ(0, more_copy.size());
    
    //check self-assigning
    LListString more_more_copy;
    more_more_copy = more_more_copy;
    EXPECT_EQ(0, more_more_copy.size());
    
    delete list;
}

TEST(LListString, PlusOperator){
	LListString* list = new LListString();
	list->insert(0, "first");
	list->insert(1, "second");

    LListString copy;
    copy.insert(0, "one");
    copy.insert(1, "two");
    copy = *list + copy;
    EXPECT_EQ(4, copy.size());
    EXPECT_EQ("one", copy[2]);
    EXPECT_EQ("first", copy[0]);
    
    // do reverse order
    copy.clear();
    copy.insert(0, "one");
    copy.insert(1, "two");
    copy = copy + *list;
    EXPECT_EQ(4, copy.size());
    EXPECT_EQ("first", copy[2]);
    EXPECT_EQ("one", copy[0]);
    
    // do adding itself
    copy.clear();
    copy.insert(0, "one");
    copy.insert(1, "two");
    copy = copy + copy;
    EXPECT_EQ(4, copy.size());
    EXPECT_EQ("one", copy[2]);
    EXPECT_EQ("one", copy[0]);
    EXPECT_EQ("two", copy[1]);
    EXPECT_EQ("two", copy[3]);

    delete list;
}

TEST(LListString, BracketOperator){
	LListString list;
	list.insert(0, "first");
	list.insert(1, "second");

    EXPECT_EQ("first", list[0]);
    EXPECT_EQ("second", list[1]);


}



