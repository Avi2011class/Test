#include <stdio.h>
#include <stdlib.h>

#define HLT 0
#define ADD 1
#define SUB 2
#define MOV 3
#define IR 4

void format_reg(int *reg)
{
	while (*reg < 0)
		*reg += 0x100;
	while (*reg > 0xFF)
		*reg -= 0x100;
}

int main(void)
{
	int regs[4] = { 0, 0, 0, 0 };
	int correct = 1;
	int stop = 0;
	while (!stop) {
		int command;
		correct = scanf("%d ", &command);

		if (correct != 1) {
			stop = 1;
			break;
		}

		switch (command) {
		case HLT:
			{
				stop = 1;
				break;
			}
		case ADD:
			{
				unsigned arg_first, arg_second;
				correct =
				    scanf("%u %u", &arg_first, &arg_second);

				if (correct < 2) {
					stop = 1;
					continue;
				}
				regs[arg_first - 5] += regs[arg_second - 5];
				format_reg(&regs[arg_first - 5]);
				break;
			}
		case SUB:
			{
				unsigned arg_first, arg_second;
				correct =
				    scanf("%u %u", &arg_first, &arg_second);
				if (correct < 2) {
					stop = 1;
					continue;
				}
				regs[arg_first - 5] -= regs[arg_second - 5];
				format_reg(&regs[arg_first - 5]);
				break;
			}
		case MOV:
			{
				unsigned arg_first, arg_second;
				correct =
				    scanf("%u %u", &arg_first, &arg_second);
				if (correct < 2) {
					stop = 1;
					continue;
				}
				regs[arg_first - 5] = arg_second;
				format_reg(&regs[arg_first - 5]);
				break;
			}
		case IR:
			{
				size_t i = 0;
				for (i = 0; i < 4; i++)
					printf("%u ", regs[i]);
				printf("\n");
				break;
			}
		default:
			{
				stop = 1;
				break;
			}
		}
	}
	return 0;
}
