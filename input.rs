fn func() -> i64 {
  global y : bool;
  global i : i32;
  y = 1;
  print y;
  i = y;
  return y;
}

fn main() -> void {
  i = 0;
  i = i +1;
  print i;
  print func(15);
}

