#include <algorithm>
#include <chrono>
#include <iostream>
#include <limits>
#include <random>
#include <string>
#include <sstream>
#include <vector>

// Keep the code limited to one namespace to match existing style.
using namespace std;

struct Song {
  string title;
  string artist;
  int durationSeconds;
};

template <typename T>
class DoublyLinkedList {
 public:
  struct Node {
    T data;
    Node *prev;
    Node *next;
    explicit Node(const T &value) : data(value), prev(nullptr), next(nullptr) {}
  };

 private:
  Node *head;
  Node *tail;
  size_t listSize;

 public:
  DoublyLinkedList() : head(nullptr), tail(nullptr), listSize(0) {}

  ~DoublyLinkedList() { clear(); }

  void clear() {
    while (head != nullptr) {
      Node *temp = head;
      head = head->next;
      delete temp;
    }
    tail = nullptr;
    listSize = 0;
  }

  size_t size() const { return listSize; }

  Node *getHead() const { return head; }

  Node *getTail() const { return tail; }

  // Append at the end of the list.
  void push_back(const T &value) {
    Node *node = new Node(value);
    if (head == nullptr) {
      head = tail = node;
    } else {
      tail->next = node;
      node->prev = tail;
      tail = node;
    }
    ++listSize;
  }

  // Remove a specific node from the list.
  void remove(Node *target) {
    if (target == nullptr) {
      return;
    }

    if (target == head) {
      head = target->next;
      if (head != nullptr) {
        head->prev = nullptr;
      }
    } else {
      target->prev->next = target->next;
    }

    if (target == tail) {
      tail = target->prev;
      if (tail != nullptr) {
        tail->next = nullptr;
      }
    } else {
      target->next->prev = target->prev;
    }

    delete target;
    --listSize;
  }

  // Find first node that satisfies the predicate.
  template <typename Predicate>
  Node *findFirst(Predicate predicate) const {
    for (Node *cur = head; cur != nullptr; cur = cur->next) {
      if (predicate(cur->data)) {
        return cur;
      }
    }
    return nullptr;
  }
};

class MusicPlayer {
 private:
  DoublyLinkedList<Song> playlist;
  DoublyLinkedList<Song>::Node *current;
  int volume;
  bool shuffleActive;

  static string formatDuration(int seconds) {
    int minutes = seconds / 60;
    int remaining = seconds % 60;
    ostringstream oss;
    oss << minutes << ':' << (remaining < 10 ? "0" : "") << remaining;
    return oss.str();
  }

  void rebuildFromVector(const vector<Song> &order) {
    playlist.clear();
    for (const Song &song : order) {
      playlist.push_back(song);
    }
    current = playlist.getHead();
  }

 public:
  MusicPlayer() : current(nullptr), volume(50), shuffleActive(false) {}

  void addSong(const Song &song) {
    playlist.push_back(song);
    if (current == nullptr) {
      current = playlist.getHead();
    }
  }

  void removeSong(const string &title) {
    if (playlist.size() == 0) {
      cout << "Playlist is empty. Nothing to remove." << endl;
      return;
    }

    DoublyLinkedList<Song>::Node *target = playlist.findFirst(
        [&title](const Song &song) { return song.title == title; });

    if (target == nullptr) {
      cout << "No song found with title '" << title << "'." << endl;
      return;
    }

    if (target == current) {
      current = current->next != nullptr ? current->next : current->prev;
    }

    playlist.remove(target);
  }

  void nextSong() {
    if (current == nullptr) {
      cout << "Playlist is empty." << endl;
      return;
    }

    if (current->next == nullptr) {
      cout << "You are at the end of the playlist." << endl;
      return;
    }

    current = current->next;
  }

  void previousSong() {
    if (current == nullptr) {
      cout << "Playlist is empty." << endl;
      return;
    }

    if (current->prev == nullptr) {
      cout << "You are at the beginning of the playlist." << endl;
      return;
    }

    current = current->prev;
  }

