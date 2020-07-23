@i = dso_local global i32 0, align 4
@j = dso_local global i32 0, align 4
@formatString = private constant [3 x i8] c"%d\00"
@formatStringendl = private constant [5 x i8] c"%d \0A\00" 

define i32 @main() {
entry:
%0 = add i32 0, 6
store i32 %0, i32* @i
%1 = add i32 0, 12
store i32 %1, i32* @j
%2 = load i32, i32* @i
%3 = load i32, i32* @j
%4 = icmp ult i32 %2, %3 
%5 = zext i1 %4 to i32
%6 = trunc i32 %5 to i1
br i1 %6, label %L-1, label %L1
L-1:
%7 = load i32, i32* @i
%8 = call i32 @printf(i8* getelementptr ([3 x i8], [3 x i8]* @formatString , i32 0, i32 0), i32 %7)
br label %L2
L1:
%9 = load i32, i32* @j
%10 = call i32 @printf(i8* getelementptr ([3 x i8], [3 x i8]* @formatString , i32 0, i32 0), i32 %9)
br label %L2
L2:
	ret i32 0
}

declare i32 @printf(i8*, i32)