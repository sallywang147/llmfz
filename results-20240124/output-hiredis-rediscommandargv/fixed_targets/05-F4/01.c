#include <iostream>
#include <hiredis/hiredis.h>

using namespace std;

int main() {
  // Connect to the Redis server
  redisContext *c = redisConnect("127.0.0.1", 6379);
  if (c == NULL) {
    cout << "Error connecting to Redis server" << endl;
    return 1;
  }

  // Set the key-value pair
  redisCommandArgv(c, 2, (char*[]) {"SET", "key", "value"}, NULL);

  // Get the value associated with the key
  redisReply *reply = (redisReply*) redisCommand(c, "GET key");
  if (reply == NULL) {
    cout << "Error getting value from Redis server" << endl;
    return 1;
  }

  // Print the value
  cout << "Value: " << reply->str << endl;

  // Free the reply object
  freeReplyObject(reply);

  // Disconnect from the Redis server
  redisFree(c);

  return 0;
}