#include "stdint.h"
#include "stdio.h"

#define MASK_RST (1 << 0)
#define MASK_EN (1 << 1)
#define MASK_CLR_FIFO 1 << 2
#define BASE_REG_SET 0
#define BASE_REG_TARI 1
#define BASE_REG_FIFO 2
#define BASE_REG_STATUS 3
#define BASE_ID 7
#define PACKET_STD_SIZE 12
#define data_package_size 26
#define data_mask_size 6
#define eop 0b00000000000000000000000000000000

int tari_test = 0b111110100;
int command_test = 0b11111111111111111111111111111111;
int command_test_size = 32;

int check_fifo_full() { return 0; }

void send_package(int package)
{
    printf("package = %04X \n", package);
}
void send_end_of_package()
{
    printf("package_eop = %04X \n", eop);
    printf("---------------------------------------------------------- \n");
}

void mount_package(int command, int size)
{
    int remain_bits_to_send = size;
    int remain_package = command;
    int last_package_size = size % data_package_size;
    printf("remain_bits_to_send = %d \n", remain_bits_to_send);
    while (remain_bits_to_send > 0)
    {
        if (remain_bits_to_send > data_package_size)
        {
            int data_to_fifo = remain_package & 0x1A;
            remain_package = remain_package >> 0x1A;
            int32_t to_fifo = data_to_fifo << 6 | 0x1A;

            while (check_fifo_full())
            {
            }
            printf("to_fifo = %04X \n", to_fifo);
            send_package(to_fifo);

            remain_bits_to_send = remain_bits_to_send - 0x1A;
        }
        else
        {
            int data_to_fifo = remain_package;
            remain_package = remain_package >> last_package_size;
            int32_t to_fifo = data_to_fifo << 6 | last_package_size;

            while (check_fifo_full())
            {
            }

            send_package(to_fifo);
            remain_bits_to_send = remain_bits_to_send - last_package_size;
        }
    }
    send_end_of_package();
}

void select_package(int *commands, int size)
{
    for (int command = 0; command < size; command++)
    {
        // https://stackoverflow.com/questions/29388711/c-how-to-get-length-of-bits-of-a-variable
        unsigned command_size, var = (commands[command] < 0) ? commands[command] : commands[command];
        for (command_size = 0; var != 0; ++command_size)
            var >>= 1;
        
        // int size_log = log2(commands[command])+1;
        //printf("command_size_log = %d \n");
        printf("command = %04X , size = %d \n", commands[command], command_size);
        mount_package(commands[command], command_size);
    }
}

int main()
{
    int commands[4];
    commands[0] = 0b11111111111111111111111111111111; //32
    commands[1] = 0b00000000;                         //8
    commands[2] = 0b1111111111111111;                 //16
    commands[3] = 0b010101010101010101010101010101;   //30
    
    int commands_size = sizeof(commands) / sizeof(int);
    printf("Resume to be sent c0 = %04X , c1 = %04X, c2 = %04X, c3 = %04X \n", commands[0], commands[1],commands[2],commands[3]);
    select_package(commands, commands_size);

    return 0;
}
