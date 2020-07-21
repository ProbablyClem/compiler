@formatString = private constant [2 x i8] c"%d" 

define i32 @main() {
entry:
%0 = add i32 0, 2
%1 = add i32 0, 3
%2 = add i32 0, 5
store i32 mul i32 (%1, %2), i32 %1, 
%0 = add i32 %0, %1
%1 = add i32 0, 8
%2 = add i32 0, 3
%1 = udiv i32 %1, %2
%0 = sub i32 %0, %1
call i32 @printf(i8* getelementptr ([2 x i8], [2 x i8]* @formatString , i32 0, i32 0), i32 %d)
	ret i32 1
}

declare i32 @printf(i8*, i32)