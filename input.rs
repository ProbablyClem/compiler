fn func() -> i64 {
  global o : bool;
  y = 1;
  print y;
  i = y;
  return y;

}

fn main() -> void {
  global i : i32;
  i = 0;
  i = i +1;
  print i;
  print func(15);
}

