#include <iostream>
#include <string>

using namespace std;

struct Song {
  string title;
  string artist;
  int durationSeconds;
};

template <typename T> class DoublyLinkedList {
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
  // Initialize an empty list.
  DoublyLinkedList() : head(nullptr), tail(nullptr), listSize(0) {}

  // Clean up all nodes.
  ~DoublyLinkedList() { clear(); }

  // Remove all nodes and reset the list.
  void clear() {
    while (head != nullptr) {
      Node *temp = head;
      head = head->next;
      delete temp;
    }
    tail = nullptr;
    listSize = 0;
  }

  // Return the number of nodes.
  size_t size() const { return listSize; }

  // Return the head node pointer.
  Node *getHead() const { return head; }

  // Return the tail node pointer.
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
};

class MusicPlayer {
private:
  DoublyLinkedList<Song> playlist;
  DoublyLinkedList<Song>::Node *current;

  static string formatDuration(int seconds) {
    int minutes = seconds / 60;
    int remaining = seconds % 60;
    string result = to_string(minutes) + ":";
    if (remaining < 10) {
      result += "0";
    }
    result += to_string(remaining);
    return result;
  }

public:
  // Initialize an empty music player.
  MusicPlayer() : current(nullptr) {}

  // Add a new song to the playlist.
  void addSong(const Song &song) {
    playlist.push_back(song);
    if (current == nullptr) {
      current = playlist.getHead();
    }
  }

  // Remove the song at a specific position.
  void removeSong(size_t index) {
    if (playlist.size() == 0) {
      cout << "Your playlist is empty, so there is nothing to remove." << endl;
      return;
    }

    // Walk the list to the requested index.
    DoublyLinkedList<Song>::Node *cursor = playlist.getHead();
    size_t currentIndex = 0;
    while (cursor != nullptr && currentIndex < index) {
      cursor = cursor->next;
      ++currentIndex;
    }

    if (cursor == nullptr) {
      cout << "Position " << index + 1 << " is out of range." << endl;
      return;
    }

    DoublyLinkedList<Song>::Node *target = cursor;

    // If we remove the current song, move to a neighbor.
    if (target == current) {
      current = current->next != nullptr ? current->next : current->prev;
    }

    playlist.remove(target);
  }

  // Move to the next song if possible.
  void nextSong() {
    if (current == nullptr) {
      cout << "Your playlist is empty." << endl;
      return;
    }

    if (current->next == nullptr) {
      cout << "You're already at the end of the playlist." << endl;
      return;
    }

    current = current->next;
  }

  // Move to the previous song if possible.
  void previousSong() {
    if (current == nullptr) {
      cout << "Your playlist is empty." << endl;
      return;
    }

    if (current->prev == nullptr) {
      cout << "You're already at the beginning of the playlist." << endl;
      return;
    }

    current = current->prev;
  }

  // Jump to a specific position in the playlist.
  void jumpTo(size_t index) {
    if (playlist.size() == 0) {
      cout << "Your playlist is empty." << endl;
      return;
    }

    // Walk the list until the requested position.
    DoublyLinkedList<Song>::Node *cursor = playlist.getHead();
    size_t currentIndex = 0;
    while (cursor != nullptr && currentIndex < index) {
      cursor = cursor->next;
      ++currentIndex;
    }

    if (cursor == nullptr) {
      cout << "Position " << index + 1 << " is out of range." << endl;
      return;
    }

    current = cursor;
  }

  // Print the full playlist with the current song marked.
  void showPlaylist() const {
    if (playlist.size() == 0) {
      cout << "Your playlist is empty." << endl;
      return;
    }

    cout << "Here's your playlist:\n";
    // Traverse from head to tail to print all nodes.
    DoublyLinkedList<Song>::Node *cursor = playlist.getHead();
    size_t index = 0;
    while (cursor != nullptr) {
      cout << (cursor == current ? "> " : "  ");
      cout << index + 1 << ". " << cursor->data.title << " by "
           << cursor->data.artist << " ("
           << formatDuration(cursor->data.durationSeconds) << ")";
      if (cursor == current) {
        cout << " <- now playing";
      }
      cout << '\n';
      cursor = cursor->next;
      ++index;
    }
  }

  // Display the current song.
  void displayCurrent() const {
    if (current == nullptr) {
      cout << "Your playlist is empty." << endl;
      return;
    }

    const Song &song = current->data;
    cout << "Now playing: " << song.title << " by " << song.artist << " ("
         << formatDuration(song.durationSeconds) << ")" << endl;
  }

  // Get total number of songs.
  int displayTotal() const { return playlist.size(); }
};

// Read an integer from standard input with validation.
static int readInt() {
  int value;
  while (!(cin >> value)) {
    cin.clear();
    cin.ignore(10000, '\n');
    cout << "Please enter a number: ";
  }
  cin.ignore(10000, '\n');
  return value;
}

// Prompt the user for song details.
static Song promptSong() {
  Song song;
  cout << "Enter the song title: ";
  getline(cin, song.title);
  cout << "Enter the artist name: ";
  getline(cin, song.artist);
  cout << "Enter the duration in seconds: ";
  song.durationSeconds = readInt();
  return song;
}

// Print the main menu options.
static void printMenu(int totalSongs) {
  cout << "\nMusic Playlist Manager (Total songs: " << totalSongs << ")\n"
       << "1) Add a song\n"
       << "2) Remove a song\n"
       << "3) Play next song\n"
       << "4) Play previous song\n"
       << "5) Jump to a position\n"
       << "6) Show the playlist\n"
       << "7) Show the current song\n"
       << "0) Exit\n"
       << "What would you like to do? ";
}

// Program entry point.
int main() {
  MusicPlayer player;
  bool running = true;

  while (running) {
    printMenu(player.displayTotal());
    int choice = readInt();

    switch (choice) {
    case 1:
      player.addSong(promptSong());
      break;
    case 2:
      player.showPlaylist();
      cout << "Enter the position of the song to remove (1-"
           << player.displayTotal() << "): ";
      player.removeSong(static_cast<size_t>(readInt() - 1));
      break;
    case 3:
      player.nextSong();
      break;
    case 4:
      player.previousSong();
      break;
    case 5:
      player.showPlaylist();
      cout << "Enter the position to jump to (1-" << player.displayTotal()
           << "): ";
      player.jumpTo(static_cast<size_t>(readInt() - 1));
      break;
    case 6:
      player.showPlaylist();
      break;
    case 7:
      player.displayCurrent();
      break;
    case 0:
      running = false;
      break;
    default:
      cout << "That option isn't available. Please try again." << endl;
      break;
    }
  }

  cout << "Thanks for using Music Playlist Manager. Goodbye!" << endl;
  return 0;
}
