#include "stdint.h"
#include "stdio.h"

#define MASK_RST (1 << 0)
#define MASK_EN (1 << 1)
#define MASK_CLR_FIFO 1 << 2
#define BASE_REG_SET 0
#define BASE_REG_TARI 1
#define BASE_REG_FIFO 2
#define BASE_ID 7
#define PACKET_STD_SIZE 12
#define data_package_size 26
#define data_mask_size 6

int tari_test = 0b111110100;

int command_ack = 0b111111111111111111111111111111;

void send_package(int pacote, int size)
{
    int remain_bits_to_send = size;
    int remain_package = pacote;
    printf("Pacote= %d , remain_package = %d\n", pacote, remain_package);
    int last_package_size = size % data_package_size;

    while (remain_bits_to_send > 0)
    {
        printf("remain_bits_to_send = %d \n", remain_bits_to_send);

        if (remain_bits_to_send > data_package_size)
        {
            printf("Package Bigger Than fifo capacity------------------------ \n");
            printf("remain_pack = %04X \n", remain_package);
            int data_to_fifo = remain_package & 0x1A;
            printf("data_to_fifo = %04X \n", data_to_fifo);
            remain_package = remain_package >> 0x1A;
            int32_t to_fifo = data_to_fifo << 6 | 0x1A;
            remain_bits_to_send = remain_bits_to_send - 0x1A;
            printf("Resume:data_to_fifo = %04X\nmask_package = %04X\nremain_package= %04X\nto_fifo = %04X\n", data_to_fifo, last_package_size, remain_package, to_fifo);
            printf("--------------------------------------------------------- \n");
        }
        else
        {
            printf("Package Smaller Than fifo capacity------------------------ \n");
            printf("remain_pack = %04X \n", remain_package);
            int data_to_fifo = remain_package;
            printf("data_to_fifo = %04X \n", data_to_fifo);
            remain_package = remain_package >> last_package_size;
            int32_t to_fifo = data_to_fifo << 6 | last_package_size;
            remain_bits_to_send = remain_bits_to_send - last_package_size;
            printf("Resume:data_to_fifo = %04X\nmask_package = %04X\nremain_package= %04X\nto_fifo = %04X\n", data_to_fifo, last_package_size, remain_package, to_fifo);
            printf("---------------------------------------------------------- \n");
        }
        printf("\n");
    }
}

int main()
{
    send_package(command_ack, 30);
    return 0;
}