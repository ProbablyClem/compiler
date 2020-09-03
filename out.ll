@y = dso_local global i1 0, align 4
@i = dso_local global i32 0, align 4
@formatString = private constant [3 x i8] c"%d\00"
@formatStringendl = private constant [5 x i8] c"%d \0A\00" 

define i64 @func() nounwind {
%1 = add i1 0, 1
store i1 %1, i1* @y
%2 = load i1, i1* @y
%3 = zext i1 %2 to i32
%4 = call i32 @printf(i8* getelementptr ([3 x i8], [3 x i8]* @formatString , i32 0, i32 0), i32 %3)
%5 = load i1, i1* @y
%6 = zext i1 %5 to i32
store i32 %6, i32* @i
%7 = load i1, i1* @y
%8 = zext i1 %7 to i64
ret i64 %8
} 

define void @main() nounwind {
entry:
%0 = add i1 0, 0
%1 = zext i1 %0 to i32
store i32 %1, i32* @i
%2 = load i32, i32* @i
%3 = udiv i32 %2, %4
%4 = add i1 0, 1
%5 = zext i1 %4 to i1
%6 = add i32 %3, %5
%7 = zext i1 %6 to i32
store i32 %7, i32* @i
%8 = load i32, i32* @i
%9 = call i32 @printf(i8* getelementptr ([3 x i8], [3 x i8]* @formatString , i32 0, i32 0), i32 %8)
%10 = add i8 0, 15
%11 = call i64 () @func()
%12 = icmp eq i32 %11, %32734 
%13 = zext i1 %12 to i32
%14 = call i32 @printf(i8* getelementptr ([3 x i8], [3 x i8]* @formatString , i32 0, i32 0), i32 %13)
} 

declare i32 @printf(i8*, i32)