#include <iostream>
#include <string>

// NOTE: keydb is a open source library written by me
//       https://github.com/clarkok/keydb
#include "keydb/db.h"
#include "config.h"
#include "entry.h"

using namespace OOP;

int
main(int argc, char **argv)
{
  // show usage
  if (argc < 2) {
    std::cerr << Config::HELP_TEXT;
    return -1;
  }
  
  // connect to the KeyDB
  KeyDB::DB *db = KeyDB::createDiskDB(Config::DB_PATH);
  try {
    db->open();
  }
  catch (const KeyDB::Exception &e) {
    // ... and if the database not exists
    db->reset();
    db->insert("RECORD", KeyDB::Buffer(""));
  }
  
  // load the index of the diaries
  auto buf = db->get("RECORD");
  Entries entries(
    reinterpret_cast<Date*>(buf.begin()), 
    reinterpret_cast<Date*>(buf.end())
  );
  
  // add a entry
  if (std::string(argv[1]) == "add") {
    Date d; // the constructor will use the date of today

    // and if the date is provided, use it instead
    if (argc > 2) {
      d = Date(argv[2]);
    }
    // insert date into index
    entries.insertDate(d);
    
    std::string content;
    std::string line;
    
    // read the diary
    while (std::getline(std::cin, line)) {
      if (line == ".")
        break;
      content += line + '\n';
    }
    
    // try to insert, will succeed when there is no diary of the date
    try {
      db->insert(
        KeyDB::Key(reinterpret_cast<char*>(&d), sizeof(Date)),
        KeyDB::Value(content.c_str(), content.length())
      );
    }
    catch (const KeyDB::Exception &e) {
      // or the diary exists, replace it
      db->update(
        KeyDB::Key(reinterpret_cast<char*>(&d), sizeof(Date)),
        KeyDB::Value(content.c_str(), content.length())
      );
    }
  }
  // list entry
  else if (std::string(argv[1]) == "list") {
    if (argc == 2) {
      // if no range provided
      for (auto d : entries) {
        std::cout << d.toString() << std::endl;
      }
    }
    else if (argc == 3) {
      // if one date provided as upper range
      Date from(argv[2]);
      auto from_iter = std::lower_bound(entries.begin(), entries.end(), from);
      auto to_iter = entries.end();
      
      for (auto i = from_iter; i != to_iter; ++i)
        std::cout << i->toString() << std::endl;
    }
    else if (argc >= 4) {
      // if both dates provided as upper and lower range
      Date from(argv[2]), to(argv[3]);
      auto from_iter = std::lower_bound(entries.begin(), entries.end(), from),
           to_iter = std::upper_bound(entries.begin(), entries.end(), to);
      for (auto i = from_iter; i != to_iter; ++i)
        std::cout << i->toString() << std::endl;
    }
  }
  // show a diary
  else if (std::string(argv[1]) == "show") {
    Date d;
    if (argc >= 3)
      d = Date(argv[2]);
    try {
      std::cout << db->get(
        KeyDB::Key(
          reinterpret_cast<char*>(&d),
          sizeof(d)
        )
      );
    }
    catch (const KeyDB::Exception& e) {
      std::cerr << "No entry fround for " << d.toString() << std::endl;
    }
  }
  // remove a diary
  else if (std::string(argv[1]) == "remove") {
    Date d;
    if (argc >= 3)
      d = Date(argv[2]);
    try {
      db->erase(
        KeyDB::Key(
          reinterpret_cast<char*>(&d),
          sizeof(d)
        )
      );
      auto i = std::lower_bound(entries.begin(), entries.end(), d);
      entries.erase(i);
    }
    catch (const KeyDB::Exception& e) {
      std::cerr << "No entry fround for " << d.toString() << std::endl;
    };
  }
  else {
    std::cerr << "Unknown command: " << argv[1] << std::endl;
    std::cerr << Config::HELP_TEXT;
    db->close();
    return -1;
  }

  // update index in database
  db->update("RECORD", 
    KeyDB::Buffer(
      reinterpret_cast<char*>(entries.data()),
      entries.size() * sizeof(Date)
    )
  );
  
  db->close();
  return 0;
}
