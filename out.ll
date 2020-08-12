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
