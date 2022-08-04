#include <stdio.h>
#include <string.h>

using namespace std;

int main(int argc, char** argv)
{
	char* argv1 = argv[1];	// 0 - program, 1 - argument (in this case string)

	if (argc < 2) {
		printf("No parameter provided*/\n");
		return(0);
	}

	int StringToInt = 0; 
	bool overflow = false;
	bool invalidInput = false;

	_asm {

		push eax		// final answer
		push ebx		// symobl
		push edx		// for mul of 10
		push ecx		// pointer to a char in string

		xor eax, eax	// zero'ing
		xor ebx, ebx	// zero'ing
		mov	ecx, argv1	// Address of argv[1] 
		xor edx, edx	// zero'ing
		
		dec ecx			// Loop increases ecx at start so we decrease to compensate 
		
		sLoop:
			
			inc ecx					// ecx points to next char in string
			mov bl, byte ptr[ecx]	// byte of string to bl 
			cmp bl, 0				// compare to zero (string end)
			jz exit_loop			// if zero byte (string end) then jump to exit_loop

			cmp bl, '0'
			jl invalid_input		// if bl < '0', then jump to invalid_input
			cmp bl, '9'
			jg invalid_input		// if bl > '9', then jump to invalid_input

			sub bl, '0'				// char x - 48 = int x

			mov edx, 10
			mul edx					// eax * 10
			jo	det_overflow		// jump if overflow
			add eax, ebx			// eax + digit
			jo	det_overflow		// jump if overflow
		
			jmp sLoop

		invalid_input :			
			mov invalidInput, 1		// bool invalidInput = true
			jmp exit_loop

		det_overflow :
			mov overflow, 1			// bool overflow = true

		exit_loop :
			mov StringToInt, eax

			pop ecx
			pop edx
			pop ebx
			pop eax
	};

	if(invalidInput)
		printf("Error: Invalid input \n");
	if (overflow)
		printf("Error: Input is too big \n");

	printf("string '%s' -> int %d\n\n", argv[1], StringToInt);
	
	if(overflow == false && invalidInput == false)
		printf("*Test (int x += 10) -> %d\n", StringToInt+=10);

	return 0;
}
