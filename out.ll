@fred = global i32 0
@jim = global i32 0
@formatString = private constant [3 x i8] c"%d\00"
@formatStringendl = private constant [5 x i8] c"%d \0A\00" 

define i32 @main() {
entry:
%0 = add i32 0, 5
store i32 %0, i32* @fred
%1 = add i32 0, 12
store i32 %1, i32* @jim
%2 = load i32, i32* @fred
%3 = load i32, i32* @jim
%4 = add i32 %2, %3
%5 = call i32 @printf(i8* getelementptr ([3 x i8], [3 x i8]* @formatString , i32 0, i32 0), i32 %4)
	ret i32 0
}

declare i32 @printf(i8*, i32)