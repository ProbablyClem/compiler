@i = dso_local global i32 0, align 4
@formatString = private constant [3 x i8] c"%d\00"
@formatStringendl = private constant [5 x i8] c"%d \0A\00" 

define i32 @main() {
entry:
%0 = add i32 0, 1
store i32 %0, i32* @i
br label %L1
L1:
%1 = load i32, i32* @i
%2 = add i32 0, 10
%3 = icmp ule i32 %1, %2 
%4 = zext i1 %3 to i32
%5 = trunc i32 %4 to i1
br i1 %5, label %L-2, label %L2
L-2:
%6 = load i32, i32* @i
%7 = call i32 @printf(i8* getelementptr ([3 x i8], [3 x i8]* @formatString , i32 0, i32 0), i32 %6)
%8 = load i32, i32* @i
%9 = add i32 0, 1
%10 = add i32 %8, %9
store i32 %10, i32* @i
br label %L1
L2:
	ret i32 0
}

declare i32 @printf(i8*, i32)