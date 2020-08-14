@i = dso_local global i32 0, align 4
@y = dso_local global i1 0, align 4
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
%1 = add i1 0, 1
store i1 %1, i1* @y
%2 = load i1, i1* @y
%3 = zext i1 %2 to i32
%4 = call i32 @printf(i8* getelementptr ([3 x i8], [3 x i8]* @formatString , i32 0, i32 0), i32 %3)
%5 = load i1, i1* @y
%6 = zext i1 %5 to i32
store i32 %6, i32* @i
%7 = load i32, i32* @i
%8 = call i32 @printf(i8* getelementptr ([3 x i8], [3 x i8]* @formatString , i32 0, i32 0), i32 %7)
ret i32 0
} 

declare i32 @printf(i8*, i32)