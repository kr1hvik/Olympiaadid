#include <iostream>
#include <vector>
#include <set>
#include <fstream>
#include <sstream>
#include <cassert>

using namespace std;

typedef pair<int, int> square;
typedef pair<int, int> vec;

char char_dir (vec direction) {
  if (direction == make_pair(-1, 0)) {
    return 'W';
  } else if (direction == make_pair(1, 0)) {
    return 'E';
  } else if (direction == make_pair(0, -1)) {
    return 'S';
  } else if (direction == make_pair(0, 1)) {
    return 'N';
  }
}

struct PathGroup {
  vector<square> squares_between;
  vec a_dir, b_dir;

  PathGroup () {
  }
  
  PathGroup (vector<square> _squares_between, vec _a_dir, vec _b_dir) {
    squares_between = _squares_between;
    a_dir = _a_dir;
    b_dir = _b_dir;
  }

  void print () {
    cout << "Path containing the following squares:" << endl;
    for (square sq : squares_between) {
      cout << "  " << sq.first << " " << sq.second << endl;
    }
    cout << "Direction for A: " << char_dir(a_dir) << " " << endl;
    cout << "Direction for B: " << char_dir(b_dir) << " " << endl;
  }

  void visualize () {
    char grid [5][5];
    for (int i = 0; i < 5; i++) {
      for (int j = 0; j < 5; j++) {
        grid[i][j] = '.';
      }
    }

    for (square sq : squares_between) {
      grid[sq.first][sq.second] = '#';
    }

    for (int i = 0; i < 5; i++) {
      for (int j = 0; j < 5; j++) {
        cout << grid[i][j];
      }
      cout << endl;
    }
  }
};

PathGroup mirror_x (PathGroup p) {
  for (int i = 0; i < (int) p.squares_between.size(); i++) {
    p.squares_between[i].first *= -1;
  }
  p.a_dir.first *= -1;
  p.b_dir.first *= -1;
  return p;
}

PathGroup mirror_y (PathGroup p) {
  for (int i = 0; i < (int) p.squares_between.size(); i++) {
    p.squares_between[i].second *= -1;
  }
  p.a_dir.second *= -1;
  p.b_dir.second *= -1;
  return p;
}

PathGroup flip_axes (PathGroup p) {
  for (int i = 0; i < (int) p.squares_between.size(); i++) {
    swap(p.squares_between[i].first, p.squares_between[i].second);
  }
  swap(p.a_dir.first, p.a_dir.second);
  swap(p.b_dir.first, p.b_dir.second);
  return p;
}

square add (square p, square q) {
  return make_pair(p.first + q.first, p.second + q.second);
}

bool path_exists (square a, square b, PathGroup pg, set<square> all_squares) {
  if (add(a, pg.squares_between.back()) != b) {
    return false;
  }

  for (square sq : pg.squares_between) {
    if (all_squares.count(add(a, sq)) == 0) {
      return false;
    }
  }

  return true;
}

bool any_exists (square a, square b, PathGroup pg, set<square> all_squares) {
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      for (int k = 0; k < 2; k++) {
        if (path_exists(a, b, pg, all_squares)) {
          return true;
        }
        pg = flip_axes(pg);
      }
      pg = mirror_y(pg);
    }
    pg = mirror_x(pg);
  }
  return false;
}

typedef pair<square, char> coordinate;

pair<bool, int> parse_int (string s) {
  int ans = 0;
  if (s.size() >= 6) {
    return make_pair(false, 0);
  } else {
    for (char c : s) {
      if (c < '0' || c > '9') {
        return make_pair(false, 0);
      } else {
        ans *= 10;
        ans += c - '0';
      }
    }
    return make_pair(true, ans);
  }
}

pair<bool, char> parse_char (string s) {
  if (s.size() != 1) {
    return make_pair(false, 0);
  } else {
    return make_pair(true, s[0]);
  }
}

pair<bool, coordinate> parse_line (string line) {
  istringstream linestream (line);
  string token;
  vector<string> tokens;
  while (linestream >> token) {
    tokens.push_back(token);
  }

  if (tokens.size() != 3) {
    return make_pair(false, make_pair(make_pair(0, 0), '0'));
  }

  pair<bool, int> x = parse_int(tokens[0]);
  pair<bool, int> y = parse_int(tokens[1]);
  pair<bool, char> c = parse_char(tokens[2]);

  if (!x.first || !y.first || !c.first) {
    return make_pair(false, make_pair(make_pair(0, 0), '0'));
  } else {
    return make_pair(true, make_pair(make_pair(x.second, y.second), c.second));
  }
}

