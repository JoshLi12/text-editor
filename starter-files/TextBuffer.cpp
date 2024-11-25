#include <iostream>
#include <string>
#include "TextBuffer.hpp"

using namespace std;

// constructor
TextBuffer::TextBuffer() : cursor(data.end()), row(1), column(0), index(0) {}

bool TextBuffer::forward() {
    if (is_at_end()) {
      return false;
    }
    else if (*cursor == '\n') {
      ++row;
      column = 0;
    }
    else {
      ++column;

    }
    ++cursor;
    ++index;
    return true;
  }

bool TextBuffer::backward() {
    if (cursor == data.begin()) {
        return false;
    }
    --cursor;
    --index;

    if (*cursor == '\n') {
        --row;
        column = compute_column();
    }
    else {
        --column;
    }
    return true;

  }

  void TextBuffer::insert(char c) {
    data.insert(cursor, c);
    if (c == '\n') {
        ++row;
        column=0;
    } else {
        ++column;
    }
    ++index;

  }

bool TextBuffer::remove() {
    if (is_at_end()) {
      return false;
    }
    data.erase(cursor);
    return true;
  }

  void TextBuffer::move_to_row_start() {
    if (cursor == data.end()) {
        --cursor;
        --index;
    }
    while (cursor != data.begin() && *(cursor) != '\n') {
      --cursor;
      --index;
    }
    if (*cursor == '\n') {
        ++cursor;
        ++index;
    }
    column = 0;
  }

  void TextBuffer::move_to_row_end() {
    while (!is_at_end() && *cursor != '\n') {
      ++cursor;
      ++column;
      ++index;
    }
  }

void TextBuffer::move_to_column(int new_column) {
    if (new_column > column) {
      while (column < new_column && !is_at_end() && *cursor != '\n') {
        forward();
      }
    }
    else {
      while (column > new_column) {
        --cursor;
        --index;
        --column;
      }
    }
  }

bool TextBuffer::up() {
    if (row == 1) {
      return false;
    }
    int temp = column;
    move_to_row_start();
    backward();
    // move_to_row_start();
    move_to_column(temp);

    // while (column < temp && !is_at_end() && *cursor != '\n') {
    //     // cout << column << endl;
    //     ++cursor;
    //     ++index;
    // }
    // column = compute_column();

    return true;
}

bool TextBuffer::down() {
    int temp = column;
    move_to_row_end();
    if (is_at_end()) {
        return false;
    }
    forward();

    while (column < temp && !is_at_end()) {
        if (*cursor != '\n') {
            ++cursor;
            ++index;
            ++column;
        }
    }
    return true;
  }

 bool TextBuffer::is_at_end() const {
    if (cursor == data.end()) {
      return true;
    }
     else {
      return false;
     }
  }

  char TextBuffer::data_at_cursor() const {
    return *cursor;
  }

int TextBuffer::get_row() const {
    return row;
}

int TextBuffer::get_column() const {
    return column;
}

int TextBuffer::get_index() const {
    return index;
}

int TextBuffer::size() const {
    return data.size();
}

std::string TextBuffer::stringify() const {
    return std::string(data.begin(), data.end());
}

int TextBuffer::compute_column() const {
    Iterator temp_cursor = cursor;
    int temp_col = 0;
    while (temp_cursor != data.begin()) {
        --temp_cursor;
        if (*temp_cursor == '\n') {
            return temp_col;
        }
        ++temp_col;
    }
    return temp_col;
}