@formatString = private constant [2 x i8] c"%d" 

define i32 @main() {
entry:
%0 = add i32 0, 13
%1 = add i32 0, 6
%2 = sub i32 %0, %1
%3 = add i32 0, 4
%4 = add i32 0, 5
%5 = mul i32 %3, %4
%6 = add i32 %2, %5
%7 = add i32 0, 8
%8 = add i32 0, 3
%9 = udiv i32 %7, %8
%10 = add i32 %6, %9
call i32 @printf(i8* getelementptr ([2 x i8], [2 x i8]* @formatString , i32 0, i32 0), i32 %10)
	ret i32 1
}

declare i32 @printf(i8*, i32)