int main (int argc, char **argv) {
  vector<PathGroup> all_paths = {
    PathGroup({{0, 0}, {1, 0}, {2, 0}, {3, 0}},                     {-1, 0}, {1, 0}),
    PathGroup({{0, 0}, {0, 1}, {1, 1}, {2, 1}, {3, 1}},             {-1, 0}, {0, -1}),
    PathGroup({{0, 0}, {0, 1}, {1, 1}, {2, 1}},                     {0, -1}, {0, -1}),
    PathGroup({{0, 0}, {0, 1}, {1, 1}},                             {1, 0},  {0, -1}),
    PathGroup({{0, 0}, {0, 1}, {0, 2}, {1, 2}, {1, 3}},             {0, -1}, {1, 0}),
    PathGroup({{0, 0}, {0, 1}, {0, 2}, {1, 2}, {1, 3}, {1, 4}},     {-1, 0}, {1, 0}),
    PathGroup({{0, 0}, {0, 1}, {1, 1}, {1, 2}, {2, 2}},             {0, -1}, {1, 0}),
    PathGroup({{0, 0}, {0, 1}, {1, 1}, {1, 2}, {2, 2}, {2, 3}},     {-1, 0}, {1, 0}),
    PathGroup({{0, 0}, {0, 1}, {1, 1}, {1, 2}, {1, 3}, {2, 3}},     {0, -1}, {0, 1})
  };
  
  ifstream input_file (argv[1]);
  ifstream answer_file (argv[2]);
  ifstream student_file (argv[3]);

  vector<string> student_output;
  while (student_file) {
    string str;
    getline(student_file, str);
    student_output.push_back(str);
  }
  student_file.close();

  if (!student_output.empty() && student_output.back().empty()) {
    student_output.pop_back();
  }

  if (student_output.empty()) { /* tyhi fail */
    cerr << "Wrong Answer" << endl;
    cout << "0.0" << endl;
    return 0;
  }

  string is_cube;
  answer_file >> is_cube;

  if (student_output[0] != "JAH" && student_output[0] != "EI") {
    cerr << "Presentation Error" << endl;
    cout << "0.0" << endl;
  }
  
  if (is_cube == "EI") {
    if (student_output[0] == "EI") {
      cerr << "OK" << endl;
      cout << "1.0" << endl;
    } else {
      cerr << "Wrong Answer" << endl;
      cout << "0.0" << endl;
    }
    return 0;
  }

  if (student_output[0] != "JAH") {
    cerr << "Wrong Answer" << endl;
    cout << "0.0" << endl;
    return 0;
  }

  if (student_output.size() != 8) {
    cerr << "Correct classification but wrong number of coordinates" << endl;
    cout << "0.5" << endl;
    return 0;
  }

  set<coordinate> student_coords;
  for (int i = 1; i < 8; i++) {
    pair<bool, coordinate> parsed_coords = parse_line(student_output[i]);
    if (!parsed_coords.first) {
      cerr << "Correct classification but unreadable coordinates" << endl;
      cout << "0.5" << endl;
      return 0;
    }
    student_coords.insert(parsed_coords.second);
  }
  
  set<square> all_squares;
  for (int i = 0; i < 6; i++) {
    square current;
    input_file >> current.first >> current.second;
    all_squares.insert(current);
  }

  set<coordinate> prc;
  vector<pair<coordinate, coordinate> > either_or;
  for (set<square>::iterator i = all_squares.begin(); i != all_squares.end(); i++) {
    for (set<square>::iterator j = all_squares.begin(); j != all_squares.end(); j++) {
      square a = *i;
      square b = *j;
      for (PathGroup pg : all_paths) {
        for (int u = 0; u < 2; u++) {
          for (int v = 0; v < 2; v++) {
            for (int w = 0; w < 2; w++) {
              if (path_exists(a, b, pg, all_squares)) {
                either_or.push_back(make_pair(make_pair(a, char_dir(pg.a_dir)),
                                              (make_pair(b, char_dir(pg.b_dir)))));
                prc.insert(make_pair(a, char_dir(pg.a_dir)));
                prc.insert(make_pair(b, char_dir(pg.b_dir)));
              }
              pg = flip_axes(pg);
            }
            pg = mirror_y(pg);
          }
          pg = mirror_x(pg);
        }
      }
    }
  }

  assert(prc.size() == 14);
  
  for (int i = 0; i < (int) either_or.size(); i++) {
    if (!((student_coords.count(either_or[i].first) != 0) ^
          (student_coords.count(either_or[i].second) != 0))) {
      cerr << "Correct classification but bad coordinates" << endl;
      cout << "0.5" << endl;
      return 0;
    }
  }

  cerr << "OK" << endl;
  cout << "1.0" << endl;
  return 0;
}
