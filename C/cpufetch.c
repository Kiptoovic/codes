#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int register1;
    int register2;
    int program_counter;
} CPU;

void fetchDecodeExecute(CPU *cpu, char *instruction) {
    int operand1, operand2;
    char operation;

    // Decode the instruction (for simplicity, assume instructions are of the form: "OP operand1 operand2")
    sscanf(instruction, "%c %d %d", &operation, &operand1, &operand2);

    // Execute the instruction based on the operation
    switch (operation) {
        case 'a': // Addition
            cpu->register1 = operand1 + operand2;
            break;
        case 's': // Subtraction
            cpu->register1 = operand1 - operand2;
            break;
        case 'm': // Multiplication
            cpu->register1 = operand1 * operand2;
            break;
        default:
            printf("Invalid operation\n");
            return;
    }

    // Update program counter (for simplicity, just increment)
    cpu->program_counter++;
}

int main() {
    CPU cpu = {0};
    char instruction[20];

    // Instruction fetch, decode, and execute loop
    while (1) {
        printf("Enter instruction (e.g., a 10 5 for addition of 10 and 5) or 'exit' to quit: ");
        fgets(instruction, 20, stdin);

        if (strncmp(instruction, "exit", 4) == 0) {
            break;
        }
        fetchDecodeExecute(&cpu, instruction);
        printf("Result in Register1: %d, Program Counter: %d\n", cpu.register1, cpu.program_counter);
    }
    return 0;
}