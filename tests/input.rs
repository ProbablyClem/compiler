fn fred() -> i32 {
  return 20;
}

fn main() -> void {
  global result : i32;
  print 10;
  result = fred(15);
  print result;
  print fred(15)+10;
}