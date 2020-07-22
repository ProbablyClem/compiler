@x = global i1 0
@formatString = private constant [3 x i8] c"%d\00"
@formatStringendl = private constant [5 x i8] c"%d \0A\00" 

define i32 @main() {
entry:
%0 = add i32 0, 7
%1 = add i32 0, 9
%2 = icmp ult i32 %0, %1 
store i1 %2, i1* @x
%3 = load i1, i1* @x
%4 = call i32 @printf(i8* getelementptr ([3 x i8], [3 x i8]* @formatString , i32 0, i32 0), i1 %3)
%5 = add i32 0, 7
%6 = add i32 0, 9
%7 = icmp ule i32 %5, %6 
store i1 %7, i1* @x
%8 = load i1, i1* @x
%9 = call i32 @printf(i8* getelementptr ([3 x i8], [3 x i8]* @formatString , i32 0, i32 0), i1 %8)
%10 = add i32 0, 7
%11 = add i32 0, 9
%12 = icmp ne i32 %10, %11 
store i1 %12, i1* @x
%13 = load i1, i1* @x
%14 = call i32 @printf(i8* getelementptr ([3 x i8], [3 x i8]* @formatString , i32 0, i32 0), i1 %13)
%15 = add i32 0, 7
%16 = add i32 0, 7
%17 = icmp eq i32 %15, %16 
store i32 %17, i32* @x
%18 = load i32, i32* @x
%19 = call i32 @printf(i8* getelementptr ([3 x i8], [3 x i8]* @formatString , i32 0, i32 0), i32 %18)
%20 = add i32 0, 7
%21 = add i32 0, 7
%22 = icmp uge i32 %20, %21 
store i32 %22, i32* @x
%23 = load i32, i32* @x
%24 = call i32 @printf(i8* getelementptr ([3 x i8], [3 x i8]* @formatString , i32 0, i32 0), i32 %23)
%25 = add i32 0, 7
%26 = add i32 0, 7
%27 = icmp ule i32 %25, %26 
store i32 %27, i32* @x
%28 = load i32, i32* @x
%29 = call i32 @printf(i8* getelementptr ([3 x i8], [3 x i8]* @formatString , i32 0, i32 0), i32 %28)
%30 = add i32 0, 9
%31 = add i32 0, 7
%32 = icmp ugt i32 %30, %31 
store i32 %32, i32* @x
%33 = load i32, i32* @x
%34 = call i32 @printf(i8* getelementptr ([3 x i8], [3 x i8]* @formatString , i32 0, i32 0), i32 %33)
%35 = add i32 0, 9
%36 = add i32 0, 7
%37 = icmp uge i32 %35, %36 
store i32 %37, i32* @x
%38 = load i32, i32* @x
%39 = call i32 @printf(i8* getelementptr ([3 x i8], [3 x i8]* @formatString , i32 0, i32 0), i32 %38)
%40 = add i32 0, 9
%41 = add i32 0, 7
%42 = icmp ne i32 %40, %41 
store i32 %42, i32* @x
%43 = load i32, i32* @x
%44 = call i32 @printf(i8* getelementptr ([3 x i8], [3 x i8]* @formatString , i32 0, i32 0), i32 %43)
	ret i32 0
}

declare i32 @printf(i8*, i32)