  void jumpTo(size_t index) {
    if (playlist.size() == 0) {
      cout << "Playlist is empty." << endl;
      return;
    }

    DoublyLinkedList<Song>::Node *cursor = playlist.getHead();
    size_t currentIndex = 0;
    while (cursor != nullptr && currentIndex < index) {
      cursor = cursor->next;
      ++currentIndex;
    }

    if (cursor == nullptr) {
      cout << "Index " << index << " is out of range." << endl;
      return;
    }

    current = cursor;
  }

  void showPlaylist() const {
    if (playlist.size() == 0) {
      cout << "Playlist is empty." << endl;
      return;
    }

    cout << "Playlist (" << (shuffleActive ? "shuffled" : "ordered") << "):\n";
    DoublyLinkedList<Song>::Node *cursor = playlist.getHead();
    size_t index = 0;
    while (cursor != nullptr) {
      cout << (cursor == current ? "> " : "  ");
      cout << index + 1 << ". " << cursor->data.title << " by " << cursor->data.artist
           << " (" << formatDuration(cursor->data.durationSeconds) << ")";
      if (cursor == current) {
        cout << " <- current";
      }
      cout << '\n';
      cursor = cursor->next;
      ++index;
    }
  }

  void displayCurrent() const {
    if (current == nullptr) {
      cout << "Playlist is empty." << endl;
      return;
    }

    const Song &song = current->data;
    cout << "Now playing: " << song.title << " by " << song.artist << " ("
         << formatDuration(song.durationSeconds) << ")" << endl;
  }

  void toggleShuffle() {
    if (playlist.size() <= 1) {
      cout << "Need at least two songs to shuffle." << endl;
      return;
    }

    vector<Song> order;
    order.reserve(playlist.size());
    for (DoublyLinkedList<Song>::Node *cursor = playlist.getHead(); cursor != nullptr;
         cursor = cursor->next) {
      order.push_back(cursor->data);
    }

    unsigned seed = static_cast<unsigned>(chrono::high_resolution_clock::now().time_since_epoch().count());
    shuffle(order.begin(), order.end(), default_random_engine(seed));

    rebuildFromVector(order);
    shuffleActive = true;
  }

  void setVolume(int requestedVolume) {
    if (requestedVolume < 0) {
      volume = 0;
    } else if (requestedVolume > 100) {
      volume = 100;
    } else {
      volume = requestedVolume;
    }

    cout << "Volume set to " << volume << "%" << endl;
  }
};

static int readInt() {
  int value;
  while (!(cin >> value)) {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Please enter a valid number: ";
  }

  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  return value;
}

static Song promptSong() {
  Song song;
  cout << "Song title: ";
  getline(cin, song.title);
  cout << "Artist: ";
  getline(cin, song.artist);
  cout << "Duration in seconds: ";
  song.durationSeconds = readInt();
  return song;
}

static void printMenu() {
  cout << "\nMusic Playlist Manager\n"
       << "1) Add song\n"
       << "2) Remove song\n"
       << "3) Next song\n"
       << "4) Previous song\n"
       << "5) Jump to position\n"
       << "6) Show playlist\n"
       << "7) Shuffle playlist\n"
       << "8) Set volume\n"
       << "9) Show current song\n"
       << "0) Exit\n"
       << "Choice: ";
}

int main() {
  MusicPlayer player;
  bool running = true;

  while (running) {
    printMenu();
    int choice = readInt();

    switch (choice) {
      case 1:
        player.addSong(promptSong());
        break;
      case 2:
        cout << "Enter title to remove: ";
        {
          string title;
          getline(cin, title);
          player.removeSong(title);
        }
        break;
      case 3:
        player.nextSong();
        break;
      case 4:
        player.previousSong();
        break;
      case 5:
        cout << "Position to jump to (1-based): ";
        player.jumpTo(static_cast<size_t>(readInt() - 1));
        break;
      case 6:
        player.showPlaylist();
        break;
      case 7:
        player.toggleShuffle();
        break;
      case 8:
        cout << "Set volume (0-100): ";
        player.setVolume(readInt());
        break;
      case 9:
        player.displayCurrent();
        break;
      case 0:
        running = false;
        break;
      default:
        cout << "Unknown choice, try again." << endl;
        break;
    }
  }

  cout << "Exiting Music Playlist Manager." << endl;
  return 0;
}
