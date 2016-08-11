
#include <iostream>
#include "isat/utils/String.h"
#include "isat/utils/TopicManager.h"
#include "isat/utils/Topic.h"
#include "isat/utils/TopicSubscription.h"
#include "isat/utils/Message.h"


using namespace std;
using namespace isat_utils;


class TestMessage : public Message
{
   public:

      TestMessage(String field) : testField(field) {}
      String testField;
};

int
main(int argc, char** argv)
{
   String testTopicName("TEST_TOPIC");
   
   TopicManager& topicMgr = TopicManager::getInstance();
   TopicSubscription *sub1 = topicMgr.subscribe(testTopicName);
   TopicSubscription *sub2 = topicMgr.subscribe(testTopicName);

   sub1->publish(new TestMessage("jamie"));
   sub1->publish(new TestMessage("rosie"));
   sub2->publish(new TestMessage("carrie"));   
   sub1->publish(new TestMessage("pipa"));


   while (sub2->hasMessages())
   {
      TestMessage const* curMsg = static_cast<TestMessage const*> (sub2->getMessage());
      cout << "sub2: message = '" << curMsg->testField << "'\n";
   }

   while (sub1->hasMessages())
   {
      TestMessage const* curMsg = static_cast<TestMessage const*> (sub1->getMessage());
      cout << "sub1: message = '" << curMsg->testField << "'\n";
   }
      
   
   return 0;
}
