typedef char TypeChar;
typedef double TypeDouble;
typedef struct{
	TypeChar *buf;
	int top;
}StackChar;
/* 定义数字栈。 */
typedef struct{
	TypeDouble *buf;
	int top;
}StackDouble;
/* 创建字符栈函数。 */
StackChar* CreateStackChar(void)
{
	StackChar* lpChar;
	lpChar = (StackChar* )malloc(sizeof(StackChar));
	if(!lpChar)
		return 0;
	lpChar->buf = (TypeChar* )malloc(sizeof(TypeChar)*100);
	if(!lpChar->buf)
	{
		free(lpChar);
		return 0;
	}
	lpChar->top = 0;
	return lpChar;
} 
/* 创建数字栈函数。 */
StackDouble* CreateStackDouble(void)
{
	StackDouble* lpDouble;
	lpDouble = (StackDouble* )malloc(sizeof(StackDouble));
	if(!lpDouble)
		return 0;
	lpDouble->buf = (TypeDouble* )malloc(sizeof(TypeDouble)*100);
	if(!lpDouble->buf)
	{
		free(lpDouble);
		return 0;
	}
	lpDouble->top = 0;
	return lpDouble;
}
/* 判断操作符优先级函数。 */
int Prior(TypeChar Operator)
{
	if(Operator=='+'||Operator=='-')
		return 1;
	if(Operator=='*'||Operator=='/'||Operator=='%')
		return 2;
	if(Operator=='^')
		return 3;
}
/* 对字符入字符栈。 */
void PushChar(StackChar* lpChar,TypeChar Operator)
{
	lpChar->buf[lpChar->top] = Operator;
	lpChar->top++;
}
/* 对数字入数字栈。 */
void PushDouble(StackDouble* lpDouble,TypeDouble Num)
{
	lpDouble->buf[lpDouble->top] = Num;
	lpDouble->top++;
}
/* 对字符出字符栈。 */
char PopChar(StackChar* lpChar)
{
	if(lpChar->top == 0)
		return 0;
	lpChar->top--;
	return lpChar->buf[lpChar->top];
}
/* 对数字出数字栈。 */
double PopDouble(StackDouble* lpDouble)
{
	if(lpDouble->top == 0)
		return 0;
	lpDouble->top--;
	return lpDouble->buf[lpDouble->top];
}
/* 用出字符栈的操作符计算从数字栈弹出的两个数。 */
double Calculate(StackDouble* lpDouble,TypeChar Operator)
{
	double StorageDouble,StackPopDouble,FinallyDouble;
	if(Operator=='+')
	{
		StorageDouble = PopDouble(lpDouble);
		StackPopDouble = PopDouble(lpDouble);
		FinallyDouble = StackPopDouble + StorageDouble;
	}
	if(Operator=='-')
	{
		StorageDouble = PopDouble(lpDouble);
		StackPopDouble = PopDouble(lpDouble);
		FinallyDouble = StackPopDouble - StorageDouble;
	}
	if(Operator=='*')
	{
		StorageDouble = PopDouble(lpDouble);
		StackPopDouble = PopDouble(lpDouble);
		FinallyDouble = StackPopDouble + StorageDouble;
		FinallyDouble = StackPopDouble * StorageDouble;
	}
	if(Operator=='/')
	{
		StorageDouble = PopDouble(lpDouble);
		StackPopDouble = PopDouble(lpDouble);
		FinallyDouble = StackPopDouble / StorageDouble;
	}
	if(Operator=='%')
	{
		StorageDouble = PopDouble(lpDouble);
		StackPopDouble = PopDouble(lpDouble);
		FinallyDouble = (int)StackPopDouble * (int)StorageDouble;
	}
	if(Operator=='^')
	{
		StorageDouble = PopDouble(lpDouble);
		StackPopDouble = PopDouble(lpDouble);
		if(StorageDouble>=0)
		{
			FinallyDouble = StackPopDouble;
			while(StorageDouble>1)
			{
				FinallyDouble = FinallyDouble*StackPopDouble;
				StorageDouble--;
			}
			if(StorageDouble==0)
				FinallyDouble = 1;
		}
		else
		{
			StorageDouble = StorageDouble*(-1);
			FinallyDouble = StackPopDouble;
			while(StorageDouble>1)
			{
				FinallyDouble = FinallyDouble*StackPopDouble;
				StorageDouble--;
			}
			FinallyDouble = 1/FinallyDouble;
		}
	}
		return FinallyDouble;
}	
/* 检测字符串输入错误函数。 */
int Error(char* ExpressionChar)
{
	int Left,Right;
	int CharC,LenExpressionChar;
	CharC = 0;
	Left = 0;
	Right = 0;
	LenExpressionChar = strlen(ExpressionChar) - 1;
	if(CharC==0)
	{
		if(('0'>ExpressionChar[CharC]||ExpressionChar[CharC]>'9')&&
		ExpressionChar[CharC]!='+'&&ExpressionChar[CharC]!='-'&&
		ExpressionChar[CharC]!='(')
			return 1;
		if(ExpressionChar[CharC]=='(')
/* 对输入字符串中左括号个数进行计数。 */
			Left++;
	}
	CharC++;
	while(ExpressionChar[CharC]!='\0')
	{
		if(('0'>ExpressionChar[CharC]||ExpressionChar[CharC]>'9')&&
		ExpressionChar[CharC]!='+'&&ExpressionChar[CharC]!='-'&&
		ExpressionChar[CharC]!='*'&&ExpressionChar[CharC]!='/'&&
		ExpressionChar[CharC]!='%'&&ExpressionChar[CharC]!='^'&&
		ExpressionChar[CharC]!='('&&ExpressionChar[CharC]!=')'&&
		ExpressionChar[CharC]!='.')
			return 1;
		if(ExpressionChar[CharC]=='+'||ExpressionChar[CharC]=='-')
		{
			if(('0'>ExpressionChar[CharC-1]||ExpressionChar[CharC-1]>'9')&&
			ExpressionChar[CharC-1]!='('&&ExpressionChar[CharC-1]!=')'||
			('0'>ExpressionChar[CharC+1]||ExpressionChar[CharC+1]>'9')&&
			ExpressionChar[CharC+1]!='('&&ExpressionChar[CharC+1]!=')')
				return 1;
		}
		if(ExpressionChar[CharC]=='*'||ExpressionChar[CharC]=='/'||
		ExpressionChar[CharC]=='%'||ExpressionChar[CharC]=='^')
		{
			if(('0'>ExpressionChar[CharC-1]||ExpressionChar[CharC-1]>'9')&&
			ExpressionChar[CharC-1]!=')'||ExpressionChar[CharC+1]!='('&&
			('0'>ExpressionChar[CharC+1]||ExpressionChar[CharC+1]>'9'))
				return 1;
		}
		if(ExpressionChar[CharC]=='(')
		{
			if(('0'>ExpressionChar[CharC+1]||ExpressionChar[CharC+1]>'9')&&
			ExpressionChar[CharC+1]!='('&&ExpressionChar[CharC+1]!='+'&&
			ExpressionChar[CharC+1]!='-'||('0'<=ExpressionChar[CharC-1]&&
			ExpressionChar[CharC-1]<='9')||ExpressionChar[CharC-1]==')')
				return 1;
/* 对输入字符串中左括号个数进行计数。 */
			Left++;
		}
		if(ExpressionChar[CharC]==')')
		{
			if(('0'<=ExpressionChar[CharC+1]&&ExpressionChar[CharC+1]<='9')||
			ExpressionChar[CharC+1]=='('||('0'>ExpressionChar[CharC-1]||
			ExpressionChar[CharC-1]>'9')&&ExpressionChar[CharC-1]!=')')
				return 1;
/* 对输入字符串中右括号个数进行计数。 */
			Right++;
		}
		if(ExpressionChar[CharC]=='.')
		{
			if(('0'>ExpressionChar[CharC-1]||ExpressionChar[CharC-1]>'9')&&
			('0'>ExpressionChar[CharC+1]||ExpressionChar[CharC+1]>'9'))
				return 1;
		}
		CharC++;
	}
	if(('0'>ExpressionChar[LenExpressionChar]||ExpressionChar[LenExpressionChar]>'9')&&
	ExpressionChar[LenExpressionChar]!=')')
			return 1;
/* 若字符串中左括号与右括号相等，则返回1，即字符串输入错误。 */
	if(Left!=Right)
		return 1;
/* 若字符串无误，则返回0。*/
	return 0;
}
int CharToDoubleAndChar(StackChar* lpChar,StackDouble* lpDouble,char* ExpressionChar)
{
	double Num0,Num1,Num2,CounterNum;
	int CharC;
	char TmpChar;
	CharC = 0;
/* 对检测字符串输入错误函数进行调用。 */
	if(Error(ExpressionChar))
		return 1;
	while(ExpressionChar[CharC]!='\0')
	{
		if('0'<=ExpressionChar[CharC]&&ExpressionChar[CharC]<='9')
		{
			Num1 = 0.0;
			CounterNum = 10;
			while('0'<=ExpressionChar[CharC]&&ExpressionChar[CharC]<='9')
			{
				Num1 = Num1*CounterNum + (ExpressionChar[CharC] - '0');
				CharC++;
			}
			if(ExpressionChar[CharC]=='.')
			{
				CharC++;
				Num2 = 0.0;
				CounterNum = 0.1;
				while('0'<=ExpressionChar[CharC]&&ExpressionChar[CharC]<='9')
				{
					Num2 = Num2 + (ExpressionChar[CharC] - '0')*CounterNum;
					CounterNum = CounterNum*0.1;
					CharC++;
				}
			}
/* 判断一个浮点数中是否存在两个小数点，若有返回1，即判为字符串输入错误。 */
			if(ExpressionChar[CharC]=='.')
				return 1;
			Num1 = Num1 + Num2;
			PushDouble(lpDouble,Num1);
		}
		if(ExpressionChar[CharC]=='+'||ExpressionChar[CharC]=='-'||
		ExpressionChar[CharC]=='*'||ExpressionChar[CharC]=='/'||
		ExpressionChar[CharC]=='%'||ExpressionChar[CharC]=='^')
		{
			if(Prior(lpChar->buf[lpChar->top - 1])<Prior(ExpressionChar[CharC])&&
			(lpChar->top - 1>=0)||lpChar->buf[lpChar->top - 1]=='('&&
			(lpChar->top - 1>=0)||lpChar->top==0)
			{
				PushChar(lpChar,ExpressionChar[CharC]);
				CharC++;
			}
		}
		if(ExpressionChar[CharC]=='+'||ExpressionChar[CharC]=='-'||
		ExpressionChar[CharC]=='*'||ExpressionChar[CharC]=='/'||
		ExpressionChar[CharC]=='%'||ExpressionChar[CharC]=='^')
		{
			if(Prior(lpChar->buf[lpChar->top - 1])>=Prior(ExpressionChar[CharC])&&
			(lpChar->top - 1>=0)&&lpChar->buf[lpChar->top - 1]!='(')
			{
				while(Prior(lpChar->buf[lpChar->top - 1])>=Prior(ExpressionChar[CharC])&&
				(lpChar->top - 1>=0)&&lpChar->buf[lpChar->top - 1]!='(')
				{
					TmpChar = PopChar(lpChar);
					PushDouble(lpDouble,Calculate(lpDouble,TmpChar));
				}
				PushChar(lpChar,ExpressionChar[CharC]);
				CharC++;
			}
		}
		if(ExpressionChar[CharC]=='(')
		{
			Num0 = 0.0;
			PushChar(lpChar,ExpressionChar[CharC]);
			CharC++;
			PushDouble(lpDouble,Num0);
			if('0'<=ExpressionChar[CharC]&&ExpressionChar[CharC]<='9'||
			ExpressionChar[CharC]=='(')
				PushChar(lpChar,'+');
			if(ExpressionChar[CharC]=='-')
			{
				PushChar(lpChar,ExpressionChar[CharC]);
				CharC++;
			}
		}
		if(ExpressionChar[CharC]==')')
		{
			TmpChar = PopChar(lpChar);
			while(TmpChar!='(')
			{
/* 判断输入字符串中括号是否匹配，若不匹配则返回1，即判为字符串输入错误。 */
				if(TmpChar==0)
					return 1;
				PushDouble(lpDouble,Calculate(lpDouble,TmpChar));
				TmpChar = PopChar(lpChar);
			}
			CharC++;
		}
	}
	TmpChar = PopChar(lpChar);
	while(TmpChar!=0)
	{
		PushDouble(lpDouble,Calculate(lpDouble,TmpChar));
		TmpChar = PopChar(lpChar);
	}
/*  若字符串输入正确，则计算其结果，并返回0。 */
	return 0;
}
main()
{
	StackChar* lpChar;
	StackDouble* lpDouble;
	char ExpressionChar[100];
	lpChar = CreateStackChar();
	lpDouble = CreateStackDouble();
	while(1)
	{
		printf("please input Expression:\n"); 
		gets(ExpressionChar);
		if(!CharToDoubleAndChar(lpChar,lpDouble,ExpressionChar))
		{
			printf("%f",*lpDouble->buf);
			break;
		}
		printf("The Expression is error,please input angin!\n");
	}
}