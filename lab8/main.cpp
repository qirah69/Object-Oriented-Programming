#include "song.h"
#include "songCol.h"
#include <iostream>
#include <map>
#include <string>
#include <vector>

// Helper to print test results cleanly
void printTestResult(const std::string &testName, bool passed) {
  std::cout << (passed ? "[PASS] " : "[FAIL] ") << testName << "\n";
}

int main() {
  std::cout << "=== Starting Final SongCollection Test Suite ===\n\n";

  std::string testFile = "song_text.txt";

  // ---------------------------------------------------------
  // TEST 1: Exception Handling
  // ---------------------------------------------------------
  bool exceptionThrown = false;
  try {
    SongCollection badCollection("this_file_does_not_exist.txt");
  } catch (const std::invalid_argument &e) {
    exceptionThrown = true;
  }
  printTestResult("Throws std::invalid_argument for missing file",
                  exceptionThrown);

  // ---------------------------------------------------------
  // TEST 2: File Parsing & Initialization
  // ---------------------------------------------------------
  // If the file isn't found, it will throw an exception here and exit!
  SongCollection library(testFile);
  std::vector<Song> allSongs = library.sortByArtist();
  printTestResult("Successfully parsed all 13 songs from file",
                  allSongs.size() == 13);

  // ---------------------------------------------------------
  // TEST 3: Inverted Index (Efficient Search)
  // ---------------------------------------------------------
  // A. Shared Vocabulary & Case Insensitivity
  // The word "queen" is in David Bowie's "Heroes" and Michael Jackson's "Billie
  // Jean"
  std::vector<Song> searchQueen = library.getSongsWithWord("QUEEN");
  printTestResult("Search finds multiple songs & ignores case",
                  searchQueen.size() == 2);

  // B. Duplicate Word Handling (The std::set fix)
  // "submarine" appears 5 times in "Yellow Submarine", but should only return 1
  // song!
  std::vector<Song> searchSubmarine = library.getSongsWithWord("submarine");
  printTestResult("Inverted index prevents duplicate songs",
                  searchSubmarine.size() == 1);

  // C. Word Not Found
  std::vector<Song> notFound = library.getSongsWithWord("zxcvbnm");
  printTestResult("Returns empty vector for non-existent word",
                  notFound.empty());

  // ---------------------------------------------------------
  // TEST 4: Grouping by Artist (Associative Container)
  // ---------------------------------------------------------
  std::map<std::string, std::vector<Song>> grouped = library.rankingBySongs();
  bool groupingCorrect =
      (grouped.size() == 7) &&             // 7 Unique Artists
      (grouped["Queen"].size() == 3) &&    // Queen has 3 songs
      (grouped["Elton John"].size() == 1); // Elton John has 1 song
  printTestResult("Groups songs by artist into std::map correctly",
                  groupingCorrect);

  // ---------------------------------------------------------
  // TEST 5: Lambda Sorting - By Artist (Increasing A->Z)
  // ---------------------------------------------------------
  std::vector<Song> artistSorted = library.sortByArtist();
  bool artistSortCorrect = (artistSorted.front().getArtist() == "Adele") &&
                           (artistSorted.back().getArtist() == "The Beatles");
  printTestResult("Lambda Sort: Artist (Increasing A->Z)", artistSortCorrect);

  // ---------------------------------------------------------
  // TEST 6: Lambda Sorting - By Title (Descending Z->A)
  // ---------------------------------------------------------
  std::vector<Song> titleSorted = library.sortByTitle();
  // Yellow Submarine (Y) should be first, Billie Jean (B) should be last
  bool titleSortCorrect =
      (titleSorted.front().getTitle() == "Yellow Submarine") &&
      (titleSorted.back().getTitle() == "Billie Jean");
  printTestResult("Lambda Sort: Title (Descending Z->A)", titleSortCorrect);

  // ---------------------------------------------------------
  // TEST 7: Lambda Sorting - By Lyrics Count (Increasing)
  // ---------------------------------------------------------
  std::vector<Song> lyricsSorted = library.sortByLyricsNumber();
  // As long as the first element has <= words than the last element, it works.
  bool lyricsSortCorrect = lyricsSorted.front().getLyricsWords().size() <=
                           lyricsSorted.back().getLyricsWords().size();
  printTestResult("Lambda Sort: Lyrics Word Count (Increasing)",
                  lyricsSortCorrect);

  std::cout << "\n=== All Tests Completed ===" << std::endl;

  return 0;
}
