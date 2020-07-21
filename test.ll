@formatString = private constant [2 x i8] c"%%d" 

define i32 @main() {
entry:
  %d = shl i32 2, 3
  call i32 @printf(i8* getelementptr ([2 x i8], [2 x i8]* @formatString , i32 0, i32 0), i32 14)
  ret i32 1
}

declare i32 @printf(i8*, i32)