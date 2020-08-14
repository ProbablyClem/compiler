fn main() {
  global i : int;
  i = 0;
  i = i +1;
  print i;
}

fn func() {
  global y : bool;
  y = true;
  print y;
  i = y;
  print i;
}