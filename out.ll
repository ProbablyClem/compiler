@i = dso_local global i32 0, align 4
@i = dso_local global i32 0, align 4
@formatString = private constant [3 x i8] c"%d\00"
@formatStringendl = private constant [5 x i8] c"%d \0A\00" 

define i32 @main() nounwind {
entry:
%0 = add i32 0, 0
store i32 %0, i32* @i
%1 = load i32, i32* @i
%2 = add i32 0, 1
%3 = add i32 %1, %2
store i32 %3, i32* @i
%4 = load i32, i32* @i
%5 = call i32 @printf(i8* getelementptr ([3 x i8], [3 x i8]* @formatString , i32 0, i32 0), i32 %4)
	 ret i32 0
} 
define i32 @func() nounwind {
entry:
%6 = add i32 0, 5
store i32 %6, i32* @i
%7 = load i32, i32* @i
%8 = add i32 0, 1
%9 = add i32 %7, %8
store i32 %9, i32* @i
%10 = load i32, i32* @i
%11 = call i32 @printf(i8* getelementptr ([3 x i8], [3 x i8]* @formatString , i32 0, i32 0), i32 %10)
	 ret i32 0
} 
declare i32 @printf(i8*, i32)